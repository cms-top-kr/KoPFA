#ifndef WCandidate_H
#define WCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "TLorentzVector.h"

namespace Ko{

  class WCandidate{
  public:
    WCandidate(){}
    virtual ~WCandidate(){}

    WCandidate(const Ko::Lepton& leg1, const Ko::METCandidate& leg2) {
      leg1_ = leg1;
      leg2_ = leg2;
      transversemass_ = leg1_.pt()+leg2_.pt(); 
      sign_ = leg1.charge();
    }

    WCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, const float& sign) {
      lv_= leg1 ;
      mv_= leg2 ;
      transversemass_ = leg1_.pt()+leg2_.pt();
      sign_ = sign;
    }

    const Ko::Lepton& leg1() const { return leg1_; }
    const Ko::METCandidate& leg2() const { return leg2_; }
    const reco::Candidate::LorentzVector& lv() const { return lv_;}
    const reco::Candidate::LorentzVector& mv() const { return mv_;}

    float transversemass() const { return transversemass_; }
    float sign() const { return sign_; }
    //float deltaR() const; 
    //float deltaPhi() const; 
  private:

    Ko::Lepton leg1_;
    Ko::METCandidate leg2_;
    reco::Candidate::LorentzVector lv_;
    reco::Candidate::LorentzVector mv_;

    float transversemass_;
    float sign_;
  };



}
#endif
