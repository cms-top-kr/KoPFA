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
// $Id: TopDILAnalyzer.h,v 1.92 2012/11/01 09:33:18 tjkim Exp $
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
#include "KoPFA/DataFormats/interface/TTbarCandidate.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include "KoPFA/TopAnalyzer/interface/BTagWeight.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"
#include "KoPFA/TopAnalyzer/interface/Histograms.h"

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
    dileptonLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("dileptonLabel");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    genJetsLabel_= iConfig.getParameter<edm::InputTag>("genJetsLabel");
    vertexLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    puWeightLabel_ = iConfig.getParameter<edm::InputTag>("puWeightLabel");
    puUpWeightLabel_ = iConfig.getParameter<edm::InputTag>("puUpWeightLabel");
    puDwWeightLabel_ = iConfig.getParameter<edm::InputTag>("puDwWeightLabel");
    puNVertexLabel_ = iConfig.getParameter<edm::InputTag>("puNVertexLabel");
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    applyIso_ = iConfig.getUntrackedParameter<bool>("applyIso",true);
    oppPair_ = iConfig.getUntrackedParameter<bool>("oppPair",true);
    std::vector<edm::ParameterSet> bTagSets = iConfig.getUntrackedParameter<std::vector<edm::ParameterSet> >("bTagSets");
    for ( int i=0, n=bTagSets.size(); i<n; ++i )
    {
      edm::ParameterSet& bTagSet = bTagSets[i];
      const std::string algo = bTagSet.getUntrackedParameter<std::string>("algo");
      const std::string name = bTagSet.getUntrackedParameter<std::string>("name");
      const double cutValue = bTagSet.getUntrackedParameter<double>("cutValue");
      const bool isCutMin = bTagSet.getUntrackedParameter<bool>("isCutMin", true); // True : reject jets with smaller than cutValue 

      std::vector<std::string>::iterator foundBtagName = std::find(bTagNames_.begin(), bTagNames_.end(), name);
      if ( foundBtagName == bTagNames_.end() )
      {
        bTagAlgos_.push_back(algo);
        bTagNames_.push_back(name);
        bTagCutValues_.push_back(cutValue);
        bTagIsCutMin_.push_back(isCutMin);
        nbjets30_.push_back(-999);
       // nbjets20_.push_back(-999);
      }
      else
      {
        cout << "what is this?" << endl;
        const int index = foundBtagName - bTagNames_.begin();
        bTagAlgos_[index] = algo;
        bTagCutValues_[index] = cutValue;
        bTagIsCutMin_[index] = isCutMin;
      }
    }
   
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for Top quark study");
    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());
 
    //TFileDirectory btagdir = fs->mkdir(Form("btagEff", i));
    

    Z = new std::vector<vallot::ZCandidate>();
    lepton1 = new std::vector<vallot::Lepton>();
    lepton2 = new std::vector<vallot::Lepton>();
    pfMet = new std::vector<vallot::METCandidate>();
    ttbar = new std::vector<vallot::TTbarMass>();
    ttbarGen = new std::vector<vallot::TTbarCandidate>();
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
    jetspt30flavor = new std::vector<int>();
    jetspt30fromtop = new std::vector<int>();
    jetspt30bDiscriminator = new std::vector<double>();
    jetspt30bDiscriminatorSSV = new std::vector<double>();

    bCSVL_ext = new std::vector<int>();
    bCSVM_ext = new std::vector<int>();
    bCSVT_ext = new std::vector<int>();

    //jetspt20 = new std::vector<math::XYZTLorentzVector>();
    //jetspt20flavor = new std::vector<int>();
    //jetspt20bDiscriminator = new std::vector<double>();

    nCutStep_ = 7;
    for ( int i = 0; i<nCutStep_; ++i )
    {
      TFileDirectory dir = fs->mkdir(Form("Step%d", i));
      h_.push_back(Histograms(&dir));
      for ( unsigned int j = 0; j<bTagAlgos_.size(); ++j )
      {
        const char* algo = bTagAlgos_[j].c_str();
        h_[i].hnBJets.push_back(dir.make<TH1F>(Form("hnBJets_%s", algo), Form("%s B jets;Number of B jets;Events", algo), 5, 0, 5));
      }
    }
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

    tree->Branch("puweight",&puweight, "puweight/d");
    tree->Branch("puweightplus",&puweightplus, "puweightplus/d");
    tree->Branch("puweightminus",&puweightminus, "puweightminus/d");

    tree->Branch("bweight30CSVL",&bweight30CSVL, "bweight30CSVL/d");
    tree->Branch("bweight30CSVM",&bweight30CSVM, "bweight30CSVM/d");
    tree->Branch("bweight30CSVT",&bweight30CSVT, "bweight30CSVT/d");
    tree->Branch("bweight30CSVLup",&bweight30CSVLup, "bweight30CSVLup/d");
    tree->Branch("bweight30CSVMup",&bweight30CSVMup, "bweight30CSVMup/d");
    tree->Branch("bweight30CSVTup",&bweight30CSVTup, "bweight30CSVTup/d");
    tree->Branch("bweight30CSVLdw",&bweight30CSVLdw, "bweight30CSVLdw/d");
    tree->Branch("bweight30CSVMdw",&bweight30CSVMdw, "bweight30CSVMdw/d");
    tree->Branch("bweight30CSVTdw",&bweight30CSVTdw, "bweight30CSVTdw/d");
    tree->Branch("bweight30CSVLuplight",&bweight30CSVLuplight, "bweight30CSVLuplight/d");
    tree->Branch("bweight30CSVMuplight",&bweight30CSVMuplight, "bweight30CSVMuplight/d");
    tree->Branch("bweight30CSVTuplight",&bweight30CSVTuplight, "bweight30CSVTuplight/d");
    tree->Branch("bweight30CSVLdwlight",&bweight30CSVLdwlight, "bweight30CSVLdwlight/d");
    tree->Branch("bweight30CSVMdwlight",&bweight30CSVMdwlight, "bweight30CSVMdwlight/d");
    tree->Branch("bweight30CSVTdwlight",&bweight30CSVTdwlight, "bweight30CSVTdwlight/d");

