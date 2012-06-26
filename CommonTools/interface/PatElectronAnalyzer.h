#ifndef KoPFA_CommonTools_PatElectronAnalyzer_h
#define KoPFA_CommonTools_PatElectronAnalyzer_h

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

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class PatElectronAnalyzer : public edm::EDProducer
{
 public:

  explicit PatElectronAnalyzer(const edm::ParameterSet&);
  ~PatElectronAnalyzer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  bool trainTrigPresel(const reco::GsfElectron& ele);
  double transverseMass( const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& met);

  edm::InputTag electronLabel_; 
  edm::InputTag beamSpotLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag rhoIsoLabel_;

  typedef pat::ElectronCollection::const_iterator MI;
  typedef pat::JetCollection::const_iterator JI;

  edm::Handle<pat::ElectronCollection> electrons_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  edm::Handle<pat::JetCollection> Jets;
  edm::Handle<reco::VertexCollection> recVtxs_;
  edm::Handle<pat::METCollection> MET_;

  TH1F * h_mvaTrigV0[2][3][2];

  TH1F * h_pfRelIso03[2][3][2];
  TH1F * h_pfRelIso04[2][3][2];
  TH1F * h_pfRelIso03db[2][3][2];
  TH1F * h_pfRelIso04db[2][3][2];
  TH1F * h_pfRelIso03rho[2][3][2];
  TH1F * h_pfRelIso04rho[2][3][2];

  TH1F * h_mtW[2][3][2];
  TH1F * h_dimass[2][3][2];
  TH1F * h_nJet[2][3][2];
  TH1F * h_met[2][3][2];
  TH1F * h_dR[2][3][2];

  TH2F * h2_mvaTrigV0[2][3][2];
  TH2F * h2_pfRelIso03[2][3][2];
  TH2F * h2_pfRelIso04[2][3][2];
  TH2F * h2_pfRelIso03db[2][3][2];
  TH2F * h2_pfRelIso04db[2][3][2];
  TH2F * h2_pfRelIso03rho[2][3][2];
  TH2F * h2_pfRelIso04rho[2][3][2];


  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

};


#endif

