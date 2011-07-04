#ifndef __KoPFA_CommonTools_interface_KoCombinedIsolation__
#define __KoPFA_CommonTools_interface_KoCombinedIsolation__


#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include <string>
#include <iostream>



/**
   \class KoCombinedIsolation
   \brief Holds combined isolation parameters, and combined isolation values. 

   this class is used to define a combined or independant isolation 
   and the associated cut, and to hold the corresonding value of 
   the isolation (both absolute and relative). It is used in PatLeptonSelector
*/

class KoCombinedIsolation {
  
 public:
  
  // default construcor
  KoCombinedIsolation() {}
  
  // init from a pset
  void initialize( const edm::ParameterSet& ps )
  {
    name_ = ps.getParameter<std::string>("name");
    absoluteCut_ = ps.getParameter<double>("absoluteCut");
    relativeCut_ = ps.getParameter<double>("relativeCut");

    // the weights can be set to 0 to get a specific isolation
    chargedWeight_ = ps.getParameter<double>("chargedWeight");
    neutralWeight_ = ps.getParameter<double>("neutralWeight");
    photonWeight_ = ps.getParameter<double>("photonWeight");
  }

  const char* name() const { return name_.c_str(); }
  const double absoluteCut() const{ return absoluteCut_; }
  const double relativeCut() const{ return relativeCut_;}
  const double chargedWeight() const { return chargedWeight_;}
  const double neutralWeight() const { return neutralWeight_;}
  const double photonWeight() const{ return photonWeight_;}
  const double isolation() const{ return isolation_;}
  const double isolationRel() const{ return isolationRel_;}

  bool testIsoCut( double chIso, double nhIso, double phIso, double norm, bool rel);


  friend std::ostream& operator<<(std::ostream& out, const KoCombinedIsolation& cutp );

  
 private:

  /// name, e.g. combinedFlorent, or charged
  std::string name_;

  /// cut on the absolute value of the isolation
  double absoluteCut_;

  /// cut on the relative value of the isolation
  double relativeCut_;

  /// weight for the charged hadron component
  double chargedWeight_;

  /// weight for the neutral hadron component
  double neutralWeight_;

  /// weight for the photon component
  double photonWeight_;

  /// computed isolation value, available after calling testIsoCut
  double isolation_;

  /// computed relative isolation value, available after calling testIsoCut
  double isolationRel_;
};

#endif
