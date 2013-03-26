// -*- C++ -*-
//
// Package:    JetFilter
// Class:      JetFilter
//
/**\class JetFilter JetFilter.cc UserCode/JetFilter/src/JetFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: JetFilter.cc,v 1.12 2012/06/18 14:33:43 tjkim Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "CommonTools/Utils/interface/PtComparator.h"

//
// class declaration
//
using namespace edm;
using namespace std;

class JetFilter : public edm::EDFilter {
   public:
      explicit JetFilter(const edm::ParameterSet&);
      ~JetFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      double resolutionFactor(const pat::Jet&);
      // ----------member data ---------------------------

      typedef pat::JetCollection::const_iterator JI;

      bool applyFilter_;
      bool bJetFirst_; 
      string bTagAlgo_;
      double bTagValue_;
      edm::InputTag rhoLabel_;
      edm::InputTag jetLabel_;
      edm::InputTag metLabel_;
      string outputJetLabel_;
      string outputMETLabel_;
      edm::InputTag vertexLabel_;
      /// loose jet ID.

      unsigned int min_;
      double ptcut_;
      double absetacut_;
      bool doJecFly_;
      bool doResJec_;
      bool isRealData_;
      bool doJecUnc_;
      bool up_;
      bool doJERUnc_;
      double resolutionFactor_;
      string globalTag_;

      FactorizedJetCorrector* resJetCorrector_;
      JetCorrectionUncertainty *jecUnc_;

      edm::ParameterSet pfJetIdParams_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
JetFilter::JetFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  applyFilter_=ps.getUntrackedParameter<bool>("applyFilter",false);
  bJetFirst_ = ps.getUntrackedParameter<bool>("bJetFirst",false);
  bTagAlgo_ = ps.getUntrackedParameter<string>("bTagAlgo","combinedSecondaryVertexBJetTags");
  bTagValue_ = ps.getUntrackedParameter<double>("bTagValue",0.244);
  rhoLabel_ =  ps.getParameter<edm::InputTag>("rhoLabel");
  jetLabel_ =  ps.getParameter<edm::InputTag>("jetLabel");
  metLabel_ = ps.getParameter<edm::InputTag>("metLabel");
  vertexLabel_ =  ps.getUntrackedParameter<edm::InputTag>("vertexLabel");
  min_ = ps.getUntrackedParameter<unsigned int>("min",1);
  ptcut_ = ps.getUntrackedParameter<double>("ptcut",30.0);
  absetacut_ = ps.getUntrackedParameter<double>("absetacut",2.5);
  pfJetIdParams_ = ps.getParameter<edm::ParameterSet> ("looseJetId");
  doJecFly_ = ps.getUntrackedParameter<bool>("doJecFly", true);
  doResJec_ = ps.getUntrackedParameter<bool>("doResJec", false);
  doJecUnc_ = ps.getUntrackedParameter<bool>("doJecUnc", false);
  up_ = ps.getUntrackedParameter<bool>("up", true); // uncertainty up
  doJERUnc_ = ps.getUntrackedParameter<bool>("doJERUnc", false);
  resolutionFactor_ = ps.getUntrackedParameter<double>("resolutionFactor", 1.0);
  globalTag_ = ps.getUntrackedParameter<string>("globalTag","GR_R_42_V23");

  resJetCorrector_ = 0;
  jecUnc_ = 0;

  outputJetLabel_ = jetLabel_.label();
  outputMETLabel_ = metLabel_.label();

  produces<std::vector<pat::Jet> >("Jets");
  produces<std::vector<pat::MET> >("MET");

}


JetFilter::~JetFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
JetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  isRealData_ = iEvent.isRealData();

  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  std::auto_ptr<std::vector<pat::Jet> > corrJets(new std::vector<pat::Jet>());
  std::auto_ptr<std::vector<pat::MET> > corrMETs(new std::vector<pat::MET>());
  std::auto_ptr<std::vector<pat::Jet> > corrbJets(new std::vector<pat::Jet>());

  edm::Handle<pat::JetCollection> Jets;
  iEvent.getByLabel(jetLabel_,Jets);

  edm::Handle<pat::METCollection> MET;
  iEvent.getByLabel(metLabel_,MET);
  pat::METCollection::const_iterator met = MET->begin();
  double met_x = met->px();
  double met_y = met->py();

  edm::Handle<double>  rho;
  iEvent.getByLabel(rhoLabel_, rho);

  edm::Handle<reco::VertexCollection> recVtxs_;
  iEvent.getByLabel(vertexLabel_,recVtxs_);

  const int nv = recVtxs_->size();

  PFJetIDSelectionFunctor looseJetIdSelector_(pfJetIdParams_);

  for (JI it = Jets->begin(); it != Jets->end(); ++it) {
    pat::Jet correctedJet = *it;

    if(abs(it->eta()) >= 2.4) continue;

    pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    bool passId = looseJetIdSelector_( *it, looseJetIdSel);

    if(!passId) continue;

    double scaleF = 1.0;
    if(doJecFly_){
      correctedJet.scaleEnergy( it->jecFactor(0) ); //set it to uncorrected jet energy
      //debug
      //cout << "uncorrected jet pt= " << correctedJet.pt() << endl;
      reco::Candidate::LorentzVector uncorrJet = it->correctedP4(0);

      resJetCorrector_->setJetEta( uncorrJet.eta() );
      resJetCorrector_->setJetPt ( uncorrJet.pt() );
      resJetCorrector_->setJetE  ( uncorrJet.energy() );
      resJetCorrector_->setJetA  ( it->jetArea() );
      resJetCorrector_->setRho   ( *(rho.product()) );
      resJetCorrector_->setNPV   ( nv );

      scaleF = resJetCorrector_->getCorrection();
    }

    correctedJet.scaleEnergy( scaleF );

    if(doJecUnc_){
      jecUnc_->setJetEta(correctedJet.eta());
      jecUnc_->setJetPt(correctedJet.pt());
      met_x += correctedJet.px();
      met_y += correctedJet.py();
      double unc = jecUnc_->getUncertainty(up_);
      double ptscaleunc = 0;
      if(up_) ptscaleunc = 1 + unc;
      else ptscaleunc = 1 - unc;
      correctedJet.scaleEnergy( ptscaleunc );
      met_x -= correctedJet.px();
      met_y -= correctedJet.py();
    }

    if(doJERUnc_){
      double jetpx = correctedJet.px();
      double jetpy = correctedJet.py();
      correctedJet.scaleEnergy( resolutionFactor(correctedJet)  );
      double dpx = correctedJet.px() - jetpx;
      double dpy = correctedJet.py() - jetpy;
      met_x -= dpx;
      met_y -= dpy;
    } 

    //debug
    //cout << "corrected= " << correctedJet.pt() << " default= " << it->pt() << endl;

    if ( correctedJet.pt() > ptcut_ ) {
      if( bJetFirst_ ){
        double bTagValue = correctedJet.bDiscriminator(bTagAlgo_);
        if( bTagValue > bTagValue_ ) {
          corrbJets->push_back(correctedJet);
        }else{
          corrJets->push_back(correctedJet);
        }
      }else{
        corrJets->push_back(correctedJet);
      }
    }

  }

  pat::MET corrMET(reco::MET ( sqrt(met_x*met_x + met_y*met_y)   , reco::MET::LorentzVector(met_x,met_y,0,sqrt(met_x*met_x + met_y*met_y))  , reco::MET::Point(0,0,0)));
  corrMETs->push_back(corrMET);

  // Jets passing identification criteria are sorted by decreasing pT
  std::sort(corrJets->begin(), corrJets->end(), GreaterByPt<pat::Jet>());
  std::sort(corrbJets->begin(), corrbJets->end(), GreaterByPt<pat::Jet>());

  if( bJetFirst_ ){
    corrJets->insert( corrJets->begin(), corrbJets->begin(), corrbJets->end());
  }

  if( corrJets->size() >= min_ ) accepted = true;

  iEvent.put(corrJets, "Jets");
  iEvent.put(corrMETs, "MET");

  if( applyFilter_ ) return accepted;
  else return true;

}

double
JetFilter::resolutionFactor(const pat::Jet& jet)
{
    if(!jet.genJet()) {
      return 1.;
    }
    double factor = 1. + (resolutionFactor_-1.)*(jet.pt() - jet.genJet()->pt())/jet.pt();
    return (factor<0 ? 0. : factor);
}

// ------------ method called once each job just before starting event loop  ------------
void
JetFilter::beginJob()
{

  if ( doJecFly_ ){
    edm::FileInPath jecL1File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L1FastJet_AK5PFchs.txt");
    edm::FileInPath jecL2File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L2Relative_AK5PFchs.txt");
    edm::FileInPath jecL3File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L3Absolute_AK5PFchs.txt");
    edm::FileInPath jecL2L3File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L2L3Residual_AK5PFchs.txt");
    std::vector<JetCorrectorParameters> jecParams;
    jecParams.push_back(JetCorrectorParameters(jecL1File.fullPath()));
    jecParams.push_back(JetCorrectorParameters(jecL2File.fullPath()));
    jecParams.push_back(JetCorrectorParameters(jecL3File.fullPath()));
    if( doResJec_ ) {
      jecParams.push_back(JetCorrectorParameters(jecL2L3File.fullPath()));
    }
    resJetCorrector_ = new FactorizedJetCorrector(jecParams);
  }

  edm::FileInPath jecUncFile("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_Uncertainty_AK5PFchs.txt");
  jecUnc_ = new JetCorrectionUncertainty(jecUncFile.fullPath());

}

// ------------ method called once each job just after ending the event loop  ------------
void
JetFilter::endJob() {
  if ( resJetCorrector_ ) delete resJetCorrector_;
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetFilter);



