#ifndef KoPFA_ElectronAnalysis_ElectronAnalyzer_H
#define KoPFA_ElectronAnalysis_ElectronAnalyzer_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

#include <memory>

class ElectronAnalyzer : public edm::EDAnalyzer
{
public:
  ElectronAnalyzer(const edm::ParameterSet& pset);
  ~ElectronAnalyzer();

  void beginJob();
  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob();

private:
  edm::InputTag electronLabel_;  
  edm::InputTag pfCandLabel_;

private:
  TTree* tree_;

  int event_, run_, lumi_;

  double gsfElePt_, gsfEleEta_, gsfElePhi_;
  double pfElePt_, pfEleEta_, pfElePhi_;

  double chIso_, nhIso_, phIso_, pfaRelIso_;
  double tkIso_, ecIso_, hcIso_, detRelIso_;

  double idMVA_;
  int idCiCLoose_, idCiCMedium_, idCiCTight_;
};

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getParameter<edm::InputTag>("electron");
  pfCandLabel_ = pset.getParameter<edm::InputTag>("pfCandidate");
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "tree");

  tree_->Branch("event", &event_, "event/i");
  tree_->Branch("run", &run_, "run/i");
  tree_->Branch("lumi", &lumi_, "lumi/i");

  tree_->Branch("gsfElePt", &gsfElePt_, "gsfElePt/d");
  tree_->Branch("gsfEleEta", &gsfEleEta_, "gsfEleEta/d");
  tree_->Branch("gsfElePhi", &gsfElePhi_, "gsfElePhi/d");

  tree_->Branch("pfElePt", &pfElePt_, "pfElePt/d");
  tree_->Branch("pfEleEta", &pfEleEta_, "pfEleEta/d");
  tree_->Branch("pfElePhi", &pfElePhi_, "pfElePhi/d");

  tree_->Branch("chIso", &chIso_, "chIso/d");
  tree_->Branch("phIso", &phIso_, "phIso/d");
  tree_->Branch("nhIso", &nhIso_, "nhIso/d");
  tree_->Branch("pfaRelIso", &pfaRelIso_, "pfaRelIso/d");

  tree_->Branch("tkIso", &tkIso_, "tkIso/d");
  tree_->Branch("ecIso", &ecIso_, "ecIso/d");
  tree_->Branch("hcIso", &hcIso_, "hcIso/d");
  tree_->Branch("detRelIso", &detRelIso_, "detRelIso/d");

  tree_->Branch("idMVA", &idMVA_, "idMVA/d");
  tree_->Branch("idCiCLoose", &idCiCLoose_, "idCiCLoose/i");
  tree_->Branch("idCiCMedium", &idCiCMedium_, "idCiCMedium/i");
  tree_->Branch("idCiCTight", &idCiCTight_, "idCiCTight/i");
}

void ElectronAnalyzer::endJob()
{

}

void ElectronAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  using namespace std;
  using namespace edm;

  event_ = event.id().event();
  run_ = event.id().run();
  lumi_ = event.id().luminosityBlock();

  edm::Handle<edm::View<reco::GsfElectron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);

  edm::Handle<edm::View<reco::PFCandidate> > pfCandHandle;
  event.getByLabel(pfCandLabel_, pfCandHandle);

  // Choose leading electron
  edm::View<reco::GsfElectron>::const_iterator leadingGsfEle = electronHandle->end();
  double leadingGsfElePt = 0;
  for ( edm::View<reco::GsfElectron>::const_iterator iEle = electronHandle->begin();
        iEle != electronHandle->end(); ++iEle )
  {
    if ( leadingGsfElePt >= iEle->pt() ) continue;

    leadingGsfElePt = iEle->pt();
    leadingGsfEle = iEle;
  }
  if ( leadingGsfEle == electronHandle->end() )
  {
    cout << "Cannot set leading electron" << endl;
    return;
  }

  // Choose leading PF electron
  edm::View<reco::PFCandidate>::const_iterator leadingPFEle = pfCandHandle->end();
  double leadingPFElePt = 0;
  for ( edm::View<reco::PFCandidate>::const_iterator iPFCand = pfCandHandle->begin();
        iPFCand != pfCandHandle->end(); ++iPFCand )
  {
    if ( abs(iPFCand->pdgId()) != 11 ) continue;
    if ( leadingPFElePt >= iPFCand->pt() ) continue;

    leadingPFElePt = iPFCand->pt();
    leadingPFEle = iPFCand;
  }
  if ( leadingPFEle == pfCandHandle->end() )
  {
    cout << "Cannot match PFCand to electron" << endl;
    return;
  }

  // Fill up tree entries
  gsfElePt_ = leadingGsfEle->pt();
  gsfEleEta_ = leadingGsfEle->eta();
  gsfElePhi_ = leadingGsfEle->phi();

  pfElePt_ = leadingPFEle->pt();
  pfEleEta_ = leadingPFEle->eta();
  pfElePhi_ = leadingPFEle->phi();

  tree_->Fill();
}

DEFINE_FWK_MODULE(ElectronAnalyzer);

#endif

