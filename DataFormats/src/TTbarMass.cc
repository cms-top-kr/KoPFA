#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/Maos.h"

using namespace Ko;

TTbarMass::TTbarMass(const reco::Candidate::LorentzVector& lep1, const reco::Candidate::LorentzVector& lep2, const reco::Candidate::LorentzVector& 
jet1, const reco::Candidate::LorentzVector& jet2, const reco::Candidate::LorentzVector& met) {

  jet1_ = jet1;
  jet2_ = jet2;    
  lep1_ = lep1;    
  lep2_ = lep2;    
  met_ = met;    

  SetM();
  SetMaosM();
  SetUser1M(jet1_, jet2_, lep1_, lep2_, met_);
  SetUser2M(jet1_, jet2_, lep1_, lep2_, met_);

}

void TTbarMass::SetM(){
  M_ = (lep1_ + lep2_ + jet1_ + jet2_ + met_).M();
}


void TTbarMass::SetMaosM() {

  //maos mass 

  //case 1
  const reco::Candidate::LorentzVector vis1op1 = lep1_ + jet1_;
  const reco::Candidate::LorentzVector vis2op1 = lep2_ + jet2_;
  const TLorentzVector lep1op1(vis1op1.Px(), vis1op1.Py(), vis1op1.Pz(), vis1op1.E());
  const TLorentzVector lep2op1(vis2op1.Px(), vis2op1.Py(), vis2op1.Pz(), vis2op1.E());

  //case 2
  const reco::Candidate::LorentzVector vis1op2 = lep2_ + jet1_;
  const reco::Candidate::LorentzVector vis2op2 = lep1_ + jet2_;
  const TLorentzVector lep1op2(vis1op2.Px(), vis1op2.Py(), vis1op2.Pz(), vis1op2.E());
  const TLorentzVector lep2op2(vis2op2.Px(), vis2op2.Py(), vis2op2.Pz(), vis2op2.E());

  //missing et
  const reco::Candidate::LorentzVector invis = met_;
  const TLorentzVector metvec(invis.Px(), invis.Py(), 0, invis.Pt());

  //Fill tree for ttbar invariant mass and top mass for two different cases
  Ko::Maos ttbar1;
  double ttbar1Mt2 = sqrt( ttbar1.MAOS(metvec, lep1op1, lep2op1, 0.0, 0.0, false) );
  Ko::Maos ttbar2;
  double ttbar2Mt2 = sqrt( ttbar2.MAOS(metvec, lep1op2, lep2op2, 0.0, 0.0, false) );

  if( ttbar1Mt2 < ttbar2Mt2 ){
    Mt2_ = ttbar1Mt2;
    maosM_ = ttbar1.M();
    leg1_ = ttbar1.leg1();
    leg2_ = ttbar1.leg2();
  }else{
    Mt2_ = ttbar2Mt2;
    maosM_ = ttbar2.M();
    leg1_ = ttbar2.leg1();
    leg2_ = ttbar2.leg2();
  }

}

void TTbarMass::SetUser1M( const reco::Candidate::LorentzVector& bq1, const reco::Candidate::LorentzVector& bq2, const reco::Candidate::LorentzVector& le1, const reco::Candidate::LorentzVector& le2, const reco::Candidate::LorentzVector& met){

    double b1 = bq1.E();
    double bt1 = bq1.Et();
    double bx1 = bq1.Px();
    double by1 = bq1.Py();
    double bz1 = bq1.Pz();

    double b2 = bq2.E();
    double bt2 = bq2.Et();
    double bx2 = bq2.Px();
    double by2 = bq2.Py();
    double bz2 = bq2.Pz();


    double e1 = le1.E();
    double pt1 = le1.Et();
    double px1 = le1.Px();
    double py1 = le1.Py();
    double pz1 = le1.Pz();

    double e2 = le2.E();
    //double pt2 = le2.Et();
    double px2 = le2.Px();
    double py2 = le2.Py();
    double pz2 = le2.Pz();

    double Met = met.Et();
    double Mex = met.Px();
    double Mey = met.Py();

    double invmass2 = 3*b1*b2 + b2*bt2 - bt2*bz2 - bz1*bz2 + 2*b2*e1 + 4*b1*e2 + 5*e1*e2 + 4*bt2*Met + 4*e1*Met + e2*Met - (bx1 + bx2)*Mex - 2*by2*Mey + bt2*pt1 + by1*px1 - 2*Mex*px1 - (bx1 + bx2)*px2 - 2*Mex*px2 - 3*Mey*py1 - 2*Mey*py2 - 3*((bx1 + bx2)*Mex + by1*py2) + 4*Met*(bt1 - pz1) - bz2*(bz1 + pz1) + (-bz2 - py2)*(bz1 + pz1) + (bz1 + pz1)*(py2 - pz2) - 2*(bz1 + pz1)*pz2 - (bt1 + bz1 + 2*pz1)*pz2;

    double invmass = sqrt(invmass2);

    user1M_ = invmass;

}

