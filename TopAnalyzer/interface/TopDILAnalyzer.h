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
// $Id: TopDILAnalyzer.h,v 1.63 2012/02/20 10:16:54 tjkim Exp $
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
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

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
    vertexLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    applyIso_ = iConfig.getUntrackedParameter<bool>("applyIso",true);
    oppPair_ = iConfig.getUntrackedParameter<bool>("oppPair",true);
    bTagAlgo_ = iConfig.getUntrackedParameter<std::string>("bTagAlgo");
    minBTagValue_ = iConfig.getUntrackedParameter<double>("minBTagValue");
    
    PileUpRD_ = iConfig.getParameter< std::vector<double> >("PileUpRD");
    PileUpMC_ = iConfig.getParameter< std::vector<double> >("PileUpMC");

    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for Top quark study");
    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    h_leadingpt   = fs->make<TH1F>( "h_leadingpt"  , "p_{t}", 50,  0., 100. );
    h_secondpt    = fs->make<TH1F>( "h_secondpt"  , "p_{t}", 50,  0., 100. );
    h_mass      = fs->make<TH1F>( "h_mass", "Mass", 100, 0., 200. );
    h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
    h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);
    h_npileupin = fs->make<TH1F>( "h_npileupin", "npileupin", 30, 0, 30);
    h_npileup = fs->make<TH1F>( "h_npileup", "npileup", 30, 0, 30);
    h_nvertex = fs->make<TH1F>( "h_nvertex", "nvertex", 30, 0, 30);

    Z = new std::vector<Ko::ZCandidate>();
    lepton1 = new std::vector<Ko::Lepton>();
    lepton2 = new std::vector<Ko::Lepton>();
    pfMet = new std::vector<Ko::METCandidate>();
    ttbar = new std::vector<Ko::TTbarMass>();
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
    bjets_TCHEL = new std::vector<math::XYZTLorentzVector>();
    bjets_CSVL = new std::vector<math::XYZTLorentzVector>();
    bjets_CSVM = new std::vector<math::XYZTLorentzVector>();
    bjets_CSVT = new std::vector<math::XYZTLorentzVector>();
    bjets_SSVHEM = new std::vector<math::XYZTLorentzVector>();
 
  }


  ~TopDILAnalyzer()
  {
  }

 private:
  virtual void beginJob() 
  {
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");
    tree->Branch("npileup",&npileup,"npileup/i");
    tree->Branch("nvertex",&nvertex,"nvertex/i");
    tree->Branch("weightin",&weightin, "weightin/d");
    tree->Branch("weight",&weight, "weight/d");
    tree->Branch("weightplus",&weightplus, "weightplus/d");
    tree->Branch("weightminus",&weightminus, "weightminus/d");

    tree->Branch("ZMass",&ZMass,"ZMass/d");
    tree->Branch("PairSign",&PairSign,"PairSign/d");
    tree->Branch("relIso1",&relIso1,"relIso1/d");
    tree->Branch("relIso2",&relIso2,"relIso2/d");
    tree->Branch("isIso",&isIso,"isIso/d");
    tree->Branch("pt1",&pt1,"pt1/d");
    tree->Branch("pt2",&pt2,"pt2/d");
    tree->Branch("eta1",&eta1,"eta1/d");
    tree->Branch("eta2",&eta2,"eta2/d");
    tree->Branch("phi1",&phi1,"phi1/d");
    tree->Branch("phi2",&phi2,"phi2/d");

    //tree->Branch("Z","std::vector<Ko::ZCandidate>", &Z);
    //tree->Branch("lepton1","std::vector<Ko::Lepton>", &lepton1);
    //tree->Branch("lepton2","std::vector<Ko::Lepton>", &lepton2);
    //tree->Branch("pfMet","std::vector<Ko::METCandidate>", &pfMet);
    tree->Branch("ttbar","std::vector<Ko::TTbarMass>", &ttbar);

    //tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);
    tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
    tree->Branch("nbjets_TCHEL",&nbjets_TCHEL,"nbjets_TCHEL/i");    
    tree->Branch("nbjets_CSVL",&nbjets_CSVL,"nbjets_CSVL/i");    
    tree->Branch("nbjets_CSVM",&nbjets_CSVM,"nbjets_CSVM/i");    
    tree->Branch("nbjets_CSVT",&nbjets_CSVT,"nbjets_CSVT/i");    
    tree->Branch("nbjets_SSVHEM",&nbjets_SSVHEM,"nbjets_SSVHEM/i");    

    //tree->Branch("bjets_TCHEL","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_TCHEL);
    //tree->Branch("bjets_CSVL","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_CSVL);
    //tree->Branch("bjets_CSVM","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_CSVM);
    //tree->Branch("bjets_CSVT","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_CSVT);
    //tree->Branch("bjets_SSVHEM","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_SSVHEM);
    
    tree->Branch("MET",&MET,"MET/d");
    tree->Branch("dphimetlepton1",&dphimetlepton1,"dphimetlepton1/d");
    tree->Branch("dphimetlepton2",&dphimetlepton2,"dphimetlepton2/d");
    tree->Branch("dphimetjet1",&dphimetjet1,"dphimetjet1/d");
    tree->Branch("dphimetjet2",&dphimetjet2,"dphimetjet2/d");

    tree->Branch("genttbarM",&genttbarM,"genttbarM/d");

    std::vector< float > Wlumi ;
    std::vector< float > TrueDist2011;
    
    for( int i=0; i< 50; ++i) {
      TrueDist2011.push_back((float)PileUpRD_[i]);
      Wlumi.push_back((float)PileUpMC_[i]);
    }

    LumiWeights_ = edm::LumiReWeighting(Wlumi, TrueDist2011);

    PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
    PShiftUp_ = reweight::PoissonMeanShifter(0.5);

  } 

  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    bool accept = false;

    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

    edm::Handle<double>  rho;
    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

    edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

    std::vector<PileupSummaryInfo>::const_iterator PVI;

    int npv = -1;
    int npvin = -1;
    float sum_nvtx = 0;
    float ave_nvtx = 0;

    if( PupInfo.isValid()){
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
        int tmpnpv = PVI->getPU_NumInteractions();
        sum_nvtx += float(tmpnpv);

        int BX = PVI->getBunchCrossing();

        if(BX == 0) {
          npvin = PVI->getPU_NumInteractions();
          npv = PVI->getTrueNumInteractions();
          continue;
        }

      } 

      ave_nvtx = sum_nvtx/3.;

      double win = LumiWeights_.weight( npvin );
      double w = LumiWeights_.weight( npv );
      //weight = LumiWeights_.weight3BX( ave_nvtx );
      double wplus  = weight*PShiftUp_.ShiftWeight( npv );
      double wminus = weight*PShiftDown_.ShiftWeight( npv );
      weightin = win; 
      weight = w;
      weightplus = wplus;
      weightminus = wminus;
    }

    h_npileupin->Fill(npv);
    h_npileup->Fill(ave_nvtx);

    npileup = npv;

    edm::Handle<reco::VertexCollection> recVtxs_;
    iEvent.getByLabel(vertexLabel_,recVtxs_);

    int nv = 0 ;

    for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
      if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
        nv++;
      }
    }

    nvertex = nv;

    h_nvertex->Fill(nv);

    //edm::Handle<double> weight_;
    //iEvent.getByLabel("PUweight", weight_);

    //if(weight_.isValid()){
    //  weight = *weight_;
    //}else{
    //  weight = 1.0;
    //}

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    edm::Handle<pat::METCollection> MET_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(metLabel_,MET_);

    pat::METCollection::const_iterator mi = MET_->begin();

    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    bool selected = false;

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);
        it1.setP4(it1.pfCandidateRef()->p4());
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

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

        //explicitly requuire opposite sign of isolated leptons
        const Ko::ZCandidate dimuon(lepton1->back(), lepton2->back());
        if( dimuon.mass() <= 12 ) continue;

        bool iso = lepton1->back().relpfIso03() < relIso1_ && lepton2->back().relpfIso03() < relIso2_;
        //bool noiso = lepton1->back().relpfIso03() > relIso1_ && lepton2->back().relpfIso03() > relIso2_;
        bool opp = it1.charge() * it2.charge() < 0;

        if(!selected) {
          selected = true;
          Z->push_back(dimuon);
          ZMass = dimuon.mass();
          PairSign = (int) it1.charge() * it2.charge();
          relIso1 = lepton1->back().relpfIso03();
          relIso2 = lepton2->back().relpfIso03();
          pt1 = it1.pt();
          pt2 = it2.pt();
          eta1 = it1.eta();
          eta2 = it2.eta();
          phi1 = it1.phi();
          phi2 = it2.phi();
          if( iso ) isIso = 1;  
        }

        if( !iso && applyIso_) continue;
        if( !opp && oppPair_) continue;

        accept = true;
        dphimetlepton1 = fabs(deltaPhi(mi->phi(),it1.phi()));
        dphimetlepton2 = fabs(deltaPhi(mi->phi(),it2.phi()));
 
        Z->push_back(dimuon);
        ZMass = dimuon.mass();
        PairSign = (int) it1.charge() * it2.charge();
        relIso1 = lepton1->back().relpfIso03();
        relIso2 = lepton2->back().relpfIso03();
        pt1 = it1.pt();
        pt2 = it2.pt();
        eta1 = it1.eta();
        eta2 = it2.eta();
        phi1 = it1.phi();
        phi2 = it2.phi();
        if( iso ) isIso = 1;       
        
        h_leadingpt->Fill(it1.pt());
        h_secondpt->Fill(it2.pt());
        h_mass->Fill(dimuon.mass());

        break;
      }
      break;
    }

    int nTCHEL = 0;
    int nCSVL = 0;
    int nCSVM = 0;
    int nCSVT = 0;
    int nSSVHEM = 0;

    for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
      corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());

      jetspt30->push_back(corrjet);        

      if( jit->bDiscriminator("trackCountingHighEffBJetTags")  > 1.7){
        nTCHEL++;
      }
      if( jit->bDiscriminator("combinedSecondaryVertexBJetTags")  > 0.244){
        nCSVL++;
      }
      if( jit->bDiscriminator("combinedSecondaryVertexBJetTags")  > 0.679){
        nCSVM++;
      }
      if( jit->bDiscriminator("combinedSecondaryVertexBJetTags")  > 0.898){
        nCSVT++;
      }
      if( jit->bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74){
        nSSVHEM++;
      }
    }

    nbjets_TCHEL = nTCHEL;
    nbjets_CSVL= nCSVL;
    nbjets_CSVM = nCSVM;
    nbjets_CSVT = nCSVT;
    nbjets_SSVHEM = nSSVHEM;

    if( jetspt30->size() >= 2 ){
      dphimetjet1 = fabs(deltaPhi(mi->phi(),jetspt30->at(0).phi()));
      dphimetjet2 = fabs(deltaPhi(mi->phi(),jetspt30->at(1).phi()));
    }

    h_jetpt30_multi->Fill(jetspt30->size());

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(mi->px(),mi->py(),0,mi->pt());
    MET = mi->pt();
    met->push_back(corrmet);

    if(metStudy_){
      const Ko::METCandidate pfmet(MET, mi->sumEt(), mi->NeutralEMFraction(),mi->NeutralHadEtFraction(),mi->ChargedHadEtFraction(),mi->ChargedEMEtFraction(),mi->MuonEtFraction() );
      pfMet->push_back(pfmet);
    }

    h_MET->Fill(MET);

    if(jetspt30->size() >= 2 && ZMass > 12){
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep1;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep2;
      lep1.SetPxPyPzE(Z->back().leg1().px(),Z->back().leg1().py(),Z->back().leg1().pz(),Z->back().leg1().energy());
      lep2.SetPxPyPzE(Z->back().leg2().px(),Z->back().leg2().py(),Z->back().leg2().pz(),Z->back().leg2().energy());

      const Ko::TTbarMass ttbarMass(lep1, lep2, jetspt30->at(0), jetspt30->at(1), met->at(0));
      ttbar->push_back(ttbarMass);

      if(genParticles_.isValid()){
        reco::Candidate::LorentzVector ttbarGen;
        for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
          int genId = mcIter->pdgId();
          if( abs(genId) == 6){
            ttbarGen += mcIter->p4();
          }
        }

        genttbarM = ttbarGen.M();
      }
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
    jetspt30->clear();
    //bjets_TCHEL->clear();
    //bjets_CSVL->clear();
    //bjets_CSVM->clear();
    //bjets_CSVT->clear();
    //bjets_SSVHEM->clear();

    nbjets_TCHEL = -999;
    nbjets_CSVL= -999;
    nbjets_CSVM = -999;
    nbjets_CSVT = -999;
    nbjets_SSVHEM = -999;

    weight = 1.0;
    weightin = 1.0;
    weightplus = 1.0;
    weightminus = 1.0;

    dphimetlepton1 = -999;  
    dphimetlepton2 = -999;  
    dphimetjet1 = -999;
    dphimetjet2 = -999;

    ZMass = -999; 
    PairSign = -999;
    relIso1 = -999;
    relIso2 = -999;
    isIso = -999;
    pt1 = -999; 
    pt2 = -999;
    eta1 = -999;
    eta2 = -999;
    phi1 = -999;
    phi2 = -999;

    genttbarM = -999;

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
  edm::InputTag vertexLabel_;

  std::vector<std::string> filters_;
  bool metStudy_;
  bool useEventCounter_;
  
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
  TH1F * h_jetpt30_multi;
  TH1F * h_npileupin;
  TH1F * h_npileup;
  TH1F * h_nvertex;

  std::vector<Ko::ZCandidate>* Z;
  std::vector<Ko::Lepton>* lepton1;
  std::vector<Ko::Lepton>* lepton2;
  std::vector<Ko::METCandidate>* pfMet;
  std::vector<Ko::TTbarMass>* ttbar;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jetspt30;
  std::vector<math::XYZTLorentzVector>* bjets_TCHEL;
  std::vector<math::XYZTLorentzVector>* bjets_CSVL;
  std::vector<math::XYZTLorentzVector>* bjets_CSVM;
  std::vector<math::XYZTLorentzVector>* bjets_CSVT;
  std::vector<math::XYZTLorentzVector>* bjets_SSVHEM;
 
  int nbjets_TCHEL;
  int nbjets_CSVL;
  int nbjets_CSVM;
  int nbjets_CSVT;
  int nbjets_SSVHEM;
 
  double MET;
  double dphimetlepton1;
  double dphimetlepton2;
  double dphimetjet1;
  double dphimetjet2;
  double ZMass;
  double PairSign;
  double relIso1;
  double relIso2;
  double isIso;
  double pt1;
  double pt2;
  double eta1;
  double eta2;
  double phi1;
  double phi2;

  double discr;

  double genttbarM;


  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int npileup;
  unsigned int nvertex;
  double weightin;
  double weight;
  double weightplus;
  double weightminus;

  edm::LumiReWeighting LumiWeights_;

  std::vector<double> PileUpRD_;
  std::vector<double> PileUpMC_;

  reweight::PoissonMeanShifter PShiftUp_;
  reweight::PoissonMeanShifter PShiftDown_;

  bool applyIso_;
  bool oppPair_;

};

