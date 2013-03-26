#include "KoPFA/CommonTools/interface/KoCombinedIsolation.h"


bool KoCombinedIsolation::testIsoCut( double chIso, double nhIso, double phIso, double norm, bool rel) {
  
  double iso = chargedWeight_*chIso + neutralWeight_*nhIso + photonWeight_*phIso;
  isolation_ = iso; 
  
  double cut = absoluteCut_;
  if( rel ) {
    iso /= norm;
    isolationRel_ = iso; 
    cut = relativeCut_;
  }
  
  if(iso < cut) return true;
  else return false;
}


std::ostream& operator<<(std::ostream& out, const KoCombinedIsolation& cutp ) {

    if(!out) return out;
    out<<cutp.name_<<" c/n/p = "
       <<cutp.chargedWeight_<<","<<cutp.neutralWeight_<<","<<cutp.photonWeight_<<" "
       <<"rel<"<<cutp.relativeCut_<<", abs<"<<cutp.absoluteCut_;

    return out;
  }
