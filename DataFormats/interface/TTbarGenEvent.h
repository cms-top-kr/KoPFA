#ifndef TTbarGenEvent_H
#define TTbarGenEvent_H

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <vector>

namespace Ko
{

class TTbarGenEvent
{
public:
  TTbarGenEvent() {};
  ~TTbarGenEvent() {};

  double m() const { return tt_.M(); };
  double mass() const { return m(); };
  double met() const { return met_; };
  
  void clear();
  void set(reco::GenParticleCollection::const_iterator begin,
           reco::GenParticleCollection::const_iterator end);

private:
  math::XYZTLorentzVector tt_;
  std::vector<math::XYZTLorentzVector> tQuarks_;
  std::vector<math::XYZTLorentzVector> bQuarks_;
  std::vector<math::XYZTLorentzVector> electrons_;
  std::vector<math::XYZTLorentzVector> muons_;
  double met_, metX_, metY_;

};

}

#endif

