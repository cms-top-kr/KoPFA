#include "KoPFA/DataFormats/interface/METCandidate.h"

using namespace Ko; 
using namespace std;

METCandidate::METCandidate( const reco::Candidate::LorentzVector& p4) : LorentzVector(p4){

  pt_ = p4.pt(); 
  eta_ = p4.eta(); 

}

