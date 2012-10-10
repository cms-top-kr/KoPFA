#ifndef KoPFA_CommonTools_cmgElectronAnalyzer_h
#define KoPFA_CommonTools_cmgElectronAnalyzer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

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

class cmgElectronAnalyzer : public edm::EDProducer
{
 public:

  explicit cmgElectronAnalyzer(const edm::ParameterSet&);
  ~cmgElectronAnalyzer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  bool trainTrigPresel(const cmg::Electron& ele);
  double transverseMass( const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& met);
  bool PassWP(EgammaCutBasedEleId::WorkingPoint workingPoint, const cmg::Electron &ele,   const double &iso_ch,
                                         const double &iso_em,       const double &iso_nh,    const double &rho);
  bool isFromW( const reco::Candidate::LorentzVector& lepton, const edm::Handle<reco::GenParticleCollection> & genParticles );
  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj, const reco::Candidate::LorentzVector& proObj, bool exact ); 

  edm::InputTag electronLabel_; 
  edm::InputTag beamSpotLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag rhoIsoLabel_;
  bool  useZMassWindow_;

  edm::Handle<reco::BeamSpot> beamSpot_;
  edm::Handle<reco::VertexCollection> recVtxs_;

  edm::Handle<std::vector<cmg::Electron> > electrons_;
  edm::Handle<std::vector<cmg::PFJet> > Jets;
  edm::Handle<std::vector<cmg::BaseMET> > MET_;

  //electron loop
  //[i][j][k] : i=QCD, j=selection, k=region
  TH1F * h_mvaTrigV0[2][11][2];
  TH1F * h_pfRelIso03[2][11][2];
  TH1F * h_pfRelIso04[2][11][2];
  TH1F * h_pfRelIso03db[2][11][2];
  TH1F * h_pfRelIso04db[2][11][2];
  TH1F * h_pfRelIso03rho[2][11][2];
  TH1F * h_pfRelIso04rho[2][11][2];
  TH1F * h_dR[2][11][2];
  TH1F * h_pt[2][11][2];
  TH1F * h_eta[2][11][2];
  TH1F * h_pv[2][11][2];
  TH1F * h_njet[2][11][2];

  //event loop
  //[i] : i=QCD
  TH1F * h_mtW[2];
  TH1F * h_dimass[2];
  TH1F * h_nJet[2];
  TH1F * h_met[2];

  //pileup dependency
  TH2F * h2_mvaTrigV0[2][11][2];
  TH2F * h2_pfRelIso03[2][11][2];
  TH2F * h2_pfRelIso04[2][11][2];
  TH2F * h2_pfRelIso03db[2][11][2];
  TH2F * h2_pfRelIso04db[2][11][2];
  TH2F * h2_pfRelIso03rho[2][11][2];
  TH2F * h2_pfRelIso04rho[2][11][2];

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

/////
   enum CutType {
      DETAIN          = (1<<0),
      DPHIIN          = (1<<1),
      SIGMAIETAIETA   = (1<<2),
      HOE             = (1<<3),
      OOEMOOP         = (1<<4),
      D0VTX           = (1<<5),
      DZVTX           = (1<<6),
      ISO             = (1<<7),
      VTXFIT          = (1<<8),
      MHITS           = (1<<9)
   };
   static const unsigned int PassAll         = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | OOEMOOP | D0VTX | DZVTX | ISO | VTXFIT | MHITS;

};


#endif

