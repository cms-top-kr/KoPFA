#include "KoPFA/DataFormats/interface/ZCandidate.h"

using namespace Ko;

float ZCandidate::deltaR() const{
 
  TLorentzVector lep1_;
  TLorentzVector lep2_;
 
  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M()); 
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M()); 

  return lep1_.DeltaR(lep2_);

}

float ZCandidate::deltaPhi() const{

  TLorentzVector lep1_;
  TLorentzVector lep2_;

  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M());  
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M());  

  return lep1_.DeltaPhi(lep2_);

}

