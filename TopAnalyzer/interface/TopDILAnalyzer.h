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
// $Id: TopDILAnalyzer.h,v 1.36 2011/04/27 13:43:06 tjkim Exp $
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
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/H2WWMass.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "PFAnalyses/CommonTools/interface/CandidateSelector.h"
#include "PFAnalyses/CommonTools/interface/PatJetIdSelector.h"

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
//#include "KoPFA/TopAnalyzer/interface/MaosTTbar.h"
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
class TopDILAnalyzer : public edm::EDAnalyzer {
 public:
  explicit TopDILAnalyzer(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    metStudy_ = iConfig.getParameter<bool>("metStudy");
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    looseJetIdSelector_.initialize( iConfig.getParameter<edm::ParameterSet> ("looseJetId") );
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
    pfMet = new std::vector<Ko::METCandidate>();
    ttbar = new std::vector<Ko::TTbarMass>();
    h2ww = new std::vector<Ko::H2WWMass>();
    met = new std::vector<math::XYZTLorentzVector>();
    jets = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
    bjets = new std::vector<math::XYZTLorentzVector>();

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

    relIso03lep1 = new std::vector<double>;
    relIso03lep2 = new std::vector<double>;
    relIso04lep1 = new std::vector<double>;
    relIso04lep2 = new std::vector<double>;
    relIso05lep1 = new std::vector<double>;
    relIso05lep2 = new std::vector<double>;

    trackIso1 = new std::vector<double>;
    ecalIso1 = new std::vector<double>;
    hcalIso1 = new std::vector<double>;
    trackIso2 = new std::vector<double>;
    ecalIso2 = new std::vector<double>;
    hcalIso2 = new std::vector<double>;
  
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
    tree->Branch("weight",&weight, "weight/d");

    tree->Branch("Z","std::vector<Ko::ZCandidate>", &Z);
    tree->Branch("pfMet","std::vector<Ko::METCandidate>", &pfMet);
    tree->Branch("ttbar","std::vector<Ko::TTbarMass>", &ttbar);
    tree->Branch("h2ww","std::vector<Ko::H2WWMass>", &h2ww);

    tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);
    tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
    tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
    tree->Branch("bjets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets);

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

    tree->Branch("relIso03lep1","std::vector<double>",&relIso03lep1);
    tree->Branch("relIso03lep2","std::vector<double>",&relIso03lep2);
    tree->Branch("relIso04lep1","std::vector<double>",&relIso04lep1);
    tree->Branch("relIso04lep2","std::vector<double>",&relIso04lep2);
    tree->Branch("relIso05lep1","std::vector<double>",&relIso05lep1);
    tree->Branch("relIso05lep2","std::vector<double>",&relIso05lep2);

    tree->Branch("trackIso1","std::vector<double>", &trackIso1);
    tree->Branch("ecalIso1","std::vector<double>", &ecalIso1);
    tree->Branch("hcalIso1","std::vector<double>", &hcalIso1);
    tree->Branch("trackIso2","std::vector<double>", &trackIso2);
    tree->Branch("ecalIso2","std::vector<double>", &ecalIso2);
    tree->Branch("hcalIso2","std::vector<double>", &hcalIso2);

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

  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

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

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);
        it1.setP4(it1.pfCandidateRef()->p4());
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;
        dphimetlepton = fabs(deltaPhi(mi->phi(),it1.phi()));

        const int sign = it1.charge() * it2.charge();
        const Ko::ZCandidate dimuon(it1.p4(), it2.p4(), sign);

        Z->push_back(dimuon);

        ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > met_;
        met_.SetPxPyPzE(mi->px(),mi->py(),0,mi->energy());
        const Ko::H2WWMass h2wwMass(it1.p4(), it2.p4(), met_,  it1.charge(),it2.charge());
        h2ww->push_back(h2wwMass);

        h_leadingpt->Fill(it1.pt());
        h_secondpt->Fill(it2.pt());
        h_mass->Fill(dimuon.mass());

        reco::IsoDeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
        reco::IsoDeposit::Direction Dir2 = Direction(it2.eta(),it2.phi());
        IsoDeposit::AbsVetos vetos_ch;
        IsoDeposit::AbsVetos vetos_nh;
        vetos_nh.push_back(new ThresholdVeto( 0.5 ));
        IsoDeposit::AbsVetos vetos_ph1;
        vetos_ph1.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph1.push_back(new RectangularEtaPhiVeto( Dir1, -0.1, 0.1, -0.2, 0.2));
        IsoDeposit::AbsVetos vetos_ph2;
        vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph2.push_back(new RectangularEtaPhiVeto( Dir2, -0.1, 0.1, -0.2, 0.2));

        chIso1->push_back(it1.chargedHadronIso());
        phIso1->push_back(it1.photonIso());
        nhIso1->push_back(it1.neutralHadronIso());

