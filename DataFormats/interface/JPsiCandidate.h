#ifndef JPsiCandidate_H
#define JPsiCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

namespace vallot{

  class JPsiCandidate{
  public:
    JPsiCandidate(){}
    virtual ~JPsiCandidate(){}

    JPsiCandidate(const vallot::Lepton& leg1, const vallot::Lepton& leg2, const double& vProb, const double& dlPV, const double& ppdlPV, const double& ppdlErrPV, const int& genRefJpmomId, const double& DlTrue, const double& ppdlTrue) {
      leg1_ = leg1;
      leg2_ = leg2;
      mass_ = (leg1_+leg2_).M();
      sign_ = leg1.charge()*leg2.charge();
      eta_  = (leg1_+leg2_).eta();
      pt_   = (leg1_+leg2_).pt();
      phi_  = (leg1_+leg2_).phi();
      theta_ = (leg1_+leg2_).theta();
      vProb_ = vProb;
      dlPV_ = dlPV;
      //dlErrPV_ = dlErrPV;
      ppdlPV_ = ppdlPV;
      ppdlErrPV_ = ppdlErrPV;
      //ppdlBS_ = ppdlBS;
      //ppdlErrBS_ = ppdlErrBS;
      genRefJpmomId_ = genRefJpmomId;
      DlTrue_ = DlTrue;
      ppdlTrue_ = ppdlTrue;
    }

    JPsiCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, const double& sign,const double& dlPV, const double& vProb, const double& ppdlPV, const double& ppdlErrPV, const int& genRefJpmomId, const double& DlTrue, const double& ppdlTrue) {
      lv1_= leg1 ;
      lv2_= leg2 ;
      mass_ = (leg1_+leg2_).M();
      sign_ = sign;
      eta_  = (leg1_+leg2_).eta();
      pt_   = (leg1_+leg2_).pt();
      phi_  = (leg1_+leg2_).phi();
      theta_ = (leg1_+leg2_).theta();
      vProb_ = vProb;
      dlPV_ = dlPV;
      //dlErrPV_ = dlErrPV;
      ppdlPV_ = ppdlPV;
      ppdlErrPV_ = ppdlErrPV;
      //ppdlBS_ = ppdlBS;
      //ppdlErrBS_ = ppdlErrBS;
      genRefJpmomId_ = genRefJpmomId;
      DlTrue_ = DlTrue;
      ppdlTrue_ = ppdlTrue;
    }

    const vallot::Lepton& leg1() const { return leg1_; }
    const vallot::Lepton& leg2() const { return leg2_; }
    const reco::Candidate::LorentzVector& lv1() const { return lv1_;}
    const reco::Candidate::LorentzVector& lv2() const { return lv2_;}

    double mass() const { return mass_; }
    double sign() const { return sign_; }
    double eta() const { return eta_; }
    double pt() const { return pt_; }
    double phi() const { return phi_; }
    double theta() const { return theta_; }
    double vProb() const { return vProb_; }
    double dlPV() const { return dlPV_; }
    //double dlErrPV() const { return dlErrPV_; }
    double ppdlPV() const { return ppdlPV_; }
    double ppdlErrPV() const { return ppdlErrPV_; }
    //double ppdlBS() const { return ppdlBS_; }
    //double ppdlErrBS() const { return ppdlErrBS_; }
    int    genRefJpmomId() const { return genRefJpmomId_; }
    double DlTrue() const { return DlTrue_; }
    double ppdlTrue() const { return ppdlTrue_; }
    double deltaR() const; 
    double deltaPhi() const;
  private:

    vallot::Lepton leg1_;
    vallot::Lepton leg2_;
    reco::Candidate::LorentzVector lv1_;
    reco::Candidate::LorentzVector lv2_;

    double mass_;
    double sign_;
    double eta_;
    double pt_;
    double phi_;
    double theta_;
    double vProb_;
    double dlPV_;
    //double dlErrPV_;
    double ppdlPV_;
    double ppdlErrPV_;
    //double ppdlBS_;
    //double ppdlErrBS_;
    int    genRefJpmomId_;
    double DlTrue_;
    double ppdlTrue_;

  };

}
#endif
