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
  label->DrawLatex(0.2,0.8,"t#bar{t} simulation in 53X");
  label->DrawLatex(0.2,0.8-0.05,Form("%s, at #sqrt{s} = 8 TeV",region.Data()));
  label->Draw();
}

void SetFrame( TH1F * h, const TString & title, double max = 1.02, double min = 0.96){
  h->Reset();
  h->SetTitle("");
  h->GetXaxis()->SetTitle(Form("%s",title.Data()));
  h->GetYaxis()->SetTitle("PF ID Efficiency");
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->SetMinimum(min);
  h->SetMaximum(max);
  h->Draw();
}

void plotNJET(TFile *f, const TString & variable){

  TCanvas *c = new TCanvas(Form("c_%s",variable.Data()),Form("c_%s",variable.Data()),500,500);

  TH1F *h_den_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Barrel/h_%s", variable.Data()));
  TH1F *h_num_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Barrel/h_%s", variable.Data()));
  TH1F *h_den_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Endcap/h_%s", variable.Data()));
  TH1F *h_num_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Endcap/h_%s", variable.Data()));

  TH1F *h_num = h_num_barrel->Clone();
  TH1F *h_den = h_den_barrel->Clone();
  h_num->Add(h_num_endcap);
  h_den->Add(h_den_endcap);

  TH1F *h = h_den->Clone();
  SetFrame( h , "Jet multiplicity", 1.02, 0.98);
  SetLabel( "All" );

  TGraphAsymmErrors *g = new TGraphAsymmErrors();
  g->BayesDivide(h_num,h_den);
  g->SetMarkerSize(0.5);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(4);
  g->Draw("PZsame");
  c->Print(Form("PFID_%s.eps",variable.Data()));

}


void plotETA(TFile *f, const TString & variable){

  TCanvas *c = new TCanvas(Form("c_%s",variable.Data()),Form("c_%s",variable.Data()),500,500);

  TH1F *h_den_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Barrel/h_%s", variable.Data()));
  TH1F *h_num_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Barrel/h_%s", variable.Data()));
  TH1F *h_den_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Endcap/h_%s", variable.Data()));
  TH1F *h_num_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Endcap/h_%s", variable.Data()));

  TH1F *h_num = h_num_barrel->Clone();
  TH1F *h_den = h_den_barrel->Clone();
  h_num->Add(h_num_endcap);
  h_den->Add(h_den_endcap);

  TH1F *h = h_den->Clone();
  SetFrame( h , "Electron #eta");
  SetLabel( "All" );

  TGraphAsymmErrors *g = new TGraphAsymmErrors();
  g->BayesDivide(h_num,h_den);
  g->SetMarkerSize(0.5);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(4);
  g->Draw("PZsame");
  c->Print(Form("PFID_%s.eps",variable.Data()));

}

void plot(TFile *f, const TString & variable, const TString & xtitle){

  TH1F *h_den_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Barrel/h_%s", variable.Data()));
  TH1F *h_num_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Barrel/h_%s", variable.Data()));
  TH1F *h_den_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Endcap/h_%s", variable.Data()));
  TH1F *h_num_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Endcap/h_%s", variable.Data()));

  TCanvas *c_barrel = new TCanvas(Form("c_%s_barrel",variable.Data()),Form("c_%s_barrel",variable.Data()),500,500);

  TH1F *h_barrel = h_den_barrel->Clone();
  SetFrame( h_barrel , Form("%s",xtitle.Data()), 1.02, 0.98);
  SetLabel( "Barrel" );

  TGraphAsymmErrors *g_barrel = new TGraphAsymmErrors();
  g_barrel->BayesDivide(h_num_barrel,h_den_barrel);
  g_barrel->SetMarkerSize(0.5);
  g_barrel->SetMarkerStyle(20);
  g_barrel->SetMarkerColor(4);
  g_barrel->Draw("PZsame");
  c_barrel->Print(Form("PFID_%s_barrel.eps",variable.Data()));

  TCanvas *c_endcap = new TCanvas(Form("c_%s_endcap",variable.Data()),Form("c_%s_endcap",variable.Data()),500,500);
  
  TH1F *h_endcap = h_den_endcap->Clone();
  SetFrame( h_endcap , Form("%s",xtitle.Data()), 1.02, 0.96);
  SetLabel( "Endcap" );

  TGraphAsymmErrors *g_endcap = new TGraphAsymmErrors();
  g_endcap->BayesDivide(h_num_endcap,h_den_endcap);
  g_endcap->SetMarkerSize(0.5);
  g_endcap->SetMarkerStyle(20);
  g_endcap->SetMarkerColor(4);
  g_endcap->Draw("PZsame");
  c_endcap->Print(Form("PFID_%s_endcap.eps",variable.Data()));

}

void plotPV(TFile *f, const TString & variable){

  Double_t newBins[31] = {0,4,6,8,10,
                         11,12,13,14,15,16,17,18,19,20,
                         21,22,23,24,25,26,27,28,29,30,
                         32,34,36,38,40,
                         60};

  TH1F *h_den_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Barrel/h_%s", variable.Data()));
  TH1F *h_num_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Barrel/h_%s", variable.Data()));
  TH1F *h_den_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Endcap/h_%s", variable.Data()));
  TH1F *h_num_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Endcap/h_%s", variable.Data()));
 
  TCanvas *c_barrel = new TCanvas(Form("c_%s_barrel",variable.Data()),Form("c_%s_barrel",variable.Data()),500,500);

  TH1F *h_barrel = h_den_barrel->Clone();
  SetFrame( h_barrel , "Number of vertices", 1.02, 0.98);
  SetLabel( "Barrel" );
 
  h_den_barrel->Rebin(30,"hNew_den_barrel",newBins);
  h_num_barrel->Rebin(30,"hNew_num_barrel",newBins);

  TGraphAsymmErrors *g_barrel = new TGraphAsymmErrors();
  g_barrel->BayesDivide(hNew_num_barrel,hNew_den_barrel);
  g_barrel->SetMarkerSize(0.5);
  g_barrel->SetMarkerStyle(20);
  g_barrel->SetMarkerColor(4);
  g_barrel->SetMaximum(1.02);
  g_barrel->Draw("PZsame");
  c_barrel->Print(Form("PFID_%s_barrel.eps",variable.Data()));

  TCanvas *c_endcap = new TCanvas(Form("c_%s_endcap",variable.Data()),Form("c_%s_endcap",variable.Data()),500,500);

  TH1F *h_endcap = h_den_endcap->Clone();
  SetFrame( h_endcap , "Number of vertices", 1.02, 0.96);
  SetLabel( "Endcap" );

  h_den_endcap->Rebin(30,"hNew_den_endcap",newBins);
  h_num_endcap->Rebin(30,"hNew_num_endcap",newBins);

  TGraphAsymmErrors *g_endcap = new TGraphAsymmErrors();
  g_endcap->BayesDivide(hNew_num_endcap,hNew_den_endcap);
  g_endcap->SetMarkerSize(0.5);
  g_endcap->SetMarkerStyle(20);
  g_endcap->SetMarkerColor(4);
  g_endcap->SetMaximum(1.02);
  g_endcap->Draw("PZsame");
  c_endcap->Print(Form("PFID_%s_endcap.eps",variable.Data()));

}

void ElectronPFId()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile *f=new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/vallot_TTbarTuneZ2.root");

  plotETA(f , "eta");
  plotPV(f , "pv");
  plot(f , "pt","P_{T}");
  plot(f , "njet","Jet multiplicity");

}

