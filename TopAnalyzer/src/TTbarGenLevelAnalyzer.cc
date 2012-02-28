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
  TH1F* hmTT_Vprt_; // mTT in the visible PS with patons
  TH1F* hmTT_Vstb_; // mTT in the isible PS with particles
  TH1F* hmLLBBMet_Vstb_; // mLLBBMet in the visible PS with particles
  TH1F* hmLLJJMet_Vstb_; // mLLJJMet in the visible PS with particles

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
  hmTT_Vprt_ = fs->make<TH1F>("hmTT_Vprt", "m(t#bar{t}) in the visible phase space with parton level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmTT_Vstb_ = fs->make<TH1F>("hmTT_Vstb", "m(t#bar{t}) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmLLBBMet_Vstb_ = fs->make<TH1F>("hmLLBBMet_Vstb", "m(llbbMet) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
  hmLLJJMet_Vstb_ = fs->make<TH1F>("hmLLJJMet_Vstb", "m(lljjMet) in the visible phase space with particle level cuts;Mass [GeV/c^{2}];Events per 1GeV", 2000, 0, 2000);
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
  if ( mLLBBMet > 0 ) // At least two leptons and b quarks are found
  {
    // Parton level visible space cut
    if ( ttbarGenEvent_->leptons_[0].pt() >= 20 and ttbarGenEvent_->leptons_[1].pt() >= 20 and 
         ttbarGenEvent_->bQuarks_[0].pt() >= 30 and ttbarGenEvent_->bQuarks_[1].pt() >= 30 and
         abs(ttbarGenEvent_->leptons_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->leptons_[1].eta()) <= 2.4 and
         abs(ttbarGenEvent_->bQuarks_[0].eta()) <= 2.4 and abs(ttbarGenEvent_->bQuarks_[1].eta()) <= 2.4 )
    {
      hmTT_Vprt_->Fill(mLLBBMet);
    }
  }

  // At least two stable leptons and b jets are found
  // Stable leptons and b jets are defined in the visible phase space
  if ( mLLBjBjMet > 0 ) 
  {
    hmTT_Vstb_->Fill(mTT);
    hmLLBBMet_Vstb_->Fill(mLLBBMet);
    hmLLJJMet_Vstb_->Fill(mLLJJMet);
  }

  if ( doTree_ ) tree_->Fill();
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

