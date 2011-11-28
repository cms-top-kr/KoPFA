#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TMath.h"

using namespace Ko;
using namespace reco;

bool isOverlap(const reco::GenJet* j, const reco::GenParticle* p)
{
  if ( !j or !p ) return false;

  std::vector<const GenParticle*> constituents = j->getGenConstituents();
  for ( std::vector<const GenParticle*>::const_iterator constituent = constituents.begin();
        constituent != constituents.end(); ++constituent)
  {
    const reco::GenParticle* jp = *constituent;

    if ( jp->pdgId() == p->pdgId() and
         (jp->p4()-p->p4()).P() < 1e-3 ) return true;
  }

  return false;
}

bool isJetDecayFrom(const reco::GenParticle* genParticle, const reco::GenJet* jet)
{
  if ( deltaR(*genParticle, *jet) < 0.4 ) return true;
  else return false;

  std::vector<const GenParticle*> constituents = jet->getGenConstituents();
  for ( std::vector<const GenParticle*>::const_iterator constituent = constituents.begin();
        constituent != constituents.end(); ++constituent )
  {
    const reco::GenParticle* p = *constituent;
    while ( p )
    {
      if ( genParticle->pdgId() == p->pdgId() and 
           (genParticle->p4()-p->p4()).P() < 1e-3 ) return true;
      else p = dynamic_cast<const reco::GenParticle*>(p->mother());
    }
  }

  return false;
}

const reco::GenParticle* findDaughter(const reco::GenParticle* genParticle, const int pdgId)
{
  if ( !genParticle ) return 0;

  for ( reco::candidate::const_iterator daughter = genParticle->begin();
        daughter != genParticle->end(); ++daughter )
  {
    const reco::GenParticle* genDaughter = dynamic_cast<const reco::GenParticle*>(&*daughter);
    if ( !genDaughter ) return 0;

    //if ( daughter->status() == 3 and abs(daughter->pdgId()) == pdgId ) return genDaughter;
    if ( abs(genDaughter->pdgId()) == pdgId )
    {
      if ( genDaughter->status() == 3 or genDaughter->status() == 1 ) return genDaughter;
      else return findDaughter(genDaughter, pdgId);
    }
    else if ( genDaughter->pdgId() == genParticle->pdgId() ) return findDaughter(genDaughter, pdgId);

  }
  return 0;
}

template<typename T>
void setLeadingParticle(T* p, T*& p1, T*& p2)
{
  if ( !p1 ) p1 = p;
  else
  {
    if ( !p2 ) p2 = p;
    if ( p2->pt() < p->pt() ) p2 = p;
    if ( p1->pt() < p2->pt() ) std::swap(p1, p2);
  }
}

void TTbarGenEvent::clear()
{
  tA_.SetPxPyPzE(0,0,0,0);
  tB_.SetPxPyPzE(0,0,0,0);
  bA_.SetPxPyPzE(0,0,0,0);
  bB_.SetPxPyPzE(0,0,0,0);
  lA_.SetPxPyPzE(0,0,0,0);
  lB_.SetPxPyPzE(0,0,0,0);
  jA_.SetPxPyPzE(0,0,0,0);
  jB_.SetPxPyPzE(0,0,0,0);

  em1_.SetPxPyPzE(0,0,0,0);
  em2_.SetPxPyPzE(0,0,0,0);
  j1_.SetPxPyPzE(0,0,0,0);
  j2_.SetPxPyPzE(0,0,0,0);

  mumuDecay = 0;
  eeDecay = 0;
  emuDecay = 0;
  tauDecay = 0;

  met_.SetPxPyPzE(0,0,0,0);
  allNuXY_.SetPxPyPzE(0,0,0,0);

  m_tt = 0;
  m_stable = m_stableBJets = 0;
  m_hardTrue = m_hardNuXY = m_hardMET = 0;
}

