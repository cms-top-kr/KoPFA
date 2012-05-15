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
double nb0(double eb, double el, double nb0, double nb1, double nb2, double nb3, double nb4, double nb5, double nb6, double nl, double eb2)
{
    return nb2*(1.0-eb)*(1.0-eb)*TMath::Power(1-el, nl) 
        + nb1*(1-eb)*TMath::Power(1-el,nl+1);
        //+ nb4*(1-eb)*(1-eb)*TMath::Power(1-eb2,2);
        //+ nb3*(1-eb)*(1-eb2)*(1-el)*(1-el);
}

// number of events with 1 tag
double nb1(double eb, double el, double nb0, double nb1, double nb2, double nb3, double nb4, double nb5, double nb6, double nl, double eb2)
{
    return nb2*(2*eb*(1.0-eb)*TMath::Power(1-el, nl) 
            +nl*(1-eb)*(1-eb)*el*TMath::Power(1-el, nl-1))
        + nb1*(eb*TMath::Power(1-el,nl+1)+(nl+1)*(1-eb)*el*TMath::Power(1-el, nl));
        //+ nb4*(2*eb*(1.0-eb)*TMath::Power(1-eb2, 2)
        //    +2*(1-eb)*(1-eb)*eb2*TMath::Power(1-eb2, 1));
        //+ nb3*(2*eb*(1-eb2)*(1-el)) ;
}

// number of events with 2 tags
double nb2(double eb, double el, double nb0, double nb1, double nb2, double nb3, double nb4, double nb5, double nb6, double nl, double eb2)
{
    return nb2*( eb*eb*TMath::Power(1-el,nl)
                 + 2*nl*eb*(1-eb)*el*TMath::Power(1-el,nl-1)
                 + TMath::Binomial(nl, 2)*(1-eb)*(1-eb)*el*el*TMath::Power(1-el,nl-2))
          + nb1*eb*el*(nl+1)*TMath::Power(1-el,nl);
         // + nb4*( eb*eb*TMath::Power(1-eb2,2)
         //        + 2*2*eb*(1-eb)*eb2*TMath::Power(1-eb2,1)
         //        + TMath::Binomial(2, 2)*(1-eb)*(1-eb)*eb2*eb2*TMath::Power(1-eb2,0))
         // + nb3*(eb*eb*(1-eb2)*(1-el) + 2*eb*eb2*(1-eb)*(1-el) + 2*eb*el*(1-eb)*(1-eb2) + eb2*el*(1-eb)*(1-eb))
          //+ nb6*( eb*eb*TMath::Power(1-eb2,4)
          //       + 2*4*eb*(1-eb)*eb2*TMath::Power(1-eb2,3)
          //       + TMath::Binomial(4, 2)*(1-eb)*(1-eb)*eb2*eb2*TMath::Power(1-eb2,2));

}

double nb2tag(double eb, double el, double nb1, double eb2, double nb2, double nb3, double nb4, double nl)
{
//    return eb*nb4 + el*nb2;

    return nb2*( eb*eb*TMath::Power(1-el,nl)
                 + 2*nl*eb*(1-eb)*el*TMath::Power(1-el,nl-1)
                 + TMath::Binomial(nl, 2)*(1-eb)*(1-eb)*el*el*TMath::Power(1-el,nl-2))
          + nb1*eb*el*(nl+1)*TMath::Power(1-el,nl)
          + nb4*( eb*eb*TMath::Power(1-eb2,2)
                 + 2*2*eb*(1-eb)*eb2*TMath::Power(1-eb2,1)
                 + TMath::Binomial(2, 2)*(1-eb)*(1-eb)*eb2*eb2*TMath::Power(1-eb2,0))
          + nb3*eb*eb*(1-eb2)*(1-el);
}

