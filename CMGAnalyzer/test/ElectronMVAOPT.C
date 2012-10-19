#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "norm.h"

void SetLabel(const TString & region){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.2,0.8,"t#bar{t} simulation in 53X");
  label->DrawLatex(0.2,0.8-0.05,Form("%s, at #sqrt{s} = 8 TeV",region.Data()));
  label->Draw();
}

void SetFrame( TH1 * h, const TString & xtitle, const TString & ytitle){
  h->SetTitle("");
  h->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
  h->GetYaxis()->SetTitle(Form("%s",ytitle.Data()));
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->Draw();
}

void ElectronMVAOPT()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_Signal_ttbar = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/vallot_TTbarTuneZ2.root");
  TFile * f_Signal_zjets = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/vallot_ZJets.root");
  TFile * f_QCD = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/vallot_Run2012ElEl.root");

  TH1F *hSignal_ttbar_mvaTrigV0_barrel = (TH1F *) f_Signal_ttbar->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_mvaTrigV0");
  TH1F *hSignal_ttbar_mvaTrigV0_endcap = (TH1F *) f_Signal_ttbar->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_mvaTrigV0");
  TH1F *hSignal_ttbar_EventSummary = (TH1F *) f_Signal_ttbar->Get("ElectronAnalysis/EventSummary");
  double nTotal_Signal_ttbar = hSignal_ttbar_EventSummary->GetBinContent(1);
  double norm_Signal_ttbar = getNorm( nTotal_Signal_ttbar, 225, 10000);

  TH1F * hSignal_ttbar_mvaTrigV0 = hSignal_ttbar_mvaTrigV0_barrel; 
  hSignal_ttbar_mvaTrigV0->Add(hSignal_ttbar_mvaTrigV0_endcap);  

  TH1F *hSignal_zjets_mvaTrigV0_barrel = (TH1F *) f_Signal_zjets->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_mvaTrigV0");
  TH1F *hSignal_zjets_mvaTrigV0_endcap = (TH1F *) f_Signal_zjets->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_mvaTrigV0");
  TH1F *hSignal_zjets_EventSummary = (TH1F *) f_Signal_zjets->Get("ElectronAnalysis/EventSummary");
  double nTotal_Signal_zjets = hSignal_zjets_EventSummary->GetBinContent(1);
  double norm_Signal_zjets = getNorm( nTotal_Signal_zjets, 3503.71, 10000);

  TH1F * hSignal_zjets_mvaTrigV0 = hSignal_zjets_mvaTrigV0_barrel;
  hSignal_zjets_mvaTrigV0->Add(hSignal_zjets_mvaTrigV0_endcap);

  TH1F *hQCD_mvaTrigV0_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_mvaTrigV0");
  TH1F *hQCD_mvaTrigV0_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_mvaTrigV0");

  TH1F * hQCD_mvaTrigV0 = hQCD_mvaTrigV0_barrel;
  hQCD_mvaTrigV0->Add(hQCD_mvaTrigV0_endcap);

  double sf_ttbar_signal = hSignal_ttbar_mvaTrigV0->Integral();
  double sf_zjets_signal = hSignal_zjets_mvaTrigV0->Integral();
  double sf_qcd = hQCD_mvaTrigV0->Integral();
  
  hSignal_ttbar_mvaTrigV0->Scale(norm_Signal_ttbar);
  hSignal_zjets_mvaTrigV0->Scale(norm_Signal_zjets);
  TH1F * hSignal_mvaTrigV0 = hSignal_ttbar_mvaTrigV0;
  //TH1F * hSignal_mvaTrigV0 = hSignal_zjets_mvaTrigV0;
  //hSignal_mvaTrigV0->Add( hSignal_zjets_mvaTrigV0 ); 
  hSignal_mvaTrigV0->Scale(1.0/sf_ttbar_signal);
  hQCD_mvaTrigV0->Scale(0.02/sf_qcd);
  //hQCD_mvaTrigV0->Scale(0.1);

  TCanvas * c = new TCanvas("c","c",500,500);
  c->SetLogy();
  c->SetGridy();
  c->SetGridx();
  SetFrame( hSignal_mvaTrigV0, "MVA TrigV0","Entries");
  SetFrame( hQCD_mvaTrigV0, "MVA TrigV0","Entries");
  hSignal_mvaTrigV0->SetLineColor(4);
  hSignal_mvaTrigV0->SetLineWidth(0.4);
  hQCD_mvaTrigV0->SetLineColor(2);
  hQCD_mvaTrigV0->SetLineWidth(0.4);

  hSignal_mvaTrigV0->Draw();
  hQCD_mvaTrigV0->Draw("same"); 

  TLegend *l= new TLegend(0.4,0.7,0.6,0.87);
  l->AddEntry(hSignal_mvaTrigV0,"Signal","L");
  l->AddEntry(hQCD_mvaTrigV0,"Background","L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print("c_mva_ttbar.eps");

  TCanvas * c_opt = new TCanvas("c_opt","c_opt",500,500);
  c_opt->SetGridy();
  c_opt->SetGridx();
  TH1* h_opt = new TH1F("h_opt","h_opt",200,-1-0.005,1-0.005);
  for(int i=0; i < 200 ; i++){
    double Si = hSignal_mvaTrigV0->Integral(i+1,200);
    double Bi = hQCD_mvaTrigV0->Integral(i+1,200);
    double soverb = Si/sqrt(Si+Bi);
    h_opt->SetBinContent(i+1, soverb);
  } 
  SetFrame( h_opt, "MVA TrigV0", "S/#sqrt{S+B}");
  h_opt->Draw();

  c_opt->Print("c_mvaopt_ttbar.eps");

  TCanvas * c_eff = new TCanvas("c_eff","c_eff",500,500);
  c_eff->SetGridy();
  c_eff->SetGridx();
  TH1* h_eff = new TH1F("h_eff","h_eff",200,-1-0.005,1-0.005);
  double total = hSignal_mvaTrigV0->Integral(1,200); 
  for(int i=0; i < 200 ; i++){
    double Si = hSignal_mvaTrigV0->Integral(i+1,200);
    double Ei = Si/total;
    h_eff->SetBinContent(i+1, Ei);
  }
 
  SetFrame( h_eff, "MVA TrigV0", "Efficiency");
  h_eff->Draw();

  c_eff->Print("c_mvaeff_ttbar.eps");

}

