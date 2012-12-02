#ifndef KoPFA_TOPAnalyzer_Maos_h
#define KoPFA_TOPAnalyzer_Maos_h

#include "TLorentzVector.h"
#include "Math/Functor.h"
#include "TMinuit.h"
#include "Minuit2/Minuit2Minimizer.h"

namespace Ko
{
  class MaxMtsq : public ROOT::Math::Functor
  {
  public:
    void set(const TVector2& met, const TLorentzVector& p1, const TLorentzVector& p2);
    double operator()(const double* x);
    
  private:
    double metX_, metY_;
    double msq1_, msq2_, et1_, et2_;
    TVector3 pv1_, pv2_;
  };

  class TTbarMt2
  {
  public:
    TTbarMt2();
    void set(const TVector2& met, 
             const TLorentzVector& p1, const TLorentzVector& p2); 

    double getMt2() { return mt2_; };
    TLorentzVector getTop1() { return p1_+nu1_; };
    TLorentzVector getTop2() { return p2_+nu2_; };
    TLorentzVector getNu1() { return nu1_; };
    TLorentzVector getNu2() { return nu2_; };

  private:
    TVector2 met_;
    TLorentzVector p1_, p2_;

    // Caching results
    double mt2_;
    TLorentzVector nu1_, nu2_;

    // Minimizer stuffs
    MaxMtsq maxMtsq_;
    ROOT::Math::Functor minFn_;
    ROOT::Minuit2::Minuit2Minimizer min_;

  };

  //used for function fo minuit  
  extern TLorentzVector tmpl1_;
  extern TLorentzVector tmpl2_;
  extern TLorentzVector tmpmet_;

  double mtsq(const TLorentzVector &ptl, const TLorentzVector &qt, double ml, double mchi);
  double mtsq(const TVector3 &ptl, const TVector3 &qt, double ml, double mchi);

  class Maos{
   public:
    Maos(){}

    double MT2(const TLorentzVector& metvec, const TLorentzVector &lep1,const TLorentzVector &lep2, double mchi);

    // use Minuit minimizer, this returns MT2 value, must be called first.
    double MAOS(const TLorentzVector& metvec, const TLorentzVector &lep1,const TLorentzVector &lep2, double mchi, double mY, bool orig);

    double M(){
      return (tmpl1_+tmpl2_+tmpnu1_ + tmpnu2_).M(); 
    }

    TLorentzVector leg1(){
      return tmpl1_ + tmpnu1_;
    } 

    TLorentzVector leg2(){
      return tmpl2_ + tmpnu2_;
    } 

    TLorentzVector nu1(){return tmpnu1_; }
    TLorentzVector nu2(){return tmpnu2_; }

   private:

    double arglist[10];

    TLorentzVector tmpnu1_;
    TLorentzVector tmpnu2_;
  };
 
}

#endif
