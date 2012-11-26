#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void SetLabel(const TString & region){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.55,0.6,"t#bar{t} signal in 53X");
  //label->DrawLatex(0.55,0.6-0.05,Form("%s at #sqrt{s} = 8 TeV",region.Data()));
  label->DrawLatex(0.55,0.6-0.05,Form("%s",region.Data()));
  label->Draw();
}

void Style(TGraphAsymmErrors* g, int c, int style){
  g->SetLineWidth(2);
  g->SetLineStyle(style);
  g->SetLineColor(c);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(c);
  g->SetMarkerSize(0.4);
  g->SetFillColor(c);
  g->SetFillStyle(3001);
  g->GetXaxis()->SetTitle("QCD efficiency");
  g->GetYaxis()->SetTitle("Signal efficiency");
}

TGraphAsymmErrors* ROC( TH1* hSignal, TH1* hQCD){
  TGraphAsymmErrors* out = new TGraphAsymmErrors();
  int nbins = hSignal->GetNbinsX();
  double totalS = hSignal->GetEntries();
  double totalB = hQCD->GetEntries();
  cout << hSignal->GetTitle() << endl;
  cout << "totalS = " << totalS << " totalB= " << totalB << endl;
  for(int i=0 ; i < 40; i++){
    double Bi = hQCD->Integral(1,i+1);
    double Si = hSignal->Integral(1,i+1);
    double eff_qcd = Bi / totalB;
    double eff_signal = Si/ totalS; 
    double err_qcd = sqrt(Bi) / totalB;
    //double purity = 0.9;
    //double eff_qcd_real = ( eff_qcd - eff_signal * ( 1- purity) ) / purity; 
    double soverb = Si/Bi;
    cout << "i= " << 0.01*(i+1) << " signal eff = " << eff_signal << " background eff = " << eff_qcd << " s/s+b= " << soverb << endl ;
    out->SetPoint(i, eff_qcd, eff_signal);
    out->SetPointEXhigh(i,err_qcd);
    out->SetPointEXlow(i, err_qcd);
  }   
  return out;
}

