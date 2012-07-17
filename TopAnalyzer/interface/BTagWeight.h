#ifndef BTAGWEIGHT_H
#define BTAGWEIGHT_H

#include <vector>
#include "TLorentzVector.h"
#include <iostream>
using namespace std;

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

    enum SYS {
      NORM,
      DW,
      UP
    };

    double reweight(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, AlgoType algo, SYS sys);

    double probmc(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);
    double probdata(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);
    

    double sfbErr(double pt, double eta){
      float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};
      float ptmax[] = {40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 670};

      double err = 0;

      if( algo_ == CSVL){
        double SFb_error[] = {
          0.0188743,
          0.0161816,
          0.0139824,
          0.0152644,
          0.0161226,
          0.0157396,
          0.0161619,
          0.0168747,
          0.0257175,
          0.026424,
          0.0264928,
          0.0315127,
          0.030734,
          0.0438259 
        };
        if( pt < 30 ) err = 0.12;
        if( pt >= 30 && pt <= 670){
          for(int i=0; i < 14; i++){
            if( pt > ptmin[i] && pt <= ptmax[i] ) {
              err = SFb_error[i];
              break;
            }
          }
        }
        if( pt > 670 ) err = SFb_error[13]*2;
      }else if( algo_ == CSVM){
        double SFb_error[] = {
          0.0295675,
          0.0295095,
          0.0210867,
          0.0219349,
          0.0227033,
          0.0204062,
          0.0185857,
          0.0256242,
          0.0383341,
          0.0409675,
          0.0420284,
          0.0541299,
          0.0578761,
          0.0655432 
        };
        if( pt < 30 ) err = 0.12;
        if( pt >= 30 && pt <= 670){
          for(int i=0; i < 14; i++){
            if( pt > ptmin[i] && pt <= ptmax[i] ) {
              err = SFb_error[i];
              break;
            }
          }
        }
        if( pt > 670 ) err = SFb_error[13]*2;
      }else if( algo_ == CSVT){
        double SFb_error[] = {
	  0.0364717,
	  0.0362281,
	  0.0232876,
	  0.0249618,
	  0.0261482,
	  0.0290466,
	  0.0300033,
	  0.0453252,
	  0.0685143,
	  0.0653621,
	  0.0712586,
	  0.094589,
          0.0777011,
          0.0866563 
        };
        if( pt < 30 ) err = 0.12;
        if( pt >= 30 && pt <= 670){
          for(int i=0; i < 14; i++){
            if( pt > ptmin[i] && pt <= ptmax[i] ) {
              err = SFb_error[i];
              break;
            }
          }
        }
        if( pt > 670 ) err = SFb_error[13]*2;
      }

      if( sys_ == NORM) return 0;
      else if( sys_ == UP ) return err; 
      else if( sys_ == DW ) return -err; 
      else return 0;
    } 

    // Data/MC b-tag scale factor
    double sfb(double pt, double eta)
    {
      double sf = 1;
      if( algo_ == CSVL ) {
        if( pt > 30 && pt < 670)  sf =  1.02658*((1.+(0.0195388*pt))/(1.+(0.0209145*pt))) + sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  1.02658*((1.+(0.0195388*30.0))/(1.+(0.0209145*30.0))) + sfbErr(pt,eta);
        else  sf =  1.02658*((1.+(0.0195388*670.0))/(1.+(0.0209145*670.0))) + sfbErr(pt,eta);
      } else if( algo_ == CSVM ){
        if( pt > 30 && pt < 670)  sf =  0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt))) + sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  0.6981*((1.+(0.414063*30.0))/(1.+(0.300155*30.0))) + sfbErr(pt,eta);
        else  sf =  0.6981*((1.+(0.414063*670.0))/(1.+(0.300155*670.0))) + sfbErr(pt,eta);
      } else if( algo_ == CSVT ){
        if( pt > 30 && pt < 670)  sf =  0.901615*((1.+(0.552628*pt))/(1.+(0.547195*pt))) + sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  0.901615*((1.+(0.552628*30.0))/(1.+(0.547195*30.0))) + sfbErr(pt,eta);
        else  sf =  0.901615*((1.+(0.552628*670.0))/(1.+(0.547195*670.0))) + sfbErr(pt,eta);
      } else  sf =  1.0; 
      return sf;
    }

    // data/MC b-tag scale factor
    double sfc(double pt, double eta)
    {
      double sf = 1;
      if( algo_ == CSVL ) {
        if( pt > 30 && pt < 670)  sf =  1.02658*((1.+(0.0195388*pt))/(1.+(0.0209145*pt))) + 2*sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  1.02658*((1.+(0.0195388*30.0))/(1.+(0.0209145*30.0))) + 2*sfbErr(pt,eta);
        else  sf =  1.02658*((1.+(0.0195388*670.0))/(1.+(0.0209145*670.0))) + 2*sfbErr(pt,eta);
      } else if( algo_ == CSVM ){
        if( pt > 30 && pt < 670)  sf =  0.6981*((1.+(0.414063*pt))/(1.+(0.300155*pt))) + 2*sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  0.6981*((1.+(0.414063*30.0))/(1.+(0.300155*30.0))) + 2*sfbErr(pt,eta);
        else  sf =  0.6981*((1.+(0.414063*670.0))/(1.+(0.300155*670.0))) + 2*sfbErr(pt,eta);
      } else if( algo_ == CSVT ){
        if( pt > 30 && pt < 670)  sf =  0.901615*((1.+(0.552628*pt))/(1.+(0.547195*pt))) + 2*sfbErr(pt,eta);
        else if( pt <= 30 )  sf =  0.901615*((1.+(0.552628*30.0))/(1.+(0.547195*30.0))) + 2*sfbErr(pt,eta);
        else  sf =  0.901615*((1.+(0.552628*670.0))/(1.+(0.547195*670.0))) + 2*sfbErr(pt,eta);
      } else  sf =  1.0;
      return sf;
    }

    // data/mc l-tag scale factor
    double sfl(double pt, double eta)
    {
      double sf = 1;
      if( algo_ == CSVL ){
        if( pt <= 670 ){
          if( fabs(eta) < 0.5) {
            if( sys_ == NORM )  sf = ((1.07536+(0.000175506*pt))+(-8.63317e-07*(pt*pt)))+(3.27516e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.994425+(-8.66392e-05*pt))+(-3.03813e-08*(pt*pt)))+(-3.52151e-10*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.15628+(0.000437668*pt))+(-1.69625e-06*(pt*pt)))+(1.00718e-09*(pt*(pt*pt)));
          } else if( fabs(eta) >= 0.5 && fabs(eta) < 1.0) {
            if( sys_ == NORM )  sf = ((1.07846+(0.00032458*pt))+(-1.30258e-06*(pt*pt)))+(8.50608e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.998088+(6.94916e-05*pt))+(-4.82731e-07*(pt*pt)))+(1.63506e-10*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.15882+(0.000579711*pt))+(-2.12243e-06*(pt*pt)))+(1.53771e-09*(pt*(pt*pt)));
          } else if( fabs(eta) >= 1.0 && fabs(eta) < 1.5) {
            if( sys_ == NORM )  sf = ((1.08294+(0.000474818*pt))+(-1.43857e-06*(pt*pt)))+(1.13308e-09*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((1.00294+(0.000289844*pt))+(-7.9845e-07*(pt*pt)))+(5.38525e-10*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.16292+(0.000659848*pt))+(-2.07868e-06*(pt*pt)))+(1.72763e-09*(pt*(pt*pt)));
          } else if( fabs(eta) >= 1.5 && fabs(eta) < 2.4) {
            if( sys_ == NORM )  sf = ((1.0617+(0.000173654*pt))+(-5.29009e-07*(pt*pt)))+(5.55931e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.979816+(0.000138797*pt))+(-3.14503e-07*(pt*pt)))+(2.38124e-10*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.14357+(0.00020854*pt))+(-7.43519e-07*(pt*pt)))+(8.73742e-10*(pt*(pt*pt)));
          } else {
            if( sys_ == NORM )  sf = ((1.0617+(0.000173654*pt))+(-5.29009e-07*(pt*pt)))+(5.55931e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.979816+(0.000138797*pt))+(-3.14503e-07*(pt*pt)))+(2.38124e-10*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.14357+(0.00020854*pt))+(-7.43519e-07*(pt*pt)))+(8.73742e-10*(pt*(pt*pt)));
          }
        }else {
          if( sys_ == NORM )  sf = ((1.0344+(0.000962994*670.0))+(-3.65392e-06*(670.0*670.0)))+(3.23525e-09*(670.0*(670.0*670.0)));
          if( sys_ == DW )  sf = ((0.956023+(0.000825106*670.0))+(-3.18828e-06*(670.0*670.0)))+(2.81787e-09*(670.0*(670.0*670.0)));
          if( sys_ == UP )  sf = ((1.11272+(0.00110104*670.0))+(-4.11956e-06*(670.0*670.0)))+(3.65263e-09*(670.0*(670.0*670.0)));
        }
      } else if( algo_ == CSVM ){
        if( pt <= 670){
          if( fabs(eta) < 0.8 ) {
            if( sys_ == NORM )  sf = ((1.06182+(0.000617034*pt))+(-1.5732e-06*(pt*pt)))+(3.02909e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.972455+(7.51396e-06*pt))+(4.91857e-07*(pt*pt)))+(-1.47661e-09*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.15116+(0.00122657*pt))+(-3.63826e-06*(pt*pt)))+(2.08242e-09*(pt*(pt*pt)));
          } else if( fabs(eta) >= 0.8 && fabs(eta) < 1.6) {
            if( sys_ == NORM )  sf = ((1.111+(-9.64191e-06*pt))+(1.80811e-07*(pt*pt)))+(-5.44868e-10*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((1.02055+(-0.000378856*pt))+(1.49029e-06*(pt*pt)))+(-1.74966e-09*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.20146+(0.000359543*pt))+(-1.12866e-06*(pt*pt)))+(6.59918e-10*(pt*(pt*pt)));
          } else if( fabs(eta) >= 1.6 && fabs(eta) < 2.4) {
            if( sys_ == NORM )  sf = ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.983476+(-0.000607242*pt))+(3.17997e-06*(pt*pt)))+(-4.01242e-09*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.18654+(-0.000795808*pt))+(3.69226e-06*(pt*pt)))+(-4.22347e-09*(pt*(pt*pt)));
          } else {
            if( sys_ == NORM )  sf = ((1.08498+(-0.000701422*pt))+(3.43612e-06*(pt*pt)))+(-4.11794e-09*(pt*(pt*pt)));
            if( sys_ == DW )  sf = ((0.983476+(-0.000607242*pt))+(3.17997e-06*(pt*pt)))+(-4.01242e-09*(pt*(pt*pt)));
            if( sys_ == UP )  sf = ((1.18654+(-0.000795808*pt))+(3.69226e-06*(pt*pt)))+(-4.22347e-09*(pt*(pt*pt)));
          }
        } else {
          if( sys_ == NORM )  sf = ((1.04318+(0.000848162*670.0))+(-2.5795e-06*(670.0*670.0)))+(1.64156e-09*(670.0*(670.0*670.0)));
          if( sys_ == DW )  sf = ((0.962627+(0.000448344*670.0))+(-1.25579e-06*(670.0*670.0)))+(4.82283e-10*(670.0*(670.0*670.0)));
          if( sys_ == UP )  sf = ((1.12368+(0.00124806*670.0))+(-3.9032e-06*(670.0*670.0)))+(2.80083e-09*(670.0*(670.0*670.0)));
        } 
      } else if( algo_ == CSVT){
        if( pt <= 670 ){
          if( sys_ == NORM )  sf = ((0.948463+(0.00288102*pt))+(-7.98091e-06*(pt*pt)))+(5.50157e-09*(pt*(pt*pt)));
          if( sys_ == DW )  sf = ((0.899715+(0.00102278*pt))+(-2.46335e-06*(pt*pt)))+(9.71143e-10*(pt*(pt*pt)));
          if( sys_ == UP )  sf = ((0.997077+(0.00473953*pt))+(-1.34985e-05*(pt*pt)))+(1.0032e-08*(pt*(pt*pt)));
        }else { 
          if( sys_ == NORM )  sf = ((0.948463+(0.00288102*670.0))+(-7.98091e-06*(670.0*670.0)))+(5.50157e-09*(670.0*(670.0*670.0)));
          if( sys_ == DW )  sf = ((0.899715+(0.00102278*670.0))+(-2.46335e-06*(670.0*670.0)))+(9.71143e-10*(670.0*(670.0*670.0)));
          if( sys_ == UP )  sf = ((0.997077+(0.00473953*670.0))+(-1.34985e-05*(670.0*670.0)))+(1.0032e-08*(670.0*(670.0*670.0)));
        }
      }else { 
         sf = 1.0; 
      }
      return sf;
    }

    // MC b-tag efficiency // need to be updated with our numbers from our signal samples
    double eb(double pt, double eta)
    {
      if( algo_ == CSVL ){
	    if( pt <= 450 ){
	    	return 0.801548 + 0.00147981*pt - 1.24055e-05*(pt*pt) + 3.84141e-08*(pt*pt*pt) - 4.31462e-11*(pt*pt*pt*pt);
	  	}
		else{
	    	return 0.801548 + 0.00147981*450.0 - 1.24055e-05*(450.0*450.0) + 3.84141e-08*(450.0*450.0*450.0) - 4.31462e-11*(450.0*450.0*450.0*450.0);
		}
	  }
      else if( algo_ == CSVM ){
	    if( pt <= 450 ){
	    	return 0.331138 + 0.0101574*pt - 7.99679e-05*(pt*pt) + 2.44717e-07*(pt*pt*pt) - 2.5903e-10*(pt*pt*pt*pt);
	  	}
		else{
	    	return 0.331138 + 0.0101574*450.0 - 7.99679e-05*(450.0*450.0) + 2.44717e-07*(450.0*450.0*450.0) - 2.5903e-10*(450.0*450.0*450.0*450.0);
		}
	  }
      else if( algo_ == CSVT ){
	    if( pt <= 450 ){
	    	return 0.109639 + 0.0130669*pt - 0.000112374*(pt*pt) + 3.50834e-07*(pt*pt*pt) - 3.66859e-10*(pt*pt*pt*pt);
	  	}
		else{
	    	return 0.109639 + 0.0130669*450.0 - 0.000112374*(450.0*450.0) + 3.50834e-07*(450.0*450.0*450.0) - 3.66859e-10*(450.0*450.0*450.0*450.0);
		}
	  }
	  else
	  {
         return 0;
	  }
    }

    //MC c-tag efficiency
    double ec(double pt, double eta)
    {
      if( algo_ == CSVL ){
	  	if( pt <= 450 ){
	    	return 0.610269 + -0.00549809*pt + 4.15105e-05*(pt*pt) + -1.28433e-07*(pt*pt*pt) + 1.32483e-10*(pt*pt*pt*pt);
	  	}
	  	else{
	    	return 0.610269 + -0.00549809*450.0 + 4.15105e-05*(450.0*450.0) + -1.28433e-07*(450.0*450.0*450.0) + 1.32483e-10*(450.0*450.0*450.0*450.0);
	  	}
	  }
      else if( algo_ == CSVM ){
	  	if( pt <= 450 ){
	    	return 0.0815163 + 0.0021852*pt + -1.41307e-05*(pt*pt) + 3.24437e-08*(pt*pt*pt) + -2.55116e-11*(pt*pt*pt*pt);
	  	}
	  	else{
	    	return 0.0815163 + 0.0021852*450.0 + -1.41307e-05*(450.0*450.0) + 3.24437e-08*(450.0*450.0*450.0) + -2.55116e-11*(450.0*450.0*450.0*450.0);
	  	}
	  }
      else if( algo_ == CSVT ){
	  	if( pt <= 450 ){
	    	return 0.0213977 + 0.00118318*pt + -1.18986e-05*(pt*pt) + 3.83806e-08*(pt*pt*pt) + -3.97903e-11*(pt*pt*pt*pt);
	  	}
	  	else{
	    	return 0.0213977 + 0.00118318*450.0 + -1.18986e-05*(450.0*450.0) + 3.83806e-08*(450.0*450.0*450.0) + -3.97903e-11*(450.0*450.0*450.0*450.0);
	  	}
	  }
	  else
	  {
        return 0;
	  }
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
      SYS sys_;

};

#endif

