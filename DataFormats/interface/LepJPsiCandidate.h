#ifndef LepJPsiCandidate_H
#define LepJPsiCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

namespace vallot{

  class LepJPsiCandidate{
  public:
    LepJPsiCandidate(){}
    virtual ~LepJPsiCandidate(){}

    LepJPsiCandidate(const vallot::Lepton& leg1, const vallot::Lepton& leg2, const vallot::Lepton& leg3) {
      leg1_ = leg1;
      leg2_ = leg2;
      leg3_ = leg3;
      mass_ = (leg1_+leg2_+leg3_).M(); 
      sign_ = leg1.charge()*leg2.charge()*leg3.charge();
      dtheta_ = fabs(leg1.theta()-(leg2+leg3).theta());
    }

    LepJPsiCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, reco::Candidate::LorentzVector& leg3, const float& sign) {
      lv1_= leg1 ;
      lv2_= leg2 ;
      lv3_= leg3 ;
      mass_ = (leg1_+leg2_+leg3_).M();
      sign_ = sign;
      dtheta_ = fabs(leg1.theta()-(leg2+leg3).theta());
    }

    const vallot::Lepton& leg1() const { return leg1_; }
    const vallot::Lepton& leg2() const { return leg2_; }
    const vallot::Lepton& leg3() const { return leg3_; }
    const reco::Candidate::LorentzVector& lv1() const { return lv1_;}
    const reco::Candidate::LorentzVector& lv2() const { return lv2_;}
    const reco::Candidate::LorentzVector& lv3() const { return lv3_;}

    float mass() const { return mass_; }
    float sign() const { return sign_; }
    float dtheta() const { return dtheta_; }
    float deltaR() const; 
    float deltaPhi() const;
  private:

    vallot::Lepton leg1_;
    vallot::Lepton leg2_;
    vallot::Lepton leg3_;
    reco::Candidate::LorentzVector lv1_;
    reco::Candidate::LorentzVector lv2_;
    reco::Candidate::LorentzVector lv3_;

    float mass_;
    float sign_;
    float dtheta_;
  };



}
#endif
