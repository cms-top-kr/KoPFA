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
// $Id: JetFilter.cc,v 1.7 2012/05/02 16:01:22 jhgoh Exp $
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
  jetLabel_ =  ps.getParameter<edm::InputTag>("jetLabel");
  metLabel_ = ps.getParameter<edm::InputTag>("metLabel");
  vertexLabel_ =  ps.getUntrackedParameter<edm::InputTag>("vertexLabel");
  min_ = ps.getUntrackedParameter<unsigned int>("min",1);
  ptcut_ = ps.getUntrackedParameter<double>("ptcut",30.0);
  absetacut_ = ps.getUntrackedParameter<double>("absetacut",2.5);
  pfJetIdParams_ = ps.getParameter<edm::ParameterSet> ("looseJetId");
  doJecFly_ = ps.getUntrackedParameter<bool>("doJecFly", true);
  doResJec_ = ps.getUntrackedParameter<bool>("doResJec", false);
  doJERUnc_ = ps.getUntrackedParameter<bool>("doJERUnc", false);
  resolutionFactor_ = ps.getUntrackedParameter<double>("resolutionFactor", 1.0);
  globalTag_ = ps.getUntrackedParameter<string>("globalTag","GR_R_42_V23");

  resJetCorrector_ = 0;
  jecUnc_ = 0;

  outputJetLabel_ = jetLabel_.label();
  outputMETLabel_ = metLabel_.label();

  produces<std::vector<pat::Jet> >(outputJetLabel_);
  produces<std::vector<pat::Jet> >(outputJetLabel_+"Up");
  produces<std::vector<pat::Jet> >(outputJetLabel_+"Dn");
  produces<std::vector<pat::MET> >(outputMETLabel_+"");
  produces<std::vector<pat::MET> >(outputMETLabel_+"Up");
  produces<std::vector<pat::MET> >(outputMETLabel_+"Dn");

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
  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  std::auto_ptr<std::vector<pat::Jet> > corrJets(new std::vector<pat::Jet>());
  std::auto_ptr<std::vector<pat::Jet> > corrJetsUp(new std::vector<pat::Jet>());
  std::auto_ptr<std::vector<pat::Jet> > corrJetsDn(new std::vector<pat::Jet>());
  std::auto_ptr<std::vector<pat::MET> > corrMETs(new std::vector<pat::MET>());
  std::auto_ptr<std::vector<pat::MET> > corrMETsUp(new std::vector<pat::MET>());
  std::auto_ptr<std::vector<pat::MET> > corrMETsDn(new std::vector<pat::MET>());

  edm::Handle<pat::JetCollection> Jets;
  iEvent.getByLabel(jetLabel_,Jets);

  edm::Handle<pat::METCollection> MET;
  iEvent.getByLabel(metLabel_,MET);
  pat::METCollection::const_iterator met = MET->begin();
  double met_x = met->px();
  double met_y = met->py();
  double metUp_x = met_x, metUp_y = met_y;
  double metDn_x = met_x, metDn_y = met_y;

  edm::Handle<double>  rho;
  iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

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

    // Do JEC uncertainty
    pat::Jet correctedJetUp = correctedJet;
    pat::Jet correctedJetDn = correctedJet;

    jecUnc_->setJetEta(correctedJetUp.eta());
    jecUnc_->setJetPt(correctedJetUp.pt());
    correctedJetUp.scaleEnergy(1+jecUnc_->getUncertainty(true));

    jecUnc_->setJetEta(correctedJetDn.eta());
    jecUnc_->setJetPt(correctedJetDn.pt());
    correctedJetDn.scaleEnergy(1-jecUnc_->getUncertainty(false));

    metUp_x += correctedJet.px() - correctedJetUp.px();
    metUp_y += correctedJet.py() - correctedJetUp.py();
    metDn_x += correctedJet.px() - correctedJetDn.px();
    metDn_y += correctedJet.py() - correctedJetDn.py();

    if(doJERUnc_){
      const double jetpx = correctedJet.px();
      const double jetpy = correctedJet.py();
      const double jetpxUp = correctedJetUp.px();
      const double jetpyUp = correctedJetUp.py();
      const double jetpxDn = correctedJetDn.px();
      const double jetpyDn = correctedJetDn.py();
      correctedJet.scaleEnergy( resolutionFactor(correctedJet)  );
      correctedJetUp.scaleEnergy( resolutionFactor(correctedJetUp) );
      correctedJetDn.scaleEnergy( resolutionFactor(correctedJetDn) );
      met_x -= correctedJet.px() - jetpx;
      met_y -= correctedJet.py() - jetpy;
      metUp_x  -= correctedJet.px() - jetpxUp;
      metUp_y  -= correctedJet.py() - jetpyUp;
      metDn_x  -= correctedJet.px() - jetpxDn;
      metDn_y  -= correctedJet.py() - jetpyDn;
    }

    //debug
    //cout << "corrected= " << correctedJet.pt() << " default= " << it->pt() << endl;

    if ( correctedJet.pt() > ptcut_ ) corrJets->push_back(correctedJet);
    if ( correctedJetUp.pt() > ptcut_ ) corrJetsUp->push_back(correctedJetUp);
    if ( correctedJetDn.pt() > ptcut_ ) corrJetsDn->push_back(correctedJetDn);
  }

  if( corrJets->size() >= min_ ) accepted = true;

  pat::MET corrMET(reco::MET ( sqrt(met_x*met_x + met_y*met_y)   , reco::MET::LorentzVector(met_x,met_y,0,sqrt(met_x*met_x + met_y*met_y))  , reco::MET::Point(0,0,0)));

  corrMETs->push_back(corrMET);

  // Jets passing identification criteria are sorted by decreasing pT
  std::sort(corrJets->begin(), corrJets->end(), GreaterByPt<pat::Jet>());
  std::sort(corrJetsUp->begin(), corrJetsUp->end(), GreaterByPt<pat::Jet>());
  std::sort(corrJetsDn->begin(), corrJetsDn->end(), GreaterByPt<pat::Jet>());

  iEvent.put(corrJets, outputJetLabel_);
  iEvent.put(corrJetsUp, outputJetLabel_+"Up");
  iEvent.put(corrJetsDn, outputJetLabel_+"Dn");
  iEvent.put(corrMETs, outputMETLabel_);
  iEvent.put(corrMETsUp, outputMETLabel_+"Up");
  iEvent.put(corrMETsDn, outputMETLabel_+"Dn");

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