        chIso2->push_back(it2.chargedHadronIso());
        phIso2->push_back(it2.photonIso());
        nhIso2->push_back(it2.neutralHadronIso());

        const double chiso03lep1 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
        const double nhiso03lep1 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
        const double phiso03lep1 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph1).first;
        const double chiso03lep2 = it2.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
        const double nhiso03lep2 = it2.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
        const double phiso03lep2 = it2.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph1).first;

        const double chiso04lep1 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
        const double nhiso04lep1 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first;
        const double phiso04lep1 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph1).first;
        const double chiso04lep2 = it2.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
        const double nhiso04lep2 = it2.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first;
        const double phiso04lep2 = it2.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph1).first;

        const double chiso05lep1 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.5, vetos_ch).first;
        const double nhiso05lep1 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.5, vetos_nh).first;
        const double phiso05lep1 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.5, vetos_ph1).first;
        const double chiso05lep2 = it2.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.5, vetos_ch).first;
        const double nhiso05lep2 = it2.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.5, vetos_nh).first;
        const double phiso05lep2 = it2.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.5, vetos_ph1).first;     

        chIsoOpt1->push_back(chiso04lep1);
        nhIsoOpt1->push_back(nhiso04lep1);
        phIsoOpt1->push_back(phiso04lep1);

        chIsoOpt2->push_back(chiso04lep2);
        nhIsoOpt2->push_back(nhiso04lep2);
        phIsoOpt2->push_back(phiso04lep2);

        const double reliso03lep1 =  (chiso03lep1+ nhiso03lep1 + phiso03lep1) / it1.pt();
        const double reliso03lep2 =  (chiso03lep2+ nhiso03lep2 + phiso03lep2) / it2.pt();
        const double reliso04lep1 =  (chiso04lep1+ nhiso04lep1 + phiso04lep1) / it1.pt();
        const double reliso04lep2 =  (chiso04lep2+ nhiso04lep2 + phiso04lep2) / it2.pt();
        const double reliso05lep1 =  (chiso05lep1+ nhiso05lep1 + phiso05lep1) / it1.pt();
        const double reliso05lep2 =  (chiso05lep2+ nhiso05lep2 + phiso05lep2) / it2.pt();

        relIso03lep1->push_back(reliso03lep1);
        relIso03lep2->push_back(reliso03lep2);
        relIso04lep1->push_back(reliso04lep1);
        relIso04lep2->push_back(reliso04lep2);
        relIso05lep1->push_back(reliso05lep1);
        relIso05lep2->push_back(reliso05lep2);

        trackIso1->push_back(it1.trackIso());
        ecalIso1->push_back(it1.ecalIso());
        hcalIso1->push_back(it1.hcalIso());

        trackIso2->push_back(it2.trackIso());
        ecalIso2->push_back(it2.ecalIso());
        hcalIso2->push_back(it2.hcalIso());
     
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
            bool overlap = checkOverlap(jit->eta(), jit->phi(), dRval1, reliso04lep1, dRval2, reliso04lep2);
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

  }

  void clear(){

    Z->clear();
    pfMet->clear();
    ttbar->clear();
    h2ww->clear();
    met->clear();
    jets->clear();
    jetspt30->clear();
    bjets->clear();

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

    relIso03lep1->clear();
    relIso03lep2->clear();
    relIso04lep1->clear();
    relIso04lep2->clear();
    relIso05lep1->clear();
    relIso05lep2->clear();

    trackIso1->clear();
    ecalIso1->clear();
    hcalIso1->clear();
    trackIso2->clear();
    ecalIso2->clear();
    hcalIso2->clear();

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
  PatJetIdSelector looseJetIdSelector_;
  
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
  std::vector<Ko::METCandidate>* pfMet;
  std::vector<Ko::TTbarMass>* ttbar;
  std::vector<Ko::H2WWMass>* h2ww;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jets;
  std::vector<math::XYZTLorentzVector>* jetspt30;
  std::vector<math::XYZTLorentzVector>* bjets;

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

  std::vector<double>* relIso03lep1;
  std::vector<double>* relIso03lep2;
  std::vector<double>* relIso04lep1;
  std::vector<double>* relIso04lep2;
  std::vector<double>* relIso05lep1;
  std::vector<double>* relIso05lep2;

  std::vector<double>* trackIso1;
  std::vector<double>* ecalIso1;
  std::vector<double>* hcalIso1;
  std::vector<double>* trackIso2;
  std::vector<double>* ecalIso2;
  std::vector<double>* hcalIso2;
  
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

  double weight;
  // Residual Jet energy correction for 38X
  bool doResJec_;
  bool doJecUnc_;
  bool up_;
  FactorizedJetCorrector* resJetCorrector_;
  JetCorrectionUncertainty *jecUnc_;
};

