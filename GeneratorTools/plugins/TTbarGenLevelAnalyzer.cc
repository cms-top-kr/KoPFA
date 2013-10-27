#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/PtComparator.h"

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
  void endJob()
  {
    for ( int i=0; i<12; ++i ) cout << "Step " << i << "   " << eventCount_[i] << endl;
  };

private:
  typedef std::vector<const reco::GenParticle*> GenParticlesPtr;
  typedef std::vector<math::XYZTLorentzVector> LorentzVectors;
  double dressup(math::XYZTLorentzVector& lv, const GenParticlesPtr& particles);
  bool hasStableB(const reco::GenJet& jet);
  void matchAndFill(TH2F* hxy, TH2F* hres, const math::XYZTLorentzVector& p,
                    const math::XYZTLorentzVector& v1, const math::XYZTLorentzVector& v2);

private:
  edm::InputTag genEventInfoLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag genJetsLabel_;

  double leptonMinPt_, leptonMaxEta_;
  double neutrinoMaxEta_;
  double jetMinPt_, jetMaxEta_;

  constexpr static double zMassPDG_ = 91.2;
  constexpr static double wMassPDG_ = 80.385;
  constexpr static double tMassPDG_ = 172.5;

  double eventCount_[12];

private:
  TTree* tree_;
  int prodMode_, decayMode_;
  double qScale_;
  LorentzVectors* electrons_, * muons_, * leptons_;
  LorentzVectors* bjets_;
  LorentzVectors* neutrinos_, * mets_;
  LorentzVectors* dileptons_, * lbCands_;
  LorentzVectors* wCands_, * tCands_;
  LorentzVectors* ttCands_;

  TH2F* hPtonElPt_DrsdElPt_;
  TH2F* hPtonMuPt_DrsdMuPt_;
  TH2F* hDrsdElPt_BareElPt_;
  TH2F* hDrsdMuPt_BareMuPt_;
  TH2F* hPtonBPt_PtclBPt_;
  TH2F* hPtonWPt_PtclWPt_;
  TH2F* hPtonTopPt_PtclTopPt_;
  TH2F* hPtonTTbarM_PtclTTbarM_;
  TH2F* hPtonTTbarPt_PtclTTbarPt_;

  TH2F* hPtonElPt_DrsdElPtRes_;
  TH2F* hPtonMuPt_DrsdMuPtRes_;
  TH2F* hDrsdElPt_BareElPtRes_;
  TH2F* hDrsdMuPt_BareMuPtRes_;
  TH2F* hPtonBPt_PtclBPtRes_;
  TH2F* hPtonWPt_PtclWPtRes_;
  TH2F* hPtonTopPt_PtclTopPtRes_;
  TH2F* hPtonTTbarM_PtclTTbarMRes_;
  TH2F* hPtonTTbarPt_PtclTTbarPtRes_;

};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  for ( int i=0; i<12; ++i ) eventCount_[i] = 0;

  bool doTree = pset.getUntrackedParameter<bool>("doTree", true);

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
  leptons_   = new LorentzVectors();
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
    tree_->Branch("leptons"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &leptons_  );
    tree_->Branch("bjets"    , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets_    );
    tree_->Branch("neutrinos", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &neutrinos_);
    tree_->Branch("mets"     , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &mets_     );

    tree_->Branch("dileptons", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &dileptons_);
    tree_->Branch("lbCands"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &lbCands_  );
    tree_->Branch("wCands"   , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &wCands_   );
    tree_->Branch("tCands"   , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &tCands_   );
    tree_->Branch("ttCands"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &ttCands_  );
  }

  hPtonElPt_DrsdElPt_ = fs->make<TH2F>("hPtonElPt_DrsdElPt", "Compared electrons;Parton electron p_{T} (GeV/c);Drsd electron p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPtonMuPt_DrsdMuPt_ = fs->make<TH2F>("hPtonMuPt_DrsdMuPt", "Compared muons;Parton muon p_{T} (GeV/c);Drsd muon p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hDrsdElPt_BareElPt_ = fs->make<TH2F>("hDrsdElPt_BareElPt", "Compared electrons;Drsd electron p_{T} (GeV/c);Bare electron p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hDrsdMuPt_BareMuPt_ = fs->make<TH2F>("hDrsdMuPt_BareMuPt", "Compared muons;Drsd muon p_{T} (GeV/c);Bare muon p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPtonBPt_PtclBPt_ = fs->make<TH2F>("hPtonBPt_PtclBPt", "Compared b jets;B quark p_{T} (GeV/c);B jet p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPtonWPt_PtclWPt_ = fs->make<TH2F>("hPtonWPt_PtclWPt", "Compared top;Parton W p_{T} (GeV/c);Particle W p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPtonTopPt_PtclTopPt_ = fs->make<TH2F>("hPtonTopPt_PtclTopPt", "Compared top;Parton top p_{T} (GeV/c);Particle top p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);
  hPtonTTbarM_PtclTTbarM_ = fs->make<TH2F>("hPtonTTbarM_PtclTTbarM", "Compared ttbar;Parton t#bar{t} M (GeV/c^{2});Particle t#bar{t} M(GeV/c^{2})", 400, 0, 2000, 400, 0, 2000);
  hPtonTTbarPt_PtclTTbarPt_ = fs->make<TH2F>("hPtonTTbarPt_PtclTTbarPt", "Compared t#bar{t};Parton t#bar{t} p_{T} (GeV/c);Particle t#bar{t} p_{T} (GeV/c)", 100, 0, 500, 100, 0, 500);

  hPtonElPt_DrsdElPtRes_ = fs->make<TH2F>("hPtonElPt_DrsdElPtRes", "Compared electrons;Parton electron p_{T} (GeV/c);Drsd electron p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hPtonMuPt_DrsdMuPtRes_ = fs->make<TH2F>("hPtonMuPt_DrsdMuPtRes", "Compared muons;Parton muon p_{T} (GeV/c);Drsd muon p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hDrsdElPt_BareElPtRes_ = fs->make<TH2F>("hDrsdElPt_BareElPtRes", "Compared electrons;Drsd electron p_{T} residual (GeV/c);Bare electron p_{T} (GeV/c)", 100, 0, 500, 100, -50, 50);
  hDrsdMuPt_BareMuPtRes_ = fs->make<TH2F>("hDrsdMuPt_BareMuPtRes", "Compared muons;Drsd muon p_{T} (GeV/c);Bare muon p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hPtonBPt_PtclBPtRes_ = fs->make<TH2F>("hPtonBPt_PtclBPtRes", "Compared b jets;B quark p_{T} (GeV/c);B jet p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hPtonWPt_PtclWPtRes_ = fs->make<TH2F>("hPtonWPt_PtclWPtRes", "Compared top;Parton W p_{T} (GeV/c);Particle W p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hPtonTopPt_PtclTopPtRes_ = fs->make<TH2F>("hPtonTopPt_PtclTopPtRes", "Compared top;Parton top p_{T} (GeV/c);Particle top p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);
  hPtonTTbarM_PtclTTbarMRes_ = fs->make<TH2F>("hPtonTTbarM_PtclTTbarMRes", "Compared ttbar;Parton t#bar{t} M (GeV/c^{2});Particle t#bar{t} M residual(GeV/c^{2})", 400, 0, 2000, 200, -100, 100);
  hPtonTTbarPt_PtclTTbarPtRes_ = fs->make<TH2F>("hPtonTTbarPt_PtclTTbarPtRes", "Compared t#bar{t};Parton t#bar{t} p_{T} (GeV/c);Particle t#bar{t} p_{T} residual (GeV/c)", 100, 0, 500, 100, -50, 50);

}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  eventCount_[0] += 1;

  electrons_->clear();
  muons_->clear();
  leptons_->clear();
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
  if ( parton1Id == 0 and parton2Id == 0 ) prodMode_ = 0; // gg fusion
  else if ( parton1Id != 0 and parton2Id != 0 ) prodMode_ = 1; // qq collision
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
      if ( std::abs(p->eta()) > neutrinoMaxEta_ ) continue;
      neutrinos_->push_back(p->p4());
    }
  }
  std::sort(neutrinos_->begin(), neutrinos_->end(), GreaterByPt<math::XYZTLorentzVector>());

  // Do dressup and keep leptons
  std::vector<int> electronsQ, muonsQ;
  for ( unsigned int i=0, n=stableLeptons.size(); i<n; ++i )
  {
    const reco::GenParticle* p = stableLeptons.at(i);
    math::XYZTLorentzVector p4 = p->p4();
    const double isolation = dressup(p4, allStables);
    if ( p4.pt() < leptonMinPt_ or std::abs(p4.eta()) > leptonMaxEta_ ) continue;
    if ( isolation > 0.2*p4.pt() ) continue;

    const unsigned int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 )
    {
      electrons_->push_back(p4);
      electronsQ.push_back(p->charge());
      hDrsdElPt_BareElPt_->Fill(p4.pt(), p->pt());
      hDrsdElPt_BareElPtRes_->Fill(p4.pt(), p->pt()-p4.pt());
    }
    else if ( absPdgId == 13 )
    {
      muons_->push_back(p4);
      muonsQ.push_back(p->charge());
      hDrsdMuPt_BareMuPt_->Fill(p4.pt(), p->pt());
      hDrsdMuPt_BareMuPtRes_->Fill(p4.pt(), p->pt()-p4.pt());
    }
  }
  // Determine decay mode
  int dileptonQ;
  math::XYZTLorentzVector lepton1, lepton2;
  if ( electrons_->size() == 2 and muons_->size() == 0 )
  {
    if ( electrons_->at(0).pt() < electrons_->at(1).pt() )
    {
      std::swap(electrons_->at(0), electrons_->at(1));
      std::swap(electronsQ[0], electronsQ[1]);
    }
    decayMode_ = 1;
    lepton1 = electrons_->at(0);
    lepton2 = electrons_->at(1);
    dileptonQ = electronsQ[0]+electronsQ[1];
  }
  else if ( electrons_->size() == 0 and muons_->size() == 2 )
  {
    if ( muons_->at(0).pt() < muons_->at(1).pt() )
    {
      std::swap(muons_->at(0), muons_->at(1));
      std::swap(muonsQ[0], muonsQ[1]);
    }
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
    if ( lepton1.pt() < lepton2.pt() ) std::swap(lepton1, lepton2);
  }
  else return;
  eventCount_[1] += 1;
  leptons_->push_back(lepton1);
  leptons_->push_back(lepton2);

  // Opposite charge
  if ( dileptonQ != 0 ) return;
  eventCount_[2] += 1;

  dileptons_->push_back(lepton1+lepton2);
  const double dileptonMass = dileptons_->at(0).mass();
  // Z veto
  if ( decayMode_ != 3 and (dileptonMass <= 20 or std::abs(dileptonMass-zMassPDG_) < 10) ) return;
  eventCount_[3] += 1;

  // Calculate MET
  if ( neutrinos_->size() < 2 ) return;
  eventCount_[4] += 1;
  const math::XYZTLorentzVector metLVec = neutrinos_->at(0) + neutrinos_->at(1);
  mets_->push_back(metLVec);

  // Find bjets
  int nJets = 0;
  for ( unsigned int i=0, n=genJetsHandle->size(); i<n; ++i )
  {
    const reco::GenJet& jet = genJetsHandle->at(i);
    if ( jet.pt() < jetMinPt_ or std::abs(jet.eta()) > jetMaxEta_ ) continue;
    if ( deltaR(jet.p4(), lepton1) < 0.5 or deltaR(jet.p4(), lepton2) < 0.5 ) continue;
    ++nJets;
    if ( !hasStableB(jet) ) continue;

    bjets_->push_back(jet.p4());
  }
  if ( nJets < 2 ) return;
  eventCount_[5] += 1;
  if ( bjets_->size() < 2 ) return;
  eventCount_[6] += 1;

  // Now we are ready for W/top combination.
  // Start from W candidate building
  int neutrinoIndex[2] = {-1, -1};
  if ( true ) { // Track to hide temp variables
    const math::XYZTLorentzVector w00 = lepton1+neutrinos_->at(0);
    const math::XYZTLorentzVector w11 = lepton2+neutrinos_->at(1);
    const math::XYZTLorentzVector w01 = lepton1+neutrinos_->at(1);
    const math::XYZTLorentzVector w10 = lepton2+neutrinos_->at(0);
    if ( std::abs(w00.mass() - wMassPDG_) + std::abs(w11.mass() - wMassPDG_)
       < std::abs(w01.mass() - wMassPDG_) + std::abs(w10.mass() - wMassPDG_) )
    {
      wCands_->push_back(w00);
      wCands_->push_back(w11);
      neutrinoIndex[0] = 0;
      neutrinoIndex[1] = 1;
    }
    else
    {
      wCands_->push_back(w01);
      wCands_->push_back(w10);
      neutrinoIndex[0] = 1;
      neutrinoIndex[1] = 0;
    }

    //if ( std::abs(wCands_->at(0).mass()-wMassPDG_) > 40 or std::abs(wCands_at(1).mass()-wMassPDG) > 40 ) return;
  }
  if ( neutrinoIndex[0] == -1 or neutrinoIndex[1] == -1 ) return;
  eventCount_[7] += 1;

  // Then proceed to top quark combination
  int topBIndex[] = {-1, -1};
  double minResMtop = 1e9;
  for ( unsigned int i=0, n=bjets_->size(); i<n; ++i )
  {
    const math::XYZTLorentzVector tPair1 = wCands_->at(0)+bjets_->at(i);
    for ( unsigned int j=0; j<n; ++j )
    {
      if ( i == j ) continue;
      const math::XYZTLorentzVector tPair2 = wCands_->at(1)+bjets_->at(j);
      const double resMtop = std::abs(tPair1.mass() - tMassPDG_) + std::abs(tPair2.mass() - tMassPDG_);
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
  eventCount_[8] += 1;

  lbCands_->push_back(lepton1+bjets_->at(topBIndex[0]));
  lbCands_->push_back(lepton2+bjets_->at(topBIndex[1]));
  tCands_->push_back(wCands_->at(0)+bjets_->at(topBIndex[0]));
  tCands_->push_back(wCands_->at(1)+bjets_->at(topBIndex[1]));
  if ( tCands_->at(0).pt() < tCands_->at(1).pt() )
  {
    std::swap(tCands_->at(0), tCands_->at(1));
  }

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

  matchAndFill(hPtonElPt_DrsdElPt_, hPtonElPt_DrsdElPtRes_, parton_e1, lepton1, lepton2);
  matchAndFill(hPtonElPt_DrsdElPt_, hPtonElPt_DrsdElPtRes_, parton_e2, lepton1, lepton2);
  matchAndFill(hPtonMuPt_DrsdMuPt_, hPtonMuPt_DrsdMuPtRes_, parton_m1, lepton1, lepton2);
  matchAndFill(hPtonMuPt_DrsdMuPt_, hPtonMuPt_DrsdMuPtRes_, parton_m2, lepton1, lepton2);
  matchAndFill(hPtonBPt_PtclBPt_, hPtonBPt_PtclBPtRes_, parton_b1, bjets_->at(0), bjets_->at(1));
  matchAndFill(hPtonBPt_PtclBPt_, hPtonBPt_PtclBPtRes_, parton_b2, bjets_->at(0), bjets_->at(1));
  matchAndFill(hPtonWPt_PtclWPt_, hPtonWPt_PtclWPtRes_, parton_w1, wCands_->at(0), wCands_->at(1));
  matchAndFill(hPtonWPt_PtclWPt_, hPtonWPt_PtclWPtRes_, parton_w2, wCands_->at(0), wCands_->at(1));
  matchAndFill(hPtonTopPt_PtclTopPt_, hPtonTopPt_PtclTopPtRes_, parton_t1, tCands_->at(0), tCands_->at(1));
  matchAndFill(hPtonTopPt_PtclTopPt_, hPtonTopPt_PtclTopPtRes_, parton_t2, tCands_->at(0), tCands_->at(1));
  hPtonTTbarPt_PtclTTbarPt_->Fill(parton_tt.pt(), ttCands_->at(0).pt());
  hPtonTTbarM_PtclTTbarM_->Fill(parton_tt.mass(), ttCands_->at(0).mass());
  hPtonTTbarPt_PtclTTbarPtRes_->Fill(parton_tt.pt(), ttCands_->at(0).pt()-parton_tt.pt());
  hPtonTTbarM_PtclTTbarMRes_->Fill(parton_tt.mass(), ttCands_->at(0).mass()-parton_tt.mass());

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
      const unsigned int absPdgId = abs(p->pdgId());
      if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 ) continue;
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

void TTbarGenLevelAnalyzer::matchAndFill(TH2F* hxy, TH2F* hres, const math::XYZTLorentzVector& p,
                                         const math::XYZTLorentzVector& v1, const math::XYZTLorentzVector& v2)
{
  if ( p.pt() <= 0.01 ) return;
  if ( v1.pt() > 0.01 and deltaR(p, v1) < 0.1 )
  {
    hxy->Fill(p.pt(), v1.pt());
    hres->Fill(p.pt(), v1.pt()-p.pt());
  }
  if ( v2.pt() > 0.01 and deltaR(p, v2) < 0.1 )
  {
    hxy->Fill(p.pt(), v2.pt());
    hres->Fill(p.pt(), v2.pt()-p.pt());
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);
