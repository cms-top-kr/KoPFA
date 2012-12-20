#ifndef KoPFA_CommonTools_cmgEMuonIsoAnalyzer_h
#define KoPFA_CommonTools_cmgEMuonIsoAnalyzer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "AnalysisDataFormats/CMGTools/interface/BaseMET.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "EGamma/EGammaAnalysisTools/interface/EGammaCutBasedEleId.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"

class cmgEMuonIsoAnalyzer : public edm::EDProducer
{
 public:

  explicit cmgEMuonIsoAnalyzer(const edm::ParameterSet&);
  ~cmgEMuonIsoAnalyzer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  bool trainTrigPresel(const cmg::Electron& ele, unsigned int numberOfHits);
  double transverseMass( const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& met);
  bool isFromWorZ( const reco::Candidate::LorentzVector& lepton, const edm::Handle<reco::GenParticleCollection> & genParticles );
  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj, const reco::Candidate::LorentzVector& proObj, bool exact ); 
  void endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup);

  edm::InputTag muonLabel_; 
  edm::InputTag electronLabel_; 
  edm::InputTag beamSpotLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;
  bool useZMassWindow_;
  bool applyPreTrigSel_;
  bool applyPFId_;
  bool qcdMC_;
  std::vector<std::string> bTagAlgos_;
  std::vector<std::string> bTagNames_;
  std::vector<double> bTagCutValues_;
  std::vector<bool> bTagIsCutMin_;
  std::vector<int> nbjets30_;
  unsigned int  numberOfHits_; 
  unsigned int  numberOfLeptons_; 
  unsigned int  numberOfJets_; 

  edm::Handle<reco::BeamSpot> beamSpot_;
  edm::Handle<reco::VertexCollection> recVtxs_;

  edm::Handle<std::vector<cmg::Muon> > muons_;
  edm::Handle<std::vector<cmg::Electron> > electrons_;
  edm::Handle<std::vector<cmg::PFJet> > Jets;
  edm::Handle<std::vector<cmg::BaseMET> > MET_;

  std::vector<std::string> filters_;
  TH1F * tmp;
  bool useEventCounter_;

  //muon loop
  //[i][j][k] : i=QCD, j=selection, k=region
  TH1F * h_pfRelIso02[3][5];
  TH1F * h_pfRelIso03[3][5];
  TH1F * h_pfRelIso04[3][5];
  TH1F * h_pfRelIso02db[3][5];
  TH1F * h_pfRelIso03db[3][5];
  TH1F * h_pfRelIso03dbmod[3][5];
  TH1F * h_pfRelIso04db[3][5];
  TH1F * h_dR[3][5];
  TH1F * h_pt[3][5];
  TH1F * h_eta[3][5];
  TH1F * h_pv[3][5];
  TH1F * h_njet[3][5];

  //event loop
  //[i] : i=QCD
  TH1F * h_mtW[3];
  TH1F * h_dimass[3];
  TH1F * h_nJet[3];
  TH1F * h_nMuon[3];
  TH1F * h_nElectron[3];
  TH1F * h_met[3];
  TH1F * h_delphi[3];
  TH1F * h_nbJet_CSVL[3];
  TH1F * h_nbJet_CSVM[3];
  TH1F * h_nbJet_CSVT[3];

  //pileup dependency
  TH2F * h2_pfRelIso02_vtx[3][5];
  TH2F * h2_pfRelIso03_vtx[3][5];
  TH2F * h2_pfRelIso04_vtx[3][5];
  TH2F * h2_pfRelIso02db_vtx[3][5];
  TH2F * h2_pfRelIso03db_vtx[3][5];
  TH2F * h2_pfRelIso04db_vtx[3][5];

  //pt dependency
  TH2F * h2_pfRelIso02_pt[3][5];
  TH2F * h2_pfRelIso03_pt[3][5];
  TH2F * h2_pfRelIso04_pt[3][5];
  TH2F * h2_pfRelIso02db_pt[3][5];
  TH2F * h2_pfRelIso03db_pt[3][5];
  TH2F * h2_pfRelIso04db_pt[3][5];

  //eta dependency
  TH2F * h2_pfRelIso02_eta[3][5];
  TH2F * h2_pfRelIso03_eta[3][5];
  TH2F * h2_pfRelIso04_eta[3][5];
  TH2F * h2_pfRelIso02db_eta[3][5];
  TH2F * h2_pfRelIso03db_eta[3][5];
  TH2F * h2_pfRelIso04db_eta[3][5];

  //dimass dependency
  TH2F * h2_pfRelIso02_dimass[3][5];
  TH2F * h2_pfRelIso03_dimass[3][5];
  TH2F * h2_pfRelIso04_dimass[3][5];
  TH2F * h2_pfRelIso02db_dimass[3][5];
  TH2F * h2_pfRelIso03db_dimass[3][5];
  TH2F * h2_pfRelIso04db_dimass[3][5];

  //QCD extraction
  TH2F * h2_SIGMuonsIso03;
  TH2F * h2_SIGMuonsPt;
  TH2F * h2_QCDMuonsIso03;
  TH2F * h2_QCDMuonsPt;
  TH2F * h2_ETCMuonsIso03;
  TH2F * h2_ETCMuonsPt;
  TRandom3 disc;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

/////

};


#endif

