#ifndef Lepton_H
#define Lepton_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "TLorentzVector.h"
#include "TMath.h"

namespace vallot{

  typedef reco::Candidate::LorentzVector LorentzVector;

  class Lepton : public LorentzVector{
  public:
    Lepton(){}
    virtual ~Lepton(){}
    Lepton(const reco::Candidate::LorentzVector& p4, const int& charge);

    float charge() const { return charge_; }

    double chIso03() const { return chIso03_; }
    double puChIso03() const { return puChIso03_; }
    double nhIso03() const { return nhIso03_; }
    double phIso03() const { return phIso03_; }
  
    double chIso04() const { return chIso04_; }
    double puChIso04() const { return puChIso04_; }
    double nhIso04() const { return nhIso04_; }
    double phIso04() const { return phIso04_; }

    double trackIso() const { return trackIso_; }
    double ecalIso() const { return ecalIso_; }
    double hcalIso() const { return hcalIso_; }

    double relpfIso03(int type = 0) const { 
      if( type == 0 ) return (chIso03_ + nhIso03_ + phIso03_) / pt_; 
      else if( type == 1) return (chIso03_ + TMath::Max( 0.0, nhIso03_ + phIso03_ - puChIso03_) ) / pt_; 
      else if( type == 2) return (chIso03_ + TMath::Max( 0.0, nhIso03_ + phIso03_ - puChIso03_) ) / pt_;
      else return -1.0;
    }

    double relpfIso04(int type = 0) const { 
      if( type == 0 ) return (chIso04_ + nhIso04_ + phIso04_) / pt_; 
      else if( type == 1) return (chIso04_ + TMath::Max( 0.0, nhIso04_ + phIso04_ - puChIso04_) ) / pt_;
      else if( type == 2) return (chIso04_ + TMath::Max( 0.0, nhIso04_ + phIso04_ - puChIso04_) ) / pt_;
      else return -1.0;
    }

    double reldetIso() const { return (trackIso_ + ecalIso_ + hcalIso_) / pt_; }

    void setIsoDeposit( pat::IsolationKeys key, const pat::IsoDeposit *dep, reco::isodeposit::AbsVetos);
    void setIsoDeposit( double trkiso, double ecaliso, double hcaliso ){ 
      trackIso_ = trkiso; 
      ecalIso_ = ecaliso;
      hcalIso_ = hcaliso;
    }

    void setPFIsoValues03( double chIso03, double puChIso03, double nhIso03, double phIso03 ){
      chIso03_ = chIso03;
      puChIso03_ = puChIso03;
      nhIso03_ = nhIso03;
      phIso03_ = phIso03;
    }

    void setPFIsoValues04( double chIso04, double puChIso04, double nhIso04, double phIso04 ){
      chIso04_ = chIso04;
      puChIso04_ = puChIso04;
      nhIso04_ = nhIso04;
      phIso04_ = phIso04;
    }

  private:

    int charge_;
    double pt_;

    double chIso03_;
    double puChIso03_;
    double nhIso03_;
    double phIso03_;

    double chIso04_;
    double puChIso04_;
    double nhIso04_;
    double phIso04_;

    double trackIso_;
    double ecalIso_;
    double hcalIso_;

  };

}
#endif
