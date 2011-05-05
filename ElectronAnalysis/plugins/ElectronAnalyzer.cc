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

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
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
  edm::InputTag genParticleLabel_;
  edm::InputTag electronLabel_;  
  edm::InputTag pfCandLabel_;

private:
  TTree* tree_;

  int event_, run_, lumi_;

  double genElePt_, genEleEta_, genElePhi_;
  double gsfElePt_, gsfEleEta_, gsfElePhi_;
  double pfaElePt_, pfaEleEta_, pfaElePhi_;

  double gsfEleEcalE_, pfaEleEcalE_;

  double chIso_, nhIso_, phIso_, pfaRelIso_;
  double tkIso_, ecIso_, hcIso_, detRelIso_;

  double idMVA_;
  int idCiCLoose_, idCiCMedium_, idCiCTight_;

  int isMatching_;

  TH1F * h_gsf_pt;
  TH1F * h_gsf_eta;
  TH1F * h_gsf_mva;

  TH1F * h_pf_pt;
  TH1F * h_pf_eta;
  TH1F * h_pf_mva;

private:
  typedef edm::View<reco::PFCandidate>::const_iterator PFCandIter;
  typedef edm::View<reco::GsfElectron>::const_iterator GsfEleIter;

  PFCandIter findElectron(const GsfEleIter gsfEle, edm::View<reco::PFCandidate> pfCandColl);
  GsfEleIter findElectron(const PFCandIter pfaEle, edm::View<reco::GsfElectron> gsfEleColl);
};

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getParameter<edm::InputTag>("electron");
  pfCandLabel_ = pset.getParameter<edm::InputTag>("pfCandidate");
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticles");
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

  tree_->Branch("genElePt", &genElePt_, "genElePt/d");
  tree_->Branch("genEleEta", &genEleEta_, "genEleEta/d");
  tree_->Branch("genElePhi", &genElePhi_, "genElePhi/d");

  tree_->Branch("gsfElePt", &gsfElePt_, "gsfElePt/d");
  tree_->Branch("gsfEleEta", &gsfEleEta_, "gsfEleEta/d");
  tree_->Branch("gsfElePhi", &gsfElePhi_, "gsfElePhi/d");

  tree_->Branch("pfaElePt", &pfaElePt_, "pfaElePt/d");
  tree_->Branch("pfaEleEta", &pfaEleEta_, "pfaEleEta/d");
  tree_->Branch("pfaElePhi", &pfaElePhi_, "pfaElePhi/d");

  tree_->Branch("gsfEleEcalE", &gsfEleEcalE_, "gsfEleEcalE/d");
  tree_->Branch("pfaEleEcalE", &pfaEleEcalE_, "pfaEleEcalE/d");

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

  tree_->Branch("isMatching", &isMatching_, "isMatching/i");

  //quick analysis
  h_gsf_pt = fs->make<TH1F>( "h_gsf_pt","h_gsf_pt", 50, 0,100);
  h_gsf_eta = fs->make<TH1F>( "h_gsf_eta","h_gsf_eta", 70, -3.5,3.5);
  h_gsf_mva = fs->make<TH1F>( "h_gsf_mva","h_gsf_mva", 40, -1,1);

  h_pf_pt = fs->make<TH1F>( "h_pf_pt","h_pf_pt", 50, 0,100);
  h_pf_eta = fs->make<TH1F>( "h_pf_eta","h_pf_eta", 70, -3.5,3.5);
  h_pf_mva = fs->make<TH1F>( "h_pf_mva","h_pf_mva", 40, -1,1);
  
}

void ElectronAnalyzer::endJob()
{

}

ElectronAnalyzer::PFCandIter ElectronAnalyzer::findElectron(const GsfEleIter gsfEle, edm::View<reco::PFCandidate> pfaEleCollection)
{
  reco::GsfTrackRef refTrk = gsfEle->gsfTrack();
  if ( refTrk.isNull() ) return pfaEleCollection.end();

  PFCandIter matchedEle = pfaEleCollection.end();

  for ( PFCandIter pfaEle = pfaEleCollection.begin(); 
        pfaEle != pfaEleCollection.end(); ++pfaEle )
  {
    if ( refTrk == pfaEle->gsfTrackRef() )
    {
      matchedEle = pfaEle;
      break;
    }
  }

  return matchedEle;
}

