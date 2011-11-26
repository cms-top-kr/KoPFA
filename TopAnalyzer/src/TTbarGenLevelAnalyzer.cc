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

//#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"

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
  const reco::GenParticle* getDaughter(const reco::GenParticle* genParticle, const int pdgId) const;
  bool isBJet(const reco::GenJet* j) const;
  bool isJetFromDecay(const reco::GenParticle* p, const reco::GenJet* j) const;
  template<typename T>
  void setLeadingParticle(T* p, T*& p1, T*& p2) const;

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag genJetLabel_;
  edm::InputTag genMETLabel_;

  double electronMaxEta_, electronMinPt_;
  double muonMaxEta_, muonMinPt_;
  double jetMaxEta_, jetMinPt_;
  double metMinPt_;

  TH1F* hGenTTbarM_;

  TTree* tree_;
  //Ko::TTbarGenEvent* ttbarGenEvent_;

  double m_tt_, m_llbbnn_, m_lljjmet_, m_llbjbjmet_;
};

TTbarGenLevelAnalyzer::TTbarGenLevelAnalyzer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");
  genJetLabel_ = pset.getParameter<edm::InputTag>("genJet");
  genMETLabel_ = pset.getParameter<edm::InputTag>("genMET");

  //ttbarGenEvent_ = new Ko::TTbarGenEvent;

}

void TTbarGenLevelAnalyzer::beginJob()
{
  //ttbarGenEvent_->clear();

  edm::Service<TFileService> fs;
  const int ttbarMassNbins = 14;
  const double ttbarMassBins[ttbarMassNbins] = {
    0, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1400
  };

  hGenTTbarM_ = fs->make<TH1F>("hGenTTbarM", "Generator level t#bar{t} mass;M(t#bar{t}) [GeV/c^{2}]", ttbarMassNbins-1, ttbarMassBins);

  tree_ = fs->make<TTree>("tree", "Tree for ttbar dilepton generator level study");
  //tree_->Branch("ttbarGen", "Ko::TTbarGenEvent", &ttbarGenEvent_);
  tree_->Branch("m_tt", &m_tt_, "m_tt/D");
  tree_->Branch("m_llbbnn", &m_llbbnn_, "m_llbbnn/D");
  tree_->Branch("m_lljjmet", &m_lljjmet_, "m_lljjmet/D");
  tree_->Branch("m_llbjbjmet", &m_llbjbjmet_, "m_llbjbjmet/D");
}

void TTbarGenLevelAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( !genParticleHandle.isValid() ) return;

  edm::Handle<std::vector<reco::GenJet> > genJetHandle;
  event.getByLabel(genJetLabel_, genJetHandle);
  if ( !genJetHandle.isValid() or genJetHandle.failedToGet() ) return;

  edm::Handle<std::vector<reco::GenMET> > genMETHandle;
  event.getByLabel(genMETLabel_, genMETHandle);
  if ( !genMETHandle.isValid() ) return;
  const reco::GenMET& genMET = *genMETHandle->begin();
  const reco::Candidate::LorentzVector metLVec(genMET.px(), genMET.py(), 0, genMET.pt());

  //ttbarGenEvent_->clear();
  //ttbarGenEvent_->set(genParticleHandle->begin(), genParticleHandle->end());

  const reco::GenParticle* tP = 0, * tM = 0; 
  const reco::GenParticle* wP = 0, * wM = 0;
  const reco::GenParticle* l1 = 0, * l2 = 0;
  const reco::GenParticle* b1 = 0, * b2 = 0;
  const reco::GenParticle* n1 = 0, * n2 = 0;

  for ( reco::GenParticleCollection::const_iterator genParticle = genParticleHandle->begin();
        genParticle != genParticleHandle->end(); ++genParticle )
  {
    const reco::GenParticle* p = &*genParticle;

    if ( genParticle->status() == 3 )
    {
      switch ( genParticle->pdgId() )
      {
        case   6: tP = p; break;
        case  -6: tM = p; break;
        case  24: wP = p; break;
        case -24: wM = p; break;
        // Find leading b-quarks
        case   5:
        case  -5:
          setLeadingParticle(p, b1, b2);
          break;
      }
    }
    // Find leading leptons
    else if ( genParticle->status() == 1 )
    {
      const int absPdgId = abs(genParticle->pdgId());
      switch ( absPdgId )
      {
        case 11:
        case 13:
          setLeadingParticle(p, l1, l2);
          break;
        case 10:
        case 12:
        case 14:
          setLeadingParticle(p, n1, n2);
          break;
      }
    }
  }

  const reco::GenParticle* bP = getDaughter(tP, 5);
  const reco::GenParticle* bM = getDaughter(tM, 5);

  const reco::GenJet* j1 = 0, * j2 = 0;
  const reco::GenJet* bj1 = 0, * bj2 = 0;
  const reco::GenJet* jP = 0, * jM = 0;
  for ( std::vector<reco::GenJet>::const_iterator genJet = genJetHandle->begin();
        genJet != genJetHandle->end(); ++genJet )
  {
    const reco::GenJet* j = &*genJet;
    setLeadingParticle(j, j1, j2);

    // Find B-Jet
    if ( isBJet(j) )
    {
      setLeadingParticle(j, bj1, bj2);

      // Find matched jets from top-b decay
      // Choose only leading jet if multiple matches found for each top quarks
      const double jPt = j->pt();
      if ( bP and isJetFromDecay(bP, j) and ( !jP or jP->pt() < jPt ) ) jP = j;
      if ( bM and isJetFromDecay(bM, j) and ( !jM or jM->pt() < jPt ) ) jM = j;
    }
  }

  if ( tP and tM ) m_tt_ = (tP->p4() + tM->p4()).M();
  if ( l1 and l2 )
  {
    const reco::Candidate::LorentzVector zLVec = l1->p4()+l2->p4();
    //if ( b1 and b2 and n1 and n2 ) m_llbbnn_ = (zLVec+b1->p4()+b2->p4()+n1->p4()+n2->p4()).M();
    if ( bP and bM and n1 and n2 ) m_llbbnn_ = (zLVec+bP->p4()+bM->p4()+n1->p4()+n2->p4()).M();
    if ( j1 and j2 )
    {
      const reco::Candidate::LorentzVector j1LVec(j1->px(), j1->py(), j1->pz(), j1->p());
      const reco::Candidate::LorentzVector j2LVec(j2->px(), j2->py(), j2->pz(), j2->p());
      m_lljjmet_ = (zLVec+j1LVec+j2LVec+metLVec).M();
    }
    if ( bj1 and bj2 )
    {
      const reco::Candidate::LorentzVector bj1LVec(bj1->px(), bj1->py(), bj1->pz(), bj1->p());
      const reco::Candidate::LorentzVector bj2LVec(bj2->px(), bj2->py(), bj2->pz(), bj2->p());
      m_llbjbjmet_ = (zLVec+bj1LVec+bj2LVec+metLVec).M();
    }
  }

  tree_->Fill();
}

