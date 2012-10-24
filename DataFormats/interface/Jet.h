#ifndef Jet_H
#define Jet_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include <iostream>
#include <map>

namespace vallot{

  typedef reco::Candidate::LorentzVector LorentzVector;

  class Jet : public LorentzVector{
  public:
    Jet(){}
    virtual ~Jet(){}
    Jet(const reco::Candidate::LorentzVector& p4);

    int flavor() const { return flavor_; }
    void setFlavor( int flavor ) { flavor_ = flavor; }

    int topdecay() const { return topdecay_; }
    void setTopdecay( int topdecay ) { topdecay_ = topdecay; }

    bool recoTopdecay(const std::string &algo ) const { 
      bool found = false;
      if( find( recoTopdecay_.begin(), recoTopdecay_.end(), algo ) != recoTopdecay_.end() ) found = true;
      return found; 
    }
    void setRecoTopdecay( const std::string & algo) { recoTopdecay_.push_back(algo); }

    double bDiscriminator() const { return bDiscriminator_ ; }
    void setbDiscriminator( double bDiscriminator ) { bDiscriminator_ = bDiscriminator; } 
  
    float secvtxMass() const { return secVtxMass_;}
    void setSecVtxMass( float secVtxMass ){ secVtxMass_ = secVtxMass; }

  private:

    int flavor_;
    int topdecay_;
    double bDiscriminator_; 
    float secVtxMass_;

    std::vector<std::string> recoTopdecay_; 

  };

}
#endif
