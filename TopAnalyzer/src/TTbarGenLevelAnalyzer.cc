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

#include "CommonTools/Utils/interface/PtComparator.h"

#include "TH1F.h"
#include "TTree.h"

#include <memory>
#include <vector>

using namespace std;
using namespace edm;
using namespace reco;

template <typename T>
struct GreaterByPtPtr
{
  bool operator()(T* t1, T* t2) const { return t1->pt() > t2->pt(); }
};

class TTbarGenLevelAnalyzer : public edm::EDAnalyzer
{
public:
  TTbarGenLevelAnalyzer(const edm::ParameterSet& pset);
  ~TTbarGenLevelAnalyzer();

  virtual void beginJob();
  virtual void endJob() {};
  virtual void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  const reco::GenParticle* getDaughter(const reco::GenParticle* genParticle, const int pdgId) const;

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag genJetLabel_;
  edm::InputTag genMETLabel_;

  TH1F* hGenTTbarM_;

  TTree* tree_;

  int br_nLeptonsTrue_;
  int br_nLeptons_; // Number of stable leptons with pT > 20 and eta < 2.5
  int br_nJets_; // Number of Jets with pT > 30 and eta < 2.5

  double br_mTT_;

  //TTbar dilepton
  std::vector<double>* br_mLL_;
  std::vector<double>* br_mLLJJMet_;
  //TTbar semilepton
  std::vector<double>* br_mtLMet_;
  std::vector<double>* br_mJJMin_;
  std::vector<double>* br_mJJAll_;
  std::vector<double>* br_mJJJJ_;
  std::vector<double>* br_mLJJJJMet_;

  GreaterByPtPtr<const reco::Candidate> greaterByPtPtr_;
};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");
  genJetLabel_ = pset.getParameter<edm::InputTag>("genJet");
  genMETLabel_ = pset.getParameter<edm::InputTag>("genMET");

  br_mLL_      = new std::vector<double>;
  br_mLLJJMet_ = new std::vector<double>;
  br_mtLMet_   = new std::vector<double>;
  br_mJJMin_   = new std::vector<double>;
  br_mJJAll_   = new std::vector<double>;
  br_mJJJJ_     = new std::vector<double>;
  br_mLJJJJMet_ = new std::vector<double>;

}

TTbarGenLevelAnalyzer::~TTbarGenLevelAnalyzer()
{
  if ( br_mLL_      ) delete br_mLL_     ;
  if ( br_mLLJJMet_ ) delete br_mLLJJMet_;
  if ( br_mtLMet_   ) delete br_mtLMet_  ;
  if ( br_mJJMin_   ) delete br_mJJMin_  ;
  if ( br_mJJAll_   ) delete br_mJJAll_  ;
  if ( br_mJJJJ_     ) delete br_mJJJJ_    ;
  if ( br_mLJJJJMet_ ) delete br_mLJJJJMet_;
}

void TTbarGenLevelAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  const int ttbarMassNbins = 14;
  const double ttbarMassBins[ttbarMassNbins] = {
    0, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1400
  };
  //const int ttbarMassNbins = sizeof(ttbarMassBins)/sizeof(double);

  hGenTTbarM_ = fs->make<TH1F>("hGenTTbarM", "Generator level t#bar{t} mass;M(t#bar{t}) [GeV/c^{2}]", ttbarMassNbins-1, ttbarMassBins);

  tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");

  tree_->Branch("nLeptonsTrue", &br_nLeptonsTrue_, "nLeptonsTrue/I");
  tree_->Branch("nLeptons"    , &br_nLeptons_    , "nLeptons/I"    );
  tree_->Branch("nJets"       , &br_nJets_       , "nJets/I"       );

  tree_->Branch("mTT", &br_mTT_, "mTT/D");
  tree_->Branch("mLL"      , "std::vector<double>", &br_mLL_     );
  tree_->Branch("mLLJJMet" , "std::vector<double>", &br_mLLJJMet_);
  tree_->Branch("mtLMet"   , "std::vector<double>", &br_mtLMet_  );
  tree_->Branch("mJJMin"   , "std::vector<double>", &br_mJJMin_  );
  tree_->Branch("mJJAll"   , "std::vector<double>", &br_mJJAll_  );
  tree_->Branch("mJJJJ"     , "std::vector<double>", &br_mJJJJ_    );
  tree_->Branch("mLJJJJMet" , "std::vector<double>", &br_mLJJJJMet_);

}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( !genParticleHandle.isValid() ) return;

  edm::Handle<edm::View<reco::GenJet> > genJetHandle;
  event.getByLabel(genJetLabel_, genJetHandle);
  if ( !genJetHandle.isValid() or genJetHandle.failedToGet() ) return;

  edm::Handle<std::vector<reco::GenMET> > genMETHandle;
  event.getByLabel(genMETLabel_, genMETHandle);
  if ( !genMETHandle.isValid() ) return;
  const reco::GenMET& genMET = *genMETHandle->begin();
  const reco::Candidate::LorentzVector metLVec(genMET.px(), genMET.py(), 0, genMET.pt());

  br_nLeptonsTrue_ = 0;
  br_nLeptons_     = 0;
  br_nJets_        = 0;

  br_mTT_ = 0;
  br_mLL_     ->clear();
  br_mLLJJMet_->clear();
  br_mtLMet_  ->clear();
  br_mJJMin_  ->clear();
  br_mJJAll_  ->clear();
  br_mJJJJ_    ->clear();
  br_mLJJJJMet_->clear();

  // Collect particles
  std::vector<const reco::GenParticle*> tQuarks;
  std::vector<const reco::GenParticle*> leptons;
  for ( reco::GenParticleCollection::const_iterator genParticle = genParticleHandle->begin();
        genParticle != genParticleHandle->end(); ++genParticle )
  {
    const reco::GenParticle* p = &*genParticle;

    if ( genParticle->status() == 3 and
         abs(genParticle->pdgId()) == 6 )
    {
      tQuarks.push_back(p);
    }
    else if ( genParticle->status() == 1 )
    {
      switch ( abs(genParticle->pdgId()) )
      {
        case 11:
        case 13:
          leptons.push_back(p);

          if ( genParticle->pt() > 20 and abs(genParticle->eta()) < 2.5 ) ++br_nLeptons_;
          break;
      }
    }
  }
  // We consider ttbar production only
  if ( tQuarks.size() > 2 ) cout << "&&&&& TTbarGenLevelAnalyzer &&&& More than 3 top quarks &&&&\n";
  if ( tQuarks.size() != 2 ) return;

  const reco::GenParticle* t1 = tQuarks[0];
  const reco::GenParticle* t2 = tQuarks[1];
  const double mTT = (t1->p4()+t2->p4()).M();
  br_mTT_ = mTT;
  hGenTTbarM_->Fill(mTT);

  // Leptons
  const reco::GenParticle* w1 = getDaughter(t1, 24);
  const reco::GenParticle* w2 = getDaughter(t2, 24);
  if ( getDaughter(w1, 11) != 0 or getDaughter(w1, 13) != 0 ) ++br_nLeptonsTrue_;
  if ( getDaughter(w2, 11) != 0 or getDaughter(w2, 13) != 0 ) ++br_nLeptonsTrue_;
  std::sort(leptons.begin(), leptons.end(), greaterByPtPtr_);

  std::vector<const reco::GenJet*> genJets;
  for ( edm::View<reco::GenJet>::const_iterator genJet = genJetHandle->begin();
        genJet != genJetHandle->end(); ++genJet )
  {
    genJets.push_back(&*genJet);

    if ( genJet->pt() > 30 and abs(genJet->eta()) < 2.5 ) ++br_nJets_;
  }
  std::sort(genJets.begin(), genJets.end(), greaterByPtPtr_);

  // TTbar-dilepton
  if ( br_nLeptonsTrue_ == 2 and leptons.size() >= 2 )
  {
    const reco::Candidate::LorentzVector llLVec = leptons[0]->p4()+leptons[1]->p4();
    br_mLL_->push_back(llLVec.M());

    if ( genJets.size() >= 2 )
    {
      br_mLLJJMet_->push_back((llLVec+genJets[0]->p4()+genJets[1]->p4()+metLVec).M());
    }
  }
  // TTbar-semilepton
  else if ( br_nLeptonsTrue_ == 1 and leptons.size() >= 1 )
  {
    const reco::Candidate::LorentzVector lMetLVec = leptons[0]->p4()+metLVec;
    br_mtLMet_->push_back(lMetLVec.Mt());

    if ( genJets.size() >= 4 )
    {
      const double m_j0j1 = (genJets[0]->p4()+genJets[1]->p4()).M();
      const double m_j1j2 = (genJets[1]->p4()+genJets[2]->p4()).M();
      const double m_j2j0 = (genJets[2]->p4()+genJets[0]->p4()).M();

      br_mJJMin_->push_back(std::min(m_j0j1, std::min(m_j1j2, m_j2j0)));
      br_mJJAll_->push_back(m_j0j1);
      br_mJJAll_->push_back(m_j1j2);
      br_mJJAll_->push_back(m_j2j0);

      const reco::Candidate::LorentzVector jjjjLVec = genJets[0]->p4()+genJets[1]->p4()+genJets[2]->p4()+genJets[3]->p4();
      br_mJJJJ_->push_back(jjjjLVec.M());
      br_mLJJJJMet_->push_back((lMetLVec+jjjjLVec).M());
    }
  }

  tree_->Fill();
}

const reco::GenParticle* TTbarGenLevelAnalyzer::getDaughter(const reco::GenParticle* genParticle, const int pdgId) const
{
  if ( !genParticle ) return 0;

  for ( reco::candidate::const_iterator daughter = genParticle->begin();
        daughter != genParticle->end(); ++daughter )
  {
    const reco::GenParticle* genDaughter = dynamic_cast<const reco::GenParticle*>(&*daughter);
    if ( !genDaughter ) return 0;
    if ( genDaughter->status() == 3 and abs(genDaughter->pdgId()) == pdgId ) return genDaughter;
  }
  return 0;
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

