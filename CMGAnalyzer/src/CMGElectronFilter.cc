// -*- C++ -*-
//
// Package:    CMGElectronFilter
// Class:      CMGElectronFilter
//
/**\class CMGElectronFilter CMGElectronFilter.cc UserCode/CMGElectronFilter/src/CMGElectronFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: CMGElectronFilter.cc,v 1.4 2012/11/03 00:28:12 tjkim Exp $
//
//

// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/CompositePtrCandidate.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "CommonTools/Utils/interface/PtComparator.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

class CMGElectronFilter : public edm::EDFilter {
   public:
      explicit CMGElectronFilter(const edm::ParameterSet&);
      ~CMGElectronFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------

      bool applyFilter_;
      edm::InputTag electronLabel_;
      double ptcut_;
      double etacut_;
      double mvacut_;
      double relIso_;
      unsigned int numberOfHits_;

      bool isRealData_;
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
CMGElectronFilter::CMGElectronFilter(const edm::ParameterSet& cfg)
{
   //now do what ever initialization is needed
  applyFilter_=cfg.getUntrackedParameter<bool>("applyFilter",false);
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  ptcut_ = cfg.getUntrackedParameter<double>("ptcut",20);
  etacut_ = cfg.getUntrackedParameter<double>("etacut",2.5);
  mvacut_ = cfg.getUntrackedParameter<double>("mvacut",0.0);
  relIso_ = cfg.getUntrackedParameter<double>("relIso",9999);
  numberOfHits_ = cfg.getUntrackedParameter<unsigned int>("numberOfHits",0);

  produces<std::vector<cmg::Electron> >("");

}


CMGElectronFilter::~CMGElectronFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CMGElectronFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  isRealData_ = iEvent.isRealData();

  bool accepted = false;

  edm::Handle<vector<cmg::Electron> > electrons_;
  iEvent.getByLabel(electronLabel_, electrons_);

  std::auto_ptr<std::vector<cmg::Electron> > pos(new std::vector<cmg::Electron>());

  for (unsigned int i=0; i < electrons_->size();++i){
    cmg::Electron electron = electrons_->at(i);

    bool passPre = electron.sourcePtr()->get()->ecalDrivenMomentum().pt() > ptcut_ && fabs(electron.sourcePtr()->get()->ecalDrivenMomentum().eta()) < etacut_ ;
    bool passdxy = fabs(electron.sourcePtr()->get()->gsfTrack()->dxy()) < 0.04;
    bool passTrig = electron.getSelection("cuts_premvaTrig"); 
    bool passConversionVeto = electron.sourcePtr()->get()->passConversionVeto();
    bool passNhits = electron.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() <= (int) numberOfHits_;
    bool passPF = electron.sourcePtr()->get()->isPF();
    double mva = electron.mvaTrigV0();
    bool passId = mva > mvacut_;

    reco::isodeposit::Direction Dir = Direction(electron.sourcePtr()->get()->superCluster()->eta(),electron.phi());

    reco::isodeposit::AbsVetos vetos_ch;
    reco::isodeposit::AbsVetos vetos_nh;
    reco::isodeposit::AbsVetos vetos_ph;

    if( abs( electron.sourcePtr()->get()->superCluster()->eta() ) > 1.479 ){
      vetos_ch.push_back(new ConeVeto( Dir, 0.015 ));
      vetos_ph.push_back(new ConeVeto( Dir, 0.08 ));
    }

    double chIso03 = electron.sourcePtr()->get()->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    double puChIso03 = electron.sourcePtr()->get()->isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    double nhIso03 = electron.sourcePtr()->get()->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
    double phIso03 = electron.sourcePtr()->get()->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
    double relIso03 = (chIso03+nhIso03+phIso03-0.5*puChIso03)/electron.pt();

    bool passIso =  relIso03 < relIso_;

    bool passed = passPre && passPF && passConversionVeto && passNhits && passIso && passId;

    if ( passed ) pos->push_back((*electrons_)[i]);

  }

  iEvent.put(pos);

  if( applyFilter_ ) return accepted;
  else return true;

}

// ------------ method called once each job just before starting event loop  ------------
void
CMGElectronFilter::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void
CMGElectronFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CMGElectronFilter);