/*
    tree->Branch("bweight20CSVL",&bweight20CSVL, "bweight20CSVL/d");
    tree->Branch("bweight20CSVM",&bweight20CSVM, "bweight20CSVM/d");
    tree->Branch("bweight20CSVT",&bweight20CSVT, "bweight20CSVT/d");
    tree->Branch("bweight20CSVLup",&bweight20CSVLup, "bweight20CSVLup/d");
    tree->Branch("bweight20CSVMup",&bweight20CSVMup, "bweight20CSVMup/d");
    tree->Branch("bweight20CSVTup",&bweight20CSVTup, "bweight20CSVTup/d");
    tree->Branch("bweight20CSVLdw",&bweight20CSVLdw, "bweight20CSVLdw/d");
    tree->Branch("bweight20CSVMdw",&bweight20CSVMdw, "bweight20CSVMdw/d");
    tree->Branch("bweight20CSVTdw",&bweight20CSVTdw, "bweight20CSVTdw/d");
    tree->Branch("bweight20CSVLuplight",&bweight20CSVLuplight, "bweight20CSVLuplight/d");
    tree->Branch("bweight20CSVMuplight",&bweight20CSVMuplight, "bweight20CSVMuplight/d");
    tree->Branch("bweight20CSVTuplight",&bweight20CSVTuplight, "bweight20CSVTuplight/d");
    tree->Branch("bweight20CSVLdwlight",&bweight20CSVLdwlight, "bweight20CSVLdwlight/d");
    tree->Branch("bweight20CSVMdwlight",&bweight20CSVMdwlight, "bweight20CSVMdwlight/d");
    tree->Branch("bweight20CSVTdwlight",&bweight20CSVTdwlight, "bweight20CSVTdwlight/d");
*/
    tree->Branch("ZMass",&ZMass,"ZMass/d");
    tree->Branch("genZMass",&genZMass,"ZMass/d");
    tree->Branch("ZtauDecay",&ZtauDecay,"ZtauDecay/i");
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

    //tree->Branch("pfMet","std::vector<vallot::METCandidate>", &pfMet);
    tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);

    tree->Branch("ttbar","std::vector<vallot::TTbarMass>", &ttbar);
    tree->Branch("ttbarGen","std::vector<vallot::TTbarCandidate>", &ttbarGen);
    tree->Branch("kinttbarM",&kinttbarM,"kinttbarM/d");
    tree->Branch("kinttbarMCSVM",&kinttbarMCSVM,"kinttbarMCSVM/d");
    tree->Branch("kinttbarMCSVT",&kinttbarMCSVT,"kinttbarMCSVT/d");

    tree->Branch("nJet30",&nJet30,"nJet30/i");
    tree->Branch("nGenJet20",&nGenJet20,"nGenJet20/i");
    tree->Branch("nGenbJet20",&nGenbJet20,"nGenbJet20/i");
    //tree->Branch("nJet20",&nJet20,"nJet20/i");

    tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
    tree->Branch("jetspt30flavor","std::vector<int>", &jetspt30flavor);
    tree->Branch("jetspt30fromtop","std::vector<int>", &jetspt30fromtop);
    tree->Branch("jetspt30bDiscriminator","std::vector<double>", &jetspt30bDiscriminator);
    tree->Branch("jetspt30bDiscriminatorSSV","std::vector<double>", &jetspt30bDiscriminatorSSV);

    tree->Branch("bCSVL_ext","std::vector<int>", &bCSVL_ext);
    tree->Branch("bCSVM_ext","std::vector<int>", &bCSVM_ext);
    tree->Branch("bCSVT_ext","std::vector<int>", &bCSVT_ext);

    //tree->Branch("jetspt20","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt20);
    //tree->Branch("jetspt20flavor","std::vector<int>", &jetspt20flavor);
    //tree->Branch("jetspt20bDiscriminator","std::vector<double>", &jetspt20bDiscriminator);
	
    for ( int i=0, n=bTagAlgos_.size(); i<n; ++i )
    {
      const std::string& name = bTagNames_[i];
      tree->Branch(("nbjets30_"+name).c_str(), &(nbjets30_[i]), ("nbjets30_"+name+"/i").c_str());
      //tree->Branch(("nbjets20_"+name).c_str(), &(nbjets20_[i]), ("nbjets20_"+name+"/i").c_str());
    }
  
    tree->Branch("nbjets30_CSVMT",&nbjets30_CSVMT,"nbjets30_CSVMT/i");

    tree->Branch("MET",&MET,"MET/d");
    tree->Branch("genttbarM",&genttbarM,"genttbarM/d");

  } 

  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    const bool isRealData = iEvent.isRealData();
    bool accept = true;
    std::vector<bool> cutStepBit(nCutStep_);

    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();


    edm::Handle<TtFullLeptonicEvent> fullLepEvt;
    iEvent.getByLabel("ttFullLepEvent", fullLepEvt);

    edm::Handle<double>  rho;
    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);


    //extracting Pileup information 
    edm::Handle<double>  puweight_;
    iEvent.getByLabel(puWeightLabel_, puweight_);

    edm::Handle<double>  puweightplus_;
    iEvent.getByLabel(puUpWeightLabel_, puweightplus_);

    edm::Handle<double>  puweightminus_;
    iEvent.getByLabel(puDwWeightLabel_, puweightminus_);

    edm::Handle<int>  npileup_;
    iEvent.getByLabel(puNVertexLabel_, npileup_);


    if( puweight_.isValid() ){
      puweight = *puweight_;
      puweightplus = *puweightplus_;
      puweightminus = *puweightminus_;
      npileup = *npileup_;
    }

    edm::Handle<reco::VertexCollection> recVtxs_;
    iEvent.getByLabel(vertexLabel_,recVtxs_);

    int nv = 0 ;

    for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
      if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
        nv++;
      }
    }

    nvertex = nv;

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    edm::Handle<pat::METCollection> MET_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(metLabel_,MET_);

    pat::METCollection::const_iterator mi = MET_->begin();

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    edm::Handle<reco::GenJetCollection> genJets_;
    iEvent.getByLabel(genJetsLabel_,genJets_);

    edm::Handle<vector<vallot::ZCandidate> > ZCand;
    iEvent.getByLabel(dileptonLabel_, ZCand);

    int mode = 0;

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        T1 it1 = muons1_->at(i);
        T2 it2 = muons2_->at(j);

        mode = 0;
        if ( it1.isMuon() ) mode |= 1;
        if ( it2.isMuon() ) mode |= 2;

        break;
      }
      break;
    }

    if( ZCand->size() > 0){
      ZMass = ZCand->at(0).mass();
      PairSign =  ZCand->at(0).sign();
      relIso1 =  ZCand->at(0).leg1().relIso03();
      relIso2 = ZCand->at(0).leg2().relIso03();
      pt1 = ZCand->at(0).leg1().pt();
      pt2 = ZCand->at(0).leg2().pt();
      eta1 = ZCand->at(0).leg1().eta();
      eta2 = ZCand->at(0).leg2().eta();
      phi1 = ZCand->at(0).leg1().phi();
      phi2 = ZCand->at(0).leg2().phi();
    }

    bool iso = relIso1 < relIso1_ && relIso2 < relIso2_;
    if( iso ) isIso = 1;

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = 0;
    }

    //for ( int bTagIndex=0, nBTag=nbjets20_.size(); bTagIndex<nBTag; ++bTagIndex )
   // {
   //   nbjets20_[bTagIndex] = 0;
   // }

    std::vector<int> bidcs_CSVL;
    std::vector<int> bidcs_CSVM;
    std::vector<int> bidcs_CSVT;
    std::vector<double> bCSVM_CSV; 

    int nj30=0;
    //int nj20=0;
    for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
      corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());
      int flavor = jit->partonFlavour();
      int isfromtop = 0;
      if( jit->genParton() ){
        const reco::GenParticle & genparton = *jit->genParton();
        bool istop = isFromtop( genparton );
        if(istop) isfromtop = 1;
      }
      double bDiscriminator = jit->bDiscriminator("combinedSecondaryVertexBJetTags");
      double bDiscriminatorSSV = jit->bDiscriminator(bTagAlgos_[4]);
      //if(jit->pt() > 20){
      //  jetspt20->push_back(corrjet);
      //  jetspt20flavor->push_back(flavor);
      //  jetspt20bDiscriminator->push_back(bDiscriminator);
        
      //  for ( int bTagIndex=0, nBTagAlgo=bTagAlgos_.size(); bTagIndex<nBTagAlgo; ++bTagIndex )
      //  {
      //    const double bTagValue = jit->bDiscriminator(bTagAlgos_[bTagIndex]);
      //    if ( (bTagIsCutMin_[bTagIndex]) xor (bTagValue < bTagCutValues_[bTagIndex]) ) ++nbjets20_[bTagIndex];
      //  }
      //  nj20++;
      //}//pt > 20 loop
      if(jit->pt() > 30){
        jetspt30->push_back(corrjet);
        jetspt30flavor->push_back(flavor);
        jetspt30fromtop->push_back(isfromtop);
        jetspt30bDiscriminator->push_back(bDiscriminator);
        jetspt30bDiscriminatorSSV->push_back(bDiscriminatorSSV);
       
        for ( int bTagIndex=0, nBTagAlgo=bTagAlgos_.size(); bTagIndex<nBTagAlgo; ++bTagIndex )
        {
          const double bTagValue = jit->bDiscriminator(bTagAlgos_[bTagIndex]);
          if ( (bTagIsCutMin_[bTagIndex]) xor (bTagValue < bTagCutValues_[bTagIndex]) ) ++nbjets30_[bTagIndex];
        }
        
        if ( bDiscriminator > bTagCutValues_[1]) {
          bidcs_CSVL.push_back(nj30); //for kinematic solution
        }
        if ( bDiscriminator > bTagCutValues_[2]) {
          bidcs_CSVM.push_back(nj30); //for kinematic solution
          bCSVM_CSV.push_back(bDiscriminator);
        }
        if ( bDiscriminator > bTagCutValues_[3]) {
          bidcs_CSVT.push_back(nj30); //for kinematic solution
        }
        nj30++;  
      }//pt > 30 loop
    }

    //nJet20 = nj20;
    nJet30 = nj30;
  
    BTagWeight bTag;

    //std::vector<TLorentzVector *> jet20(nJet20);
    //std::vector<int> jet20flavor(nJet20);
    //for (unsigned int i=0; i < nJet20; i++)
    //{
    //  jet20[i] = new TLorentzVector( jetspt20->at(i).px(), jetspt20->at(i).py(), jetspt20->at(i).pz(), jetspt20->at(i).energy() );
    //  jet20flavor[i] = jetspt20flavor->at(i);
    //}

    //if( !isRealData ){
    //  bweight20CSVL = bTag.reweight( jet20, jet20flavor, nbjets20_[1], BTagWeight::CSVL, BTagWeight::NORM);
    //  bweight20CSVM = bTag.reweight( jet20, jet20flavor, nbjets20_[2], BTagWeight::CSVM, BTagWeight::NORM);
    //  bweight20CSVT = bTag.reweight( jet20, jet20flavor, nbjets20_[3], BTagWeight::CSVT, BTagWeight::NORM);

    //  bweight20CSVLup = bTag.reweight( jet20, jet20flavor, nbjets20_[1], BTagWeight::CSVL, BTagWeight::UP);
    //  bweight20CSVMup = bTag.reweight( jet20, jet20flavor, nbjets20_[2], BTagWeight::CSVM, BTagWeight::UP);
    //  bweight20CSVTup = bTag.reweight( jet20, jet20flavor, nbjets20_[3], BTagWeight::CSVT, BTagWeight::UP);

    //  bweight20CSVLdw = bTag.reweight( jet20, jet20flavor, nbjets20_[1], BTagWeight::CSVL, BTagWeight::DW);
    //  bweight20CSVMdw = bTag.reweight( jet20, jet20flavor, nbjets20_[2], BTagWeight::CSVM, BTagWeight::DW);
    //  bweight20CSVTdw = bTag.reweight( jet20, jet20flavor, nbjets20_[3], BTagWeight::CSVT, BTagWeight::DW);

    //  bweight20CSVLuplight = bTag.reweight( jet20, jet20flavor, nbjets20_[1], BTagWeight::CSVL, BTagWeight::UPLight);
    //  bweight20CSVMuplight = bTag.reweight( jet20, jet20flavor, nbjets20_[2], BTagWeight::CSVM, BTagWeight::UPLight);
    //  bweight20CSVTuplight = bTag.reweight( jet20, jet20flavor, nbjets20_[3], BTagWeight::CSVT, BTagWeight::UPLight);

    //  bweight20CSVLdwlight = bTag.reweight( jet20, jet20flavor, nbjets20_[1], BTagWeight::CSVL, BTagWeight::DWLight);
    //  bweight20CSVMdwlight = bTag.reweight( jet20, jet20flavor, nbjets20_[2], BTagWeight::CSVM, BTagWeight::DWLight);
    //  bweight20CSVTdwlight = bTag.reweight( jet20, jet20flavor, nbjets20_[3], BTagWeight::CSVT, BTagWeight::DWLight);

    //}

    //std::vector<TLorentzVector *> jet30(nJet30);
    std::vector<double> jet30pt(nJet30);
    std::vector<double> jet30eta(nJet30);
    std::vector<int> jet30flavor(nJet30);

    for (unsigned int i=0; i < nJet30; i++)
    {
      //jet30[i] = new TLorentzVector( jetspt30->at(i).px(), jetspt30->at(i).py(), jetspt30->at(i).pz(), jetspt30->at(i).energy() );
      jet30pt[i] = jetspt30->at(i).pt();
      jet30eta[i] = jetspt30->at(i).eta();
      jet30flavor[i] = jetspt30flavor->at(i);
    }
   
    if( !isRealData ){
      bweight30CSVL = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::NORM);
      bweight30CSVM = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::NORM);
      bweight30CSVT = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::NORM);

      //add adddtional erro for b : set it true
      bweight30CSVLup = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::UP);
      bweight30CSVMup = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::UP, true);
      bweight30CSVTup = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::UP, true);

      bweight30CSVLdw = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::DW);
      bweight30CSVMdw = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::DW, true);
      bweight30CSVTdw = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::DW, true);

      bweight30CSVLuplight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::UPLight);
      bweight30CSVMuplight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::UPLight);
      bweight30CSVTuplight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::UPLight);

      bweight30CSVLdwlight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::DWLight);
      bweight30CSVMdwlight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::DWLight);
      bweight30CSVTdwlight = bTag.reweight( jet30pt, jet30eta, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::DWLight);

    }

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(mi->px(),mi->py(),0,mi->pt());
    MET = mi->pt();
    met->push_back(corrmet);

    if(metStudy_){
      const vallot::METCandidate pfmet(MET, mi->sumEt(), mi->NeutralEMFraction(),mi->NeutralHadEtFraction(),mi->ChargedHadEtFraction(),mi->ChargedEMEtFraction(),mi->MuonEtFraction() );
      pfMet->push_back(pfmet);
    }

    if(jetspt30->size() >= 2 && ZMass > 12){
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep1;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep2;
      lep1.SetPxPyPzE(ZCand->at(0).leg1().px(),ZCand->at(0).leg1().py(),ZCand->at(0).leg1().pz(),ZCand->at(0).leg1().energy());
      lep2.SetPxPyPzE(ZCand->at(0).leg2().px(),ZCand->at(0).leg2().py(),ZCand->at(0).leg2().pz(),ZCand->at(0).leg2().energy());

      const vallot::TTbarMass ttbarMass(lep1, lep2, jetspt30->at(0), jetspt30->at(1), met->at(0));
      ttbar->push_back(ttbarMass);

      const string hypo = "kKinSolution";
      if( fullLepEvt.isValid()){
        if( fullLepEvt->isHypoValid(hypo) ){
          //int btagsinhypo;
          //bool foundOneTagSolution = false;
          //for(size_t i=0;i<fullLepEvt->numberOfAvailableHypos(hypo);++i){
          //  btagsinhypo = 0;
          //  for(size_t j=0; j<bidcs.size(); ++j){
          //    if(fullLepEvt->jetLeptonCombination(hypo,i)[0]==bidcs[j]) btagsinhypo++;
          //    if(fullLepEvt->jetLeptonCombination(hypo,i)[1]==bidcs[j]) btagsinhypo++;		
          //  }
          //  if(btagsinhypo==2){ // stop if hypothesis has two b-jets
          //    cmb = i;
	  //    break;
          //  }else if(btagsinhypo==1 && !foundOneTagSolution){ // if one b-tag in hypothesis store index but go on and look for solution with 2 tags
          //    cmb = i;
          //    foundOneTagSolution = true;
          //  }   
          //}

          int cmb_CSVL = findKinSolution(fullLepEvt, hypo, bidcs_CSVL, bCSVL_ext);
          int cmb_CSVM = findKinSolution(fullLepEvt, hypo, bidcs_CSVM, bCSVM_ext);
          int cmb_CSVT = findKinSolution(fullLepEvt, hypo, bidcs_CSVT, bCSVT_ext);

          const reco::Candidate* topCand_CSVL = fullLepEvt->top(hypo, cmb_CSVL);
          const reco::Candidate* topBarCand_CSVL = fullLepEvt->topBar(hypo, cmb_CSVL);
          reco::Candidate::LorentzVector kinttbarCSVL =  topCand_CSVL->p4() + topBarCand_CSVL->p4() ; 
          kinttbarM = kinttbarCSVL.mass();

          const reco::Candidate* topCand_CSVM = fullLepEvt->top(hypo, cmb_CSVM);
          const reco::Candidate* topBarCand_CSVM = fullLepEvt->topBar(hypo, cmb_CSVM);
          reco::Candidate::LorentzVector kinttbarCSVM =  topCand_CSVM->p4() + topBarCand_CSVM->p4() ;
          kinttbarMCSVM = kinttbarCSVM.mass();

          const reco::Candidate* topCand_CSVT = fullLepEvt->top(hypo, cmb_CSVT);
          const reco::Candidate* topBarCand_CSVT = fullLepEvt->topBar(hypo, cmb_CSVT);
          reco::Candidate::LorentzVector kinttbarCSVT =  topCand_CSVT->p4() + topBarCand_CSVT->p4() ;
          kinttbarMCSVT = kinttbarCSVT.mass();

        }
      }
    }

    int ntopb = (int)bidcs_CSVM.size() - (int)bCSVM_ext->size();
    int nextb = 0 ;

    for(size_t i = 0; i < bCSVM_ext->size() ; i++){
      if ( bCSVM_CSV[i] > 0.898 ) ++nextb;
    }

    nbjets30_CSVMT = ntopb + nextb;

    //gen information
    vallot::TTbarCandidate ttbarGenLevel;

    double genZmass = -999;
 
    if(genParticles_.isValid()){
      //now this loop is for Z mass only
      for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
	int genId = mcIter->pdgId();
        ZtauDecay = 0;
        if(abs(genId) == 11 || abs(genId) == 13 || abs(genId) == 15){
	  int moid = -99;
	  int gmoid = -99;
	  const reco::Candidate *mcand = mcIter->mother();
	  if( mcand != 0) {
	    moid = mcand->pdgId();
	    if( mcand->pdgId() == mcIter->pdgId() ) {
	      if( mcand->mother() != 0 ){
		const reco::Candidate *gcand = mcand->mother();
		gmoid = gcand->pdgId();
		if( gmoid == 23 ) {
		  genZmass = gcand->p4().M();
                  if( abs(genId) == 15 ) ZtauDecay = 1;
		  break;
		}
	      }
	    }

	    if( moid == 23 ) {
	      genZmass = mcand->p4().M();
              if( abs(genId) == 15 ) ZtauDecay = 1;
	      break;
	    }
	  }
	}
      }

      genZMass = genZmass;

      const reco::GenParticleCollection* myGenParticles = 0;
      myGenParticles = &(*genParticles_);
      if(genJets_.isValid()){
        const reco::GenJetCollection* myGenJets = 0;
        myGenJets = &(*genJets_);
        ttbarGenLevel.building(myGenJets, myGenParticles);
      }
      genttbarM = ttbarGenLevel.mass();
    }

    nGenJet20 = ttbarGenLevel.NJets20();
    nGenbJet20 = ttbarGenLevel.NbJets20();

    ttbarGen->push_back(ttbarGenLevel);

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    tree->Fill();

    if ( accept )
    {
      cutStepBit[0] = (ZMass > 12);
      cutStepBit[1] = (relIso1 < relIso1_ && relIso2 < relIso2_); 
      cutStepBit[2] = (PairSign < 0);
      cutStepBit[4] = (jetspt30->size() >= 2);
      if ( mode == 1 or mode == 2 )
      {
        cutStepBit[3] = true;
        cutStepBit[5] = true;
      }
      else
      {
        cutStepBit[3] = abs(ZMass - 91.2) > 15;
        cutStepBit[5] = MET > 30;
      }
      cutStepBit[6] = (nbjets30_[1] >= 1);
      
      for ( int cutStep = 0; cutStep < nCutStep_; ++cutStep )
      {
        h_[cutStep].hNEvents->Fill(0);

        bool isPassingCutStep = true;
        for ( int i=0; i<=cutStep; ++i )
        {
          if ( !cutStepBit[i] )
          {
            isPassingCutStep = false;
            break;
          }
        }
        if ( !isPassingCutStep ) continue;
        
        h_[cutStep].hNEvents->Fill(1);

        h_[cutStep].hgenttbarM->Fill(genttbarM);
        h_[cutStep].hnpileup->Fill(npileup);
        h_[cutStep].hnvertex->Fill(nvertex);
        h_[cutStep].hNLepton1->Fill(muons1_->size());
        h_[cutStep].hNLepton2->Fill(muons2_->size());
        const int nJets = jetspt30->size();
        h_[cutStep].hNJet->Fill(nJets);

        h_[cutStep].hpt1->Fill(pt1);
        h_[cutStep].hpt2->Fill(pt2);
        h_[cutStep].heta1->Fill(eta1);
        h_[cutStep].heta2->Fill(eta2);
        h_[cutStep].hrelIso1->Fill(relIso1);
        h_[cutStep].hrelIso2->Fill(relIso2);

        if ( nJets > 0 )
        {
          h_[cutStep].hjet1pt ->Fill(jetspt30->at(0).pt() );
          h_[cutStep].hjet1eta->Fill(jetspt30->at(0).eta());
          h_[cutStep].hjet1phi->Fill(jetspt30->at(0).phi());
        }
        if ( nJets > 1 )
        {
          h_[cutStep].hjet2pt ->Fill(jetspt30->at(1).pt() );
          h_[cutStep].hjet2eta->Fill(jetspt30->at(1).eta());
          h_[cutStep].hjet2phi->Fill(jetspt30->at(1).phi());

          h_[cutStep].hHT->Fill(pt1+pt2+jetspt30->at(0).pt()+jetspt30->at(1).pt());
        }
        if ( nJets > 2 )
        {
          h_[cutStep].hjet3pt ->Fill(jetspt30->at(2).pt() );
          h_[cutStep].hjet3eta->Fill(jetspt30->at(2).eta());
          h_[cutStep].hjet3phi->Fill(jetspt30->at(2).phi());
        }
        if ( nJets > 3 )
        {
          h_[cutStep].hjet4pt ->Fill(jetspt30->at(3).pt() );
          h_[cutStep].hjet4eta->Fill(jetspt30->at(3).eta());
          h_[cutStep].hjet4phi->Fill(jetspt30->at(3).phi());
        }
        for ( int i=0, n=nbjets30_.size(); i<n; ++i )
        {
          h_[cutStep].hnBJets.at(i)->Fill(nbjets30_[i]);
        }

        h_[cutStep].hMET->Fill(MET);
        h_[cutStep].hMETPhi->Fill(met->at(0).phi());
        if ( !pfMet->empty() )
        {
          h_[cutStep].hSumET->Fill(pfMet->at(0).sumEt());
          h_[cutStep].hChET->Fill(pfMet->at(0).chargedHadEt());
          h_[cutStep].hNhET->Fill(pfMet->at(0).neutralHadEt());
          h_[cutStep].hPhET->Fill(pfMet->at(0).photonEt());
        }

        h_[cutStep].hZMass->Fill(ZMass);

        if ( !ttbar->empty() )
        {
          h_[cutStep].hvsumM->Fill(ttbar->at(0).M());
          h_[cutStep].hmaosM->Fill(ttbar->at(0).maosM());
          h_[cutStep].htopMass1->Fill(ttbar->at(0).leg1().M());
          h_[cutStep].htopMass2->Fill(ttbar->at(0).leg2().M());
        }
      }
    }

    return accept;

  }

  void clear(){

    Z->clear();
    lepton1->clear();
    lepton2->clear();
    pfMet->clear();
    ttbar->clear();
    ttbarGen->clear();
    met->clear();
    jetspt30->clear();
    jetspt30flavor->clear();
    jetspt30fromtop->clear();
    jetspt30bDiscriminator->clear();
    jetspt30bDiscriminatorSSV->clear();
    //jetspt20->clear();
    //jetspt20flavor->clear();
    //jetspt20bDiscriminator->clear();

    bCSVL_ext->clear();
    bCSVM_ext->clear();
    bCSVT_ext->clear();

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = -999;
    }

    //for ( int bTagIndex=0, nBTag=nbjets20_.size(); bTagIndex<nBTag; ++bTagIndex )
    //{
    //  nbjets20_[bTagIndex] = -999;
   // }

    puweight = 1.0;
    puweightplus = 1.0;
    puweightminus = 1.0;

    bweight30CSVL = 1.0;
    bweight30CSVM = 1.0;
    bweight30CSVT = 1.0;

    bweight30CSVLup = 1.0;
    bweight30CSVMup = 1.0;
    bweight30CSVTup = 1.0;

    bweight30CSVLdw = 1.0;
    bweight30CSVMdw = 1.0;
    bweight30CSVTdw = 1.0;

    bweight30CSVLuplight = 1.0;
    bweight30CSVMuplight = 1.0;
    bweight30CSVTuplight = 1.0;

    bweight30CSVLdwlight = 1.0;
    bweight30CSVMdwlight = 1.0;
    bweight30CSVTdwlight = 1.0;

    //bweight20CSVL = 1.0;
    //bweight20CSVM = 1.0;
    //bweight20CSVT = 1.0;

    //bweight20CSVLup = 1.0;
    //bweight20CSVMup = 1.0;
    //bweight20CSVTup = 1.0;

    //bweight20CSVLdw = 1.0;
    //bweight20CSVMdw = 1.0;
    //bweight20CSVTdw = 1.0;

    //bweight20CSVLuplight = 1.0;
    //bweight20CSVMuplight = 1.0;
    //bweight20CSVTuplight = 1.0;

    //bweight20CSVLdwlight = 1.0;
    //bweight20CSVMdwlight = 1.0;
    //bweight20CSVTdwlight = 1.0;

    ZMass = -999; 
    genZMass = -999; 
    ZtauDecay = 0; 
    PairSign = -999;
    relIso1 = -999;
    relIso2 = -999;
    isIso = -1;
    pt1 = -999; 
    pt2 = -999;
    eta1 = -999;
    eta2 = -999;
    phi1 = -999;
    phi2 = -999;

    kinttbarM = -999;
    kinttbarMCSVM = -999;
    kinttbarMCSVT = -999;
    genttbarM = -999;

    nJet30 = 0;
    nGenJet20 = 0;
    nGenbJet20 = 0;
    //nJet20 = 0;

    nbjets30_CSVMT = 0;

  }

  bool isFromtop( const reco::GenParticle& p){
    bool out = false;

    string pt = Form("%f", p.pt());
    string pdgid = Form("%i",p.pdgId());
    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
    while( mother != 0 ){
      string id = Form("%i", mother->pdgId());
      string mopt = Form("%f", mother->pt());
      if( abs(mother->pdgId()) == 6 ) {
        out = true;
      }
      mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
    }

    return out;
  }


  int findKinSolution( edm::Handle<TtFullLeptonicEvent>  fullLepEvt, const string hypo, std::vector<int> bidcs, std::vector<int>* extb ){

    vector<int> topbid;

    int cmb = 0;
    int btagsinhypo;
    bool foundOneTagSolution = false;
    for(size_t i=0;i<fullLepEvt->numberOfAvailableHypos(hypo);++i){
      btagsinhypo = 0;
      vector<int> tmp;
      for(size_t j=0; j<bidcs.size(); ++j){
        if(fullLepEvt->jetLeptonCombination(hypo,i)[0]==bidcs[j]) {
          btagsinhypo++;
          tmp.push_back(j);
        }
        if(fullLepEvt->jetLeptonCombination(hypo,i)[1]==bidcs[j]) {
          btagsinhypo++;
          tmp.push_back(j);
        }
      }
      if(btagsinhypo==2){ // stop if hypothesis has two b-jets
        cmb = i;
        topbid = tmp;
        break;
      }else if(btagsinhypo==1 && !foundOneTagSolution){ // if one b-tag in hypothesis store index but go on and look for solution with 2 tags
        cmb = i;
        topbid = tmp;
        foundOneTagSolution = true;
      }
    }

    for(size_t i=0; i < bidcs.size(); ++i){
      bool topid = false;
      for(size_t j=0; j < topbid.size() ; ++j){
        if( bidcs[i] == topbid[j] ){
          topid = true;
        } 
      }
      if( !topid ) extb->push_back(i);
    }

    return cmb;

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
  edm::InputTag dileptonLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;
  edm::InputTag vertexLabel_;

  edm::InputTag puWeightLabel_;
  edm::InputTag puUpWeightLabel_;
  edm::InputTag puDwWeightLabel_;
  edm::InputTag puNVertexLabel_;

  std::vector<std::string> filters_;
  bool metStudy_;
  bool useEventCounter_;
  
  // relIso
  double relIso1_;
  double relIso2_;
  std::vector<std::string> bTagAlgos_;
  std::vector<std::string> bTagNames_;
  std::vector<double> bTagCutValues_;
  std::vector<bool> bTagIsCutMin_;
  std::vector<int> nbjets30_;
  //std::vector<int> nbjets20_;

  TTree* tree;

  TH1F * tmp;

  std::vector<vallot::ZCandidate>* Z;
  std::vector<vallot::Lepton>* lepton1;
  std::vector<vallot::Lepton>* lepton2;
  std::vector<vallot::METCandidate>* pfMet;
  std::vector<vallot::TTbarMass>* ttbar;
  std::vector<vallot::TTbarCandidate>* ttbarGen;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jetspt30;
  std::vector<int>* jetspt30flavor;
  std::vector<int>* jetspt30fromtop;
  std::vector<double>* jetspt30bDiscriminator;  
  std::vector<double>* jetspt30bDiscriminatorSSV;  
  //std::vector<math::XYZTLorentzVector>* jetspt20;
  //std::vector<int>* jetspt20flavor;
  //std::vector<double>* jetspt20bDiscriminator;  

  std::vector<int>* bCSVL_ext;
  std::vector<int>* bCSVM_ext;
  std::vector<int>* bCSVT_ext;


  double MET;
  double ZMass;
  double genZMass;
  int ZtauDecay;
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

  double kinttbarM;
  double kinttbarMCSVM;
  double kinttbarMCSVT;
  double genttbarM;


  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int npileup;
  unsigned int nvertex;
  //unsigned int nJet20;
  unsigned int nJet30;
  unsigned int nGenJet20;
  unsigned int nGenbJet20;
  unsigned int nbjets30_CSVMT;

  double puweight;
  double puweightplus;
  double puweightminus;

  double bweight30CSVL;
  double bweight30CSVM;
  double bweight30CSVT;

  double bweight30CSVLup;
  double bweight30CSVMup;
  double bweight30CSVTup;

  double bweight30CSVLdw;
  double bweight30CSVMdw;
  double bweight30CSVTdw;

  double bweight30CSVLuplight;
  double bweight30CSVMuplight;
  double bweight30CSVTuplight;

  double bweight30CSVLdwlight;
  double bweight30CSVMdwlight;
  double bweight30CSVTdwlight;

  //double bweight20CSVL;
  //double bweight20CSVM;
  //double bweight20CSVT;

  //double bweight20CSVLup;
  //double bweight20CSVMup;
  //double bweight20CSVTup;

  //double bweight20CSVLdw;
  //double bweight20CSVMdw;
  //double bweight20CSVTdw;

  //double bweight20CSVLuplight;
  //double bweight20CSVMuplight;
  //double bweight20CSVTuplight;

  //double bweight20CSVLdwlight;
  //double bweight20CSVMdwlight;
  //double bweight20CSVTdwlight;

  bool applyIso_;
  bool oppPair_;

  int nCutStep_;
  std::vector<Histograms> h_;

};

