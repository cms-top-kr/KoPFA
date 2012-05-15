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
double nb0(double eb, double el, double nb0, double nb1, double nb2, double nl)
{
    return nb2*(1.0-eb)*(1.0-eb)*TMath::Power(1-el, nl) 
        + nb1*(1-eb)*TMath::Power(1-el,nl+1);
}

// number of events with 1 tag
double nb1(double eb, double el, double nb0, double nb1, double nb2, double nl)
{
    return nb2*(2*eb*(1.0-eb)*TMath::Power(1-el, nl) 
            +nl*(1-eb)*(1-eb)*el*TMath::Power(1-el, nl-1))
        + nb1*(eb*TMath::Power(1-el,nl+1)+(nl+1)*(1-eb)*el*TMath::Power(1-el, nl));
}

// number of events with 2 tags
double nb2(double eb, double el, double nb0, double nb1, double nb2, double nl)
{
    return nb2*( eb*eb*TMath::Power(1-el,nl)
                 + 2*nl*eb*(1-eb)*el*TMath::Power(1-el,nl-1)
                 + TMath::Binomial(nl, 2)*(1-eb)*(1-eb)*el*el*TMath::Power(1-el,nl-2))
          + nb1*eb*el*(nl+1)*TMath::Power(1-el,nl);
}

// number of events with 3 tags
double nb3(double eb, double el, double nb0, double nb1, double nb2, double nl)
{
    return nb2*( eb*eb*nl*el*TMath::Power(1-el,nl-1)
                 + 2*eb*(1-eb)*TMath::Binomial(nl,2)*el*el*TMath::Power(1-el,nl-2))
          + nb1*nl*eb*el*el*(1-el);
}

// number of events with 4 tags
double nb4(double eb, double el, double nb0, double nb1, double nb2, double nl)
{
    return nb2*eb*eb*el*el + nb1*eb*el*el*el;
}
double ntotal;

/*
double nball(double *x, double *par)
{
    if (x[0]>=0.0 && x[0]<1.0) return nb0(par[0], par[1], 0.0, ntotal*(1-par[2]), ntotal*par[2],3);
    else if (x[0]>=1.0 && x[0]<2.0) return nb1(par[0], par[1], 0.0, ntotal*(1-par[2]), ntotal*par[2],3);
    else if (x[0]>=2.0 && x[0]<3.0) return nb2(par[0], par[1], 0.0, ntotal*(1-par[2]), ntotal*par[2],3);
    else if (x[0]>=3.0 && x[0]<4.0) return nb3(par[0], par[1], 0.0, ntotal*(1-par[2]), ntotal*par[2],3);
}
*/

// 
double eb=0.7;
double el=0.1; // estimate from fake tagging 
double acc = 0.98; // estimate this from MC

// par[0] is b-tagging efficiency
double nball(double *x, double *par)
{
    if (x[0]>=0.0 && x[0]<1.0) return nb0(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2);
    else if (x[0]>=1.0 && x[0]<2.0) return nb1(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2);
    else if (x[0]>=2.0 && x[0]<3.0) return nb2(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2);
    else if (x[0]>=3.0 && x[0]<4.0) return nb3(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2);
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
    double eb_initial = 0.6;
    double el_initial=el;
    double acc_initial=acc;

    TF1 *ftot = new TF1("ftot", nball, 0.0,2.9, 2);
    ftot->SetParameters(eb_initial, el_initial, acc_initial);
    
    //ftot->SetParLimits(0, 0.0, 1.0);
    //ftot->SetParLimits(1, 0.0, 1000.0);
    //ftot->SetParLimits(2, 0.0, 1000.0);
    
    h1->Fit("ftot");
    h1->Draw("e");
}

void extracttageff(){
  cout << "CSVL" << endl;
  extracttageff(7052,47093,73842,8479);
  //cout << "CSVM" << endl;
  //extracttageff(19953,65087,51009,1119);
  //cout << "CSVT" << endl;
  //extracttageff(37546,68532,30829,296);

}
