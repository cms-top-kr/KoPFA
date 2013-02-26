#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include "TLatex.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void DrawLegend(TGraphAsymmErrors* g, TLegend* l, const TString ID_Algo,TString opt){
  //TLegend *l= new TLegend(loc);
  l->AddEntry(g,ID_Algo,opt);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void DrawLegendHisto(TH1* h, TLegend* l, const TString LegendName,TString opt){
  l->AddEntry(h,LegendName,opt);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
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

void HistoLegend(TH1* h, TLegend* l, const TString ID_Algo,TString opt){
  l->AddEntry(h,ID_Algo,opt);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void HistoStyle(TH1* h, int c, int mstyle){
  h->SetLineWidth(2);
  //h->SetLineStyle(lstyle);
  h->SetLineColor(c);
  h->SetMarkerStyle(mstyle);
  h->SetMarkerColor(c);
  h->SetMarkerSize(1.1);
  h->SetFillColor(c);
  //h->SetFillStyle(3001);
  //h->GetXaxis()->SetTitle("QCD efficiency");
  //h->GetYaxis()->SetTitle("Signal efficiency");
}

void GraphStyleEff(TGraphAsymmErrors* g, int c, int mstyle){
  g->SetLineWidth(2);
  //g->SetLineStyle(lstyle);
  g->SetLineColor(c);
  g->SetMarkerStyle(mstyle);
  g->SetMarkerColor(c);
  g->SetMarkerSize(1.1);
  g->SetFillColor(c);
  //g->SetFillStyle(3001);
  g->GetXaxis()->SetTitle("Relative Isolation");
  g->GetYaxis()->SetTitle("Efficiency");
}

TGraphAsymmErrors* ROC( TH1* hSignal, TH1* hQCD){
  TGraphAsymmErrors* out = new TGraphAsymmErrors();
  int nbins = hSignal->GetNbinsX();
  double totalS = hSignal->GetEntries();
  double totalB = hQCD->GetEntries();
  cout << "=============================================================" << endl;
  cout << hSignal->GetTitle() << endl;
  cout << "totalS = " << totalS << "      totalB= " << totalB << endl;
  cout << "=============================================================" << endl;
  int bin;
  for(int i=0 ; i < 51; i++){
    bin=i+1;
//    bin=i;
    double Bi = hQCD->Integral(0,bin);
    double Si = hSignal->Integral(0,bin);
    double eff_qcd = Bi / totalB;
    double eff_signal = Si/ totalS; 
    double err_qcd = sqrt(Bi) / totalB;
    double soverb = eff_signal/sqrt(eff_signal+eff_qcd);
    cout.setf(ios::fixed);
    cout.precision(5);
    cout << "isolation value = "  << 0.01*(bin) << "      signal eff = " << eff_signal << "      background eff = " << eff_qcd << "      s/sqrt(s+b)= " << soverb << endl ;
    cout.precision();
    //out->SetPoint(i, eff_signal, 1-eff_qcd);
    out->SetPoint(i, eff_qcd, eff_signal);
    out->SetPointEXhigh(i,err_qcd);
    out->SetPointEXlow(i, err_qcd);
  }   
  return out;
}

TGraphAsymmErrors* EFF( TH1* hSignal ){
  TGraphAsymmErrors* out = new TGraphAsymmErrors();
  int nbins = hSignal->GetNbinsX();
  double totalS = hSignal->GetEntries();
  int bin;
  for(int i=0 ; i < 1000; i++){
    bin=i+1;
    double Si = hSignal->Integral(0,bin);
    double eff_signal = Si/ totalS; 
    out->SetPoint(i, 0.01*(i+1), eff_signal);
    //out->SetPointEXhigh(i,err_signal);
    //out->SetPointEXlow(i, err_signal);
  }   
  return out;
}

void ROCPlot(){

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TString srcDir ="/afs/cern.ch/work/t/tjkim/public/MuonOut/MuMuDec25/"; // 2 bJets
  TString srcDir2 ="/afs/cern.ch/work/t/tjkim/public/MuonOut/"; // 
  TString plots ="./plots_isoOpt2012db/";

  TFile * fSIG = new TFile(srcDir2+"vallot_TTbarTuneZ2.root");
  TFile * fRD  = new TFile(srcDir+"MuonIso_Run2012MuMu.root");

////////////////////////////////////////////////////////////////////////////////

  TH2F * h2_QCD_pfRelIso02db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso02db_vtx");
  TH2F * h2_QCD_pfRelIso03db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso03db_vtx");
  TH2F * h2_QCD_pfRelIso04db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso04db_vtx");

  TH1D* hQCD_pfRelIso02db_lowPU = h2_QCD_pfRelIso02db->ProjectionY("hQCD_pfRelIso02db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso03db_lowPU = h2_QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso04db_lowPU = h2_QCD_pfRelIso04db->ProjectionY("hQCD_pfRelIso04db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso02db_hiPU  = h2_QCD_pfRelIso02db->ProjectionY("hQCD_pfRelIso02db_hiPU",15,50);  
  TH1D* hQCD_pfRelIso03db_hiPU  = h2_QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_hiPU",15,50);  
  TH1D* hQCD_pfRelIso04db_hiPU  = h2_QCD_pfRelIso04db->ProjectionY("hQCD_pfRelIso04db_hiPU",15,50);  
  TH1D* hQCD_pfRelIso02db  = h2_QCD_pfRelIso02db->ProjectionY("hQCD_pfRelIso02db_hiPU",0,50);
  TH1D* hQCD_pfRelIso03db  = h2_QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_hiPU",0,50);
  TH1D* hQCD_pfRelIso04db  = h2_QCD_pfRelIso04db->ProjectionY("hQCD_pfRelIso04db_hiPU",0,50);

  hQCD_pfRelIso02db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db_hiPU->GetXaxis()->SetRangeUser(0,1.0);

  TCanvas *c2db2=new TCanvas("c2db2","QCD-db",400,400);
  gPad->SetLogy();
  hQCD_pfRelIso04db_lowPU->Draw();
  hQCD_pfRelIso03db_lowPU->Draw("same");
  hQCD_pfRelIso04db_hiPU->Draw("same");
  hQCD_pfRelIso03db_hiPU->Draw("same");
  hQCD_pfRelIso04db_lowPU->SetLineColor(4);
  hQCD_pfRelIso03db_lowPU->SetLineColor(3);
  hQCD_pfRelIso04db_lowPU->SetLineColor(4);
  hQCD_pfRelIso03db_hiPU->SetLineColor(3);
  hQCD_pfRelIso04db_hiPU->SetLineStyle(2);
  hQCD_pfRelIso03db_hiPU->SetLineStyle(2);
  
  hQCD_pfRelIso03db_lowPU->GetXaxis()->SetTitle("RelIso");
  hQCD_pfRelIso04db_lowPU->GetXaxis()->SetTitle("RelIso");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegendHisto(hQCD_pfRelIso04db_lowPU, l, "Cone R=0.4 (low PU)","L");
  DrawLegendHisto(hQCD_pfRelIso03db_lowPU, l, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(hQCD_pfRelIso04db_hiPU, l, "Cone R=0.4 (high PU)","L");
  DrawLegendHisto(hQCD_pfRelIso03db_hiPU, l, "Cone R=0.3 (high PU)","L");

  c2db2->Print(plots+"PUQCDdb2.png");
  c2db2->Print(plots+"PUQCDdb2.pdf");

////////////////////////////////////////////////////////////////////////////////

  TH2F * h2_SIG_pfRelIso02db = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso02db_vtx");
  TH2F * h2_SIG_pfRelIso03db = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso03db_vtx");
  TH2F * h2_SIG_pfRelIso04db = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso04db_vtx");

  TH1D* hSIG_pfRelIso02db_lowPU = h2_SIG_pfRelIso02db->ProjectionY("hSIG_pfRelIso02db_lowPU",1,14);  
  TH1D* hSIG_pfRelIso03db_lowPU = h2_SIG_pfRelIso03db->ProjectionY("hSIG_pfRelIso03db_lowPU",1,14);  
  TH1D* hSIG_pfRelIso04db_lowPU = h2_SIG_pfRelIso04db->ProjectionY("hSIG_pfRelIso04db_lowPU",1,14);  
  TH1D* hSIG_pfRelIso02db_hiPU  = h2_SIG_pfRelIso02db->ProjectionY("hSIG_pfRelIso02db_hiPU",15,50);  
  TH1D* hSIG_pfRelIso03db_hiPU  = h2_SIG_pfRelIso03db->ProjectionY("hSIG_pfRelIso03db_hiPU",15,50);  
  TH1D* hSIG_pfRelIso04db_hiPU  = h2_SIG_pfRelIso04db->ProjectionY("hSIG_pfRelIso04db_hiPU",15,50);  

  hSIG_pfRelIso02db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso02db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04db_hiPU->GetXaxis()->SetRangeUser(0,1.0);

  TCanvas *c4db2=new TCanvas("c4db2","SIG-db",400,400);
  gPad->SetLogy();
  hSIG_pfRelIso04db_lowPU->Draw();
  hSIG_pfRelIso03db_lowPU->Draw("same");
  hSIG_pfRelIso04db_hiPU->Draw("same");
  hSIG_pfRelIso03db_hiPU->Draw("same");
  hSIG_pfRelIso04db_lowPU->SetLineColor(4);
  hSIG_pfRelIso03db_lowPU->SetLineColor(3);
  hSIG_pfRelIso04db_hiPU->SetLineColor(4);
  hSIG_pfRelIso03db_hiPU->SetLineColor(3);
  hSIG_pfRelIso04db_hiPU->SetLineStyle(2);
  hSIG_pfRelIso03db_hiPU->SetLineStyle(2);
  hSIG_pfRelIso03db_lowPU->GetXaxis()->SetTitle("RelIso");
  hSIG_pfRelIso04db_lowPU->GetXaxis()->SetTitle("RelIso");

  TLegend *l= new TLegend(0.45,0.88,0.83,0.68);
  DrawLegendHisto(hSIG_pfRelIso04db_lowPU, l, "Cone R=0.4 (low PU)","L");
  DrawLegendHisto(hSIG_pfRelIso03db_lowPU, l, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(hSIG_pfRelIso04db_hiPU, l, "Cone R=0.4 (high PU)","L");
  DrawLegendHisto(hSIG_pfRelIso03db_hiPU, l, "Cone R=0.3 (high PU)","L");

  c4db2->Print(plots+"PUsignaldb2.png");
  c4db2->Print(plots+"PUsignaldb2.pdf");

////////////////////////////////////////////////////////////////////////////////

  gROC_SIG03_lowPUdb = ROC(hSIG_pfRelIso03db_lowPU, hQCD_pfRelIso03db_lowPU);
  gROC_SIG04_lowPUdb = ROC(hSIG_pfRelIso04db_lowPU, hQCD_pfRelIso04db_lowPU);
  gROC_SIG03_hiPUdb = ROC(hSIG_pfRelIso03db_hiPU, hQCD_pfRelIso03db_hiPU);
  gROC_SIG04_hiPUdb = ROC(hSIG_pfRelIso04db_hiPU, hQCD_pfRelIso04db_hiPU);

  //gROC_SIG04_lowPUdb->GetXaxis()->SetRangeUser(0,0.15);
  //gROC_SIG04_lowPUdb->SetMaximum(0.96);
  //gROC_SIG04_lowPUdb->SetMinimum(0.6);

//////////////

  TCanvas *c5db_lowPU = new TCanvas("c5db_lowPU","ROC_lowPU",400,400);
  c5db_lowPU->SetTickx();
  c5db_lowPU->SetTicky();

  Style(gROC_SIG03_lowPUdb, 2, 23);
  Style(gROC_SIG04_lowPUdb, 4, 22);

  gROC_SIG03_lowPUdb->GetXaxis()->SetNdivisions(505);

  gROC_SIG04_lowPUdb->Draw("ACP");
  gROC_SIG03_lowPUdb->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gROC_SIG03_lowPUdb, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gROC_SIG04_lowPUdb, l, "Cone R=0.4 (low PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"Delta-beta Correction");
  label->Draw();

  c5db_lowPU->Print(plots+"ROC_lowPU.png");
  c5db_lowPU->Print(plots+"ROC_lowPU.pdf");

//////////////////

  TCanvas *c5db_highPU = new TCanvas("c5db_highPU","ROC_highPU",400,400);
  c5db_highPU->SetTickx();
  c5db_highPU->SetTicky();

  Style(gROC_SIG03_hiPUdb, 2, 23);
  Style(gROC_SIG04_hiPUdb, 4, 22);

  gROC_SIG04_hiPUdb->Draw("ACP");
  gROC_SIG03_hiPUdb->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gROC_SIG03_hiPUdb, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gROC_SIG04_hiPUdb, l, "Cone R=0.4 (high PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"Delta-beta Correction");
  label->Draw();

  c5db_highPU->Print(plots+"ROC_highPU.png");
  c5db_highPU->Print(plots+"ROC_highPU.eps");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5effdb = new TCanvas("c5effdb","IsoEff-SIGdb",400,400);
  c5effdb->SetTickx();
  c5effdb->SetTicky();

  gEFF_SIG03db_lowPU = EFF(hSIG_pfRelIso03db_lowPU);
  gEFF_SIG04db_lowPU = EFF(hSIG_pfRelIso04db_lowPU);
  gEFF_SIG03db_hiPU = EFF(hSIG_pfRelIso03db_hiPU);
  gEFF_SIG04db_hiPU = EFF(hSIG_pfRelIso04db_hiPU);

  GraphStyleEff(gEFF_SIG03db_lowPU, 2, 23);
  GraphStyleEff(gEFF_SIG04db_lowPU, 4, 22);
  GraphStyleEff(gEFF_SIG03db_hiPU, 28, 2);
  GraphStyleEff(gEFF_SIG04db_hiPU, 8, 5);

  double max = gEFF_SIG04db_lowPU->GetHistogram()->GetMaximum();
  gEFF_SIG04db_lowPU->GetXaxis()->SetRangeUser(0,0.4);
  gEFF_SIG04db_lowPU->SetMinimum(0.3);
  gEFF_SIG04db_lowPU->SetMaximum(0.6);

  gEFF_SIG04db_lowPU->Draw("ACP");
  gEFF_SIG03db_lowPU->Draw("CPsame");
  gEFF_SIG04db_hiPU->Draw("CPsame");
  gEFF_SIG03db_hiPU->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gEFF_SIG03db_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gEFF_SIG04db_lowPU, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gEFF_SIG03db_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gEFF_SIG04db_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"Delta-beta Correction");
  label->Draw();

  c5effdb->Print(plots+"PUSIGdb_efficiency.png");
  c5effdb->Print(plots+"PUSIGdb_efficiency.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5effQCDdb = new TCanvas("c5effQCDdb","IsoEff-QCDdb",400,400);
  c5effQCDdb->SetTickx();
  c5effQCDdb->SetTicky();

  gEFF_QCD03db_lowPU = EFF(hQCD_pfRelIso03db_lowPU);
  gEFF_QCD04db_lowPU = EFF(hQCD_pfRelIso04db_lowPU);
  gEFF_QCD03db_hiPU = EFF(hQCD_pfRelIso03db_hiPU);
  gEFF_QCD04db_hiPU = EFF(hQCD_pfRelIso04db_hiPU);

  GraphStyleEff(gEFF_QCD03db_lowPU, 2, 23);
  GraphStyleEff(gEFF_QCD04db_lowPU, 4, 22);
  GraphStyleEff(gEFF_QCD03db_hiPU, 28, 2);
  GraphStyleEff(gEFF_QCD04db_hiPU, 8, 5);

  gEFF_QCD04db_lowPU->GetXaxis()->SetRangeUser(0,0.4);
  gEFF_QCD04db_lowPU->SetMinimum(0);
  gEFF_QCD04db_lowPU->SetMaximum(0.5);

  gEFF_QCD04db_lowPU->Draw("ACP");
  gEFF_QCD03db_lowPU->Draw("CPsame");
  gEFF_QCD04db_hiPU->Draw("CPsame");
  gEFF_QCD03db_hiPU->Draw("CPsame");

  TLegend *l= new TLegend(0.22,0.62,0.60,0.82);
  DrawLegend(gEFF_QCD03db_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gEFF_QCD04db_lowPU, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gEFF_QCD03db_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gEFF_QCD04db_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.22,0.84,"Delta-beta Correction");
  label->Draw();

  c5effQCDdb->Print(plots+"PUQCDdb_efficiency.png");
  c5effQCDdb->Print(plots+"PUQCDdb_efficiency.pdf");

///////////////////////////////////////////////////////////////////////////////
}
