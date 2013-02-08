// -*- C++ -*-
//
// Package:    CMGTopDILAnalyzer
// Class:      CMGTopDILAnalyzer
// 
/**\class CMGTopDILAnalyzer CMGTopDILAnalyzer.cc UserCode/CMGTopDILAnalyzer/src/CMGTopDILAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: CMGTopDILAnalyzer.h,v 1.20 2013/02/07 21:28:12 tjkim Exp $
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
#include "AnalysisDataFormats/CMGTools/interface/BaseMET.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarDILEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "KoPFA/DataFormats/interface/Maos.h"
#include "KoPFA/DataFormats/interface/Jet.h"
#include "KoPFA/CMGDataFormats/interface/CMGTTbarCandidate.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include "KoPFA/TopAnalyzer/interface/BTagWeight.h"
#include "KoPFA/TopAnalyzer/interface/BTagWeight2012.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"
#include "KoPFA/TopAnalyzer/interface/Histograms.h"
#include "AnalysisDataFormats/CMGTools/interface/GenericTypes.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;
using namespace vallot;

template<class T>
struct bigger_second
: std::binary_function<T,T,bool>
{
   inline bool operator()(const T& lhs, const T& rhs)
   {
      return lhs.second > rhs.second;
   }
};
typedef std::pair<int,double> data_t;

template<typename T1, typename T2>
class CMGTopDILAnalyzer : public edm::EDFilter {
 public:
  explicit CMGTopDILAnalyzer(const edm::ParameterSet& iConfig){
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
    fullLepEvt_ = iConfig.getUntrackedParameter<edm::InputTag>("fullLepEvt");
    //fullLepEvt2_ = iConfig.getUntrackedParameter<edm::InputTag>("fullLepEvt2");
    nstep_ = iConfig.getUntrackedParameter<unsigned int>("nstep",0);
    run2012_ = iConfig.getUntrackedParameter<bool>("run2012",true);
 
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

    Z = new std::vector<vallot::ZCandidate>();
    lep1 = new std::vector<vallot::Lepton>();
    lep2 = new std::vector<vallot::Lepton>();
    pfMet = new std::vector<vallot::METCandidate>();
    ttbar = new std::vector<vallot::TTbarMass>();
    ttbarKin = new std::vector<vallot::TTbarDILEvent>();
    ttbarMaos = new std::vector<vallot::TTbarDILEvent>();
    ttbarGen = new std::vector<vallot::CMGTTbarCandidate>();
    jets = new std::vector<vallot::Jet>();
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();

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


  ~CMGTopDILAnalyzer()
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

    tree->Branch("ZMass",&ZMass,"ZMass/d");
    tree->Branch("genZMass",&genZMass,"ZMass/d");
    tree->Branch("ZtauDecay",&ZtauDecay,"ZtauDecay/i");
    tree->Branch("isIso",&isIso,"isIso/d");
    tree->Branch("PairSign",&PairSign,"PairSign/d");
    tree->Branch("lep1_relIso03",&lep1_relIso03,"lep1_relIso03/d");
    tree->Branch("lep2_relIso03",&lep2_relIso03,"lep2_relIso03/d");
    tree->Branch("lep1_relIso03db",&lep1_relIso03db,"lep1_relIso03db/d");
    tree->Branch("lep2_relIso03db",&lep2_relIso03db,"lep2_relIso03db/d");
    tree->Branch("lep1_relIso03rho",&lep1_relIso03rho,"lep1_relIso03rho/d");
    tree->Branch("lep2_relIso03rho",&lep2_relIso03rho,"lep2_relIso03rho/d");
    tree->Branch("lep1_pt",&lep1_pt,"lep1_pt/d");
    tree->Branch("lep2_pt",&lep2_pt,"lep2_pt/d");
    tree->Branch("lep1_eta",&lep1_eta,"lep1_eta/d");
    tree->Branch("lep2_eta",&lep2_eta,"lep2_eta/d");
    tree->Branch("lep1_phi",&lep1_phi,"lep1_phi/d");
    tree->Branch("lep2_phi",&lep2_phi,"lep2_phi/d");
    tree->Branch("lep1_charge",&lep1_charge,"lep1_charge/d");
    tree->Branch("lep2_charge",&lep2_charge,"lep2_charge/d");

    tree->Branch("jets_secvtxmass","std::vector<double>",&jets_secvtxmass);
    tree->Branch("jets_pt","std::vector<double>",&jets_pt);
    tree->Branch("jets_eta","std::vector<double>",&jets_eta);
    tree->Branch("jets_phi","std::vector<double>",&jets_phi);
    tree->Branch("jets_flavor","std::vector<int>",&jets_flavor);
    tree->Branch("jets_fromtop","std::vector<int>",&jets_fromtop);
    tree->Branch("jets_bDiscriminatorJP","std::vector<double>",&jets_bDiscriminatorJP);
    tree->Branch("jets_bDiscriminatorCSV","std::vector<double>",&jets_bDiscriminatorCSV);

    //tree->Branch("lep1","std::vector<vallot::Lepton>",&lep1);
    //tree->Branch("lep2","std::vector<vallot::Lepton>",&lep2);
    //tree->Branch("jets","std::vector<vallot::Jet>",&jets);
    //tree->Branch("pfMet","std::vector<vallot::METCandidate>", &pfMet);
    //tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);

    //tree->Branch("ttbar","std::vector<vallot::TTbarMass>", &ttbar);
    //tree->Branch("ttbarKin","std::vector<vallot::TTbarDILEvent>", &ttbarKin);
    //tree->Branch("ttbarMaos","std::vector<vallot::TTbarDILEvent>", &ttbarMaos);
    //tree->Branch("ttbarGen","std::vector<vallot::CMGTTbarCandidate>", &ttbarGen);

    tree->Branch("kin_nu_pt",&kin_nu_pt,"kin_nu_pt/d");
    tree->Branch("kin_nu_eta",&kin_nu_eta,"kin_nu_eta/d");
    tree->Branch("kin_nu_phi",&kin_nu_phi,"kin_nu_phi/d");
    tree->Branch("kin_nuBar_pt",&kin_nuBar_pt,"kin_nuBar_pt/d");
    tree->Branch("kin_nuBar_eta",&kin_nuBar_eta,"kin_nuBar_eta/d");
    tree->Branch("kin_nuBar_phi",&kin_nuBar_phi,"kin_nuBar_phi/d");

    tree->Branch("kin_top_pt",&kin_top_pt,"kin_top_pt/d");
    tree->Branch("kin_top_eta",&kin_top_eta,"kin_top_eta/d");
    tree->Branch("kin_top_phi",&kin_top_phi,"kin_top_phi/d");
    tree->Branch("kin_top_mass",&kin_top_mass,"kin_top_mass/d");
    tree->Branch("kin_topBar_pt",&kin_topBar_pt,"kin_topBar_pt/d");
    tree->Branch("kin_topBar_eta",&kin_topBar_eta,"kin_topBar_eta/d");
    tree->Branch("kin_topBar_phi",&kin_topBar_phi,"kin_topBar_phi/d");
    tree->Branch("kin_topBar_mass",&kin_topBar_mass,"kin_topBar_mass/d");

    tree->Branch("kin_jetid","std::vector<int>", &kin_jetid);
    tree->Branch("csvd_jetid","std::vector<int>", &csvd_jetid);

    //tree->Branch("maos_ttbar_mass",&maos_ttbar_mass,"maos_ttbar_mass/d");
    tree->Branch("kin_ttbar_mass",&kin_ttbar_mass,"kin_ttbar_mass/d");
    tree->Branch("vsumttbarM",&vsumttbarM,"vsumttbarM/d");
    tree->Branch("genttbarM",&genttbarM,"genttbarM/d");

    tree->Branch("nJet30",&nJet30,"nJet30/i");
    tree->Branch("nGenJet20",&nGenJet20,"nGenJet20/i");
    tree->Branch("nGenbJet20",&nGenbJet20,"nGenbJet20/i");
    tree->Branch("nGencJet20",&nGencJet20,"nGencJet20/i");

    tree->Branch("genLep1_pt",&genLep1_pt,"genLep1_pt/d");
    tree->Branch("genLep2_pt",&genLep2_pt,"genLep2_pt/d");
    tree->Branch("genLep1_eta",&genLep1_eta,"genLep1_eta/d");
    tree->Branch("genLep2_eta",&genLep2_eta,"genLep2_eta/d");
   
    tree->Branch("ttbarGen_dileptonic",&ttbarGen_dileptonic,"ttbarGen_dileptonic/i"); 

    for ( int i=0, n=bTagAlgos_.size(); i<n; ++i )
    {
      const std::string& name = bTagNames_[i];
      tree->Branch(("nbjets30_"+name).c_str(), &(nbjets30_[i]), ("nbjets30_"+name+"/i").c_str());
    }

    tree->Branch("MET",&MET,"MET/d");

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


    edm::Handle<vector<vallot::TTbarDILEvent> > fullLepEvt;
    iEvent.getByLabel(fullLepEvt_, fullLepEvt);

    //edm::Handle<vector<vallot::TTbarDILEvent> > fullLepEvt2;
    //iEvent.getByLabel(fullLepEvt2_, fullLepEvt2);
 
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
    edm::Handle<std::vector<cmg::BaseMET> > MET_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(metLabel_,MET_);

    std::vector<cmg::BaseMET>::const_iterator mi = MET_->begin();

    edm::Handle<std::vector<cmg::PFJet> > Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    edm::Handle<std::vector<cmg::GenJet> > genJets_;
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
      lep1_relIso03 =  ZCand->at(0).leg1().relIso03();
      lep2_relIso03 =  ZCand->at(0).leg2().relIso03();
      lep1_relIso03db =  ZCand->at(0).leg1().relIso03(1);
      lep2_relIso03db =  ZCand->at(0).leg2().relIso03(1);
      lep1_relIso03rho =  ZCand->at(0).leg1().relIso03(2);
      lep2_relIso03rho =  ZCand->at(0).leg2().relIso03(2);
      lep1_pt = ZCand->at(0).leg1().pt();
      lep2_pt = ZCand->at(0).leg2().pt();
      lep1_eta = ZCand->at(0).leg1().eta();
      lep2_eta = ZCand->at(0).leg2().eta();
      lep1_phi = ZCand->at(0).leg1().phi();
      lep2_phi = ZCand->at(0).leg2().phi();
      lep1_charge = ZCand->at(0).leg1().charge();
      lep2_charge = ZCand->at(0).leg2().charge();
      lep1->push_back( ZCand->at(0).leg1() );
      lep2->push_back( ZCand->at(0).leg2() );
    }

    bool iso = lep1_relIso03 < relIso1_ && lep2_relIso03 < relIso2_;
    if( iso ) isIso = 1;

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = 0;
    }

    std::vector<int> bidcs;
    int idx=0;

    std::map<int,double> mapJetBDiscriminator;

    for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {

      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
      corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());

      int jetfromtop = 0;

      if( !isRealData){
        for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
          int genId = mcIter->pdgId();
          const reco::GenParticle& p = *mcIter;

          if(abs(genId) != 5 ) continue;

          if(isLast(p, 5) ){
            double dRval = deltaR(jit->eta(), jit->phi(), p.eta(), p.phi());
            if( dRval < 0.5 ) {
              bool topdecay = isFromtop( p );
              if( topdecay ) jetfromtop = 1; 
              break; 
            }
          }
        }
      } 

      int flavor = jit->partonFlavour();

      double bDiscriminator = jit->bDiscriminator("combinedSecondaryVertexBJetTags");
      double bDiscriminatorJP = jit->bDiscriminator("jetProbabilityBJetTags");

      float secvtxmass = jit->secvtxMass();
      if(jit->pt() > 30){
        vallot::Jet jet( jit->p4() );
        jet.setFlavor( flavor );
        jet.setTopdecay( jetfromtop );
        jet.setbDiscriminator( bDiscriminator );
        jet.setSecVtxMass( secvtxmass );  
        jets->push_back(jet);
     
        jetspt30->push_back(corrjet);
       
        mapJetBDiscriminator[idx] = bDiscriminator;

        for ( int bTagIndex=0, nBTagAlgo=bTagAlgos_.size(); bTagIndex<nBTagAlgo; ++bTagIndex )
        {
          const double bTagValue = jit->bDiscriminator(bTagAlgos_[bTagIndex].c_str());
          if ( (bTagIsCutMin_[bTagIndex]) xor (bTagValue < bTagCutValues_[bTagIndex]) ) ++nbjets30_[bTagIndex];
        }

        if ( bDiscriminator > bTagCutValues_[2]) bidcs.push_back(idx); //for kinematic solution
        idx++;  

        jets_secvtxmass.push_back( secvtxmass );
        jets_pt.push_back(jit->p4().pt());
        jets_eta.push_back(jit->p4().eta());
        jets_phi.push_back(jit->p4().phi());
        jets_flavor.push_back(flavor);
        jets_fromtop.push_back(jetfromtop);
        jets_bDiscriminatorJP.push_back(bDiscriminatorJP);
        jets_bDiscriminatorCSV.push_back(bDiscriminator); 

      }//pt > 30 loop
    }
    std::vector< std::pair<int,double> > vecJetBDisc(mapJetBDiscriminator.begin(), mapJetBDiscriminator.end());
    std::sort(vecJetBDisc.begin(), vecJetBDisc.end(), bigger_second<data_t>());
    for(std::vector< std::pair<int,double> >::iterator it = vecJetBDisc.begin() ; it != vecJetBDisc.end(); ++it)
        csvd_jetid.push_back((*it).first);


    nJet30 = jets->size();
    std::vector<TLorentzVector *> jet30(nJet30);
    std::vector<int> jet30flavor(nJet30);

    for (unsigned int i=0; i < nJet30; i++)
    {
      jet30[i] = new TLorentzVector( jets->at(i).px(), jets->at(i).py(), jets->at(i).pz(), jets->at(i).energy() );
      jet30flavor[i] = jets->at(i).flavor();
    }
   
    if( !isRealData ){
      if( run2012_ == true ){
        BTagWeight2012 bTag;

        bweight30CSVL = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight2012::CSVL, BTagWeight2012::NORM);
        bweight30CSVM = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight2012::CSVM, BTagWeight2012::NORM);
        bweight30CSVT = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight2012::CSVT, BTagWeight2012::NORM);

        bweight30CSVLup = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight2012::CSVL, BTagWeight2012::UP);
        bweight30CSVMup = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight2012::CSVM, BTagWeight2012::UP);
        bweight30CSVTup = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight2012::CSVT, BTagWeight2012::UP);

        bweight30CSVLdw = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight2012::CSVL, BTagWeight2012::DW);
        bweight30CSVMdw = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight2012::CSVM, BTagWeight2012::DW);
        bweight30CSVTdw = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight2012::CSVT, BTagWeight2012::DW);

        bweight30CSVLuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight2012::CSVL, BTagWeight2012::UPLight);
        bweight30CSVMuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight2012::CSVM, BTagWeight2012::UPLight);
        bweight30CSVTuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight2012::CSVT, BTagWeight2012::UPLight);

        bweight30CSVLdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight2012::CSVL, BTagWeight2012::DWLight);
        bweight30CSVMdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight2012::CSVM, BTagWeight2012::DWLight);
        bweight30CSVTdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight2012::CSVT, BTagWeight2012::DWLight);
      }else{
        BTagWeight bTag;

        bweight30CSVL = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::NORM);
        bweight30CSVM = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::NORM);
        bweight30CSVT = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::NORM);

        bweight30CSVLup = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::UP);
        bweight30CSVMup = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::UP);
        bweight30CSVTup = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::UP);

        bweight30CSVLdw = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::DW);
        bweight30CSVMdw = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::DW);
        bweight30CSVTdw = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::DW);

        bweight30CSVLuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::UPLight);
        bweight30CSVMuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::UPLight);
        bweight30CSVTuplight = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::UPLight);

        bweight30CSVLdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[1], BTagWeight::CSVL, BTagWeight::DWLight);
        bweight30CSVMdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[2], BTagWeight::CSVM, BTagWeight::DWLight);
        bweight30CSVTdwlight = bTag.reweight( jet30, jet30flavor, nbjets30_[3], BTagWeight::CSVT, BTagWeight::DWLight);
      }
    }

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(mi->px(),mi->py(),0,mi->pt());
    MET = mi->pt();
    met->push_back(corrmet);

    if(jetspt30->size() >= 2 && ZMass > 12){
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep1;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep2;
      lep1.SetPxPyPzE(ZCand->at(0).leg1().px(),ZCand->at(0).leg1().py(),ZCand->at(0).leg1().pz(),ZCand->at(0).leg1().energy());
      lep2.SetPxPyPzE(ZCand->at(0).leg2().px(),ZCand->at(0).leg2().py(),ZCand->at(0).leg2().pz(),ZCand->at(0).leg2().energy());

      const vallot::TTbarMass ttbarMass(lep1, lep2, jetspt30->at(0), jetspt30->at(1), met->at(0));
      ttbar->push_back(ttbarMass);

      vsumttbarM = ttbarMass.M();

      int cmb = 0 ;
      const string hypo = "kKinSolution"; 

      if( fullLepEvt->size() > 0){
        
        int btagsinhypo;
        bool foundOneTagSolution = false;
        for(size_t i=0;i<fullLepEvt->size() ;++i){
          btagsinhypo = 0;
          for(size_t j=0; j<bidcs.size(); ++j){
            if(fullLepEvt->at(i).bid(0)==(unsigned int) bidcs[j]) btagsinhypo++;
            if(fullLepEvt->at(i).bid(1)==(unsigned int) bidcs[j]) btagsinhypo++;		
          }
          if(btagsinhypo==2){ // stop if hypothesis has two b-jets
            cmb = i;
            break;
          }else if(btagsinhypo==1 && !foundOneTagSolution){ // if one b-tag in hypothesis store index but go on and look for solution with 2 tags
            cmb = i;
            foundOneTagSolution = true;
          }   
        }
        
        //const reco::Candidate* topCand = fullLepEvt->top(hypo, cmb);
        //const reco::Candidate* topBarCand = fullLepEvt->topBar(hypo, cmb);
        //reco::Candidate::LorentzVector kinttbar =  topCand->p4() + topBarCand->p4() ; 
        //kin_ttbar_mass = kinttbar.mass();
        kin_ttbar_mass = fullLepEvt->at(cmb).M();
        unsigned int b = fullLepEvt->at(cmb).bid(0);
        unsigned int bbar = fullLepEvt->at(cmb).bid(1);
        jets->at(b).setRecoTopdecay("kinSolution");
        jets->at(bbar).setRecoTopdecay("kinSolution");
        ttbarKin->push_back( fullLepEvt->at(cmb) );
        unsigned int j0 = fullLepEvt->at(cmb).jid(0);
        unsigned int j1 = fullLepEvt->at(cmb).jid(1);
  
        kin_jetid.push_back(b);
        kin_jetid.push_back(bbar);
        kin_jetid.push_back(j0);
        kin_jetid.push_back(j1);

        kin_nu_pt = fullLepEvt->at(cmb).nu1().Pt();
        kin_nu_eta = fullLepEvt->at(cmb).nu1().Eta();
        kin_nu_phi = fullLepEvt->at(cmb).nu1().Phi();

        kin_nuBar_pt = fullLepEvt->at(cmb).nu2().Pt();
        kin_nuBar_eta = fullLepEvt->at(cmb).nu2().Eta();
        kin_nuBar_phi = fullLepEvt->at(cmb).nu2().Phi();

        kin_top_pt = fullLepEvt->at(cmb).leg1().Pt();
        kin_top_eta = fullLepEvt->at(cmb).leg1().Eta();
        kin_top_phi = fullLepEvt->at(cmb).leg1().Phi();
        kin_top_mass = fullLepEvt->at(cmb).leg1().M();

        kin_topBar_pt = fullLepEvt->at(cmb).leg2().Pt();
        kin_topBar_eta = fullLepEvt->at(cmb).leg2().Eta();
        kin_topBar_phi = fullLepEvt->at(cmb).leg2().Phi();
        kin_topBar_mass = fullLepEvt->at(cmb).leg2().M();

      }

//////////
      /*
      cmb = 0 ;

      if( fullLepEvt2->size() > 0){
        int btagsinhypo;
        bool foundOneTagSolution = false;
        for(size_t i=0;i<fullLepEvt2->size() ;++i){

          btagsinhypo = 0;
          for(size_t j=0; j<bidcs.size(); ++j){
            if(fullLepEvt2->at(i).bid(0)==(unsigned int) bidcs[j]) btagsinhypo++;
            if(fullLepEvt2->at(i).bid(1)==(unsigned int) bidcs[j]) btagsinhypo++;		
          }
          if(btagsinhypo==2){ // stop if hypothesis has two b-jets
            cmb = i;
            break;
          }else if(btagsinhypo==1 && !foundOneTagSolution){ // if one b-tag in hypothesis store index but go on and look for solution with 2 tags
            cmb = i;
            foundOneTagSolution = true;
          }   
        }
        //const reco::Candidate* topCand = fullLepEvt->top(hypo, cmb);
        //const reco::Candidate* topBarCand = fullLepEvt->topBar(hypo, cmb);
        //reco::Candidate::LorentzVector kinttbar =  topCand->p4() + topBarCand->p4() ; 
        //kin_ttbar_mass = kinttbar.mass();
        maos_ttbar_mass = fullLepEvt2->at(cmb).M();
        unsigned int b = fullLepEvt2->at(cmb).bid(0);
        unsigned int bbar = fullLepEvt2->at(cmb).bid(1);
        jets->at(b).setRecoTopdecay("maosSolution");
        jets->at(bbar).setRecoTopdecay("maosSolution");
        ttbarMaos->push_back( fullLepEvt2->at(cmb) );
        
      }
      */
    }
