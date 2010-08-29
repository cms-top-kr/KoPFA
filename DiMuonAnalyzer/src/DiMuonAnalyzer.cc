// -*- C++ -*-
//
// Package:    DiMuonAnalyzer
// Class:      DiMuonAnalyzer
// 
/**\class DiMuonAnalyzer DiMuonAnalyzer.cc UserCode/DiMuonAnalyzer/src/DiMuonAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: DiMuonAnalyzer.cc,v 1.9 2010/07/28 00:19:42 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "PFAnalyses/CommonTools/interface/CandidateSelector.h"
#include "PFAnalyses/CommonTools/interface/PatJetIdSelector.h"

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

//
// class declaration
//

class DiMuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DiMuonAnalyzer(const edm::ParameterSet&);
      ~DiMuonAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      bool checkOverlap(const double &, const double &, edm::Handle<pat::MuonCollection>& );

      typedef pat::MuonCollection::const_iterator MI;
      typedef pat::JetCollection::const_iterator JI;

      edm::InputTag muonLabel_;
      edm::InputTag metLabel_;
      edm::InputTag jetLabel_;
      std::vector<std::string> filters_;
      bool useEventCounter_;
      /// loose jet ID. 
      PatJetIdSelector looseJetIdSelector_;
 
      TTree* tree;

      TH1F * tmp;
      TH1F * h_leadingpt;
      TH1F * h_secondpt;
      TH1F * h_mass;
      TH1F * h_MET;
      TH1F * h_jet_multi;
      TH1F * h_jetpt30_multi;

      std::vector<Ko::ZCandidate>* Z;
      std::vector<math::XYZTLorentzVector>* muon1;
      std::vector<math::XYZTLorentzVector>* muon2;
      std::vector<math::XYZTLorentzVector>* jets;
      std::vector<math::XYZTLorentzVector>* jetspt30;
      std::vector<math::XYZTLorentzVector>* muons;

      std::vector<double>* chIso;
      std::vector<double>* phIso;
      std::vector<double>* nhIso;
      std::vector<double>* chIsoOpt;
      std::vector<double>* phIsoOpt;
      std::vector<double>* nhIsoOpt;

      std::vector<double>* trackIso;
      std::vector<double>* ecalIso;
      std::vector<double>* hcalIso;
 
      std::vector<double>* chIso1;
      std::vector<double>* phIso1;
      std::vector<double>* nhIso1;
      std::vector<double>* chIso2;
      std::vector<double>* phIso2;
      std::vector<double>* nhIso2;

      std::vector<double>* chIsoOpt1;
      std::vector<double>* phIsoOpt1;
      std::vector<double>* nhIsoOpt1;
      std::vector<double>* chIsoOpt2;
      std::vector<double>* phIsoOpt2;
      std::vector<double>* nhIsoOpt2;

      std::vector<double>* trackIso1;
      std::vector<double>* ecalIso1;
      std::vector<double>* hcalIso1;
      std::vector<double>* trackIso2;
      std::vector<double>* ecalIso2;
      std::vector<double>* hcalIso2;
    
      double MET;
      // ----------member data ---------------------------

      //add run event data
      unsigned int EVENT;
      unsigned int RUN;
      unsigned int LUMI;
  
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
DiMuonAnalyzer::DiMuonAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  muonLabel_ =  iConfig.getParameter<edm::InputTag>("muonLabel");
  metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
  jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
  useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
  filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
  looseJetIdSelector_.initialize( iConfig.getParameter<edm::ParameterSet> ("looseJetId") );

  

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Top quark study");
  tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

  h_leadingpt   = fs->make<TH1F>( "h_leadingpt"  , "p_{t}", 50,  0., 100. );
  h_secondpt    = fs->make<TH1F>( "h_secondpt"  , "p_{t}", 50,  0., 100. );
  h_mass      = fs->make<TH1F>( "h_mass", "Mass", 100, 0., 200. );   
  h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
  h_jet_multi = fs->make<TH1F>( "h_jet_multi", "jet_multi", 10, 0, 10);
  h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);

  Z = new std::vector<Ko::ZCandidate>();
  muon1 = new std::vector<math::XYZTLorentzVector>();
  muon2 = new std::vector<math::XYZTLorentzVector>();
  jets = new std::vector<math::XYZTLorentzVector>();
  jetspt30 = new std::vector<math::XYZTLorentzVector>();
  muons = new std::vector<math::XYZTLorentzVector>();

  chIso = new std::vector<double>;
  phIso = new std::vector<double>;
  nhIso = new std::vector<double>;
  chIsoOpt = new std::vector<double>;
  phIsoOpt = new std::vector<double>;
  nhIsoOpt = new std::vector<double>;

  trackIso = new std::vector<double>;
  ecalIso = new std::vector<double>;
  hcalIso = new std::vector<double>;
  
  chIso1 = new std::vector<double>;
  phIso1 = new std::vector<double>;
  nhIso1 = new std::vector<double>;
  chIso2 = new std::vector<double>;
  phIso2 = new std::vector<double>;
  nhIso2 = new std::vector<double>;

  chIsoOpt1 = new std::vector<double>;
  phIsoOpt1 = new std::vector<double>;
  nhIsoOpt1 = new std::vector<double>;
  chIsoOpt2 = new std::vector<double>;
  phIsoOpt2 = new std::vector<double>;
  nhIsoOpt2 = new std::vector<double>;

  trackIso1 = new std::vector<double>;
  ecalIso1 = new std::vector<double>;
  hcalIso1 = new std::vector<double>;
  trackIso2 = new std::vector<double>;
  ecalIso2 = new std::vector<double>;
  hcalIso2 = new std::vector<double>;

}


DiMuonAnalyzer::~DiMuonAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DiMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace isodeposit;

  Z->clear();
  muon1->clear();
  muon2->clear();
  jets->clear();
  jetspt30->clear();
  muons->clear();

  chIso->clear();
  phIso->clear();
  nhIso->clear();
  chIsoOpt->clear();
  phIsoOpt->clear();
  nhIsoOpt->clear();

  trackIso->clear();
  ecalIso->clear();
  hcalIso->clear();

  chIso1->clear();
  phIso1->clear();
  nhIso1->clear();
  chIso2->clear();
  phIso2->clear();
  nhIso2->clear();

  chIsoOpt1->clear();
  phIsoOpt1->clear();
  nhIsoOpt1->clear();
  chIsoOpt2->clear();
  phIsoOpt2->clear();
  nhIsoOpt2->clear();

  trackIso1->clear();
  ecalIso1->clear();
  hcalIso1->clear();
  trackIso2->clear();
  ecalIso2->clear();
  hcalIso2->clear();


  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  edm::Handle<pat::MuonCollection> muons_;
  edm::Handle<pat::METCollection> MET_;
  iEvent.getByLabel(muonLabel_,muons_);
  iEvent.getByLabel(metLabel_,MET_);

  pat::METCollection::const_iterator mi = MET_->begin();
  MET = mi->pt(); 
  h_MET->Fill(MET);

  edm::Handle<pat::JetCollection> Jets;
  iEvent.getByLabel(jetLabel_, Jets);

  for (JI it = Jets->begin(); it != Jets->end(); ++it) {

    if(abs(it->eta()) >= 2.5) continue; 
    bool overlap = checkOverlap(it->eta(), it->phi(), muons_);
    if(overlap) continue;

    pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    bool passId = looseJetIdSelector_( *it, looseJetIdSel);

    if(passId){
      jets->push_back(it->p4());
      if( it->pt() > 30)
        jetspt30->push_back(it->p4());
    }
  }

  h_jet_multi->Fill(jets->size());
  h_jetpt30_multi->Fill(jetspt30->size());


  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;

  for(MI mi = muons_->begin(); mi != muons_->end(); mi++){
    muons->push_back(mi->p4());

    chIso->push_back(mi->chargedHadronIso());
    phIso->push_back(mi->photonIso());
    nhIso->push_back(mi->neutralHadronIso());

    chIsoOpt->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
    nhIsoOpt->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
    phIsoOpt->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

    trackIso->push_back(mi->trackIso());
    ecalIso->push_back(mi->ecalIso());
    hcalIso->push_back(mi->hcalIso());


  }

  for(MI mi = muons_->begin(); mi != muons_->end()-1; mi++){
   
    for(MI mj = mi + 1 ; mj != muons_->end(); mj++){

      int sign = mi->charge() * mj->charge();
      Ko::ZCandidate dimuon(mi->p4(), mj->p4(), sign);

      Z->push_back(dimuon);
      muon1->push_back(mi->p4());
      muon2->push_back(mj->p4());

      h_leadingpt->Fill(mi->pt());
      h_secondpt->Fill(mj->pt());
      h_mass->Fill(dimuon.mass());

      chIso1->push_back(mi->chargedHadronIso());
      phIso1->push_back(mi->photonIso());
      nhIso1->push_back(mi->neutralHadronIso());

      chIso2->push_back(mi->chargedHadronIso());
      phIso2->push_back(mi->photonIso());
      nhIso2->push_back(mi->neutralHadronIso());

      chIsoOpt1->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIsoOpt1->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      phIsoOpt1->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

      chIsoOpt2->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIsoOpt2->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      phIsoOpt2->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

      trackIso1->push_back(mi->trackIso());
      ecalIso1->push_back(mi->ecalIso());
      hcalIso1->push_back(mi->hcalIso());

      trackIso2->push_back(mi->trackIso());
      ecalIso2->push_back(mi->ecalIso());
      hcalIso2->push_back(mi->hcalIso());

      break;
    }
  }
   
  //ESHandle<SetupData> pSetup;
  //iSetup.get<SetupRecord>().get(pSetup);
  tree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonAnalyzer::beginJob()
{
  tree->Branch("EVENT",&EVENT,"EVENT/i");
  tree->Branch("RUN",&RUN,"RUN/i");
  tree->Branch("LUMI",&LUMI,"LUMI/i");

  tree->Branch("Z","std::vector<Ko::ZCandidate>", &Z);
  tree->Branch("muon1","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &muon1);
  tree->Branch("muon2","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &muon2);

  tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
  tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
  tree->Branch("muons","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &muons);

  tree->Branch("chIsoOpt","std::vector<double>", &chIsoOpt);
  tree->Branch("phIsoOpt","std::vector<double>", &phIsoOpt);
  tree->Branch("nhIsoOpt","std::vector<double>", &nhIsoOpt);

  tree->Branch("chIso","std::vector<double>", &chIso);
  tree->Branch("phIso","std::vector<double>", &phIso);
  tree->Branch("nhIso","std::vector<double>", &nhIso);

  tree->Branch("trackIso","std::vector<double>", &trackIso);
  tree->Branch("ecalIso","std::vector<double>", &ecalIso);
  tree->Branch("hcalIso","std::vector<double>", &hcalIso);

  tree->Branch("chIso1","std::vector<double>", &chIso1);
  tree->Branch("phIso1","std::vector<double>", &phIso1);
  tree->Branch("nhIso1","std::vector<double>", &nhIso1);
  tree->Branch("chIso2","std::vector<double>", &chIso2);
  tree->Branch("phIso2","std::vector<double>", &phIso2);
  tree->Branch("nhIso2","std::vector<double>", &nhIso2);

  tree->Branch("chIsoOpt1","std::vector<double>", &chIsoOpt1);
  tree->Branch("phIsoOpt1","std::vector<double>", &phIsoOpt1);
  tree->Branch("nhIsoOpt1","std::vector<double>", &nhIsoOpt1);
  tree->Branch("chIsoOpt2","std::vector<double>", &chIsoOpt2);
  tree->Branch("phIsoOpt2","std::vector<double>", &phIsoOpt2);
  tree->Branch("nhIsoOpt2","std::vector<double>", &nhIsoOpt2);

  tree->Branch("trackIso1","std::vector<double>", &trackIso1);
  tree->Branch("ecalIso1","std::vector<double>", &ecalIso1);
  tree->Branch("hcalIso1","std::vector<double>", &hcalIso1);
  tree->Branch("trackIso2","std::vector<double>", &trackIso2);
  tree->Branch("ecalIso2","std::vector<double>", &ecalIso2);
  tree->Branch("hcalIso2","std::vector<double>", &hcalIso2);

  tree->Branch("MET",&MET,"MET/d");
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonAnalyzer::endJob() {
           if(useEventCounter_){
             DQMStore* store = &*edm::Service<DQMStore>();
             if(filters_.size()>0) {
               for(unsigned int i=0;i<filters_.size();++i) {
                 MonitorElement *tmpM = store->get(filters_[i]);
                 tmp->SetBinContent(i+1,tmpM->getFloatValue());
                 tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
               }
             }
           }
}

bool DiMuonAnalyzer::checkOverlap( const double & eta, const double & phi, edm::Handle<pat::MuonCollection>& muons){ 

  bool overlap = false;
  for(MI mi = muons->begin(); mi != muons->end(); mi++){
    double dRval = deltaR(eta, phi, mi->eta(), mi->phi());
    overlap = dRval < 0.4;
  }

  return overlap;

}


//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonAnalyzer);
