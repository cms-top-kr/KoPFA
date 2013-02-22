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

void GraphStyle(TGraphAsymmErrors* g, int c, int mstyle){
  //g->SetLineWidth(2);
  //g->SetLineStyle(lstyle);
  g->SetLineColor(c);
  g->SetMarkerStyle(mstyle);
  g->SetMarkerColor(c);
  g->SetMarkerSize(0.8);
  g->SetFillColor(c);
  //g->SetFillStyle(3001);
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

void isoOpt2012db(){
//  gROOT->LoadMacro("tdrStyle.C");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/MuonOut/MuMuDec25/"; // 2 bJets
//  TString srcDir2 ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/MuonOut/MuMuDec26TTbarbtag1/"; // 
  TString srcDir2 ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/MuonOut/MuMuDec30TTbar2jets/"; // 
  TString plots ="./plots_isoOpt2012db/";

  //TFile * fSIG = new TFile(srcDir+"vallot_ZJets.root");
  //TFile * fQCDmc = new TFile(srcDir+"vallot_QCDMuon.root");
  //TFile * fSIG = new TFile(srcDir+"MuonIso_Run2012MuMu.root");
  TFile * fSIG = new TFile(srcDir2+"vallot_TTbarTuneZ2.root");
  TFile * fRD  = new TFile(srcDir+"MuonIso_Run2012MuMu.root");

////////////////////////////////////////////////////////////////////////////////
  TCanvas *c0=new TCanvas("c0","2dQCDiso",400,400);

  TH2F * h2_QCD_iso = (TH2F*) fRD->Get("MuonAnalysis/h2_QCDMuonsIso03");
  h2_QCD_iso->GetXaxis()->SetTitleSize(0.05);
  h2_QCD_iso->GetYaxis()->SetTitleSize(0.05);
  h2_QCD_iso->GetXaxis()->SetTitle("Relative Isolation (Leg1)");
  h2_QCD_iso->GetYaxis()->SetTitle("Relative Isolation (Leg2)");
  h2_QCD_iso->Draw("colZ");

  c0->Print(plots+"2dQCDiso.png");
  c0->Print(plots+"2dQCDiso.pdf");

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  TCanvas *c1=new TCanvas("c1","2dQCDpt",400,400);

  TH2F * h2_QCD_pt = (TH2F*) fRD->Get("MuonAnalysis/h2_QCDMuonsPt");
  h2_QCD_pt->GetXaxis()->SetTitleSize(0.05);
  h2_QCD_pt->GetYaxis()->SetTitleSize(0.05);
  h2_QCD_pt->GetXaxis()->SetTitle("P_{T} (Leg1)(GeV/c)");
  h2_QCD_pt->GetYaxis()->SetTitle("P_{T} (Leg2)(GeV/c)");
  h2_QCD_pt->Draw("colZ");

  c1->Print(plots+"2dQCDpt.png");
  c1->Print(plots+"2dQCDpt.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2=new TCanvas("c2","QCD_",400,400);
  c2->SetLogy();
  c2->Divide(2,2);

  TH2F * h2_QCD_pfRelIso02 = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso02_vtx");
  TH2F * h2_QCD_pfRelIso03 = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso03_vtx");
  TH2F * h2_QCD_pfRelIso04 = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso04_vtx");

  TH1D* hQCD_pfRelIso02_lowPU = h2_QCD_pfRelIso02->ProjectionY("hQCD_pfRelIso02_lowPU",1,14);  
  TH1D* hQCD_pfRelIso03_lowPU = h2_QCD_pfRelIso03->ProjectionY("hQCD_pfRelIso03_lowPU",1,14);  
  TH1D* hQCD_pfRelIso04_lowPU = h2_QCD_pfRelIso04->ProjectionY("hQCD_pfRelIso04_lowPU",1,14);  
  TH1D* hQCD_pfRelIso02_hiPU  = h2_QCD_pfRelIso02->ProjectionY("hQCD_pfRelIso02_hiPU",15,50);  
  TH1D* hQCD_pfRelIso03_hiPU  = h2_QCD_pfRelIso03->ProjectionY("hQCD_pfRelIso03_hiPU",15,50);  
  TH1D* hQCD_pfRelIso04_hiPU  = h2_QCD_pfRelIso04->ProjectionY("hQCD_pfRelIso04_hiPU",15,50);  


  hQCD_pfRelIso02_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04_hiPU->GetXaxis()->SetRangeUser(0,1.0);

  c2->cd(1);
  gPad->SetLogy(); 
  hQCD_pfRelIso02_lowPU->SetLineColor(1);
  hQCD_pfRelIso02_lowPU->Draw();
  hQCD_pfRelIso02_hiPU->SetLineColor(6);
  hQCD_pfRelIso02_hiPU->Draw("same");
  c2->cd(2);
  gPad->SetLogy(); 
  hQCD_pfRelIso03_lowPU->SetLineColor(2);
  hQCD_pfRelIso03_lowPU->Draw();
  hQCD_pfRelIso03_hiPU->SetLineColor(28);
  hQCD_pfRelIso03_hiPU->Draw("same");
  c2->cd(3);
  gPad->SetLogy(); 
  hQCD_pfRelIso04_lowPU->SetLineColor(4);
  hQCD_pfRelIso04_lowPU->Draw();
  hQCD_pfRelIso04_hiPU->SetLineColor(8);
  hQCD_pfRelIso04_hiPU->Draw("same");
  c2->cd(4);
  gPad->SetLogy(); 
  hQCD_pfRelIso02_lowPU->Draw();
  hQCD_pfRelIso03_lowPU->Draw("same");
  hQCD_pfRelIso04_lowPU->Draw("same");
  hQCD_pfRelIso02_hiPU->Draw("same");
  hQCD_pfRelIso03_hiPU->Draw("same");
  hQCD_pfRelIso04_hiPU->Draw("same");

  c2->Print(plots+"QCD.png");
  c2->Print(plots+"QCD.pdf");

  TCanvas *c22=new TCanvas("c22","QCD()",400,400);
  gPad->SetLogy();
  hQCD_pfRelIso04_lowPU->Draw();
  hQCD_pfRelIso03_lowPU->Draw("same");
  hQCD_pfRelIso02_lowPU->Draw("same");
  hQCD_pfRelIso02_lowPU->GetXaxis()->SetTitle("RelIso");
  hQCD_pfRelIso03_lowPU->GetXaxis()->SetTitle("RelIso");
  hQCD_pfRelIso04_lowPU->GetXaxis()->SetTitle("RelIso");

  c22->Print(plots+"PUQCD2.png");
  c22->Print(plots+"PUQCD2.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2db=new TCanvas("c2db","QCD_db",400,400);
  c2db->SetLogy();
  c2db->Divide(2,2);

  TH2F * h2_QCD_pfRelIso02db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso02db_vtx");
  TH2F * h2_QCD_pfRelIso03db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso03db_vtx");
  TH2F * h2_QCD_pfRelIso04db = (TH2F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h2_pfRelIso04db_vtx");

  TH1D* hQCD_pfRelIso02db_lowPU = h2_QCD_pfRelIso02db->ProjectionY("hQCD_pfRelIso02db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso03db_lowPU = h2_QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso04db_lowPU = h2_QCD_pfRelIso04db->ProjectionY("hQCD_pfRelIso04db_lowPU",1,14);  
  TH1D* hQCD_pfRelIso02db_hiPU  = h2_QCD_pfRelIso02db->ProjectionY("hQCD_pfRelIso02db_hiPU",15,50);  
  TH1D* hQCD_pfRelIso03db_hiPU  = h2_QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_hiPU",15,50);  
  TH1D* hQCD_pfRelIso04db_hiPU  = h2_QCD_pfRelIso04db->ProjectionY("hQCD_pfRelIso04db_hiPU",15,50);  


  hQCD_pfRelIso02db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db_hiPU->GetXaxis()->SetRangeUser(0,1.0);

  c2db->cd(1);
  gPad->SetLogy(); 
  hQCD_pfRelIso02db_lowPU->SetLineColor(1);
  hQCD_pfRelIso02db_lowPU->Draw();
  hQCD_pfRelIso02db_hiPU->SetLineColor(6);
  hQCD_pfRelIso02db_hiPU->Draw("same");
  c2db->cd(2);
  gPad->SetLogy(); 
  hQCD_pfRelIso03db_lowPU->SetLineColor(2);
  hQCD_pfRelIso03db_lowPU->Draw();
  hQCD_pfRelIso03db_hiPU->SetLineColor(28);
  hQCD_pfRelIso03db_hiPU->Draw("same");
  c2db->cd(3);
  gPad->SetLogy(); 
  hQCD_pfRelIso04db_lowPU->SetLineColor(4);
  hQCD_pfRelIso04db_lowPU->Draw();
  hQCD_pfRelIso04db_hiPU->SetLineColor(8);
  hQCD_pfRelIso04db_hiPU->Draw("same");
  c2db->cd(4);
  gPad->SetLogy(); 
  hQCD_pfRelIso02db_lowPU->Draw();
  hQCD_pfRelIso03db_lowPU->Draw("same");
  hQCD_pfRelIso04db_lowPU->Draw("same");
  hQCD_pfRelIso02db_hiPU->Draw("same");
  hQCD_pfRelIso03db_hiPU->Draw("same");
  hQCD_pfRelIso04db_hiPU->Draw("same");

  c2db->Print(plots+"QCDdb.png");
  c2db->Print(plots+"QCDdb.pdf");

  TCanvas *c2db2=new TCanvas("c2db2","QCD(db)",400,400);
  gPad->SetLogy();
  hQCD_pfRelIso04db_lowPU->Draw();
  hQCD_pfRelIso03db_lowPU->Draw("same");
  hQCD_pfRelIso02db_lowPU->Draw("same");
  hQCD_pfRelIso02db_lowPU->GetXaxis()->SetTitle("RelIso");
  hQCD_pfRelIso03db_lowPU->GetXaxis()->SetTitle("RelIso");
  hQCD_pfRelIso04db_lowPU->GetXaxis()->SetTitle("RelIso");

  c2db2->Print(plots+"PUQCDdb2.png");
  c2db2->Print(plots+"PUQCDdb2.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c4db=new TCanvas("c4db","SIG_db",400,400);
  c4db->SetLogy();
  c4db->Divide(2,2);

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

  c4db->cd(1);
  gPad->SetLogy(); 
  hSIG_pfRelIso02db_lowPU->SetLineColor(1);
  hSIG_pfRelIso02db_lowPU->Draw();
  hSIG_pfRelIso02db_hiPU->SetLineColor(6);
  hSIG_pfRelIso02db_hiPU->Draw("same");
  c4db->cd(2);
  gPad->SetLogy(); 
  hSIG_pfRelIso03db_lowPU->SetLineColor(2);
  hSIG_pfRelIso03db_lowPU->Draw();
  hSIG_pfRelIso03db_hiPU->SetLineColor(28);
  hSIG_pfRelIso03db_hiPU->Draw("same");
  c4db->cd(3);
  gPad->SetLogy(); 
  hSIG_pfRelIso04db_lowPU->SetLineColor(4);
  hSIG_pfRelIso04db_lowPU->Draw();
  hSIG_pfRelIso04db_hiPU->SetLineColor(8);
  hSIG_pfRelIso04db_hiPU->Draw("same");
  c4db->cd(4);
  gPad->SetLogy(); 
  hSIG_pfRelIso02db_lowPU->Draw();
  hSIG_pfRelIso03db_lowPU->Draw("same");
  hSIG_pfRelIso04db_lowPU->Draw("same");
  hSIG_pfRelIso02db_hiPU->Draw("same");
  hSIG_pfRelIso03db_hiPU->Draw("same");
  hSIG_pfRelIso04db_hiPU->Draw("same");

  c4db->Print(plots+"signaldb.png");
  c4db->Print(plots+"signaldb.pdf");

  TCanvas *c4db2=new TCanvas("c4db2","SIG(db)",400,400);
  gPad->SetLogy();
  hSIG_pfRelIso04db_lowPU->Draw();
  hSIG_pfRelIso03db_lowPU->Draw("same");
  hSIG_pfRelIso02db_lowPU->Draw("same");
  hSIG_pfRelIso02db_lowPU->GetXaxis()->SetTitle("RelIso");
  hSIG_pfRelIso03db_lowPU->GetXaxis()->SetTitle("RelIso");
  hSIG_pfRelIso04db_lowPU->GetXaxis()->SetTitle("RelIso");

  c4db2->Print(plots+"PUsignaldb2.png");
  c4db2->Print(plots+"PUsignaldb2.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c4=new TCanvas("c4","SIG_",400,400);
  c4->SetLogy();
  c4->Divide(2,2);

  TH2F * h2_SIG_pfRelIso02 = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso02_vtx");
  TH2F * h2_SIG_pfRelIso03 = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso03_vtx");
  TH2F * h2_SIG_pfRelIso04 = (TH2F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h2_pfRelIso04_vtx");

  TH1D* hSIG_pfRelIso02_lowPU = h2_SIG_pfRelIso02->ProjectionY("hSIG_pfRelIso02_lowPU",1,14);  
  TH1D* hSIG_pfRelIso03_lowPU = h2_SIG_pfRelIso03->ProjectionY("hSIG_pfRelIso03_lowPU",1,14);  
  TH1D* hSIG_pfRelIso04_lowPU = h2_SIG_pfRelIso04->ProjectionY("hSIG_pfRelIso04_lowPU",1,14);  
  TH1D* hSIG_pfRelIso02_hiPU  = h2_SIG_pfRelIso02->ProjectionY("hSIG_pfRelIso02_hiPU",15,50);  
  TH1D* hSIG_pfRelIso03_hiPU  = h2_SIG_pfRelIso03->ProjectionY("hSIG_pfRelIso03_hiPU",15,50);  
  TH1D* hSIG_pfRelIso04_hiPU  = h2_SIG_pfRelIso04->ProjectionY("hSIG_pfRelIso04_hiPU",15,50);  


  hSIG_pfRelIso02_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04_lowPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso02_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03_hiPU->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04_hiPU->GetXaxis()->SetRangeUser(0,1.0);

  c4->cd(1);
  gPad->SetLogy(); 
  hSIG_pfRelIso02_lowPU->SetLineColor(1);
  hSIG_pfRelIso02_lowPU->Draw();
  hSIG_pfRelIso02_hiPU->SetLineColor(6);
  hSIG_pfRelIso02_hiPU->Draw("same");
  c4->cd(2);
  gPad->SetLogy(); 
  hSIG_pfRelIso03_lowPU->SetLineColor(2);
  hSIG_pfRelIso03_lowPU->Draw();
  hSIG_pfRelIso03_hiPU->SetLineColor(28);
  hSIG_pfRelIso03_hiPU->Draw("same");
  c4->cd(3);
  gPad->SetLogy(); 
  hSIG_pfRelIso04_lowPU->SetLineColor(4);
  hSIG_pfRelIso04_lowPU->Draw();
  hSIG_pfRelIso04_hiPU->SetLineColor(8);
  hSIG_pfRelIso04_hiPU->Draw("same");
  c4->cd(4);
  gPad->SetLogy(); 
  hSIG_pfRelIso02_lowPU->Draw();
  hSIG_pfRelIso03_lowPU->Draw("same");
  hSIG_pfRelIso04_lowPU->Draw("same");
  hSIG_pfRelIso02_hiPU->Draw("same");
  hSIG_pfRelIso03_hiPU->Draw("same");
  hSIG_pfRelIso04_hiPU->Draw("same");

  c4->Print(plots+"signal.png");
  c4->Print(plots+"signal.pdf");

  TCanvas *c42=new TCanvas("c42","SIG()",400,400);
  gPad->SetLogy();
  hSIG_pfRelIso04_lowPU->Draw();
  hSIG_pfRelIso03_lowPU->Draw("same");
  hSIG_pfRelIso02_lowPU->Draw("same");
  hSIG_pfRelIso02_lowPU->GetXaxis()->SetTitle("RelIso");
  hSIG_pfRelIso03_lowPU->GetXaxis()->SetTitle("RelIso");
  hSIG_pfRelIso04_lowPU->GetXaxis()->SetTitle("RelIso");

  c42->Print(plots+"PUsignal2.png");
  c42->Print(plots+"PUsignal2.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5 = new TCanvas("c5","ROC-SIG_QCD",400,400);
  c5->SetTickx();
  c5->SetTicky();

  gROC_SIG03_lowPU = ROC(hSIG_pfRelIso03_lowPU, hQCD_pfRelIso03_lowPU);
  gROC_SIG04_lowPU = ROC(hSIG_pfRelIso04_lowPU, hQCD_pfRelIso04_lowPU);
  gROC_SIG03_hiPU = ROC(hSIG_pfRelIso03_hiPU, hQCD_pfRelIso03_hiPU);
  gROC_SIG04_hiPU = ROC(hSIG_pfRelIso04_hiPU, hQCD_pfRelIso04_hiPU);

  GraphStyle(gROC_SIG03_lowPU, 2, 23);
  GraphStyle(gROC_SIG04_lowPU, 4, 22);
  GraphStyle(gROC_SIG03_hiPU, 28, 2);
  GraphStyle(gROC_SIG04_hiPU, 8, 5);

  gROC_SIG04_lowPU->GetXaxis()->SetRangeUser(0,0.15);
  gROC_SIG04_lowPU->SetMaximum(0.96);
  gROC_SIG04_lowPU->SetMinimum(0.6);

  gROC_SIG04_lowPU->Draw("ACP");
  gROC_SIG03_lowPU->Draw("CPsame");
  gROC_SIG04_hiPU->Draw("CPsame");
  gROC_SIG03_hiPU->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gROC_SIG03_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gROC_SIG04_lowPU, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gROC_SIG03_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gROC_SIG04_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TGraphAsymmErrors* gr03_lowPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_lowPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr03_hiPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_hiPU = new TGraphAsymmErrors();

  double effQcd3,effSignal3,effQcd4,effSignal4;
  double effQcd3high,effSignal3high,effQcd4high,effSignal4high;
  gROC_SIG03_lowPU->GetPoint(14,effQcd3,effSignal3);
  gROC_SIG04_lowPU->GetPoint(19,effQcd4,effSignal4);
  gROC_SIG03_hiPU->GetPoint(14,effQcd3high,effSignal3high);
  gROC_SIG04_hiPU->GetPoint(19,effQcd4high,effSignal4high);

  gr03_lowPU->SetPoint(1, effQcd3,effSignal3);
  gr04_lowPU->SetPoint(1, effQcd4,effSignal4);
  gr03_hiPU->SetPoint(1, effQcd3high,effSignal3high);
  gr04_hiPU->SetPoint(1, effQcd4high,effSignal4high);

  gr03_lowPU->SetMarkerStyle(34);
  gr03_lowPU->SetMarkerSize(2.5);
  gr03_lowPU->SetMarkerColor(2);
  gr03_lowPU->SetLineWidth(3);
  gr04_lowPU->SetMarkerStyle(34);
  gr04_lowPU->SetMarkerSize(2.5);
  gr04_lowPU->SetMarkerColor(4);
  gr04_lowPU->SetLineWidth(3);
  gr03_hiPU->SetMarkerStyle(34);
  gr03_hiPU->SetMarkerSize(2.5);
  gr03_hiPU->SetMarkerColor(28);
  gr03_hiPU->SetLineWidth(3);
  gr04_hiPU->SetMarkerStyle(34);
  gr04_hiPU->SetMarkerSize(2.5);
  gr04_hiPU->SetMarkerColor(8);
  gr04_hiPU->SetLineWidth(3);

  gr03_lowPU->Draw("P");
  gr04_lowPU->Draw("Psame");
  gr03_hiPU->Draw("Psame");
  gr04_hiPU->Draw("Psame");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"No Delta-beta Correction");
  label->Draw();

  c5->Print(plots+"PUroc.png");
  c5->Print(plots+"PUroc.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5db = new TCanvas("c5db","ROC-SIG_QCD-db",400,400);
  c5db->SetTickx();
  c5db->SetTicky();

  gROC_SIG03_lowPUdb = ROC(hSIG_pfRelIso03db_lowPU, hQCD_pfRelIso03db_lowPU);
  gROC_SIG04_lowPUdb = ROC(hSIG_pfRelIso04db_lowPU, hQCD_pfRelIso04db_lowPU);
  gROC_SIG03_hiPUdb = ROC(hSIG_pfRelIso03db_hiPU, hQCD_pfRelIso03db_hiPU);
  gROC_SIG04_hiPUdb = ROC(hSIG_pfRelIso04db_hiPU, hQCD_pfRelIso04db_hiPU);

  GraphStyle(gROC_SIG03_lowPUdb, 2, 23);
  GraphStyle(gROC_SIG04_lowPUdb, 4, 22);
  GraphStyle(gROC_SIG03_hiPUdb, 28, 2);
  GraphStyle(gROC_SIG04_hiPUdb, 8, 5);

  gROC_SIG04_lowPUdb->GetXaxis()->SetRangeUser(0,0.15);
  gROC_SIG04_lowPUdb->SetMaximum(0.96);
  gROC_SIG04_lowPUdb->SetMinimum(0.6);

  gROC_SIG04_lowPUdb->Draw("ACP");
  gROC_SIG03_lowPUdb->Draw("CPsame");
  gROC_SIG04_hiPUdb->Draw("CPsame");
  gROC_SIG03_hiPUdb->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gROC_SIG03_lowPUdb, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gROC_SIG04_lowPUdb, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gROC_SIG03_hiPUdb, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gROC_SIG04_hiPUdb, l, "Cone R=0.4 (high PU)","PL");

  TGraphAsymmErrors* gr03_lowPUdb = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_lowPUdb = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr03_hiPUdb = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_hiPUdb = new TGraphAsymmErrors();

  double effQcd3,effSignal3,effQcd4,effSignal4;
  double effQcd3high,effSignal3high,effQcd4high,effSignal4high;
  gROC_SIG03_lowPUdb->GetPoint(14,effQcd3,effSignal3);
  gROC_SIG04_lowPUdb->GetPoint(19,effQcd4,effSignal4);
  gROC_SIG03_hiPUdb->GetPoint(14,effQcd3high,effSignal3high);
  gROC_SIG04_hiPUdb->GetPoint(19,effQcd4high,effSignal4high);

  gr03_lowPUdb->SetPoint(1, effQcd3,effSignal3);
  gr04_lowPUdb->SetPoint(1, effQcd4,effSignal4);
  gr03_hiPUdb->SetPoint(1, effQcd3high,effSignal3high);
  gr04_hiPUdb->SetPoint(1, effQcd4high,effSignal4high);

  gr03_lowPUdb->SetMarkerStyle(34);
  gr03_lowPUdb->SetMarkerSize(2.5);
  gr03_lowPUdb->SetMarkerColor(2);
  gr03_lowPUdb->SetLineWidth(3);
  gr04_lowPUdb->SetMarkerStyle(34);
  gr04_lowPUdb->SetMarkerSize(2.5);
  gr04_lowPUdb->SetMarkerColor(4);
  gr04_lowPUdb->SetLineWidth(3);
  gr03_hiPUdb->SetMarkerStyle(34);
  gr03_hiPUdb->SetMarkerSize(2.5);
  gr03_hiPUdb->SetMarkerColor(28);
  gr03_hiPUdb->SetLineWidth(3);
  gr04_hiPUdb->SetMarkerStyle(34);
  gr04_hiPUdb->SetMarkerSize(2.5);
  gr04_hiPUdb->SetMarkerColor(8);
  gr04_hiPUdb->SetLineWidth(3);

  gr03_lowPUdb->Draw("P");
  gr04_lowPUdb->Draw("Psame");
  gr03_hiPUdb->Draw("Psame");
  gr04_hiPUdb->Draw("Psame");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"Delta-beta Correction");
  label->Draw();

  c5db->Print(plots+"PUrocdb.png");
  c5db->Print(plots+"PUrocdb.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5low = new TCanvas("c5low","ROC-SIG_QCD-low",400,400);
  c5low->SetTickx();
  c5low->SetTicky();

  gROC_SIG03_lowPU = ROC(hSIG_pfRelIso03_lowPU, hQCD_pfRelIso03_lowPU);
  gROC_SIG04_lowPU = ROC(hSIG_pfRelIso04_lowPU, hQCD_pfRelIso04_lowPU);
  gROC_SIG03_lowPUdb = ROC(hSIG_pfRelIso03db_lowPU, hQCD_pfRelIso03db_lowPU);
  gROC_SIG04_lowPUdb = ROC(hSIG_pfRelIso04db_lowPU, hQCD_pfRelIso04db_lowPU);

  GraphStyle(gROC_SIG03_lowPU, 2, 23);
  GraphStyle(gROC_SIG04_lowPU, 4, 22);
  GraphStyle(gROC_SIG03_lowPUdb, 28, 2);
  GraphStyle(gROC_SIG04_lowPUdb, 8, 5);

  gROC_SIG04_lowPU->GetXaxis()->SetRangeUser(0,0.15);
  gROC_SIG04_lowPU->SetMaximum(0.96);
  gROC_SIG04_lowPU->SetMinimum(0.6);

  gROC_SIG04_lowPU->Draw("ACP");
  gROC_SIG03_lowPU->Draw("CPsame");
  gROC_SIG04_lowPUdb->Draw("CPsame");
  gROC_SIG03_lowPUdb->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.53,0.83,0.43);
  DrawLegend(gROC_SIG03_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gROC_SIG04_lowPU, l, "Cone R=0.4 (low PU)","PL");

  TLegend *l2= new TLegend(0.45,0.33,0.83,0.23);
  DrawLegend(gROC_SIG03_lowPUdb, l2, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gROC_SIG04_lowPUdb, l2, "Cone R=0.4 (low PU)","PL");

  TGraphAsymmErrors* gr03_lowPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_lowPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr03_lowPUdb = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_lowPUdb = new TGraphAsymmErrors();

  double effQcd3,effSignal3,effQcd4,effSignal4;
  double effQcd3high,effSignal3high,effQcd4high,effSignal4high;
  gROC_SIG03_lowPU->GetPoint(14,effQcd3,effSignal3);
  gROC_SIG04_lowPU->GetPoint(19,effQcd4,effSignal4);
  gROC_SIG03_lowPUdb->GetPoint(14,effQcd3high,effSignal3high);
  gROC_SIG04_lowPUdb->GetPoint(19,effQcd4high,effSignal4high);

  gr03_lowPU->SetPoint(1, effQcd3,effSignal3);
  gr04_lowPU->SetPoint(1, effQcd4,effSignal4);
  gr03_lowPUdb->SetPoint(1, effQcd3high,effSignal3high);
  gr04_lowPUdb->SetPoint(1, effQcd4high,effSignal4high);

  gr03_lowPU->SetMarkerStyle(34);
  gr03_lowPU->SetMarkerSize(2.5);
  gr03_lowPU->SetMarkerColor(2);
  gr03_lowPU->SetLineWidth(3);
  gr04_lowPU->SetMarkerStyle(34);
  gr04_lowPU->SetMarkerSize(2.5);
  gr04_lowPU->SetMarkerColor(4);
  gr04_lowPU->SetLineWidth(3);
  gr03_lowPUdb->SetMarkerStyle(34);
  gr03_lowPUdb->SetMarkerSize(2.5);
  gr03_lowPUdb->SetMarkerColor(28);
  gr03_lowPUdb->SetLineWidth(3);
  gr04_lowPUdb->SetMarkerStyle(34);
  gr04_lowPUdb->SetMarkerSize(2.5);
  gr04_lowPUdb->SetMarkerColor(8);
  gr04_lowPUdb->SetLineWidth(3);

  gr03_lowPU->Draw("P");
  gr04_lowPU->Draw("Psame");
  gr03_lowPUdb->Draw("Psame");
  gr04_lowPUdb->Draw("Psame");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.55,"No Delta-beta Correction");
  label->Draw();

  TLatex *label2= new TLatex;
  label2->SetNDC();
  label2->SetTextSize(0.04);
  label2->DrawLatex(0.45,0.35,"Delta-beta Correction");
  label2->Draw();

  c5low->Print(plots+"PUroclow.png");
  c5low->Print(plots+"PUroclow.pdf");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5high = new TCanvas("c5high","ROC-SIG_QCD-high",400,400);
  c5high->SetTickx();
  c5high->SetTicky();

  gROC_SIG03_hiPU = ROC(hSIG_pfRelIso03_hiPU, hQCD_pfRelIso03_hiPU);
  gROC_SIG04_hiPU = ROC(hSIG_pfRelIso04_hiPU, hQCD_pfRelIso04_hiPU);
  gROC_SIG03_hiPUdb = ROC(hSIG_pfRelIso03db_hiPU, hQCD_pfRelIso03db_hiPU);
  gROC_SIG04_hiPUdb = ROC(hSIG_pfRelIso04db_hiPU, hQCD_pfRelIso04db_hiPU);

  GraphStyle(gROC_SIG03_hiPU, 2, 23);
  GraphStyle(gROC_SIG04_hiPU, 4, 22);
  GraphStyle(gROC_SIG03_hiPUdb, 28, 2);
  GraphStyle(gROC_SIG04_hiPUdb, 8, 5);

  gROC_SIG04_hiPU->GetXaxis()->SetRangeUser(0,0.15);
  gROC_SIG04_hiPU->SetMaximum(0.96);
  gROC_SIG04_hiPU->SetMinimum(0.6);

  gROC_SIG04_hiPU->Draw("ACP");
  gROC_SIG03_hiPU->Draw("CPsame");
  gROC_SIG04_hiPUdb->Draw("CPsame");
  gROC_SIG03_hiPUdb->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.53,0.83,0.43);
  DrawLegend(gROC_SIG03_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gROC_SIG04_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TLegend *l2= new TLegend(0.45,0.33,0.83,0.23);
  DrawLegend(gROC_SIG03_hiPUdb, l2, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gROC_SIG04_hiPUdb, l2, "Cone R=0.4 (high PU)","PL");

  TGraphAsymmErrors* gr03_hiPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_hiPU = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr03_hiPUdb = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr04_hiPUdb = new TGraphAsymmErrors();

  double effQcd3,effSignal3,effQcd4,effSignal4;
  double effQcd3high,effSignal3high,effQcd4high,effSignal4high;
  gROC_SIG03_hiPU->GetPoint(14,effQcd3,effSignal3);
  gROC_SIG04_hiPU->GetPoint(19,effQcd4,effSignal4);
  gROC_SIG03_hiPUdb->GetPoint(14,effQcd3high,effSignal3high);
  gROC_SIG04_hiPUdb->GetPoint(19,effQcd4high,effSignal4high);

  gr03_hiPU->SetPoint(1, effQcd3,effSignal3);
  gr04_hiPU->SetPoint(1, effQcd4,effSignal4);
  gr03_hiPUdb->SetPoint(1, effQcd3high,effSignal3high);
  gr04_hiPUdb->SetPoint(1, effQcd4high,effSignal4high);

  gr03_hiPU->SetMarkerStyle(34);
  gr03_hiPU->SetMarkerSize(2.5);
  gr03_hiPU->SetMarkerColor(2);
  gr03_hiPU->SetLineWidth(3);
  gr04_hiPU->SetMarkerStyle(34);
  gr04_hiPU->SetMarkerSize(2.5);
  gr04_hiPU->SetMarkerColor(4);
  gr04_hiPU->SetLineWidth(3);
  gr03_hiPUdb->SetMarkerStyle(34);
  gr03_hiPUdb->SetMarkerSize(2.5);
  gr03_hiPUdb->SetMarkerColor(28);
  gr03_hiPUdb->SetLineWidth(3);
  gr04_hiPUdb->SetMarkerStyle(34);
  gr04_hiPUdb->SetMarkerSize(2.5);
  gr04_hiPUdb->SetMarkerColor(8);
  gr04_hiPUdb->SetLineWidth(3);

  gr03_hiPU->Draw("P");
  gr04_hiPU->Draw("Psame");
  gr03_hiPUdb->Draw("Psame");
  gr04_hiPUdb->Draw("Psame");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.55,"No Delta-beta Correction");
  label->Draw();

  TLatex *label2= new TLatex;
  label2->SetNDC();
  label2->SetTextSize(0.04);
  label2->DrawLatex(0.45,0.35,"Delta-beta Correction");
  label2->Draw();

  c5high->Print(plots+"PUrochigh.png");
  c5high->Print(plots+"PUrochigh.pdf");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5eff = new TCanvas("c5eff","IsoEff-SIG",400,400);
  c5eff->SetTickx();
  c5eff->SetTicky();

  gEFF_SIG03_lowPU = EFF(hSIG_pfRelIso03_lowPU);
  gEFF_SIG04_lowPU = EFF(hSIG_pfRelIso04_lowPU);
  gEFF_SIG03_hiPU = EFF(hSIG_pfRelIso03_hiPU);
  gEFF_SIG04_hiPU = EFF(hSIG_pfRelIso04_hiPU);

  GraphStyleEff(gEFF_SIG03_lowPU, 2, 23);
  GraphStyleEff(gEFF_SIG04_lowPU, 4, 22);
  GraphStyleEff(gEFF_SIG03_hiPU, 28, 2);
  GraphStyleEff(gEFF_SIG04_hiPU, 8, 5);

  gEFF_SIG04_lowPU->GetXaxis()->SetRangeUser(0,0.4);
  gEFF_SIG04_lowPU->SetMinimum(0.3);
  gEFF_SIG04_lowPU->SetMaximum(1);

  gEFF_SIG04_lowPU->Draw("ACP");
  gEFF_SIG03_lowPU->Draw("CPsame");
  gEFF_SIG04_hiPU->Draw("CPsame");
  gEFF_SIG03_hiPU->Draw("CPsame");

  TLegend *l= new TLegend(0.45,0.38,0.83,0.18);
  DrawLegend(gEFF_SIG03_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gEFF_SIG04_lowPU, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gEFF_SIG03_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gEFF_SIG04_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"No Delta-beta Correction");
  label->Draw();

  c5eff->Print(plots+"PUSIG_efficiency.png");
  c5eff->Print(plots+"PUSIG_efficiency.pdf");

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

  gEFF_SIG04db_lowPU->GetXaxis()->SetRangeUser(0,0.4);
  gEFF_SIG04db_lowPU->SetMinimum(0.3);
  gEFF_SIG04db_lowPU->SetMaximum(1);

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

  TCanvas *c5effQCD = new TCanvas("c5effQCD","IsoEff-QCD",400,400);
  c5effQCD->SetTickx();
  c5effQCD->SetTicky();

  gEFF_QCD03_lowPU = EFF(hQCD_pfRelIso03_lowPU);
  gEFF_QCD04_lowPU = EFF(hQCD_pfRelIso04_lowPU);
  gEFF_QCD03_hiPU = EFF(hQCD_pfRelIso03_hiPU);
  gEFF_QCD04_hiPU = EFF(hQCD_pfRelIso04_hiPU);

  GraphStyleEff(gEFF_QCD03_lowPU, 2, 23);
  GraphStyleEff(gEFF_QCD04_lowPU, 4, 22);
  GraphStyleEff(gEFF_QCD03_hiPU, 28, 2);
  GraphStyleEff(gEFF_QCD04_hiPU, 8, 5);

  gEFF_QCD04_lowPU->GetXaxis()->SetRangeUser(0,0.4);
  gEFF_QCD04_lowPU->SetMinimum(0);
  gEFF_QCD04_lowPU->SetMaximum(1);

  gEFF_QCD04_lowPU->Draw("ACP");
  gEFF_QCD03_lowPU->Draw("CPsame");
  gEFF_QCD04_hiPU->Draw("CPsame");
  gEFF_QCD03_hiPU->Draw("CPsame");

  TLegend *l= new TLegend(0.22,0.62,0.60,0.82);
  DrawLegend(gEFF_QCD03_lowPU, l, "Cone R=0.3 (low PU)","PL");
  DrawLegend(gEFF_QCD04_lowPU, l, "Cone R=0.4 (low PU)","PL");
  DrawLegend(gEFF_QCD03_hiPU, l, "Cone R=0.3 (high PU)","PL");
  DrawLegend(gEFF_QCD04_hiPU, l, "Cone R=0.4 (high PU)","PL");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.22,0.84,"No Delta-beta Correction");
  label->Draw();

  c5effQCD->Print(plots+"PUQCD_efficiency.png");
  c5effQCD->Print(plots+"PUQCD_efficiency.pdf");

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
  gEFF_QCD04db_lowPU->SetMaximum(1);

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

  TCanvas *c5sig = new TCanvas("c5sig","RDSignificance S/sqrt(S+B)",400,400);
  double xmax =0.4;
  double ymin=0.85;
  double ymax=0.905;
  TH1F* h3=new TH1F("h3","Significance for cone 0.3",40,0,xmax);
  TH1F* h4=new TH1F("h4","Significance for cone 0.4",40,0,xmax);
  TH1F* h33=new TH1F("h33","Significance for cone 0.3",40,0,xmax);
  TH1F* h44=new TH1F("h44","Significance for cone 0.4",40,0,xmax);

  for (int i=0; i<41;i++){
    double eff_signal3low,eff_signal4low;
    double eff_qcd3low,eff_qcd4low;
    double eff_signal3hi,eff_signal4hi;
    double eff_qcd3hi,eff_qcd4hi;

    gROC_SIG03_lowPU->GetPoint(i,eff_qcd3low,eff_signal3low);
    gROC_SIG04_lowPU->GetPoint(i,eff_qcd4low,eff_signal4low);
    gROC_SIG03_hiPU->GetPoint(i,eff_qcd3hi,eff_signal3hi);
    gROC_SIG04_hiPU->GetPoint(i,eff_qcd4hi,eff_signal4hi);

    double soverb3low = eff_signal3low/sqrt(eff_signal3low+eff_qcd3low);
    double soverb4low = eff_signal4low/sqrt(eff_signal4low+eff_qcd4low);
    double soverb3hi = eff_signal3hi/sqrt(eff_signal3hi+eff_qcd3hi);
    double soverb4hi = eff_signal4hi/sqrt(eff_signal4hi+eff_qcd4hi);

    h3->SetBinContent(i,soverb3low);
    h4->SetBinContent(i,soverb4low);
    h33->SetBinContent(i,soverb3hi);
    h44->SetBinContent(i,soverb4hi);
  }
/////

//  gPad->SetGridx();
//  gPad->SetGridy();

  h3->SetLineColor(2);
  h4->SetLineColor(4);
  h33->SetLineColor(28);
  h44->SetLineColor(8);
  h4->SetMinimum(ymin);
  h4->SetMaximum(ymax);
  h4->GetXaxis()->SetTitle("Isolation Threshold");
  h4->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  h4->Draw();
  h3->Draw("same");
  h33->Draw("same");
  h44->Draw("same");

  TLegend *l= new TLegend(0.45,0.38,0.88,0.18);
  DrawLegendHisto(h3, l, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(h4, l, "Cone R=0.4 (low PU)","L");
  DrawLegendHisto(h33, l, "Cone R=0.3 (high PU)","L");
  DrawLegendHisto(h44, l, "Cone R=0.4 (high PU)","L");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"No Delta-beta Correction");
  label->Draw();

  c5sig->Print(plots+"PUsignificance.png");
  c5sig->Print(plots+"PUsignificance.pdf");

///////////////////////////////////////////////////////////////////////////////

  TCanvas *c5sigdb = new TCanvas("c5sigdb","RDSignificancedb S/sqrt(S+B)",400,400);
  double xmax =0.4;
  double ymin=0.85;
  double ymax=0.905;
  TH1F* h3db=new TH1F("h3db","Significance for cone 0.3",40,0,xmax);
  TH1F* h4db=new TH1F("h4db","Significance for cone 0.4",40,0,xmax);
  TH1F* h33db=new TH1F("h33db","Significance for cone 0.3",40,0,xmax);
  TH1F* h44db=new TH1F("h44db","Significance for cone 0.4",40,0,xmax);

  for (int i=0; i<41;i++){
    double eff_signal3low,eff_signal4low;
    double eff_qcd3low,eff_qcd4low;
    double eff_signal3hi,eff_signal4hi;
    double eff_qcd3hi,eff_qcd4hi;

    gROC_SIG03_lowPUdb->GetPoint(i,eff_qcd3low,eff_signal3low);
    gROC_SIG04_lowPUdb->GetPoint(i,eff_qcd4low,eff_signal4low);
    gROC_SIG03_hiPUdb->GetPoint(i,eff_qcd3hi,eff_signal3hi);
    gROC_SIG04_hiPUdb->GetPoint(i,eff_qcd4hi,eff_signal4hi);

    double soverb3low = eff_signal3low/sqrt(eff_signal3low+eff_qcd3low);
    double soverb4low = eff_signal4low/sqrt(eff_signal4low+eff_qcd4low);
    double soverb3hi = eff_signal3hi/sqrt(eff_signal3hi+eff_qcd3hi);
    double soverb4hi = eff_signal4hi/sqrt(eff_signal4hi+eff_qcd4hi);

    h3db->SetBinContent(i,soverb3low);
    h4db->SetBinContent(i,soverb4low);
    h33db->SetBinContent(i,soverb3hi);
    h44db->SetBinContent(i,soverb4hi);
  }
/////

//  gPad->SetGridx();
//  gPad->SetGridy();
  h3db->SetLineColor(2);
  h4db->SetLineColor(4);
  h33db->SetLineColor(28);
  h44db->SetLineColor(8);
  h4db->SetMinimum(ymin);
  h4db->SetMaximum(ymax);
  h4db->GetXaxis()->SetTitle("Isolation Threshold");
  h4db->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  h4db->Draw();
  h3db->Draw("same");
  h33db->Draw("same");
  h44db->Draw("same");

  TLegend *l= new TLegend(0.45,0.38,0.88,0.18);
  DrawLegendHisto(h3db, l, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(h4db, l, "Cone R=0.4 (low PU)","L");
  DrawLegendHisto(h33db, l, "Cone R=0.3 (high PU)","L");
  DrawLegendHisto(h44db, l, "Cone R=0.4 (high PU)","L");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.40,"Delta-beta Correction");
  label->Draw();

  c5sigdb->Print(plots+"PUsignificancedb.png");
  c5sigdb->Print(plots+"PUsignificancedb.pdf");

///////////////////////////////////////////////////////////////////////////////

  TCanvas *c5siglow = new TCanvas("c5siglow","RDSignificance S/sqrt(S+B) low pile-up",400,400);
  double xmax =0.4;
  double ymin=0.85;
  double ymax=0.905;
  TH1F* h3=new TH1F("h3","Significance for cone 0.3",40,0,xmax);
  TH1F* h4=new TH1F("h4","Significance for cone 0.4",40,0,xmax);
  TH1F* h33=new TH1F("h33","Significance for cone 0.3",40,0,xmax);
  TH1F* h44=new TH1F("h44","Significance for cone 0.4",40,0,xmax);

  for (int i=0; i<41;i++){
    double eff_signal3low,eff_signal4low;
    double eff_qcd3low,eff_qcd4low;
    double eff_signal3lowdb,eff_signal4lowdb;
    double eff_qcd3lowdb,eff_qcd4lowdb;

    gROC_SIG03_lowPU->GetPoint(i,eff_qcd3low,eff_signal3low);
    gROC_SIG04_lowPU->GetPoint(i,eff_qcd4low,eff_signal4low);
    gROC_SIG03_lowPUdb->GetPoint(i,eff_qcd3lowdb,eff_signal3lowdb);
    gROC_SIG04_lowPUdb->GetPoint(i,eff_qcd4lowdb,eff_signal4lowdb);

    double soverb3low = eff_signal3low/sqrt(eff_signal3low+eff_qcd3low);
    double soverb4low = eff_signal4low/sqrt(eff_signal4low+eff_qcd4low);
    double soverb3lowdb = eff_signal3lowdb/sqrt(eff_signal3lowdb+eff_qcd3lowdb);
    double soverb4lowdb = eff_signal4lowdb/sqrt(eff_signal4lowdb+eff_qcd4lowdb);

    h3->SetBinContent(i,soverb3low);
    h4->SetBinContent(i,soverb4low);
    h33->SetBinContent(i,soverb3lowdb);
    h44->SetBinContent(i,soverb4lowdb);
  }
/////

//  gPad->SetGridx();
//  gPad->SetGridy();

  h3->SetLineColor(2);
  h4->SetLineColor(4);
  h33->SetLineColor(28);
  h44->SetLineColor(8);
  h4->SetMinimum(ymin);
  h4->SetMaximum(ymax);
  h4->GetXaxis()->SetTitle("Isolation Threshold");
  h4->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  h4->Draw();
  h3->Draw("same");
  h33->Draw("same");
  h44->Draw("same");

  TLegend *l= new TLegend(0.45,0.53,0.83,0.43);
  DrawLegendHisto(h3, l, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(h4, l, "Cone R=0.4 (low PU)","L");

  TLegend *l2= new TLegend(0.45,0.33,0.83,0.23);
  DrawLegendHisto(h33, l2, "Cone R=0.3 (low PU)","L");
  DrawLegendHisto(h44, l2, "Cone R=0.4 (low PU)","L");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.55,"No Delta-beta Correction");
  label->Draw();

  TLatex *label2= new TLatex;
  label2->SetNDC();
  label2->SetTextSize(0.04);
  label2->DrawLatex(0.45,0.35,"Delta-beta Correction");
  label2->Draw();

  c5siglow->Print(plots+"PUsignificancelow.png");
  c5siglow->Print(plots+"PUsignificancelow.pdf");

///////////////////////////////////////////////////////////////////////////////

  TCanvas *c5sighigh = new TCanvas("c5sighigh","RDSignificance S/sqrt(S+B) high pile-up",400,400);
  double xmax =0.4;
  double ymin=0.85;
  double ymax=0.905;
  TH1F* h3=new TH1F("h3","Significance for cone 0.3",40,0,xmax);
  TH1F* h4=new TH1F("h4","Significance for cone 0.4",40,0,xmax);
  TH1F* h33=new TH1F("h33","Significance for cone 0.3",40,0,xmax);
  TH1F* h44=new TH1F("h44","Significance for cone 0.4",40,0,xmax);

  for (int i=0; i<41;i++){
    double eff_signal3hi,eff_signal4hi;
    double eff_qcd3hi,eff_qcd4hi;
    double eff_signal3hidb,eff_signal4hidb;
    double eff_qcd3hidb,eff_qcd4hidb;

    gROC_SIG03_hiPU->GetPoint(i,eff_qcd3hi,eff_signal3hi);
    gROC_SIG04_hiPU->GetPoint(i,eff_qcd4hi,eff_signal4hi);
    gROC_SIG03_hiPUdb->GetPoint(i,eff_qcd3hidb,eff_signal3hidb);
    gROC_SIG04_hiPUdb->GetPoint(i,eff_qcd4hidb,eff_signal4hidb);

    double soverb3hi = eff_signal3hi/sqrt(eff_signal3hi+eff_qcd3hi);
    double soverb4hi = eff_signal4hi/sqrt(eff_signal4hi+eff_qcd4hi);
    double soverb3hidb = eff_signal3hidb/sqrt(eff_signal3hidb+eff_qcd3hidb);
    double soverb4hidb = eff_signal4hidb/sqrt(eff_signal4hidb+eff_qcd4hidb);

    h3->SetBinContent(i,soverb3hi);
    h4->SetBinContent(i,soverb4hi);
    h33->SetBinContent(i,soverb3hidb);
    h44->SetBinContent(i,soverb4hidb);
  }
/////

//  gPad->SetGridx();
//  gPad->SetGridy();

  h3->SetLineColor(2);
  h4->SetLineColor(4);
  h33->SetLineColor(28);
  h44->SetLineColor(8);
  h4->SetMinimum(ymin);
  h4->SetMaximum(ymax);
  h4->GetXaxis()->SetTitle("Isolation Threshold");
  h4->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  h4->Draw();
  h3->Draw("same");
  h33->Draw("same");
  h44->Draw("same");

  TLegend *l= new TLegend(0.45,0.53,0.83,0.43);
  DrawLegendHisto(h3, l, "Cone R=0.3 (high PU)","L");
  DrawLegendHisto(h4, l, "Cone R=0.4 (high PU)","L");

  TLegend *l2= new TLegend(0.45,0.33,0.83,0.23);
  DrawLegendHisto(h33, l2, "Cone R=0.3 (high PU)","L");
  DrawLegendHisto(h44, l2, "Cone R=0.4 (high PU)","L");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.45,0.55,"No Delta-beta Correction");
  label->Draw();

  TLatex *label2= new TLatex;
  label2->SetNDC();
  label2->SetTextSize(0.04);
  label2->DrawLatex(0.45,0.35,"Delta-beta Correction");
  label2->Draw();

  c5sighigh->Print(plots+"PUsignificancehigh.png");
  c5sighigh->Print(plots+"PUsignificancehigh.pdf");


////////////////////////////////////////////////////////////////////////////////

}