//////////
    //gen information
    vallot::CMGTTbarCandidate ttbarGenLevel;

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
    }

    if( genParticles_.isValid() && genJets_.isValid() ){ // && topSample_){
      const reco::GenParticleCollection* myGenParticles = 0;
      myGenParticles = &(*genParticles_);
      const std::vector<cmg::GenJet>* myGenJets = 0;
      myGenJets = &(*genJets_);

      ttbarGenLevel.building(myGenJets, myGenParticles);
      genttbarM = ttbarGenLevel.mass();
      nGenJet20 = ttbarGenLevel.NJets20();
      nGenbJet20 = ttbarGenLevel.NbJets20();
      nGencJet20 = ttbarGenLevel.NcJets20();
      genLep1_pt = ttbarGenLevel.lepton1().pt();
      genLep2_pt = ttbarGenLevel.lepton2().pt();
      genLep1_eta = ttbarGenLevel.lepton1().eta();
      genLep2_eta = ttbarGenLevel.lepton2().eta();
      ttbarGen_dileptonic = ttbarGenLevel.diLeptonic();

      ttbarGen->push_back(ttbarGenLevel);
    }

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);

    if ( accept )
    {
      cutStepBit[0] = (ZMass > 12);
      cutStepBit[1] = (isIso > 0); 
      cutStepBit[2] = (PairSign < 0);
      if ( mode == 1 or mode == 2 )
      {
        cutStepBit[3] = true;
        cutStepBit[4] = true;
      }
      else
      {
        cutStepBit[3] = abs(ZMass - 91.2) > 15;
        cutStepBit[4] = MET > 30;
      }
      cutStepBit[5] = (nJet30 >= 2);
      cutStepBit[6] = (nJet30 >= 4);
      
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

        h_[cutStep].hpt1->Fill(lep1_pt);
        h_[cutStep].hpt2->Fill(lep2_pt);
        h_[cutStep].heta1->Fill(lep1_eta);
        h_[cutStep].heta2->Fill(lep2_eta);
        h_[cutStep].hrelIso1->Fill(lep1_relIso03);
        h_[cutStep].hrelIso2->Fill(lep2_relIso03);

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

          h_[cutStep].hHT->Fill(lep1_pt+lep2_pt+jetspt30->at(0).pt()+jetspt30->at(1).pt());
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

    bool fill = true;
    for( unsigned int i = 0 ; i <= nstep_ ; i++){
      if ( !cutStepBit[i] ) {
        fill = false;
        break;
      }
    }

    if( fill ){
      tree->Fill();
    }

    return accept;

  }

  void clear(){

    Z->clear();
    lep1->clear();
    lep2->clear();
    pfMet->clear();
    ttbar->clear();
    ttbarKin->clear();
    ttbarMaos->clear();
    ttbarGen->clear();
    jets->clear();
    met->clear();
    jetspt30->clear();

    kin_jetid.clear();
    csvd_jetid.clear();

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = -999;
    }

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

    ZMass = -999; 
    genZMass = -999; 
    ZtauDecay = 0; 
    PairSign = -999;
    isIso = -1;
    lep1_relIso03 = -999;
    lep2_relIso03 = -999;
    lep1_relIso03db = -999;
    lep2_relIso03db = -999;
    lep1_relIso03rho = -999;
    lep2_relIso03rho = -999;
    lep1_pt = -999; 
    lep2_pt = -999;
    lep1_eta = -999;
    lep2_eta = -999;
    lep1_phi = -999;
    lep2_phi = -999;
    lep1_charge = 0.0;
    lep2_charge = 0.0;
 
    kin_ttbar_mass = -999;
    maos_ttbar_mass = -999;
    genttbarM = -999;
    vsumttbarM = -999;

    jets_secvtxmass.clear();
    jets_pt.clear();
    jets_eta.clear();
    jets_phi.clear();
    jets_flavor.clear();
    jets_fromtop.clear();
    jets_bDiscriminatorJP.clear();
    jets_bDiscriminatorCSV.clear();

    nJet30 = 0;
    nGenJet20 = 0;
    nGenbJet20 = 0;
    nGencJet20 = 0;

    genLep1_pt = 0;
    genLep2_pt = 0;

    genLep1_eta = 0;
    genLep2_eta = 0;

    ttbarGen_dileptonic = 0;

    kin_nu_pt = -999;
    kin_nu_eta = -999;
    kin_nu_phi = -999;

    kin_nuBar_pt = -999;
    kin_nuBar_eta = -999;
    kin_nuBar_phi = -999;

    kin_top_pt = -999;
    kin_top_eta = -999;
    kin_top_phi = -999;
    kin_top_mass = -999;

    kin_topBar_pt = -999;
    kin_topBar_eta = -999;
    kin_topBar_phi = -999;
    kin_topBar_mass = -999;

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

  bool isLast( const reco::GenParticle& p, int id ){
    bool out = true;

    unsigned int nDaughters = p.numberOfDaughters();
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daugh = p.daughter(iDaughter);
      if( abs(daugh->pdgId()) == id) {
        out = false;
        break;
      }
    }

    return out;
  }


  typedef vector<cmg::PFJet>::const_iterator JI;

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

  edm::InputTag fullLepEvt_;
  //edm::InputTag fullLepEvt2_;

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

  TTree* tree;

  TH1F * tmp;

  std::vector<vallot::ZCandidate>* Z;
  std::vector<vallot::Lepton>* lep1;
  std::vector<vallot::Lepton>* lep2;
  std::vector<vallot::METCandidate>* pfMet;
  std::vector<vallot::TTbarMass>* ttbar;
  std::vector<vallot::TTbarDILEvent>* ttbarKin;
  std::vector<vallot::TTbarDILEvent>* ttbarMaos;
  std::vector<vallot::CMGTTbarCandidate>* ttbarGen;
  std::vector<vallot::Jet>* jets;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jetspt30;

  std::vector<int> kin_jetid;
  std::vector<int> csvd_jetid;

  double MET;
  double ZMass;
  double genZMass;
  int ZtauDecay;
  double PairSign;
  double isIso;
  double lep1_relIso03;
  double lep2_relIso03;
  double lep1_relIso03db;
  double lep2_relIso03db;
  double lep1_relIso03rho;
  double lep2_relIso03rho;
  double lep1_pt;
  double lep2_pt;
  double lep1_eta;
  double lep2_eta;
  double lep1_phi;
  double lep2_phi;
  double lep1_charge;
  double lep2_charge;

  double kin_ttbar_mass;
  double maos_ttbar_mass;
  double genttbarM;
  double vsumttbarM;

  std::vector<double> jets_secvtxmass;
  std::vector<double> jets_pt;
  std::vector<double> jets_eta;
  std::vector<double> jets_phi;
  std::vector<int> jets_flavor;
  std::vector<int> jets_fromtop;
  std::vector<double> jets_bDiscriminatorJP;
  std::vector<double> jets_bDiscriminatorCSV;

  unsigned int nJet30;
  unsigned int nGenJet20;
  unsigned int nGenbJet20;
  unsigned int nGencJet20;

  double genLep1_pt;
  double genLep2_pt;

  double genLep1_eta;
  double genLep2_eta;

  int ttbarGen_dileptonic;
  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int npileup;
  unsigned int nvertex;

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

  double kin_nu_pt;
  double kin_nu_eta;
  double kin_nu_phi;

  double kin_nuBar_pt;
  double kin_nuBar_eta;
  double kin_nuBar_phi;

  double kin_top_pt;
  double kin_top_eta;
  double kin_top_phi;
  double kin_top_mass;

  double kin_topBar_pt;
  double kin_topBar_eta;
  double kin_topBar_phi;
  double kin_topBar_mass;

  bool applyIso_;
  bool oppPair_;

  unsigned int nstep_;
  bool run2012_;

  int nCutStep_;
  std::vector<Histograms> h_;

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


};

