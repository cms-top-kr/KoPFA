#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void DrawLegend(TGraphAsymmErrors* g, TLegend* l, const TString ID_Algo,TString opt){
  //TLegend *l= new TLegend(loc);
  l->AddEntry(g,ID_Algo,opt);
  l->SetTextSize(0.03);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void GraphStyle(TGraphAsymmErrors* g, int c, int mstyle){
  g->SetLineWidth(2);
  //g->SetLineStyle(lstyle);
  g->SetLineColor(c);
  g->SetMarkerStyle(mstyle);
  g->SetMarkerColor(c);
  g->SetMarkerSize(1.1);
  g->SetFillColor(c);
  //g->SetFillStyle(3001);
  g->GetXaxis()->SetTitle("QCD efficiency");
  g->GetYaxis()->SetTitle("Signal efficiency");
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
  g->GetYaxis()->SetTitle("Signal efficiency");
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
  for(int i=0 ; i < 41; i++){
    bin=i+1;
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
  for(int i=0 ; i < 41; i++){
    bin=i+1;
    double Si = hSignal->Integral(0,bin);
    double eff_signal = Si/ totalS; 
    out->SetPoint(i, 0.01*(i+1), eff_signal);
    //out->SetPointEXhigh(i,err_signal);
    //out->SetPointEXlow(i, err_signal);
  }   
  return out;
}

void isoOpt2012(){
  gROOT->LoadMacro("tdrStyle.C");
  setTDRStyle();

  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/CMGAnalyzer/prod/Out/03DEC_1jets/";

  TFile * fRD = new TFile("/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/CMGAnalyzer/prod/Out/etc/MuonIso_01DEC_Run2012MuMu.root");
  //TFile * fSIG = new TFile(srcDir+"vallot_ZJets.root");
  TFile * fSIG = new TFile(srcDir+"vallot_TTbarTuneZ2.root");
  TFile * fQCDmc = new TFile(srcDir+"vallot_QCDMuon.root");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2=new TCanvas("c2","QCD",800,800);
  c2->SetLogy();
  c2->Divide(2,2);

  TH1F * hQCD_Edncap_pfRelIso02 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso02");
  TH1F * hQCD_Barrel_pfRelIso02 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso02");
  TH1F * hQCD_pfRelIso02 = (TH1F*)hQCD_Edncap_pfRelIso02->Clone("hQCD_pfRelIso02");
  TH1F * hQCD_Edncap_pfRelIso03 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso03");
  TH1F * hQCD_Barrel_pfRelIso03 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso03");
  TH1F * hQCD_pfRelIso03 = (TH1F*)hQCD_Edncap_pfRelIso03->Clone("hQCD_pfRelIso03");
  TH1F * hQCD_Edncap_pfRelIso04 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso04");
  TH1F * hQCD_Barrel_pfRelIso04 = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso04");
  TH1F * hQCD_pfRelIso04 = (TH1F*)hQCD_Edncap_pfRelIso04->Clone("hQCD_pfRelIso04");

  hQCD_pfRelIso02->Add(hQCD_Barrel_pfRelIso02);
  hQCD_pfRelIso02->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02->SetTitle("hQCD_pfRelIso02");

  hQCD_pfRelIso03->Add(hQCD_Barrel_pfRelIso03);
  hQCD_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03->SetTitle("hQCD_pfRelIso03");

  hQCD_pfRelIso04->Add(hQCD_Barrel_pfRelIso04);
  hQCD_pfRelIso04->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04->SetTitle("hQCD_pfRelIso04");

/*
  TH1F * hQCD_pfRelIso02db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02db");
  TH1F * hQCD_pfRelIso03db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03db");
  TH1F * hQCD_pfRelIso04db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04db");

  hQCD_pfRelIso02db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02db->SetTitle("hQCD_pfRelIso02db");

  hQCD_pfRelIso03db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db->SetTitle("hQCD_pfRelIso03db");

  hQCD_pfRelIso04db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db->SetTitle("hQCD_pfRelIso04db");
*/

  c2->cd(1);
  gPad->SetLogy(); 
  hQCD_pfRelIso02->Draw();
  c2->cd(2);
  gPad->SetLogy(); 
  hQCD_pfRelIso03->SetLineColor(2);
  hQCD_pfRelIso03->Draw();
  c2->cd(3);
  gPad->SetLogy(); 
  hQCD_pfRelIso04->SetLineColor(4);
  hQCD_pfRelIso04->Draw();
  c2->cd(4);
  gPad->SetLogy();

  hQCD_pfRelIso02->SetMaximum(3000);
  hQCD_pfRelIso02->SetMinimum(50);
  hQCD_pfRelIso02->Draw();
  hQCD_pfRelIso03->Draw("same");
  hQCD_pfRelIso04->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2db=new TCanvas("c2db","QCD_db",800,800);
  c2db->SetLogy();
  c2db->Divide(2,2);

  TH1F * hQCD_Edncap_pfRelIso02db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso02db");
  TH1F * hQCD_Barrel_pfRelIso02db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso02db");
  TH1F * hQCD_pfRelIso02db = (TH1F*)hQCD_Edncap_pfRelIso02db->Clone("hQCD_pfRelIso02db");
  TH1F * hQCD_Edncap_pfRelIso03db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso03db");
  TH1F * hQCD_Barrel_pfRelIso03db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso03db");
  TH1F * hQCD_pfRelIso03db = (TH1F*)hQCD_Edncap_pfRelIso03db->Clone("hQCD_pfRelIso03db");
  TH1F * hQCD_Edncap_pfRelIso04db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Endcap/h_pfRelIso04db");
  TH1F * hQCD_Barrel_pfRelIso04db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/Barrel/h_pfRelIso04db");
  TH1F * hQCD_pfRelIso04db = (TH1F*)hQCD_Edncap_pfRelIso04db->Clone("hQCD_pfRelIso04db");

  hQCD_pfRelIso02db->Add(hQCD_Barrel_pfRelIso02db);
  hQCD_pfRelIso02db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02db->SetTitle("hQCD_Total_pfRelIso02db");

  hQCD_pfRelIso03db->Add(hQCD_Barrel_pfRelIso03db);
  hQCD_pfRelIso03db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db->SetTitle("hQCD_Total_pfRelIso03db");

  hQCD_pfRelIso04db->Add(hQCD_Barrel_pfRelIso04db);
  hQCD_pfRelIso04db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db->SetTitle("hQCD_Total_pfRelIso04db");
/*
  TH1F * hQCD_pfRelIso02db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02db");
  TH1F * hQCD_pfRelIso03db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03db");
  TH1F * hQCD_pfRelIso04db = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04db");

  hQCD_pfRelIso02db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso02db->SetTitle("hQCD_pfRelIso02db");

  hQCD_pfRelIso03db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso03db->SetTitle("hQCD_pfRelIso03db");

  hQCD_pfRelIso04db->GetXaxis()->SetRangeUser(0,1.0);
  hQCD_pfRelIso04db->SetTitle("hQCD_pfRelIso04db");
*/
  c2db->cd(1);
  gPad->SetLogy(); 
  hQCD_pfRelIso02db->Draw();
  c2db->cd(2);
  gPad->SetLogy(); 
  hQCD_pfRelIso03db->SetLineColor(2);
  hQCD_pfRelIso03db->Draw();
  c2db->cd(3);
  gPad->SetLogy(); 
  hQCD_pfRelIso04db->SetLineColor(4);
  hQCD_pfRelIso04db->Draw();
  c2db->cd(4);
  gPad->SetLogy();

  hQCD_pfRelIso02db->SetMaximum(3000);
  hQCD_pfRelIso02db->SetMinimum(50);
  hQCD_pfRelIso02db->Draw();
  hQCD_pfRelIso03db->Draw("same");
  hQCD_pfRelIso04db->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2qcdmc=new TCanvas("c2qcdmc","MC QCD",800,800);
  c2qcdmc->Divide(2,2);

  TH1F * hQCDmc_pfRelIso02 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hQCDmc_pfRelIso03 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hQCDmc_pfRelIso04 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");

  hQCDmc_pfRelIso02->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmc_pfRelIso02->SetTitle("hQCDmc_pfRelIso02");

  hQCDmc_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmc_pfRelIso03->SetTitle("hQCDmc_pfRelIso03");

  hQCDmc_pfRelIso04->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmc_pfRelIso04->SetTitle("hQCDmc_pfRelIso04");

  c2qcdmc->cd(1);
  gPad->SetLogy(); 
  hQCDmc_pfRelIso02->Draw();
  c2qcdmc->cd(2);
  gPad->SetLogy(); 
  hQCDmc_pfRelIso03->SetLineColor(2);
  hQCDmc_pfRelIso03->Draw();
  c2qcdmc->cd(3);
  gPad->SetLogy(); 
  hQCDmc_pfRelIso04->SetLineColor(4);
  hQCDmc_pfRelIso04->Draw();
  c2qcdmc->cd(4);
  gPad->SetLogy();

  hQCDmc_pfRelIso02->SetMaximum(3000);
  hQCDmc_pfRelIso02->SetMinimum(50);
  hQCDmc_pfRelIso02->Draw();
  hQCDmc_pfRelIso03->Draw("same");
  hQCDmc_pfRelIso04->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c2qcdmcdb=new TCanvas("c2qcdmcdb","mcdb QCD",800,800);
  c2qcdmcdb->Divide(2,2);

  TH1F * hQCDmcdb_pfRelIso02 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02db");
  TH1F * hQCDmcdb_pfRelIso03 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03db");
  TH1F * hQCDmcdb_pfRelIso04 = (TH1F*) fQCDmc->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04db");

  hQCDmcdb_pfRelIso02->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmcdb_pfRelIso02->SetTitle("hQCDmcdb_pfRelIso02");

  hQCDmcdb_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmcdb_pfRelIso03->SetTitle("hQCDmcdb_pfRelIso03");

  hQCDmcdb_pfRelIso04->GetXaxis()->SetRangeUser(0,1.0);
  hQCDmcdb_pfRelIso04->SetTitle("hQCDmcdb_pfRelIso04");

  c2qcdmcdb->cd(1);
  gPad->SetLogy(); 
  hQCDmcdb_pfRelIso02->Draw();
  c2qcdmcdb->cd(2);
  gPad->SetLogy(); 
  hQCDmcdb_pfRelIso03->SetLineColor(2);
  hQCDmcdb_pfRelIso03->Draw();
  c2qcdmcdb->cd(3);
  gPad->SetLogy(); 
  hQCDmcdb_pfRelIso04->SetLineColor(4);
  hQCDmcdb_pfRelIso04->Draw();
  c2qcdmcdb->cd(4);
  gPad->SetLogy();

  hQCDmcdb_pfRelIso02->SetMaximum(3000);
  hQCDmcdb_pfRelIso02->SetMinimum(50);
  hQCDmcdb_pfRelIso02->Draw();
  hQCDmcdb_pfRelIso03->Draw("same");
  hQCDmcdb_pfRelIso04->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c4db=new TCanvas("c4db","SIG_db",800,800);
  c4db->SetLogy();
  c4db->Divide(2,2);

  TH1F * hSIG_pfRelIso02db = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso02db");
  TH1F * hSIG_pfRelIso03db = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03db");
  TH1F * hSIG_pfRelIso04db = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04db");

  hSIG_pfRelIso02db->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03db->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04db->GetXaxis()->SetRangeUser(0,1.0);

  c4db->cd(1);
  gPad->SetLogy(); 
  hSIG_pfRelIso02db->SetLineColor(1);
  hSIG_pfRelIso02db->Draw();
  c4db->cd(2);
  gPad->SetLogy(); 
  hSIG_pfRelIso03db->SetLineColor(2);
  hSIG_pfRelIso03db->Draw();
  c4db->cd(3);
  gPad->SetLogy(); 
  hSIG_pfRelIso04db->SetLineColor(4);
  hSIG_pfRelIso04db->Draw();
  c4db->cd(4);
  gPad->SetLogy(); 
  hSIG_pfRelIso02db->Draw();
  hSIG_pfRelIso03db->Draw("same");
  hSIG_pfRelIso04db->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c4=new TCanvas("c4","SIG",800,800);
  c4->Divide(2,2);

  TH1F * hSIG_pfRelIso02 = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso02");
  TH1F * hSIG_pfRelIso03 = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hSIG_pfRelIso04 = (TH1F*) fSIG->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");

  hSIG_pfRelIso02->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  hSIG_pfRelIso04->GetXaxis()->SetRangeUser(0,1.0);

  c4->cd(1);
  gPad->SetLogy(); 
  hSIG_pfRelIso02->SetLineColor(1);
  hSIG_pfRelIso02->Draw();
  c4->cd(2);
  gPad->SetLogy(); 
  hSIG_pfRelIso03->SetLineColor(2);
  hSIG_pfRelIso03->Draw();
  c4->cd(3);
  gPad->SetLogy(); 
  hSIG_pfRelIso04->SetLineColor(4);
  hSIG_pfRelIso04->Draw();
  c4->cd(4);
  gPad->SetLogy(); 
  hSIG_pfRelIso02->Draw();
  hSIG_pfRelIso03->Draw("same");
  hSIG_pfRelIso04->Draw("same");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5 = new TCanvas("c5","ROC-SIG",600,600);
  c5->SetTickx();
  c5->SetTicky();

  gROC_SIG03 = ROC(hSIG_pfRelIso03, hQCD_pfRelIso03);
  gROC_SIG04 = ROC(hSIG_pfRelIso04, hQCD_pfRelIso04);

  GraphStyle(gROC_SIG03, 2, 21);
  GraphStyle(gROC_SIG04, 4, 22);

  gROC_SIG04->GetXaxis()->SetRangeUser(0,0.06);

  gROC_SIG04->Draw("ACP");
  gROC_SIG03->Draw("CPsame");

  TLegend *l3= new TLegend(0.45,0.18,0.83,0.28);
  TLegend *l4= new TLegend(0.45,0.28,0.83,0.38);

  DrawLegend(gROC_SIG03, l3, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gROC_SIG04, l4, "PFIso (SIG)(Cone 0.4)","PL");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5db = new TCanvas("c5db","ROC-SIGdb",600,600);
  c5db->SetTickx();
  c5db->SetTicky();

  gROC_SIG03db = ROC(hSIG_pfRelIso03db, hQCD_pfRelIso03db);
  gROC_SIG04db = ROC(hSIG_pfRelIso04db, hQCD_pfRelIso04db);

  GraphStyle(gROC_SIG03db, 2, 21);
  GraphStyle(gROC_SIG04db, 4, 22);

  gROC_SIG04db->GetXaxis()->SetRangeUser(0,0.06);

  gROC_SIG04db->Draw("ACP");
  gROC_SIG03db->Draw("CPsame");

  TLegend *l3= new TLegend(0.45,0.18,0.83,0.28);
  TLegend *l4= new TLegend(0.45,0.28,0.83,0.38);

  DrawLegend(gROC_SIG03db, l3, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gROC_SIG04db, l4, "PFIso (SIG)(Cone 0.4)","PL");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5mc = new TCanvas("c5mc","ROC-SIGmc",600,600);
  c5mc->SetTickx();
  c5mc->SetTicky();

  gROC_SIG03mc = ROC(hSIG_pfRelIso03, hQCDmc_pfRelIso03);
  gROC_SIG04mc = ROC(hSIG_pfRelIso04, hQCDmc_pfRelIso04);

  GraphStyle(gROC_SIG03mc, 2, 21);
  GraphStyle(gROC_SIG04mc, 4, 22);

  gROC_SIG04mc->GetXaxis()->SetRangeUser(0,0.05);

  gROC_SIG04mc->Draw("ACP");
  gROC_SIG03mc->Draw("CPsame");

  TLegend *l3= new TLegend(0.45,0.18,0.83,0.28);
  TLegend *l4= new TLegend(0.45,0.28,0.83,0.38);

  DrawLegend(gROC_SIG03mc, l3, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gROC_SIG04mc, l4, "PFIso (SIG)(Cone 0.4)","PL");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5mcdb = new TCanvas("c5mcdb","ROC-SIGmcdb",600,600);
  c5mcdb->SetTickx();
  c5mcdb->SetTicky();

  gROC_SIG03mcdb = ROC(hSIG_pfRelIso03, hQCDmcdb_pfRelIso03);
  gROC_SIG04mcdb = ROC(hSIG_pfRelIso04, hQCDmcdb_pfRelIso04);

  GraphStyle(gROC_SIG03mcdb, 2, 21);
  GraphStyle(gROC_SIG04mcdb, 4, 22);

  gROC_SIG04mcdb->GetXaxis()->SetRangeUser(0,0.05);

  gROC_SIG04mcdb->Draw("ACP");
  gROC_SIG03mcdb->Draw("CPsame");

  TLegend *l3= new TLegend(0.45,0.18,0.83,0.28);
  TLegend *l4= new TLegend(0.45,0.28,0.83,0.38);

  DrawLegend(gROC_SIG03mcdb, l3, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gROC_SIG04mcdb, l4, "PFIso (SIG)(Cone 0.4)","PL");

////////////////////////////////////////////////////////////////////////////////

  TCanvas *c5mcdbeff = new TCanvas("c5mcdbeff","IsoEff-SIGmcdb",600,600);
  c5mcdbeff->SetTickx();
  c5mcdbeff->SetTicky();

  gEFF_SIG02mcdb = EFF(hSIG_pfRelIso02);
  gEFF_SIG03mcdb = EFF(hSIG_pfRelIso03);
  gEFF_SIG04mcdb = EFF(hSIG_pfRelIso04);

  GraphStyleEff(gEFF_SIG02mcdb, 1, 20);
  GraphStyleEff(gEFF_SIG03mcdb, 2, 21);
  GraphStyleEff(gEFF_SIG04mcdb, 4, 22);

  gEFF_SIG04mcdb->GetXaxis()->SetRangeUser(0,0.4);

  gEFF_SIG04mcdb->Draw("ACP");
  gEFF_SIG03mcdb->Draw("CPsame");
  gEFF_SIG02mcdb->Draw("CPsame");

  TLegend *l2= new TLegend(0.45,0.18,0.83,0.28);
  TLegend *l3= new TLegend(0.45,0.28,0.83,0.38);
  TLegend *l4= new TLegend(0.45,0.38,0.83,0.48);

  DrawLegend(gEFF_SIG03mcdb, l2, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gEFF_SIG03mcdb, l3, "PFIso (SIG)(Cone 0.3)","PL");
  DrawLegend(gEFF_SIG04mcdb, l4, "PFIso (SIG)(Cone 0.4)","PL");

///////////////////////////////////////////////////////////////////////////////

  TCanvas *c5sig = new TCanvas("c5sig","Significance",800,800);
  c5sig->Divide(2,2);
  double xmax =0.4;
  double ymin=0.7;
  TH1F* h1=new TH1F("h1","Significance for PfIso",40,0,xmax);
  TH1F* h2=new TH1F("h2","Significance for PfIso_db",40,0,xmax);
  TH1F* h3=new TH1F("h3","Significance for PfIso(QCDmc)",40,0,xmax);
  TH1F* h4=new TH1F("h4","Significance for PfIso_db(QCDmc)",40,0,xmax);
  TH1F* h11=new TH1F("h11","Significance for PfIso",40,0,xmax);
  TH1F* h22=new TH1F("h22","Significance for PfIso_db",40,0,xmax);
  TH1F* h33=new TH1F("h33","Significance for PfIso(QCDmc)",40,0,xmax);
  TH1F* h44=new TH1F("h44","Significance for PfIso_db(QCDmc)",40,0,xmax);
  cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
  for (int i=0; i<41;i++){
    double eff_signal1,eff_signal2,eff_signal3,eff_signal4;
    double eff_qcd1,eff_qcd2,eff_qcd3,eff_qcd4;
    double eff_signal11,eff_signal22,eff_signal33,eff_signal44;
    double eff_qcd11,eff_qcd22,eff_qcd33,eff_qcd44;

    gROC_SIG03->GetPoint(i,eff_qcd1,eff_signal1);
    gROC_SIG03db->GetPoint(i,eff_qcd2,eff_signal2);
    gROC_SIG03mc->GetPoint(i,eff_qcd3,eff_signal3);
    gROC_SIG03mcdb->GetPoint(i,eff_qcd4,eff_signal4);
    gROC_SIG04->GetPoint(i,eff_qcd11,eff_signal11);
    gROC_SIG04db->GetPoint(i,eff_qcd22,eff_signal22);
    gROC_SIG04mc->GetPoint(i,eff_qcd33,eff_signal33);
    gROC_SIG04mcdb->GetPoint(i,eff_qcd44,eff_signal44);

    double soverb1 = eff_signal1/sqrt(eff_signal1+eff_qcd1);
    double soverb2 = eff_signal2/sqrt(eff_signal2+eff_qcd2);
    double soverb3 = eff_signal3/sqrt(eff_signal3+eff_qcd3);
    double soverb4 = eff_signal4/sqrt(eff_signal4+eff_qcd4);
    double soverb11 = eff_signal11/sqrt(eff_signal11+eff_qcd11);
    double soverb22 = eff_signal22/sqrt(eff_signal22+eff_qcd22);
    double soverb33 = eff_signal33/sqrt(eff_signal33+eff_qcd33);
    double soverb44 = eff_signal44/sqrt(eff_signal44+eff_qcd44);

    h1->SetBinContent(i,soverb1);
    h2->SetBinContent(i,soverb2);
    h3->SetBinContent(i,soverb3);
    h4->SetBinContent(i,soverb4);
    h11->SetBinContent(i,soverb11);
    h22->SetBinContent(i,soverb22);
    h33->SetBinContent(i,soverb33);
    h44->SetBinContent(i,soverb44);
  }
  c5sig->cd(1); 
  gPad->SetGridx();
  gPad->SetGridy();
  h1->SetLineColor(2);
  h11->SetLineColor(4);
  h1->SetMinimum(ymin);
  h1->Draw();
  h11->Draw("same");

  c5sig->cd(2); 
  gPad->SetGridx();
  gPad->SetGridy();
  h2->SetLineColor(2);
  h22->SetLineColor(4);
  h2->SetMinimum(ymin);
  h2->Draw();
  h22->Draw("same");

  c5sig->cd(3); 
  gPad->SetGridx();
  gPad->SetGridy();
  h3->SetLineColor(2);
  h33->SetLineColor(4);
  h3->SetMinimum(ymin);
  h3->Draw();
  h33->Draw("same");

  c5sig->cd(4); 
  gPad->SetGridx();
  gPad->SetGridy();
  h4->SetLineColor(2);
  h44->SetLineColor(4);
  h4->SetMinimum(ymin);
  h4->Draw();
  h44->Draw("same");

////////////////////////////////////////////////////////////////////////////////

}
