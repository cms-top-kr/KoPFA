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

};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");
  genJetLabel_ = pset.getParameter<edm::InputTag>("genJet");
  genMETLabel_ = pset.getParameter<edm::InputTag>("genMET");

  ttbarGenEvent_ = new Ko::TTbarGenEvent;

}

void TTbarGenLevelAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");
  tree_->Branch("ttbarGen", "Ko::TTbarGenEvent", &ttbarGenEvent_);
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

  tree_->Fill();
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

