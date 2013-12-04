// -*- C++ -*-
//
// Package:    CMGTopDILJPsiAnalyzer
// Class:      CMGTopDILJPsiAnalyzer
// 
/**\class CMGTopDILJPsiAnalyzer CMGTopDILJPsiAnalyzer.cc UserCode/CMGTopDILJPsiAnalyzer/src/CMGTopDILJPsiAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: CMGTopDILJPsiAnalyzer.h,v 1.27 2013/03/26 09:29:03 tjkim Exp $
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
#include "KoPFA/DataFormats/interface/JPsiCandidate.h"
#include "KoPFA/DataFormats/interface/LepJPsiCandidate.h"
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
#include "KoPFA/CMGDataFormats/interface/CMGTTbarJPsiCandidate.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include "KoPFA/TopAnalyzer/interface/BTagWeight.h"
#include "KoPFA/TopAnalyzer/interface/BTagWeight2012.h"
#include "KoPFA/TopAnalyzer/interface/LeptonWeight.h"
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

template<typename T1, typename T2, typename T3, typename T4>
class CMGTopDILJPsiAnalyzer : public edm::EDFilter {
 public:
  explicit CMGTopDILJPsiAnalyzer(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1");  //Z
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2");  //Z
    muonLabel3_ = iConfig.getParameter<edm::InputTag>("muonLabel3");  //JPsi
    muonLabel4_ = iConfig.getParameter<edm::InputTag>("muonLabel4");  //JPsi
    dileptonLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("dileptonLabel");
    jpsiLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("jpsiLabel");
    lepJPsiLabel1_ = iConfig.getUntrackedParameter<edm::InputTag>("lepJPsiLabel1");
    lepJPsiLabel2_ = iConfig.getUntrackedParameter<edm::InputTag>("lepJPsiLabel2");
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
//    fullLepEvt_ = iConfig.getUntrackedParameter<edm::InputTag>("fullLepEvt");
    //fullLepEvt2_ = iConfig.getUntrackedParameter<edm::InputTag>("fullLepEvt2");
    nstep_ = iConfig.getUntrackedParameter<unsigned int>("nstep",0);
    run2012_ = iConfig.getUntrackedParameter<bool>("run2012",true);
    histograms_ = iConfig.getUntrackedParameter<bool>("histograms",false);
 
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
        //inbJet_.push_back(-999);
        //dRJPsibjet_.push_back(-999);
        //dRlep3bjet_.push_back(-999);
        //dRlep4bjet_.push_back(-999);
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
    //cout << "step1" << endl;
   
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for Top quark study");
    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    Z = new std::vector<vallot::ZCandidate>();
    JPsi = new std::vector<vallot::JPsiCandidate>();
    LepJPsi1 = new std::vector<vallot::LepJPsiCandidate>();
    LepJPsi2 = new std::vector<vallot::LepJPsiCandidate>();
    lep1 = new std::vector<vallot::Lepton>();
    lep2 = new std::vector<vallot::Lepton>();
    lep3 = new std::vector<vallot::Lepton>();
    lep4 = new std::vector<vallot::Lepton>();
    pfMet = new std::vector<vallot::METCandidate>();
    //ttbar = new std::vector<vallot::TTbarMass>();
//    ttbarKin = new std::vector<vallot::TTbarDILEvent>();
//    ttbarMaos = new std::vector<vallot::TTbarDILEvent>();
    ttbarGen = new std::vector<vallot::CMGTTbarJPsiCandidate>();
    jets = new std::vector<vallot::Jet>();
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();

    nCutStep_ = 9;
    nProcess_ = 5;

    if( histograms_ ){
      for ( int k = 0; k < nProcess_; ++k){
        for ( int i = 0; i<nCutStep_; ++i )
        {
          TString path = "";
          if( k == 1 ) path = Form("TTBar/"); //jkim 
          //if( k == 1 ) path = Form("TTBB/");
          //if( k == 2 ) path = Form("TTCC/");
          //if( k == 3 ) path = Form("TTLF/");
          if( k == 2 ) path = Form("TTOther/");
          if( k == 3 ) path = Form("TTLJ/");
          if( k == 4 ) path = Form("QCD/");
          TFileDirectory dir = fs->mkdir(Form("%sStep%d", path.Data(), i));
          h_[k].push_back(Histograms(&dir));
          for ( unsigned int j = 0; j<bTagAlgos_.size(); ++j )
          {
            const char* algo = bTagAlgos_[j].c_str();
            h_[k][i].hnBJets.push_back(dir.make<TH1F>(Form("hnBJets_%s", algo), Form("%s B jets;Number of B jets;Events", algo), 5, 0, 5));
          }
        }
      }
    }
  }

  ~CMGTopDILJPsiAnalyzer()
  {

    delete Z;
    delete JPsi;
    delete LepJPsi1;
    delete LepJPsi2;
    delete lep1;
    delete lep2;
    delete lep3;
    delete lep4;
    delete pfMet;
    delete ttbarGen;
    delete jets;
    delete met;
    delete jetspt30;

  }

 private:
  virtual void beginJob() 
  {
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");
    tree->Branch("npileup",&npileup,"npileup/i");
    tree->Branch("nvertex",&nvertex,"nvertex/i");

    //tree->Branch("topweight",&topweight, "topweight/d");
    tree->Branch("puweight",&puweight, "puweight/d");
    tree->Branch("puweightplus",&puweightplus, "puweightplus/d");
    tree->Branch("puweightminus",&puweightminus, "puweightminus/d");

//    tree->Branch("bweight30CSVL",&bweight30CSVL, "bweight30CSVL/d");
/////    tree->Branch("bweight30CSVM",&bweight30CSVM, "bweight30CSVM/d");
//    tree->Branch("bweight30CSVT",&bweight30CSVT, "bweight30CSVT/d");
//    tree->Branch("bweight30CSVLup",&bweight30CSVLup, "bweight30CSVLup/d");
/////    tree->Branch("bweight30CSVMup",&bweight30CSVMup, "bweight30CSVMup/d");
//    tree->Branch("bweight30CSVTup",&bweight30CSVTup, "bweight30CSVTup/d");
//    tree->Branch("bweight30CSVLdw",&bweight30CSVLdw, "bweight30CSVLdw/d");
/////    tree->Branch("bweight30CSVMdw",&bweight30CSVMdw, "bweight30CSVMdw/d");
//    tree->Branch("bweight30CSVTdw",&bweight30CSVTdw, "bweight30CSVTdw/d");
//    tree->Branch("bweight30CSVLuplight",&bweight30CSVLuplight, "bweight30CSVLuplight/d");
/////    tree->Branch("bweight30CSVMuplight",&bweight30CSVMuplight, "bweight30CSVMuplight/d");
//    tree->Branch("bweight30CSVTuplight",&bweight30CSVTuplight, "bweight30CSVTuplight/d");
//    tree->Branch("bweight30CSVLdwlight",&bweight30CSVLdwlight, "bweight30CSVLdwlight/d");
/////    tree->Branch("bweight30CSVMdwlight",&bweight30CSVMdwlight, "bweight30CSVMdwlight/d");
//    tree->Branch("bweight30CSVTdwlight",&bweight30CSVTdwlight, "bweight30CSVTdwlight/d");

    tree->Branch("ZMass",&ZMass,"ZMass/d");
    tree->Branch("genZMass",&genZMass,"ZMass/d");
    tree->Branch("ZtauDecay",&ZtauDecay,"ZtauDecay/i");
    tree->Branch("isIso",&isIso,"isIso/d");
    tree->Branch("PairSign",&PairSign,"PairSign/d");
    tree->Branch("JPsiMass",&JPsiMass,"JPsiMass/d"); //correct me
    tree->Branch("JPsiEta",&JPsiEta,"JPsiEta/d");
    tree->Branch("JPsiPt",&JPsiPt,"JPsiPt/d");
    tree->Branch("JPsiPhi",&JPsiPhi,"JPsiPhi/d");
    //tree->Branch("JPsiTheta",&JPsiTheta,"JPsiTheta/d");
    tree->Branch("JPsiPairSign",&JPsiPairSign,"JPsiPairSign/d");
    tree->Branch("JPsiJetMinDR",&JPsiJetMinDR,"JPsiJetMinDR/d");
    tree->Branch("JPsiJetMinDPhi",&JPsiJetMinDPhi,"JPsiJetMinDPhi/d");
    tree->Branch("JPsivProb",&JPsivProb,"JPsivProb/d");
    tree->Branch("JPsidlPV",&JPsidlPV,"JPsidlPV/d");
    //tree->Branch("JPsidlErrPV",&JPsidlErrPV,"JPsidlErrPV/d");
    tree->Branch("JPsippdlPV",&JPsippdlPV,"JPsippdlPV/d");
    tree->Branch("JPsippdlErrPV",&JPsippdlErrPV,"JPsippdlErrPV/d");
    //tree->Branch("JPsippdlBS",&JPsippdlBS,"JPsippdlBS/d");
    //tree->Branch("JPsippdlErrBS",&JPsippdlErrBS,"JPsippdlErrBS/d");
    tree->Branch("JPsiMomIDTrue",&JPsiMomIDTrue,"JPsiMomIDTrue/i");
    tree->Branch("JPsiDlTrue",&JPsiDlTrue,"JPsiDlTrue/d");
    tree->Branch("JPsippdlTrue",&JPsippdlTrue,"JPsippdlTrue/d");
    tree->Branch("LepJPsiMass1",&LepJPsiMass1,"LepJPsi1Mass1/d");
    tree->Branch("LepJPsiMass2",&LepJPsiMass2,"LepJPsi2Mass2/d");
    tree->Branch("LepJPsidTheta1",&LepJPsidTheta1,"LepJPsidTheta1/d");
    tree->Branch("LepJPsidTheta2",&LepJPsidTheta2,"LepJPsidTheta2/d");
    tree->Branch("LepJPsidThetalower",&LepJPsidThetalower,"LepJPsidThetalower/d");
    tree->Branch("LepJPsidThetabigger",&LepJPsidThetabigger,"LepJPsidThetabigger/d");
    tree->Branch("LepJPsidPhi1",&LepJPsidPhi1,"LepJPsidPhi1/d");
    tree->Branch("LepJPsidPhi2",&LepJPsidPhi2,"LepJPsidPhi2/d");
    tree->Branch("LepJPsidPhilower",&LepJPsidPhilower,"LepJPsidPhilower/d");
    tree->Branch("LepJPsidPhibigger",&LepJPsidPhibigger,"LepJPsidPhibigger/d");
    tree->Branch("LepJPsidR1",&LepJPsidR1,"LepJPsidR1/d");
    tree->Branch("LepJPsidR2",&LepJPsidR2,"LepJPsidR2/d");
    tree->Branch("LepJPsidRlower",&LepJPsidRlower,"LepJPsidRlower/d");
    tree->Branch("LepJPsidRbigger",&LepJPsidRbigger,"LepJPsidRbigger/d");
    //tree->Branch("inJet",&inJet,"inJet/d");
    tree->Branch("nJPsiCand",&nJPsiCand,"nJPsiCand/i");
    tree->Branch("nLepJPsiCand1",&nLepJPsiCand1,"nLepJPsiCand1/i");
    tree->Branch("nLepJPsiCand2",&nLepJPsiCand2,"nLepJPsiCand2/i");

    tree->Branch("lep1_relIso04",&lep1_relIso04,"lep1_relIso04/d");
    tree->Branch("lep2_relIso04",&lep2_relIso04,"lep2_relIso04/d");
    /*tree->Branch("lep1_chIso03",&lep1_chIso03,"lep1_chIso03/d");
    tree->Branch("lep2_chIso03",&lep2_chIso03,"lep2_chIso03/d");
    tree->Branch("lep1_nhIso03",&lep1_nhIso03,"lep1_nhIso03/d");
    tree->Branch("lep2_nhIso03",&lep2_nhIso03,"lep2_nhIso03/d");
    tree->Branch("lep1_phIso03",&lep1_phIso03,"lep1_phIso03/d");
    tree->Branch("lep2_phIso03",&lep2_phIso03,"lep2_phIso03/d");*/
    tree->Branch("lep1_relIso03",&lep1_relIso03,"lep1_relIso03/d");
    tree->Branch("lep2_relIso03",&lep2_relIso03,"lep2_relIso03/d");
    tree->Branch("lep1_relIso03db",&lep1_relIso03db,"lep1_relIso03db/d");
    tree->Branch("lep2_relIso03db",&lep2_relIso03db,"lep2_relIso03db/d");
    tree->Branch("lep1_relIso03rho",&lep1_relIso03rho,"lep1_relIso03rho/d");
    tree->Branch("lep2_relIso03rho",&lep2_relIso03rho,"lep2_relIso03rho/d");
    tree->Branch("lep1_pt",&lep1_pt,"lep1_pt/d");
    tree->Branch("lep2_pt",&lep2_pt,"lep2_pt/d");
    tree->Branch("lep3_pt",&lep3_pt,"lep3_pt/d");
    tree->Branch("lep4_pt",&lep4_pt,"lep4_pt/d");
    tree->Branch("lep1_eta",&lep1_eta,"lep1_eta/d");
    tree->Branch("lep2_eta",&lep2_eta,"lep2_eta/d");
    tree->Branch("lep3_eta",&lep3_eta,"lep3_eta/d");
    tree->Branch("lep4_eta",&lep4_eta,"lep4_eta/d");
    tree->Branch("lep1_phi",&lep1_phi,"lep1_phi/d");
    tree->Branch("lep2_phi",&lep2_phi,"lep2_phi/d");
    tree->Branch("lep3_phi",&lep3_phi,"lep3_phi/d");
    tree->Branch("lep4_phi",&lep4_phi,"lep4_phi/d");
    tree->Branch("lep1_theta",&lep1_theta,"lep1_theta/d");
    tree->Branch("lep2_theta",&lep2_theta,"lep2_theta/d");
    tree->Branch("lep1_charge",&lep1_charge,"lep1_charge/d");
    tree->Branch("lep2_charge",&lep2_charge,"lep2_charge/d");
    tree->Branch("lep3_charge",&lep3_charge,"lep3_charge/d");
    tree->Branch("lep4_charge",&lep4_charge,"lep4_charge/d");
    tree->Branch("lepweight",&lepweight,"lepweight/d");

    //tree->Branch("jets_secvtxmass","std::vector<double>",&jets_secvtxmass);
    tree->Branch("jets_Lxy","std::vector<double>",&jets_Lxy);
    tree->Branch("jets_LxyErr","std::vector<double>",&jets_LxyErr);
    tree->Branch("jets_pt","std::vector<double>",&jets_pt);
    tree->Branch("jets_eta","std::vector<double>",&jets_eta);
    tree->Branch("jets_phi","std::vector<double>",&jets_phi);
    tree->Branch("jets_flavor","std::vector<int>",&jets_flavor);
    tree->Branch("jets_fromtop","std::vector<int>",&jets_fromtop);
    //tree->Branch("jets_bDiscriminatorJP","std::vector<double>",&jets_bDiscriminatorJP);
    //tree->Branch("jets_bDiscriminatorCSV","std::vector<double>",&jets_bDiscriminatorCSV);
    //tree->Branch("jets_bDisCSVweight","std::vector<double>",&jets_bDisCSVweight);

    //tree->Branch("lep1","std::vector<vallot::Lepton>",&lep1);
    //tree->Branch("lep2","std::vector<vallot::Lepton>",&lep2);
    //tree->Branch("lep2","std::vector<vallot::Lepton>",&lep3);
    //tree->Branch("lep2","std::vector<vallot::Lepton>",&lep4);
    //tree->Branch("jets","std::vector<vallot::Jet>",&jets);
    //tree->Branch("pfMet","std::vector<vallot::METCandidate>", &pfMet);
    //tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);

    //tree->Branch("ttbar","std::vector<vallot::TTbarMass>", &ttbar);
    //tree->Branch("ttbarKin","std::vector<vallot::TTbarDILEvent>", &ttbarKin);
    //tree->Branch("ttbarMaos","std::vector<vallot::TTbarDILEvent>", &ttbarMaos);
    //tree->Branch("ttbarGen","std::vector<vallot::CMGTTbarJPsiCandidate>", &ttbarGen);

