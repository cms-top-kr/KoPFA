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
  math::XYZTLorentzVector* tt_;
  std::vector<math::XYZTLorentzVector>* tQuarks_;
  std::vector<math::XYZTLorentzVector>* bQuarks_;
  std::vector<math::XYZTLorentzVector>* electrons_;
  std::vector<math::XYZTLorentzVector>* muons_;
  double metX_, metY_;
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

  tt_ = new math::XYZTLorentzVector;
  tQuarks_ = new std::vector<math::XYZTLorentzVector>;
  bQuarks_ = new std::vector<math::XYZTLorentzVector>;
  electrons_ = new std::vector<math::XYZTLorentzVector>;
  muons_ = new std::vector<math::XYZTLorentzVector>;
  
}

void TTbarGenLevelAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  const int ttbarMassNbins = 14;
  const double ttbarMassBins[ttbarMassNbins] = {
    0, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1400
  };

  hGenTTbarM_ = fs->make<TH1F>("hGenTTbarM", "Generator level t#bar{t} mass;M(t#bar{t}) [GeV/c^{2}]", ttbarMassNbins-1, ttbarMassBins);

  tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");
  tree_->Branch("tt", "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >", &tt_);
  tree_->Branch("tQuarks", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &tQuarks_);
  tree_->Branch("bQuarks", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bQuarks_);
  tree_->Branch("electrons", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &electrons_);
  tree_->Branch("muons", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &muons_);
  tree_->Branch("metX", &metX_, "metX/d");
  tree_->Branch("metY", &metY_, "metY/d");
 
}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( !genParticleHandle.isValid() ) return;

  tt_->SetPxPyPzE(0,0,0,0);
  tQuarks_->clear();
  bQuarks_->clear();
  electrons_->clear();
  muons_->clear();

  metX_ = 0;
  metY_ = 0;

  for ( reco::GenParticleCollection::const_iterator genParticle = genParticleHandle->begin();
        genParticle != genParticleHandle->end(); ++genParticle )
  {
    if ( genParticle->status() != 3 ) continue;
    
    const int absPdgId = abs(genParticle->pdgId());

    if ( absPdgId == 6 )
    {
      *tt_ += genParticle->p4();
      tQuarks_->push_back(genParticle->p4());
      continue;
    }

    // Find mother particle with status == 3
    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(genParticle->mother());
    while ( mother != 0 and mother->status() != 3 )
    {
      mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
    }
    if ( !mother or mother->status() != 3 ) continue;
    const int motherAbsPdgId = abs(mother->pdgId());

    if ( absPdgId == 5 and motherAbsPdgId == 6 )
    {
      bQuarks_->push_back(genParticle->p4());
    }
    if ( motherAbsPdgId == 24 )
    {
      if ( absPdgId == 11 )
      {
        electrons_->push_back(genParticle->p4());
      }
      else if ( absPdgId == 13 ) 
      {
        muons_->push_back(genParticle->p4());
      }
      else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
      {
        metX_ += genParticle->px();
        metY_ += genParticle->py();
      }
    }
  }

  hGenTTbarM_->Fill(tt_->M());
  tree_->Fill();
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

