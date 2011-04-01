#ifndef ZCandidate_H
#define ZCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "TLorentzVector.h"

namespace Ko{

  class ZCandidate{
  public:
    ZCandidate(){}
    virtual ~ZCandidate(){}
    ZCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, const float& sign) {
      leg1_ = leg1;
      leg2_ = leg2;
      mass_ = (leg1_+leg2_).M(); 
      sign_ = sign;
    }
    const reco::Candidate::LorentzVector& leg1() const { return leg1_; }
    const reco::Candidate::LorentzVector& leg2() const { return leg2_; }
    float mass() const { return mass_; }
    float sign() const { return sign_; }
    float deltaR() const; 
    float deltaPhi() const;
  private:

    reco::Candidate::LorentzVector leg1_;
    reco::Candidate::LorentzVector leg2_;
    float mass_;
    float sign_;
  };



}
#endif
