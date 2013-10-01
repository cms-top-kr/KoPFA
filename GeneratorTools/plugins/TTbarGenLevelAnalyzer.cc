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
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "TTree.h"
#include "TH2F.h"

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
  double dressup(math::XYZTLorentzVector& lv, const GenParticlesPtr& particles);
  bool hasStableB(const reco::GenJet& jet);
  void matchAndFill(TH2F* h, const math::XYZTLorentzVector& p,
                    const math::XYZTLorentzVector& v1, const math::XYZTLorentzVector& v2);

private:
  edm::InputTag genEventInfoLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;

  double leptonMinPt_, leptonMaxEta_;
  double neutrinoMaxEta_;
  double jetMinPt_, jetMaxEta_;

  constexpr static double zMassPDG_ = 91.2;
  constexpr static double wMassPDG_ = 80.4;
  constexpr static double tMassPDG_ = 172.5;

private:
  TTree* tree_;
  int prodMode_, decayMode_;
  double qScale_;
  LorentzVectors* electrons_, * muons_;
  LorentzVectors* bjets_;
  LorentzVectors* neutrinos_, * mets_;
  LorentzVectors* dileptons_, * lbCands_; 
  LorentzVectors* wCands_, * tCands_;
  LorentzVectors* ttCands_;

  TH2F* hPartonElectronPt_DressedElectronPt_;
  TH2F* hPartonMuonPt_DressedMuonPt_;
  TH2F* hDressedElectronPt_BareElectronPt_;
  TH2F* hDressedMuonPt_BareMuonPt_;
  TH2F* hPartonBPt_ParticleBPt_;
  TH2F* hPartonWPt_ParticleWPt_;
  TH2F* hPartonTopPt_ParticleTopPt_;
  TH2F* hPartonTTbarM_ParticleTTbarM_;
  TH2F* hPartonTTbarPt_ParticleTTbarPt_;

};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  bool doTree = pset.getUntrackedParameter<bool>("doTree", false);

  genEventInfoLabel_ = pset.getUntrackedParameter<edm::InputTag>("genEventInfo");
  genParticlesLabel_ = pset.getUntrackedParameter<edm::InputTag>("genParticles");
  genJetsLabel_ = pset.getUntrackedParameter<edm::InputTag>("genJets");

  leptonMinPt_  = pset.getUntrackedParameter<double>("leptonMinPt", 20);
  leptonMaxEta_ = pset.getUntrackedParameter<double>("leptonMaxEta", 2.4);
  neutrinoMaxEta_ = pset.getUntrackedParameter<double>("neutrinoMaxEta", 5.0);
  jetMinPt_  = pset.getUntrackedParameter<double>("jetMinPt", 30);
  jetMaxEta_ = pset.getUntrackedParameter<double>("jetMaxEta", 2.4);

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
  tree_ = 0;
  if ( doTree )
  {
    tree_ = fs->make<TTree>("tree", "tree");
    tree_->Branch("decayMode", &decayMode_, "decayMode/I");
    tree_->Branch("prodMode" , &prodMode_ , "prodMode/I" );
    tree_->Branch("qScale"   , &qScale_   , "qScale/D"   );

    tree_->Branch("electrons", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &electrons_);
    tree_->Branch("muons"    , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &muons_    );
    tree_->Branch("bjets"    , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_    );
    tree_->Branch("neutrinos", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &neutrinos_);
    tree_->Branch("mets"     , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &mets_     );

    tree_->Branch("dileptons", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &dileptons_);
    tree_->Branch("lbCands"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &lbCands_  );
    tree_->Branch("wCands"   , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &wCands_   );
    tree_->Branch("tCands"   , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &tCands_   );
    tree_->Branch("ttCands"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &ttCands_  );
  }

  hPartonElectronPt_DressedElectronPt_ = fs->make<TH2F>("hPartonElectronPt_DressedElectronPt", "Compared electrons;Parton electron p_{T} (GeV/c);Dressed electron p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPartonMuonPt_DressedMuonPt_ = fs->make<TH2F>("hPartonMuonPt_DressedMuonPt", "Compared muons;Parton muon p_{T} (GeV/c);Dressed muon p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hDressedElectronPt_BareElectronPt_ = fs->make<TH2F>("hDressedElectronPt_BareElectronPt", "Compared electrons;Dressed electron p_{T} (GeV/c);Bare electron p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hDressedMuonPt_BareMuonPt_ = fs->make<TH2F>("hDressedMuonPt_BareMuonPt", "Compared muons;Dressed muon p_{T} (GeV/c);Bare muon p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPartonBPt_ParticleBPt_ = fs->make<TH2F>("hPartonBPt_ParticleBPt", "Compared b jets;B quark p_{T} (GeV/c);B jet p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPartonWPt_ParticleWPt_ = fs->make<TH2F>("hPartonWPt_ParticleWPt", "Compared top;Parton W p_{T} (GeV/c);Particle W p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPartonTopPt_ParticleTopPt_ = fs->make<TH2F>("hPartonTopPt_ParticleTopPt", "Compared top;Parton top p_{T} (GeV/c);Particle top p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPartonTTbarM_ParticleTTbarM_ = fs->make<TH2F>("hPartonTTbarM_ParticleTTbarM", "Compared ttbar;Parton t#bar{t} M (GeV/c^{2});Particle t#bar{t} M(GeV/c^{2})", 400, 0, 2000, 400, 0, 2000);
  hPartonTTbarPt_ParticleTTbarPt_ = fs->make<TH2F>("hPartonTTbarPt_ParticleTTbarPt", "Compared t#bar{t};Parton t#bar{t} p_{T} (GeV/c);Particle t#bar{t} p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);

}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  electrons_->clear();
  muons_->clear();
  bjets_->clear();
  neutrinos_->clear();
  mets_->clear();
  
  dileptons_->clear();
  lbCands_->clear();
  wCands_->clear();
  tCands_->clear();
  ttCands_->clear();

  edm::Handle<GenEventInfoProduct> genEventInfoHandle;
  event.getByLabel(genEventInfoLabel_, genEventInfoHandle);

  edm::Handle<reco::GenParticleCollection> genParticlesHandle;
  event.getByLabel(genParticlesLabel_, genParticlesHandle);

  edm::Handle<reco::GenJetCollection> genJetsHandle;
  event.getByLabel(genJetsLabel_, genJetsHandle);

  const gen::PdfInfo* pdf = genEventInfoHandle->pdf();
  const int parton1Id = pdf->id.first;
  const int parton2Id = pdf->id.second;
  if ( parton1Id == 0 and parton2Id == 0 ) prodMode_ = 1; // gg fusion
  else if ( parton1Id != 0 and parton2Id != 0 ) prodMode_ = 3; // qq collision
  else prodMode_ = 2; // gq scattering
  qScale_ = pdf->scalePDF;

  // Collect stable particles for the particle level analysis
  GenParticlesPtr stableLeptons;
  GenParticlesPtr allStables;
  for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::GenParticle* p = &genParticlesHandle->at(i);
    if ( p->status() != 1 ) continue;
    allStables.push_back(p);
    const unsigned int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 or absPdgId == 13 ) stableLeptons.push_back(p);
    else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
    {
      if ( abs(p->eta()) > neutrinoMaxEta_ ) continue;
      neutrinos_->push_back(p->p4());
    }
  }

  // Do dressup and keep leptons
  std::vector<int> electronsQ, muonsQ;
  for ( unsigned int i=0, n=stableLeptons.size(); i<n; ++i )
  {
    const reco::GenParticle* p = stableLeptons.at(i);
    math::XYZTLorentzVector p4 = p->p4();
    const double isolation = dressup(p4, allStables);
    if ( p4.pt() < leptonMinPt_ or abs(p4.eta()) > leptonMaxEta_ ) continue;
    if ( isolation > 0.2*p4.pt() ) continue;

    const unsigned int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 ) 
    {
      electrons_->push_back(p4);
      electronsQ.push_back(p->charge());
      hDressedElectronPt_BareElectronPt_->Fill(p4.pt(), p->pt());
    }
    else if ( absPdgId == 13 )
    {
      muons_->push_back(p4);
      muonsQ.push_back(p->charge());
      hDressedMuonPt_BareMuonPt_->Fill(p4.pt(), p->pt());
    }
  }
  // Determine decay mode
  int dileptonQ;
  math::XYZTLorentzVector lepton1, lepton2;
  if ( electrons_->size() == 2 and muons_->size() == 0 )
  {
    decayMode_ = 1;
    lepton1 = electrons_->at(0);
    lepton2 = electrons_->at(1);
    dileptonQ = electronsQ[0]+electronsQ[1];
  }
  else if ( electrons_->size() == 0 and muons_->size() == 2 )
  {
    decayMode_ = 2;
    lepton1 = muons_->at(0);
    lepton2 = muons_->at(1);
    dileptonQ = muonsQ[0] + muonsQ[1];
  }
  else if ( electrons_->size() == 1 and muons_->size() == 1 )
  {
    decayMode_ = 3;
    lepton1 = electrons_->at(0);
    lepton2 = muons_->at(0);
    dileptonQ = electronsQ[0] + muonsQ[0];
  }
  else return;
  // Opposite charge
  if ( dileptonQ != 0 ) return;

  dileptons_->push_back(lepton1+lepton2);
  const double dileptonMass = dileptons_->at(0).mass();
  // Z veto
  if ( decayMode_ != 3 and (dileptonMass < 20 or std::abs(dileptonMass-zMassPDG_) < 10) ) return;

  // Calculate MET
  if ( neutrinos_->size() < 2 ) return;
  const math::XYZTLorentzVector metLVec = neutrinos_->at(0) + neutrinos_->at(1);
  mets_->push_back(metLVec);

  // Find bjets
  for ( unsigned int i=0, n=genJetsHandle->size(); i<n; ++i )
  {
    const reco::GenJet& jet = genJetsHandle->at(i);
    if ( jet.pt() < jetMinPt_ or abs(jet.eta()) > jetMaxEta_ ) continue;
    //if ( deltaR(jet.p4(), lepton1) < 0.5 or deltaR(jet.p4(), lepton2) < 0.5 ) continue;
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
  lbCands_->push_back(lepton1+bjets_->at(topBIndex[0]));
  lbCands_->push_back(lepton2+bjets_->at(topBIndex[1]));
  tCands_->push_back(wCands_->at(0)+bjets_->at(topBIndex[0]));
  tCands_->push_back(wCands_->at(1)+bjets_->at(topBIndex[1]));

  ttCands_->push_back(tCands_->at(0)+tCands_->at(1));

  // Collect parton level objects
  math::XYZTLorentzVector parton_m1, parton_m2;
  math::XYZTLorentzVector parton_e1, parton_e2;
  math::XYZTLorentzVector parton_b1, parton_b2;
  math::XYZTLorentzVector parton_w1, parton_w2;
  math::XYZTLorentzVector parton_t1, parton_t2;
  for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::GenParticle* p = &genParticlesHandle->at(i);
    if ( p->status() != 3 ) continue;
    const math::XYZTLorentzVector p4 = p->p4();
    switch ( p->pdgId() )
    {
      case   6 : parton_t1 = p4; break;
      case  -6 : parton_t2 = p4; break;
      case   5 : parton_b1 = p4; break;
      case  -5 : parton_b2 = p4; break;
      case  11 : parton_e1 = p4; break;
      case -11 : parton_e2 = p4; break;
      case  13 : parton_m1 = p4; break;
      case -13 : parton_m2 = p4; break;
      case  24 : parton_w1 = p4; break;
      case -24 : parton_w2 = p4; break;
    }
  }
  math::XYZTLorentzVector parton_tt = parton_t1 + parton_t2;

  matchAndFill(hPartonElectronPt_DressedElectronPt_, parton_e1, lepton1, lepton2);
  matchAndFill(hPartonElectronPt_DressedElectronPt_, parton_e2, lepton1, lepton2);
  matchAndFill(hPartonMuonPt_DressedMuonPt_, parton_m1, lepton1, lepton2);
  matchAndFill(hPartonMuonPt_DressedMuonPt_, parton_m2, lepton1, lepton2);
  matchAndFill(hPartonBPt_ParticleBPt_, parton_b1, bjets_->at(0), bjets_->at(1));
  matchAndFill(hPartonBPt_ParticleBPt_, parton_b2, bjets_->at(0), bjets_->at(1));
  matchAndFill(hPartonWPt_ParticleWPt_, parton_w1, wCands_->at(0), wCands_->at(1));
  matchAndFill(hPartonWPt_ParticleWPt_, parton_w2, wCands_->at(0), wCands_->at(1));
  matchAndFill(hPartonTopPt_ParticleTopPt_, parton_t1, tCands_->at(0), tCands_->at(1));
  matchAndFill(hPartonTopPt_ParticleTopPt_, parton_t2, tCands_->at(0), tCands_->at(1));
  hPartonTTbarPt_ParticleTTbarPt_->Fill(parton_tt.pt(), ttCands_->at(0).pt());
  hPartonTTbarM_ParticleTTbarM_->Fill(parton_tt.mass(), ttCands_->at(0).mass());

  if ( tree_ ) tree_->Fill();
}

double TTbarGenLevelAnalyzer::dressup(math::XYZTLorentzVector& lv, const GenParticlesPtr& particles)
{
  double isolation = 0;
  for ( int i=0, n=particles.size(); i<n; ++i )
  {
    const reco::GenParticle* p = particles.at(i);
    const math::XYZTLorentzVector p4 = p->p4();
    const double dR = deltaR(lv, p4);
    if ( dR < 0.1 )
    {
      if ( p->pdgId() == 22 ) lv += p4;
    }
    else if ( dR < 0.3 )
    {
      const double pt = p->pt();
      if ( pt > 0.5 ) isolation += pt;
    }
  }
  return isolation;
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

void TTbarGenLevelAnalyzer::matchAndFill(TH2F* h, const math::XYZTLorentzVector& p, 
                                         const math::XYZTLorentzVector& v1, const math::XYZTLorentzVector& v2)
{
  if ( p.pt() <= 0.01 ) return; 
  if ( v1.pt() > 0.01 and deltaR(p, v1) < 0.1 ) h->Fill(p.pt(), v1.pt());
  if ( v2.pt() > 0.01 and deltaR(p, v2) < 0.1 ) h->Fill(p.pt(), v2.pt());
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);