// number of events with 3 tags
double nb3(double eb, double el, double nb0, double nb1, double nb2, double nb3, double nb4, double nb5, double nb6, double nl, double eb2)
{
    return nb2*( eb*eb*nl*el*TMath::Power(1-el,nl-1)
                 + 2*eb*(1-eb)*TMath::Binomial(nl,2)*el*el*TMath::Power(1-el,nl-2))
          + nb1*nl*eb*el*el*(1-el)
          + nb4*( 2*eb*eb*eb2*(1-eb2)
                 + 2*eb*(1-eb)*eb2*eb2 );
          //+ nb3*( eb*eb*eb2*TMath::Power(1-el,nl) + eb*eb*el*(1-eb2)*TMath::Power(1-el,nl-1) + 2*nl*el*eb2*(1-eb)*TMath::Power(1-el,nl-1) + TMath::Binomial(nl,2)*el*el*(1-eb)*(1-eb)*(1-eb2) )
          //+ nb6*( 4*eb*eb*eb2*TMath::Power(1-eb2,3) + 2*TMath::Binomial(4,2)*eb*(1-eb)*eb2*eb2*TMath::Power(1-eb2,2) + TMath::Binomial(4,3)*(1-eb)*(1-eb)*eb2*eb2*eb2*(1-eb2)); 
}

