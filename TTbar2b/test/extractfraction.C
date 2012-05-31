#include "TH2F.h"
#include "TMath.h"
#include "TRandom3.h"

double nttll[18];
double nttbb[18];

double r = 1;

double nbtag(double *x, double *par)
{
    int ntag = x[0];

    return (1-par[0])/(1-r)*nttll[ntag] + par[0]/r*nttbb[ntag];

}

void extractfraction(TH1* hdata, TH1* httbb, TH1* httll, const TString & decayMode)
{
    double kfract_initial = r;

    for(int i = 0 ; i < 18 ; i++){
      nttbb[i] = httbb->GetBinContent(i+1);
      nttll[i] = httll->GetBinContent(i+1);
    }

    TCanvas * c= new TCanvas("c","c",1);
    TF1 *ftot = new TF1("ftot", nbtag, 0,18, 1);
    //ftot->SetParameters(kfract_initial);
    //ftot->SetParLimits(0, 0, kfraction_initial + 0.1 );
    hdata->SetMaximum(1.0);
    hdata->Fit("ftot","LW","",0,18);
    hdata->Draw();
    TString decayMode = 
    c->Print(Form("c_ttbb_fraction_%s.eps",decayMode.Data()));
}

void extractfraction(const TString & decayMode = "MuEl"){

  TFile * f = new TFile(Form("%s_ttbb_v7/%s.root", decayMode.Data(), decayMode.Data()));

  TH1F * h_ttbb_CSVL = (TH1F*) f->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVL");
  TH1F * h_ttll_CSVL = (TH1F*) f->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVL");
  TH1F * h_data_CSVL = (TH1F*) f->Get("Step_6/hDataSub_Step_6_nbJet_CSVL");
  h_data_CSVL->Add(h_ttll_CSVL);

  TH1F * h_ttbb_CSVM = (TH1F*) f->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVM");
  TH1F * h_ttll_CSVM = (TH1F*) f->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVM");
  TH1F * h_data_CSVM = (TH1F*) f->Get("Step_6/hDataSub_Step_6_nbJet_CSVM");
  h_data_CSVM->Add(h_ttll_CSVM);

  TH1F * h_ttbb_CSVT = (TH1F*) f->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVT");
  TH1F * h_ttll_CSVT = (TH1F*) f->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVT");
  TH1F * h_data_CSVT = (TH1F*) f->Get("Step_6/hDataSub_Step_6_nbJet_CSVT");
  h_data_CSVT->Add(h_ttll_CSVT);

  TH1F * h_data_all = new TH1F("h_data_all","h_data_all",18,0,18);
  TH1F * h_ttll_all = new TH1F("h_ttll_all","h_ttll_all",18,0,18);
  TH1F * h_ttbb_all = new TH1F("h_ttbb_all","h_ttbb_all",18,0,18);

  double N_data = h_data_CSVL->Integral();
  double N_ttbb = h_ttbb_CSVL->Integral();
  double N_ttll = h_ttll_CSVL->Integral();
  double N_tt = N_ttbb + N_ttll;

  cout << "Total number of background subtracted data= " << N_data << " Total number of tt signal= " << N_tt << endl;

  for(int i=1 ; i <= 18; i++){
    double nd = 0;
    double nl = 0;
    double nb = 0;
    double nde = 0;
    double nle = 0;
    double nbe = 0;
    if( i >= 1 && i <=6 ){
      double abnd = h_data_CSVL->GetBinContent(i);
      double abnl = h_ttll_CSVL->GetBinContent(i);
      double abnb = h_ttbb_CSVL->GetBinContent(i);
      nd = abnd;
      nl = abnl;
      nb = abnb;
      nde = sqrt(abnd)/N_data;
      nle = sqrt(abnl)/N_tt;
      nbe = sqrt(abnb)/N_tt;
      cout << i << " : " << nd << " +- " << nde << "  " << sqrt(nd) << endl;
    }else if( i >=7 && i<= 12){
      double abnd = h_data_CSVM->GetBinContent(i-6);
      double abnl = h_ttll_CSVM->GetBinContent(i-6);
      double abnb = h_ttbb_CSVM->GetBinContent(i-6);
      nd = abnd;
      nl = abnl;
      nb = abnb;
      nde = sqrt(abnd)/N_data;
      nle = sqrt(abnl)/N_tt;
      nbe = sqrt(abnb)/N_tt;
      cout << i << " : " << nd << " +- " << nde <<  " " << sqrt(nd) << endl;
    }else{
      double abnd = h_data_CSVT->GetBinContent(i-12);
      double abnl = h_ttll_CSVT->GetBinContent(i-12);
      double abnb = h_ttbb_CSVT->GetBinContent(i-12);
      nd = abnd;
      nl = abnl;
      nb = abnb;
      nde = sqrt(abnd)/N_data;
      nle = sqrt(abnl)/N_tt;
      nbe = sqrt(abnb)/N_tt;
      cout << i << " : " << nd << " +- " << nde << sqrt(nd) << endl;
    } 
    h_data_all->SetBinContent(i,nd);
    h_ttll_all->SetBinContent(i,nl);
    h_ttbb_all->SetBinContent(i,nb);
  }

  h_data_all->Sumw2();
  h_ttbb_all->Sumw2();
  h_ttll_all->Sumw2();
 
  h_data_all->Scale(1.0/N_data);
  h_ttll_all->Scale(1.0/N_tt);
  h_ttbb_all->Scale(1.0/N_tt);

  r = N_ttbb / N_tt; 

  cout << "R= " << r << endl;

  h_data_all->SetTitle(Form("%s",decayMode.Data()));

  extractfraction( h_data_all, h_ttbb_all, h_ttll_all, decayMode);
 
}
