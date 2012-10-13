#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void Style(TGraphAsymmErrors* g, int c, int style){
  g->SetLineWidth(2);
  g->SetLineStyle(style);
  g->SetLineColor(c);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(c);
  g->SetMarkerSize(0.4);
  g->GetXaxis()->SetTitle("QCD efficiency");
  g->GetYaxis()->SetTitle("Signal efficiency");
}

TGraphAsymmErrors* ROC( TH1F* hSignal, TH1F* hQCD){
  TGraphAsymmErrors* out = new TGraphAsymmErrors();
  int nbins = hSignal->GetNbinsX();
  double totalS = hSignal->GetEntries();
  double totalB = hQCD->GetEntries();
  cout << "totalS = " << totalS << " totalB= " << totalB << endl;
  for(int i=0 ; i < nbins; i++){
    double Bi = hQCD->Integral(1,i+1);
    double Si = hSignal->Integral(1,i+1);
    cout << "i= " << i+1 << " Bi= " << Bi << " Si= " << Si << endl; 
    double eff_qcd = Bi / totalB;
    double eff_signal = Si/ totalS; 
    out->SetPoint(i, eff_qcd, eff_signal);
  }  
  
  return out;
}

void ElectronPFIso(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_Signal = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121012v3/vallot_TTbarTuneZ2.root");
  //TFile * f_Signal = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121012v3/vallot_ZJets.root");
  TFile * f_QCD =new TFile("../prod/Out/vallot_Run2012ElEl_nohit.root");

  TH1F *hSignal_pfRelIso04_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04");
  TH1F *hSignal_pfRelIso04_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04");
  TH1F *hSignal_pfRelIso04db_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04db");
  TH1F *hSignal_pfRelIso04db_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04db");
  TH1F *hSignal_pfRelIso04rho_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04rho");
  TH1F *hSignal_pfRelIso04rho_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04rho");

  TH1F *hSignal_pfRelIso04 = hSignal_pfRelIso04_barrel->Clone();
  TH1F *hSignal_pfRelIso04db = hSignal_pfRelIso04db_barrel->Clone();
  TH1F *hSignal_pfRelIso04rho = hSignal_pfRelIso04rho_barrel->Clone();

  hSignal_pfRelIso04->Add(hSignal_pfRelIso04_endcap);
  hSignal_pfRelIso04db->Add(hSignal_pfRelIso04db_endcap);
  hSignal_pfRelIso04rho->Add(hSignal_pfRelIso04rho_endcap);

  TH1F *hQCD_pfRelIso04_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04");
  TH1F *hQCD_pfRelIso04_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04");
  TH1F *hQCD_pfRelIso04db_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04db");
  TH1F *hQCD_pfRelIso04db_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04db");
  TH1F *hQCD_pfRelIso04rho_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04rho");
  TH1F *hQCD_pfRelIso04rho_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04rho");

  TH1F *hQCD_pfRelIso04 = hQCD_pfRelIso04_barrel->Clone();
  TH1F *hQCD_pfRelIso04db = hQCD_pfRelIso04db_barrel->Clone();
  TH1F *hQCD_pfRelIso04rho = hQCD_pfRelIso04rho_barrel->Clone();

  hQCD_pfRelIso04->Add(hQCD_pfRelIso04_endcap);
  hQCD_pfRelIso04db->Add(hQCD_pfRelIso04db_endcap);
  hQCD_pfRelIso04rho->Add(hQCD_pfRelIso04rho_endcap);

  TH1F *hSignal_pfRelIso03_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03");
  TH1F *hSignal_pfRelIso03_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03");
  TH1F *hSignal_pfRelIso03db_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03db");
  TH1F *hSignal_pfRelIso03db_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03db");
  TH1F *hSignal_pfRelIso03rho_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03rho");
  TH1F *hSignal_pfRelIso03rho_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03rho");

  TH1F *hSignal_pfRelIso03 = hSignal_pfRelIso03_barrel->Clone();
  TH1F *hSignal_pfRelIso03db = hSignal_pfRelIso03db_barrel->Clone();
  TH1F *hSignal_pfRelIso03rho = hSignal_pfRelIso03rho_barrel->Clone();

  hSignal_pfRelIso03->Add(hSignal_pfRelIso03_endcap);
  hSignal_pfRelIso03db->Add(hSignal_pfRelIso03db_endcap);
  hSignal_pfRelIso03rho->Add(hSignal_pfRelIso03rho_endcap);

  TH1F *hQCD_pfRelIso03_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03");
  TH1F *hQCD_pfRelIso03_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03");
  TH1F *hQCD_pfRelIso03db_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03db");
  TH1F *hQCD_pfRelIso03db_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03db");
  TH1F *hQCD_pfRelIso03rho_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03rho");
  TH1F *hQCD_pfRelIso03rho_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03rho");

  TH1F *hQCD_pfRelIso03 = hQCD_pfRelIso03_barrel->Clone();
  TH1F *hQCD_pfRelIso03db = hQCD_pfRelIso03db_barrel->Clone();
  TH1F *hQCD_pfRelIso03rho = hQCD_pfRelIso03rho_barrel->Clone();

  hQCD_pfRelIso03->Add(hQCD_pfRelIso03_endcap);
  hQCD_pfRelIso03db->Add(hQCD_pfRelIso03db_endcap);
  hQCD_pfRelIso03rho->Add(hQCD_pfRelIso03rho_endcap);
  
  TCanvas * c = new TCanvas("c","c",500,500);
  hSignal_pfRelIso03->SetLineColor(2);
  hQCD_pfRelIso03->SetLineColor(4);
  ROC_pfRelIso03 = ROC( hSignal_pfRelIso03, hQCD_pfRelIso03);
  ROC_pfRelIso03db = ROC( hSignal_pfRelIso03db, hQCD_pfRelIso03db);
  ROC_pfRelIso03rho = ROC( hSignal_pfRelIso03rho, hQCD_pfRelIso03rho);
  Style( ROC_pfRelIso03, 1, 1);
  Style( ROC_pfRelIso03db, 2, 1);
  Style( ROC_pfRelIso03rho, 4, 1);
  ROC_pfRelIso04 = ROC( hSignal_pfRelIso04, hQCD_pfRelIso04);
  ROC_pfRelIso04db = ROC( hSignal_pfRelIso04db, hQCD_pfRelIso04db);
  ROC_pfRelIso04rho = ROC( hSignal_pfRelIso04rho, hQCD_pfRelIso04rho);
  Style( ROC_pfRelIso04, 1, 2);
  Style( ROC_pfRelIso04db, 2, 2);
  Style( ROC_pfRelIso04rho, 4, 2);

  ROC_pfRelIso03->Draw("ALP");
  ROC_pfRelIso03db->Draw("sameLP");
  ROC_pfRelIso03rho->Draw("sameLP");

  //ROC_pfRelIso04->Draw("sameLP");
  //ROC_pfRelIso04db->Draw("sameLP");
  //ROC_pfRelIso04rho->Draw("sameLP");

  TLegend *l= new TLegend(0.6,0.4,0.9,0.6);
  l->AddEntry(ROC_pfRelIso03,"CHS only","LP");
  l->AddEntry(ROC_pfRelIso03db,"dbeta","LP");
  l->AddEntry(ROC_pfRelIso03rho,"rho","LP");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

}
