#ifndef TTbarGenEvent_H
#define TTbarGenEvent_H

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include <vector>

namespace Ko
{

class TTbarGenEvent
{
public:
  TTbarGenEvent() {};
  ~TTbarGenEvent() {};

  void set(const reco::GenParticleCollection* genParticles,
           const reco::GenJetCollection* genJets,
           const reco::GenMET* genMET);

private:
  void clear();

private:
  math::XYZTLorentzVector tA_, tB_;
  math::XYZTLorentzVector bA_, bB_;
  math::XYZTLorentzVector lA_, lB_;
  math::XYZTLorentzVector jA_, jB_;

  math::XYZTLorentzVector em1_, em2_;
  math::XYZTLorentzVector j1_, j2_;

  int mumuDecay;
  int eeDecay;
  int emuDecay;
  int tauDecay;
 
  math::XYZTLorentzVector met_;
  math::XYZTLorentzVector allNuXY_;

  double m_tt;
  double m_stable, m_stableBJets;
  double m_hardTrue, m_hardNuXY, m_hardMET;

};

}

#endif

