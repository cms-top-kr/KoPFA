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
  label->DrawLatex(0.4,0.5,Form("%s",region.Data()));
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

void ElectronMVAOPT(bool merge=true, const int area = 0)
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_Signal = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/njet1_update/vallot_TTbarTuneZ2.root");
  TFile * f_QCD = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/njet1_update/vallot_Run2012ElEl.root");

  TH1F *hSignal_mvaTrigV0[3];
  hSignal_mvaTrigV0[0] = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel1/h_mvaTrigV0");
  hSignal_mvaTrigV0[1] = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel2/h_mvaTrigV0");
  hSignal_mvaTrigV0[2] = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_mvaTrigV0");
  TH1F *hQCD_mvaTrigV0[3];
  hQCD_mvaTrigV0[0] = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel1/h_mvaTrigV0");
  hQCD_mvaTrigV0[1] = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel2/h_mvaTrigV0");
  hQCD_mvaTrigV0[2] = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_mvaTrigV0");

  TH1F *hSignal_EventSummary = (TH1F *) f_Signal->Get("ElectronAnalysis/EventSummary");

  double nTotal_Signal = hSignal_EventSummary->GetBinContent(1);
  double norm_Signal = getNorm( nTotal_Signal, 225, 10000);
  //double norm_Signal = getNorm( nTotal_Signal, 3503.71, 10000); //ZJets

  if(merge){
    hSignal_mvaTrigV0[0]->Add(hSignal_mvaTrigV0[1]);  
    hSignal_mvaTrigV0[0]->Add(hSignal_mvaTrigV0[2]);  
    hQCD_mvaTrigV0[0]->Add(hQCD_mvaTrigV0[1]);  
    hQCD_mvaTrigV0[0]->Add(hQCD_mvaTrigV0[2]);  
  }

  double sf_Signal = hSignal_mvaTrigV0[area]->Integral();
  double sf_QCD = hQCD_mvaTrigV0[area]->Integral();
  
  hSignal_mvaTrigV0[area]->Scale(norm_Signal);
  hSignal_mvaTrigV0[area]->Scale(1.0/sf_Signal);
  hQCD_mvaTrigV0[area]->Scale(0.02/sf_QCD);
 
  //Rebin
  hSignal_mvaTrigV0[area]->Rebin(10);
  hQCD_mvaTrigV0[area]->Rebin(10);

  TCanvas * c = new TCanvas("c","c",500,500);
  c->SetLogy();
  c->SetGridy();
  c->SetGridx();
  SetFrame( hSignal_mvaTrigV0[area], "MVA TrigV0","Entries");
  SetFrame( hQCD_mvaTrigV0[area], "MVA TrigV0","Entries");
  hSignal_mvaTrigV0[area]->SetLineColor(4);
  hSignal_mvaTrigV0[area]->SetFillColor(4);
  hSignal_mvaTrigV0[area]->SetFillStyle(3335);
  hSignal_mvaTrigV0[area]->SetLineWidth(0.4);
  hQCD_mvaTrigV0[area]->SetLineColor(2);
  hQCD_mvaTrigV0[area]->SetFillColor(2);
  hQCD_mvaTrigV0[area]->SetFillStyle(3353);
  hQCD_mvaTrigV0[area]->SetLineWidth(0.4);

  hSignal_mvaTrigV0[area]->Draw();
  hQCD_mvaTrigV0[area]->Draw("same"); 

  if(merge){
    SetLabel( "|#eta| < 2.5" );
  }else{
    if(area ==0) SetLabel( "0 < |#eta| < 0.8" );
    if(area ==1) SetLabel( "0.8 < |#eta| < 1.479" );
    if(area ==2) SetLabel( "1.479 < |#eta| < 2.5" );
  }

  TLegend *l= new TLegend(0.4,0.7,0.6,0.87);
  l->AddEntry(hSignal_mvaTrigV0[area],"Signal","F");
  l->AddEntry(hQCD_mvaTrigV0[area],"Background","F");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  if(merge){
    c->Print("c_mva_ttbar.eps");
  }else{
    c->Print(Form("c_mva_ttbar_%i.eps",area));
  }

  int nbins = 20;

  TCanvas * c_opt = new TCanvas("c_opt","c_opt",500,500);
  c_opt->SetGridy();
  c_opt->SetGridx();
  TH1* h_opt = new TH1F("h_opt","h_opt",nbins,-1,1);
  for(int i=0; i < nbins ; i++){
    double Si = hSignal_mvaTrigV0[area]->Integral(i+1, nbins);
    double Bi = hQCD_mvaTrigV0[area]->Integral(i+1,nbins);
    double soverb = Si/sqrt(Si+Bi);
    h_opt->SetBinContent(i+1, soverb);
  } 
  SetFrame( h_opt, "MVA TrigV0", "S/#sqrt{S+B}");
  h_opt->Draw();

  if(merge){
    SetLabel( "|#eta| < 2.5" );
  }else{
    if(area ==0) SetLabel( "0 < |#eta| < 0.8" );
    if(area ==1) SetLabel( "0.8 < |#eta| < 1.479" );
    if(area ==2) SetLabel( "1.479 < |#eta| < 2.5" );
  }

  if(merge){
    c_opt->Print("c_mvaopt_ttbar.eps");
  }else{
    c_opt->Print(Form("c_mvaopt_ttbar_%i.eps",area));
  }

  TCanvas * c_eff = new TCanvas("c_eff","c_eff",500,500);
  c_eff->SetGridy();
  c_eff->SetGridx();
  TH1* h_eff = new TH1F("h_eff","h_eff",nbins,-1,1);
  double total = hSignal_mvaTrigV0[area]->Integral(1,nbins); 
  for(int i=0; i < nbins ; i++){
    double Si = hSignal_mvaTrigV0[area]->Integral(i+1,nbins);
    double Ei = Si/total;
    h_eff->SetBinContent(i+1, Ei);
  }
 
  SetFrame( h_eff, "MVA TrigV0", "Efficiency");
  h_eff->Draw();
 
  if(merge){
    SetLabel( "|#eta| < 2.5" );
  }else{
    if(area ==0) SetLabel( "0 < |#eta| < 0.8" );
    if(area ==1) SetLabel( "0.8 < |#eta| < 1.479" );
    if(area ==2) SetLabel( "1.479 < |#eta| < 2.5" );
  }

  if(merge){
    c_eff->Print("c_mvaeff_ttbar.eps");
  }else{
    c_eff->Print(Form("c_mvaeff_ttbar_%i.eps",area));
  }
}

