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
// $Id: ZFilter.h,v 1.2 2012/06/07 15:10:16 tjkim Exp $
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

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

template<typename T1, typename T2>
class ZFilter : public edm::EDFilter {
 public:
  explicit ZFilter(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    applyFilter_ = iConfig.getUntrackedParameter<bool>("applyFilter",true);
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");
    min_ = iConfig.getParameter<double>("min");  
    max_ = iConfig.getParameter<double>("max");  
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");

    produces<std::vector<Ko::ZCandidate> >("DiLepton");
    produces<std::vector<T1> >("Lepton1");
    produces<std::vector<T2> >("Lepton2");

  }

  // ------------ method called once each job just after ending the event loop  ------------
  void
  endJob() {
  }


  ~ZFilter(){}

 private:
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    bool accept = false;

    std::auto_ptr<std::vector<Ko::ZCandidate> > dilp(new std::vector<Ko::ZCandidate>());
    std::auto_ptr<std::vector<Ko::ZCandidate> > seldilp(new std::vector<Ko::ZCandidate>());
    std::auto_ptr<std::vector<T1> > lep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > lep2(new std::vector<T2>());
    std::auto_ptr<std::vector<T1> > sellep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > sellep2(new std::vector<T2>());

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

        Ko::Lepton lepton1(it1.p4(), (int) it1.charge());
        Ko::Lepton lepton2(it2.p4(), (int) it2.charge());

        reco::isodeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
        reco::isodeposit::Direction Dir2 = Direction(it2.eta(),it2.phi());
        reco::isodeposit::AbsVetos vetos_ch;
        reco::isodeposit::AbsVetos vetos_nh;
        vetos_nh.push_back(new ThresholdVeto( 0.5 ));
        reco::isodeposit::AbsVetos vetos_ph1;
        vetos_ph1.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph1.push_back(new RectangularEtaPhiVeto( Dir1, -0.1, 0.1, -0.2, 0.2));
        reco::isodeposit::AbsVetos vetos_ph2;
        vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph2.push_back(new RectangularEtaPhiVeto( Dir2, -0.1, 0.1, -0.2, 0.2));

        //pf isolation setup
        lepton1.setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton1.setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton1.setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph1 );

        lepton2.setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton2.setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton2.setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph2 );

        //detector based isolation
        double trackIso1 = it1.trackIso();
        double ecalIso1 = it1.ecalIso();
        double hcalIso1 = it1.hcalIso();

        double trackIso2 = it2.trackIso();
        double ecalIso2 = it2.ecalIso();
        double hcalIso2 = it2.hcalIso();

        lepton1.setIsoDeposit( trackIso1, ecalIso1, hcalIso1);
        lepton2.setIsoDeposit( trackIso2, ecalIso2, hcalIso2);
   
        bool iso = lepton1.relpfIso03() < relIso1_ && lepton2.relpfIso03() < relIso2_;
        bool opp = it1.charge() * it2.charge() < 0;

        Ko::ZCandidate dimuon(lepton1, lepton2);


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

};

