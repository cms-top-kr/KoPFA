#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "KoPFA/CMGDataFormats/interface/CMGTTbarJPsiCandidate.h"

#include "TTree.h"
#include "TFile.h"
#include <vector>

using namespace edm;
using namespace std;

class CMGTTbarJPsiGenFilter : public edm::EDFilter
{
public:
  CMGTTbarJPsiGenFilter(const edm::ParameterSet& pset);
  ~CMGTTbarJPsiGenFilter() {};

  void beginJob();
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};
  bool isLastQuark(const reco::GenParticle&, const int&);
  bool isFromtop(const reco::GenParticle&);

  string debug;

private:
  bool applyFilter_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;

  TTree* tree;
  double genLep1_pt;
  double genLep2_pt;
  double genbquark1_pt;
  double genbquark2_pt;
  double gentquark1_pt;
  double gentquark2_pt;
  double genbJet1_pt;
  double genbJet2_pt;
  double genpriJPsi_pt;
  double gensecJPsi_pt;
  double gentbJPsi_pt;
  double gentbJPsilp_pt;
  double gentbJPsilm_pt;
  double gentbbJPsi_pt;
  double gentbbJPsilp_pt;
  double gentbbJPsilm_pt;
/*  double genJPsi1_pt;
  double genJPsi2_pt;
  double genJPsiB1_pt;
  double genJPsiB2_pt;
  double genJPsiLep1P_pt;
  double genJPsiLep1M_pt;
  double genJPsiLep2P_pt;
  double genJPsiLep2M_pt;
*/
  double genbquark1_p;
  double genbquark2_p;
  double genbJet1_p;
  double genbJet2_p;
  double gentbJPsi_p;
  double gentbbJPsi_p;
/*  double genJPsiB1_p;
  double genJPsiB2_p;
*/
  double genLep1_eta;
  double genLep2_eta;
  double genbquark1_eta;
  double genbquark2_eta;
  double gentquark1_eta;
  double gentquark2_eta;
  double genbJet1_eta;
  double genbJet2_eta;
  double genpriJPsi_eta;
  double gensecJPsi_eta;
  double gentbJPsi_eta;
  double gentbJPsilp_eta;
  double gentbJPsilm_eta;
  double gentbbJPsi_eta;
  double gentbbJPsilp_eta;
  double gentbbJPsilm_eta;
/*  double genJPsi1_eta;
  double genJPsi2_eta;
  int    genJPsiB_ID;
  double genJPsiB1_eta;
  double genJPsiB2_eta;
  double genJPsiLep1P_eta;
  double genJPsiLep1M_eta;
  double genJPsiLep2P_eta;
  double genJPsiLep2M_eta;
*/
  double genLep1_phi;
  double genLep2_phi;
  double genbquark1_phi;
  double genbquark2_phi;
  double gentquark1_phi;
  double gentquark2_phi;
  double genbJet1_phi;
  double genbJet2_phi;
  double gentbJPsi_phi;
  double gentbJPsilp_phi;
  double gentbJPsilm_phi;
  double gentbbJPsi_phi;
  double gentbbJPsilp_phi;
  double gentbbJPsilm_phi;
/*  double genJPsi1_phi;
  double genJPsi2_phi;
  double genJPsiB1_phi;
  double genJPsiB2_phi;
  double genJPsiLep1P_phi;
  double genJPsiLep1M_phi;
  double genJPsiLep2P_phi;
  double genJPsiLep2M_phi;
*/
  double genbquark1_theta;
  double genbquark2_theta;
  double genbJet1_theta;
  double genbJet2_theta;

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
/*  double genJPsi1_mass;
  double genJPsi2_mass;*/
  double genlepJPsi1_mass;
  double genlepJPsi2_mass;

  int genNpJPsi;
  int genNbJPsi;
  int genNbQuarksTop;
  int genNbQuarks;
  int genNbJets;
  int genNbJetJPsi;
  int genNtbJPsi; 
  int genNtbJPsilp;
  int genNtbJPsilm;
  int genNtbbJPsi;
  int genNtbbJPsilp;
  int genNtbbJPsilm;

  int ttbarGen_dileptonic;
  int ttbarGen_mumu;
  int ttbarGen_muel;
  int ttbarGen_elel;

  /*
  TH1F* b_status3_daughterid;

  TH1F* b_from_top_pt;
  TH1F* b_from_top_multi;
  TH1F* b_from_top_motherid;
  TH1F* b_from_top_status;

  TH1F* b_from_nontop_pt;
  TH1F* b_from_nontop_multi;
  TH1F* b_from_nontop_motherid;
  TH1F* b_from_nontop_status;

  TH1F* b_multiplicity;
  */

