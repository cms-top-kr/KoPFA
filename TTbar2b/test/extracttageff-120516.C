// Author: Suyong Choi
// Date: 2012-05-04
// Usage: 
// If you have distribution of number of b-tagged jets, n0, n1, n2, n3
// calling extracttageff(n0, n1, n2, n3) will create a histogram and fit to
// extract b-tagging, light tagging efficiencies and acceptance for 2 b-quarks 
// from tt-bar decays. 
//
// This acceptance for 2 b-quark jets may not be always 1 
// after requiring 2 leptons + 4 jets + MET
//

// number of events with 0 tag
// input arguments
// eb: b-jet tag efficiency
// el: light jet tagging efficiency
// nb0: number of events with 0 b-quark passing acceptance cuts
// nb1: number of events with 1 b-quark passing acceptance cuts
// nb2: number of events with 1 b-quark passing acceptance cuts
// nl: number of extra jets (besides the b-quark jets) in event
//

#include "TH2F.h"
#include "TMath.h"
#include "TRandom3.h"

// fraction of events with 4,5,6,... hadronic jets after selection (before b-tagging)
double njetfrac[10]={0.714, 0.210, 0.0583, 0.0147, 0.00302, 0.00058, 0, 0, 0, 0}; //CMSSW
// fraction of events with 0,1,2,3 bquarks
double accarr[4] = {0.01, 0.194, 0.759, 0.036}; // CMSSW

int ntotal;

double nbtag(double *x, double *par)
{
    int ntag = x[0];

    double eb = par[0];
    double el = par[1];//0.0011; // fix or let it float

    double nb2weight=0.0;
    double nb1weight=0.0;
    double nb0weight=0.0;

    // case when 3 b quarks in acceptance
    for (int ib=0; ib<=TMath::Min(3, ntag); ib++) // maximum 2 tags
    {
        double bweight = TMath::Binomial(3, ib) * TMath::Power(eb, ib) * TMath::Power(1.0-eb, 3-ib);
        double lweight=0.0;
        int iltag = ntag-ib;
        for (int ljet=TMath::Max(iltag, 1); ljet<=6; ljet++) // number of lightjets
        {
            lweight += njetfrac[ljet-1] *TMath::Binomial(ljet, iltag) 
                * TMath::Power(el, iltag) * TMath::Power(1.0-el, ljet-iltag);
        }
        nb2weight += accarr[3]*bweight*lweight;
    }

    // case when b quark in acceptance is 2
    for (int ib=0; ib<=TMath::Min(2, ntag); ib++) // maximum 2 tags
    {
        double bweight = TMath::Binomial(2, ib) * TMath::Power(eb, ib) * TMath::Power(1.0-eb, 2-ib);
        double lweight=0.0;
        int iltag = ntag-ib;
        for (int ljet=TMath::Max(iltag, 2); ljet<=6; ljet++) // number of lightjets
        {
            lweight += njetfrac[ljet-2] *TMath::Binomial(ljet, iltag) 
                * TMath::Power(el, iltag) * TMath::Power(1.0-el, ljet-iltag);
        }
        nb2weight += accarr[2]*bweight*lweight;
    }
    // case when b quark in acceptance is 1
    for (int ib=0; ib<=TMath::Min(1, ntag); ib++) // maximum 1 tag
    {
        double bweight = TMath::Binomial(1, ib) * TMath::Power(eb, ib) * TMath::Power(1.0-eb, 1-ib);
        double lweight=0.0;
        int iltag = ntag-ib;
        for (int ljet=TMath::Max(iltag, 3); ljet<=7; ljet++) // number of lightjets
        {
            lweight += njetfrac[ljet-3] *TMath::Binomial(ljet, iltag) 
                * TMath::Power(el, iltag) * TMath::Power(1.0-el, ljet-iltag);
        }
        nb1weight += accarr[1]*bweight*lweight;
    }
    // case when b quark in acceptance is 0
    for (int ib=0; ib<=TMath::Min(0, ntag); ib++) // maximum 2 tags
    {
        double bweight = 1.0;
        double lweight=0.0;
        int iltag = ntag-ib;
        for (int ljet=TMath::Max(iltag, 4); ljet<=8; ljet++) // number of lightjets
        {
            lweight += njetfrac[ljet-4] *TMath::Binomial(ljet, iltag) 
                * TMath::Power(el, iltag) * TMath::Power(1.0-el, ljet-iltag);
        }
        nb0weight += accarr[0]*bweight*lweight;
    }
    return ntotal*(nb0weight+nb1weight + nb2weight);
}

void extracttageff(int n0, int n1, int n2, int n3)
{

    // n3 information is not used in the fit
    h1=new TH1F("h1", "h1",3, 0.0, 3.0);
    h1->Fill(0, n0);
    h1->Fill(1, n1);
    h1->Fill(2, n2);
    h1->Fill(3, n3);

    ntotal = n0+n1+n2+n3;

    double eb_initial = 0.5;
    double el_initial = 0.0152364;

    TF1 *ftot = new TF1("ftot", nbtag, 0.0,5, 2);
    ftot->SetParameters(eb_initial, el_initial);
    ftot->SetParLimits(1, el_initial, el_initial);
    h1->Fit("ftot");
    h1->Draw("e");
}

void extracttageff(){
  //cout << "CSVL" << endl;
  //extracttageff(7052,47093,73842,8479);
  cout << "CSVM" << endl;
  extracttageff(19953,65087,51009,1119);
  //cout << "CSVT" << endl;
  //extracttageff(37546,68532,30829,296);
}

void predictntags_mc(double eb, double eberr, double el, double elerr)
{
    ntotal = 1;
    TH1F *hntag0 = new TH1F("hntag0", "0 tag prediction", 100, 0.0, 1.0);
    TH1F *hntag1 = new TH1F("hntag1", "1 tag prediction", 100, 0.0, 1.0);
    TH1F *hntag2 = new TH1F("hntag2", "2 tag prediction", 100, 0.0, 1.0);
    TH1F *hntag3 = new TH1F("hntag3", "3 tag prediction", 100, 0.0, 1.0);

    TRandom3 rn;

    for (int i=0; i<1000; i++)
    {
        ftot->SetParameters(rn.Gaus(eb, eberr), rn.Gaus(el, elerr));
        hntag0->Fill(ftot->Eval(0.5));
        hntag1->Fill(ftot->Eval(1.5));
        hntag2->Fill(ftot->Eval(2.5));
        hntag3->Fill(ftot->Eval(3.5));
    }
}
