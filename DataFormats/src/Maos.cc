#include "KoPFA/DataFormats/interface/Maos.h"

using namespace std;
using namespace Ko;

double Ko::mtsq(const TLorentzVector &ptl, const TLorentzVector &qt, double ml, double mchi)
{
    TVector3 l1 = ptl.Vect();
    TVector3 l2 = qt.Vect();
    return mtsq(l1, l2, ml, mchi);
}

double Ko::mtsq(const TVector3 &ptl, const TVector3 &qt, double ml, double mchi)
{
    TVector3 l1 = ptl;
    TVector3 l2 = qt;
    l1.SetZ(0.0);
    l2.SetZ(0.0);

    double El = TMath::Hypot(ml, l1.Mag());
    double Echi = TMath::Hypot(mchi, l2.Mag());

    return  ml*ml + mchi*mchi + 2.0*(El*Echi - l1.Dot(l2));
}

TLorentzVector Ko::tmpl1_;
TLorentzVector Ko::tmpl2_;
TLorentzVector Ko::tmpmet_;

void minfn(Int_t &npar, Double_t *gin, Double_t &retval, Double_t *par, Int_t iflag){
    static TLorentzVector p1;
    static TLorentzVector p2;

    double mt12, mt22;

    p1.SetPxPyPzE(par[0], par[1], 0.0, TMath::Hypot(par[0], par[1]));
    p2 = Ko::tmpmet_ - p1;
    mt12 = Ko::mtsq(Ko::tmpl1_, p1, Ko::tmpl1_.M(), 0.0);
    mt22 = Ko::mtsq(Ko::tmpl2_, p2, Ko::tmpl2_.M(), 0.0);
    // should try swapping
    retval = fmax(mt12, mt22);
}

double Ko::Maos::MT2(const TLorentzVector& metvec, const TLorentzVector &lep1, const TLorentzVector &lep2, double mchi){

    TMinuit *gMinuit = new TMinuit(2);
    gMinuit->SetPrintLevel(-1);
    static bool init=false;

    int ierflg=0;
    gMinuit->SetFCN(minfn);
    arglist[0] = 1.0;
    gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
    gMinuit->mnparm(0, "nu1px", 0.001, 0.0001, 0, 0, ierflg);
    gMinuit->mnparm(1, "nu1py", 0.001, 0.0001, 0, 0, ierflg);
    arglist[0] = -1;
    gMinuit->mnexcm("SET PRI", arglist, 1, ierflg);
    arglist[0] = 1000;
    arglist[1] = 0.1;
    init=true;

    // copy
    tmpl1_ = lep1;
    tmpl2_ = lep2;
    tmpmet_ = metvec;

    double l1 = metvec.Vect().Dot(lep1.Vect())/metvec.P()/lep1.P();

    arglist[0] = 1;
    arglist[1] = l1*lep1.Px();
    gMinuit->mnexcm("SET PAR", arglist, 2, ierflg);
    arglist[0] = 2;
    arglist[1] = l1*lep1.Py();
    gMinuit->mnexcm("SET PAR", arglist, 2, ierflg);

    arglist[0] = 1000;
    arglist[1] = 1e-3;
    gMinuit->mnexcm("SIM", arglist, 2, ierflg);
    arglist[0] = 1000;
    arglist[1] = 1e-3;
    gMinuit->mnexcm("MINI", arglist, 2, ierflg);
    //tm.mnexcm("MINI", arglist, 1, ierflg);

    //double nu1px, nu2px;
    //double nu1pxe, nu2pxe;
    //double nu1py, nu2py;
    //double nu1pye, nu2pye;

    double nu1px;
    double nu1pxe;
    double nu1py;
    double nu1pye;

    gMinuit->GetParameter(0, nu1px, nu1pxe);
    gMinuit->GetParameter(1, nu1py, nu1pye);

    Double_t amin,edm,errdef;
    Int_t nvpar,nparx,icstat;
    gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

    tmpnu1_.SetPx(nu1px);
    tmpnu1_.SetPy(nu1py);
    tmpnu1_.SetPz(0.0);
    tmpnu1_.SetE(TMath::Hypot(nu1px, nu1py));
    tmpnu2_ = metvec-tmpnu1_;

    return amin;
}

// use Minuit minimizer
double Ko::Maos::MAOS(const TLorentzVector& metvec, const TLorentzVector &lep1,const TLorentzVector &lep2, 
                           double mchi, double mY, bool orig){
    double mt22 = MT2(metvec, lep1, lep2, mchi);

    // add Z componet 
    tmpnu1_.SetPz(tmpnu1_.Pt()/sqrt(lep1.M()*lep1.M() + lep1.Pt()*lep1.Pt())*lep1.Pz()); //considering the invariant mass of visible particles
    tmpnu1_.SetE(tmpnu1_.P());
    tmpnu2_.SetPz(tmpnu2_.Pt()/sqrt(lep2.M()*lep2.M() + lep2.Pt()*lep2.Pt())*lep2.Pz());
    tmpnu2_.SetE(tmpnu2_.P());

    return mt22;
}

void MaxMtsq::set(const TVector2& met, const TLorentzVector& p1, const TLorentzVector& p2)
{
  pv1_ = p1.Vect();
  pv2_ = p2.Vect();
  metX_ = met.X();
  metY_ = met.Y();

  msq1_ = p1.M2();
  msq2_ = p2.M2();
  et1_ = std::sqrt(msq1_+pv1_.Perp2());
  et2_ = std::sqrt(msq2_+pv2_.Perp2());
}

double MaxMtsq::operator()(const double* x)
{
  TVector3 q1(x[0], x[1], 0);
  TVector3 q2(metX_-x[0], metY_-x[1], 0);
  const double mtsq1 = msq1_ + 2*(et1_*q1.Mag()-q1.Dot(pv1_));
  const double mtsq2 = msq2_ + 2*(et2_*q2.Mag()-q2.Dot(pv2_));

  return std::max(mtsq1, mtsq2);
}

TTbarMt2::TTbarMt2():
  maxMtsq_(), minFn_(maxMtsq_, 2), min_(ROOT::Minuit2::kMigrad)
{
  min_.SetMaxFunctionCalls(1000000);
  min_.SetMaxIterations(100000);
  min_.SetTolerance(0.001);

  min_.SetFunction(minFn_);
}

void TTbarMt2::set(const TVector2& met,
                   const TLorentzVector& p1, const TLorentzVector& p2)
{
  met_ = met;
  p1_ = p1;
  p2_ = p2;

  maxMtsq_.set(met_, p1_, p2_);
  min_.SetVariable(0, "nu1Px", 0.001, 0.0001);
  min_.SetVariable(1, "nu1Py", 0.001, 0.0001);

  min_.Minimize();

  // Update results
  const double* sol = min_.X();
  mt2_ = maxMtsq_(sol);

  nu1_.SetXYZT(sol[0], sol[1], 0, 0);
  nu2_.SetXYZT(met_.X()-sol[0], met_.Y()-sol[1], 0, 0);
  nu1_.SetPz(nu1_.Pt()*p1.Z()/std::sqrt(p1.M2()+p1.Perp2()));
  nu2_.SetPz(nu2_.Pt()*p2.Z()/std::sqrt(p2.M2()+p2.Perp2()));
  nu1_.SetE(nu1_.P());
  nu2_.SetE(nu2_.P());
}

