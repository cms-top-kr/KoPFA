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

  double m() const { return tt_.M(); };
  double mass() const { return m(); };
  double met() const { return met_; };
  
  void clear();
  void set(const reco::GenParticleCollection* genParticles,
           const reco::GenJetCollection* genJets,
           const reco::GenMET* genMET);

private:
  math::XYZTLorentzVector tt_;
  std::vector<math::XYZTLorentzVector> tQuarks_;
  std::vector<math::XYZTLorentzVector> bQuarks_;
  std::vector<math::XYZTLorentzVector> leptons_;
  std::vector<math::XYZTLorentzVector> electrons_;
  std::vector<math::XYZTLorentzVector> muons_;
  std::vector<math::XYZTLorentzVector> taus_;
 
  int mumuDecay;
  int eeDecay;
  int emuDecay;
  int tauDecay;
 
  double met_, metX_, metY_;

  // Particle level objects
  std::vector<math::XYZTLorentzVector> stableElectrons_;
  std::vector<math::XYZTLorentzVector> stableMuons_;
  std::vector<math::XYZTLorentzVector> jets_;
  std::vector<int> jetsBMatch_;

private:
  bool isOverlap(const std::vector<const reco::GenParticle*>& pColl1,
                                const std::vector<const reco::GenParticle*>& pColl2,
                                int& nMatch);
  void findStableDaughters(const reco::GenParticle* p,
                           std::vector<const reco::GenParticle*>& stableDaughters);
  bool isBHadron(const int absPdgId);

};

}

#endif

