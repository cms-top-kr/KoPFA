#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>


void ElectronPFId()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();
  
  TFile *f=new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/vallot_TTbarTuneZ2.root");

  plot(f, "pv");

}

void plot(TFile * f, const TString & variable){

  TCanvas *c = new TCanvas("c_pv","c_pv",500,500);
  TH1F *h_den_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Endcap/h_%s",variable.Data()));
  TH1F *h_num_endcap = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Endcap/h_%s",variable.Data()));
  TH1F *h_den_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIso/Barrel/h_%s",variable.Data()));
  TH1F *h_num_barrel = (TH1F *) f->Get(Form("ElectronAnalysis/Signal/IDMediumIsoPF/Barrel/h_%s",variable.Data()));

  TH1F *h_den = h_den_endcap->Clone();
  TH1F *h_num = h_num_endcap->Clone();

  h_den->Add(h_den_barrel);
  h_num->Add(h_num_barrel);

  Double_t newBins[31] = {0,4,6,8,10,
                         11,12,13,14,15,16,17,18,19,20,
                         21,22,23,24,25,26,27,28,29,30,
                         32,34,36,38,40,
                         60};

  h_den->Rebin(30,"hNew_den",newBins);
  h_num->Rebin(30,"hNew_num",newBins);

  TH1F *h = hNew_den->Clone();
  h->SetTitle("");
  h->GetXaxis()->SetTitle("Number of Vertices");
  h->GetYaxis()->SetTitle("PF ID Efficiency");
  h->Reset();
  h->Sumw2();
  h->Divide(hNew_num, hNew_den);
  h->SetMarkerSize(0.4);
  h->SetMarkerStyle(20);
  h->Draw("P");
  c->Print(Form("PFID_%s.eps",variable.Data()));

}


