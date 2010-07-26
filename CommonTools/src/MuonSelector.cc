#include "KoPFA/CommonTools/interface/MuonSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

MuonSelector::MuonSelector(const edm::ParameterSet& cfg)
{

  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  muonSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  produces<std::vector<pat::Muon> >("");
}

MuonSelector::~MuonSelector()
{

}

void MuonSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  iEvent.getByLabel(muonLabel_, muons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 

  std::auto_ptr<std::vector<pat::Muon> > pos(new std::vector<pat::Muon>());

  for (unsigned int i=0; i < muons_->size();++i){
    const pat::Muon muon = muons_->at(i);
    pat::strbitset muonSel = muonSelector_.getBitTemplate();
    muonSelector_( muon, beamSpot_, muonSel );

    bool passed = muonSel.test("VBTF");

    if(passed){
      pos->push_back((*muons_)[i]);
    }
  }

  iEvent.put(pos);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(MuonSelector);



