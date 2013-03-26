#ifndef TTbarDILEvent_H
#define TTbarDILEvent_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "TLorentzVector.h"

namespace vallot{

  class TTbarDILEvent{
  public:
    TTbarDILEvent(){}
    virtual ~TTbarDILEvent(){}

    const TLorentzVector& leg1() const { return leg1_; }
    void SetLeg1( const TLorentzVector & leg1 ) { leg1_ = leg1; }
    const TLorentzVector& leg2() const { return leg2_; }
    void SetLeg2( const TLorentzVector & leg2 ) { leg2_ = leg2; }

    const TLorentzVector& nu1() const { return nu1_; }
    void SetNu1( const TLorentzVector & nu1 ) { nu1_ = nu1; }
    const TLorentzVector& nu2() const { return nu2_; }
    void SetNu2( const TLorentzVector & nu2 ) { nu2_ = nu2; }

    float M() const { return M_; }
    void SetM( float M ){ M_ = M; }

    float Mt2() const { return Mt2_; }
    void SetMt2( float Mt2 ){ Mt2_ = Mt2; }
    
    float Mbb() const { return Mbb_; }
    void SetMbb( float Mbb ){ Mbb_ = Mbb; }
 
    unsigned int bid(unsigned int i) const { return jets_[i]; }
    void SetBId( int b, int bbar ){ 
      jets_.push_back(b);
      jets_.push_back(bbar);
    }
 
    unsigned int jid(unsigned int i) const{ return jetsnotfromtop_[i] ; }
    void SetJId( int j1, int j2 ){ 
      jetsnotfromtop_.push_back(j1);
      jetsnotfromtop_.push_back(j2);
    }

  private:

    TLorentzVector leg1_;
    TLorentzVector leg2_;

    TLorentzVector nu1_;
    TLorentzVector nu2_;

    float M_;
    float Mbb_;
    std::vector<int> jets_;
    std::vector<int> jetsnotfromtop_;
    float Mt2_;

  };

}
#endif
