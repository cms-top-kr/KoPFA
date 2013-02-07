// -*- C++ -*-
//
// Package:    TopDILAnalyzer
// Class:      TopDILAnalyzer
// 
/**\class TopDILAnalyzer TopDILAnalyzer.cc UserCode/TopDILAnalyzer/src/TopDILAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: CMGZFilter.h,v 1.5 2012/11/15 09:34:27 youngjo Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "KoPFA/DataFormats/interface/Maos.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"


//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

template<typename T1, typename T2>
class CMGZFilter : public edm::EDFilter {
 public:
  explicit CMGZFilter(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    applyFilter_ = iConfig.getUntrackedParameter<bool>("applyFilter",true);
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");
    min_ = iConfig.getParameter<double>("min");  
    max_ = iConfig.getParameter<double>("max");  
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    rhoIsoLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("rhoIsoLabel");

    produces<std::vector<vallot::ZCandidate> >("DiLepton");
    produces<std::vector<T1> >("Lepton1");
    produces<std::vector<T2> >("Lepton2");

  }

  // ------------ method called once each job just after ending the event loop  ------------
  void
  endJob() {
  }


  ~CMGZFilter(){}

 private:
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    bool accept = false;
    const bool isRealData = iEvent.isRealData();

    std::auto_ptr<std::vector<vallot::ZCandidate> > dilp(new std::vector<vallot::ZCandidate>());
    std::auto_ptr<std::vector<vallot::ZCandidate> > seldilp(new std::vector<vallot::ZCandidate>());
    std::auto_ptr<std::vector<T1> > lep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > lep2(new std::vector<T2>());
    std::auto_ptr<std::vector<T1> > sellep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > sellep2(new std::vector<T2>());

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);

    edm::Handle<double>  rho_;
    iEvent.getByLabel(rhoIsoLabel_, rho_);
    double rhoIso = *(rho_.product());

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

        vallot::Lepton lepton1(it1.p4(), (int) it1.charge());
        vallot::Lepton lepton2(it2.p4(), (int) it2.charge());

        //pf isolation setup
        lepton1.setPFIsoValues03( it1.chargedHadronIso(0.3), it1.puChargedHadronIso(0.3), it1.neutralHadronIso(0.3), it1.photonIso(0.3) );
        lepton2.setPFIsoValues03( it2.chargedHadronIso(0.3), it2.puChargedHadronIso(0.3), it2.neutralHadronIso(0.3), it2.photonIso(0.3) );
        lepton1.setPFIsoValues04( it1.chargedHadronIso(0.4), it1.puChargedHadronIso(0.4), it1.neutralHadronIso(0.4), it1.photonIso(0.4) );
        lepton2.setPFIsoValues04( it2.chargedHadronIso(0.4), it2.puChargedHadronIso(0.4), it2.neutralHadronIso(0.4), it2.photonIso(0.4) );

        double AEff03Lep1 = 0.00;
        double AEff04Lep1 = 0.00;

        double AEff03Lep2 = 0.00;
        double AEff04Lep2 = 0.00;

        if( !it1.isMuon() ){
          double sceta1 = it1.sourcePtr()->get()->superCluster()->eta(); 
          AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta1, ElectronEffectiveArea::kEleEAData2012);
          AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta1, ElectronEffectiveArea::kEleEAData2012);
        }

        if( !it2.isMuon() ){ 
          double sceta2 = it2.sourcePtr()->get()->superCluster()->eta(); 
          AEff03Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta2, ElectronEffectiveArea::kEleEAData2012);
          AEff04Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta2, ElectronEffectiveArea::kEleEAData2012);
        }
   
        lepton1.setRho( rhoIso );
        lepton2.setRho( rhoIso );
        lepton1.setAEff03( AEff03Lep1 );
        lepton2.setAEff03( AEff03Lep2 );
        lepton1.setAEff04( AEff04Lep1 );
        lepton2.setAEff04( AEff04Lep2 );

        //detector based isolation
        double trackIso1 = it1.sourcePtr()->get()->trackIso();
        double ecalIso1 = it1.sourcePtr()->get()->ecalIso();
        double hcalIso1 = it1.sourcePtr()->get()->hcalIso();

        double trackIso2 = it2.sourcePtr()->get()->trackIso();
        double ecalIso2 = it2.sourcePtr()->get()->ecalIso();
        double hcalIso2 = it2.sourcePtr()->get()->hcalIso();

        lepton1.setIsoDeposit( trackIso1, ecalIso1, hcalIso1);
        lepton2.setIsoDeposit( trackIso2, ecalIso2, hcalIso2);
  
        double lepton1_relIso03 = 999;
        double lepton2_relIso03 = 999;

        if( it1.isMuon() ) {
          lepton1.setType(1);
          lepton1_relIso03 = lepton1.relIso03(1);  
        }else{
          lepton1.setType(0);
          lepton1_relIso03 = lepton1.relIso03(2);
        }

        if( it2.isMuon() ) {
          lepton2.setType(1);
          lepton2_relIso03 = lepton1.relIso03(1);
        }else{
          lepton2.setType(0);
          lepton2_relIso03 = lepton1.relIso03(2);
        }

        bool iso = lepton1_relIso03 < relIso1_ && lepton2_relIso03 < relIso2_;
        bool opp = it1.sourcePtr()->get()->charge() * it2.sourcePtr()->get()->charge() < 0;

        vallot::ZCandidate dimuon(lepton1, lepton2);

        if( iso && opp){
          seldilp->push_back( dimuon );
          sellep1->push_back( (*muons1_)[i] );
          sellep2->push_back( (*muons2_)[j] );      
        }else{
          dilp->push_back( dimuon );
          lep1->push_back( (*muons1_)[i] );
          lep2->push_back( (*muons2_)[j] );
        }
        
      }
    }

    if( seldilp->size() > 0){
      dilp->insert( dilp->begin(), seldilp->begin(), seldilp->end());
      lep1->insert( lep1->begin(), sellep1->begin(), sellep1->end());
      lep2->insert( lep2->begin(), sellep2->begin(), sellep2->end());
    }
    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);

    if( dilp->size() > 0 && dilp->at(0).mass() >  min_ ) { 
      accept = true;
    }

    iEvent.put(dilp,"DiLepton");
    iEvent.put(lep1,"Lepton1");
    iEvent.put(lep2,"Lepton2");

    if(applyFilter_) return accept;
    else return true;

  }

  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact ) {
    double proEta = proObj.eta();
    double proPhi = proObj.phi();
    double proPt  = proObj.pt();
    double pasEta = pasObj.eta();
    double pasPhi = pasObj.phi();
    double pasPt  = pasObj.pt();

    double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);
    double dPtRel = 999.0;
    if( proPt > 0.0 ) dPtRel = fabs( pasPt - proPt )/proPt;
    // If we are comparing two objects for which the candidates should
    // be exactly the same, cut hard. Otherwise take cuts from user.
    if( exact ) return ( dRval < 1e-3 && dPtRel < 1e-3 );
    else        return ( dRval < 0.025 && dPtRel < 0.025 );
  }

  bool applyFilter_;
  edm::InputTag muonLabel1_;
  edm::InputTag muonLabel2_;
  double min_;
  double max_;
  double relIso1_;
  double relIso2_;
  edm::InputTag rhoIsoLabel_;

};

