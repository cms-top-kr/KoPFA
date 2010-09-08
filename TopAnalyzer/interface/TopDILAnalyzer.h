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
// $Id: TopDILAnalyzer.h,v 1.1 2010/09/08 00:26:44 tjkim Exp $
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

#include "DataFormats/Math/interface/deltaR.h"
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

template<typename T1, typename T2>
class TopDILAnalyzer : public edm::EDAnalyzer {
  public:
    explicit TopDILAnalyzer(const edm::ParameterSet& iConfig){
      //now do what ever initialization is needed
      muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");
      muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");
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
      jets = new std::vector<math::XYZTLorentzVector>();
      jetspt30 = new std::vector<math::XYZTLorentzVector>();

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


    ~TopDILAnalyzer(){}

   private:
      virtual void beginJob() 
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

      virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

          edm::Handle<std::vector<T1> > muons1_;
          edm::Handle<std::vector<T2> > muons2_;
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
	    bool overlap = checkOverlap(it->eta(), it->phi(), muons1_, muons2_);
	    if( overlap ) continue;

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

          for(unsigned i = 0; i != muons1_->size(); i++){
            for(unsigned j = 0; j != muons2_->size(); j++){
              T1 it1 = muons1_->at(i);
              T2 it2 = muons2_->at(j);
              const edm::Ptr<T1> Ptr1(muons1_,i); 
              const edm::Ptr<T2> Ptr2(muons2_,j); 
	      bool match = MatchObjects( Ptr1->p4(), Ptr2->p4(), true);
	      if(match) continue;

	      int sign = it1.charge() * it2.charge();
	      Ko::ZCandidate dimuon(Ptr1->p4(), Ptr2->p4(), sign);

	      Z->push_back(dimuon);

	      h_leadingpt->Fill(it1.pt());
	      h_secondpt->Fill(it2.pt());
	      h_mass->Fill(dimuon.mass());

	      chIso1->push_back(it1.chargedHadronIso());
	      phIso1->push_back(it1.photonIso());
	      nhIso1->push_back(it1.neutralHadronIso());

	      chIso2->push_back(it2.chargedHadronIso());
	      phIso2->push_back(it2.photonIso());
	      nhIso2->push_back(it2.neutralHadronIso());

	      chIsoOpt1->push_back(it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
	      nhIsoOpt1->push_back(it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
	      phIsoOpt1->push_back(it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

	      chIsoOpt2->push_back(it2.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
	      nhIsoOpt2->push_back(it2.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
	      phIsoOpt2->push_back(it2.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

	      trackIso1->push_back(it1.trackIso());
	      ecalIso1->push_back(it1.ecalIso());
	      hcalIso1->push_back(it1.hcalIso());

	      trackIso2->push_back(it2.trackIso());
	      ecalIso2->push_back(it2.ecalIso());
	      hcalIso2->push_back(it2.hcalIso());

	      break;
	    }
            break;
	  }
	  //ESHandle<SetupData> pSetup;
	  //iSetup.get<SetupRecord>().get(pSetup);
	  tree->Fill();

	}



      virtual void endJob() 
      {
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


      bool checkOverlap(const double & eta, const double & phi, edm::Handle<vector<T1> >& src1, edm::Handle<vector<T2> >& src2)
      {

        bool overlap = false;
        for(unsigned i = 0; i != src1->size(); i++){
          T1 it = src1->at(i);
          double dRval = deltaR(eta, phi, it.eta(), it.phi());
          overlap = dRval < 0.4 ;
          if(overlap) return overlap;
        }

        for(unsigned i = 0; i != src2->size(); i++){
          T2 it = src2->at(i);
          double dRval = deltaR(eta, phi, it.eta(), it.phi());
          overlap = dRval < 0.4 ;
          if(overlap) return overlap;
        }

        return overlap;

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
      TH1F * h_leadingpt;
      TH1F * h_secondpt;
      TH1F * h_mass;
      TH1F * h_MET;
      TH1F * h_jet_multi;
      TH1F * h_jetpt30_multi;

      std::vector<Ko::ZCandidate>* Z;
      std::vector<math::XYZTLorentzVector>* jets;
      std::vector<math::XYZTLorentzVector>* jetspt30;

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