/*  TH1F* h_multiplicity_bQuarks;
  TH1F* h_multiplicity_bGenJets;

  TH1F* h_multiplicity_bQuarks20;
  TH1F* h_multiplicity_bQuarks20DILVIS;
  TH1F* h_multiplicity_bQuarks20DILVISJPsi;

  TH1F* h_multiplicity_bGenJets20;
  TH1F* h_multiplicity_bGenJets20DILVIS;
  TH1F* h_multiplicity_bGenJets20DILVISJPsi;

  TH1F* h_multiplicity_GenJets;
  TH1F* h_multiplicity_GenJets10;
  TH1F* h_multiplicity_GenJets15;
  TH1F* h_multiplicity_GenJets20;
  TH1F* h_multiplicity_GenJets25;
  TH1F* h_multiplicity_GenJets30;

  TH1F* h_multiplicity_GenJetsDIL;
  TH1F* h_multiplicity_GenJets10DIL;
  TH1F* h_multiplicity_GenJets15DIL;
  TH1F* h_multiplicity_GenJets20DIL;
  TH1F* h_multiplicity_GenJets25DIL;
  TH1F* h_multiplicity_GenJets30DIL;

  TH1F* h_multiplicity_GenJetsDILVIS;
  TH1F* h_multiplicity_GenJets10DILVIS;
  TH1F* h_multiplicity_GenJets15DILVIS;
  TH1F* h_multiplicity_GenJets20DILVIS;
  TH1F* h_multiplicity_GenJets25DILVIS;
  TH1F* h_multiplicity_GenJets30DILVIS;

  TH1F* h_multiplicity_GenJetsDILVISJPsi;
  TH1F* h_multiplicity_GenJets10DILVISJPsi;
  TH1F* h_multiplicity_GenJets15DILVISJPsi;
  TH1F* h_multiplicity_GenJets20DILVISJPsi;
  TH1F* h_multiplicity_GenJets25DILVISJPsi;
  TH1F* h_multiplicity_GenJets30DILVISJPsi;
*/
  TH1F* h_nEvents;
  TH1F* h_nEvents_parton;

  TH1F* h_nEvents_inclusive;
  TH1F* h_nEvents_parton_inclusive;

  //std::vector<vallot::CMGTTbarJPsiCandidate>* ttbarGen;

};

CMGTTbarJPsiGenFilter::CMGTTbarJPsiGenFilter(const edm::ParameterSet& pset)
{
  applyFilter_= pset.getUntrackedParameter<bool>("applyFilter",false);
  genParticlesLabel_= pset.getParameter<edm::InputTag>("genParticlesLabel");
  genJetsLabel_= pset.getParameter<edm::InputTag>("genJetsLabel");

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Top quark study");

  /*
  b_from_top_pt  = fs->make<TH1F>( "b_from_top_pt"  , "p_{T}", 100,  0., 150. );
  b_from_top_multi  = fs->make<TH1F>( "b_from_top_multi"  , "Multiplicity", 10,  0, 10 );
  b_from_top_motherid  = fs->make<TH1F>( "b_from_top_motherid"  , "Mother PdgId", 3000,  0, 3000 );
  b_from_top_status  = fs->make<TH1F>( "b_from_top_status"  , "status", 10,  0, 10 );

  b_from_nontop_pt  = fs->make<TH1F>( "b_from_nontop_pt"  , "p_{T}", 100,  0., 150. );
  b_from_nontop_multi  = fs->make<TH1F>( "b_from_nontop_multi"  , "Multiplicity", 10,  0, 10 );
  b_from_nontop_motherid  = fs->make<TH1F>( "b_from_nontop_motherid"  , "Mother PdgId", 3000,  0, 3000 );
  b_from_nontop_status  = fs->make<TH1F>( "b_from_nontop_status"  , "status", 10,  0, 10 );

  b_multiplicity  = fs->make<TH1F>( "b_multiplicity"  , "Multiplicity", 10,  0, 10 );
  */

/*  h_multiplicity_bQuarks  = fs->make<TH1F>( "h_multiplicity_bQuarks"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets  = fs->make<TH1F>( "h_multiplicity_bGenJets"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_bQuarks20  = fs->make<TH1F>( "h_multiplicity_bQuarks20"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bQuarks20DILVIS  = fs->make<TH1F>( "h_multiplicity_bQuarks20DILVIS"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bQuarks20DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_bQuarks20DILVISJPsi"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_bGenJets20  = fs->make<TH1F>( "h_multiplicity_bGenJets20"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets20DILVIS  = fs->make<TH1F>( "h_multiplicity_bGenJets20DILVIS"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets20DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_bGenJets20DILVISJPsi"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_GenJets  = fs->make<TH1F>( "h_multiplicity_GenJets"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10  = fs->make<TH1F>( "h_multiplicity_GenJets10"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15  = fs->make<TH1F>( "h_multiplicity_GenJets15"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20  = fs->make<TH1F>( "h_multiplicity_GenJets20"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25  = fs->make<TH1F>( "h_multiplicity_GenJets25"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30  = fs->make<TH1F>( "h_multiplicity_GenJets30"  , "Multiplicity", 12,  0, 12 );
  
  h_multiplicity_GenJetsDIL  = fs->make<TH1F>( "h_multiplicity_GenJetsDIL"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DIL  = fs->make<TH1F>( "h_multiplicity_GenJets10DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DIL  = fs->make<TH1F>( "h_multiplicity_GenJets15DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DIL  = fs->make<TH1F>( "h_multiplicity_GenJets20DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DIL  = fs->make<TH1F>( "h_multiplicity_GenJets25DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DIL  = fs->make<TH1F>( "h_multiplicity_GenJets30DIL"  , "Multiplicity", 12,  0, 12 );

  h_multiplicity_GenJetsDILVIS  = fs->make<TH1F>( "h_multiplicity_GenJetsDILVIS"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets10DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets15DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets20DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets25DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets30DILVIS"  , "Multiplicity", 12,  0, 12 );

  h_multiplicity_GenJetsDILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJetsDILVISJPsi"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJets10DILVISJPsi"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJets15DILVISJPsi"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJets20DILVISJPsi"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJets25DILVISJPsi"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DILVISJPsi  = fs->make<TH1F>( "h_multiplicity_GenJets30DILVISJPsi"  , "Multiplicity", 12,  0, 12 );
*/
  h_nEvents = fs->make<TH1F>( "h_nEvents"  , "h_nEvents", 6,  0, 6 );
  h_nEvents_parton = fs->make<TH1F>( "h_nEvents_parton"  , "h_nEvents_parton", 6,  0, 6 );

  h_nEvents_inclusive = fs->make<TH1F>( "h_nEvents_inclusive"  , "h_nEvents", 6,  0, 6 );
  h_nEvents_parton_inclusive = fs->make<TH1F>( "h_nEvents_parton_inclusive"  , "h_nEvents_parton", 6,  0, 6 );

  //ttbarGen = new std::vector<vallot::CMGTTbarJPsiCandidate>();
}

