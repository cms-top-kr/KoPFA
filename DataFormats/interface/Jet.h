#ifndef Jet_H
#define Jet_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"

namespace vallot{

  typedef reco::Candidate::LorentzVector LorentzVector;

  class Jet : public LorentzVector{
  public:
    Jet(){}
    virtual ~Jet(){}
    Jet(const reco::Candidate::LorentzVector& p4);

    int flavor(){ return flavor_; }
    void setFlavor( int flavor ) { flavor_ = flavor; }

    bool topdecay(){ return topdecay_; }
    void setTopdecay( bool topdecay ){ topdecay_ = topdecay; }

    double bDiscriminator(){ return bDiscriminator_ ; }
    void setbDiscriminator( double bDiscriminator ){ bDiscriminator_ = bDiscriminator; } 
  
    float secVtxMass(){ return secVtxMass_;}
    void setSecVtxMass( float secVtxMass ){ secVtxMass_ = secVtxMass; }

  private:

    int flavor_;
    bool topdecay_;
    double bDiscriminator_; 
    float secVtxMass_;

  };

}
#endif
