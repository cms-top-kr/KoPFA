#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"

using namespace Ko;

void TTbarGenEvent::clear()
{
  tt_.SetPxPyPzE(0,0,0,0);
  tQuarks_.clear();
  bQuarks_.clear();
  electrons_.clear();
  muons_.clear();
  met_ = metX_ = metY_ = 0;
}

void TTbarGenEvent::set(reco::GenParticleCollection::const_iterator begin,
                        reco::GenParticleCollection::const_iterator end)
{
  for ( reco::GenParticleCollection::const_iterator genParticle = begin;
        genParticle != end; ++genParticle )
  {
    if ( genParticle->status() != 3 ) continue;

    const int absPdgId = abs(genParticle->pdgId());

    if ( absPdgId == 6 )
    {
      tt_ += genParticle->p4();
      tQuarks_.push_back(genParticle->p4());
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
      bQuarks_.push_back(genParticle->p4());
    }
    if ( motherAbsPdgId == 24 )
    {
      if ( absPdgId == 11 )
      {
        electrons_.push_back(genParticle->p4());
      }
      else if ( absPdgId == 13 ) 
      {
        muons_.push_back(genParticle->p4());
      }
      else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
      {
        metX_ += genParticle->px();
        metY_ += genParticle->py();
      }
    }
  }

  met_ = hypot(metX_, metY_);
}

