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
           const reco::GenJetCollection* genJets = 0,
           const reco::GenMET* genMET = 0);

  double m() const { return mTT_; };
  double mass() const { return m(); };
  double met() const { return met_; };

private:
  void clear();
  const reco::GenParticle* getDaughter(const reco::GenParticle* mother, const int absPdgId);

  double mTT_;
  math::XYZTLorentzVector t1_, t2_;
  math::XYZTLorentzVector b1_, b2_;

  std::vector<math::XYZTLorentzVector> qcdBquarks_;

  std::vector<math::XYZTLorentzVector> leptons_;
  std::vector<math::XYZTLorentzVector> acceptedLeptons_;
  //std::vector<math::XYZTLorentzVector> electrons_;
  //std::vector<math::XYZTLorentzVector> muons_;
  //std::vector<math::XYZTLorentzVector> taus_;

  std::vector<math::XYZTLorentzVector> jets_;
  std::vector<math::XYZTLorentzVector> bJets_;

  int lep1Type_;
  int lep2Type_;
  int tauDecay;

  double met_, metX_, metY_;

};

}

#endif

