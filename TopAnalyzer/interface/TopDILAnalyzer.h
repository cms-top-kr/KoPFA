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
// $Id: TopDILAnalyzer.h,v 1.43 2011/05/22 21:32:44 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"

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
#include "PFAnalyses/CommonTools/interface/CandidateSelector.h"
#include "PFAnalyses/CommonTools/interface/PatJetIdSelector.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"

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
class TopDILAnalyzer : public edm::EDFilter {
 public:
  explicit TopDILAnalyzer(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    //looseJetIdSelector_.initialize( iConfig.getParameter<edm::ParameterSet> ("looseJetId") );
    pfJetIdParams_ = iConfig.getParameter<edm::ParameterSet> ("looseJetId");
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    bTagAlgo_ = iConfig.getUntrackedParameter<std::string>("bTagAlgo");
    minBTagValue_ = iConfig.getUntrackedParameter<double>("minBTagValue");

    // Residual Jet energy correction for 38X
    doResJec_ = iConfig.getUntrackedParameter<bool>("doResJec", false);
    doJecUnc_ = iConfig.getUntrackedParameter<bool>("doJecUnc", false);
    up_ = iConfig.getUntrackedParameter<bool>("up", true); // uncertainty up
    resJetCorrector_ = 0;
    jecUnc_ = 0;

    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for Top quark study");
    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    h_leadingpt   = fs->make<TH1F>( "h_leadingpt"  , "p_{t}", 50,  0., 100. );
    h_secondpt    = fs->make<TH1F>( "h_secondpt"  , "p_{t}", 50,  0., 100. );
    h_mass      = fs->make<TH1F>( "h_mass", "Mass", 100, 0., 200. );
    h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
    h_jet_multi = fs->make<TH1F>( "h_jet_multi", "jet_multi", 10, 0, 10);
    h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);
    h_bjet_multi = fs->make<TH1F>( "h_bjet_multi", "bjet_multi", 10, 0, 10);

