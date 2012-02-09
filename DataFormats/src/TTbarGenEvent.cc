#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "CommonTools/Utils/interface/PtComparator.h"

using namespace Ko;

const reco::GenParticle* TTbarGenEvent::getDaughter(const reco::GenParticle* mother, const int absPdgId)
{
  if ( !mother ) return 0;

  for ( int i=0, n = mother->numberOfDaughters(); i < n; ++i )
  {
    const reco::GenParticle* p = dynamic_cast<const reco::GenParticle*>(mother->daughter(i));
    if ( !p ) return 0;
    if ( abs(p->pdgId()) == absPdgId ) return p;
  }
  
  return 0;
}

void TTbarGenEvent::clear()
{
  mTT_ = -1;
  qcdBquarks_.clear();
  leptons_.clear();
  acceptedLeptons_.clear();
  jets_.clear();
  bJets_.clear();

  met_ = metX_ = metY_ = 0;
}

void TTbarGenEvent::set(const reco::GenParticleCollection* genParticles,
                        const reco::GenJetCollection* genJets,
                        const reco::GenMET* genMET)
{
  clear();

  // Find TTbar pair
  const reco::GenParticle* t1 = 0, * t2 = 0;
  const reco::GenParticleCollection::const_iterator begin = genParticles->begin();
  const  reco::GenParticleCollection::const_iterator end = genParticles->end();
  for ( reco::GenParticleCollection::const_iterator p = begin; p != end; ++p )
  {
    if ( p->status() != 3 ) continue;
    if ( p->pdgId() ==  6 ) t1 = &*p;
    else if ( p->pdgId() == -6 ) t2 = &*p;

    if ( t1 and t2 ) break;
  }

  // We don't have to analyze non-ttbar events
  if ( !t1 or !t2 ) return;

  // Get daughters of top quarks
  const reco::GenParticle* w1 = 0, * w2 = 0;
  const reco::GenParticle* b1 = 0, * b2 = 0;
  for ( int i = 0, n = t1->numberOfDaughters(); i < n; ++i )
  {
    const reco::GenParticle* p = dynamic_cast<const reco::GenParticle*>(t1->daughter(i));
    if ( !p ) continue;
    if ( p->status() != 3 ) continue;
    if ( abs(p->pdgId()) == 24 ) w1 = p;
    else if ( abs(p->pdgId()) == 5 ) b1 = p;
  }
  for ( int i = 0, n = t2->numberOfDaughters(); i < n; ++i )
  {
    const reco::GenParticle* p = dynamic_cast<const reco::GenParticle*>(t2->daughter(i));
    if ( !p ) continue;
    if ( p->status() != 3 ) continue;
    if ( abs(p->pdgId()) == 24 ) w2 = p;
    else if ( abs(p->pdgId()) == 5 ) b2 = p;
  }
  if ( !b1 or !b2 ) return; // This will not happen, all top quarks decay to W and b

  t1_ = t1->p4();
  t2_ = t2->p4();
  mTT_ = (t1_+t2_).M();
  b1_ = b1->p4();
  b2_ = b2->p4();

  // Get leptons from W decay
  const reco::GenParticle* l1 = 0, * l2 = 0;
  const reco::GenParticle* tau1 = 0, * tau2 = 0; 
  for ( int i = 0, n = w1->numberOfDaughters(); i < n; ++i )
  {
    const reco::GenParticle* p = dynamic_cast<const reco::GenParticle*>(w1->daughter(i));
    if ( !p ) continue;
    if ( p->status() != 3 ) continue;
    const int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 or absPdgId == 13 )
    {
      l1 = p;
      break;
    }
    else if ( absPdgId == 15 )
    {
      tau1 = p;
      break;
    }
  }
  for ( int i=0, n = w2->numberOfDaughters(); i < n; ++i )
  {
    const reco::GenParticle* p = dynamic_cast<const reco::GenParticle*>(w2->daughter(i));
    if ( !p ) continue;
    if ( p->status() != 3 ) continue;
    const int absPdgId = abs(p->pdgId());
    if ( absPdgId == 11 or absPdgId == 13 )
    {
      l2 = p;
      break;
    }
    else if ( absPdgId == 15 )
    {
      tau2 = p;
      break;
    }
  }

  // Special care is needed for tau->lepton decay
  if ( tau1 and tau1->numberOfDaughters() >= 2 )
  {
    const reco::GenParticle* tauW = getDaughter(tau1, 24);
    if ( tauW )
    {
      if ( !l1 ) l1 = getDaughter(tauW, 11);
      if ( !l1 ) l1 = getDaughter(tauW, 13);
      if ( l1 ) ++tauDecay;
    }
  }
  if ( tau2 and tau2->numberOfDaughters() >= 2 )
  {
    const reco::GenParticle* tauW = getDaughter(tau2, 24);
    if ( tauW )
    {
      if ( !l2 ) l2 = getDaughter(tauW, 11);
      if ( !l2 ) l2 = getDaughter(tauW, 13);
      if ( l2 ) ++tauDecay;
    }
  }

  // Get particles which were not considered yet
  std::vector<const reco::GenParticle*> acceptedLeptons;
  std::vector<const reco::GenParticle*> qcdBquarks;
  for ( reco::GenParticleCollection::const_iterator p = begin;
        p != end; ++p )
  {
    const int status = p->status();
    const int absPdgId = abs(p->pdgId());

    // Collect stable leptons within acceptance
    if ( status == 1 )
    {
      if ( absPdgId == 11 or absPdgId == 13 )
      {
        if ( p->pt() < 20 or abs(p->eta()) > 2.4 ) continue;

        acceptedLeptons.push_back(&*p);
      }
      else if ( genMET and (absPdgId == 12 or absPdgId == 14 or absPdgId == 16) )
      {
        metX_ += p->px();
        metY_ += p->py();
      }
    }

    // Collect B quarks not from Top quark decay (and itself)
    if ( status == 2 and absPdgId == 5 )
    {
      const int motherAbsPdgId = abs(p->mother()->pdgId()); 
      if ( motherAbsPdgId == 6 ) continue;

      if ( motherAbsPdgId == 2212 or motherAbsPdgId == 21 or
           motherAbsPdgId <= 4 ) qcdBquarks.push_back(&*p);
    }
  }

  for ( int i = 0, n = acceptedLeptons.size(); i < n; ++i )
  {
    acceptedLeptons_.push_back(acceptedLeptons[i]->p4());
  }
  std::sort(acceptedLeptons_.begin(), acceptedLeptons_.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  if ( genJets )
  {
    const reco::GenJetCollection::const_iterator begin = genJets->begin();
    const reco::GenJetCollection::const_iterator end = genJets->end();

    for ( reco::GenJetCollection::const_iterator jet = begin; jet != end; ++jet )
    {
      const double jetPt = jet->pt();
      if ( jetPt < 30 or abs(jet->eta()) > 2.4 ) continue;

      const math::XYZTLorentzVector jetP4 = jet->p4();
      jets_.push_back(jetP4);

      // Find b quark matching genJet
      if ( (deltaR(jetP4, b1_) < 0.4 and abs(jetPt-b1_.pt())/jetPt < 3.0) or 
           (deltaR(jetP4, b2_) < 0.4 and abs(jetPt-b2_.pt())/jetPt < 3.0) ) bJets_.push_back(jetP4);
      else
      {
        for ( int i = 0, n = qcdBquarks_.size(); i < n; ++i )
        {
          if ( deltaR(jetP4, qcdBquarks_[i]) < 0.4 and abs(jetPt-qcdBquarks_[i].pt())/jetPt < 3.0 )
          {
            bJets_.push_back(jetP4);
            break;
          }
        }
      }
    }
  }

  if ( genMET )
  {
    metX_ = genMET->px();
    metY_ = genMET->py();
  }
  met_ = hypot(metX_, metY_);

  // TTbar decay modes
  if ( l1 and l2 )
  {
    // Dilepton channels 
    leptons_.push_back(l1->p4());
    leptons_.push_back(l2->p4());

    lep1Type_ = l1->pdgId();
    lep2Type_ = l2->pdgId();
  }
  else if ( l1 or l2 )
  {
    // Lepton+Jet channels
    if ( l1 )
    {
      leptons_.push_back(l1->p4());
      lep1Type_ = l1->pdgId();
    }
    else lep1Type_ = 0;

    if ( l2 )
    {
      leptons_.push_back(l2->p4());
      lep2Type_ = l2->pdgId();
    }
    else lep2Type_ = 0;
  }
}