void TTbarMass::SetUser2M( const reco::Candidate::LorentzVector& bq1, const reco::Candidate::LorentzVector& bq2, const reco::Candidate::LorentzVector& le1, const reco::Candidate::LorentzVector& le2, const reco::Candidate::LorentzVector& met){
    double b1 = bq1.E();
    //double bt1 = bq1.Et();
    double bx1 = bq1.Px();
    double by1 = bq1.Py();
    double bz1 = bq1.Pz();

    double b2 = bq2.E();
    //double bt2 = bq2.Et();
    double bx2 = bq2.Px();
    double by2 = bq2.Py();
    double bz2 = bq2.Pz();


    double e1 = le1.E();
    //double pt1 = le1.Et();
    double px1 = le1.Px();
    double py1 = le1.Py();
    double pz1 = le1.Pz();

    double e2 = le2.E();
    //double pt2 = le2.Et();
    double px2 = le2.Px();    double py2 = le2.Py();    double pz2 = le2.Pz();

    double Met = met.Et();
    double Mex = met.Px();
    double Mey = met.Py();

    double invmass2 = 1.262208073067337*TMath::Power(b1,2) + 1.262208073067337*TMath::Power(b2,2) - 0.11690974715234576*TMath::Power(bx1,2) - 2.325269993670129*bx1*bx2 - 0.11690974715234576*TMath::Power(bx2,2) - 0.11690974715234576*TMath::Power(by1,2) + (-2.325269993670129*by1 - 0.11690974715234576*by2)*by2 - 1.262208073067337*TMath::Power(bz1,2) - 2.524416146134674*bz1*bz2 - 1.262208073067337*TMath::Power(bz2,2) + 0.36094746796490595*bz2*e1 + 1.262208073067337*TMath::Power(e1,2) + 2.4333915254807796*e1*e2 + 1.262208073067337*TMath::Power(e2,2) - 1.262208073067337*bz2*Met + 2.1819625834627003*e1*Met + 2.1819625834627003*e2*Met + TMath::Power(Met,2) + b1*(2.524416146134674*b2 - 0.05845487357617288*bx1 - 0.05845487357617288*by1 + 2.524416146134674*e1 + 2.524416146134674*e2 + 1.9461541091171606*Met) + b2*(-0.05845487357617288*bx2 - 0.05845487357617288*by2 + 2.524416146134674*e1 + 2.524416146134674*e2 + 1.9461541091171606*Met) - 2.642748152984737*bx1*Mex - 2.642748152984737*bx2*Mex - 0.05845487357617288*by1*Mex - 0.05845487357617288*by2*Mex - 0.07888800456670857*TMath::Power(Mex,2) - 0.05845487357617288*bx1*Mey - 0.05845487357617288*bx2*Mey - 2.642748152984737*by1*Mey - 2.642748152984737*by2*Mey - 0.07888800456670857*TMath::Power(Mey,2) - 4.445035641931849*bx1*px1 - 2.4669701406160556*bx2*px1 - 2.6821921552680914*Mex*px1 - 0.7099920411003772*TMath::Power(px1,2) - 2.4669701406160556*bx1*px2 - 4.445035641931849*bx2*px2 - 2.6821921552680914*Mex*px2 - 1.10443206393392*px1*px2 - 0.7099920411003772*TMath::Power(px2,2) - 4.445035641931849*by1*py1 - 2.4669701406160556*by2*py1 - 2.6821921552680914*Mey*py1 - 0.7099920411003772*TMath::Power(py1,2) - 2.4669701406160556*by1*py2 - 4.445035641931849*by2*py2 - 2.6821921552680914*Mey*py2 - 1.10443206393392*py1*py2 - 0.7099920411003772*TMath::Power(py2,2) - 3.0098807896221116*bz2*pz1 - 1.262208073067337*Met*pz1 - 1.262208073067337*TMath::Power(pz1,2) + bz1*(0.36094746796490595*e2 - 1.262208073067337*Met - 2.524416146134674*pz1 - 3.0098807896221116*pz2) - 2.524416146134674*bz2*pz2 - 1.262208073067337*Met*pz2 - 2.524416146134674*pz1*pz2 - 1.262208073067337*TMath::Power(pz2,2);

    double invmass = sqrt(invmass2);

    user2M_ = invmass;
}