void TTbarGenEvent::set(const reco::GenParticleCollection* genParticles,
                        const reco::GenJetCollection* genJets,
                        const reco::GenMET* genMET)
{
  clear();

  math::XYZTLorentzVector allNuLVec;
  double allNuXY_x = 0, allNuXY_y = 0;

  const reco::GenParticle* tA = 0, * tB = 0;
  const reco::GenParticle* em1 = 0, * em2 = 0;
  for ( reco::GenParticleCollection::const_iterator genParticle = genParticles->begin();
        genParticle != genParticles->end(); ++genParticle )
  {
    const reco::GenParticle* p = &*genParticle;

    if ( p->status() == 3 )
    {
      switch ( p->pdgId() )
      {
        case  6: tA = p; break;
        case -6: tB = p; break;
        default: break;
      }
    }
    else if ( p->status() == 1 )
    {
      switch ( abs(p->pdgId()) )
      {
        case 11:
        case 13:
          setLeadingParticle(p, em1, em2);
          break;
        case 12:
        case 14:
        case 16:
          allNuXY_x += p->px();
          allNuXY_y += p->py();
          allNuLVec += p->p4();
        default: break;
      }
    }
  }

  if ( tA ) tA_ = tA->p4();
  if ( tB ) tB_ = tB->p4();
  if ( em1 ) em1_ = em1->p4();
  if ( em2 ) em2_ = em2->p4();

  // Set Missing E_T
  met_.SetPxPyPzE(genMET->px(), genMET->py(), 0, genMET->pt());
  allNuXY_.SetPxPyPzE(allNuXY_x, allNuXY_y, 0, TMath::Hypot(allNuXY_x, allNuXY_y));

  const reco::GenParticle* bA = findDaughter(tA, 5);
  const reco::GenParticle* bB = findDaughter(tB, 5);
  if ( bA ) bA_ = bA->p4();
  if ( bB ) bB_ = bB->p4();

  const reco::GenParticle* wA = findDaughter(tA, 24);
  const reco::GenParticle* wB = findDaughter(tB, 24);

  const reco::GenParticle* lA = 0;
  if ( (lA = findDaughter(wA, 11)) ) ++eeDecay;
  else if ( (lA = findDaughter(wA, 13)) ) ++mumuDecay;
  else if ( (lA = findDaughter(wA, 15)) )
  {
    ++tauDecay;
    const reco::GenParticle* dau = 0;
    if ( (dau = findDaughter(lA, 11)) ) ++eeDecay;
    else if ( (dau = findDaughter(lA, 13)) ) ++mumuDecay;
  }

  const reco::GenParticle* lB = 0;
  if ( (lB = findDaughter(wB, 11)) ) ++eeDecay;
  else if ( (lB = findDaughter(wB, 13)) ) ++mumuDecay;
  else if ( (lB = findDaughter(wB, 15)) )
  {
    ++tauDecay;
    const reco::GenParticle* dau = 0;
    if ( (dau = findDaughter(lB, 11)) ) ++eeDecay;
    else if ( (dau = findDaughter(lB, 13)) ) ++mumuDecay;
  }

  if ( eeDecay == 1 and mumuDecay == 1 )
  {
    eeDecay = mumuDecay = 0;
    emuDecay = 1;
  }

  if ( lA ) lA_ = lA->p4();
  if ( lB ) lB_ = lB->p4();

  const reco::GenJet* jA = 0, * jB = 0;
  const reco::GenJet* j1 = 0, * j2 = 0;
  for ( reco::GenJetCollection::const_iterator genJet = genJets->begin();
        genJet != genJets->end(); ++genJet )
  {
    const reco::GenJet* j = &*genJet;

    if ( isJetDecayFrom(bA, j) and ( !jA or jA->pt() < j->pt() ) ) jA = j;
    if ( isJetDecayFrom(bB, j) and ( !jB or jB->pt() < j->pt() ) ) jB = j;

    //if ( isOverlap(j, lA) or isOverlap(j, lB) ) continue;
    if ( isOverlap(j, em1) or isOverlap(j, em2) ) continue;

    setLeadingParticle(j, j1, j2);
  }
  if ( jA ) jA_.SetXYZT(jA->px(), jA->py(), jA->pz(), jA->p());
  if ( jB ) jB_.SetXYZT(jB->px(), jB->py(), jB->pz(), jB->p());
  if ( j1 ) j1_.SetXYZT(j1->px(), j1->py(), j1->pz(), j1->p());
  if ( j2 ) j2_.SetXYZT(j2->px(), j2->py(), j2->pz(), j2->p());

  // Fill mass variables
  if ( tA and tB ) m_tt = (tA_+tB_).M();
  if ( em1 and em2 and j1 and j2 ) m_stable = (em1_+em2_+j1_+j2_+met_).M();
  if ( lA and lB )
  {
    const math::XYZTLorentzVector zLVec = lA_+lB_;
    const math::XYZTLorentzVector allVisTrue = zLVec+bA_+bB_;
    m_hardTrue = (allVisTrue+allNuLVec).M();
    m_hardNuXY = (allVisTrue+allNuXY_).M();
    m_hardMET = (allVisTrue+met_).M();

    if ( jA and jB ) m_stableBJets = (zLVec+jA_+jB_+met_).M();
  }

}

