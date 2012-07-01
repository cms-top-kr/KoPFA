#include "TH2F.h"
#include "TMath.h"
#include "TRandom3.h"
#include "THStack.h"

int initbtag  = 0;
double fraction = 0.01;

const int nbins = 5;

double nttbb[nbins*3];
double nttcc[nbins*3];
double nttll[nbins*3];

double N_ttjj = 0;

double nbtag(double *x, double *par)
{
    int ntag = x[0];

    return  par[1]*N_ttjj*(par[0]*nttbb[ntag] + (1-par[0])*nttll[ntag]);
    //return  par[2]*N_ttjj*(par[0]*nttbb[ntag] + par[1]*nttcc[ntag] + (1-par[0]-par[1])*nttll[ntag]);

}

void Fit(TH1* data, TH1* ttbb, TH1* ttcc, TH1* ttll, const TString & decayMode)
{
    double kfract_initial = fraction;
    double kttjj_initial = 1.0;

    ttll->Add(ttcc);

    TH1* hdata = (TH1*) data->Clone();
    TH1* httbb = (TH1*) ttbb->Clone();
    TH1* httcc = (TH1*) ttcc->Clone();
    TH1* httll = (TH1*) ttll->Clone();

    double N_data = hdata->Integral();
    double N_ttbb = httbb->Integral();
    double N_ttcc = httcc->Integral();
    double N_ttll = httll->Integral();

    N_ttjj = N_ttbb + N_ttll;
    //N_ttjj = N_ttbb + N_ttcc + N_ttll;
    double r = N_ttbb / N_ttjj;

    cout << "Total number of background subtracted data= " << N_data << " Total number of tt signal= " << N_ttjj << endl;

    httbb->Sumw2();
    httcc->Sumw2();
    httll->Sumw2();
    httll->Scale(1.0/N_ttll);
    httbb->Scale(1.0/N_ttbb);
    httcc->Scale(1.0/N_ttcc);

    int n = data->GetXaxis()->GetNbins();

    for(int i = 0 ; i < n; i++){
      nttbb[i] = httbb->GetBinContent(i+1);
      nttcc[i] = httcc->GetBinContent(i+1);
      nttll[i] = httll->GetBinContent(i+1);
    }

    TCanvas * c= new TCanvas(Form("c%s",decayMode.Data()),"c",1);
    c->SetLogy();
    TF1 *ftot = new TF1("ftot", nbtag , 0, n, 2);
    ftot->SetParameter(0, r);
    //ftot->SetParameter(1, kfract_initial);
    ftot->SetParameter(1, kttjj_initial);
    ftot->SetParLimits(0, 0.0, 1.0 );
    //ftot->SetParLimits(1, 0.0, 1.0 );
    ftot->SetParLimits(1, kttjj_initial*0.5, kttjj_initial*1.5 );
    hdata->Fit("ftot","RN","",0,n);

    double R = ftot->GetParameter(0);
    //double Rcc = ftot->GetParameter(1);
    double k = ftot->GetParameter(1);
    httbb->Scale( k*N_ttjj*R );
    //httcc->Scale( k*N_ttjj*Rcc );
    //httll->Scale( k*N_ttjj*(1 - R - Rcc) );
    httll->Scale( k*N_ttjj*(1 - R) );

    httbb->SetFillColor(kRed+2);
    //httcc->SetFillColor(kRed+1);
    httll->SetFillColor(kRed);

    //httcc->SetFillStyle(1001);
    httbb->SetFillStyle(1001);
    httll->SetFillStyle(1001);

    THStack * s = new THStack("tt","tt");
    s->Add(httbb);
    //s->Add(httcc);
    s->Add(httll);
    s->Draw("FHIST");
    s->GetYaxis()->SetTitle("Events");
    s->GetXaxis()->SetTitle("b-Jet Multiplicity (CSVM)");
    s->SetTitle("Fit Result");
    s->SetMaximum(4000);

    hdata->SetMarkerSize(1);
    hdata->SetMarkerStyle(20);
    hdata->Draw("samee");
    hdata->SetTitle(Form("%s",decayMode.Data()));

    TLegend *l = new TLegend(0.75,0.68,0.92,0.88);
    l->AddEntry(hdata,"Data","L");
    l->AddEntry(httll,"t#bar{t} + ll","F");
    //l->AddEntry(httcc,"t#bar{t} + cc","F");
    l->AddEntry(httbb,"t#bar{t} + bb","F");
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();

    c->Print(Form("c_ttbb_fraction_%s.eps",decayMode.Data()));
}

