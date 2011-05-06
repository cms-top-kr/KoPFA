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

  std::vector<double>* genElePt_;
  std::vector<double>* gsfElePt_;
  std::vector<double>* pfaElePt_;

  std::vector<double>* genEleEta_;
  std::vector<double>* gsfEleEta_;
  std::vector<double>* pfaEleEta_;

  std::vector<double>* genElePhi_;
  std::vector<double>* gsfElePhi_;
  std::vector<double>* pfaElePhi_;

  std::vector<double>* genEleE_;
  std::vector<double>* gsfEleE_;
  std::vector<double>* pfaEleE_;

  std::vector<double>* matchedPfaElePt_;
  std::vector<double>* matchedPfaEleEta_;
  std::vector<double>* matchedPfaElePhi_;
  std::vector<double>* matchedPfaEleE_;

  std::vector<double>* gsfEleEcalE_;
  std::vector<double>* pfaEleEcalE_;

  std::vector<double>* idGsfMva_;
  std::vector<double>* idPfaMva_;
  std::vector<double>* idCiC_;

  std::vector<bool>* gsfToPfaMatch_;
  std::vector<bool>* pfaToGsfMatch_;

  TH1F * h_gsf_pt;
  TH1F * h_gsf_eta;
  TH1F * h_gsf_mva;

  TH1F * h_pf_pt;
  TH1F * h_pf_eta;
  TH1F * h_pf_mva;

private:
  typedef edm::View<reco::PFCandidate>::const_iterator PFCandIter;
  typedef edm::View<reco::GsfElectron>::const_iterator GsfEleIter;

  PFCandIter findElectron(const GsfEleIter gsfEle, PFCandIter begin, PFCandIter end);
  GsfEleIter findElectron(const PFCandIter pfaEle, GsfEleIter begin, GsfEleIter end);
};

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getParameter<edm::InputTag>("electron");
  pfCandLabel_ = pset.getParameter<edm::InputTag>("pfCandidate");
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticles");

  genElePt_ = new std::vector<double>;
  gsfElePt_ = new std::vector<double>;
  pfaElePt_ = new std::vector<double>;

  genEleEta_ = new std::vector<double>;
  gsfEleEta_ = new std::vector<double>;
  pfaEleEta_ = new std::vector<double>;

  genElePhi_ = new std::vector<double>;
  gsfElePhi_ = new std::vector<double>;
  pfaElePhi_ = new std::vector<double>;

  genEleE_ = new std::vector<double>;
  gsfEleE_ = new std::vector<double>;
  pfaEleE_ = new std::vector<double>;

  matchedPfaElePt_ = new std::vector<double>;
  matchedPfaEleEta_ = new std::vector<double>;
  matchedPfaElePhi_ = new std::vector<double>;
  matchedPfaEleE_ = new std::vector<double>;

  gsfEleEcalE_ = new std::vector<double>;
  pfaEleEcalE_ = new std::vector<double>;

  idGsfMva_ = new std::vector<double>;
  idPfaMva_ = new std::vector<double>;
  idCiC_ = new std::vector<double>;

  gsfToPfaMatch_ = new std::vector<bool>;
  pfaToGsfMatch_ = new std::vector<bool>;
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

  tree_->Branch("genElePt", "std::vector<double>", &genElePt_);
  tree_->Branch("gsfElePt", "std::vector<double>", &gsfElePt_);
  tree_->Branch("pfaElePt", "std::vector<double>", &pfaElePt_);

  tree_->Branch("genEleEta", "std::vector<double>", &genEleEta_);
  tree_->Branch("gsfEleEta", "std::vector<double>", &gsfEleEta_);
  tree_->Branch("pfaEleEta", "std::vector<double>", &pfaEleEta_);

  tree_->Branch("genElePhi", "std::vector<double>", &genElePhi_);
  tree_->Branch("gsfElePhi", "std::vector<double>", &gsfElePhi_);
  tree_->Branch("pfaElePhi", "std::vector<double>", &pfaElePhi_);

  tree_->Branch("genEleE", "std::vector<double>", &genEleE_);
  tree_->Branch("gsfEleE", "std::vector<double>", &gsfEleE_);
  tree_->Branch("pfaEleE", "std::vector<double>", &pfaEleE_);

  tree_->Branch("matchedPfaElePt", "std::vector<double>", &matchedPfaElePt_);
  tree_->Branch("matchedPfaEleEta", "std::vector<double>", &matchedPfaEleEta_);
  tree_->Branch("matchedPfaElePhi", "std::vector<double>", &matchedPfaElePhi_);
  tree_->Branch("matchedPfaEleE", "std::vector<double>", &matchedPfaEleE_);

  tree_->Branch("gsfEleEcalE", "std::vector<double>", &gsfEleEcalE_);
  tree_->Branch("pfaEleEcalE", "std::vector<double>", &pfaEleEcalE_);

  tree_->Branch("idGsfMva", "std::vector<double>", &idGsfMva_);
  tree_->Branch("idPfaMva", "std::vector<double>", &idPfaMva_);
  tree_->Branch("idCiC", "std::vector<double>", &idCiC_);

  tree_->Branch("gsfToPfaMatch", "std::vector<bool>", &gsfToPfaMatch_);
  tree_->Branch("pfaToGsfMatch", "std::vector<bool>", &pfaToGsfMatch_);

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