/*    tree->Branch("kin_nu_pt",&kin_nu_pt,"kin_nu_pt/d");
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
*/

    //tree->Branch("csvd_jetid","std::vector<int>", &csvd_jetid);

    //tree->Branch("maos_ttbar_mass",&maos_ttbar_mass,"maos_ttbar_mass/d");
    //tree->Branch("kin_ttbar_mass",&kin_ttbar_mass,"kin_ttbar_mass/d");
    //tree->Branch("kin_ttbar_dphi",&kin_ttbar_dphi,"kin_ttbar_dphi/d");
    //tree->Branch("vsumttbarM",&vsumttbarM,"vsumttbarM/d");
    //tree->Branch("genttbarM",&genttbarM,"genttbarM/d");

    tree->Branch("nJet30",&nJet30,"nJet30/i");
    tree->Branch("nJet30Up",&nJet30Up,"nJet30Up/i");
    tree->Branch("nJet30Dw",&nJet30Dw,"nJet30Dw/i");
    tree->Branch("nGenJet20",&nGenJet20,"nGenJet20/i");
    tree->Branch("nGenbJet20",&nGenbJet20,"nGenbJet20/i");

    tree->Branch("genLep1_pt",&genLep1_pt,"genLep1_pt/d");
    tree->Branch("genLep2_pt",&genLep2_pt,"genLep2_pt/d");
    tree->Branch("genbquark1_pt",&genbquark1_pt,"genbquark1_pt/d");
    tree->Branch("genbquark2_pt",&genbquark2_pt,"genbquark2_pt/d");
    tree->Branch("gentquark1_pt",&gentquark1_pt,"gentquark1_pt/d");
    tree->Branch("gentquark2_pt",&gentquark2_pt,"gentquark2_pt/d");
    /*tree->Branch("genJPsi1_pt",&genJPsi1_pt,"genJPsi1_pt/d");
    tree->Branch("genJPsi2_pt",&genJPsi2_pt,"genJPsi2_pt/d");
    tree->Branch("genJPsiB1_pt",&genJPsiB1_pt,"genJPsiB1_pt/d");
    tree->Branch("genJPsiB2_pt",&genJPsiB2_pt,"genJPsiB2_pt/d");
    tree->Branch("genJPsiLep1P_pt",&genJPsiLep1P_pt,"genJPsiLep1P_pt/d");
    tree->Branch("genJPsiLep1M_pt",&genJPsiLep1M_pt,"genJPsiLep1M_pt/d");
    tree->Branch("genJPsiLep2P_pt",&genJPsiLep2P_pt,"genJPsiLep2P_pt/d");
    tree->Branch("genJPsiLep2M_pt",&genJPsiLep2M_pt,"genJPsiLep2M_pt/d");*/
    tree->Branch("genpriJPsi_pt",&genpriJPsi_pt,"genpriJPsi_pt/d");
    tree->Branch("gensecJPsi_pt",&gensecJPsi_pt,"gensecJPsi_pt/d");
    tree->Branch("gentbJPsi_pt",&gentbJPsi_pt,"gentbJPsi_pt/d");
    tree->Branch("gentbJPsilp_pt",&gentbJPsilp_pt,"gentbJPsilp_pt/d");
    tree->Branch("gentbJPsilm_pt",&gentbJPsilm_pt,"gentbJPsilm_pt/d");
    tree->Branch("gentbbJPsi_pt",&gentbbJPsi_pt,"gentbbJPsi_pt/d");
    tree->Branch("gentbbJPsilp_pt",&gentbbJPsilp_pt,"gentbbJPsilp_pt/d");
    tree->Branch("gentbbJPsilm_pt",&gentbbJPsilm_pt,"gentbbJPsilm_pt/d");

/////    tree->Branch("genbquark1_p",&genbquark1_p,"genbquark1_p/d");
/////    tree->Branch("genbquark2_p",&genbquark2_p,"genbquark2_p/d");
    /*tree->Branch("genJPsi1_p",&genJPsi1_p,"genJPsi1_p/d");
    tree->Branch("genJPsi2_p",&genJPsi2_p,"genJPsi2_p/d");
    tree->Branch("genJPsiB1_p",&genJPsiB1_p,"genJPsiB1_p/d");
    tree->Branch("genJPsiB2_p",&genJPsiB2_p,"genJPsiB2_p/d");*/

    tree->Branch("genLep1_eta",&genLep1_eta,"genLep1_eta/d");
    tree->Branch("genLep2_eta",&genLep2_eta,"genLep2_eta/d");
    tree->Branch("genbquark1_eta",&genbquark1_eta,"genbquark1_eta/d");
    tree->Branch("genbquark2_eta",&genbquark2_eta,"genbquark2_eta/d");
    tree->Branch("gentquark1_eta",&gentquark1_eta,"gentquark1_eta/d");
    tree->Branch("gentquark2_eta",&gentquark2_eta,"gentquark2_eta/d");
