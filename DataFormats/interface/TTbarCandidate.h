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

    typedef std::vector<math::XYZTLorentzVector> LorentzVectors;

    // status 3
    const math::XYZTLorentzVector bquarks1() const { return bJets_[0]; }
    const math::XYZTLorentzVector bquarks2() const { return bJets_[1]; }

    const math::XYZTLorentzVector lepton1() const { return leptons_[0]; }
    const math::XYZTLorentzVector lepton2() const { return leptons_[1]; }

    const math::XYZTLorentzVector bJets1() const { return bJets_[0]; }
    const math::XYZTLorentzVector bJets2() const { return bJets_[1]; }
    const math::XYZTLorentzVector bJets3() const { return bJets_[2]; }
    const math::XYZTLorentzVector bJets4() const { return bJets_[3]; }
   
    void building( const reco::GenParticleCollection* genParticles );
    void setMatchedBJets(const reco::GenJetCollection* genJets); 

    double mass() const { return mass_; }

    bool taunic() const { return taunic_; }

    int NbJets() const { return NbJets_ ; }

  private:

    std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
    bool hasBottom(const reco::Candidate &c);
    bool decayFromBHadron(const reco::Candidate &c);
    const reco::Candidate* lastBHadron(const reco::Candidate &c);
    bool isLastbottom(const reco::GenParticle&);
    bool isFromtop(const reco::GenParticle&);
    double deltaR( const reco::Candidate &pasObj, const reco::GenJet &proObj );


    LorentzVectors bquarks_;
    LorentzVectors leptons_;
    LorentzVectors bJets_;

    double mass_;

    bool taunic_;

    int NbJets_;

  };

}
#endif
