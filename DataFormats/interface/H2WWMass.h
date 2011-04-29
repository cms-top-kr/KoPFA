#ifndef H2WWMass_H
#define H2WWMass_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "TLorentzVector.h"

namespace Ko{

  class H2WWMass{
  public:
    H2WWMass(){}
    virtual ~H2WWMass(){}

    H2WWMass(const reco::Candidate::LorentzVector& lep1, const reco::Candidate::LorentzVector& lep2, const reco::Candidate::LorentzVector& met, const float& charge1, const float& charge2);

    const TLorentzVector& leg1() const { return leg1_; }
    const TLorentzVector& leg2() const { return leg2_; }
    const TLorentzVector& nu1() { return nu1_; };
    const TLorentzVector& nu2() { return nu2_; };
    const TLorentzVector& met() { return met__; };

    float M() const { return M_; }
    float charge1() const { return charge1_; }
    float charge2() const { return charge2_; }
    float Mt2() const { return Mt2_; }
    float maosM() const { return maosM_; }
    float SM() const { return SM_; }

  private:

    void SetM();
    void SetMaosM();
    void SetSM();

    reco::Candidate::LorentzVector lep1_;
    reco::Candidate::LorentzVector lep2_;
    reco::Candidate::LorentzVector met_;

    TLorentzVector leg1_;
    TLorentzVector leg2_;
    TLorentzVector nu1_;
    TLorentzVector nu2_;
    TLorentzVector met__;

    float M_;
    float Mt2_;    
    float maosM_;
    float SM_;

    float charge1_;
    float charge2_;

  };

}
#endif
