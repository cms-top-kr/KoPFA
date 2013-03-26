#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <memory>
#include <vector>

using namespace std;
using namespace edm;
using namespace reco;

class TTbarGenLevelAnalyzer : public edm::EDAnalyzer
{
public:
  TTbarGenLevelAnalyzer(const edm::ParameterSet& pset);
  ~TTbarGenLevelAnalyzer() {};

  virtual void beginJob();
  virtual void endJob() {};
  virtual void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag genJetLabel_;
  edm::InputTag genMETLabel_;

  TTree* tree_;
  Ko::TTbarGenEvent* ttbarGenEvent_;

  TH1F* hmTT_Full_; // mTT in the full PS
  TH1F* hmTT_Pton_; // mTT in the visible PS with partons
  TH1F* hmTT_PtonPS_; // mTT in the visible PS with partons, after parton shower
  TH1F* hmTT_Ptcl_; // mTT in the isible PS with particles
  TH1F* hmLLBjBjMet_Ptcl_; // mLLBjBjMet in the visible PS with particles
  TH1F* hmLLJJMet_Ptcl_; // mLLJJMet in the visible PS with particles

  TH1F* hmTop_; // Top quark mass
  TH1F* hDmTop_; // Top quark mass difference
  TH1F* hPtTop_; // Top quark pT

  TH2F* hPartonVsParticle_;

  TH2F* hBR_;

  bool doTree_;
};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");
  genJetLabel_ = pset.getParameter<edm::InputTag>("genJet");
  genMETLabel_ = pset.getParameter<edm::InputTag>("genMET");

  doTree_ = pset.getUntrackedParameter<bool>("doTree", false);

  ttbarGenEvent_ = new Ko::TTbarGenEvent;

}

void TTbarGenLevelAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  if ( doTree_ )
  {
    tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");
    tree_->Branch("ttbarGen", "Ko::TTbarGenEvent", &ttbarGenEvent_);
  }

  hmTT_Full_ = fs->make<TH1F>("hmTT_Full", "m(t#bar{t}) in the full phase space;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmTT_Pton_ = fs->make<TH1F>("hmTT_Pton", "m(t#bar{t}) in the visible phase space with parton level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmTT_PtonPS_ = fs->make<TH1F>("hmTT_PtonPS", "m(t#bar{t}) in the visible phase space with parton level cuts PS;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmTT_Ptcl_ = fs->make<TH1F>("hmTT_Ptcl", "m(t#bar{t}) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);

  // Dileptonic modes
  hmLLBjBjMet_Ptcl_ = fs->make<TH1F>("hmLLBjBjMet_Ptcl", "m(llBjBjMet) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmLLJJMet_Ptcl_ = fs->make<TH1F>("hmLLJJMet_Ptcl", "m(lljjMet) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);

  hmTop_ = fs->make<TH1F>("hmTop", "m(top); Mass [GeV/c^{2}];Entries per 1GeV", 40, 175-20, 175+20);
  hDmTop_ = fs->make<TH1F>("hDmTop", "Top mass difference;Mass difference [GeV/c^{2}];Events per 1GeV", 50, 0, 50);
  hPtTop_ = fs->make<TH1F>("hPtTop", "Top quark's transverse momentum;Transverse momentum [GeV/c^{2}];Entries per 1GeV", 2000, 0, 2000);

  hPartonVsParticle_ = fs->make<TH2F>("hPartonVsParticle", "Visible phase space correlation;Parton level;Particle level", 2, 0, 2, 2, 0, 2);
  hPartonVsParticle_->GetXaxis()->SetBinLabel(1, "T");
  hPartonVsParticle_->GetXaxis()->SetBinLabel(2, "F");
  hPartonVsParticle_->GetYaxis()->SetBinLabel(1, "T");
  hPartonVsParticle_->GetYaxis()->SetBinLabel(2, "F");
  hPartonVsParticle_->SetOption("COLZ");

  hBR_ = fs->make<TH2F>("hBR", "Branching ratio;Top quark decay modes;Anti-top decay modes", 4, 1, 5, 4, 1, 5);
  hBR_->GetXaxis()->SetBinLabel(1, "e");
  hBR_->GetXaxis()->SetBinLabel(2, "#mu");
  hBR_->GetXaxis()->SetBinLabel(3, "#tau");
  hBR_->GetXaxis()->SetBinLabel(4, "Hadronic");
  hBR_->GetYaxis()->SetBinLabel(1, "e");
  hBR_->GetYaxis()->SetBinLabel(2, "#mu");
  hBR_->GetYaxis()->SetBinLabel(3, "#tau");
  hBR_->GetYaxis()->SetBinLabel(4, "Hadronic");
  hBR_->SetOption("COLZ");
}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( !genParticleHandle.isValid() ) return;

  edm::Handle<reco::GenJetCollection> genJetHandle;
  event.getByLabel(genJetLabel_, genJetHandle);
  if ( !genJetHandle.isValid() or genJetHandle.failedToGet() ) return;

  edm::Handle<std::vector<reco::GenMET> > genMETHandle;
  event.getByLabel(genMETLabel_, genMETHandle);
  if ( !genMETHandle.isValid() ) return;
  const reco::GenMET& genMET = *genMETHandle->begin();

  ttbarGenEvent_->set(genParticleHandle.product(), genJetHandle.product(), &genMET);

  const double mTT = ttbarGenEvent_->partonTTbar().M();
  const double mLLBBMet = ttbarGenEvent_->partonLLBBMet().M();
  const double mLLJJMet = ttbarGenEvent_->particleLLJJMet().M();
  const double mLLBjBjMet = ttbarGenEvent_->particleLLBjBjMet().M();

  hmTT_Full_->Fill(mTT);

  // Fill decay mode
  int lepType1 = 0, lepType2 = 0;
  for ( int i=0, n=genParticleHandle->size(); i<n; ++i )
  {
    const reco::GenParticle& pTop = genParticleHandle->at(i);
    if ( pTop.status() != 3 ) continue;
    if ( abs(pTop.pdgId()) != 6 ) continue;
    if ( pTop.numberOfDaughters() < 2 ) continue;
    if ( abs(pTop.daughter(0)->pdgId()) == 6 ) continue;

    const reco::GenParticle* pW = 0;
    for ( int j=0, m=pTop.numberOfDaughters(); j<m; ++j )
    {
      const reco::GenParticle* dau = dynamic_cast<const reco::GenParticle*>(pTop.daughter(j));
      if ( abs(dau->pdgId()) == 24 )
      {
        pW = dau;
        break;
      }
    }

    // Determine decay mode of W
    int lepType;
    while ( true )
    {
      lepType = 4;
      for ( int j=0, m=pW->numberOfDaughters(); j<m; ++j )
      {
        const reco::GenParticle* dau = dynamic_cast<const reco::GenParticle*>(pW->daughter(j));
        if ( !dau ) { lepType = -2; break; }

        const int pdgId = abs(dau->pdgId());
        if ( pdgId == 24 ) { pW = dau; lepType = -1; break; }
        else if ( pdgId == 11 ) { lepType = 1; break; }
        else if ( pdgId == 13 ) { lepType = 2; break; }
        else if ( pdgId == 15 ) { lepType = 3; break; }
      }
      if ( lepType != -1 ) break;
    }
    if ( pTop.pdgId() > 0 ) lepType1 = lepType;
    else lepType2 = lepType;
  }
  hBR_->Fill(lepType1, lepType2);

  bool isPartonLevel = false;
  if ( mLLBBMet > 0 ) // At least two leptons and b quarks are found
  {
    // Parton level visible space cut
    if ( ttbarGenEvent_->leptons_[0].pt() >= 20 and ttbarGenEvent_->leptons_[1].pt() >= 20 and 
         ttbarGenEvent_->bQuarks_[0].pt() >= 30 and ttbarGenEvent_->bQuarks_[1].pt() >= 30 and
         abs(ttbarGenEvent_->leptons_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->leptons_[1].eta()) <= 2.4 and
         abs(ttbarGenEvent_->bQuarks_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->bQuarks_[1].eta()) <= 2.4 )
    {
      isPartonLevel = true;
      hmTT_Pton_->Fill(mTT);
    }
  }

  if ( ttbarGenEvent_->leptons_.size() >= 2 and ttbarGenEvent_->topBquarks_.size() >= 2 and
       ttbarGenEvent_->leptons_[0].pt() >= 20 and ttbarGenEvent_->leptons_[1].pt() >= 20 and
       ttbarGenEvent_->topBquarks_[0].pt() >= 30 and ttbarGenEvent_->topBquarks_[1].pt() >= 30 and
       abs(ttbarGenEvent_->leptons_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->leptons_[1].eta()) <= 2.4 and
       abs(ttbarGenEvent_->topBquarks_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->topBquarks_[1].eta()) <= 2.4 )
  {
    isPartonLevel = true;
    hmTT_PtonPS_->Fill(mTT);
  }

  if ( ttbarGenEvent_->tQuarks_.size() >= 2 )
  {
    const double mTop1 = ttbarGenEvent_->tQuarks_[0].mass();
    const double mTop2 = ttbarGenEvent_->tQuarks_[1].mass();
    hmTop_->Fill(mTop1);
    hmTop_->Fill(mTop2);
    hDmTop_->Fill(abs(mTop1-mTop2));

    hPtTop_->Fill(ttbarGenEvent_->tQuarks_[0].pt());
    hPtTop_->Fill(ttbarGenEvent_->tQuarks_[1].pt());
  }

  // At least two stable leptons and b jets are found
  // Stable leptons and b jets are defined in the visible phase space
  bool isParticleLevel = false;
  if ( mLLBjBjMet > 0 ) 
  {
    isParticleLevel = true;
    hmTT_Ptcl_->Fill(mTT);
    hmLLJJMet_Ptcl_->Fill(mLLJJMet);
    hmLLBjBjMet_Ptcl_->Fill(mLLBjBjMet);
  }

  if ( isPartonLevel and isParticleLevel ) hPartonVsParticle_->Fill(1.,1.);
  else if ( isPartonLevel and !isParticleLevel ) hPartonVsParticle_->Fill(1.,0.);
  else if ( !isPartonLevel and isParticleLevel ) hPartonVsParticle_->Fill(0.,1.);
  else hPartonVsParticle_->Fill(0.,0.);

  if ( doTree_ ) tree_->Fill();
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

