#include "KoPFA/CommonTools/interface/TriggerTool.h"

#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/EventSetup.h"



TriggerTool::TriggerTool(const edm::ParameterSet& iConfig) {
  
using namespace std;
using namespace edm;

  processName_ = iConfig.getParameter< string >("processName");

  inputTagTriggerEvent_ 
    = iConfig.getParameter<InputTag>("TriggerEvent");

  inputTagTriggerResults_
    = iConfig.getParameter<InputTag>("TriggerResults");

  HLTPath_ = iConfig.getParameter< string >("HLTPath");

  // cout<<"TriggerTool on path "<<HLTPath_<<endl;

  verbose_ = 
    iConfig.getUntrackedParameter<bool>("verbose",false);


  produces< ParticleCollection >();
  
}



TriggerTool::~TriggerTool() { }



void TriggerTool::beginJob() { }

// ---------------------------------------------------------------------------------------------

// -- Retrieve from the provenance the HLT configuration. To be done in
// -- beginRun() since the configuration may not be the same when one
// -- analyzes more than one run.

void TriggerTool::beginRun(edm::Run& iRun, edm::EventSetup const& iSetup)
{
  using namespace std;
  using namespace edm;


  bool changed(true);
  if (hltConfig_.init(iRun,iSetup,processName_,changed)) {
    cout << " ici " << endl;
    if (changed) {
      // check if trigger name in (new) config
      if (HLTPath_!="@") { // "@" means: analyze all triggers in config
        const unsigned int n(hltConfig_.size());
        const unsigned int triggerIndex(hltConfig_.triggerIndex(HLTPath_));
        if (triggerIndex>=n) {
          cout << "TriggerTool::beginRun :"
               << " TriggerName " << HLTPath_
               << " not available in (new) config!" << endl;
          cout << "Available TriggerNames are: " << endl;
          hltConfig_.dump("Triggers");
        }
      }
      if (verbose_) {
       	hltConfig_.dump("Streams");
       	hltConfig_.dump("Datasets");
      }
      // hltConfig_.dump("PrescaleTable");
      // hltConfig_.dump("ProcessPSet");
    }
  } else {
    cout << " TriggerTool::beginRun: "
         << " config extraction failure with process name "
         << processName_ << endl;
  }
}

// ---------------------------------------------------------------------------------------------



void TriggerTool::produce(edm::Event& iEvent, 
			  const edm::EventSetup& iSetup) {
  
  using namespace trigger;
  using namespace edm;
  using namespace std;

  auto_ptr< ParticleCollection > 
    pOutput( new ParticleCollection ); 
 


  // get event products
  iEvent.getByLabel(inputTagTriggerResults_,triggerResultsHandle_);
  if (!triggerResultsHandle_.isValid()) {
    cout << "TriggerTool::produce: Error in getting TriggerResults product from Event!" << endl;
    return;
  }
  iEvent.getByLabel(inputTagTriggerEvent_,triggerEventHandle_);
  if (!triggerEventHandle_.isValid()) {
    cout << "TriggerTool::produce: Error in getting TriggerEvent product from Event!" << endl;
    return;
  }
  // sanity check

  assert(triggerResultsHandle_->size()==hltConfig_.size());

  const unsigned int n(hltConfig_.size());
  const unsigned int triggerIndex(hltConfig_.triggerIndex(HLTPath_));

  assert(triggerIndex==iEvent.triggerNames(*triggerResultsHandle_).triggerIndex(HLTPath_));

  if (triggerIndex>=n) {
    cout << "TriggerTool::produce: path "
         << HLTPath_ << " - not found!" << endl;
    return;
  }

  if ( triggerResultsHandle_->error(triggerIndex) ) {
        cout << " The path returned error... " << endl;
	iEvent.put( pOutput );
        return;
  }

  if ( ! triggerResultsHandle_->wasrun(triggerIndex) ) {
        cout << " The path was not run... " << endl;
	iEvent.put( pOutput );
        return;
  }

  // look only at events which pass the trigger
  if ( ! triggerResultsHandle_->accept(triggerIndex) ) {
	iEvent.put( pOutput );
        return;
  }

  // modules on this trigger path
  const unsigned int m(hltConfig_.size(triggerIndex));
  const vector<string>& moduleLabels(hltConfig_.moduleLabels(triggerIndex));

  const unsigned int moduleIndex(triggerResultsHandle_->index(triggerIndex));
  assert (moduleIndex<m);


  // Results from TriggerEvent product - Attention: must look only for
  // modules actually run in this path for this event!
  for (unsigned int j=0; j<=moduleIndex; ++j) {

    const string& moduleLabel(moduleLabels[j]);
    const string  moduleType(hltConfig_.moduleType(moduleLabel));
    if (moduleType =="HLTLevel1GTSeed") continue;

        // cout << "module Label Type " << moduleLabel << " " << moduleType << endl;
    // check whether the module is packed up in TriggerEvent product
    const unsigned int filterIndex(triggerEventHandle_->filterIndex(InputTag(moduleLabel,"",processName_)));

    if (filterIndex<triggerEventHandle_->sizeFilters()) {
      if (verbose_ ) {
      	cout << "module Label Type " << moduleLabel << " " << moduleType << endl;
      	cout << " 'L3' filter in slot " << j << " - label/type " << moduleLabel << "/" << moduleType << endl;
      }
      const Vids& VIDS (triggerEventHandle_->filterIds(filterIndex));
      const Keys& KEYS(triggerEventHandle_->filterKeys(filterIndex));
      const size_type nI(VIDS.size());
      const size_type nK(KEYS.size());
      assert(nI==nK);
      const size_type n(max(nI,nK));
      if (verbose_) cout << "   " << n  << " accepted 'L3' objects found: " << endl;
      const TriggerObjectCollection& TOC(triggerEventHandle_->getObjects());
      for (size_type i=0; i!=n; ++i) {
        const TriggerObject& TO(TOC[KEYS[i]]);
	if (verbose_) {
          cout << "   " << i << " " << VIDS[i] << "/" << KEYS[i] << ": "
               << TO.id() << " " << TO.pt() << " " << TO.eta() << " " << TO.phi() << " " << TO.mass()
               << endl;
	}
    //converting the trigger object into a particle 
	reco::Particle particle = TO.particle();
	pOutput->push_back( particle );

      }
    }
  }






/*
  edm::Handle< TriggerEvent > teHandle; 
  iEvent.getByLabel(inputTagTriggerEvent_, teHandle );

  const TriggerEvent& triggerEvent = *teHandle;

  const TriggerObjectCollection& objColl = triggerEvent.getObjects();
  for(unsigned i=0; i<objColl.size(); ++i ) {
    const TriggerObject& obj = objColl[i];
    
    //converting the trigger object into a particle 
    reco::Particle particle = obj.particle();
     
    pOutput->push_back( particle );
  }
*/


  iEvent.put( pOutput );
  
}



#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/InputSourceMacros.h"
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(TriggerTool);



