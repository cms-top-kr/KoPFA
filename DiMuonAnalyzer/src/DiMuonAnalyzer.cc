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
// $Id: DiMuonAnalyzer.cc,v 1.13 2010/09/08 00:49:09 tjkim Exp $
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
      bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,const reco::Candidate::LorentzVector& proObj, bool exact );
      typedef pat::MuonCollection::const_iterator MI;
      typedef pat::JetCollection::const_iterator JI;

      edm::InputTag muonLabel1_;
      edm::InputTag muonLabel2_;
      edm::InputTag metLabel_;
      edm::InputTag jetLabel_;
      std::vector<std::string> filters_;
      bool useEventCounter_;
      /// loose jet ID. 
      PatJetIdSelector looseJetIdSelector_;
 
      TTree* tree;

      TH1F * tmp;
      TH1F * h_lep1pt;
      TH1F * h_lep2pt;
      TH1F * h_mass;
      TH1F * h_MET;
      TH1F * h_jet_multi;
      TH1F * h_jetpt30_multi;
      TH1F * h_chIso03lep1;
      TH1F * h_phIso03lep1;
      TH1F * h_nhIso03lep1;
      TH1F * h_chIso03lep2;
      TH1F * h_phIso03lep2;
      TH1F * h_nhIso03lep2;

      TH1F * h_chIso04lep1;
      TH1F * h_phIso04lep1;
      TH1F * h_nhIso04lep1;
      TH1F * h_chIso04lep2;
      TH1F * h_phIso04lep2;
      TH1F * h_nhIso04lep2;

      TH1F * h_chIso05lep1;
      TH1F * h_phIso05lep1;
      TH1F * h_nhIso05lep1;
      TH1F * h_chIso05lep2;
      TH1F * h_phIso05lep2;
      TH1F * h_nhIso05lep2;

      TH1F * h_trackIso1;
      TH1F * h_ecalIso1;
      TH1F * h_hcalIso1;
      TH1F * h_trackIso2;
      TH1F * h_ecalIso2;
      TH1F * h_hcalIso2;

      
      std::vector<Ko::ZCandidate>* Z;
      std::vector<math::XYZTLorentzVector>* jets;
      std::vector<math::XYZTLorentzVector>* jetspt30;

      std::vector<double>* chIso1;
      std::vector<double>* phIso1;
      std::vector<double>* nhIso1;
      std::vector<double>* chIso2;
      std::vector<double>* phIso2;
      std::vector<double>* nhIso2;

      std::vector<double>* chIso03lep1;
      std::vector<double>* phIso03lep1;
      std::vector<double>* nhIso03lep1;
      std::vector<double>* chIso03lep2;
      std::vector<double>* phIso03lep2;
      std::vector<double>* nhIso03lep2;

      std::vector<double>* chIso04lep1;
      std::vector<double>* phIso04lep1;
      std::vector<double>* nhIso04lep1;
      std::vector<double>* chIso04lep2;
      std::vector<double>* phIso04lep2;
      std::vector<double>* nhIso04lep2;

      std::vector<double>* chIso05lep1;
      std::vector<double>* phIso05lep1;
      std::vector<double>* nhIso05lep1;
      std::vector<double>* chIso05lep2;
      std::vector<double>* phIso05lep2;
      std::vector<double>* nhIso05lep2;
  
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
  muonLabel1_ =  iConfig.getParameter<edm::InputTag>("muonLabel1");
  muonLabel2_ =  iConfig.getParameter<edm::InputTag>("muonLabel2");
  metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
  jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
  useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
  filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
  looseJetIdSelector_.initialize( iConfig.getParameter<edm::ParameterSet> ("looseJetId") );

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Top quark study");
  tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

  h_lep1pt   = fs->make<TH1F>( "h_lep1pt"  , "p_{t}", 50,  0., 100. );
  h_lep2pt    = fs->make<TH1F>( "h_lep2pt"  , "p_{t}", 50,  0., 100. );
  h_mass      = fs->make<TH1F>( "h_mass", "Mass", 100, 0., 200. );   
  h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
  h_jet_multi = fs->make<TH1F>( "h_jet_multi", "jet_multi", 10, 0, 10);
  h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);

  h_chIso03lep1 = fs->make<TH1F>("h_chIso03lep1","chIso03lep1", 50, 0, 0.5);
  h_nhIso03lep1 = fs->make<TH1F>("h_nhIso03lep1","nhIso03lep1", 50, 0, 0.5);
  h_phIso03lep1 = fs->make<TH1F>("h_phIso03lep1","phIso03lep1", 50, 0, 0.5);
  h_chIso03lep2 = fs->make<TH1F>("h_chIso03lep2","chIso03lep2", 50, 0, 0.5);
  h_nhIso03lep2 = fs->make<TH1F>("h_nhIso03lep2","nhIso03lep2", 50, 0, 0.5);
  h_phIso03lep2 = fs->make<TH1F>("h_phIso03lep2","phIso03lep2", 50, 0, 0.5);

  h_chIso04lep1 = fs->make<TH1F>("h_chIso04lep1","chIso04lep1", 50, 0, 0.5);
  h_nhIso04lep1 = fs->make<TH1F>("h_nhIso04lep1","nhIso04lep1", 50, 0, 0.5);
  h_phIso04lep1 = fs->make<TH1F>("h_phIso04lep1","phIso04lep1", 50, 0, 0.5);
  h_chIso04lep2 = fs->make<TH1F>("h_chIso04lep2","chIso04lep2", 50, 0, 0.5);
  h_nhIso04lep2 = fs->make<TH1F>("h_nhIso04lep2","nhIso04lep2", 50, 0, 0.5);
  h_phIso04lep2 = fs->make<TH1F>("h_phIso04lep2","phIso04lep2", 50, 0, 0.5);
 
  h_chIso05lep1 = fs->make<TH1F>("h_chIso05lep1","chIso05lep1", 50, 0, 0.5);
  h_nhIso05lep1 = fs->make<TH1F>("h_nhIso05lep1","nhIso05lep1", 50, 0, 0.5);
  h_phIso05lep1 = fs->make<TH1F>("h_phIso05lep1","phIso05lep1", 50, 0, 0.5);
  h_chIso05lep2 = fs->make<TH1F>("h_chIso05lep2","chIso05lep2", 50, 0, 0.5);
  h_nhIso05lep2 = fs->make<TH1F>("h_nhIso05lep2","nhIso05lep2", 50, 0, 0.5);
  h_phIso05lep2 = fs->make<TH1F>("h_phIso05lep2","phIso05lep2", 50, 0, 0.5);

  h_trackIso1 = fs->make<TH1F>("h_trackIso1","trackIso1", 50, 0, 0.5);
  h_ecalIso1 = fs->make<TH1F>("h_ecalIso1","ecalIso1", 50, 0, 0.5);
  h_hcalIso1 = fs->make<TH1F>("h_hcalIso1","hcalIso1", 50, 0, 0.5);
  h_trackIso2 = fs->make<TH1F>("h_trackIso2","trackIso2", 50, 0, 0.5);
  h_ecalIso2 = fs->make<TH1F>("h_ecalIso2","ecalIso2", 50, 0, 0.5);
  h_hcalIso2 = fs->make<TH1F>("h_hcalIso2","hcalIso2", 50, 0, 0.5);

  Z = new std::vector<Ko::ZCandidate>();
  jets = new std::vector<math::XYZTLorentzVector>();
  jetspt30 = new std::vector<math::XYZTLorentzVector>();

  chIso1 = new std::vector<double>;
  phIso1 = new std::vector<double>;
  nhIso1 = new std::vector<double>;
  chIso2 = new std::vector<double>;
  phIso2 = new std::vector<double>;
  nhIso2 = new std::vector<double>;

  chIso03lep1 = new std::vector<double>;
  phIso03lep1 = new std::vector<double>;
  nhIso03lep1 = new std::vector<double>;
  chIso03lep2 = new std::vector<double>;
  phIso03lep2 = new std::vector<double>;
  nhIso03lep2 = new std::vector<double>;

  chIso04lep1 = new std::vector<double>;
  phIso04lep1 = new std::vector<double>;
  nhIso04lep1 = new std::vector<double>;
  chIso04lep2 = new std::vector<double>;
  phIso04lep2 = new std::vector<double>;
  nhIso04lep2 = new std::vector<double>;

  chIso05lep1 = new std::vector<double>;
  phIso05lep1 = new std::vector<double>;
  nhIso05lep1 = new std::vector<double>;
  chIso05lep2 = new std::vector<double>;
  phIso05lep2 = new std::vector<double>;
  nhIso05lep2 = new std::vector<double>;

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
  jets->clear();
  jetspt30->clear();

  chIso1->clear();
  phIso1->clear();
  nhIso1->clear();
  chIso2->clear();
  phIso2->clear();
  nhIso2->clear();

  chIso03lep1->clear();
  phIso03lep1->clear();
  nhIso03lep1->clear();
  chIso03lep2->clear();
  phIso03lep2->clear();
  nhIso03lep2->clear();

  chIso04lep1->clear();
  phIso04lep1->clear();
  nhIso04lep1->clear();
  chIso04lep2->clear();
  phIso04lep2->clear();
  nhIso04lep2->clear();

  chIso05lep1->clear();
  phIso05lep1->clear();
  nhIso05lep1->clear();
  chIso05lep2->clear();
  phIso05lep2->clear();
  nhIso05lep2->clear();

  trackIso1->clear();
  ecalIso1->clear();
  hcalIso1->clear();
  trackIso2->clear();
  ecalIso2->clear();
  hcalIso2->clear();


  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  edm::Handle<pat::MuonCollection> muons1_;
  edm::Handle<pat::MuonCollection> muons2_;
  edm::Handle<pat::METCollection> MET_;
  iEvent.getByLabel(muonLabel1_,muons1_);
  iEvent.getByLabel(muonLabel2_,muons2_);
  iEvent.getByLabel(metLabel_,MET_);

  pat::METCollection::const_iterator mi = MET_->begin();
  MET = mi->pt(); 
  h_MET->Fill(MET);

  edm::Handle<pat::JetCollection> Jets;
  iEvent.getByLabel(jetLabel_, Jets);

  for (JI it = Jets->begin(); it != Jets->end(); ++it) {

    if(abs(it->eta()) >= 2.5) continue; 

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

  for(MI mi = muons1_->begin() ; mi != muons1_->end(); mi++){
    for(MI mj = muons2_->begin(); mj != muons2_->end(); mj++){
 
      const bool match = MatchObjects( mi->p4(), mj->p4(), true);
      if(match) continue;

      int sign = mi->charge() * mj->charge();
      Ko::ZCandidate dimuon(mi->p4(), mj->p4(), sign);

      Z->push_back(dimuon);

      h_lep1pt->Fill(mi->pt());
      h_lep2pt->Fill(mj->pt());
      h_mass->Fill(dimuon.mass());

      chIso1->push_back(mi->chargedHadronIso());
      phIso1->push_back(mi->photonIso());
      nhIso1->push_back(mi->neutralHadronIso());

      chIso2->push_back(mj->chargedHadronIso());
      phIso2->push_back(mj->photonIso());
      nhIso2->push_back(mj->neutralHadronIso());

      //reco::IsoDeposit::Direction Dir1 = Direction(mi->eta(),mi->phi());
      //reco::IsoDeposit::Direction Dir2 = Direction(mj->eta(),mj->phi());

      IsoDeposit::AbsVetos vetos_ch;
      IsoDeposit::AbsVetos vetos_nh;
      vetos_nh.push_back(new ThresholdVeto( 0.5 ));
      IsoDeposit::AbsVetos vetos_ph1;
      vetos_ph1.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph1.push_back(new RectangularEtaPhiVeto( Dir1, -0.1, 0.1, -0.2, 0.2)); // useful to compare with Random Cone technic
      IsoDeposit::AbsVetos vetos_ph2;
      vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph2.push_back(new RectangularEtaPhiVeto( Dir2, -0.1, 0.1, -0.2, 0.2)); // useful to compare with Random Cone technic

      chIso03lep1->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first);
      nhIso03lep1->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first);
      phIso03lep1->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph1).first);
      chIso03lep2->push_back(mj->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first);
      nhIso03lep2->push_back(mj->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first);
      phIso03lep2->push_back(mj->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph2).first);

      chIso04lep1->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIso04lep1->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first);
      phIso04lep1->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph1).first);
      chIso04lep2->push_back(mj->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIso04lep2->push_back(mj->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first);
      phIso04lep2->push_back(mj->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph2).first);

      chIso05lep1->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.5, vetos_ch).first);
      nhIso05lep1->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.5, vetos_nh).first);
      phIso05lep1->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.5, vetos_ph1).first);
      chIso05lep2->push_back(mj->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.5, vetos_ch).first);
      nhIso05lep2->push_back(mj->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.5, vetos_nh).first);
      phIso05lep2->push_back(mj->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.5, vetos_ph2).first);

      trackIso1->push_back(mi->trackIso());
      ecalIso1->push_back(mi->ecalIso());
      hcalIso1->push_back(mi->hcalIso());

      trackIso2->push_back(mj->trackIso());
      ecalIso2->push_back(mj->ecalIso());
      hcalIso2->push_back(mj->hcalIso());

      h_chIso03lep1->Fill(chIso03lep1->back());
      h_nhIso03lep1->Fill(nhIso03lep1->back());
      h_phIso03lep1->Fill(phIso03lep1->back());
      h_chIso03lep2->Fill(chIso03lep2->back());
      h_nhIso03lep2->Fill(nhIso03lep2->back());
      h_phIso03lep2->Fill(phIso03lep2->back());
   
      h_chIso04lep1->Fill(chIso04lep1->back());
      h_nhIso04lep1->Fill(nhIso04lep1->back());
      h_phIso04lep1->Fill(phIso04lep1->back());
      h_chIso04lep2->Fill(chIso04lep2->back());
      h_nhIso04lep2->Fill(nhIso04lep2->back());
      h_phIso04lep2->Fill(phIso04lep2->back());

      h_chIso05lep1->Fill(chIso05lep1->back());
      h_nhIso05lep1->Fill(nhIso05lep1->back());
      h_phIso05lep1->Fill(phIso05lep1->back());
      h_chIso05lep2->Fill(chIso05lep2->back());
      h_nhIso05lep2->Fill(nhIso05lep2->back());
      h_phIso05lep2->Fill(phIso05lep2->back());

      h_trackIso1->Fill(trackIso1->back());
      h_ecalIso1->Fill(ecalIso1->back());
      h_hcalIso1->Fill(hcalIso1->back());
      h_trackIso2->Fill(trackIso2->back());
      h_ecalIso2->Fill(ecalIso2->back());
      h_hcalIso2->Fill(hcalIso2->back());


      break;
    }
    break;
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

  tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
  tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);

  tree->Branch("chIso1","std::vector<double>", &chIso1);
  tree->Branch("phIso1","std::vector<double>", &phIso1);
  tree->Branch("nhIso1","std::vector<double>", &nhIso1);
  tree->Branch("chIso2","std::vector<double>", &chIso2);
  tree->Branch("phIso2","std::vector<double>", &phIso2);
  tree->Branch("nhIso2","std::vector<double>", &nhIso2);

  tree->Branch("chIso03lep1","std::vector<double>", &chIso03lep1);
  tree->Branch("phIso03lep1","std::vector<double>", &phIso03lep1);
  tree->Branch("nhIso03lep1","std::vector<double>", &nhIso03lep1);
  tree->Branch("chIso03lep2","std::vector<double>", &chIso03lep2);
  tree->Branch("phIso03lep2","std::vector<double>", &phIso03lep2);
  tree->Branch("nhIso03lep2","std::vector<double>", &nhIso03lep2);

  tree->Branch("chIso04lep1","std::vector<double>", &chIso04lep1);
  tree->Branch("phIso04lep1","std::vector<double>", &phIso04lep1);
  tree->Branch("nhIso04lep1","std::vector<double>", &nhIso04lep1);
  tree->Branch("chIso04lep2","std::vector<double>", &chIso04lep2);
  tree->Branch("phIso04lep2","std::vector<double>", &phIso04lep2);
  tree->Branch("nhIso04lep2","std::vector<double>", &nhIso04lep2);

  tree->Branch("chIso05lep1","std::vector<double>", &chIso05lep1);
  tree->Branch("phIso05lep1","std::vector<double>", &phIso05lep1);
  tree->Branch("nhIso05lep1","std::vector<double>", &nhIso05lep1);
  tree->Branch("chIso05lep2","std::vector<double>", &chIso05lep2);
  tree->Branch("phIso05lep2","std::vector<double>", &phIso05lep2);
  tree->Branch("nhIso05lep2","std::vector<double>", &nhIso05lep2);

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

bool DiMuonAnalyzer::MatchObjects( const reco::Candidate::LorentzVector& pasObj, const reco::Candidate::LorentzVector& proObj, bool exact ) {
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

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonAnalyzer);
