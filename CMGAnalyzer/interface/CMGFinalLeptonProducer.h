#ifndef KoPFA_CommonTools_CMGFinalLeptonProducer_h
#define KoPFA_CommonTools_CMGFinalLeptonProducer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "KoPFA/CommonTools/interface/MuonIDSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatMuonSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"
#include "KoPFA/CommonTools/interface/LeptonIsoSelector.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class CMGFinalLeptonProducer : public edm::EDProducer
{
 public:

  explicit CMGFinalLeptonProducer(const edm::ParameterSet&);
  ~CMGFinalLeptonProducer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  edm::InputTag MuMuLep1Label_;
  edm::InputTag MuMuLep2Label_;
  edm::InputTag MuElLep1Label_;
  edm::InputTag MuElLep2Label_;
  edm::InputTag ElElLep1Label_;
  edm::InputTag ElElLep2Label_;
 
  edm::Handle<vector<cmg::Muon> > mmlep1_;
  edm::Handle<vector<cmg::Muon> > mmlep2_;
  edm::Handle<vector<cmg::Muon> > melep1_;
  edm::Handle<vector<cmg::Electron> > eelep1_;
  edm::Handle<vector<cmg::Electron> > eelep2_;
  edm::Handle<vector<cmg::Electron> > melep2_;

};


#endif

