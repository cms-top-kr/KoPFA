#ifndef TTbarMass_H
#define TTbarMass_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "TLorentzVector.h"

namespace Ko{

  class TTbarMass{
  public:
    TTbarMass(){}
    virtual ~TTbarMass(){}

    TTbarMass(const reco::Candidate::LorentzVector& lep1, const reco::Candidate::LorentzVector& lep2, const reco::Candidate::LorentzVector& jet1, const reco::Candidate::LorentzVector& jet2, const reco::Candidate::LorentzVector& met);

    const TLorentzVector& leg1() const { return leg1_; }
    const TLorentzVector& leg2() const { return leg2_; }

    float M() const { return M_; }
    float Mt2() const { return Mt2_; }
    float maosM() const { return maosM_; }
    float user1M() const { return user1M_; } 
    float user2M() const { return user2M_; }
  private:

    void SetM();
    void SetMaosM();
    void SetUser1M( const reco::Candidate::LorentzVector& bq1, const reco::Candidate::LorentzVector& bq2, const reco::Candidate::LorentzVector& le1, const reco::Candidate::LorentzVector& le2, const reco::Candidate::LorentzVector& met);
    void SetUser2M( const reco::Candidate::LorentzVector& bq1, const reco::Candidate::LorentzVector& bq2, const reco::Candidate::LorentzVector& le1, const reco::Candidate::LorentzVector& le2, const reco::Candidate::LorentzVector& met);

    reco::Candidate::LorentzVector lep1_;
    reco::Candidate::LorentzVector lep2_;
    reco::Candidate::LorentzVector jet1_;
    reco::Candidate::LorentzVector jet2_;
    reco::Candidate::LorentzVector met_;

    TLorentzVector leg1_;
    TLorentzVector leg2_;
    float M_;
    float Mt2_;    
    float maosM_;
    float user1M_;
    float user2M_;
  };

}
#endif
