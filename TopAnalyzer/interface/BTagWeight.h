#ifndef BTAGWEIGHT_H
#define BTAGWEIGHT_H

#include <vector>
#include "TLorentzVector.h"
#include <iostream>

class BTagWeight
{

  public:
    BTagWeight(){};
    ~BTagWeight(){};

    enum AlgoType {
      CSVL,
      CSVM,
      CSVT
    };

    double reweight(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, AlgoType algo);

    double probmc(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);
    double probdata(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);

    // Data/MC b-tag scale factor
    double sfb(double pt, double eta)
    {
      if( algo_ == CSVL ) {
        if( pt > 30 && pt < 670) { return 1.02658*((1.+(0.0195388*pt))/(1.+(0.0209145*pt))); }
        else if( pt <= 30 ) { return 1.02658*((1.+(0.0195388*30.0))/(1.+(0.0209145*30.0))); }
        else { return 1.02658*((1.+(0.0195388*670.0))/(1.+(0.0209145*670.0))); }
      }
      else if( algo_ == CSVM ){
        if( pt > 30 && pt < 670) { return 0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt))); }
        else if( pt <= 30 ) { return 0.6981*((1.+(0.414063*30.0))/(1.+(0.300155*30.0))); }
        else { return 0.6981*((1.+(0.414063*670.0))/(1.+(0.300155*670.0))); }
      }
      else if( algo_ == CSVT ){
        if( pt > 30 && pt < 670) { return 0.901615*((1.+(0.552628*pt))/(1.+(0.547195*pt))); }
        else if( pt <= 30 ) { return 0.901615*((1.+(0.552628*30.0))/(1.+(0.547195*30.0))); }
        else { return 0.901615*((1.+(0.552628*670.0))/(1.+(0.547195*670.0))); }
      }else { return 1.0; } 
    }

    // data/MC b-tag scale factor
    double sfc(double pt, double eta)
    {
      if( algo_ == CSVL ) {
        if( pt > 30 && pt < 670) { return 1.02658*((1.+(0.0195388*pt))/(1.+(0.0209145*pt))); }
        else if( pt <= 30 ) { return 1.02658*((1.+(0.0195388*30.0))/(1.+(0.0209145*30.0))); }
        else { return 1.02658*((1.+(0.0195388*670.0))/(1.+(0.0209145*670.0))); }
      }
      else if( algo_ == CSVM ){
        if( pt > 30 && pt < 670) { return 0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt))); }
        else if( pt <= 30 ) { return 0.6981*((1.+(0.414063*30.0))/(1.+(0.300155*30.0))); }
        else { return 0.6981*((1.+(0.414063*670.0))/(1.+(0.300155*670.0))); }
      }
      else if( algo_ == CSVT ){
        if( pt > 30 && pt < 670) { return 0.901615*((1.+(0.552628*pt))/(1.+(0.547195*pt))); }
        else if( pt <= 30 ) { return 0.901615*((1.+(0.552628*30.0))/(1.+(0.547195*30.0))); }
        else { return 0.901615*((1.+(0.552628*670.0))/(1.+(0.547195*670.0))); }
      }else { return 1.0; }
    }

    // data/mc l-tag scale factor
    double sfl(double pt, double eta)
    {
      if( algo_ == CSVL ){
        if( pt <= 670 ){
          if( fabs(eta) < 0.5) return ((1.07536+(0.000175506*pt))+(-8.63317e-07*(pt*pt)))+(3.27516e-10*(pt*(pt*pt)));
          else if( fabs(eta) >= 0.5 && fabs(eta) < 1.0) return ((1.07846+(0.00032458*pt))+(-1.30258e-06*(pt*pt)))+(8.50608e-10*(pt*(pt*pt)));
          else if( fabs(eta) >= 1.0 && fabs(eta) < 1.5) return ((1.08294+(0.000474818*pt))+(-1.43857e-06*(pt*pt)))+(1.13308e-09*(pt*(pt*pt)));
          else if( fabs(eta) >= 1.5 && fabs(eta) < 2.4) return ((1.0617+(0.000173654*pt))+(-5.29009e-07*(pt*pt)))+(5.55931e-10*(pt*(pt*pt)));
          else return ((1.0617+(0.000173654*pt))+(-5.29009e-07*(pt*pt)))+(5.55931e-10*(pt*(pt*pt)));
        }else {
          return ((1.0344+(0.000962994*670.0))+(-3.65392e-06*(670.0*670.0)))+(3.23525e-09*(670.0*(670.0*670.0)));
        }
      }else if( algo_ == CSVM ){
        if( pt <= 670){
          if( fabs(eta) < 0.8 ) return ((1.06182+(0.000617034*pt))+(-1.5732e-06*(pt*pt)))+(3.02909e-10*(pt*(pt*pt)));
          else if( fabs(eta) >= 0.8 && fabs(eta) < 1.6) return ((1.111+(-9.64191e-06*pt))+(1.80811e-07*(pt*pt)))+(-5.44868e-10*(pt*(pt*pt)));
          else if( fabs(eta) >= 1.6 && fabs(eta) < 2.4) return ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));
          else return ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));
        }else {
          return ((1.04318+(0.000848162*670.0))+(-2.5795e-06*(670.0*670.0)))+(1.64156e-09*(670.0*(670.0*670.0)));
        }
      }else if( algo_ == CSVT){
        if( pt <= 670 ){
          return ((0.948463+(0.00288102*pt))+(-7.98091e-06*(pt*pt)))+(5.50157e-09*(pt*(pt*pt)));
        }else { 
          return ((0.948463+(0.00288102*670.0))+(-7.98091e-06*(670.0*670.0)))+(5.50157e-09*(670.0*(670.0*670.0)));
        }
      }else { 
        return 1.0; 
      }
    }

    // MC b-tag efficiency // need to be updated with our numbers from our signal samples
    double eb(double pt, double eta)
    {
      double x;
      if( algo_ == CSVL) x = 0.244;
      else if( algo_ == CSVM ) x = 0.679;
      else if( algo_ == CSVT ) x = 0.898;
      else x = 0; //it should not reach this point
      
      return -1.73338329789*x*x*x*x +  1.26161794785*x*x*x +  0.784721653518*x*x +  -1.03328577451*x +  1.04305075822;
    }

    //MC c-tag efficiency
    double ec(double pt, double eta)
    {
      double x;
      if( algo_ == CSVL) x = 0.244;
      else if( algo_ == CSVM ) x = 0.679;
      else if( algo_ == CSVT ) x = 0.898; 
      else x = 0; // it should not reach this point
      
      return -1.5734604211*x*x*x*x +  1.52798999269*x*x*x +  0.866697059943*x*x +  -1.66657942274*x +  0.780639301724;
    }

    //MC l-tag efficiency
    double el(double pt, double eta)
    {
      if( algo_ == CSVL ){
        if( pt <= 670 ){
          if( fabs(eta) < 0.5) return 242534*(((1+(0.0182863*pt))+(4.50105e-05*(pt*pt)))/(1+(108569*pt)));
          else if( fabs(eta) >= 0.5 && fabs(eta) < 1.0) return 129.938*(((1+(0.0197657*pt))+(4.73472e-05*(pt*pt)))/(1+(55.2415*pt)));
          else if( fabs(eta) >= 1.0 && fabs(eta) < 1.5) return 592.214*(((1+(0.00671207*pt))+(6.46109e-05*(pt*pt)))/(1+(134.318*pt)));
          else if( fabs(eta) >= 1.5 && fabs(eta) < 2.4) return 93329*(((1+(0.0219705*pt))+(3.76566e-05*(pt*pt)))/(1+(18245.1*pt)));
          else return 93329*(((1+(0.0219705*pt))+(3.76566e-05*(pt*pt)))/(1+(18245.1*pt)));
        }else {
          return 18168.8*(((1+(0.020356*670.0))+(2.73475e-05*(670.0*670.0)))/(1+(5239.42*670.0)));
        }
      }else if( algo_ == CSVM ){
        if( pt <= 670){
          if( fabs(eta) < 0.8 ) return (0.00967751+(2.54564e-05*pt))+(-6.92256e-10*(pt*pt));
          else if( fabs(eta) >= 0.8 && fabs(eta) < 1.6) return (0.00974141+(5.09503e-05*pt))+(2.0641e-08*(pt*pt));
          else if( fabs(eta) >= 1.6 && fabs(eta) < 2.4) return (0.013595+(0.000104538*pt))+(-1.36087e-08*(pt*pt));
          else return (0.013595+(0.000104538*pt))+(-1.36087e-08*(pt*pt));
        }else {
          return (0.0113428+(5.18983e-05*670.0))+(-2.59881e-08*(670.0*670.0));
        }
      }else if( algo_ == CSVT){
        if( pt <= 670 ){
          return 0.00315116*(((1+(-0.00769281*pt))+(2.58066e-05*(pt*pt)))+(-2.02149e-08*(pt*(pt*pt))));
        }else {
          return 0.00315116*(((1+(-0.00769281*670.0))+(2.58066e-05*(670.0*670.0)))+(-2.02149e-08*(670.0*(670.0*670.0))));
        }
      }else {
        return 0;
      }
    }

    private:

      AlgoType algo_;

};

#endif