// number of events with 4 tags
double nb4(double eb, double el, double nb0, double nb1, double nb2, double nb3, double nb4, double nb5, double nb6, double nl, double eb2)
{
    return nb2*eb*eb*el*el + nb1*eb*el*el*el + nb4*eb*eb*eb2*eb2 + nb3*eb*eb*eb2*el + nb4*eb*eb*eb2*eb2; 
         // + nb6*( TMath::Binomial(4,2)*eb*eb*eb2*eb2*(1-eb2)*(1-eb2) + 2*TMath::Binomial(4,3)*eb*eb2*eb2*eb2*(1-eb)*(1-eb2) + eb2*eb2*eb2*eb2*(1-eb)*(1-eb));
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
double eb=0.759878;
double eb2 = eb*0.07;
double el=0.053928; // estimate from fake tagging 
//double el= 0.13;

//double eb = 0.618554;
//double eb2 = eb*0.09;
//double el = 0.00525799;
//double el = 0.015;

//double eb = 0.480271;
//double eb2 = eb*0.16;
//double el = 0.0000001;
//double el = 0.00187526;


double acc = 0.99; // estimate this from MC
double frac = 0.05;
// par[0] is b-tagging efficiency
//double nball(double *x, double *par)
//{
//    if (x[0]>=0.0 && x[0]<1.0) return nb0(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2, par[2], par[3]);
//    else if (x[0]>=1.0 && x[0]<2.0) return nb1(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2, par[2], par[3]);
//    else if (x[0]>=2.0 && x[0]<3.0) return nb2(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2, par[2], par[3]);
//    else if (x[0]>=3.0 && x[0]<4.0) return nb3(par[0], par[1], 0.0, ntotal*(1-acc), ntotal*acc,2, par[2], par[3]);
//}

double nball(double *x, double *par)
{
//   if (x[0]>=0.0 && x[0]<1.0) return nb0( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*(1-par[2]), par[4]*ntotal*par[2], 2, par[3]);
//   else if (x[0]>=1.0 && x[0]<2.0) return nb1( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*(1-par[2]), par[4]*ntotal*par[2],  2, par[3]);
//   else if (x[0]>=2.0 && x[0]<3.0) return nb2( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*(1-par[2]), par[4]*ntotal*par[2],  2, par[3]);
//   else if (x[0]>=3.0 && x[0]<4.0) return nb3( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*(1-par[2]), par[4]*ntotal*par[2],  2, par[3]);

   if (x[0]>=0.0 && x[0]<1.0) return nb0( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*0.14, par[4]*ntotal*0.80, 0, par[4]*ntotal*0.03, 2, par[3]);
   else if (x[0]>=1.0 && x[0]<2.0) return nb1( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*0.14, par[4]*ntotal*0.80, 0, par[4]*ntotal*0.03, 2, par[3]);
   else if (x[0]>=2.0 && x[0]<3.0) return nb2( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*0.14, par[4]*ntotal*0.80, 0, par[4]*ntotal*0.03, 2, par[3]);
   else if (x[0]>=3.0 && x[0]<4.0) return nb3( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*0.14, par[4]*ntotal, 0, par[4]*ntotal*0.03, 2, par[3]);
   else if (x[0]>=4.0 && x[0]<5.0) return nb4( par[0], par[1], 0.0, (1-par[4])*ntotal*(1-par[2]), (1-par[4])*ntotal*par[2], par[4]*ntotal*0.14, par[4]*ntotal, 0, par[4]*ntotal*0.03, 2, par[3]);
}

double nball2(double *x, double *par)
{

//   if (x[0]>=0.0 && x[0]<1.0) return nb2tag( 0.490742*par[0], 0.540725*par[1], 0.0*par[2], par[3], ntotal*(1-par[4]), par[4]*ntotal);
//   else if (x[0]>=1.0 && x[0]<2.0) return nb2tag( 0.395901*par[0], 0.370432*par[1], 0.0*par[2], par[3], ntotal*(1-par[4]), par[4]*ntotal);
//   else if (x[0]>=2.0 && x[0]<3.0) return nb2tag( 0.263604*par[0], 0.22256*par[1], 0.0*par[2], par[3], ntotal*(1-par[4]), par[4]*ntotal);

   if (x[0]>=0.0 && x[0]<1.0) return nb2tag( 0.759878*par[0], 0.0539280*par[1], ntotal*(1-par[2]), par[3], ntotal*(1-par[4]), par[4]*ntotal*0.01,  par[4]*ntotal*0.99, 2);
   else if (x[0]>=1.0 && x[0]<2.0) return nb2tag( 0.618554*par[0], 0.00525799*par[1], ntotal*(1-par[2]), par[3], ntotal*(1-par[4]),  par[4]*ntotal*0.01, par[4]*ntotal*0.99, 2);
   else if (x[0]>=2.0 && x[0]<3.0) return nb2tag(  0.480271*par[0], 0.0*par[1], ntotal*(1-par[2]), par[3], ntotal*(1-par[4]),  par[4]*ntotal*0.01, par[4]*ntotal*0.99, 2);

}   

void extracttageffExt(int n0, int n1, int n2, int n3, int n4)
{

    // n3 information is not used in the fit
    h1=new TH1F("h1", "h1",5, 0.0, 5.0);
    h1->Fill(0, n0);
    h1->Fill(1, n1);
    h1->Fill(2, n2);
    h1->Fill(3, n3);
    h1->Fill(4, n4);

    ntotal = n0+n1+n2+n3+n4;

    double eb_initial = eb;
    double el_initial = el;
    double acc_initial = acc;
    double eb2_initial= eb2;
    double frac_initial= 0.01;

    TF1 *ftot = new TF1("ftot", nball, 0.0, 5.0, 5);
    ftot->SetParameters(eb_initial, el_initial, acc_initial, eb2_initial, frac_initial);

    //ftot->SetParLimits(0, eb, eb);
    //ftot->SetParLimits(1, el, el);
    ftot->SetParLimits(2, acc, acc);
    
    //ftot->SetParLimits(0, 1, 1);
    //ftot->SetParLimits(1, 1, 1);
    //ftot->SetParLimits(2, 0.98, 0.98);

    ftot->SetParLimits(3, 0, 1);
    //ftot->SetParLimits(4, 0.0, 1000.0);

    h1->Fit("ftot","R","same",0,5);
    h1->Draw("e");
}

void extracttageffExt(){
  cout << "L" << endl;
  extracttageffExt(7052,47093,73842,8479,689);
  cout << "M" << endl;
  extracttageffExt(19953,65087,51009,1119,45);
  cout << "T" << endl;
  extracttageffExt(37546,68532,30829,296,12);
  //cout << "2 btag" << endl;
  //extracttageffExt(73842,51009,30829,0,0);

}