ElectronAnalyzer::GsfEleIter ElectronAnalyzer::findElectron(const PFCandIter pfaEle, edm::View<reco::GsfElectron> gsfEleCollection)
{
  reco::GsfTrackRef refTrk = pfaEle->gsfTrackRef();
  if ( refTrk.isNull() ) return gsfEleCollection.end();

  GsfEleIter matchedEle = gsfEleCollection.end();

  for ( GsfEleIter gsfEle = gsfEleCollection.begin();
      gsfEle != gsfEleCollection.end(); ++gsfEle )
  {
    if ( refTrk == gsfEle->gsfTrack() )
    {
      matchedEle = gsfEle;
      break;
    }
  }

  return matchedEle;
}

void ElectronAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  using namespace std;
  using namespace edm;

  event_ = event.id().event();
  run_ = event.id().run();
  lumi_ = event.id().luminosityBlock();

  edm::Handle<edm::View<reco::GenParticle> > genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);

  edm::Handle<edm::View<reco::GsfElectron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);

  edm::Handle<edm::View<reco::PFCandidate> > pfCandHandle;
  event.getByLabel(pfCandLabel_, pfCandHandle);

  // Set default values
  genElePt_ = genEleEta_ = genElePhi_ = -999;
  gsfElePt_ = gsfEleEta_ = gsfElePhi_ = -999;
  pfaElePt_ = pfaEleEta_ = pfaElePhi_ = -999;

  gsfEleEcalE_ = pfaEleEcalE_ = -999;
  isMatching_ = 0;

  // Choose leading gen electron
  if ( genParticleHandle.isValid() )
  {
    edm::View<reco::GenParticle>::const_iterator leadingGenEle = genParticleHandle->end();
    double leadingGenElePt = 0;
    for ( edm::View<reco::GenParticle>::const_iterator iGen = genParticleHandle->begin();
          iGen != genParticleHandle->end(); ++iGen )
    {
      if ( abs(iGen->pdgId()) != 11 or iGen->status() != 3 ) continue;

      if ( leadingGenElePt >= iGen->pt() ) continue;      
      leadingGenEle = iGen;
      leadingGenElePt = iGen->pt();
    }
    if ( leadingGenEle != genParticleHandle->end() )
    {
      genElePt_ = leadingGenEle->pt();
      genEleEta_ = leadingGenEle->eta();
      genElePhi_ = leadingGenEle->phi();
    }
  }

  // Choose leading electron
  edm::View<reco::GsfElectron>::const_iterator leadingGsfEle = electronHandle->end();
  double leadingGsfElePt = 0;
  for ( edm::View<reco::GsfElectron>::const_iterator iEle = electronHandle->begin();
      iEle != electronHandle->end(); ++iEle )
  {
    //Fill histograms
    h_gsf_pt->Fill(iEle->pt());
    h_gsf_eta->Fill(iEle->eta());
    h_gsf_mva->Fill(iEle->mva());

    if ( leadingGsfElePt >= iEle->pt() ) continue;
    leadingGsfElePt = iEle->pt();
    leadingGsfEle = iEle;
  }
  if ( leadingGsfEle != electronHandle->end() )
  {
    gsfElePt_ = leadingGsfEle->pt();
    gsfEleEta_ = leadingGsfEle->eta();
    gsfElePhi_ = leadingGsfEle->phi();

    gsfEleEcalE_ = leadingGsfEle->ecalEnergy();
  }

  // Choose leading PF electron
  edm::View<reco::PFCandidate>::const_iterator leadingPFEle = pfCandHandle->end();
  double leadingPFElePt = 0;
  for ( edm::View<reco::PFCandidate>::const_iterator iPFCand = pfCandHandle->begin();
      iPFCand != pfCandHandle->end(); ++iPFCand )
  {
    if ( abs(iPFCand->pdgId()) != 11 ) continue;
    //Fill histograms
    h_pf_pt->Fill(iPFCand->pt());
    h_pf_eta->Fill(iPFCand->eta());
    h_pf_mva->Fill(iPFCand->mva_e_pi());

    if ( leadingPFElePt >= iPFCand->pt() ) continue;
    leadingPFElePt = iPFCand->pt();
    leadingPFEle = iPFCand;
  }
  if ( leadingPFEle != pfCandHandle->end() )
  {
    pfaElePt_ = leadingPFEle->pt();
    pfaEleEta_ = leadingPFEle->eta();
    pfaElePhi_ = leadingPFEle->phi();

    pfaEleEcalE_ = leadingPFEle->ecalEnergy();
  }

  tree_->Fill();
}

DEFINE_FWK_MODULE(ElectronAnalyzer);

#endif