void extractR(){

  TFile * f_MuMu = new TFile("result30JunNoTop2/MuMu/MuMu.root");
  TFile * f_MuEl = new TFile("result30JunNoTop2/MuEl/MuEl.root");
  TFile * f_ElEl = new TFile("result30JunNoTop2/ElEl/ElEl.root");

  TH1F * h_ttbb_CSVM_MuMu = (TH1F*) f_MuMu->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVM");
  TH1F * h_ttcc_CSVM_MuMu = (TH1F*) f_MuMu->Get("Step_6/hMC_TTbarcc_Step_6_nbJet_CSVM");
  TH1F * h_ttll_CSVM_MuMu = (TH1F*) f_MuMu->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVM");
  TH1F * h_data_CSVM_MuMu = (TH1F*) f_MuMu->Get("Step_6/hDataSub_Step_6_nbJet_CSVM");
  h_data_CSVM_MuMu->Add(h_ttll_CSVM_MuMu);
  h_data_CSVM_MuMu->Add(h_ttcc_CSVM_MuMu);

  TH1F * h_ttbb_CSVM_MuEl = (TH1F*) f_MuEl->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVM");
  TH1F * h_ttcc_CSVM_MuEl = (TH1F*) f_MuEl->Get("Step_6/hMC_TTbarcc_Step_6_nbJet_CSVM");
  TH1F * h_ttll_CSVM_MuEl = (TH1F*) f_MuEl->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVM");
  TH1F * h_data_CSVM_MuEl = (TH1F*) f_MuEl->Get("Step_6/hDataSub_Step_6_nbJet_CSVM");
  h_data_CSVM_MuEl->Add(h_ttll_CSVM_MuEl);
  h_data_CSVM_MuEl->Add(h_ttcc_CSVM_MuEl);
 
  TH1F * h_ttbb_CSVM_ElEl = (TH1F*) f_ElEl->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVM");
  TH1F * h_ttcc_CSVM_ElEl = (TH1F*) f_ElEl->Get("Step_6/hMC_TTbarcc_Step_6_nbJet_CSVM");
  TH1F * h_ttll_CSVM_ElEl = (TH1F*) f_ElEl->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVM");
  TH1F * h_data_CSVM_ElEl = (TH1F*) f_ElEl->Get("Step_6/hDataSub_Step_6_nbJet_CSVM");
  h_data_CSVM_ElEl->Add(h_ttll_CSVM_ElEl);
  h_data_CSVM_ElEl->Add(h_ttcc_CSVM_ElEl);


  TH1F * hFit_data_CSVM_MuMu = new TH1F("hFit_data_CSVM_MuMu","hFit_data_CSVM_MuMu",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttll_CSVM_MuMu = new TH1F("hFit_ttll_CSVM_MuMu","hFit_ttll_CSVM_MuMu",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttbb_CSVM_MuMu = new TH1F("hFit_ttbb_CSVM_MuMu","hFit_ttbb_CSVM_MuMu",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttcc_CSVM_MuMu = new TH1F("hFit_ttcc_CSVM_MuMu","hFit_ttcc_CSVM_MuMu",nbins,-0.5,nbins - 0.5);

  TH1F * hFit_data_CSVM_MuEl = new TH1F("hFit_data_CSVM_MuEl","hFit_data_CSVM_MuEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttll_CSVM_MuEl = new TH1F("hFit_ttll_CSVM_MuEl","hFit_ttll_CSVM_MuEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttbb_CSVM_MuEl = new TH1F("hFit_ttbb_CSVM_MuEl","hFit_ttbb_CSVM_MuEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttcc_CSVM_MuEl = new TH1F("hFit_ttcc_CSVM_MuEl","hFit_ttcc_CSVM_MuEl",nbins,-0.5,nbins - 0.5);

  TH1F * hFit_data_CSVM_ElEl = new TH1F("hFit_data_CSVM_ElEl","hFit_data_CSVM_ElEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttll_CSVM_ElEl = new TH1F("hFit_ttll_CSVM_ElEl","hFit_ttll_CSVM_ElEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttbb_CSVM_ElEl = new TH1F("hFit_ttbb_CSVM_ElEl","hFit_ttbb_CSVM_ElEl",nbins,-0.5,nbins - 0.5);
  TH1F * hFit_ttcc_CSVM_ElEl = new TH1F("hFit_ttcc_CSVM_ElEl","hFit_ttcc_CSVM_ElEl",nbins,-0.5,nbins - 0.5);

  TH1F * hFit_data_CSVM_all = new TH1F("hFit_data_CSVM_all","hFit_data_CSVM_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * hFit_ttll_CSVM_all = new TH1F("hFit_ttll_CSVM_all","hFit_ttll_CSVM_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * hFit_ttbb_CSVM_all = new TH1F("hFit_ttbb_CSVM_all","hFit_ttbb_CSVM_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * hFit_ttcc_CSVM_all = new TH1F("hFit_ttcc_CSVM_all","hFit_ttcc_CSVM_all",nbins*3,-0.5,nbins*3 - 0.5);

  for(int i=1 ; i <= nbins; i++){
    double data_CSVM_MuMu = 0;
    double ttll_CSVM_MuMu = 0;
    double ttbb_CSVM_MuMu = 0;
    double ttcc_CSVM_MuMu = 0;

    double data_CSVM_MuEl = 0;
    double ttll_CSVM_MuEl = 0;
    double ttbb_CSVM_MuEl = 0;
    double ttcc_CSVM_MuEl = 0;

    double data_CSVM_ElEl = 0;
    double ttll_CSVM_ElEl = 0;
    double ttbb_CSVM_ElEl = 0;
    double ttcc_CSVM_ElEl = 0;


    if( i > initbtag ) {
      data_CSVM_MuMu = h_data_CSVM_MuMu->GetBinContent(i);
      ttll_CSVM_MuMu = h_ttll_CSVM_MuMu->GetBinContent(i);
      ttbb_CSVM_MuMu = h_ttbb_CSVM_MuMu->GetBinContent(i);
      ttcc_CSVM_MuMu = h_ttcc_CSVM_MuMu->GetBinContent(i);

      data_CSVM_MuEl = h_data_CSVM_MuEl->GetBinContent(i);
      ttll_CSVM_MuEl = h_ttll_CSVM_MuEl->GetBinContent(i);
      ttbb_CSVM_MuEl = h_ttbb_CSVM_MuEl->GetBinContent(i);
      ttcc_CSVM_MuEl = h_ttcc_CSVM_MuEl->GetBinContent(i);

      data_CSVM_ElEl = h_data_CSVM_ElEl->GetBinContent(i);
      ttll_CSVM_ElEl = h_ttll_CSVM_ElEl->GetBinContent(i);
      ttbb_CSVM_ElEl = h_ttbb_CSVM_ElEl->GetBinContent(i);
      ttcc_CSVM_ElEl = h_ttcc_CSVM_ElEl->GetBinContent(i);
    }

    hFit_data_CSVM_MuMu->SetBinContent(i, data_CSVM_MuMu );
    hFit_ttll_CSVM_MuMu->SetBinContent(i, ttll_CSVM_MuMu );
    hFit_ttbb_CSVM_MuMu->SetBinContent(i, ttbb_CSVM_MuMu );
    hFit_ttcc_CSVM_MuMu->SetBinContent(i, ttcc_CSVM_MuMu );

    hFit_data_CSVM_MuEl->SetBinContent(i, data_CSVM_MuEl );
    hFit_ttll_CSVM_MuEl->SetBinContent(i, ttll_CSVM_MuEl );
    hFit_ttbb_CSVM_MuEl->SetBinContent(i, ttbb_CSVM_MuEl );
    hFit_ttcc_CSVM_MuEl->SetBinContent(i, ttcc_CSVM_MuEl );

    hFit_data_CSVM_ElEl->SetBinContent(i, data_CSVM_ElEl );
    hFit_ttll_CSVM_ElEl->SetBinContent(i, ttll_CSVM_ElEl );
    hFit_ttbb_CSVM_ElEl->SetBinContent(i, ttbb_CSVM_ElEl );
    hFit_ttcc_CSVM_ElEl->SetBinContent(i, ttcc_CSVM_ElEl );

  }


  for(int i=1 ; i <= nbins*3; i++){
    double nd = 0;
    double nl = 0;
    double nb = 0;
    double nc = 0;
    int tag = 0;
    if( i >= 1 && i <= nbins ){
      nd = hFit_data_CSVM_MuMu->GetBinContent(i);
      nl = hFit_ttll_CSVM_MuMu->GetBinContent(i);
      nb = hFit_ttbb_CSVM_MuMu->GetBinContent(i);
      nc = hFit_ttcc_CSVM_MuMu->GetBinContent(i);
      tag = i - 1  ;
    }else if( i > nbins && i<= nbins*2){
      nd = hFit_data_CSVM_MuEl->GetBinContent(i-nbins);
      nl = hFit_ttll_CSVM_MuEl->GetBinContent(i-nbins);
      nb = hFit_ttbb_CSVM_MuEl->GetBinContent(i-nbins);
      nc = hFit_ttcc_CSVM_MuEl->GetBinContent(i-nbins);
      tag = i - (1 + nbins) ;
    }else if( i > nbins*2){
      nd = hFit_data_CSVM_ElEl->GetBinContent(i-nbins*2);
      nl = hFit_ttll_CSVM_ElEl->GetBinContent(i-nbins*2);
      nb = hFit_ttbb_CSVM_ElEl->GetBinContent(i-nbins*2);
      nc = hFit_ttcc_CSVM_ElEl->GetBinContent(i-nbins*2);
      tag = i - (1 + nbins*2) ;
    } 
    cout << "i= " << i << " nd= " << nd << " nl= " << nl << " nb= " << nb << endl;
    hFit_data_CSVM_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    hFit_ttll_CSVM_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    hFit_ttbb_CSVM_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    hFit_ttcc_CSVM_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    hFit_data_CSVM_all->SetBinContent(i,nd);
    hFit_ttll_CSVM_all->SetBinContent(i,nl);
    hFit_ttbb_CSVM_all->SetBinContent(i,nb);
    hFit_ttcc_CSVM_all->SetBinContent(i,nc);
  }

  Fit( hFit_data_CSVM_all, hFit_ttbb_CSVM_all, hFit_ttcc_CSVM_all,  hFit_ttll_CSVM_all, "Combined");
  Fit( hFit_data_CSVM_MuMu, hFit_ttbb_CSVM_MuMu, hFit_ttcc_CSVM_MuMu, hFit_ttll_CSVM_MuMu, "MuMu");
  Fit( hFit_data_CSVM_MuEl, hFit_ttbb_CSVM_MuEl, hFit_ttcc_CSVM_MuEl, hFit_ttll_CSVM_MuEl, "MuEl");
  Fit( hFit_data_CSVM_ElEl, hFit_ttbb_CSVM_ElEl, hFit_ttcc_CSVM_ElEl, hFit_ttll_CSVM_ElEl, "ElEl");
 
}
