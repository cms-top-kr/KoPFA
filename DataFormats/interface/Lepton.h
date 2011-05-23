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

namespace Ko{

  typedef reco::Candidate::LorentzVector LorentzVector;

  class Lepton : public LorentzVector{
  public:
    Lepton(){}
    virtual ~Lepton(){}
    Lepton(const reco::Candidate::LorentzVector& p4, const int& charge);

    float charge() const { return charge_; }

    double chIso03() const { return chIso03_; }
    double nhIso03() const { return nhIso03_; }
    double phIso03() const { return phIso03_; }
  
    double chIso04() const { return chIso04_; }
    double nhIso04() const { return nhIso04_; }
    double phIso04() const { return phIso04_; }

    double trackIso() const { return trackIso_; }
    double ecalIso() const { return ecalIso_; }
    double hcalIso() const { return hcalIso_; }

    double relpfIso03() const { return (chIso03_ + nhIso03_ + phIso03_) / pt_; }
    double relpfIso04() const { return (chIso04_ + nhIso04_ + phIso04_) / pt_; }
    double reldetIso() const { return (trackIso_ + ecalIso_ + hcalIso_) / pt_; }

    void setIsoDeposit( pat::IsolationKeys key, const pat::IsoDeposit *dep, reco::isodeposit::AbsVetos);
    void setIsoDeposit( double trkiso, double ecaliso, double hcaliso ){ 
      trackIso_ = trkiso; 
      ecalIso_ = ecaliso;
      hcalIso_ = hcaliso;
    }

  private:

    int charge_;
    double pt_;

    double chIso03_;
    double nhIso03_;
    double phIso03_;

    double chIso04_;
    double nhIso04_;
    double phIso04_;

    double trackIso_;
    double ecalIso_;
    double hcalIso_;

  };

}
#endif
