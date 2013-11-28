#include "KoPFA/DataFormats/interface/JPsiCandidate.h"

using namespace vallot;

double JPsiCandidate::deltaR() const{
 
  TLorentzVector lep1_;
  TLorentzVector lep2_;
 
  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M()); 
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M()); 

  return lep1_.DeltaR(lep2_);

}

double JPsiCandidate::deltaPhi() const{

  TLorentzVector lep1_;
  TLorentzVector lep2_;

  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M());  
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M());  

  return lep1_.DeltaPhi(lep2_);

}


