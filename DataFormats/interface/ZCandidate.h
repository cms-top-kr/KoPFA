#ifndef ZCandidate_H
#define ZCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

namespace Ko{

  class ZCandidate{
  public:
    ZCandidate(){}
    virtual ~ZCandidate(){}

    ZCandidate(const Ko::Lepton& leg1, const Ko::Lepton& leg2) {
      leg1_ = leg1;
      leg2_ = leg2;
      mass_ = (leg1_+leg2_).M(); 
      sign_ = leg1.charge()*leg2.charge();
    }

    ZCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, const float& sign) {
      lv1_= leg1 ;
      lv2_= leg2 ;
      mass_ = (leg1_+leg2_).M();
      sign_ = sign;
    }

    const Ko::Lepton& leg1() const { return leg1_; }
    const Ko::Lepton& leg2() const { return leg2_; }
    const reco::Candidate::LorentzVector& lv1() const { return lv1_;}
    const reco::Candidate::LorentzVector& lv2() const { return lv2_;}

    float mass() const { return mass_; }
    float sign() const { return sign_; }
    float deltaR() const; 
    float deltaPhi() const;
  private:

    Ko::Lepton leg1_;
    Ko::Lepton leg2_;
    reco::Candidate::LorentzVector lv1_;
    reco::Candidate::LorentzVector lv2_;

    float mass_;
    float sign_;
  };



}
#endif
