#include "KoPFA/TopAnalyzer/interface/MaosTTbar.h"
#include<iostream>
using namespace std;

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
      mt12 = Ko::mtsq(Ko::tmpl1_, p1, 0.0, 0.0);
      mt22 = Ko::mtsq(Ko::tmpl2_, p2, 0.0, 0.0);
      // should try swapping
      retval = fmax(mt12, mt22);
}

double Ko::MaosTTbar::MT2(const TLorentzVector& metvec, const TLorentzVector &lep1, const TLorentzVector &lep2, double mchi){

     TMinuit *gMinuit = new TMinuit(2);
     static bool init=false;

     int ierflg=0;
     if (!init)
     {
       cout << "init..." << endl;
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
     }

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
double Ko::MaosTTbar::MAOS(const TLorentzVector& metvec, const TLorentzVector &lep1,const TLorentzVector &lep2, 
               double mchi, double mY, bool orig){
      double mt22 = MT2(metvec, lep1, lep2, mchi);

      // add Z componet 
      tmpnu1_.SetPz(tmpnu1_.Pt()/lep1.Pt()*lep1.Pz());
      tmpnu1_.SetE(tmpnu1_.P());
      tmpnu2_.SetPz(tmpnu2_.Pt()/lep2.Pt()*lep2.Pz());
      tmpnu2_.SetE(tmpnu2_.P());
 
      return mt22;
}

