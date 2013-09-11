#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TTree.h"

#include <iostream>
#include <vector>

using namespace std;

class TTbarGenLevelAnalyzer : public edm::EDAnalyzer
{
public:
  TTbarGenLevelAnalyzer(const edm::ParameterSet& pset);
  ~TTbarGenLevelAnalyzer() {};

  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  typedef std::vector<const reco::GenParticle*> GenParticlesPtr;
  typedef std::vector<math::XYZTLorentzVector> LorentzVectors;
  void dressup(math::XYZTLorentzVector& lv, const GenParticlesPtr& photons);
  bool hasStableB(const reco::GenJet& jet);

private:
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;

  double leptonMinPt_, leptonMaxEta_;
  double neutrinoMaxEta_;
  double jetMinPt_, jetMaxEta_;

  constexpr static double wMassPDG_ = 80.4;
  constexpr static double tMassPDG_ = 172.5;

private:
  TTree* tree_;
  int decayMode_;
  LorentzVectors* electrons_, * muons_;
  LorentzVectors* bjets_;
  LorentzVectors* neutrinos_, * mets_;
  LorentzVectors* dileptons_, * lbCands_; 
  LorentzVectors* wCands_, * tCands_;
  LorentzVectors* ttCands_;
};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticlesLabel_ = pset.getParameter<edm::InputTag>("genParticles");
  genJetsLabel_ = pset.getParameter<edm::InputTag>("genJets");

  leptonMinPt_  = pset.getParameter<double>("leptonMinPt");
  leptonMaxEta_ = pset.getParameter<double>("leptonMaxEta");
  neutrinoMaxEta_ = pset.getParameter<double>("neutrinoMaxEta");
  jetMinPt_  = pset.getParameter<double>("jetMinPt");
  jetMaxEta_ = pset.getParameter<double>("jetMaxEta");

  electrons_ = new LorentzVectors();
  muons_     = new LorentzVectors();
  bjets_     = new LorentzVectors();
  neutrinos_ = new LorentzVectors();

  mets_      = new LorentzVectors();
  dileptons_ = new LorentzVectors();
  lbCands_   = new LorentzVectors();
  wCands_    = new LorentzVectors();
  tCands_    = new LorentzVectors();
  ttCands_   = new LorentzVectors();

  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "tree");
  tree_->Branch("electrons", "std::vector<math::XYZTLorentzVector>", &electrons_);
  tree_->Branch("muons"    , "std::vector<math::XYZTLorentzVector>", &muons_    );
  tree_->Branch("bjets"    , "std::vector<math::XYZTLorentzVector>", &bjets_    );
  tree_->Branch("mets"     , "std::vector<math::XYZTLorentzVector>", &mets_     );

  tree_->Branch("dileptons", "std::vector<math::XYZTLorentzVector>", &dileptons_);
  tree_->Branch("lbCands"  , "std::vector<math::XYZTLorentzVector>", &lbCands_  );
  tree_->Branch("wCands"   , "std::vector<math::XYZTLorentzVector>", &wCands_   );
  tree_->Branch("tCands"   , "std::vector<math::XYZTLorentzVector>", &tCands_   );
  tree_->Branch("ttCands"  , "std::vector<math::XYZTLorentzVector>", &ttCands_  );

}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  electrons_->clear();
  muons_->clear();
  bjets_->clear();
  mets_->clear();
  
  dileptons_->clear();
  lbCands_->clear();
  wCands_->clear();
  tCands_->clear();
  ttCands_->clear();

  edm::Handle<reco::GenParticleCollection> genParticlesHandle;
  event.getByLabel(genParticlesLabel_, genParticlesHandle);

  edm::Handle<reco::GenJetCollection> genJetsHandle;
  event.getByLabel(genJetsLabel_, genJetsHandle);

  // Collect stable particles for the particle level analysis
  GenParticlesPtr stableLeptons;
  GenParticlesPtr stablePhotons;
  for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::GenParticle* p = &genParticlesHandle->at(i);
    if ( p->status() != 1 ) continue;
    const unsigned int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 or absPdgId == 13 ) stableLeptons.push_back(p);
    else if ( absPdgId == 22 ) stablePhotons.push_back(p);
    else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
    {
      if ( abs(p->eta()) > neutrinoMaxEta_ ) continue;
      neutrinos_->push_back(p->p4());
    }
  }

  // Do dressup and keep leptons
  for ( unsigned int i=0, n=stableLeptons.size(); i<n; ++i )
  {
    const reco::GenParticle* p = stableLeptons.at(i);
    math::XYZTLorentzVector p4 = p->p4();
    dressup(p4, stablePhotons);
    if ( p4.pt() < leptonMinPt_ or abs(p4.eta()) > leptonMaxEta_ ) continue;

    const unsigned int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 ) electrons_->push_back(p4);
    else if ( absPdgId == 13 ) muons_->push_back(p4);
  }
  // Determine decay mode
  math::XYZTLorentzVector lepton1, lepton2;
  if ( electrons_->size() == 2 and muons_->size() == 0 )
  {
    decayMode_ = 1;
    lepton1 = electrons_->at(0);
    lepton2 = electrons_->at(1);
  }
  else if ( electrons_->size() == 0 and muons_->size() == 2 )
  {
    decayMode_ = 2;
    lepton1 = muons_->at(0);
    lepton2 = muons_->at(1);
  }
  else if ( electrons_->size() == 1 and muons_->size() == 1 )
  {
    decayMode_ = 3;
    lepton1 = electrons_->at(0);
    lepton2 = muons_->at(0);
  }
  else return;
  dileptons_->push_back(lepton1+lepton2);

  // Calculate MET
  if ( neutrinos_->size() < 2 ) return;
  const math::XYZTLorentzVector metLVec = neutrinos_->at(0) + neutrinos_->at(1);
  mets_->push_back(metLVec);

  // Find bjets
  for ( unsigned int i=0, n=genJetsHandle->size(); i<n; ++i )
  {
    const reco::GenJet& jet = genJetsHandle->at(i);
    if ( jet.pt() < jetMinPt_ or abs(jet.eta()) < jetMaxEta_ ) continue;
    if ( deltaR(jet.p4(), lepton1) < 0.5 or deltaR(jet.p4(), lepton2) < 0.5 ) continue;
    if ( !hasStableB(jet) ) continue;

    bjets_->push_back(jet.p4());
  }
  if ( bjets_->size() < 2 ) return;

  // Now we are ready for W/top combination.
  // Start from W candidate building
  const math::XYZTLorentzVector w00 = lepton1+neutrinos_->at(0);
  const math::XYZTLorentzVector w11 = lepton2+neutrinos_->at(1);
  const math::XYZTLorentzVector w01 = lepton1+neutrinos_->at(1);
  const math::XYZTLorentzVector w10 = lepton2+neutrinos_->at(0);
  if ( abs(w00.mass() - wMassPDG_) + abs(w11.mass() - wMassPDG_) 
     < abs(w01.mass() - wMassPDG_) + abs(w10.mass() - wMassPDG_) )
  {
    wCands_->push_back(w00);
    wCands_->push_back(w11);
  }
  else
  {
    wCands_->push_back(w01);
    wCands_->push_back(w10);
  }
  // Then proceed to top quark combination
  int topBIndex[] = {-1, -1};
  double minResMtop = 1e9;
  for ( unsigned int i=0, n=bjets_->size(); i<n; ++i )
  {
    for ( unsigned int j=0; j<n; ++j )
    {
      if ( i == j ) continue;
      const math::XYZTLorentzVector tPair1 = wCands_->at(0)+bjets_->at(i);
      const math::XYZTLorentzVector tPair2 = wCands_->at(1)+bjets_->at(j);
      const double resMtop = abs(tPair1.mass() - tMassPDG_) + abs(tPair2.mass() - tMassPDG_);
      if ( resMtop < minResMtop )
      {
        minResMtop = resMtop;
        topBIndex[0] = i;
        topBIndex[1] = j;
      }
    }
  }
  // Skip if no B jet combination found
  if ( topBIndex[0] == -1 or topBIndex[1] == -1 ) return;
  tCands_->push_back(wCands_->at(0)+bjets_->at(topBIndex[0]));
  tCands_->push_back(wCands_->at(1)+bjets_->at(topBIndex[1]));

  tree_->Fill();
}

void TTbarGenLevelAnalyzer::dressup(math::XYZTLorentzVector& lv, const GenParticlesPtr& photons)
{
  for ( int i=0, n=photons.size(); i<n; ++i )
  {
    const math::XYZTLorentzVector p4 = photons.at(i)->p4();
    if ( deltaR(lv, p4) > 0.1 ) continue;
    lv += p4;
  }
}

bool TTbarGenLevelAnalyzer::hasStableB(const reco::GenJet& jet)
{
  for ( int i=0, n=jet.nConstituents(); i<n; ++i )
  {
    const reco::GenParticle* p = jet.getGenConstituent(i);
    if ( p->pdgId() == 7 ) return true;
  }
  return false;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);
