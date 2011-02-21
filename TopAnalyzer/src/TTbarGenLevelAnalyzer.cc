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
  edm::InputTag genParticleLabel_;
  double electronMaxEta_, electronMinPt_;
  double muonMaxEta_, muonMinPt_;
  double jetMaxEta_, jetMinPt_;
  double metMinPt_;

  TH1F* hGenTTbarM_;

  TTree* tree_;
  Ko::TTbarGenEvent* ttbarGenEvent_;
};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");

  electronMaxEta_ = pset.getParameter<double>("electronMaxEta");
  electronMinPt_ = pset.getParameter<double>("electronMinPt");
  muonMaxEta_ = pset.getParameter<double>("muonMaxEta");
  muonMinPt_ = pset.getParameter<double>("muonMinPt");
  jetMaxEta_ = pset.getParameter<double>("jetMaxEta");
  jetMinPt_ = pset.getParameter<double>("jetMinPt");
  metMinPt_ = pset.getParameter<double>("metMinPt");

  ttbarGenEvent_ = new Ko::TTbarGenEvent;

}

void TTbarGenLevelAnalyzer::beginJob()
{
  ttbarGenEvent_->clear();

  edm::Service<TFileService> fs;
  const int ttbarMassNbins = 14;
  const double ttbarMassBins[ttbarMassNbins] = {
    0, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1400
  };

  hGenTTbarM_ = fs->make<TH1F>("hGenTTbarM", "Generator level t#bar{t} mass;M(t#bar{t}) [GeV/c^{2}]", ttbarMassNbins-1, ttbarMassBins);

  tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");
  tree_->Branch("ttbarGen", "Ko::TTbarGenEvent", &ttbarGenEvent_);
 
}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( !genParticleHandle.isValid() ) return;

  ttbarGenEvent_->clear();
  ttbarGenEvent_->set(genParticleHandle->begin(), genParticleHandle->end());

  //hGenTTbarM_->Fill(ttbarGenEvent_->mass());
  tree_->Fill();
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