/*    tree->Branch("genJPsi1_eta",&genJPsi1_eta,"genJPsi1_eta/d");
    tree->Branch("genJPsi2_eta",&genJPsi2_eta,"genJPsi2_eta/d");
    tree->Branch("genJPsiB1_eta",&genJPsiB1_eta,"genJPsiB1_eta/d");
    tree->Branch("genJPsiB2_eta",&genJPsiB2_eta,"genJPsiB2_eta/d");
    tree->Branch("genJPsiLep1P_eta",&genJPsiLep1P_eta,"genJPsiLep1P_eta/d");
    tree->Branch("genJPsiLep1M_eta",&genJPsiLep1M_eta,"genJPsiLep1M_eta/d");
    tree->Branch("genJPsiLep2P_eta",&genJPsiLep2P_eta,"genJPsiLep2P_eta/d");
    tree->Branch("genJPsiLep2M_eta",&genJPsiLep2M_eta,"genJPsiLep2M_eta/d");*/
  tree->Branch("genpriJPsi_eta",&genpriJPsi_eta,"genpriJPsi_eta/d");
  tree->Branch("gensecJPsi_eta",&gensecJPsi_eta,"gensecJPsi_eta/d");
  tree->Branch("gentbJPsi_eta",&gentbJPsi_eta,"gentbJPsi_eta/d");
  tree->Branch("gentbJPsilp_eta",&gentbJPsilp_eta,"gentbJPsilp_eta/d");
  tree->Branch("gentbJPsilm_eta",&gentbJPsilm_eta,"gentbJPsilm_eta/d");
  tree->Branch("gentbbJPsi_eta",&gentbbJPsi_eta,"gentbbJPsi_eta/d");
  tree->Branch("gentbbJPsilp_eta",&gentbbJPsilp_eta,"gentbbJPsilp_eta/d");
  tree->Branch("gentbbJPsilm_eta",&gentbbJPsilm_eta,"gentbbJPsilm_eta/d");

    tree->Branch("genLep1_phi",&genLep1_phi,"genLep1_phi/d");
    tree->Branch("genLep2_phi",&genLep2_phi,"genLep2_phi/d");
    tree->Branch("gentquark1_phi",&gentquark1_phi,"gentquark1_phi/d");
    tree->Branch("gentquark2_phi",&gentquark2_phi,"gentquark2_phi/d");
    tree->Branch("genbquark1_phi",&genbquark1_phi,"genbquark1_phi/d");
    tree->Branch("genbquark2_phi",&genbquark2_phi,"genbquark2_phi/d");
/*    tree->Branch("genJPsi1_phi",&genJPsi1_phi,"genJPsi1_phi/d");
    tree->Branch("genJPsi2_phi",&genJPsi2_phi,"genJPsi2_phi/d");
    tree->Branch("genJPsiB1_phi",&genJPsiB1_phi,"genJPsiB1_phi/d");
    tree->Branch("genJPsiB2_phi",&genJPsiB2_phi,"genJPsiB2_phi/d");
    tree->Branch("genJPsiLep1P_phi",&genJPsiLep1P_phi,"genJPsiLep1P_phi/d");
    tree->Branch("genJPsiLep1M_phi",&genJPsiLep1M_phi,"genJPsiLep1M_phi/d");
    tree->Branch("genJPsiLep2P_phi",&genJPsiLep2P_phi,"genJPsiLep2P_phi/d");
    tree->Branch("genJPsiLep2M_phi",&genJPsiLep2M_phi,"genJPsiLep2M_phi/d");*/
  tree->Branch("gentbJPsi_phi",&gentbJPsi_phi,"gentbJPsi_phi/d");
  tree->Branch("gentbJPsilp_phi",&gentbJPsilp_phi,"gentbJPsilp_phi/d");
  tree->Branch("gentbJPsilm_phi",&gentbJPsilm_phi,"gentbJPsilm_phi/d");
  tree->Branch("gentbbJPsi_phi",&gentbbJPsi_phi,"gentbbJPsi_phi/d");
  tree->Branch("gentbbJPsilp_phi",&gentbbJPsilp_phi,"gentbbJPsilp_phi/d");
  tree->Branch("gentbbJPsilm_phi",&gentbbJPsilm_phi,"gentbbJPsilm_phi/d");
  
    //tree->Branch("genbquark1_theta",&genbquark1_theta,"genbquark1_theta/d");
    //tree->Branch("genbquark2_theta",&genbquark2_theta,"genbquark2_theta/d");

  tree->Branch("genpriJPsi_3Dl",&genpriJPsi_3Dl,"genpriJPsi_3Dl/d");
  tree->Branch("gensecJPsi_3Dl",&gensecJPsi_3Dl,"gensecJPsi_3Dl/d");
  tree->Branch("gentbJPsi_3Dl",&gentbJPsi_3Dl,"gentbJPsi_3Dl/d");
  tree->Branch("gentbbJPsi_3Dl",&gentbbJPsi_3Dl,"gentbbJPsi_3Dl/d");
  tree->Branch("genpriJPsi_ppdl",&genpriJPsi_ppdl,"genpriJPsi_ppdl/d");
  tree->Branch("gensecJPsi_ppdl",&gensecJPsi_ppdl,"gensecJPsi_ppdl/d");
  tree->Branch("gentbJPsi_ppdl",&gentbJPsi_ppdl,"gentbJPsi_ppdl/d");
  tree->Branch("gentbbJPsi_ppdl",&gentbbJPsi_ppdl,"gentbbJPsi_ppdl/d");
  tree->Branch("gentbJPsi_dtheta",&gentbJPsi_dtheta,"gentbJPsi_dtheta/d");
  tree->Branch("gentbbJPsi_dtheta",&gentbbJPsi_dtheta,"gentbbJPsi_dtheta/d");

  tree->Branch("genpriJPsi_mass",&genpriJPsi_mass,"genpriJPsi_mass/d");
  tree->Branch("gensecJPsi_mass",&gensecJPsi_mass,"gensecJPsi_mass/d");
    tree->Branch("gentbJPsi_mass",&gentbJPsi_mass,"gentbJPsi_mass/d"); 
    tree->Branch("gentbbJPsi_mass",&gentbbJPsi_mass,"gentbbJPsi_mass/d"); 
