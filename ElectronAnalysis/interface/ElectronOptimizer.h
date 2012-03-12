#ifndef KoPFA_CommonTools_ElectronOptimizer_h
#define KoPFA_CommonTools_ElectronOptimizer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
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
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class ElectronOptimizer : public edm::EDAnalyzer
{
 public:

  explicit ElectronOptimizer(const edm::ParameterSet&);
  ~ElectronOptimizer();

  void beginJob();
  void analyze(const edm::Event&, const edm::EventSetup&);
  void endJob();

 private:
  double transverseMass( const reco::Candidate::LorentzVector& lepton,
                                     const reco::Candidate::LorentzVector& met);
  void endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup);
  
  edm::InputTag electronLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
 
  typedef pat::ElectronCollection::const_iterator MI;
  edm::Handle<pat::ElectronCollection> electrons_;
   edm::Handle<reco::VertexCollection> recVtxs_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  edm::Handle<pat::METCollection> pfMET;
  edm::Handle<pat::JetCollection> pfJet;

  std::vector<std::string> idNames_;

  bool useEventCounter_;
  std::vector<std::string> filters_;

  int RUN;
  int LUMI;
  int EVENT;

  int multiplicity;
  int nVertex;
  double mt;
  double MET;
  double dphi;
  int njets;
  double dimass;

  double ele1_mva;
  double ele2_mva;
  double ele1_pt;
  double ele2_pt;
  double ele1_eta;
  double ele2_eta;
  double ele1_chIso;
  double ele2_chIso;
  double ele1_nhIso;
  double ele2_nhIso;
  double ele1_phIso;
  double ele2_phIso;  
  double ele1_relIso;
  double ele2_relIso;  
  double ele1_relIso_dbeta;
  double ele2_relIso_dbeta;

  double ele1_charge;
  double ele2_charge;

  double ele1_reco_chIso;
  double ele2_reco_chIso;
  double ele1_reco_nhIso;
  double ele2_reco_nhIso;
  double ele1_reco_phIso;
  double ele2_reco_phIso;
  double ele1_reco_relIso;
  double ele2_reco_relIso;


  std::map<std::string, int> ele1_Id;
  std::map<std::string, int> ele2_Id;

  TH1F* tmp;

  TTree *tree;
};


#endif

