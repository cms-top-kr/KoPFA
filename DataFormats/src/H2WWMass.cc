#include "KoPFA/DataFormats/interface/H2WWMass.h"
#include "KoPFA/DataFormats/interface/Maos.h"

using namespace Ko;

H2WWMass::H2WWMass(const reco::Candidate::LorentzVector& lep1, const reco::Candidate::LorentzVector& lep2, const reco::Candidate::LorentzVector& met, const float& charge1, const float& charge2 ) {

  lep1_ = lep1;    
  lep2_ = lep2;    
  met_ = met;
  charge1_ = charge1;    
  charge2_ = charge2;

  const TLorentzVector lep1op1(lep1_.Px(), lep1_.Py(), lep1_.Pz(), lep1_.E());
  const TLorentzVector lep2op1(lep2_.Px(), lep2_.Py(), lep2_.Pz(), lep2_.E());
  const TLorentzVector metvec(met_.Px(), met_.Py(), 0, met_.Pt());

  leg1_ = lep1op1;
  leg2_ = lep2op1;
  met__ = metvec;

  SetM();
  SetMaosM();
  SetSM();

}

void H2WWMass::SetM(){
  M_ = (lep1_ + lep2_ + met_).M();
}


void H2WWMass::SetMaosM() {

  //maos mass 
  //Fill tree for h2ww 
  Ko::Maos h2ww;
  double h2wwMt2 = sqrt( h2ww.MAOS(met__, leg1_, leg2_, 0.0, 0.0, false) );

    Mt2_ = h2wwMt2;
    nu1_ = h2ww.nu1();
    nu2_ = h2ww.nu2();
    maosM_ = (leg1_+leg2_+nu1_+nu2_).M();

}

void H2WWMass::SetSM() {

    //mass using simbolic regrassion
    //http://arxiv.org/PS_cache/arxiv/pdf/1006/1006.4998v1.pdf

    TVector2 mu1, mu2, met2d;
    mu1.SetMagPhi(leg1_.Pt(), leg1_.Phi());
    mu2.SetMagPhi(leg2_.Pt(), leg2_.Phi());
    met2d.SetMagPhi(met__.Et(),met__.Phi());

    float sm1 = 2*leg1_.Pt()*leg1_.Pt()+2*leg2_.Pt()*leg2_.Pt();
    float sm2 = leg1_.Pt()*leg2_.Pt()+met__.Et()*(leg1_.Pt()+leg2_.Pt());
    float sm3 = met2d*(mu1+mu2)+2*mu1*mu2;

      SM_=sqrt(sm1+3*(sm2-sm3));

}