/*    tree->Branch("genJPsiB1_theta",&genJPsiB1_theta,"genJPsiB1_theta/d");
    tree->Branch("genJPsiB2_theta",&genJPsiB2_theta,"genJPsiB2_theta/d");
    tree->Branch("genJPsi1_theta",&genJPsi1_theta,"genJPsi1_theta/d");
    tree->Branch("genJPsi2_theta",&genJPsi2_theta,"genJPsi2_theta/d");

    tree->Branch("genJPsi1_mass",&genJPsi1_mass,"genJPsi1_mass/d"); 
    tree->Branch("genJPsi2_mass",&genJPsi2_mass,"genJPsi2_mass/d"); */

  tree->Branch("genNpJPsi",&genNpJPsi,"genNpJPsi/d");
  tree->Branch("genNbJPsi",&genNbJPsi,"genNbJPsi/d");
  tree->Branch("genNbQuarksTop",&genNbQuarksTop,"genNbQuarksTop/d");
  tree->Branch("genNbQuarks",&genNbQuarks,"genNbQuarks/d");
  tree->Branch("genNbJets",&genNbJets,"genNbJets/d");
  //tree->Branch("genNbJetJPsi",&genNbJetJPsi,"genNbJetJPsi/d");
  tree->Branch("genNtbJPsi",&genNtbJPsi,"genNtbJPsi/d");
  tree->Branch("genNtbJPsilp",&genNtbJPsilp,"genNtbJPsilp/d");
  tree->Branch("genNtbJPsilm",&genNtbJPsilm,"genNtbJPsilm/d");
  tree->Branch("genNtbbJPsi",&genNtbbJPsi,"genNtbbJPsi/d");
  tree->Branch("genNtbbJPsilp",&genNtbbJPsilp,"genNtbbJPsilp/d");
  tree->Branch("genNtbbJPsilm",&genNtbbJPsilm,"genNtbbJPsilm/d");

    tree->Branch("ttbarGen_dileptonic",&ttbarGen_dileptonic,"ttbarGen_dileptonic/i"); 
    tree->Branch("visible",&visible,"visible/i"); 
    //tree->Branch("ttbb",&ttbb,"ttbb/i"); 
    //tree->Branch("ttcc",&ttcc,"ttcc/i"); 
    //tree->Branch("ttLF",&ttLF,"ttLF/i"); 
  
    for ( int i=0, n=bTagAlgos_.size(); i<n; ++i )
    {
      const std::string& name = bTagNames_[i];
      tree->Branch(("nbjets30_"+name).c_str(), &(nbjets30_[i]), ("nbjets30_"+name+"/i").c_str());
      //tree->Branch(("inbJet_"+name).c_str(), &(inbJet_[i]), ("inbJet_"+name+"/i").c_str());
      //tree->Branch(("dRJPsibjet_"+name).c_str(), &(dRJPsibjet_[i]), ("dRJPsibjet_"+name+"/i").c_str());
      //tree->Branch(("dRlep3bjet_"+name).c_str(), &(dRlep3bjet_[i]), ("dRlep3bjet_"+name+"/i").c_str());
      //tree->Branch(("dRlep4bjet_"+name).c_str(), &(dRlep4bjet_[i]), ("dRlep4bjet_"+name+"/i").c_str());
    }

    tree->Branch("MET",&MET,"MET/d");
    tree->Branch("metphi",&metphi,"metphi/d");

    tree->Branch("METUp",&METUp,"METUp/d");
    tree->Branch("METDw",&METDw,"METDw/d");
    //cout << "step2" << endl;
  } 

  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    const bool isRealData = iEvent.isRealData();
    bool accept = true;
    std::vector<bool> cutStepBit(nCutStep_);
    std::vector<bool> processBit(nProcess_);

    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();


    //edm::Handle<vector<vallot::TTbarDILEvent> > fullLepEvt;
    //iEvent.getByLabel(fullLepEvt_, fullLepEvt);

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

    //cout << "step3" << endl;

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    edm::Handle<std::vector<T3> > muons3_;
    edm::Handle<std::vector<T4> > muons4_;
    edm::Handle<std::vector<cmg::BaseMET> > MET_;
    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(muonLabel3_,muons3_);
    iEvent.getByLabel(muonLabel4_,muons4_);
    iEvent.getByLabel(metLabel_,MET_);

    std::vector<cmg::BaseMET>::const_iterator mi = MET_->begin();
    MET = mi->pt();
    metphi = mi->phi();
    double metup_x = MET_->begin()->px();
    double metup_y = MET_->begin()->py();
    double metdw_x = MET_->begin()->px();
    double metdw_y = MET_->begin()->py();

    edm::Handle<std::vector<cmg::PFJet> > Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    edm::Handle<std::vector<cmg::GenJet> > genJets_;
    iEvent.getByLabel(genJetsLabel_,genJets_);

    edm::Handle<vector<vallot::ZCandidate> > ZCand;
    iEvent.getByLabel(dileptonLabel_, ZCand);

    edm::Handle<vector<vallot::JPsiCandidate> > JPsiCand;
    iEvent.getByLabel(jpsiLabel_, JPsiCand);

    edm::Handle<vector<vallot::LepJPsiCandidate> > LepJPsiCand1;
    iEvent.getByLabel(lepJPsiLabel1_, LepJPsiCand1);

    edm::Handle<vector<vallot::LepJPsiCandidate> > LepJPsiCand2;
    iEvent.getByLabel(lepJPsiLabel2_, LepJPsiCand2);

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
      LeptonWeight LepWeight;
      ZMass = ZCand->at(0).mass();
      PairSign =  ZCand->at(0).sign();
      lep1_relIso04 =  ZCand->at(0).leg1().relIso04();
      lep2_relIso04 =  ZCand->at(0).leg2().relIso04();
      lep1_relIso03 =  ZCand->at(0).leg1().relIso03();
      lep2_relIso03 =  ZCand->at(0).leg2().relIso03();
      /*lep1_chIso03 =  ZCand->at(0).leg1().chIso03();
      lep2_chIso03 =  ZCand->at(0).leg2().chIso03(); 
      lep1_nhIso03 =  ZCand->at(0).leg1().nhIso03();
      lep2_nhIso03 =  ZCand->at(0).leg2().nhIso03();  
      lep1_phIso03 =  ZCand->at(0).leg1().phIso03();
      lep2_phIso03 =  ZCand->at(0).leg2().phIso03();*/  
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
      lep1_theta = ZCand->at(0).leg1().theta();
      lep2_theta = ZCand->at(0).leg2().theta();
      lep1_charge = ZCand->at(0).leg1().charge();
      lep2_charge = ZCand->at(0).leg2().charge();
      lep1->push_back( ZCand->at(0).leg1() );
      lep2->push_back( ZCand->at(0).leg2() );

      double sf1 = 1.0;
      double sf2 = 1.0;
      if( mode == 0 ) {
        sf1 =  LepWeight.SF(lep1_pt, lep1_eta, LeptonWeight::Electron);
        sf2 =  LepWeight.SF(lep2_pt, lep2_eta, LeptonWeight::Electron);
      }else if( mode == 3){
        sf1 =  LepWeight.SF(lep1_pt, lep1_eta, LeptonWeight::Muon);
        sf2 =  LepWeight.SF(lep2_pt, lep2_eta, LeptonWeight::Muon);
      }else{
        sf1 =  LepWeight.SF(lep1_pt, lep1_eta, LeptonWeight::Muon);
        sf2 =  LepWeight.SF(lep2_pt, lep2_eta, LeptonWeight::Electron);
      }
 
      lepweight = sf1 * sf2;
    }

    //cout << "step4" << endl;

    nJPsiCand =  JPsiCand->size();
    nLepJPsiCand1 =  LepJPsiCand1->size();
    nLepJPsiCand2 =  LepJPsiCand2->size();

    if( nJPsiCand > 0 && nLepJPsiCand1 > 0 && nLepJPsiCand2 > 0){
      JPsiMass = JPsiCand->at(0).mass();
      JPsiEta = JPsiCand->at(0).eta();
      JPsiPt = JPsiCand->at(0).pt();
      JPsiPhi = JPsiCand->at(0).phi();
      //JPsiTheta = JPsiCand->at(0).theta();
      JPsivProb = JPsiCand->at(0).vProb();
      JPsidlPV = JPsiCand->at(0).dlPV();
      //JPsidlErrPV = JPsiCand->at(0).dlErrPV();
      JPsippdlPV = JPsiCand->at(0).ppdlPV();
      JPsippdlErrPV = JPsiCand->at(0).ppdlErrPV();
      //JPsippdlBS = JPsiCand->at(0).ppdlBS();
      //JPsippdlErrBS = JPsiCand->at(0).ppdlErrBS();
      JPsiMomIDTrue = JPsiCand->at(0).genRefJpmomId();
      JPsiDlTrue = JPsiCand->at(0).DlTrue();
      JPsippdlTrue = JPsiCand->at(0).ppdlTrue();
      LepJPsiMass1 = LepJPsiCand1->at(0).mass();
      LepJPsiMass2 = LepJPsiCand2->at(0).mass();
      LepJPsidTheta1 = LepJPsiCand1->at(0).dtheta();
      LepJPsidTheta2 = LepJPsiCand2->at(0).dtheta();
      /*if(LepJPsidTheta1<LepJPsidTheta2) 
      {  LepJPsidThetalower = LepJPsidTheta1;
         LepJPsidThetabigger =LepJPsidTheta2;
      }else if(LepJPsidTheta1>LepJPsidTheta2){
         LepJPsidThetalower = LepJPsidTheta2;
         LepJPsidThetabigger =LepJPsidTheta1;
      }else{ LepJPsidThetalower = LepJPsidTheta1; }*/
      LepJPsidThetalower = LepJPsidTheta1<=LepJPsidTheta2? LepJPsidTheta1:LepJPsidTheta2;
      LepJPsidThetabigger = LepJPsidTheta1>LepJPsidTheta2? LepJPsidTheta1:LepJPsidTheta2;
      LepJPsidPhi1 = fabs(LepJPsiCand1->at(0).deltaPhi());
      LepJPsidPhi2 = fabs(LepJPsiCand2->at(0).deltaPhi());
      /*if(LepJPsidPhi1<LepJPsidPhi2)
      {  LepJPsidPhilower = LepJPsidPhi1;
         LepJPsidPhibigger = LepJPsidPhi2;
      }else if(LepJPsidPhi1>LepJPsidPhi2){
         LepJPsidPhilower = LepJPsidPhi2;
         LepJPsidPhibigger = LepJPsidPhi1;
      }else{  LepJPsidPhilower = LepJPsidPhi1; } */
         LepJPsidPhilower = LepJPsidPhi1<=LepJPsidPhi2? LepJPsidPhi1:LepJPsidPhi2;
         LepJPsidPhibigger = LepJPsidPhi1>LepJPsidPhi2? LepJPsidPhi1:LepJPsidPhi2;
      LepJPsidR1 = LepJPsiCand1->at(0).deltaR();
      LepJPsidR2 = LepJPsiCand2->at(0).deltaR();
      /*if(LepJPsidR1<LepJPsidR2){
         LepJPsidRlower = LepJPsidR1;
         LepJPsidRbigger = LepJPsidR2;
      }else if(LepJPsidR1>LepJPsidR2){
         LepJPsidRlower = LepJPsidR2;
         LepJPsidRbigger = LepJPsidR1;
      }else { LepJPsidRlower = LepJPsidR1; }*/
      LepJPsidRlower = LepJPsidR1<=LepJPsidR2? LepJPsidR1:LepJPsidR2;
      LepJPsidRbigger = LepJPsidR1>LepJPsidR2? LepJPsidR1:LepJPsidR2;
      JPsiPairSign =  JPsiCand->at(0).sign();
      lep3_pt = JPsiCand->at(0).leg1().pt();
      lep4_pt = JPsiCand->at(0).leg2().pt();
      lep3_eta = JPsiCand->at(0).leg1().eta();
      lep4_eta = JPsiCand->at(0).leg2().eta();
      lep3_phi = JPsiCand->at(0).leg1().phi();
      lep4_phi = JPsiCand->at(0).leg2().phi();
      lep3_charge = JPsiCand->at(0).leg1().charge();
      lep4_charge = JPsiCand->at(0).leg2().charge();
      lep3->push_back( JPsiCand->at(0).leg1() );
      lep4->push_back( JPsiCand->at(0).leg2() );
    }

    bool iso = lep1_relIso03 < relIso1_ && lep2_relIso03 < relIso2_;
    if( iso ) isIso = 1;

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = 0;
      //inbJet_[bTagIndex] = 0;
      //dRJPsibjet_[bTagIndex] = -999;
      //dRlep3bjet_[bTagIndex] = -999;
      //dRlep4bjet_[bTagIndex] = -999;
      
    }

    //cout << "step5" << endl;

    std::vector<int> bidcs;
    int idx=0;

    std::map<int,double> mapJetBDiscriminator;

    double njet = 0;
    double njetUp = 0;
    double njetDw = 0;
    double metup;
    double metdw;
    double minDR = 999;
    double minDPhi = 999;

    for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {

      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjetup;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjetdw;
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
      //double bDiscriminatorJP = jit->bDiscriminator("jetProbabilityBJetTags");
      //float secvtxmass = jit->secvtxMass();
      double uncert = jit->uncOnFourVectorScale();
      float Lxy = jit->Lxy();
      float LxyErr = jit->LxyErr();

      mapJetBDiscriminator[idx] = bDiscriminator;

      for ( int bTagIndex=0, nBTagAlgo=bTagAlgos_.size(); bTagIndex<nBTagAlgo; ++bTagIndex )
      {
        const double bTagValue = jit->bDiscriminator(bTagAlgos_[bTagIndex].c_str());
        if ( (bTagIsCutMin_[bTagIndex]) xor (bTagValue < bTagCutValues_[bTagIndex]) ) {
             ++nbjets30_[bTagIndex];
             //double dRJPsibjet = deltaR(JPsiEta, JPsiPhi, jit->p4().eta(), jit->p4().phi());
             //double dR3 =  deltaR(lep3_eta, lep3_phi, jit->p4().eta(), jit->p4().phi());
             //double dR4 =  deltaR(lep4_eta, lep4_phi, jit->p4().eta(), jit->p4().phi());

             //if( dRJPsibjet < 0.5) {
                 //dRJPsibjet_[bTagIndex] = dRJPsibjet;
                 //dRlep3bjet_[bTagIndex] = dR3;
                 //dRlep4bjet_[bTagIndex] = dR4;
                 //inbJet_[bTagIndex] = 1;
                 //inJet = 1;
             //}

        }
      }
      if ( bDiscriminator > bTagCutValues_[2]) bidcs.push_back(idx); //for kinematic solution
      idx++;  

      //CSV b-discriminator 
  //    double bDisCSVweight = bDiscriminatorWeight(jit->p4().pt(), bDiscriminator, flavor );

      //build vallo:Jet  : turned off
      //vallot::Jet jet( jit->p4() );
      //jet.setFlavor( flavor );
      //jet.setTopdecay( jetfromtop );
      //jet.setbDiscriminator( bDiscriminator );
      //jet.setSecVtxMass( secvtxmass );  
      //jets->push_back(jet);
 
      //jets_secvtxmass.push_back( secvtxmass );
      jets_Lxy.push_back(Lxy);
      jets_LxyErr.push_back(LxyErr);
      jets_pt.push_back(jit->p4().pt());
      jets_eta.push_back(jit->p4().eta());
      jets_phi.push_back(jit->p4().phi());
      jets_flavor.push_back(flavor);
      jets_fromtop.push_back(jetfromtop);
//      jets_bDiscriminatorJP.push_back(bDiscriminatorJP);
//      jets_bDiscriminatorCSV.push_back(bDiscriminator); 
//      jets_bDisCSVweight.push_back( bDisCSVweight);
//      jets_bDisCSVweight.push_back( 1.0 );
    
      corrjetup = corrjet * (1+uncert); 
      corrjetdw = corrjet * (1-uncert); 

      if( JPsiMass > 0 && jit->pt() > 30){
        double dR = deltaR(jit->eta(), jit->phi(), JPsiEta, JPsiPhi);
        if(dR < minDR ) minDR = dR;
      }

      if( JPsiMass > 0 && jit->pt() > 30){
        double dphi = fabs(jit->phi()-JPsiPhi);
        if(dphi < minDPhi ) minDPhi = dphi;
      }
      
      if(jit->pt() > 30){
        jetspt30->push_back(corrjet);
        njet++;
      }//pt > 30 loop

      if(corrjetup.pt() > 30){
        njetUp++;
        metup_x -= corrjet.px()- corrjetup.px();
        metup_y -= corrjet.py()- corrjetup.py();
      }//pt > 30 loop
      if(corrjetdw.pt() > 30){
        njetDw++;
        metdw_x -= corrjet.px()- corrjetdw.px();
        metdw_y -= corrjet.py()- corrjetdw.py();
      }//pt > 30 loop

    }

    //csvd order
    std::vector< std::pair<int,double> > vecJetBDisc(mapJetBDiscriminator.begin(), mapJetBDiscriminator.end());
    std::sort(vecJetBDisc.begin(), vecJetBDisc.end(), bigger_second<data_t>());
    for(std::vector< std::pair<int,double> >::iterator it = vecJetBDisc.begin() ; it != vecJetBDisc.end(); ++it)
        //csvd_jetid.push_back((*it).first);

    //JPsi Jet minDR, minDPhi
    JPsiJetMinDR = minDR;   
    JPsiJetMinDPhi = minDPhi;   

    //JES uncertainty
    nJet30 = njet;
    nJet30Up = njetUp;
    nJet30Dw = njetDw;

