#ifndef TTbarCandidate_H
#define TTbarCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

#include <vector>

namespace Ko{

  class TTbarCandidate{
  public:
    TTbarCandidate(){}
    virtual ~TTbarCandidate(){}

    // status 3
    const std::vector<math::XYZTLorentzVector>& bquarks() const { return bquarks_; } 
    const std::vector<math::XYZTLorentzVector>& leptons() const { return leptons_; } 
    const std::vector<math::XYZTLorentzVector>& bJets() const { return bJets_; } 

    void building( const reco::GenParticleCollection* genParticles );
    void setMatchedBJets(const reco::GenJetCollection* genJets); 

    double mass() const { return mass_; }

    bool taunic() const { return taunic_; }

  private:

    std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
    bool hasBottom(const reco::Candidate &c);
    bool decayFromBHadron(const reco::Candidate &c);
    const reco::Candidate* lastBHadron(const reco::Candidate &c);
    bool isLastbottom(const reco::GenParticle&);
    bool isFromtop(const reco::GenParticle&);
    double deltaR( const reco::Candidate &pasObj, const reco::GenJet &proObj );


    std::vector<math::XYZTLorentzVector> bquarks_;
    std::vector<math::XYZTLorentzVector> leptons_;
    std::vector<math::XYZTLorentzVector> bJets_;

    double mass_;

    bool taunic_;


  };

}
#endif
