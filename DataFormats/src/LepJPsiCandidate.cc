#include "KoPFA/DataFormats/interface/LepJPsiCandidate.h"

using namespace vallot;

float LepJPsiCandidate::deltaR() const{
 
  TLorentzVector lep1_;
  TLorentzVector lep2_;
  TLorentzVector lep3_;
 
  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M()); 
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M()); 
  lep3_.SetPtEtaPhiM(leg3_.pt(), leg3_.eta(), leg3_.phi(), leg2_.M()); 

  return lep1_.DeltaR(lep2_+lep3_);

}

float LepJPsiCandidate::deltaPhi() const{

  TLorentzVector lep1_;
  TLorentzVector lep2_;
  TLorentzVector lep3_;

  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M());  
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M());  
  lep3_.SetPtEtaPhiM(leg3_.pt(), leg3_.eta(), leg3_.phi(), leg2_.M());

  return lep1_.DeltaPhi(lep2_+lep3_);

}