bool TTbarGenLevelAnalyzer::isBJet(const reco::GenJet* jet) const
{
  std::vector<const GenParticle*> constituents = jet->getGenConstituents();
  for ( std::vector<const GenParticle*>::const_iterator constituent = constituents.begin();
        constituent != constituents.end(); ++constituent )
  {
    const reco::GenParticle* p = *constituent;
    while ( true ) 
    {
      if ( !p ) break;

      if ( p->status() == 3 and abs(p->pdgId()) == 5 )
      {
        // This is B jet: A jet constituent came from b-quark in hard process
        return true;
      }
      else
      {
        // Continue following up mothers
        p = dynamic_cast<const reco::GenParticle*>(p->mother());
      }
    }
  }

  // If control reaches here, no b quarks found in the mothers of jet constituent
  return false;
}

bool TTbarGenLevelAnalyzer::isJetFromDecay(const reco::GenParticle* genParticle, const reco::GenJet* jet) const 
{
  std::vector<const GenParticle*> constituents = jet->getGenConstituents();
  for ( std::vector<const GenParticle*>::const_iterator constituent = constituents.begin();
        constituent != constituents.end(); ++constituent )
  {
    const reco::GenParticle* p = *constituent;
    while ( true )
    {
      if ( !p ) break;

      if ( genParticle->collisionId() == p->collisionId() ) return true;
    }
  }

  return false;
}

const reco::GenParticle* TTbarGenLevelAnalyzer::getDaughter(const reco::GenParticle* genParticle, const int pdgId) const
{
  if ( !genParticle ) return 0;

  for ( reco::candidate::const_iterator daughter = genParticle->begin();
        daughter != genParticle->end(); ++daughter )
  {
    const reco::GenParticle* genDaughter = dynamic_cast<const reco::GenParticle*>(&*daughter);
    if ( !genDaughter ) return 0;
    if ( daughter->status() == 3 and abs(daughter->pdgId()) == pdgId ) return genDaughter;
  }
  return 0;
}

template<typename T>
void TTbarGenLevelAnalyzer::setLeadingParticle(T* p, T*& p1, T*& p2) const
{
  if ( !p1 ) p1 = p;
  else
  {
    if ( !p2 ) p2 = p;
    if ( p2->pt() < p->pt() ) p2 = p;
    if ( p1->pt() < p2->pt() ) std::swap(p1, p2);
  }
}

DEFINE_FWK_MODULE(TTbarGenLevelAnalyzer);

