#include <map>
#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
using namespace std;

void draw_cross(){
  double mass[22] = {400, 500, 600, 700, 750, 800, 900, 1000, 1100, 1200, 1250, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2500, 3000, 4000};
  double ZXsectionW1[22]; 
  double ZXsectionW10[22];
 
  ZXsectionW1[0] = 34.9407229800567;
  ZXsectionW1[1] = 16.2208794979645;
  ZXsectionW1[2] = 8.39767273739487;
  ZXsectionW1[3] = 4.32226740967146;
  ZXsectionW1[4] = 3.16951400706147;
  ZXsectionW1[5] = 2.34033302171543;
  ZXsectionW1[6] = 1.32872871867939;
  ZXsectionW1[7] = 0.820761719054490;
  ZXsectionW1[8] = 0.510985294571310;
  ZXsectionW1[9] = 0.314670015735676;
  ZXsectionW1[10] = 0.249122386537253;
  ZXsectionW1[11] = 0.202089463533531;
  ZXsectionW1[12] = 0.129001415033279;
  ZXsectionW1[13] = 8.526785886254366E-002;
  ZXsectionW1[14] = 5.602235613859859E-002;
  ZXsectionW1[15] = 3.822469568160305E-002;
  ZXsectionW1[16] = 2.549136943431924E-002;
  ZXsectionW1[17] = 1.764021438377848E-002;
  ZXsectionW1[18] = 1.184858819322720E-002;
  ZXsectionW1[19] = 1.928157720376056E-003;
  ZXsectionW1[20] = 3.626054308973676E-004;
  ZXsectionW1[21] = 4.164114248995513E-005;

  ZXsectionW10[0] = 311.013309471323;
  ZXsectionW10[1] = 153.682299011077;
  ZXsectionW10[2] = 75.0409942491538;
  ZXsectionW10[3] = 39.0661259878917;
  ZXsectionW10[4] = 28.9004943828312;
  ZXsectionW10[5] = 21.6514366060899;
  ZXsectionW10[6] = 12.5196257716675;
  ZXsectionW10[7] = 7.53308383862020;
  ZXsectionW10[8] = 4.63308520207644;
  ZXsectionW10[9] = 2.91166614554835;
  ZXsectionW10[10] = 2.33667766234276;
  ZXsectionW10[11] = 1.87085078253264;
  ZXsectionW10[12] = 1.22305948434307;
  ZXsectionW10[13] = 0.807603584161058;
  ZXsectionW10[14] = 0.537340006786219;
  ZXsectionW10[15] = 0.362747194416033;
  ZXsectionW10[16] = 0.245936700204853;
  ZXsectionW10[17] = 0.167685463346609;
  ZXsectionW10[18] = 0.115187988289196;
  ZXsectionW10[19] = 1.834984978492599E-002;
  ZXsectionW10[20] = 3.035694870566993E-003;
  ZXsectionW10[21] = 8.113652765880886E-005;

  int Bin[5] = { 1, 4, 7, 10, 13};
  double M[5] = { 500, 750, 1000, 1250, 1500};

  //double Obs[5] = { 0.965903, 1.71487, 2.67068, 5.50933, 14.3103 }; 
  //double Exp[5] = { 0.878171, 1.64791, 2.93108, 5.95836, 12.4856 };
  //double Exp_1l[5] = { 0.497016, 0.96476, 1.70321, 4.09405, 8.25135};
  //double Exp_1h[5] = { 1.30104, 2.35354, 4.22406, 9.35285, 20.6409};
  //double Exp_2l[5] = { 0.373546, 0.66596, 1.20068, 2.57552, 5.43545};
  //double Exp_2h[5] = { 1.69199, 3.04895, 5.66721, 13.7032, 30.5465};

  double Obs[5], Exp[5], Exp_1l[5], Exp_1h[5], Exp_2l[5], Exp_2h[5];

  ifstream in_expected;
  ifstream in_observed;
  in_expected.open("bayesian_limits_expected.txt");
  in_observed.open("bayesian_limits_observed.txt");

  double obsmass, expmass, obslimit, explimit, l_one, h_one, l_two, h_two;

  //SKIP first line
  string line;
  getline(in_expected,line);
  getline(in_observed,line);

  //Reading from txt files
  for(int i=0; i<5 ;i++){
    in_observed >> obsmass >> obslimit;
    in_expected >> expmass >> explimit >> l_two >> h_two >> l_one >> h_one;
    if(obsmass != expmass) cout << "ERROR" << endl;
    Obs[i] = obslimit;
    Exp[i] = explimit;
    Exp_1l[i] = l_one;
    Exp_1h[i] = h_one;
    Exp_2l[i] = l_two;
    Exp_2h[i] = h_two;
  }

  TCanvas *canvas = new TCanvas("limit set","limit set");
  canvas->SetLogy();
  
  TGraph * ZW1 = new TGraph();
  TGraph * ZW10 = new TGraph();
  TGraph * limit_obs = new TGraph();
  TGraph * limit_exp = new TGraph();
  TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
  TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();

  for(int i=0 ; i < 14 ; i++){
    ZW1->SetPoint(i, mass[i], ZXsectionW1[i]);
    ZW10->SetPoint(i, mass[i], ZXsectionW10[i]);
  }

  for(int i=0 ; i < 5 ; i++){
    double obs = Obs[i]*ZXsectionW1[Bin[i]];

    double exp = Exp[i]*ZXsectionW1[Bin[i]];

    double exp_1h = Exp_1h[i]*ZXsectionW1[Bin[i]] - exp;
    double exp_1l = exp - Exp_1l[i]*ZXsectionW1[Bin[i]];

    double exp_2h = Exp_2h[i]*ZXsectionW1[Bin[i]] - exp;
    double exp_2l = exp - Exp_2l[i]*ZXsectionW1[Bin[i]];

    limit_obs->SetPoint(i, M[i], obs);
    limit_exp->SetPoint(i, M[i], exp);

    band_exp1->SetPoint(i, M[i], exp);
    band_exp1->SetPointEYhigh(i, exp_1h);
    band_exp1->SetPointEYlow(i, exp_1l);
    
    //cout << exp << " " << exp_1h << " " << exp_1l << " " << exp_2h << " " << exp_2l << endl;

    band_exp2->SetPoint(i, M[i], exp);
    band_exp2->SetPointEYhigh(i, exp_2h);
    band_exp2->SetPointEYlow(i, exp_2l);
  }

  ZW1->SetLineColor(4);
  ZW1->SetLineWidth(2.0);
  ZW1->SetLineStyle(9);
  ZW1->SetMaximum(300);
  ZW1->GetXaxis()->SetTitle("M_{Zprime} (GeV/c^{2})");
  ZW1->GetYaxis()->SetTitle("Cross section (pb)");

  ZW1->Draw("AL");
  //ZW10->Draw("L");
  ZW10->SetLineColor(2);
  ZW10->SetLineWidth(2.0);
  ZW10->SetLineStyle(9);

  ZW1->SetTitle("CMS Preliminary, 1.1 fb^{-1}");
  ZW1->SetTitle();

  band_exp2->SetFillColor(3);
  band_exp2->SetLineColor(0);
  //band_exp2->SetFillStyle(4000);
  band_exp2->Draw("3same");

  band_exp1->SetFillColor(5);
  band_exp1->SetLineColor(0);
  //band_exp1->SetFillStyle(4000);
  band_exp1->Draw("3same");


  limit_obs->Draw("PL");
  limit_obs->SetLineWidth(2);
  limit_obs->SetMarkerSize(1.0);
  limit_obs->SetMaximum(150.0);
  limit_obs->SetMinimum(0);
  limit_obs->SetMarkerStyle(20);
   
  limit_exp->Draw("PL");
  limit_exp->SetLineStyle(2);
  limit_exp->SetLineWidth(2);
  limit_exp->SetMarkerSize(1.0);
  limit_exp->SetMaximum(150.0);
  limit_exp->SetMinimum(0);
  limit_exp->SetMarkerStyle(20);

  ZW1->Draw("L");

  //Legend
  TLegend *l = new TLegend(0.65,0.63,0.90,0.88);
  l->AddEntry(ZW1,"Zprime","L");
  l->AddEntry(limit_obs,"Observed", "PL");
  l->AddEntry(limit_exp,"Expected", "PL");
  l->AddEntry(band_exp1,"#pm1 #sigma band", "F");
  l->AddEntry(band_exp2,"#pm2 #sigma band", "F");
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  canvas->Print("zprime_limit_mumu.eps");

}