    Z = new std::vector<Ko::ZCandidate>();
    lepton1 = new std::vector<Ko::Lepton>();
    lepton2 = new std::vector<Ko::Lepton>();
    pfMet = new std::vector<Ko::METCandidate>();
    ttbar = new std::vector<Ko::TTbarMass>();
    met = new std::vector<math::XYZTLorentzVector>();
    jets = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
    bjets = new std::vector<math::XYZTLorentzVector>();

  }


  ~TopDILAnalyzer()
  {
    if ( resJetCorrector_ ) delete resJetCorrector_;
    if ( jecUnc_ ) delete jecUnc_;
  }

 private:
  virtual void beginJob() 
  {
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");
    tree->Branch("nvertex",&nvertex,"nvertex/i");
    tree->Branch("weight",&weight, "weight/d");

    tree->Branch("Z","std::vector<Ko::ZCandidate>", &Z);
    tree->Branch("lepton1","std::vector<Ko::Lepton>", &lepton1);
    tree->Branch("lepton2","std::vector<Ko::Lepton>", &lepton2);
    tree->Branch("pfMet","std::vector<Ko::METCandidate>", &pfMet);
    tree->Branch("ttbar","std::vector<Ko::TTbarMass>", &ttbar);

    tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);
    tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
    tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
    tree->Branch("bjets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets);

    tree->Branch("MET",&MET,"MET/d");
    tree->Branch("dphimetlepton",&dphimetlepton,"dphimetlepton/d");

    tree->Branch("genttbarM",&genttbarM,"genttbarM/d");
    tree->Branch("resmaosM",&resmaosM,"resmaosM/d");
    tree->Branch("resvsumM",&resvsumM,"resvsumM/d");
    tree->Branch("resuser1M",&resuser1M,"resuser1M/d");
    tree->Branch("resuser2M",&resuser2M,"resuser2M/d");

    tree->Branch("sumEt",&sumEt,"sumEt/d");
    tree->Branch("photonEt",&photonEt,"photonEt/d");
    tree->Branch("chargedHadronEt",&chargedHadronEt,"chargedHadronEt/d");
    tree->Branch("neutralHadronEt",&neutralHadronEt,"neutralHadronEt/d");

    // Jet energy correction for 38X
    if ( doResJec_ )
    {
      edm::FileInPath jecFile("CondFormats/JetMETObjects/data/Spring10DataV2_L2L3Residual_AK5PF.txt");
      std::vector<JetCorrectorParameters> jecParams;
      jecParams.push_back(JetCorrectorParameters(jecFile.fullPath()));
      resJetCorrector_ = new FactorizedJetCorrector(jecParams);
    }

    if ( doJecUnc_){
        edm::FileInPath jecUncFile("CondFormats/JetMETObjects/data/Spring10_Uncertainty_AK5PF.txt");
        jecUnc_ = new JetCorrectionUncertainty(jecUncFile.fullPath());
    }
 

 } 

  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    bool accept = false;

    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

    edm::Handle<reco::VertexCollection> recVtxs_;
    iEvent.getByLabel("offlinePrimaryVertices",recVtxs_);

    int nv = 0 ;

    for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
      if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
            nv++;
      }
    }

    nvertex = nv;
 
    edm::Handle<double> weight_;
    iEvent.getByLabel("PUweight", weight_);

    if(weight_.isValid()){
      weight = *weight_;
    }else{
      weight = 1.0;
    }

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    edm::Handle<pat::METCollection> MET_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(metLabel_,MET_);

    pat::METCollection::const_iterator mi = MET_->begin();
    //MET = mi->pt();
    //met->push_back(mi->p4());
    //h_MET->Fill(MET);
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    sumEt = 0;
    photonEt = 0;
    chargedHadronEt = 0;
    neutralHadronEt = 0;

    for(CI ci = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
      const reco::PFCandidate& pfc = *ci;
      double E = pfc.energy();
      double theta = pfc.theta();
      double sintheta = sin(theta);
      double et = E*sintheta;
      sumEt += et;
      if( pfc.particleId() == 1 ) chargedHadronEt += et;
      if( pfc.particleId() == 5 ) neutralHadronEt += et;
      if( pfc.particleId() == 4 ) photonEt += et; 
    } 


    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    PFJetIDSelectionFunctor looseJetIdSelector_(pfJetIdParams_);

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);
        it1.setP4(it1.pfCandidateRef()->p4());
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;
        dphimetlepton = fabs(deltaPhi(mi->phi(),it1.phi()));

        accept = true;

        const Ko::Lepton lep1(it1.p4(), (int) it1.charge());
        const Ko::Lepton lep2(it2.p4(), (int) it2.charge());

        lepton1->push_back(lep1);
        lepton2->push_back(lep2);

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
        lepton1->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton1->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton1->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph1 );
    
        lepton2->back().setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton2->back().setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton2->back().setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph2 );
 
        //detector based isolation
        lepton1->back().setIsoDeposit( it1.trackIso(), it1.ecalIso(), it1.hcalIso());
        lepton2->back().setIsoDeposit( it2.trackIso(), it2.ecalIso(), it2.hcalIso());

        const Ko::ZCandidate dimuon(lepton1->back(), lepton2->back());
        Z->push_back(dimuon);


        h_leadingpt->Fill(it1.pt());
        h_secondpt->Fill(it2.pt());
        h_mass->Fill(dimuon.mass());

        double met_x = mi->px();
        double met_y = mi->py();
        
        //Jet selection by checking overlap with selected leptons
        for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {

          ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
          corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());

          double scaleF = 1.0;
          if(doResJec_){
            resJetCorrector_->setJetEta(jit->eta());
            resJetCorrector_->setJetPt(jit->pt());
            scaleF = resJetCorrector_->getCorrection();
            corrjet *= scaleF;
          }

          if(doJecUnc_){
            jecUnc_->setJetEta(jit->eta());
            jecUnc_->setJetPt(scaleF*jit->pt());
            met_x += corrjet.px();
            met_y += corrjet.py();
            double unc = jecUnc_->getUncertainty(up_);
            double c_sw = 0.015; //for release differences and calibration changes
            double c_pu = 0.2*0.8*2.2/(corrjet.pt()); // PU uncertainty
            double c_bjets = 0; // bjet uncertainty
            if(corrjet.pt() > 50 && corrjet.pt() < 200 && fabs(corrjet.eta()) < 2.0) {
              c_bjets = 0.02;
            }else c_bjets = 0.03;

            double cor = sqrt(c_sw*c_sw + c_pu*c_pu+c_bjets*c_bjets);
            unc = sqrt(unc*unc + cor*cor);
            double ptscaleunc = 0;
            if(up_) ptscaleunc = 1 + unc;
            else ptscaleunc = 1 - unc;
            corrjet *= ptscaleunc;
            met_x -= corrjet.px();
            met_y -= corrjet.py();
          }

          //geometric acceptance
          if(fabs(jit->eta()) >= 2.5) continue;

          pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
          bool passId = looseJetIdSelector_( *jit, looseJetIdSel);
          //jet id
          if(passId){
            const double dRval1 = deltaR(jit->eta(), jit->phi(), it1.eta(), it1.phi());
            const double dRval2 = deltaR(jit->eta(), jit->phi(), it2.eta(), it2.phi());
            bool overlap = checkOverlap(jit->eta(), jit->phi(), dRval1, lep1.relpfIso04(), dRval2, lep2.relpfIso04());
            //jet cleaning
            if( overlap ) continue;

            jets->push_back(corrjet);
            if(corrjet.pt() > 30){
              jetspt30->push_back(corrjet);
              discr = jit->bDiscriminator(bTagAlgo_);
              if(discr > minBTagValue_){
                bjets->push_back(corrjet);
              }
            }

          }
          
        }

        h_jet_multi->Fill(jets->size());
        h_jetpt30_multi->Fill(jetspt30->size());
        h_bjet_multi->Fill(bjets->size());

        ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
        corrmet.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x + met_y*met_y));
        MET = sqrt(met_x*met_x + met_y*met_y);
        met->push_back(corrmet);

        if(metStudy_){
          const Ko::METCandidate pfmet(MET, mi->sumEt(), mi->NeutralEMFraction(),mi->NeutralHadEtFraction(),mi->ChargedHadEtFraction(),mi->ChargedEMEtFraction(),mi->MuonEtFraction() );
          pfMet->push_back(pfmet);
        }

        h_MET->Fill(MET);

        if(jetspt30->size() >= 2){
          const Ko::TTbarMass ttbarMass(it1.p4(), it2.p4(), jetspt30->at(0), jetspt30->at(1), met->at(0));
          ttbar->push_back(ttbarMass);

          if(genParticles_.isValid()){
            TLorentzVector ttbarGen(0,0,0,0);

            for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
              int genId = mcIter->pdgId();
              if( fabs(genId) == 6){ 
                //double mass = mcIter->p4().M(); 
                TLorentzVector top(mcIter->p4().Px(), mcIter->p4().Py(), mcIter->p4().Pz(), mcIter->p4().E());
                ttbarGen = ttbarGen+top;
              }
          
            }

            genttbarM = ttbarGen.M();
            resmaosM = ttbar->back().maosM() - ttbarGen.M();
            resvsumM = ttbar->back().M() - ttbarGen.M();
            resuser1M = ttbar->back().user1M() - ttbarGen.M();
            resuser2M = ttbar->back().user2M() - ttbarGen.M();
          }
        }

        break;
      }
      break;
    }

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    tree->Fill();

    return accept;

  }

  void clear(){

    Z->clear();
    lepton1->clear();
    lepton2->clear();
    pfMet->clear();
    ttbar->clear();
    met->clear();
    jets->clear();
    jetspt30->clear();
    bjets->clear();

    genttbarM = -999;
    resmaosM = -999; 
    resvsumM = -999;
    resuser1M = -999;
    resuser2M = -999;

    sumEt = -1;
    photonEt = -1;
    chargedHadronEt = -1;
    neutralHadronEt = -1;

  }

  virtual bool endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup){
    if(useEventCounter_){
      for(unsigned int i=0;i<filters_.size();++i) {
        std::string name = filters_[i];
        edm::Handle<edm::MergeableCounter> numEventsCounter;
        lumi.getByLabel(name, numEventsCounter);
        if( numEventsCounter.isValid()){
          tmp->AddBinContent(i+1, numEventsCounter->value);
          tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
        }
      }
    }
    return true;
  }

  bool checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2)
  {

    bool overlap = false;
    if( reliso1 < relIso1_ ) {
      overlap = dRval1 < 0.4 ;
      if(overlap) return overlap;
    }

    if( reliso2 < relIso2_ ) {
      overlap = dRval2 < 0.4 ;
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
  edm::InputTag genParticlesLabel_;

  std::vector<std::string> filters_;
  bool metStudy_;
  bool useEventCounter_;
  //bool applyPUweight_;
  //edm::InputTag weightLabel_;
  // loose jet ID. 
  //PatJetIdSelector looseJetIdSelector_;
  //PFJetIDSelectionFunctor looseJetIdSelector_;
  
  // relIso
  double relIso1_;
  double relIso2_;
  // btag Discriminator
  std::string bTagAlgo_;
  double minBTagValue_;

  TTree* tree;

  TH1F * tmp;
  TH1F * h_leadingpt;
  TH1F * h_secondpt;
  TH1F * h_mass;
  TH1F * h_MET;
  TH1F * h_jet_multi;
  TH1F * h_jetpt30_multi;
  TH1F * h_bjet_multi;

  std::vector<Ko::ZCandidate>* Z;
  std::vector<Ko::Lepton>* lepton1;
  std::vector<Ko::Lepton>* lepton2;
  std::vector<Ko::METCandidate>* pfMet;
  std::vector<Ko::TTbarMass>* ttbar;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jets;
  std::vector<math::XYZTLorentzVector>* jetspt30;
  std::vector<math::XYZTLorentzVector>* bjets;

  double MET;
  double dphimetlepton;

  double discr;

  double genttbarM;
  double resmaosM;
  double resvsumM;
  double resuser1M;
  double resuser2M;

  double sumEt;
  double photonEt;
  double chargedHadronEt;
  double neutralHadronEt;


  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int nvertex;
  double weight;
  // Residual Jet energy correction for 38X
  bool doResJec_;
  bool doJecUnc_;
  bool up_;
  FactorizedJetCorrector* resJetCorrector_;
  JetCorrectionUncertainty *jecUnc_;

  edm::ParameterSet pfJetIdParams_;

};