/*    if( nJet30 >= 4){
      for(int i = 0; i < (int) nJet30 ; i++){
        if( i  <  2 ) continue;
        int jetid = csvd_jetid[i];
        //double bDisCSVweight = bDiscriminatorWeight(jets_pt[jetid], jets_bDiscriminatorCSV[jetid], jets_flavor[jetid], i );
        //jets_bDisCSVweight[jetid] =  bDisCSVweight ;
      }
    }
*/
    metup = sqrt(metup_x*metup_x + metup_y*metup_y);
    metdw = sqrt(metdw_x*metdw_x + metdw_y*metdw_y);
    METUp = metup;
    METDw = metdw;    

    //event selection
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
    cutStepBit[5] = (nJet30 >= 1); //jkim
    cutStepBit[6] = (nbjets30_[1] >= 1);  //jkim
    cutStepBit[7] = (nJPsiCand > 0 && JPsiPairSign < 0 );  //jkim
    cutStepBit[8] = (JPsiMass > 3.0 && JPsiMass < 3.2);  //jkim

    //process selection
    visible = nGenJet20 >= 1 && nGenbJet20 >=1 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.5 && abs( genLep2_eta ) < 2.5;
    //ttbb  = !isRealData && visible && nGenbJet20 >= 4; 
    //ttcc  = !isRealData && visible && nGencJet20 >= 2 && !ttbb;
    //ttLF  = !isRealData && visible && !ttbb && !ttcc; 

    processBit[0] = !isRealData && true;
    processBit[1] = !isRealData && visible ; //ttbar  && nGenbJet20 >= 4; //ttbb
    //processBit[2] = !isRealData && visible && nGencJet20 >= 2 && !processBit[1]; //ttcc
    //processBit[3] = !isRealData && visible && !processBit[1] && !processBit[2]; //ttLF
    processBit[2] = !isRealData && !visible; //TTOthers
    processBit[3] = !isRealData && ttbarGen_dileptonic != 1;
    processBit[4] = lep1_relIso03 > 0.2 && lep2_relIso03 > 0.2;

// old style
//    std::vector<TLorentzVector *> jet30(nJet30);
//    std::vector<int> jet30flavor(nJet30);
//    for (unsigned int i=0; i < nJet30; i++)
//    {
//      jet30[i] = new TLorentzVector( jets->at(i).px(), jets->at(i).py(), jets->at(i).pz(), jets->at(i).energy() );
//      jet30flavor[i] = jets->at(i).flavor();
//    }

    //bool prebtag = cutStepBit[0] && cutStepBit[1] && cutStepBit[2] && cutStepBit[3] && cutStepBit[4]; // && cutStepBit[5] ;
    bool dilepton = cutStepBit[0] && cutStepBit[1] && cutStepBit[2] ; //correct me
   
    if( !isRealData && dilepton && nJet30 >= 1){
      if( run2012_ == true ){
        BTagWeight2012 bTag;

//        bweight30CSVL = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight2012::CSVL, BTagWeight2012::NORM);
/////        bweight30CSVM = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight2012::CSVM, BTagWeight2012::NORM);
        //bweight30CSVT = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight2012::CSVT, BTagWeight2012::NORM);

//        bweight30CSVLup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight2012::CSVL, BTagWeight2012::UP);
/////        bweight30CSVMup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight2012::CSVM, BTagWeight2012::UP);
        //bweight30CSVTup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight2012::CSVT, BTagWeight2012::UP);

//        bweight30CSVLdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight2012::CSVL, BTagWeight2012::DW);
/////        bweight30CSVMdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight2012::CSVM, BTagWeight2012::DW);
        //bweight30CSVTdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight2012::CSVT, BTagWeight2012::DW);

//        bweight30CSVLuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight2012::CSVL, BTagWeight2012::UPLight);
/////        bweight30CSVMuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight2012::CSVM, BTagWeight2012::UPLight);
        //bweight30CSVTuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight2012::CSVT, BTagWeight2012::UPLight);

//        bweight30CSVLdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight2012::CSVL, BTagWeight2012::DWLight);
/////        bweight30CSVMdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight2012::CSVM, BTagWeight2012::DWLight);
        //bweight30CSVTdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight2012::CSVT, BTagWeight2012::DWLight);
      }else{
        BTagWeight bTag;

//        bweight30CSVL = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight::CSVL, BTagWeight::NORM);
/////        bweight30CSVM = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight::CSVM, BTagWeight::NORM);
        //bweight30CSVT = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight::CSVT, BTagWeight::NORM);

//        bweight30CSVLup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight::CSVL, BTagWeight::UP);
/////        bweight30CSVMup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight::CSVM, BTagWeight::UP);
        //bweight30CSVTup = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight::CSVT, BTagWeight::UP);

//        bweight30CSVLdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight::CSVL, BTagWeight::DW);
/////        bweight30CSVMdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight::CSVM, BTagWeight::DW);
        //bweight30CSVTdw = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight::CSVT, BTagWeight::DW);

//        bweight30CSVLuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight::CSVL, BTagWeight::UPLight);
/////        bweight30CSVMuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight::CSVM, BTagWeight::UPLight);
        //bweight30CSVTuplight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight::CSVT, BTagWeight::UPLight);

//        bweight30CSVLdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[0], BTagWeight::CSVL, BTagWeight::DWLight);
/////        bweight30CSVMdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[1], BTagWeight::CSVM, BTagWeight::DWLight);
        //bweight30CSVTdwlight = bTag.reweight( jets_pt, jets_eta, jets_flavor, nbjets30_[2], BTagWeight::CSVT, BTagWeight::DWLight);
      }
    }
    //cout<<"step6"<<endl;

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(mi->px(),mi->py(),0,mi->pt());
    met->push_back(corrmet);

    //cout<<"step7"<<endl;

/*    if(dilepton && nJet30 > 0){
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep1;
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep2;
      lep1.SetPxPyPzE(ZCand->at(0).leg1().px(),ZCand->at(0).leg1().py(),ZCand->at(0).leg1().pz(),ZCand->at(0).leg1().energy());
      lep2.SetPxPyPzE(ZCand->at(0).leg2().px(),ZCand->at(0).leg2().py(),ZCand->at(0).leg2().pz(),ZCand->at(0).leg2().energy());*/

      //const vallot::TTbarMass ttbarMass(lep1, lep2, jetspt30->at(csvd_jetid[0]), jetspt30->at(csvd_jetid[1]), met->at(0));
      //ttbar->push_back(ttbarMass);

      //vsumttbarM = ttbarMass.M();