ElectronAnalyzer::PFCandIter ElectronAnalyzer::findElectron(const GsfEleIter gsfEle, 
                                                            ElectronAnalyzer::PFCandIter begin, 
                                                            ElectronAnalyzer::PFCandIter end)
{
  reco::GsfTrackRef refTrk = gsfEle->gsfTrack();
  if ( refTrk.isNull() ) return end;

  PFCandIter matchedEle = end;
  for ( PFCandIter pfaEle = begin; pfaEle != end; ++pfaEle )
  {
    if ( refTrk == pfaEle->gsfTrackRef() )
    {
      matchedEle = pfaEle;
      break;
    }
  }

  return matchedEle;
}

ElectronAnalyzer::GsfEleIter ElectronAnalyzer::findElectron(const PFCandIter pfaEle, 
                                                            ElectronAnalyzer::GsfEleIter begin, 
                                                            ElectronAnalyzer::GsfEleIter end)
{
  reco::GsfTrackRef refTrk = pfaEle->gsfTrackRef();
  if ( refTrk.isNull() ) return end;

  GsfEleIter matchedEle = end;
  for ( GsfEleIter gsfEle = begin; gsfEle != end; ++gsfEle )
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
  genElePt_->clear();
  gsfElePt_->clear();
  pfaElePt_->clear();

  genEleEta_->clear();
  gsfEleEta_->clear();
  pfaEleEta_->clear();

  genElePhi_->clear();
  gsfElePhi_->clear();
  pfaElePhi_->clear();

  genEleE_->clear();
  gsfEleE_->clear();
  pfaEleE_->clear();

  matchedPfaElePt_->clear();
  matchedPfaEleEta_->clear();
  matchedPfaElePhi_->clear();
  matchedPfaEleE_->clear();

  gsfEleEcalE_->clear();
  pfaEleEcalE_->clear();

  idGsfMva_->clear();
  idPfaMva_->clear();
  idCiC_->clear();

  gsfToPfaMatch_->clear();
  pfaToGsfMatch_->clear();

  if ( genParticleHandle.isValid() )
  {
    for ( edm::View<reco::GenParticle>::const_iterator iGen = genParticleHandle->begin();
          iGen != genParticleHandle->end(); ++iGen )
    {
      if ( abs(iGen->pdgId()) != 11 or iGen->status() != 3 ) continue;

      const reco::Candidate::LorentzVector p4 = iGen->p4();
      genElePt_->push_back(p4.pt());
      genEleEta_->push_back(p4.eta());
      genElePhi_->push_back(p4.phi());
      genEleE_->push_back(p4.e());
    }
  }

  for ( edm::View<reco::GsfElectron>::const_iterator iEle = electronHandle->begin();
        iEle != electronHandle->end(); ++iEle )
  {
    //Fill histograms
    h_gsf_pt->Fill(iEle->pt());
    h_gsf_eta->Fill(iEle->eta());
    h_gsf_mva->Fill(iEle->mva());

    const reco::Candidate::LorentzVector p4 = iEle->p4();
    gsfElePt_->push_back(p4.pt());
    gsfEleEta_->push_back(p4.eta());
    gsfElePhi_->push_back(p4.phi());
    gsfEleE_->push_back(p4.e());

    gsfEleEcalE_->push_back(iEle->ecalEnergy());
    idGsfMva_->push_back(iEle->mva());

    PFCandIter matched = findElectron(iEle, pfCandHandle->begin(), pfCandHandle->end());
    if ( matched != pfCandHandle->end() )
    {
      gsfToPfaMatch_->push_back(true);

      matchedPfaElePt_->push_back(matched->pt());
      matchedPfaEleEta_->push_back(matched->eta());
      matchedPfaElePhi_->push_back(matched->phi());
      matchedPfaEleE_->push_back(matched->p4().e());
    }
    else
    {
      gsfToPfaMatch_->push_back(false);
    }
  }

  for ( edm::View<reco::PFCandidate>::const_iterator iPFCand = pfCandHandle->begin();
      iPFCand != pfCandHandle->end(); ++iPFCand )
  {
    if ( abs(iPFCand->pdgId()) != 11 ) continue;
    //Fill histograms
    h_pf_pt->Fill(iPFCand->pt());
    h_pf_eta->Fill(iPFCand->eta());
    h_pf_mva->Fill(iPFCand->mva_e_pi());

    const reco::Candidate::LorentzVector p4 = iPFCand->p4();
    pfaElePt_->push_back(p4.pt());
    pfaEleEta_->push_back(p4.eta());
    pfaElePhi_->push_back(p4.phi());
    pfaEleE_->push_back(p4.e());

    pfaEleEcalE_->push_back(iPFCand->ecalEnergy());
    idPfaMva_->push_back(iPFCand->mva_e_pi());

    GsfEleIter matched = findElectron(iPFCand, electronHandle->begin(), electronHandle->end());
    if ( matched != electronHandle->end() )
    {
      pfaToGsfMatch_->push_back(true);
    }
    else
    {
      pfaToGsfMatch_->push_back(false);
    }
  }

  tree_->Fill();
}

DEFINE_FWK_MODULE(ElectronAnalyzer);

#endif