void CMGTTbarJPsiGenFilter::beginJob(){
  //tree->Branch("ttbarGen","std::vector<vallot::CMGTTbarJPsiCandidate>", &ttbarGen);
  tree->Branch("genLep1_pt",&genLep1_pt,"genLep1_pt/d");
  tree->Branch("genLep2_pt",&genLep2_pt,"genLep2_pt/d");
  tree->Branch("genbquark1_pt",&genbquark1_pt,"genbquark1_pt/d");
  tree->Branch("genbquark2_pt",&genbquark2_pt,"genbquark2_pt/d");
  tree->Branch("gentquark1_pt",&gentquark1_pt,"gentquark1_pt/d");
  tree->Branch("gentquark2_pt",&gentquark2_pt,"gentquark2_pt/d");
  tree->Branch("genbJet1_pt",&genbJet1_pt,"genbJet1_pt/d");
  tree->Branch("genbJet2_pt",&genbJet2_pt,"genbJet2_pt/d");
  tree->Branch("genpriJPsi_pt",&genpriJPsi_pt,"genpriJPsi_pt/d");
  tree->Branch("gensecJPsi_pt",&gensecJPsi_pt,"gensecJPsi_pt/d");
  tree->Branch("gentbJPsi_pt",&gentbJPsi_pt,"gentbJPsi_pt/d");
  tree->Branch("gentbJPsilp_pt",&gentbJPsilp_pt,"gentbJPsilp_pt/d");
  tree->Branch("gentbJPsilm_pt",&gentbJPsilm_pt,"gentbJPsilm_pt/d");
  tree->Branch("gentbbJPsi_pt",&gentbbJPsi_pt,"gentbbJPsi_pt/d");
  tree->Branch("gentbbJPsilp_pt",&gentbbJPsilp_pt,"gentbbJPsilp_pt/d");
  tree->Branch("gentbbJPsilm_pt",&gentbbJPsilm_pt,"gentbbJPsilm_pt/d");
/*  tree->Branch("genJPsi1_pt",&genJPsi1_pt,"genJPsi1_pt/d");
  tree->Branch("genJPsi2_pt",&genJPsi2_pt,"genJPsi2_pt/d");
  tree->Branch("genJPsiB1_pt",&genJPsiB1_pt,"genJPsiB1_pt/d");
  tree->Branch("genJPsiB2_pt",&genJPsiB2_pt,"genJPsiB2_pt/d");
  tree->Branch("genJPsiLep1P_pt",&genJPsiLep1P_pt,"genJPsiLep1P_pt/d");
  tree->Branch("genJPsiLep1M_pt",&genJPsiLep1M_pt,"genJPsiLep1M_pt/d");
  tree->Branch("genJPsiLep2P_pt",&genJPsiLep2P_pt,"genJPsiLep2P_pt/d");
  tree->Branch("genJPsiLep2M_pt",&genJPsiLep2M_pt,"genJPsiLep2M_pt/d");*/

  tree->Branch("genLep1_eta",&genLep1_eta,"genLep1_eta/d");
  tree->Branch("genLep2_eta",&genLep2_eta,"genLep2_eta/d");
  tree->Branch("genbquark1_eta",&genbquark1_eta,"genbquark1_eta/d");
  tree->Branch("genbquark2_eta",&genbquark2_eta,"genbquark2_eta/d");
  tree->Branch("gentquark1_eta",&gentquark1_eta,"gentquark1_eta/d");
  tree->Branch("gentquark2_eta",&gentquark2_eta,"gentquark2_eta/d");
  tree->Branch("genbJet1_eta",&genbJet1_eta,"genbJet1_eta/d");
  tree->Branch("genbJet2_eta",&genbJet2_eta,"genbJet2_eta/d");
  tree->Branch("genpriJPsi_eta",&genpriJPsi_eta,"genpriJPsi_eta/d");
  tree->Branch("gensecJPsi_eta",&gensecJPsi_eta,"gensecJPsi_eta/d");
  tree->Branch("gentbJPsi_eta",&gentbJPsi_eta,"gentbJPsi_eta/d");
  tree->Branch("gentbJPsilp_eta",&gentbJPsilp_eta,"gentbJPsilp_eta/d");
  tree->Branch("gentbJPsilm_eta",&gentbJPsilm_eta,"gentbJPsilm_eta/d");
  tree->Branch("gentbbJPsi_eta",&gentbbJPsi_eta,"gentbbJPsi_eta/d");
  tree->Branch("gentbbJPsilp_eta",&gentbbJPsilp_eta,"gentbbJPsilp_eta/d");
  tree->Branch("gentbbJPsilm_eta",&gentbbJPsilm_eta,"gentbbJPsilm_eta/d");
/*  tree->Branch("genJPsi1_eta",&genJPsi1_eta,"genJPsi1_eta/d");
  tree->Branch("genJPsi2_eta",&genJPsi2_eta,"genJPsi2_eta/d");
  tree->Branch("genJPsiB_ID",&genJPsiB_ID,"genJPsiB_ID/I");
  tree->Branch("genJPsiB1_eta",&genJPsiB1_eta,"genJPsiB1_eta/d");
  tree->Branch("genJPsiB2_eta",&genJPsiB2_eta,"genJPsiB2_eta/d");
  tree->Branch("genJPsiLep1P_eta",&genJPsiLep1P_eta,"genJPsiLep1P_eta/d");
  tree->Branch("genJPsiLep1M_eta",&genJPsiLep1M_eta,"genJPsiLep1M_eta/d");
  tree->Branch("genJPsiLep2P_eta",&genJPsiLep2P_eta,"genJPsiLep2P_eta/d");
  tree->Branch("genJPsiLep2M_eta",&genJPsiLep2M_eta,"genJPsiLep2M_eta/d");*/

  tree->Branch("genLep1_phi",&genLep1_phi,"genLep1_phi/d");
  tree->Branch("genLep2_phi",&genLep2_phi,"genLep2_phi/d");
  tree->Branch("genbquark1_phi",&genbquark1_phi,"genbquark1_phi/d");
  tree->Branch("genbquark2_phi",&genbquark2_phi,"genbquark2_phi/d");
  tree->Branch("gentquark1_phi",&gentquark1_phi,"gentquark1_phi/d");
  tree->Branch("gentquark2_phi",&gentquark2_phi,"gentquark2_phi/d");
  tree->Branch("genbJet1_phi",&genbJet1_phi,"genbJet1_phi/d");
  tree->Branch("genbJet2_phi",&genbJet2_phi,"genbJet2_phi/d");
  tree->Branch("gentbJPsi_phi",&gentbJPsi_phi,"gentbJPsi_phi/d");
  tree->Branch("gentbJPsilp_phi",&gentbJPsilp_phi,"gentbJPsilp_phi/d");
  tree->Branch("gentbJPsilm_phi",&gentbJPsilm_phi,"gentbJPsilm_phi/d");
  tree->Branch("gentbbJPsi_phi",&gentbbJPsi_phi,"gentbbJPsi_phi/d");
  tree->Branch("gentbbJPsilp_phi",&gentbbJPsilp_phi,"gentbbJPsilp_phi/d");
  tree->Branch("gentbbJPsilm_phi",&gentbbJPsilm_phi,"gentbbJPsilm_phi/d");
/*  tree->Branch("genJPsi1_phi",&genJPsi1_phi,"genJPsi1_phi/d");
  tree->Branch("genJPsi2_phi",&genJPsi2_phi,"genJPsi2_phi/d");
  tree->Branch("genJPsiB1_phi",&genJPsiB1_phi,"genJPsiB1_phi/d");
  tree->Branch("genJPsiB2_phi",&genJPsiB2_phi,"genJPsiB2_phi/d");
  tree->Branch("genJPsiLep1P_phi",&genJPsiLep1P_phi,"genJPsiLep1P_phi/d");
  tree->Branch("genJPsiLep1M_phi",&genJPsiLep1M_phi,"genJPsiLep1M_phi/d");
  tree->Branch("genJPsiLep2P_phi",&genJPsiLep2P_phi,"genJPsiLep2P_phi/d");
  tree->Branch("genJPsiLep2M_phi",&genJPsiLep2M_phi,"genJPsiLep2M_phi/d");*/

  tree->Branch("genbquark1_p",&genbquark1_p,"genbquark1_p/d");
  tree->Branch("genbquark2_p",&genbquark2_p,"genbquark2_p/d");
  tree->Branch("genbJet1_p",&genbJet1_p,"genbJet1_p/d");
  tree->Branch("genbJet2_p",&genbJet2_p,"genbJet2_p/d");
/*  tree->Branch("genJPsi1_p",&genJPsi1_p,"genJPsi1_p/d");
  tree->Branch("genJPsi2_p",&genJPsi2_p,"genJPsi2_p/d");
  tree->Branch("genJPsiB1_p",&genJPsiB1_p,"genJPsiB1_p/d");
  tree->Branch("genJPsiB2_p",&genJPsiB2_p,"genJPsiB2_p/d");*/

  tree->Branch("genbquark1_theta",&genbquark1_theta,"genbquark1_theta/d");
  tree->Branch("genbquark2_theta",&genbquark2_theta,"genbquark2_theta/d");
  tree->Branch("genbJet1_theta",&genbJet1_theta,"genbJet1_theta/d");
  tree->Branch("genbJet2_theta",&genbJet2_theta,"genbJet2_theta/d");

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
//  tree->Branch("genJPsi1_mass",&genJPsi1_mass,"genJPsi1_mass/d");
//  tree->Branch("genJPsi2_mass",&genJPsi2_mass,"genJPsi2_mass/d");
  tree->Branch("genlepJPsi1_mass",&genlepJPsi1_mass,"genlepJPsi1_mass/d");
  tree->Branch("genlepJPsi2_mass",&genlepJPsi2_mass,"genlepJPsi2_mass/d");

  tree->Branch("genNpJPsi",&genNpJPsi,"genNpJPsi/d");
  tree->Branch("genNbJPsi",&genNbJPsi,"genNbJPsi/d");
  tree->Branch("genNbQuarksTop",&genNbQuarksTop,"genNbQuarksTop/d");
  tree->Branch("genNbQuarks",&genNbQuarks,"genNbQuarks/d");
  tree->Branch("genNbJets",&genNbJets,"genNbJets/d");
  tree->Branch("genNbJetJPsi",&genNbJetJPsi,"genNbJetJPsi/d");
  tree->Branch("genNtbJPsi",&genNtbJPsi,"genNtbJPsi/d");
  tree->Branch("genNtbJPsilp",&genNtbJPsilp,"genNtbJPsilp/d");
  tree->Branch("genNtbJPsilm",&genNtbJPsilm,"genNtbJPsilm/d");
  tree->Branch("genNtbbJPsi",&genNtbbJPsi,"genNtbbJPsi/d");
  tree->Branch("genNtbbJPsilp",&genNtbbJPsilp,"genNtbbJPsilp/d");
  tree->Branch("genNtbbJPsilm",&genNtbbJPsilm,"genNtbbJPsilm/d");

  tree->Branch("ttbarGen_dileptonic",&ttbarGen_dileptonic,"ttbarGen_dileptonic/d");
  tree->Branch("ttbarGen_mumu",&ttbarGen_mumu,"ttbarGen_mumu/d");
  tree->Branch("ttbarGen_muel",&ttbarGen_muel,"ttbarGen_muel/d");
  tree->Branch("ttbarGen_elel",&ttbarGen_elel,"ttbarGen_elel/d");

}