/*      int cmb = 0 ;
      const string hypo = "kKinSolution"; 

      if( fullLepEvt.isValid() && fullLepEvt->size() > 0){
        
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
        //jets->at(b).setRecoTopdecay("kinSolution");
        //jets->at(bbar).setRecoTopdecay("kinSolution");
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

        double deltaPhi = kin_top_phi - kin_topBar_phi;
        while( deltaPhi > M_PI ) deltaPhi -= 2*M_PI;
        while( deltaPhi <= -M_PI) deltaPhi += 2*M_PI;
        kin_ttbar_dphi = fabs(deltaPhi);
 
      }*/

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
//  }
//////////
    //gen information
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

    //ttbar gen variables
    vallot::CMGTTbarJPsiCandidate ttbarGenLevel;

    if( genParticles_.isValid() && genJets_.isValid() ){ // && prebtag){ // && topSample_){
      const reco::GenParticleCollection* myGenParticles = 0;
      myGenParticles = &(*genParticles_);
      const std::vector<cmg::GenJet>* myGenJets = 0;
      myGenJets = &(*genJets_);

      ttbarGenLevel.building(myGenJets, myGenParticles);
      //genttbarM = ttbarGenLevel.mass();
      nGenJet20 = ttbarGenLevel.NJets20();
      nGenbJet20 = ttbarGenLevel.NbJets20();
      //nGencJet20 = ttbarGenLevel.NcJets20();

      genLep1_pt = ttbarGenLevel.lepton1().pt();
      genLep2_pt = ttbarGenLevel.lepton2().pt();
      genLep1_phi = ttbarGenLevel.lepton1().phi();
      genLep2_phi = ttbarGenLevel.lepton2().phi();
      genLep1_eta = ttbarGenLevel.lepton1().eta();
      genLep2_eta = ttbarGenLevel.lepton2().eta();

      gentquark1_eta = ttbarGenLevel.tquarks1().eta();
      gentquark2_eta = ttbarGenLevel.tquarks2().eta();
      gentquark1_pt = ttbarGenLevel.tquarks1().pt();
      gentquark2_pt = ttbarGenLevel.tquarks2().pt();
      gentquark1_phi = ttbarGenLevel.tquarks1().phi();
      gentquark2_phi = ttbarGenLevel.tquarks2().phi();

      genbquark1_eta = ttbarGenLevel.bquarks1().eta();
      genbquark2_eta = ttbarGenLevel.bquarks2().eta();
      genbquark1_pt = ttbarGenLevel.bquarks1().pt();
      genbquark2_pt = ttbarGenLevel.bquarks2().pt();
      genbquark1_phi = ttbarGenLevel.bquarks1().phi();
      genbquark2_phi = ttbarGenLevel.bquarks2().phi();
/////      genbquark1_p = ttbarGenLevel.bquarks1().P();
/////      genbquark2_p = ttbarGenLevel.bquarks2().P();
      //genbquark1_theta = ttbarGenLevel.bquarks1().theta();
      //genbquark2_theta = ttbarGenLevel.bquarks2().theta();

 /*     genJPsi1_mass = ttbarGenLevel.JPsi1().mass();
      genJPsi2_mass = ttbarGenLevel.JPsi2().mass();
      genJPsi1_eta = ttbarGenLevel.JPsi1().eta();
      genJPsi2_eta = ttbarGenLevel.JPsi2().eta();
      genJPsi1_pt = ttbarGenLevel.JPsi1().pt();
      genJPsi2_pt = ttbarGenLevel.JPsi2().pt();
      genJPsi1_phi = ttbarGenLevel.JPsi1().phi();
      genJPsi2_phi = ttbarGenLevel.JPsi2().phi();
      genJPsi1_p = ttbarGenLevel.JPsi1().P();
      genJPsi2_p = ttbarGenLevel.JPsi2().P();
      genJPsi1_theta = ttbarGenLevel.JPsi1().theta();
      genJPsi2_theta = ttbarGenLevel.JPsi2().theta();

      genJPsiB1_eta = ttbarGenLevel.JPsiB1().eta();
      genJPsiB2_eta = ttbarGenLevel.JPsiB2().eta();
      genJPsiB1_pt = ttbarGenLevel.JPsiB1().pt();
      genJPsiB2_pt = ttbarGenLevel.JPsiB2().pt();
      genJPsiB1_phi = ttbarGenLevel.JPsiB1().phi();
      genJPsiB2_phi = ttbarGenLevel.JPsiB2().phi();
      genJPsiB1_p = ttbarGenLevel.JPsiB1().P();
      genJPsiB2_p = ttbarGenLevel.JPsiB2().P();
      genJPsiB1_theta = ttbarGenLevel.JPsiB1().theta();
      genJPsiB2_theta = ttbarGenLevel.JPsiB2().theta();

      genJPsiLep1P_pt = ttbarGenLevel.JPsilepton1P().pt();
      genJPsiLep1M_pt = ttbarGenLevel.JPsilepton1M().pt();
      genJPsiLep1P_eta = ttbarGenLevel.JPsilepton1P().eta();
      genJPsiLep1M_eta = ttbarGenLevel.JPsilepton1M().eta();
      genJPsiLep1P_phi = ttbarGenLevel.JPsilepton1P().phi();
      genJPsiLep1M_phi = ttbarGenLevel.JPsilepton1M().phi();
      genJPsiLep2P_pt = ttbarGenLevel.JPsilepton2P().pt();
      genJPsiLep2M_pt = ttbarGenLevel.JPsilepton2M().pt();
      genJPsiLep2P_eta = ttbarGenLevel.JPsilepton2P().eta();
      genJPsiLep2M_eta = ttbarGenLevel.JPsilepton2M().eta();
      genJPsiLep2P_phi = ttbarGenLevel.JPsilepton2P().phi();
      genJPsiLep2M_phi = ttbarGenLevel.JPsilepton2M().phi();
*/
    genpriJPsi_mass = ttbarGenLevel.priJPsi().mass();
    gensecJPsi_mass = ttbarGenLevel.secJPsi().mass();
    genpriJPsi_eta = ttbarGenLevel.priJPsi().eta();
    gensecJPsi_eta = ttbarGenLevel.secJPsi().eta();
    genpriJPsi_pt = ttbarGenLevel.priJPsi().pt();
    gensecJPsi_pt = ttbarGenLevel.secJPsi().pt();
    genNpJPsi = ttbarGenLevel.NpJPsi();
    genNbJPsi = ttbarGenLevel.NbJPsi();
    genNbQuarksTop = ttbarGenLevel.NbQuarksTop();
    genNbQuarks = ttbarGenLevel.NbQuarks();
    genNbJets = ttbarGenLevel.NbJets();
    //genNbJetJPsi = ttbarGenLevel.NbJetJPsi();

    gentbJPsi_mass = ttbarGenLevel.tbJPsi().mass();
    gentbbJPsi_mass = ttbarGenLevel.tbbJPsi().mass();
    gentbJPsi_pt = ttbarGenLevel.tbJPsi().pt();
    //if(gentbJPsi_pt>0) cout<<"gentbJPsi_pt : "<<gentbJPsi_pt<<endl;
    gentbJPsilp_pt = ttbarGenLevel.tbJPsilp().pt();
    gentbJPsilm_pt = ttbarGenLevel.tbJPsilm().pt();
    gentbbJPsi_pt = ttbarGenLevel.tbbJPsi().pt();
    //if(gentbbJPsi_pt>0) cout<<"gentbbJPsi_pt : "<<gentbbJPsi_pt<<endl;
    gentbbJPsilp_pt = ttbarGenLevel.tbbJPsilp().pt();
    gentbbJPsilm_pt = ttbarGenLevel.tbbJPsilm().pt();
    gentbJPsi_eta = ttbarGenLevel.tbJPsi().eta();
    gentbJPsilp_eta = ttbarGenLevel.tbJPsilp().eta();
    gentbJPsilm_eta = ttbarGenLevel.tbJPsilm().eta();
    gentbbJPsi_eta = ttbarGenLevel.tbbJPsi().eta();
    gentbbJPsilp_eta = ttbarGenLevel.tbbJPsilp().eta();
    gentbbJPsilm_eta = ttbarGenLevel.tbbJPsilm().eta();
    gentbJPsi_phi = ttbarGenLevel.tbJPsi().phi();
    gentbJPsilp_phi = ttbarGenLevel.tbJPsilp().phi();
    gentbJPsilm_phi = ttbarGenLevel.tbJPsilm().phi();
    gentbbJPsi_phi = ttbarGenLevel.tbbJPsi().phi();
    gentbbJPsilp_phi = ttbarGenLevel.tbbJPsilp().phi();
    gentbbJPsilm_phi = ttbarGenLevel.tbbJPsilm().phi();
    genNtbJPsi = ttbarGenLevel.NtbJPsi();
    genNtbJPsilp = ttbarGenLevel.NtbJPsilp();
    genNtbJPsilm = ttbarGenLevel.NtbJPsilm();
    genNtbbJPsi = ttbarGenLevel.NtbbJPsi();
    genNtbbJPsilp = ttbarGenLevel.NtbbJPsilp();
    genNtbbJPsilm = ttbarGenLevel.NtbbJPsilm();

    genpriJPsi_3Dl = ttbarGenLevel.priJPsi3DlTrue();
    gensecJPsi_3Dl = ttbarGenLevel.secJPsi3DlTrue();
    genpriJPsi_ppdl = ttbarGenLevel.priJPsippdlTrue();
    gensecJPsi_ppdl = ttbarGenLevel.secJPsippdlTrue();
    gentbJPsi_3Dl = ttbarGenLevel.tbJPsi3DlTrue();
    gentbbJPsi_3Dl = ttbarGenLevel.tbbJPsi3DlTrue();
    gentbJPsi_ppdl = ttbarGenLevel.tbJPsippdlTrue();
    gentbbJPsi_ppdl = ttbarGenLevel.tbbJPsippdlTrue();
    gentbJPsi_dtheta = ttbarGenLevel.tbJPsidthetaTrue();
    gentbbJPsi_dtheta = ttbarGenLevel.tbbJPsidthetaTrue();

      ttbarGen_dileptonic = ttbarGenLevel.diLeptonic();

      //if(ttbarGenLevel.is2tops())
      //       topweight = sqrt( exp(0.156-0.00137*ttbarGenLevel.topquark1().pt() ) * exp(0.156-0.00137*ttbarGenLevel.topquark2().pt()) ); 
      //else topweight = 1.0;

      ttbarGen->push_back(ttbarGenLevel);
    }
    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    double w = puweight;

    //fill histograms
   if ( histograms_ )
    {

      for ( int process = 0 ; process < nProcess_; ++ process){ 
	for ( int cutStep = 0; cutStep < nCutStep_; ++cutStep )
	{
	  h_[process][cutStep].hNEvents->Fill(0);

	  bool isPassingCutStep = true;
	  for ( int i=0; i<=cutStep; ++i )
	  {
            if( i == 1 && process == 6) continue;//special treatmenet for QCD process
	    if ( !cutStepBit[i] )
	    {
	      isPassingCutStep = false;
	      break;
	    }
	  }
	  if ( !isPassingCutStep ) continue;
          if ( !processBit[process] ) continue;
	  
	  h_[process][cutStep].hNEvents->Fill(1);

	  //h_[process][cutStep].hgenttbarM->Fill(genttbarM,w);
	  h_[process][cutStep].hnpileup->Fill(npileup,w);
	  h_[process][cutStep].hnvertex->Fill(nvertex,w);
	  h_[process][cutStep].hNLepton1->Fill(muons1_->size(),w);
	  h_[process][cutStep].hNLepton2->Fill(muons2_->size(),w);
	  h_[process][cutStep].hNLepton3->Fill(muons3_->size(),w);
	  h_[process][cutStep].hNLepton4->Fill(muons4_->size(),w);
          h_[process][cutStep].hNJPsi->Fill(JPsiCand->size(),w);
          h_[process][cutStep].hNLepJPsi1->Fill(LepJPsiCand1->size(),w);
          h_[process][cutStep].hNLepJPsi2->Fill(LepJPsiCand2->size(),w);
	  h_[process][cutStep].hNJet->Fill(nJet30,w);

	  h_[process][cutStep].hpt1->Fill(lep1_pt,w);
	  h_[process][cutStep].hpt2->Fill(lep2_pt,w);
	  h_[process][cutStep].hpt3->Fill(lep3_pt,w);
	  h_[process][cutStep].hpt4->Fill(lep4_pt,w);
	  h_[process][cutStep].heta1->Fill(lep1_eta,w);
	  h_[process][cutStep].heta2->Fill(lep2_eta,w);
	  h_[process][cutStep].heta3->Fill(lep3_eta,w);
	  h_[process][cutStep].heta4->Fill(lep4_eta,w);
	  h_[process][cutStep].hrelIso1->Fill(lep1_relIso03,w);
	  h_[process][cutStep].hrelIso2->Fill(lep2_relIso03,w);
	  //h_[process][cutStep].hrelIso3->Fill(lep3_relIso03,w);
	  //h_[process][cutStep].hrelIso4->Fill(lep4_relIso03,w);

	  if ( nJet30 > 0 )
	  {
	    h_[process][cutStep].hjet1pt ->Fill(jets_pt[0],w);
	    h_[process][cutStep].hjet1eta->Fill(jets_eta[0],w);
	    h_[process][cutStep].hjet1phi->Fill(jets_phi[0],w);
	  }
	  if ( nJet30 > 1 )
	  {
	    h_[process][cutStep].hjet2pt ->Fill(jets_pt[1],w);
	    h_[process][cutStep].hjet2eta->Fill(jets_eta[1],w);
	    h_[process][cutStep].hjet2phi->Fill(jets_phi[1],w);

	    h_[process][cutStep].hHT->Fill(lep1_pt+lep2_pt+jets_pt[0]+jets_pt[1],w);
	  }
	  if ( nJet30 > 2 )
	  {
	    h_[process][cutStep].hjet3pt ->Fill(jets_pt[2],w);
	    h_[process][cutStep].hjet3eta->Fill(jets_eta[2],w);
	    h_[process][cutStep].hjet3phi->Fill(jets_phi[2],w);
	  }
	  if ( nJet30 > 3 )
	  {
	    h_[process][cutStep].hjet4pt ->Fill(jets_pt[3],w);
	    h_[process][cutStep].hjet4eta->Fill(jets_eta[3],w);
	    h_[process][cutStep].hjet4phi->Fill(jets_phi[3],w);
            //can be used for CSVT selection
            //h_[process][cutStep].hBDiscriminatorCSVJet3->Fill(jets_bDiscriminatorCSV[csvd_jetid[2]],w*bweight30CSVT*jets_bDisCSVweight[csvd_jetid[2]]);
            //h_[process][cutStep].hBDiscriminatorCSVJet4->Fill(jets_bDiscriminatorCSV[csvd_jetid[3]],w*bweight30CSVT*jets_bDisCSVweight[csvd_jetid[3]]);
	  }

	  for ( int i=0, n=nbjets30_.size(); i<n; ++i )
	  {
            //double bweight = 1.0;
            //if( i == 0 ) bweight = bweight30CSVL;
            /////if( i == 1 ) bweight = bweight30CSVM;
            //if( i == 2 ) bweight = bweight30CSVT;
	    /////h_[process][cutStep].hnBJets.at(i)->Fill(nbjets30_[i],w*bweight);
	  }

	  h_[process][cutStep].hMET->Fill(MET,w);
	  h_[process][cutStep].hMETPhi->Fill(met->at(0).phi(),w);
	  if ( !pfMet->empty() )
	  {
	    h_[process][cutStep].hSumET->Fill(pfMet->at(0).sumEt(),w);
	    h_[process][cutStep].hChET->Fill(pfMet->at(0).chargedHadEt(),w);
	    h_[process][cutStep].hNhET->Fill(pfMet->at(0).neutralHadEt(),w);
	    h_[process][cutStep].hPhET->Fill(pfMet->at(0).photonEt(),w);
	  }

	  h_[process][cutStep].hZMass->Fill(ZMass,w);
          h_[process][cutStep].hJPsiMass->Fill(JPsiMass,w);
          h_[process][cutStep].hLepJPsiMass1->Fill(LepJPsiMass1,w);
          h_[process][cutStep].hLepJPsiMass2->Fill(LepJPsiMass2,w);

	  /*if ( !ttbar->empty() )
	  {
	    h_[process][cutStep].hvsumM->Fill(ttbar->at(0).M(),w);
	    h_[process][cutStep].hmaosM->Fill(ttbar->at(0).maosM(),w);
	    h_[process][cutStep].htopMass1->Fill(ttbar->at(0).leg1().M(),w);
	    h_[process][cutStep].htopMass2->Fill(ttbar->at(0).leg2().M(),w);
	  }*/
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
    JPsi->clear();
    LepJPsi1->clear();
    LepJPsi2->clear();
    lep1->clear();
    lep2->clear();
    lep3->clear();
    lep4->clear();
    pfMet->clear();
    //ttbar->clear();
    //ttbarKin->clear();
    //ttbarMaos->clear();
    ttbarGen->clear();
    jets->clear();
    met->clear();
    jetspt30->clear();

    //kin_jetid.clear();
    //csvd_jetid.clear();

    for ( int bTagIndex=0, nBTag=nbjets30_.size(); bTagIndex<nBTag; ++bTagIndex )
    {
      nbjets30_[bTagIndex] = -999;
      //inbJet_[bTagIndex] = -999;
    }

    //topweight = 1.0;
    puweight = 1.0;
    puweightplus = 1.0;
    puweightminus = 1.0;

    //bweight30CSVL = 1.0;
    /////bweight30CSVM = 1.0;
    //bweight30CSVT = 1.0;

    //bweight30CSVLup = 1.0;
    //////bweight30CSVMup = 1.0;
    //bweight30CSVTup = 1.0;

    //bweight30CSVLdw = 1.0;
    /////bweight30CSVMdw = 1.0;
    //bweight30CSVTdw = 1.0;

    //bweight30CSVLuplight = 1.0;
    /////bweight30CSVMuplight = 1.0;
    //bweight30CSVTuplight = 1.0;

    //bweight30CSVLdwlight = 1.0;
    /////bweight30CSVMdwlight = 1.0;
    //bweight30CSVTdwlight = 1.0;

    ZMass = -999; 
    genZMass = -999; 
    ZtauDecay = 0; 
    PairSign = -999;
    JPsiMass = -999;
    JPsiEta = -999;
    JPsiPhi = -999;
    //JPsiTheta = -999;
    JPsiPt = -999;
    JPsivProb = -999;
    JPsidlPV = -999;
    //JPsidlErrPV = -999;
    JPsippdlPV = -999;
    JPsippdlErrPV = -999;
    //JPsippdlBS = -999;
    //JPsippdlErrBS = -999;
    JPsiMomIDTrue = -999;
    JPsiDlTrue = -999;
    JPsippdlTrue = -999;
    LepJPsiMass1 = -999;
    LepJPsiMass2 = -999;
    LepJPsidTheta1 = -999;
    LepJPsidTheta2 = -999;
    LepJPsidThetalower = -999;
    LepJPsidThetabigger = -999;
    LepJPsidPhi1 = -999;
    LepJPsidPhi2 = -999;
    LepJPsidPhilower = -999;
    LepJPsidPhibigger = -999;
    LepJPsidR1 = -999;
    LepJPsidR2 = -999;
    LepJPsidRlower = -999;
    LepJPsidRbigger = -999;
    JPsiPairSign = -999;
    JPsiJetMinDR = -999;
    JPsiJetMinDPhi = -999;
    isIso = -1;
    //inJet = -1;
    lep1_relIso04 = -999;
    lep2_relIso04 = -999;
    /*lep1_chIso03 = -999;
    lep2_chIso03 = -999;
    lep1_nhIso03 = -999;
    lep2_nhIso03 = -999;
    lep1_phIso03 = -999;
    lep2_phIso03 = -999;*/
    lep1_relIso03 = -999;
    lep2_relIso03 = -999;
    lep1_relIso03db = -999;
    lep2_relIso03db = -999;
    lep1_relIso03rho = -999;
    lep2_relIso03rho = -999;
    lep1_pt = -999; 
    lep2_pt = -999;
    lep3_pt = -999;
    lep4_pt = -999;
    lep1_eta = -999;
    lep2_eta = -999;
    lep3_eta = -999;
    lep4_eta = -999;
    lep1_phi = -999;
    lep2_phi = -999;
    lep3_phi = -999;
    lep4_phi = -999;
    lep1_theta = -999;
    lep2_theta = -999;
    lep1_charge = 0.0;
    lep2_charge = 0.0;
    lep3_charge = 0.0;
    lep4_charge = 0.0;
    lepweight = 1.0;
 
    //kin_ttbar_mass = -999;
    //kin_ttbar_dphi = -999;
    //maos_ttbar_mass = -999;
    //genttbarM = -999;
    //vsumttbarM = -999;

    //jets_secvtxmass.clear();
    jets_Lxy.clear();
    jets_LxyErr.clear();
    jets_pt.clear();
    jets_eta.clear();
    jets_phi.clear();
    jets_flavor.clear();
    jets_fromtop.clear();
    //jets_bDiscriminatorJP.clear();
    jets_bDiscriminatorCSV.clear();
    //jets_bDisCSVweight.clear();

    nJet30 = 0;
    nJet30Up = 0;
    nJet30Dw = 0;
    nGenJet20 = 0;
    nGenbJet20 = 0;
    //nGencJet20 = 0;

    genLep1_pt = -1;
    genLep2_pt = -1;
    genbquark1_pt = -1;
    genbquark2_pt = -1; 
    gentquark1_pt = -1;
    gentquark2_pt = -1;
/*    genJPsi1_pt = -1;
    genJPsi2_pt = -1;
    genJPsiB1_pt = -1;
    genJPsiB2_pt = -1;
    genJPsiLep1P_pt = -1;
    genJPsiLep1M_pt = -1;
    genJPsiLep2P_pt = -1;
    genJPsiLep2M_pt = -1;*/
  genpriJPsi_pt = -1;
  gensecJPsi_pt = -1;
  gentbJPsi_pt = -1;
  gentbJPsilp_pt = -1;
  gentbJPsilm_pt = -1;
  gentbbJPsi_pt = -1;
  gentbbJPsilp_pt = -1;
  gentbbJPsilm_pt = -1;

/////    genbquark1_p = -1; 
/////    genbquark2_p = -1;
/*    genJPsi1_p = -1;
    genJPsi2_p = -1;
    genJPsiB1_p = -1;
    genJPsiB2_p = -1;*/

    genLep1_eta = -999;
    genLep2_eta = -999;
    genbquark1_eta = -999;
    genbquark2_eta = -999;
    gentquark1_eta = -999;
    gentquark2_eta = -999;
/*    genJPsi1_eta = -999;
    genJPsi2_eta = -999;
    genJPsiB1_eta = -999;
    genJPsiB2_eta = -999;
    genJPsiLep1P_eta = -999;
    genJPsiLep1M_eta = -999;
    genJPsiLep2P_eta = -999;
    genJPsiLep2M_eta = -999;*/
  genpriJPsi_eta = -999;
  gensecJPsi_eta = -999;
  gentbJPsi_eta = -999;
  gentbJPsilp_eta = -999;
  gentbJPsilm_eta = -999;
  gentbbJPsi_eta = -999;
  gentbbJPsilp_eta = -999;
  gentbbJPsilm_eta = -999;

    genLep1_phi = -999;
    genLep2_phi = -999;
    genbquark1_phi = -999;
    genbquark2_phi = -999;
    gentquark1_phi = -999;
    gentquark2_phi = -999;
/*    genJPsi1_phi = -999;
    genJPsi2_phi = -999;
    genJPsiB1_phi = -999;
    genJPsiB2_phi = -999;
    genJPsiLep1P_phi = -999;
    genJPsiLep1M_phi = -999;
    genJPsiLep2P_phi = -999;
    genJPsiLep2M_phi = -999;*/
  gentbJPsi_phi = -999;
  gentbJPsilp_phi = -999;
  gentbJPsilm_phi = -999;
  gentbbJPsi_phi = -999;
  gentbbJPsilp_phi = -999;
  gentbbJPsilm_phi = -999;

    //genbquark1_theta = -999;
    //genbquark2_theta = -999;
/*    genJPsiB1_theta = -999;
    genJPsiB2_theta = -999;
    genJPsi1_theta = -999;
    genJPsi2_theta = -999;

    genJPsi1_mass = -1
    genJPsi2_mass = -1;*/

  genpriJPsi_3Dl = -999;
  gensecJPsi_3Dl = -999;
  gentbJPsi_3Dl = -999;
  gentbbJPsi_3Dl = -999;
  genpriJPsi_ppdl = -999;
  gensecJPsi_ppdl = -999;
  gentbJPsi_ppdl = -999;
  gentbbJPsi_ppdl = -999;
  gentbJPsi_dtheta = -999;
  gentbbJPsi_dtheta = -999;

  genpriJPsi_mass = -1;
  gensecJPsi_mass = -1;
  gentbJPsi_mass = -1;
  gentbbJPsi_mass = -1;

  genNpJPsi = -1;
  genNbJPsi = -1;
  genNbQuarksTop = -1;
  genNbQuarks = -1;
  genNbJets = -1;
  //genNbJetJPsi = -1;
  genNtbJPsi = -1;
  genNtbJPsilp = -1;
  genNtbJPsilm = -1;
  genNtbbJPsi = -1;
  genNtbbJPsilp = -1;
  genNtbbJPsilm = -1;

    ttbarGen_dileptonic = 0;
    visible = 0;
    //ttbb = 0;
    //ttcc = 0;
    //ttLF = 0;

    /*kin_nu_pt = -999;
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
    */
    metphi = -999;
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

  double PTWeight(double pt, int flavor, int i){
    double w = 1.0;
    if( i == 2 ){
      w = 1.07059 - 0.0012197*pt + 5.10046e-07*pow(pt,2) + 2.12404e-09*pow(pt,3);  
    }else if( i > 2){
      w = 1.02154 + 4.66542e-05*pt -5.23393e-06*pow(pt,2) + 8.56852e-09*pow(pt,3);
    }
    return w;
  }

  double bDiscriminatorWeight(double pt, double x, int flavor, int i, bool all){

    if( all == false && fabs(flavor) == 5 ) return 1.0; 
    if( all == false && x > 0.9 ) return 1.0;

    double w = 1.0;
 
    if( run2012_ ){
      if(i == 2){
        w = 0.625022+2.75887*x-4.44845*pow(x,2)+3.46847*pow(x,3)-1.38906*pow(x,4);
      }else if( i > 2 ){
        w = 0.691663+4.51816*x-9.47984*pow(x,2)+9.28541*pow(x,3)-4.34451*pow(x,4);
      }
    }else{
      if(i == 2){
        w = 0.721659+1.66156*x+0.264706*pow(x,2)-3.49383*pow(x,3)+2.43802*pow(x,4);
      }else if( i > 2){
        w = 0.788629+3.0651*x-5.8926*pow(x,2)+5.05896*pow(x,3)-2.12369*pow(x,4);
      }
    }


    return w;
  }  

  typedef vector<cmg::PFJet>::const_iterator JI;

  edm::InputTag muonLabel1_;
  edm::InputTag muonLabel2_;
  edm::InputTag muonLabel3_;
  edm::InputTag muonLabel4_;
  edm::InputTag dileptonLabel_;
  edm::InputTag jpsiLabel_;
  edm::InputTag lepJPsiLabel1_;
  edm::InputTag lepJPsiLabel2_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;
  edm::InputTag vertexLabel_;

  edm::InputTag puWeightLabel_;
  edm::InputTag puUpWeightLabel_;
  edm::InputTag puDwWeightLabel_;
  edm::InputTag puNVertexLabel_;

  //edm::InputTag fullLepEvt_;
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
  //std::vector<int> inbJet_;
  //std::vector<double> dRJPsibjet_;
  //std::vector<double> dRlep3bjet_;
  //std::vector<double> dRlep4bjet_;

  TTree* tree;

  TH1F * tmp;

  std::vector<vallot::ZCandidate>* Z;
  std::vector<vallot::JPsiCandidate>* JPsi;
  std::vector<vallot::LepJPsiCandidate>* LepJPsi1;
  std::vector<vallot::LepJPsiCandidate>* LepJPsi2;
  std::vector<vallot::Lepton>* lep1;
  std::vector<vallot::Lepton>* lep2;
  std::vector<vallot::Lepton>* lep3;
  std::vector<vallot::Lepton>* lep4;
  std::vector<vallot::METCandidate>* pfMet;
  //std::vector<vallot::TTbarMass>* ttbar;
  //std::vector<vallot::TTbarDILEvent>* ttbarKin;
  //std::vector<vallot::TTbarDILEvent>* ttbarMaos;
  std::vector<vallot::CMGTTbarJPsiCandidate>* ttbarGen;
  std::vector<vallot::Jet>* jets;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jetspt30;

  //std::vector<int> kin_jetid;
  //std::vector<int> csvd_jetid;

  double MET;
  double metphi;
  double METUp;
  double METDw;
  double ZMass;
  double genZMass;
  double JPsiMass;
  double JPsiEta;
  double JPsiPhi;
  //double JPsiTheta;
  double JPsiPt;
  double JPsivProb;
  double JPsidlPV;
  //double JPsidlErrPV;
  double JPsippdlPV;
  double JPsippdlErrPV;
  //double JPsippdlBS;
  //double JPsippdlErrBS;
  int    JPsiMomIDTrue;
  double JPsiDlTrue;
  double JPsippdlTrue;
  double LepJPsidTheta1;
  double LepJPsidTheta2;
  double LepJPsidThetalower;
  double LepJPsidThetabigger;
  double LepJPsidPhi1;
  double LepJPsidPhi2;
  double LepJPsidPhilower;
  double LepJPsidPhibigger;
  double LepJPsidR1;
  double LepJPsidR2;
  double LepJPsidRlower;
  double LepJPsidRbigger;
  double LepJPsiMass1;
  double LepJPsiMass2;
  int ZtauDecay;
  double PairSign;
  double JPsiPairSign;
  double JPsiJetMinDR;
  double JPsiJetMinDPhi;
  double isIso;
  //double inJet;
  double lep1_relIso04;
  double lep2_relIso04;
  double lep1_relIso03;
  double lep2_relIso03;
  /*double lep1_chIso03;
  double lep2_chIso03;
  double lep1_nhIso03;
  double lep2_nhIso03;
  double lep1_phIso03;
  double lep2_phIso03;*/
  double lep1_relIso03db;
  double lep2_relIso03db;
  double lep1_relIso03rho;
  double lep2_relIso03rho;
  double lep1_pt;
  double lep2_pt;
  double lep3_pt;
  double lep4_pt;
  double lep1_eta;
  double lep2_eta;
  double lep3_eta;
  double lep4_eta;
  double lep1_phi;
  double lep2_phi;
  double lep3_phi;
  double lep4_phi;
  double lep1_theta;
  double lep2_theta;
  double lep1_charge;
  double lep2_charge;
  double lep3_charge;
  double lep4_charge;
  double lepweight;

  //double kin_ttbar_mass;
  //double kin_ttbar_dphi;
  //double maos_ttbar_mass;
  //double genttbarM;
  //double vsumttbarM;

  //std::vector<double> jets_secvtxmass;
  std::vector<double> jets_Lxy;
  std::vector<double> jets_LxyErr;
  std::vector<double> jets_pt;
  std::vector<double> jets_eta;
  std::vector<double> jets_phi;
  std::vector<int> jets_flavor;
  std::vector<int> jets_fromtop;
  //std::vector<double> jets_bDiscriminatorJP;
  std::vector<double> jets_bDiscriminatorCSV;
  //std::vector<double> jets_bDisCSVweight;
  std::vector<double> jets_ptweight;

  unsigned int nJet30;
  unsigned int nJet30Up;
  unsigned int nJet30Dw;
  unsigned int nGenJet20;
  unsigned int nGenbJet20;
  //unsigned int nGencJet20;

  unsigned int nJPsiCand;
  unsigned int nLepJPsiCand1;
  unsigned int nLepJPsiCand2;

  double genLep1_pt;
  double genLep2_pt;
  double genbquark1_pt;
  double genbquark2_pt;      
  double gentquark1_pt;
  double gentquark2_pt;
/*  double genJPsi1_pt;
  double genJPsi2_pt;
  double genJPsiB1_pt;
  double genJPsiB2_pt;
  double genJPsiLep1P_pt; 
  double genJPsiLep1M_pt; 
  double genJPsiLep2P_pt; 
  double genJPsiLep2M_pt; */
  double genpriJPsi_pt;
  double gensecJPsi_pt;
  double gentbJPsi_pt;
  double gentbJPsilp_pt;
  double gentbJPsilm_pt;
  double gentbbJPsi_pt;
  double gentbbJPsilp_pt;
  double gentbbJPsilm_pt;

/////  double genbquark1_p;
/////  double genbquark2_p;   
/*  double genJPsi1_p;
  double genJPsi2_p;
  double genJPsiB1_p;
  double genJPsiB2_p;*/

  double genLep1_eta;
  double genLep2_eta;
  double genbquark1_eta;
  double genbquark2_eta; 
  double gentquark1_eta;
  double gentquark2_eta;
/*  double genJPsi1_eta;
  double genJPsi2_eta;
  double genJPsiB1_eta;
  double genJPsiB2_eta;
  double genJPsiLep1P_eta;
  double genJPsiLep1M_eta;
  double genJPsiLep2P_eta;
  double genJPsiLep2M_eta;*/
  double genpriJPsi_eta;
  double gensecJPsi_eta;
  double gentbJPsi_eta;
  double gentbJPsilp_eta;
  double gentbJPsilm_eta;
  double gentbbJPsi_eta;
  double gentbbJPsilp_eta;
  double gentbbJPsilm_eta;

  double genLep1_phi;
  double genLep2_phi;
  double genbquark1_phi;
  double genbquark2_phi; 
  double gentquark1_phi;
  double gentquark2_phi;
/*  double genJPsi1_phi;
  double genJPsi2_phi;
  double genJPsiB1_phi;
  double genJPsiB2_phi;
  double genJPsiLep1P_phi;
  double genJPsiLep1M_phi;
  double genJPsiLep2P_phi;
  double genJPsiLep2M_phi;*/
  double gentbJPsi_phi;
  double gentbJPsilp_phi;
  double gentbJPsilm_phi;
  double gentbbJPsi_phi;
  double gentbbJPsilp_phi;
  double gentbbJPsilm_phi;

  //double genbquark1_theta;
  //double genbquark2_theta;

  double genpriJPsi_3Dl;
  double gensecJPsi_3Dl;
  double gentbJPsi_3Dl;
  double gentbbJPsi_3Dl;
  double genpriJPsi_ppdl;
  double gensecJPsi_ppdl;
  double gentbJPsi_ppdl;
  double gentbbJPsi_ppdl;
  double gentbJPsi_dtheta;
  double gentbbJPsi_dtheta;

  double genpriJPsi_mass;
  double gensecJPsi_mass;
  double gentbJPsi_mass;
  double gentbbJPsi_mass;

  int genNpJPsi;
  int genNbJPsi;
  int genNbQuarksTop;
  int genNbQuarks;
  int genNbJets;
  //int genNbJetJPsi;
  int genNtbJPsi;
  int genNtbJPsilp;
  int genNtbJPsilm;
  int genNtbbJPsi;
  int genNtbbJPsilp;
  int genNtbbJPsilm;

  int ttbarGen_dileptonic;
  int visible;
  //int ttbb;
  //int ttcc;
  //int ttLF;
  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int npileup;
  unsigned int nvertex;

  //double topweight;
  double puweight;
  double puweightplus;
  double puweightminus;

  //double bweight30CSVL;
  /////double bweight30CSVM;
  //double bweight30CSVT;

  //double bweight30CSVLup;
  /////double bweight30CSVMup;
  //double bweight30CSVTup;

  //double bweight30CSVLdw;
  /////double bweight30CSVMdw;
  //double bweight30CSVTdw;

  //double bweight30CSVLuplight;
  /////double bweight30CSVMuplight;
  //double bweight30CSVTuplight;

  //double bweight30CSVLdwlight;
  /////double bweight30CSVMdwlight;
  //double bweight30CSVTdwlight;

/*  double kin_nu_pt;
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
*/
  bool applyIso_;
  bool oppPair_;

  unsigned int nstep_;
  bool run2012_;
  bool histograms_;

  int nCutStep_;
  int nProcess_;
  //std::vector<Histograms> h_;
  std::map<int, std::vector<Histograms> > h_;

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