void ElectronPFIso(bool merge=true, const int area=0){
  const int n =3;
  //if merge is true, area should be 0. The area is where to look among n

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_Signal = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/njet1_update/vallot_TTbarTuneZ2.root");
  TFile * f_QCD =new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/njet1_update/vallot_Run2012ElEl.root");

  TH2F * h2Signal_pfRelIso03[n];
  TH2F * h2Signal_pfRelIso03db[n];
  TH2F * h2Signal_pfRelIso03rho[n];

  TH2F * h2QCD_pfRelIso03[n];
  TH2F * h2QCD_pfRelIso03db[n];
  TH2F * h2QCD_pfRelIso03rho[n];

  for(int i=0; i < n; i++){
    TString region = "";
    if( i== 0) region = "Endcap";
    if( i== 1) region = "Barrel1";
    if( i== 2) region = "Barrel2";

    h2Signal_pfRelIso03[i] = (TH2F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h2_pfRelIso03",region.Data()));
    h2Signal_pfRelIso03db[i] = (TH2F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h2_pfRelIso03db",region.Data()));
    h2Signal_pfRelIso03rho[i] = (TH2F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h2_pfRelIso03rho",region.Data()));

    h2QCD_pfRelIso03[i] = (TH2F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h2_pfRelIso03",region.Data()));
    h2QCD_pfRelIso03db[i] = (TH2F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h2_pfRelIso03db",region.Data()));
    h2QCD_pfRelIso03rho[i] = (TH2F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h2_pfRelIso03rho",region.Data()));
  }

  /////merge three regions
  if(merge){
    for(int i=1; i < n; i++){
      h2Signal_pfRelIso03[0]->Add(h2Signal_pfRelIso03[i]);
      h2Signal_pfRelIso03db[0]->Add(h2Signal_pfRelIso03db[i]);
      h2Signal_pfRelIso03rho[0]->Add(h2Signal_pfRelIso03rho[i]);
   
      h2QCD_pfRelIso03[0]->Add(h2QCD_pfRelIso03[i]);
      h2QCD_pfRelIso03db[0]->Add(h2QCD_pfRelIso03db[i]);
      h2QCD_pfRelIso03rho[0]->Add(h2QCD_pfRelIso03rho[i]);
    }
  }
  ////////

  int npu = 15;

  TH1D* hSignal_pfRelIso03_lowPU = h2Signal_pfRelIso03[area]->ProjectionY("hSignal_pfRelIso03_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03db_lowPU = h2Signal_pfRelIso03db[area]->ProjectionY("hSignal_pfRelIso03db_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03rho_lowPU = h2Signal_pfRelIso03rho[area]->ProjectionY("hSignal_pfRelIso03rho_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03_highPU = h2Signal_pfRelIso03[area]->ProjectionY("hSignal_pfRelIso03_highPU",npu,50);
  TH1D* hSignal_pfRelIso03db_highPU = h2Signal_pfRelIso03db[area]->ProjectionY("hSignal_pfRelIso03db_highPU",npu,50);
  TH1D* hSignal_pfRelIso03rho_highPU = h2Signal_pfRelIso03rho[area]->ProjectionY("hSignal_pfRelIso03rho_highPU",npu,50);

  TH1D* hQCD_pfRelIso03_lowPU = h2QCD_pfRelIso03[area]->ProjectionY("hQCD_pfRelIso03_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03db_lowPU = h2QCD_pfRelIso03db[area]->ProjectionY("hQCD_pfRelIso03db_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03rho_lowPU = h2QCD_pfRelIso03rho[area]->ProjectionY("hQCD_pfRelIso03rho_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03_highPU = h2QCD_pfRelIso03[area]->ProjectionY("hQCD_pfRelIso03_highPU",npu,50);
  TH1D* hQCD_pfRelIso03db_highPU = h2QCD_pfRelIso03db[area]->ProjectionY("hQCD_pfRelIso03db_highPU",npu,50);
  TH1D* hQCD_pfRelIso03rho_highPU = h2QCD_pfRelIso03rho[area]->ProjectionY("hQCD_pfRelIso03rho_highPU",npu,50);

  ///////1d plots//////

  TH1F *hSignal_pfRelIso[3][n];
  TH1F *hSignal_pfRelIsodb[3][n];
  TH1F *hSignal_pfRelIsorho[3][n];

  TH1F *hQCD_pfRelIso[3][n];
  TH1F *hQCD_pfRelIsodb[3][n];
  TH1F *hQCD_pfRelIsorho[3][n];

  for(int r=0; r < 2; r++){
    TString dR = "";
    if( r == 0 ) dR = "03";
    if( r == 1 ) dR = "04";
    for(int i=0; i < n; i++){
      TString region = "";
      if( i== 0) region = "Endcap";
      if( i== 1) region = "Barrel1";
      if( i== 2) region = "Barrel2";
      hSignal_pfRelIso[r][i] = (TH1F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h_pfRelIso%s",region.Data(),dR.Data()));
      hSignal_pfRelIsodb[r][i] = (TH1F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h_pfRelIso%sdb",region.Data(),dR.Data()));
      hSignal_pfRelIsorho[r][i] = (TH1F *) f_Signal->Get(Form("ElectronAnalysis/Signal/IDPF/%s/h_pfRelIso%srho",region.Data(),dR.Data()));

      hQCD_pfRelIso[r][i] = (TH1F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h_pfRelIso%s",region.Data(),dR.Data()));
      hQCD_pfRelIsodb[r][i] = (TH1F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h_pfRelIso%sdb",region.Data(),dR.Data()));
      hQCD_pfRelIsorho[r][i] = (TH1F *) f_QCD->Get(Form("ElectronAnalysis/QCD/IDPF/%s/h_pfRelIso%srho",region.Data(),dR.Data()));

    }

  }

  if(merge){
    for(int r=0; r < 2; r++){
      for( int i =1; i < n ;i++){
        hSignal_pfRelIso[r][0]->Add(hSignal_pfRelIso[r][i]);
        hSignal_pfRelIsodb[r][0]->Add(hSignal_pfRelIsodb[r][i]);
        hSignal_pfRelIsorho[r][0]->Add(hSignal_pfRelIsorho[r][i]);

        hQCD_pfRelIso[r][0]->Add(hQCD_pfRelIso[r][i]);
        hQCD_pfRelIsodb[r][0]->Add(hQCD_pfRelIsodb[r][i]);
        hQCD_pfRelIsorho[r][0]->Add(hQCD_pfRelIsorho[r][i]);
      } 
    }
  }

  ROC_pfRelIso03 = ROC( hSignal_pfRelIso[0][area], hQCD_pfRelIso[0][area]);
  ROC_pfRelIso03db = ROC( hSignal_pfRelIsodb[0][area], hQCD_pfRelIsodb[0][area]);
  ROC_pfRelIso03rho = ROC( hSignal_pfRelIsorho[0][area], hQCD_pfRelIsorho[0][area]);

  ROC_pfRelIso04 = ROC( hSignal_pfRelIso[1][area], hQCD_pfRelIso[1][area]);
  ROC_pfRelIso04db = ROC( hSignal_pfRelIsodb[1][area], hQCD_pfRelIsodb[1][area]);
  ROC_pfRelIso04rho = ROC( hSignal_pfRelIsorho[1][area], hQCD_pfRelIsorho[1][area]);

  ROC_pfRelIso03_lowPU = ROC( hSignal_pfRelIso03_lowPU, hQCD_pfRelIso03_lowPU);
  ROC_pfRelIso03db_lowPU = ROC( hSignal_pfRelIso03db_lowPU, hQCD_pfRelIso03db_lowPU);
  ROC_pfRelIso03rho_lowPU = ROC( hSignal_pfRelIso03rho_lowPU, hQCD_pfRelIso03rho_lowPU);

  ROC_pfRelIso03_highPU = ROC( hSignal_pfRelIso03_highPU, hQCD_pfRelIso03_highPU);
  ROC_pfRelIso03db_highPU = ROC( hSignal_pfRelIso03db_highPU, hQCD_pfRelIso03db_highPU);
  ROC_pfRelIso03rho_highPU = ROC( hSignal_pfRelIso03rho_highPU, hQCD_pfRelIso03rho_highPU);

  TCanvas * c_dR = new TCanvas("c_dR","c_dR",500,500);
  Style( ROC_pfRelIso03db, 2, 1);
  Style( ROC_pfRelIso04db, 4, 1);
  ROC_pfRelIso03db->Draw("ALP");
  ROC_pfRelIso04db->Draw("sameLP");
  SetLabel("");

  TLegend *l= new TLegend(0.6,0.3,0.9,0.5);
  l->AddEntry(ROC_pfRelIso03db,"dR = 0.3","LP");
  l->AddEntry(ROC_pfRelIso04db,"dR = 0.4","LP");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c_dR->Print("c_iso_dR.eps");

  TCanvas * c = new TCanvas("c","c",500,500);
  Style( ROC_pfRelIso03, 1, 1);
  Style( ROC_pfRelIso03db, 2, 1);
  Style( ROC_pfRelIso03rho, 4, 1);
  ROC_pfRelIso03->Draw("ALP");
  ROC_pfRelIso03db->Draw("sameLP");
  ROC_pfRelIso03rho->Draw("sameLP");

  TLegend *l= new TLegend(0.6,0.3,0.9,0.5);
  l->AddEntry(ROC_pfRelIso03,"CHS only","LP");
  l->AddEntry(ROC_pfRelIso03db,"+dbeta","LP");
  l->AddEntry(ROC_pfRelIso03rho,"+rho","LP");
  SetLabel("");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print("c_iso_corrtype.eps");

  TCanvas * c_lowPU = new TCanvas("c_lowPU","c_lowPU",500,500);
  Style( ROC_pfRelIso03_lowPU, 1, 1);
  Style( ROC_pfRelIso03db_lowPU, 2, 1);
  Style( ROC_pfRelIso03rho_lowPU, 4, 1);
  ROC_pfRelIso03_lowPU->Draw("ALP");
  ROC_pfRelIso03db_lowPU->Draw("sameLP");
  ROC_pfRelIso03rho_lowPU->Draw("sameLP");
  SetLabel("PU < 15");
  l->Draw();

  TCanvas * c_highPU = new TCanvas("c_highPU","c_highPU",500,500);
  Style( ROC_pfRelIso03_highPU, 1, 1);
  Style( ROC_pfRelIso03db_highPU, 2, 1);
  Style( ROC_pfRelIso03rho_highPU, 4, 1);
  ROC_pfRelIso03_highPU->Draw("ALP");
  ROC_pfRelIso03db_highPU->Draw("sameLP");
  ROC_pfRelIso03rho_highPU->Draw("sameLP");
  SetLabel("PU #geq 15");
  l->Draw();

}
