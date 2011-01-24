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
// $Id: TopDILAnalyzer.h,v 1.16 2011/01/17 09:00:55 tjkim Exp $
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

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "KoPFA/TopAnalyzer/interface/MaosTTbar.h"
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
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    looseJetIdSelector_.initialize( iConfig.getParameter<edm::ParameterSet> ("looseJetId") );
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");

    // Residual Jet energy correction for 38X
    doResJec_ = iConfig.getUntrackedParameter<bool>("doResJec", false);
    resJetCorrector_ = 0;

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
    toptotal = new std::vector<math::XYZTLorentzVector>();
    met = new std::vector<math::XYZTLorentzVector>();
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
  }

 private:
  virtual void beginJob() 
  {
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");

    tree->Branch("Z","std::vector<Ko::ZCandidate>", &Z);
    tree->Branch("toptotal","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &toptotal);

    tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);
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

    tree->Branch("maosttbarM",&maosttbarM,"maosttbarM/d");
    tree->Branch("maosMt2",&maosMt2,"maosMt2/d");
    tree->Branch("maostop1M",&maostop1M,"maostop1M/d");
    tree->Branch("maostop2M",&maostop2M,"maostop2M/d");

    //tree->Branch("maos2ttbarM",&maos2ttbarM,"maos2ttbarM/d");
    //tree->Branch("maos2Mt2",&maos2Mt2,"maos2Mt2/d");
    //tree->Branch("maos2top1M",&maos2top1M,"maos2top1M/d");
    //tree->Branch("maos2top2M",&maos2top2M,"maos2top2M/d");

    tree->Branch("vsumttbarM",&vsumttbarM, "vsumttbarM/d");
    tree->Branch("genttbarM",&genttbarM,"genttbarM/d");
    tree->Branch("relmaosM",&relmaosM,"relmaosM/d");
    tree->Branch("relvsumM",&relvsumM,"relvsumM/d");
    //tree->Branch("rel3ttbarM",&rel3ttbarM,"rel3ttbarM/d");

    // Jet energy correction for 38X
    if ( doResJec_ )
    {
      edm::FileInPath jecFile("CondFormats/JetMETObjects/data/Spring10DataV2_L2L3Residual_AK5PF.txt");
      std::vector<JetCorrectorParameters> jecParams;
      jecParams.push_back(JetCorrectorParameters(jecFile.fullPath()));
      resJetCorrector_ = new FactorizedJetCorrector(jecParams);
    }
  } 

  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    clear();

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
    met->push_back(mi->p4());
    h_MET->Fill(MET);

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

        //Jet selection by checking overlap with selected leptons
        for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {

          //geometric acceptance
          if(abs(jit->eta()) >= 2.5) continue;

          pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
          bool passId = looseJetIdSelector_( *jit, looseJetIdSel);
          //jet id
          if(passId){
            const double dRval1 = deltaR(jit->eta(), jit->phi(), it1.eta(), it1.phi());
            const double dRval2 = deltaR(jit->eta(), jit->phi(), it2.eta(), it2.phi());
            bool overlap = checkOverlap(jit->eta(), jit->phi(), dRval1, reliso04lep1, dRval2, reliso04lep2);
            //jet cleaning
            if( overlap ) continue;

            ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
            corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());

            if(doResJec_){
              resJetCorrector_->setJetEta(jit->eta());
              resJetCorrector_->setJetPt(jit->pt());
              const double scaleF = resJetCorrector_->getCorrection();
              corrjet *= scaleF;
            }

            jets->push_back(corrjet);
            if( corrjet.pt() > 30){
              jetspt30->push_back(corrjet);
            }
          }
        }

        h_jet_multi->Fill(jets->size());
        h_jetpt30_multi->Fill(jetspt30->size());


        if(jetspt30->size() >= 2){
          toptotal->push_back(it1.p4() + it2.p4() + jetspt30->at(0) + jetspt30->at(1) + met->at(0));

          //case 1
          const math::XYZTLorentzVector vis1op1 = it1.p4()+jetspt30->at(0);
          const math::XYZTLorentzVector vis2op1 = it2.p4()+jetspt30->at(1);
          const TLorentzVector lep1op1(vis1op1.Px(), vis1op1.Py(), vis1op1.Pz(), vis1op1.E());
          const TLorentzVector lep2op1(vis2op1.Px(), vis2op1.Py(), vis2op1.Pz(), vis2op1.E());

          //case 2
          const math::XYZTLorentzVector vis1op2 = it2.p4()+jetspt30->at(0);
          const math::XYZTLorentzVector vis2op2 = it1.p4()+jetspt30->at(1);
          const TLorentzVector lep1op2(vis1op2.Px(), vis1op2.Py(), vis1op2.Pz(), vis1op2.E());
          const TLorentzVector lep2op2(vis2op2.Px(), vis2op2.Py(), vis2op2.Pz(), vis2op2.E());

          //missing et
          const math::XYZTLorentzVector invis = met->at(0);
          const TLorentzVector metvec(invis.Px(), invis.Py(), 0, invis.Pt());

          //Fill tree for ttbar invariant mass and top mass for two different cases
          Ko::MaosTTbar ttbar1;
          double ttbar1Mt2 = sqrt( ttbar1.MAOS(metvec, lep1op1, lep2op1, 0.0, 0.0, false) );
          Ko::MaosTTbar ttbar2;
          double ttbar2Mt2 = sqrt( ttbar2.MAOS(metvec, lep1op2, lep2op2, 0.0, 0.0, false) );

          //double diffmaos1 = fabs(ttbar1top1M - ttbar1top2M);
          //double diffmaos2 = fabs(ttbar2top1M - ttbar2top2M);

          if( ttbar1Mt2 < ttbar2Mt2 ){
            maosMt2 = ttbar1Mt2;
            maosttbarM = ttbar1.M();
            maostop1M = ttbar1.top1M();
            maostop2M = ttbar1.top2M();
          }else{
            maosMt2 = ttbar2Mt2;
            maosttbarM = ttbar2.M();
            maostop1M = ttbar2.top1M();
            maostop2M = ttbar2.top2M();
          }

          //if( diffmaos1 < diffmaos2 ){
          //  maos2Mt2 = ttbar1Mt2;
          //  maos2ttbarM = ttbar1.M();
          //  maos2top1M = ttbar1.top1M();
          //  maos2top2M = ttbar1.top2M();
          //}else{
          //  maos2Mt2 = ttbar2Mt2;
          //  maos2ttbarM = ttbar2.M();
          //  maos2top1M = ttbar2.top1M();
          //  maos2top2M = ttbar2.top2M();
          //}

          vsumttbarM = (it1.p4() + it2.p4() + jetspt30->at(0) + jetspt30->at(1) + met->at(0)).M();

          if(genParticles_.isValid()){
              TLorentzVector ttbar(0,0,0,0);

            for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
              int genId = mcIter->pdgId();
              if( fabs(genId) == 6){ 
                //double mass = mcIter->p4().M(); 
                TLorentzVector top(mcIter->p4().Px(), mcIter->p4().Py(), mcIter->p4().Pz(), mcIter->p4().E());
                ttbar = ttbar+top;
              }
          
            }
            genttbarM = ttbar.M();
            relmaosM = ttbar.M() - maosttbarM;
            relvsumM = ttbar.M() - vsumttbarM;
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
    toptotal->clear();
    met->clear();
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

    //clear maos variables
    maosttbarM = -1;
    maosMt2 = -1;
    maostop1M = -1;
    maostop2M = -1;

    //maos2ttbarM = -1;
    //maos2Mt2 = -1;
    //maos2top1M = -1;
    //maos2top2M = -1;

    vsumttbarM = -1;
    genttbarM = -1;
    relmaosM = -999; 
    relvsumM = -999;
    //rel3ttbarM = -999;
 

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
  bool useEventCounter_;
  /// loose jet ID. 
  PatJetIdSelector looseJetIdSelector_;
  /// relIso
  double relIso1_;
  double relIso2_;

  TTree* tree;

  TH1F * tmp;
  TH1F * h_leadingpt;
  TH1F * h_secondpt;
  TH1F * h_mass;
  TH1F * h_MET;
  TH1F * h_jet_multi;
  TH1F * h_jetpt30_multi;

  std::vector<Ko::ZCandidate>* Z;
  std::vector<math::XYZTLorentzVector>* toptotal;
  std::vector<math::XYZTLorentzVector>* met;
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

  double maosttbarM;
  double maosMt2;
  double maostop1M;
  double maostop2M;

  //double maos2ttbarM;
  //double maos2Mt2;
  //double maos2top1M;
  //double maos2top2M;

  double vsumttbarM;

  double genttbarM;
  double relmaosM;
  double relvsumM;
  //double rel3ttbarM;

  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  // Residual Jet energy correction for 38X
  bool doResJec_;
  FactorizedJetCorrector* resJetCorrector_;
};

