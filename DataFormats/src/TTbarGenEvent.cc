#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"

using namespace Ko;

void TTbarGenEvent::clear()
{
  tt_.SetPxPyPzE(0,0,0,0);
  tQuarks_.clear();
  bQuarks_.clear();
  leptons_.clear();

  mumuDecay = 0;
  eeDecay = 0;
  emuDecay = 0;
  tauDecay = 0;

  electrons_.clear();
  muons_.clear();
  taus_.clear();
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
        leptons_.push_back(genParticle->p4());
      }
      else if ( absPdgId == 13 ) 
      {
        muons_.push_back(genParticle->p4());
        leptons_.push_back(genParticle->p4());
      }
      else if ( absPdgId ==  15 )
      {
        int nlep = 0;
        unsigned int nTauDaughters = genParticle->numberOfDaughters();
        for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
          if( nlep == 1) break;
          const reco::Candidate* decay = genParticle->daughter(iTauDaughter);
          if ( abs(decay->pdgId()) == 11 ) {
            taus_.push_back(decay->p4());
            electrons_.push_back(genParticle->p4());
            leptons_.push_back(decay->p4());
            ++nlep;
          }else if( abs(decay->pdgId()) == 13  ){
            taus_.push_back(decay->p4());
            muons_.push_back(genParticle->p4());
            leptons_.push_back(decay->p4());
            ++nlep;
          }else if( abs(decay->pdgId()) == 15 ){
            unsigned int nTauGrandDaughters = decay->numberOfDaughters();
            for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
              const reco::Candidate* granddecay = decay->daughter(iTauGrandDaughter);
              if ( abs(granddecay->pdgId()) == 11 ) {
                taus_.push_back(granddecay->p4());
                electrons_.push_back(genParticle->p4());
                leptons_.push_back(granddecay->p4());
                ++nlep;
              }else if( abs(granddecay->pdgId()) == 13){
                taus_.push_back(granddecay->p4());
                muons_.push_back(genParticle->p4());
                leptons_.push_back(granddecay->p4());
                ++nlep;
              }else{
                continue;
              }
            }
          }else {
           continue;
          }
        }
      }
      else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
      {
        metX_ += genParticle->px();
        metY_ += genParticle->py();
      }
    }
  }

  if( leptons_.size() >= 2 ){

    if( taus_.size() > 0 ){
      tauDecay = 1;
    }
   
    if( muons_.size() >= 2 ){
      mumuDecay = 1;
    }else if( electrons_.size() >= 2){
      eeDecay = 1;
    }else if( electrons_.size() == 1 && muons_.size() == 1){
      emuDecay = 1;
    }else{
      std::cout << "it should not reach here" << std::endl;
    }

  }
  met_ = hypot(metX_, metY_);
}