bool CMGTTbarJPsiGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{
  const bool isRealData = iEvent.isRealData();

  if (isRealData )
    return true;

  //ttbarGen->clear();
  genLep1_pt = -1;
  genLep2_pt = -1;
  genbquark1_pt = -1;
  genbquark2_pt = -1;
  gentquark1_pt = -1;
  gentquark2_pt = -1;
  genbJet1_pt = -1;
  genbJet2_pt = -1;
  genpriJPsi_pt = -1;
  gensecJPsi_pt = -1;
  gentbJPsi_pt = -1;
  gentbJPsilp_pt = -1;
  gentbJPsilm_pt = -1;
  gentbbJPsi_pt = -1;
  gentbbJPsilp_pt = -1;
  gentbbJPsilm_pt = -1;
/*  genJPsi1_pt = -1;
  genJPsi2_pt = -1;
  genJPsiB1_pt = -1;
  genJPsiB2_pt = -1;
  genJPsiLep1P_pt = -1;
  genJPsiLep1M_pt = -1;
  genJPsiLep2P_pt = -1;
  genJPsiLep2M_pt = -1;
*/
  genbquark1_p = -1;
  genbquark2_p = -1;
  genbJet1_p = -1;
  genbJet2_p = -1;
/*  genJPsi1_p = -1;
  genJPsi2_p = -1;
  genJPsiB1_p = -1;
  genJPsiB2_p = -1;
*/
  genLep1_eta = -999;
  genLep2_eta = -999;
  genbquark1_eta = -999;
  genbquark2_eta = -999;
  gentquark1_eta = -999;
  gentquark2_eta = -999;
  genbJet1_eta = -999;
  genbJet2_eta = -999;
  genpriJPsi_eta = -999;
  gensecJPsi_eta = -999;
  gentbJPsi_eta = -999;
  gentbJPsilp_eta = -999;
  gentbJPsilm_eta = -999;
  gentbbJPsi_eta = -999;
  gentbbJPsilp_eta = -999;
  gentbbJPsilm_eta = -999;
/*  genJPsi1_eta = -999;
  genJPsi2_eta = -999;
  genJPsiB_ID = 0;
  genJPsiB1_eta = -999;
  genJPsiB2_eta = -999;
  genJPsiLep1P_eta = -999;
  genJPsiLep1M_eta = -999;
  genJPsiLep2P_eta = -999;
  genJPsiLep2M_eta = -999;
*/
  gentbJPsi_phi = -999;
  gentbJPsilp_phi = -999;
  gentbJPsilm_phi = -999;
  gentbbJPsi_phi = -999;
  gentbbJPsilp_phi = -999;
  gentbbJPsilm_phi = -999;
  //genJPsi1_phi = -999;
  //genJPsi2_phi = -999;
  genLep1_phi = -999;
  genLep2_phi = -999;
  genbquark1_phi = -999;
  genbquark2_phi = -999;
  gentquark1_phi = -999;
  gentquark2_phi = -999;
  genbJet1_phi = -999;
  genbJet2_phi = -999;
/*  genJPsiB1_phi = -999;
  genJPsiB2_phi = -999;
  genJPsiLep1P_phi = -999;
  genJPsiLep1M_phi = -999;
  genJPsiLep2P_phi = -999;
  genJPsiLep2M_phi = -999;
*/
  genbquark1_theta = -999;
  genbquark2_theta = -999;
  genbJet1_theta = -999;
  genbJet2_theta = -999;

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
  //genJPsi1_mass = -1;
  //genJPsi2_mass = -1;
  genlepJPsi1_mass = -1;
  genlepJPsi2_mass = -1;

  genNpJPsi = -1;
  genNbJPsi = -1;
  genNbQuarksTop = -1;
  genNbQuarks = -1;
  genNbJets = -1;
  genNbJetJPsi = -1;
  genNtbJPsi = -1;
  genNtbJPsilp = -1;
  genNtbJPsilm = -1;
  genNtbbJPsi = -1;
  genNtbbJPsilp = -1;
  genNtbbJPsilm = -1;

  ttbarGen_dileptonic = -1;
  ttbarGen_mumu = -1;
  ttbarGen_muel = -1;
  ttbarGen_elel = -1;

  bool accepted = false;

  using namespace std;
  using namespace edm;
  using namespace reco;
  debug = "";
  debug += "---------EVENT start---------\n" ;

  edm::Handle<std::vector<cmg::GenJet> > genJets_;
  iEvent.getByLabel(genJetsLabel_,genJets_);

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  const reco::GenParticleCollection* myGenParticles = 0;
  myGenParticles = &(*genParticles_);

  /*

  unsigned int nParticles = myGenParticles->size();

  int nb_from_top = 0;
  int nb_from_nontop = 0;
  int nb = 0;

  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    const reco::GenParticle& p = (*myGenParticles)[ip];
   
    if ( abs(p.pdgId()) != 5 ) continue;
    bool isLast = isLastQuark(p, 5);
    if (isLast != true) continue;
 
    int status = p.status();

    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
    int motherAbsPdgId = abs(mother->pdgId());

    bool isfromtop = isFromtop(p);

    if( !isfromtop ) {  
      b_from_nontop_status->Fill(status);
      b_from_nontop_motherid->Fill(motherAbsPdgId);
      b_from_nontop_pt->Fill(p.pt());
      nb_from_nontop++ ;
    }else{
      b_from_top_status->Fill(status);
      b_from_top_motherid->Fill(motherAbsPdgId);
      b_from_top_pt->Fill(p.pt());
      nb_from_top++  ;
    }

    nb++;
  }

  b_multiplicity->Fill(nb);
  */

  //gen information
  vallot::CMGTTbarJPsiCandidate ttbarGenLevel;

  if(genJets_.isValid()){
    const std::vector<cmg::GenJet>* myGenJets = 0;
    myGenJets = &(*genJets_);

    ttbarGenLevel.building(myGenJets, myGenParticles);

    //ttbarGen->push_back(ttbarGenLevel);
    genLep1_pt = ttbarGenLevel.lepton1().pt();
    genLep2_pt = ttbarGenLevel.lepton2().pt();
    genLep1_eta = ttbarGenLevel.lepton1().eta();
    genLep2_eta = ttbarGenLevel.lepton2().eta();
    genLep1_phi = ttbarGenLevel.lepton1().phi();
    genLep2_phi = ttbarGenLevel.lepton2().phi();

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
    genbquark1_p = ttbarGenLevel.bquarks1().P();
    genbquark2_p = ttbarGenLevel.bquarks2().P();
    genbquark1_theta = ttbarGenLevel.bquarks1().theta();
    genbquark2_theta = ttbarGenLevel.bquarks2().theta();

    genbJet1_eta = ttbarGenLevel.bJets1().eta();
    genbJet2_eta = ttbarGenLevel.bJets2().eta();
    genbJet1_pt = ttbarGenLevel.bJets1().pt();
    genbJet2_pt = ttbarGenLevel.bJets2().pt();
    genbJet1_phi = ttbarGenLevel.bJets1().phi();
    genbJet2_phi = ttbarGenLevel.bJets2().phi();
    genbJet1_p = ttbarGenLevel.bJets1().P();
    genbJet2_p = ttbarGenLevel.bJets2().P();
    genbJet1_theta = ttbarGenLevel.bJets1().theta();
    genbJet2_theta = ttbarGenLevel.bJets2().theta();

    genpriJPsi_mass = ttbarGenLevel.priJPsi().mass();
    gensecJPsi_mass = ttbarGenLevel.secJPsi().mass();
    genpriJPsi_eta = ttbarGenLevel.priJPsi().eta();
    gensecJPsi_eta = ttbarGenLevel.secJPsi().eta();
    genpriJPsi_pt = ttbarGenLevel.priJPsi().pt();
    gensecJPsi_pt = ttbarGenLevel.secJPsi().pt();
    genpriJPsi_3Dl = ttbarGenLevel.priJPsi3DlTrue();
    gensecJPsi_3Dl = ttbarGenLevel.secJPsi3DlTrue();
    genpriJPsi_ppdl = ttbarGenLevel.priJPsippdlTrue();
    gensecJPsi_ppdl = ttbarGenLevel.secJPsippdlTrue();
    genNpJPsi = ttbarGenLevel.NpJPsi();
    genNbJPsi = ttbarGenLevel.NbJPsi();
    genNbQuarksTop = ttbarGenLevel.NbQuarksTop();
    genNbQuarks = ttbarGenLevel.NbQuarks();
    genNbJets = ttbarGenLevel.NbJets();
    //genNbJetJPsi = ttbarGenLevel.NbJetJPsi();

    gentbJPsi_pt = ttbarGenLevel.tbJPsi().pt();
    gentbJPsilp_pt = ttbarGenLevel.tbJPsilp().pt();
    gentbJPsilm_pt = ttbarGenLevel.tbJPsilm().pt();
    gentbbJPsi_pt = ttbarGenLevel.tbbJPsi().pt();
    //if(gentbbJPsi_pt!=0) cout<<"gentbbJPsi_pt : " <<gentbbJPsi_pt<<endl;
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

    gentbJPsi_3Dl = ttbarGenLevel.tbJPsi3DlTrue();
    gentbbJPsi_3Dl = ttbarGenLevel.tbbJPsi3DlTrue();
    gentbJPsi_ppdl = ttbarGenLevel.tbJPsippdlTrue();
    gentbbJPsi_ppdl = ttbarGenLevel.tbbJPsippdlTrue();
    gentbJPsi_dtheta = ttbarGenLevel.tbJPsidthetaTrue();
    gentbbJPsi_dtheta = ttbarGenLevel.tbbJPsidthetaTrue();

/*    genJPsi1_mass = ttbarGenLevel.JPsi1().mass();
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

    genlepJPsi1_mass = ttbarGenLevel.lepJPsi1().mass();
    genlepJPsi2_mass = ttbarGenLevel.lepJPsi2().mass();

    genJPsiB_ID = ttbarGenLevel.JPsiBID();
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
    ttbarGen_dileptonic = ttbarGenLevel.diLeptonic();
    ttbarGen_mumu = ttbarGenLevel.diLeptonicMuoMuo();
    ttbarGen_muel = ttbarGenLevel.diLeptonicMuoEle();
    ttbarGen_elel = ttbarGenLevel.diLeptonicEleEle();

    /*bool dil = ttbarGenLevel.diLeptonic() == 1 ;
    bool vis = ttbarGenLevel.lepton1().pt() > 20 && abs(ttbarGenLevel.lepton1().eta()) < 2.5 && ttbarGenLevel.lepton2().pt() > 20 && abs(ttbarGenLevel.lepton2().eta()) < 2.5 && ttbarGenLevel.NbJets20() >= 1;
    bool nbjets1 = ttbarGenLevel.NbJets20() >= 1;
    bool njets1 = ttbarGenLevel.NJets20() >= 1;
    bool JPsi = ttbarGenLevel.NbJetJPsi() >= 1;

    bool nbpartons1 = ttbarGenLevel.NbQuarks20() >= 1;
    bool vis_parton = ttbarGenLevel.lepton1().pt() > 20 && abs(ttbarGenLevel.lepton1().eta()) < 2.5 && ttbarGenLevel.lepton2().pt() > 20 && abs(ttbarGenLevel.lepton2().eta()) < 2.5 && ttbarGenLevel.NbQuarks20() >= 1;
    bool JPsi_parton = ttbarGenLevel.NbQuarks20() >= 1;

    h_multiplicity_bQuarks->Fill( ttbarGenLevel.NbQuarks() ) ;
    h_multiplicity_bQuarks20->Fill( ttbarGenLevel.NbQuarks20() ) ;
    if( dil && vis ) h_multiplicity_bQuarks20DILVIS->Fill( ttbarGenLevel.NbQuarks20() );
    if( dil && vis && JPsi) h_multiplicity_bQuarks20DILVISJPsi->Fill( ttbarGenLevel.NbQuarks20() );
    h_multiplicity_bGenJets->Fill( ttbarGenLevel.NbJets() );
    h_multiplicity_bGenJets20->Fill( ttbarGenLevel.NbJets20() );
    if( dil && vis ) h_multiplicity_bGenJets20DILVIS->Fill( ttbarGenLevel.NbJets20() );
    if( dil && vis && JPsi ) h_multiplicity_bGenJets20DILVISJPsi->Fill( ttbarGenLevel.NbJets20() );

    h_nEvents->Fill(0);
    if( dil ) h_nEvents->Fill(1);
    if( dil && vis ) h_nEvents->Fill(2);
    if( dil && vis && njets1  ) h_nEvents->Fill(3);
    if( dil && vis && njets1 && JPsi  ) h_nEvents->Fill(4);
    //if( dil && vis && njets4 && !ttbb && ttcc  ) h_nEvents->Fill(5);

    if( njets1 && nbjets1 ) h_nEvents_inclusive->Fill(0);
    if( njets1 && nbjets1 && JPsi  ) h_nEvents_inclusive->Fill(1);
    if( dil && nbjets1 && njets1  ) h_nEvents_inclusive->Fill(2);
    if( dil && nbjets1 && njets1 && JPsi  ) h_nEvents_inclusive->Fill(3);
    if( vis && njets1  ) h_nEvents_inclusive->Fill(4);
    if( vis && njets1 && JPsi ) h_nEvents_inclusive->Fill(5);

    h_nEvents_parton->Fill(0);
    if( dil ) h_nEvents_parton->Fill(1);
    if( dil && vis_parton ) h_nEvents_parton->Fill(2);
    if( dil && vis_parton && njets1  ) h_nEvents_parton->Fill(3);
    if( dil && vis_parton && njets1 && JPsi_parton  ) h_nEvents_parton->Fill(4);
    //if( dil && vis_parton && njets4 && !ttbb_parton && ttcc  ) h_nEvents_parton->Fill(5);    

    if( njets1 && nbpartons1 ) h_nEvents_parton_inclusive->Fill(0);
    if( njets1 && nbpartons1 && JPsi_parton  ) h_nEvents_parton_inclusive->Fill(1);
    if( dil && nbpartons1 && njets1  ) h_nEvents_parton_inclusive->Fill(2);
    if( dil && nbpartons1 && njets1 && JPsi_parton  ) h_nEvents_parton_inclusive->Fill(3);
    if( vis_parton && njets1  ) h_nEvents_parton_inclusive->Fill(4);
    if( vis_parton && njets1 && JPsi_parton  ) h_nEvents_parton_inclusive->Fill(5);
 
    h_multiplicity_GenJets->Fill( ttbarGenLevel.NJets() );
    h_multiplicity_GenJets10->Fill( ttbarGenLevel.NJets10() );
    h_multiplicity_GenJets15->Fill( ttbarGenLevel.NJets15() );
    h_multiplicity_GenJets20->Fill( ttbarGenLevel.NJets20() );
    h_multiplicity_GenJets25->Fill( ttbarGenLevel.NJets25() );
    h_multiplicity_GenJets30->Fill( ttbarGenLevel.NJets30() );

    if( dil ){
      h_multiplicity_GenJetsDIL->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DIL->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DIL->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DIL->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DIL->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DIL->Fill( ttbarGenLevel.NJets30() );
    }

   if( dil && vis ){
      h_multiplicity_GenJetsDILVIS->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DILVIS->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DILVIS->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DILVIS->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DILVIS->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DILVIS->Fill( ttbarGenLevel.NJets30() );
    }

    if( dil && vis && JPsi ){
      h_multiplicity_GenJetsDILVISJPsi->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DILVISJPsi->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DILVISJPsi->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DILVISJPsi->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DILVISJPsi->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DILVISJPsi->Fill( ttbarGenLevel.NJets30() );
    }*/

  }

  //if( nb_from_top <=2 && nb_from_nontop <=0){
  //  accepted = false;
  //}
  //else {
    //more than 2 b-quarks are from top. But it will be considered as tt+bb.
  //  accepted = true;
  //}

  //b_from_top_multi->Fill(nb_from_top);
  //b_from_nontop_multi->Fill(nb_from_nontop);

  if( ttbarGenLevel.NbJets20() >= 1 ) accepted = true;

  tree->Fill();

  if(!applyFilter_) return true;  
  else return accepted;

}

bool CMGTTbarJPsiGenFilter::isLastQuark( const reco::GenParticle& p, const int & pdgId ){
   bool out = true;

   unsigned int nDaughters = p.numberOfDaughters();
   for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
     const reco::Candidate* daugh = p.daughter(iDaughter);
     if( abs(daugh->pdgId()) == pdgId) {
       out = false;
       break;
     }
   }

   return out;
}

bool CMGTTbarJPsiGenFilter::isFromtop( const reco::GenParticle& p){
  bool out = false;
  string tmp = "";
  tmp += "Let's study this b quark \n";
  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  tmp += "pt = " + pt + " id= " + pdgid + "\n";
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    tmp += "mother pdgid= " + id + " pt= " + mopt +"\n";
    if( abs(mother->pdgId()) == 6 ) { 
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }
 
  if(out) debug += tmp; 
  return out;
}

DEFINE_FWK_MODULE(CMGTTbarJPsiGenFilter);

