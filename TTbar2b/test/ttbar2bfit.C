//
//   Example of a program to fit non-equidistant data points
//   =======================================================
//
//   The fitting function fcn is a simple chisquare function
//   The data consists of 5 data points (arrays x,y,z) + the errors in errorsz
//   More details on the various functions or parameters for these functions
//   can be obtained in an interactive ROOT session with:
//    Root > TMinuit *minuit = new TMinuit(10);
//    Root > minuit->mnhelp("*")  to see the list of possible keywords
//    Root > minuit->mnhelp("SET") explains most parameters
//Author: Rene Brun

#include "TMinuit.h"

Float_t z[3],b[3],c[3],l[3],errorz[3];

//______________________________________________________________________________
Double_t func(float b,float c,float l,Double_t *par)
{
 Double_t value= par[0]*b + par[1]*c + par[2]*l;
 
 return value;
}

//______________________________________________________________________________
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 3;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   for (i=0;i<nbins; i++) {
     delta  = (z[i]-func(b[i],c[i],l[i],par))/errorz[i];
     chisq += delta*delta;
   }
   f = chisq;
}

//______________________________________________________________________________
void ttbar2bfit()
{
// The z values
	z[0]=172;
	z[1]=21;
        z[2]=127;
// The errors on z values
	errorz[0]=sqrt( z[0] );
	errorz[1]=sqrt( z[1] );
	errorz[2]=sqrt( z[2] );
// the b values
	b[0]=0.94;
	b[1]=0.70;
        b[2]=0.89;
// the c values
	c[0]=0.53;
	c[1]=0.21;
	c[2]=0.64;
// the l values
        l[0]=0.53;
        l[1]=0.10;
        l[2]=0.15;

   TMinuit *gMinuit = new TMinuit(3);  //initialize TMinuit with a maximum of 2 params
   gMinuit->SetFCN(fcn);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   static Double_t vstart[3] = {0.0, 0.0, 0.0};
   static Double_t step[3] = {0.001 , 0.001, 0.001};
   gMinuit->mnparm(0, "a1", vstart[0], step[0], 0.0,0.0,ierflg);
   gMinuit->mnparm(1, "a2", vstart[1], step[1], 0.0,0.0,ierflg);
   gMinuit->mnparm(2, "a3", vstart[2], step[2], 0.0,0.0,ierflg);

// Now ready for minimization step
   arglist[0] = 500;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   //gMinuit->mnprin(3,amin);

}



