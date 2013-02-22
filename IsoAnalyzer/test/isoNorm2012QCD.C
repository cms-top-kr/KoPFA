#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void DrawLegendHisto(TH1* h, TLegend* l, const TString LegendName,TString opt){
  l->AddEntry(h,LegendName,opt);
  l->SetTextSize(0.03);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void isoNorm2012QCD(){

  gROOT->LoadMacro("tdrStyle.C");
  setTDRStyle();

  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/MuonOut/MuMuDec25/";//for QCD
  TString plots ="./plots_isoNorm2012QCD/";

  TFile * fRD           = new TFile(srcDir+"MuonIso_Run2012MuMu.root");
  TFile * fQCD          = new TFile(srcDir+"vallot_QCDMuon.root");
  TFile * ftWbar        = new TFile(srcDir+"vallot_SingleTopBartW.root");
  TFile * ftW           = new TFile(srcDir+"vallot_SingleToptW.root");
  TFile * fTTbar        = new TFile(srcDir+"vallot_TTbarTuneZ2.root");
  TFile * fWJets        = new TFile(srcDir+"vallot_WJetsToLNu.root");
  TFile * fWW           = new TFile(srcDir+"vallot_WW.root");
  TFile * fWZ           = new TFile(srcDir+"vallot_WZ.root");
  TFile * fZJets        = new TFile(srcDir+"vallot_ZJets.root");
  TFile * fZJets10To50 = new TFile(srcDir+"vallot_ZJets10To50.root");
  TFile * fZZ           = new TFile(srcDir+"vallot_ZZ.root");
/////////////////////////////////////////////////////////////////////////////////////////////
  TH1F * hRD_EventSummary          = (TH1F*) fRD->Get("MuonAnalysis/EventSummary");
  TH1F * hQCD_EventSummary         = (TH1F*) fQCD->Get("MuonAnalysis/EventSummary");
  TH1F * htWbar_EventSummary       = (TH1F*) ftWbar->Get("MuonAnalysis/EventSummary");
  TH1F * htW_EventSummary          = (TH1F*) ftW->Get("MuonAnalysis/EventSummary");
  TH1F * hTTbar_EventSummary       = (TH1F*) fTTbar->Get("MuonAnalysis/EventSummary");
  TH1F * hWJets_EventSummary       = (TH1F*) fWJets->Get("MuonAnalysis/EventSummary");
  TH1F * hWW_EventSummary          = (TH1F*) fWW->Get("MuonAnalysis/EventSummary");
  TH1F * hWZ_EventSummary          = (TH1F*) fWZ->Get("MuonAnalysis/EventSummary");
  TH1F * hZJets_EventSummary       = (TH1F*) fZJets->Get("MuonAnalysis/EventSummary");
  TH1F * hZJets10To50_EventSummary = (TH1F*) fZJets10To50->Get("MuonAnalysis/EventSummary");
  TH1F * hZZ_EventSummary          = (TH1F*) fZZ->Get("MuonAnalysis/EventSummary");

  int nRD          = hRD_EventSummary->GetBinContent(1);
  int nQCD         = hQCD_EventSummary->GetBinContent(1);
  int ntWbar       = htWbar_EventSummary->GetBinContent(1);
  int ntW          = htW_EventSummary->GetBinContent(1);
  int nTTbar       = hTTbar_EventSummary->GetBinContent(1);
  int nWJets       = hWJets_EventSummary->GetBinContent(1);
  int nWW          = hWW_EventSummary->GetBinContent(1);
  int nWZ          = hWZ_EventSummary->GetBinContent(1);
  int nZJets       = hZJets_EventSummary->GetBinContent(1);
  int nZJets10To50 = hZJets10To50_EventSummary->GetBinContent(1);
  int nZZ          = hZZ_EventSummary->GetBinContent(1);

  cout << "Number of Events fRD          = " << nRD << endl;
  cout << "Number of Events fQCD         = " << nQCD << endl;
  cout << "Number of Events ftWbar       = " << ntWbar << endl;
  cout << "Number of Events ftW          = " << ntW << endl;
  cout << "Number of Events fTTbar       = " << nTTbar << endl;
  cout << "Number of Events fWJets       = " << nWJets << endl;
  cout << "Number of Events fWW          = " << nWW << endl;
  cout << "Number of Events fWZ          = " << nWZ << endl;
  cout << "Number of Events fZJets       = " << nZJets << endl;
  cout << "Number of Events fZJets10To50 = " << nZJets10To50 << endl;
  cout << "Number of Events fZZ          = " << nZZ << endl;
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
  double TILRD        = 12.018*1000;

  double xQCD         = 364000000*0.00037;
  //double xQCD         = 135000;
  double xtWbar       = 11.1;
  double xtW          = 11.1;
  //double xTTbar       = 225.197;
  double xTTbar       = 23.6196 ;
  double xWJets       = 36257.2;
  double xWW          = 54.8;
  double xWZ          = 32.3;
  double xZJets       = 3503.17;
  double xZJets10To50 = 860;
  double xZZ          = 7.7;

  double TILQCD         = nQCD/xQCD;
  double TILtWbar       = ntWbar/xtWbar;
  double TILtW          = ntW/xtW;
  double TILTTbar       = nTTbar/xTTbar;
  double TILWJets       = nWJets/xWJets;
  double TILWW          = nWW/xWW;
  double TILWZ          = nWZ/xWZ;
  double TILZJets       = nZJets/xZJets;
  double TILZJets10To50 = nZJets10To50/xZJets10To50;
  double TILZZ          = nZZ/xZZ;

  double sfQCD         = TILRD/TILQCD;
  double sftWbar       = TILRD/TILtWbar;
  double sftW          = TILRD/TILtW;
  double sfTTbar       = TILRD/TILTTbar;
  double sfWJets       = TILRD/TILWJets;
  double sfWW          = TILRD/TILWW;
  double sfWZ          = TILRD/TILWZ;
  double sfZJets       = TILRD/TILZJets;
  double sfZJets10To50 = TILRD/TILZJets10To50;
  double sfZZ          = TILRD/TILZZ;

  cout << "==========================================< Cross Section of the Process" << endl;
  cout << "Cross Section of the Process fQCD         = " << xQCD << endl;
  cout << "Cross Section of the Process ftWbar       = " << xtWbar << endl;
  cout << "Cross Section of the Process ftW          = " << xtW << endl;
  cout << "Cross Section of the Process fTTbar       = " << xTTbar << endl;
  cout << "Cross Section of the Process fWJets       = " << xWJets << endl;
  cout << "Cross Section of the Process fWW          = " << xWW << endl;
  cout << "Cross Section of the Process fWZ          = " << xWZ << endl;
  cout << "Cross Section of the Process fZJets       = " << xZJets << endl;
  cout << "Cross Section of the Process fZJets10To50 = " << xZJets10To50 << endl;
  cout << "Cross Section of the Process fZZ          = " << xZZ << endl;
  cout << "==========================================< Integrated Luminosity of MC sample" << endl;
  cout << "Integrated Luminosity of MC sample fQCD         = " << TILQCD << endl;
  cout << "Integrated Luminosity of MC sample ftWbar       = " << TILtWbar << endl;
  cout << "Integrated Luminosity of MC sample ftW          = " << TILtW << endl;
  cout << "Integrated Luminosity of MC sample fTTbar       = " << TILTTbar << endl;
  cout << "Integrated Luminosity of MC sample fWJets       = " << TILWJets << endl;
  cout << "Integrated Luminosity of MC sample fWW          = " << TILWW << endl;
  cout << "Integrated Luminosity of MC sample fWZ          = " << TILWZ << endl;
  cout << "Integrated Luminosity of MC sample fZJets       = " << TILZJets << endl;
  cout << "Integrated Luminosity of MC sample fZJets10To50 = " << TILZJets10To50 << endl;
  cout << "Integrated Luminosity of MC sample fZZ          = " << TILZZ << endl;
  cout << "==========================================< Scale Factor of MC sample" << endl;
  cout << "Scale Factor of MC sample fQCD         = " << sfQCD << endl;
  cout << "Scale Factor of MC sample ftWbar       = " << sftWbar << endl;
  cout << "Scale Factor of MC sample ftW          = " << sftW << endl;
  cout << "Scale Factor of MC sample fTTbar       = " << sfTTbar << endl;
  cout << "Scale Factor of MC sample fWJets       = " << sfWJets << endl;
  cout << "Scale Factor of MC sample fWW          = " << sfWW << endl;
  cout << "Scale Factor of MC sample fWZ          = " << sfWZ << endl;
  cout << "Scale Factor of MC sample fZJets       = " << sfZJets << endl;
  cout << "Scale Factor of MC sample fZJets10To50 = " << sfZJets10To50 << endl;
  cout << "Scale Factor of MC sample fZZ          = " << sfZZ << endl;

///////////////////////////////////////////////////////////////////////////////////////////[isolation>

  TH1F * hRD_pfRelIso03          = (TH1F*) fRD->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hQCD_pfRelIso03         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * htWbar_pfRelIso03       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * htW_pfRelIso03          = (TH1F*) ftW->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hTTbar_pfRelIso03       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hWJets_pfRelIso03       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hWW_pfRelIso03          = (TH1F*) fWW->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hWZ_pfRelIso03          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hZJets_pfRelIso03       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hZJets10To50_pfRelIso03 = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");
  TH1F * hZZ_pfRelIso03          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso03");

//  cpfRelIso03=new TCanvas("cpfRelIso03","cpfRelIso03",1200,900);
//  cpfRelIso03->SetLogy();
//  cpfRelIso03->Divide(4,3);

//  cpfRelIso03->cd(1); 
//  hRD_pfRelIso03->Draw();  

//  cpfRelIso03->cd(2); 
  hQCD_pfRelIso03->Scale(sfQCD);  
//  hQCD_pfRelIso03->Draw();  
//  cpfRelIso03->cd(3); 
  htWbar_pfRelIso03->Scale(sftWbar);  
//  htWbar_pfRelIso03->Draw();  
//  cpfRelIso03->cd(4); 
  htW_pfRelIso03->Scale(sftW);  
//  htW_pfRelIso03->Draw();  
//  cpfRelIso03->cd(5); 
  hTTbar_pfRelIso03->Scale(sfTTbar);  
//  hTTbar_pfRelIso03->Draw();  
//  cpfRelIso03->cd(6); 
  hWJets_pfRelIso03->Scale(sfWJets);  
//  hWJets_pfRelIso03->Draw();  
//  cpfRelIso03->cd(7); 
  hWW_pfRelIso03->Scale(sfWW);  
//  hWW_pfRelIso03->Draw();  
//  cpfRelIso03->cd(8); 
  hWZ_pfRelIso03->Scale(sfWZ);  
//  hWZ_pfRelIso03->Draw();  
//  cpfRelIso03->cd(9); 
  hZJets_pfRelIso03->Scale(sfZJets);  
//  hZJets_pfRelIso03->Draw();  
//  cpfRelIso03->cd(10); 
  hZJets10To50_pfRelIso03->Scale(sfZJets10To50);  
//  hZJets10To50_pfRelIso03->Draw();  
//  cpfRelIso03->cd(11); 
  hZZ_pfRelIso03->Scale(sfZZ);  
//  hZZ_pfRelIso03->Draw();  

  cpfRelIso03st=new TCanvas("cpfRelIso03st","cpfRelIso03st",400,400);
  cpfRelIso03st->SetLogy();

  THStack *hs = new THStack("hs","Stacked histograms");

  hRD_pfRelIso03->SetLineColor(1);
  hRD_pfRelIso03->SetLineWidth(1);
  hRD_pfRelIso03->SetMarkerStyle(22);
  hRD_pfRelIso03->SetMarkerColor(1);
  hRD_pfRelIso03->SetMarkerSize(1.1);

  hQCD_pfRelIso03->SetLineColor(5);
  hQCD_pfRelIso03->SetLineWidth(1);
  hQCD_pfRelIso03->SetFillColor(5);

  hTTbar_pfRelIso03->SetLineColor(2);
  hTTbar_pfRelIso03->SetLineWidth(1);
  hTTbar_pfRelIso03->SetFillColor(2);

  hWW_pfRelIso03->SetLineColor(17);
  hWW_pfRelIso03->SetLineWidth(1);
  hWW_pfRelIso03->SetFillColor(17);
  hWZ_pfRelIso03->SetLineColor(17);
  hWZ_pfRelIso03->SetLineWidth(1);
  hWZ_pfRelIso03->SetFillColor(17);
  hZZ_pfRelIso03->SetLineColor(17);
  hZZ_pfRelIso03->SetLineWidth(1);
  hZZ_pfRelIso03->SetFillColor(17);

  hZJets_pfRelIso03->SetLineColor(4);
  hZJets_pfRelIso03->SetLineWidth(1);
  hZJets_pfRelIso03->SetFillColor(4);
  hZJets10To50_pfRelIso03->SetLineColor(4);
  hZJets10To50_pfRelIso03->SetLineWidth(1);
  hZJets10To50_pfRelIso03->SetFillColor(4);

  hWJets_pfRelIso03->SetLineColor(3);
  hWJets_pfRelIso03->SetLineWidth(1);
  hWJets_pfRelIso03->SetFillColor(3);

  htWbar_pfRelIso03->SetLineColor(6);
  htWbar_pfRelIso03->SetLineWidth(1);
  htWbar_pfRelIso03->SetFillColor(6);
  htW_pfRelIso03->SetLineColor(6);
  htW_pfRelIso03->SetLineWidth(1);
  htW_pfRelIso03->SetFillColor(6);


  hs->Add(hTTbar_pfRelIso03);  
  hs->Add(hWJets_pfRelIso03);  
  hs->Add(hWW_pfRelIso03);  
  hs->Add(hWZ_pfRelIso03);  
  hs->Add(hZZ_pfRelIso03);  
  hs->Add(htWbar_pfRelIso03);  
  hs->Add(htW_pfRelIso03);  
  hs->Add(hZJets_pfRelIso03);  
  hs->Add(hZJets10To50_pfRelIso03);  
  hs->Add(hQCD_pfRelIso03);  

  hRD_pfRelIso03->SetMinimum(0.99);
  hRD_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  //hRD_pfRelIso03->GetXaxis()->SetTitleFont(1.1);
  hRD_pfRelIso03->GetXaxis()->SetTitleSize(0.06);
  hRD_pfRelIso03->GetXaxis()->SetTitle("Relative Isolation");
  hRD_pfRelIso03->GetYaxis()->SetTitleSize(0.06);
  hRD_pfRelIso03->GetYaxis()->SetTitle("Events");
  hRD_pfRelIso03->Draw("E1P");
  hs->Draw("same");
  hRD_pfRelIso03->Draw("E1Psame");

  TLegend *l= new TLegend(0.6,0.62,0.9,0.92);
  l->AddEntry(hRD_pfRelIso03, " Data","P");
  l->AddEntry(hZJets_pfRelIso03, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_pfRelIso03, " Single top","F2");
  l->AddEntry(hWW_pfRelIso03, " Dibosons","F2");
  l->AddEntry(hWJets_pfRelIso03, " W #rightarrow l#nu","F2");
  l->AddEntry(hTTbar_pfRelIso03, " t#bar{t}","F2");
  l->AddEntry(hQCD_pfRelIso03, " QCD Multijet","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cpfRelIso03st->Print(plots+"PFiso03.pdf");
  cpfRelIso03st->Print(plots+"PFiso03.png");
///////////////////////////////////////////////////////////////////////////////////////////<isolation]
///////////////////////////////////////////////////////////////////////////////////////////[isoQCD02>

  cQCDpfRelIso02=new TCanvas("cQCDpfRelIso02","cQCDpfRelIso02",400,400);
  //cQCDpfRelIso02->SetLogy();

  TH1F * hRD_QCDpfRelIso02          = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hQCD_QCDpfRelIso02         = (TH1F*) fQCD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * htWbar_QCDpfRelIso02       = (TH1F*) ftWbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * htW_QCDpfRelIso02          = (TH1F*) ftW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hTTbar_QCDpfRelIso02       = (TH1F*) fTTbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hWJets_QCDpfRelIso02       = (TH1F*) fWJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hWW_QCDpfRelIso02          = (TH1F*) fWW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hWZ_QCDpfRelIso02          = (TH1F*) fWZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hZJets_QCDpfRelIso02       = (TH1F*) fZJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hZJets10To50_QCDpfRelIso02 = (TH1F*) fZJets10To50->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");
  TH1F * hZZ_QCDpfRelIso02          = (TH1F*) fZZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso02");

  hQCD_QCDpfRelIso02->Scale(sfQCD);  
  htWbar_QCDpfRelIso02->Scale(sftWbar);  
  htW_QCDpfRelIso02->Scale(sftW);  
  hTTbar_QCDpfRelIso02->Scale(sfTTbar);  
  hWJets_QCDpfRelIso02->Scale(sfWJets);  
  hWW_QCDpfRelIso02->Scale(sfWW);  
  hWZ_QCDpfRelIso02->Scale(sfWZ);  
  hZJets_QCDpfRelIso02->Scale(sfZJets);  
  hZJets10To50_QCDpfRelIso02->Scale(sfZJets10To50);  
  hZZ_QCDpfRelIso02->Scale(sfZZ);  
  hZZ_QCDpfRelIso02->Draw();  

  THStack *hs_QCDpfRelIso02 = new THStack("hs_QCDpfRelIso02","Stacked histograms (QCDpfRelIso02)");

  hRD_QCDpfRelIso02->SetLineColor(1);
  hRD_QCDpfRelIso02->SetLineWidth(1);
  hRD_QCDpfRelIso02->SetMarkerStyle(22);
  hRD_QCDpfRelIso02->SetMarkerColor(1);
  hRD_QCDpfRelIso02->SetMarkerSize(1.1);

  hQCD_QCDpfRelIso02->SetLineColor(5);
  hQCD_QCDpfRelIso02->SetLineWidth(1);
  hQCD_QCDpfRelIso02->SetFillColor(5);

  hTTbar_QCDpfRelIso02->SetLineColor(2);
  hTTbar_QCDpfRelIso02->SetLineWidth(1);
  hTTbar_QCDpfRelIso02->SetFillColor(2);

  hWW_QCDpfRelIso02->SetLineColor(17);
  hWW_QCDpfRelIso02->SetLineWidth(1);
  hWW_QCDpfRelIso02->SetFillColor(17);
  hWZ_QCDpfRelIso02->SetLineColor(17);
  hWZ_QCDpfRelIso02->SetLineWidth(1);
  hWZ_QCDpfRelIso02->SetFillColor(17);
  hZZ_QCDpfRelIso02->SetLineColor(17);
  hZZ_QCDpfRelIso02->SetLineWidth(1);
  hZZ_QCDpfRelIso02->SetFillColor(17);

  hZJets_QCDpfRelIso02->SetLineColor(4);
  hZJets_QCDpfRelIso02->SetLineWidth(1);
  hZJets_QCDpfRelIso02->SetFillColor(4);
  hZJets10To50_QCDpfRelIso02->SetLineColor(4);
  hZJets10To50_QCDpfRelIso02->SetLineWidth(1);
  hZJets10To50_QCDpfRelIso02->SetFillColor(4);

  hWJets_QCDpfRelIso02->SetLineColor(3);
  hWJets_QCDpfRelIso02->SetLineWidth(1);
  hWJets_QCDpfRelIso02->SetFillColor(3);

  htWbar_QCDpfRelIso02->SetLineColor(6);
  htWbar_QCDpfRelIso02->SetLineWidth(1);
  htWbar_QCDpfRelIso02->SetFillColor(6);
  htW_QCDpfRelIso02->SetLineColor(6);
  htW_QCDpfRelIso02->SetLineWidth(1);
  htW_QCDpfRelIso02->SetFillColor(6);

  hs_QCDpfRelIso02->Add(hTTbar_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hWJets_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hWW_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hWZ_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hZZ_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(htWbar_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(htW_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hZJets_QCDpfRelIso02);  
  hs_QCDpfRelIso02->Add(hZJets10To50_QCDpfRelIso02);  
  //hs_QCDpfRelIso02->Add(hQCD_QCDpfRelIso02);  
  hRD_QCDpfRelIso02->SetMaximum(500);
  hRD_QCDpfRelIso02->SetMinimum(0.99);
  hRD_QCDpfRelIso02->GetXaxis()->SetRangeUser(0,1.0);

  //hRD_QCDpfRelIso02->GetXaxis()->SetTitleFont(2.1);
  hRD_QCDpfRelIso02->GetXaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso02->GetXaxis()->SetTitle("Relative Isolation");
  hRD_QCDpfRelIso02->GetYaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso02->GetYaxis()->SetTitle("Events");
  hRD_QCDpfRelIso02->Draw("E1P");
  hs_QCDpfRelIso02->Draw("same");
  hRD_QCDpfRelIso02->Draw("E1Psame");

//  TLegend *l= new TLegend(0.6,0.55,0.9,0.85);
  TLegend *l= new TLegend(0.6,0.25,0.9,0.55);
  l->AddEntry(hRD_QCDpfRelIso02, " Data","P");
  l->AddEntry(hZJets_QCDpfRelIso02, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_QCDpfRelIso02, " Single top","F2");
  l->AddEntry(hWW_QCDpfRelIso02, " Dibosons","F2");
  l->AddEntry(hWJets_QCDpfRelIso02, " W #rightarrow l#nu","F2");
  l->AddEntry(hTTbar_QCDpfRelIso02, " t#bar{t}","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cQCDpfRelIso02->Print(plots+"cQCDpfRelIso02.pdf");
  cQCDpfRelIso02->Print(plots+"cQCDpfRelIso02.png");
///////////////////////////////////////////////////////////////////////////////////////////<isoQCD02]
///////////////////////////////////////////////////////////////////////////////////////////[isoQCD03>

  cQCDpfRelIso03=new TCanvas("cQCDpfRelIso03","cQCDpfRelIso03",400,400);
  //cQCDpfRelIso03->SetLogy();

  TH1F * hRD_QCDpfRelIso03          = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hQCD_QCDpfRelIso03         = (TH1F*) fQCD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * htWbar_QCDpfRelIso03       = (TH1F*) ftWbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * htW_QCDpfRelIso03          = (TH1F*) ftW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hTTbar_QCDpfRelIso03       = (TH1F*) fTTbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hWJets_QCDpfRelIso03       = (TH1F*) fWJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hWW_QCDpfRelIso03          = (TH1F*) fWW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hWZ_QCDpfRelIso03          = (TH1F*) fWZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hZJets_QCDpfRelIso03       = (TH1F*) fZJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hZJets10To50_QCDpfRelIso03 = (TH1F*) fZJets10To50->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");
  TH1F * hZZ_QCDpfRelIso03          = (TH1F*) fZZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso03");

  hQCD_QCDpfRelIso03->Scale(sfQCD);  
  htWbar_QCDpfRelIso03->Scale(sftWbar);  
  htW_QCDpfRelIso03->Scale(sftW);  
  hTTbar_QCDpfRelIso03->Scale(sfTTbar);  
  hWJets_QCDpfRelIso03->Scale(sfWJets);  
  hWW_QCDpfRelIso03->Scale(sfWW);  
  hWZ_QCDpfRelIso03->Scale(sfWZ);  
  hZJets_QCDpfRelIso03->Scale(sfZJets);  
  hZJets10To50_QCDpfRelIso03->Scale(sfZJets10To50);  
  hZZ_QCDpfRelIso03->Scale(sfZZ);  
  hZZ_QCDpfRelIso03->Draw();  

  THStack *hs_QCDpfRelIso03 = new THStack("hs_QCDpfRelIso03","Stacked histograms (QCDpfRelIso03)");

  hRD_QCDpfRelIso03->SetLineColor(1);
  hRD_QCDpfRelIso03->SetLineWidth(1);
  hRD_QCDpfRelIso03->SetMarkerStyle(22);
  hRD_QCDpfRelIso03->SetMarkerColor(1);
  hRD_QCDpfRelIso03->SetMarkerSize(1.1);

  hQCD_QCDpfRelIso03->SetLineColor(5);
  hQCD_QCDpfRelIso03->SetLineWidth(1);
  hQCD_QCDpfRelIso03->SetFillColor(5);

  hTTbar_QCDpfRelIso03->SetLineColor(2);
  hTTbar_QCDpfRelIso03->SetLineWidth(1);
  hTTbar_QCDpfRelIso03->SetFillColor(2);

  hWW_QCDpfRelIso03->SetLineColor(17);
  hWW_QCDpfRelIso03->SetLineWidth(1);
  hWW_QCDpfRelIso03->SetFillColor(17);
  hWZ_QCDpfRelIso03->SetLineColor(17);
  hWZ_QCDpfRelIso03->SetLineWidth(1);
  hWZ_QCDpfRelIso03->SetFillColor(17);
  hZZ_QCDpfRelIso03->SetLineColor(17);
  hZZ_QCDpfRelIso03->SetLineWidth(1);
  hZZ_QCDpfRelIso03->SetFillColor(17);

  hZJets_QCDpfRelIso03->SetLineColor(4);
  hZJets_QCDpfRelIso03->SetLineWidth(1);
  hZJets_QCDpfRelIso03->SetFillColor(4);
  hZJets10To50_QCDpfRelIso03->SetLineColor(4);
  hZJets10To50_QCDpfRelIso03->SetLineWidth(1);
  hZJets10To50_QCDpfRelIso03->SetFillColor(4);

  hWJets_QCDpfRelIso03->SetLineColor(3);
  hWJets_QCDpfRelIso03->SetLineWidth(1);
  hWJets_QCDpfRelIso03->SetFillColor(3);

  htWbar_QCDpfRelIso03->SetLineColor(6);
  htWbar_QCDpfRelIso03->SetLineWidth(1);
  htWbar_QCDpfRelIso03->SetFillColor(6);
  htW_QCDpfRelIso03->SetLineColor(6);
  htW_QCDpfRelIso03->SetLineWidth(1);
  htW_QCDpfRelIso03->SetFillColor(6);

  hs_QCDpfRelIso03->Add(hTTbar_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hWJets_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hWW_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hWZ_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hZZ_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(htWbar_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(htW_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hZJets_QCDpfRelIso03);  
  hs_QCDpfRelIso03->Add(hZJets10To50_QCDpfRelIso03);  
  //hs_QCDpfRelIso03->Add(hQCD_QCDpfRelIso03);  
//  hRD_QCDpfRelIso03->SetMaximum(10000);
  hRD_QCDpfRelIso03->SetMinimum(0.99);
  hRD_QCDpfRelIso03->GetXaxis()->SetRangeUser(0,1.0);

  //hRD_QCDpfRelIso03->GetXaxis()->SetTitleFont(2.1);
  hRD_QCDpfRelIso03->GetXaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso03->GetXaxis()->SetTitle("Relative Isolation");
  hRD_QCDpfRelIso03->GetYaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso03->GetYaxis()->SetTitle("Events");
  hRD_QCDpfRelIso03->Draw("E1P");
  hs_QCDpfRelIso03->Draw("same");
  hRD_QCDpfRelIso03->Draw("E1Psame");

  TLegend *l= new TLegend(0.6,0.25,0.9,0.55);
  l->AddEntry(hRD_QCDpfRelIso03, " Data","P");
  l->AddEntry(hZJets_QCDpfRelIso03, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_QCDpfRelIso03, " Single top","F2");
  l->AddEntry(hWW_QCDpfRelIso03, " Dibosons","F2");
  l->AddEntry(hWJets_QCDpfRelIso03, " W #rightarrow l#nu","F2");
  l->AddEntry(hTTbar_QCDpfRelIso03, " t#bar{t}","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cQCDpfRelIso03->Print(plots+"cQCDpfRelIso03.pdf");
  cQCDpfRelIso03->Print(plots+"cQCDpfRelIso03.png");
///////////////////////////////////////////////////////////////////////////////////////////<isoQCD03]
///////////////////////////////////////////////////////////////////////////////////////////[isoQCD04>

  cQCDpfRelIso04=new TCanvas("cQCDpfRelIso04","cQCDpfRelIso04",400,400);
//  cQCDpfRelIso04->SetLogy();

  TH1F * hRD_QCDpfRelIso04          = (TH1F*) fRD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hQCD_QCDpfRelIso04         = (TH1F*) fQCD->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * htWbar_QCDpfRelIso04       = (TH1F*) ftWbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * htW_QCDpfRelIso04          = (TH1F*) ftW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hTTbar_QCDpfRelIso04       = (TH1F*) fTTbar->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hWJets_QCDpfRelIso04       = (TH1F*) fWJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hWW_QCDpfRelIso04          = (TH1F*) fWW->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hWZ_QCDpfRelIso04          = (TH1F*) fWZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hZJets_QCDpfRelIso04       = (TH1F*) fZJets->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hZJets10To50_QCDpfRelIso04 = (TH1F*) fZJets10To50->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");
  TH1F * hZZ_QCDpfRelIso04          = (TH1F*) fZZ->Get("MuonAnalysis/QCD/IDLoose/h_pfRelIso04");

  hQCD_QCDpfRelIso04->Scale(sfQCD);  
  htWbar_QCDpfRelIso04->Scale(sftWbar);  
  htW_QCDpfRelIso04->Scale(sftW);  
  hTTbar_QCDpfRelIso04->Scale(sfTTbar);  
  hWJets_QCDpfRelIso04->Scale(sfWJets);  
  hWW_QCDpfRelIso04->Scale(sfWW);  
  hWZ_QCDpfRelIso04->Scale(sfWZ);  
  hZJets_QCDpfRelIso04->Scale(sfZJets);  
  hZJets10To50_QCDpfRelIso04->Scale(sfZJets10To50);  
  hZZ_QCDpfRelIso04->Scale(sfZZ);  
  hZZ_QCDpfRelIso04->Draw();  

  THStack *hs_QCDpfRelIso04 = new THStack("hs_QCDpfRelIso04","Stacked histograms (QCDpfRelIso04)");

  hRD_QCDpfRelIso04->SetLineColor(1);
  hRD_QCDpfRelIso04->SetLineWidth(1);
  hRD_QCDpfRelIso04->SetMarkerStyle(22);
  hRD_QCDpfRelIso04->SetMarkerColor(1);
  hRD_QCDpfRelIso04->SetMarkerSize(1.1);

  hQCD_QCDpfRelIso04->SetLineColor(5);
  hQCD_QCDpfRelIso04->SetLineWidth(1);
  hQCD_QCDpfRelIso04->SetFillColor(5);

  hTTbar_QCDpfRelIso04->SetLineColor(2);
  hTTbar_QCDpfRelIso04->SetLineWidth(1);
  hTTbar_QCDpfRelIso04->SetFillColor(2);

  hWW_QCDpfRelIso04->SetLineColor(17);
  hWW_QCDpfRelIso04->SetLineWidth(1);
  hWW_QCDpfRelIso04->SetFillColor(17);
  hWZ_QCDpfRelIso04->SetLineColor(17);
  hWZ_QCDpfRelIso04->SetLineWidth(1);
  hWZ_QCDpfRelIso04->SetFillColor(17);
  hZZ_QCDpfRelIso04->SetLineColor(17);
  hZZ_QCDpfRelIso04->SetLineWidth(1);
  hZZ_QCDpfRelIso04->SetFillColor(17);

  hZJets_QCDpfRelIso04->SetLineColor(4);
  hZJets_QCDpfRelIso04->SetLineWidth(1);
  hZJets_QCDpfRelIso04->SetFillColor(4);
  hZJets10To50_QCDpfRelIso04->SetLineColor(4);
  hZJets10To50_QCDpfRelIso04->SetLineWidth(1);
  hZJets10To50_QCDpfRelIso04->SetFillColor(4);

  hWJets_QCDpfRelIso04->SetLineColor(3);
  hWJets_QCDpfRelIso04->SetLineWidth(1);
  hWJets_QCDpfRelIso04->SetFillColor(3);

  htWbar_QCDpfRelIso04->SetLineColor(6);
  htWbar_QCDpfRelIso04->SetLineWidth(1);
  htWbar_QCDpfRelIso04->SetFillColor(6);
  htW_QCDpfRelIso04->SetLineColor(6);
  htW_QCDpfRelIso04->SetLineWidth(1);
  htW_QCDpfRelIso04->SetFillColor(6);

  hs_QCDpfRelIso04->Add(hTTbar_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hWJets_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hWW_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hWZ_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hZZ_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(htWbar_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(htW_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hZJets_QCDpfRelIso04);  
  hs_QCDpfRelIso04->Add(hZJets10To50_QCDpfRelIso04);  
  //hs_QCDpfRelIso04->Add(hQCD_QCDpfRelIso04);  
//  hRD_QCDpfRelIso04->SetMaximum(10000);
  hRD_QCDpfRelIso04->SetMinimum(0.99);
  hRD_QCDpfRelIso04->GetXaxis()->SetRangeUser(0,1.0);

  //hRD_QCDpfRelIso04->GetXaxis()->SetTitleFont(2.1);
  hRD_QCDpfRelIso04->GetXaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso04->GetXaxis()->SetTitle("Relative Isolation");
  hRD_QCDpfRelIso04->GetYaxis()->SetTitleSize(0.06);
  hRD_QCDpfRelIso04->GetYaxis()->SetTitle("Events");
  hRD_QCDpfRelIso04->Draw("E1P");
  hs_QCDpfRelIso04->Draw("same");
  hRD_QCDpfRelIso04->Draw("E1Psame");

  TLegend *l= new TLegend(0.6,0.25,0.9,0.55);
  l->AddEntry(hRD_QCDpfRelIso04, " Data","P");
  l->AddEntry(hZJets_QCDpfRelIso04, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_QCDpfRelIso04, " Single top","F2");
  l->AddEntry(hWW_QCDpfRelIso04, " Dibosons","F2");
  l->AddEntry(hWJets_QCDpfRelIso04, " W #rightarrow l#nu","F2");
  l->AddEntry(hTTbar_QCDpfRelIso04, " t#bar{t}","F2");
//  l->AddEntry(hQCD_QCDpfRelIso04, " QCD Multijet","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cQCDpfRelIso04->Print(plots+"cQCDpfRelIso04.pdf");
  cQCDpfRelIso04->Print(plots+"cQCDpfRelIso04.png");
///////////////////////////////////////////////////////////////////////////////////////////<isoQCD04]
///////////////////////////////////////////////////////////////////////////////////////////[SIGpurity>

  double InteRD20  = hRD_pfRelIso03->Integral(1,20);
  double InteRD40  = hRD_pfRelIso03->Integral(1,40);
  double InteRD100  = hRD_pfRelIso03->Integral(1,100);
  double InteRD1000 = hRD_pfRelIso03->Integral(1,1000);
  double InteTTbar20 = hTTbar_pfRelIso03->Integral(1,20);
  double InteTTbar40 = hTTbar_pfRelIso03->Integral(1,40);
  double InteTTbar100 = hTTbar_pfRelIso03->Integral(1,100);
  double InteTTbar1000 = hTTbar_pfRelIso03->Integral(1,1000);

  double IntetWbar       = htWbar_pfRelIso03->Integral(1,100);
  double IntetW          = htW_pfRelIso03->Integral(1,100);
  double InteWJets       = hWJets_pfRelIso03->Integral(1,100);
  double InteWW          = hWW_pfRelIso03->Integral(1,100);
  double InteWZ          = hWZ_pfRelIso03->Integral(1,100);
  double InteZJets       = hZJets_pfRelIso03->Integral(1,100);
  double InteZJets10To50 = hZJets10To50_pfRelIso03->Integral(1,100);
  double InteZZ          = hZZ_pfRelIso03->Integral(1,100);
  double InteMC100 = IntetWbar + IntetW + InteWJets + InteWW + InteWZ + InteZJets + InteZJets10To50 + InteZZ + InteTTbar100;

  double IntetWbar2       = htWbar_pfRelIso03->Integral(1,1000);
  double IntetW2          = htW_pfRelIso03->Integral(1,1000);
  double InteWJets2       = hWJets_pfRelIso03->Integral(1,1000);
  double InteWW2          = hWW_pfRelIso03->Integral(1,1000);
  double InteWZ2          = hWZ_pfRelIso03->Integral(1,1000);
  double InteZJets2       = hZJets_pfRelIso03->Integral(1,1000);
  double InteZJets10To502 = hZJets10To50_pfRelIso03->Integral(1,1000);
  double InteZZ2          = hZZ_pfRelIso03->Integral(1,1000);
  double InteMC1000 = IntetWbar2 + IntetW2 + InteWJets2 + InteWW2 + InteWZ2 + InteZJets2 + InteZJets10To502 + InteZZ2 + InteTTbar1000;

  cout <<"======================================================================"<<endl;
  cout <<"InteRD20   = " << InteRD20 <<   "      InteTTbar20   = " << InteTTbar20 <<   "     Purity(%) = " << 100*InteTTbar20/InteRD20     << endl;
  cout <<"InteRD40   = " << InteRD40 <<   "      InteTTbar40   = " << InteTTbar40 <<   "     Purity(%) = " << 100*InteTTbar40/InteRD40     << endl;
  cout <<"InteRD100  = " << InteRD100 <<  "     InteTTbar100  = " << InteTTbar100 <<  "     Purity(%) = " << 100*InteTTbar100/InteRD100   << endl;
  cout <<"InteRD1000 = " << InteRD1000 << "     InteTTbar1000 = " << InteTTbar1000 << "     Purity(%) = " << 100*InteTTbar1000/InteRD1000 << endl;
  cout <<"======================================================================"<<endl;
  cout <<"InteMC100 = " << InteMC100 << "       InteTTbar100 = " << InteTTbar100 << "     Purity(%) = " << 100*InteTTbar100/InteMC100 << endl;
  cout <<"InteMC1000 = " << InteMC1000 << "     InteTTbar1000 = " << InteTTbar1000 << "     Purity(%) = " << 100*InteTTbar1000/InteMC1000 << endl;
  cout <<"======================================================================"<<endl;

///////////////////////////////////////////////////////////////////////////////////////////<SIGpurity]
///////////////////////////////////////////////////////////////////////////////////////////[QCDpurity02>

  double QCDInteRD100  = hRD_QCDpfRelIso02->Integral(1,100);
  double QCDInteRD1000 = hRD_QCDpfRelIso02->Integral(1,1000);

  double QCDInteTTbar100 = hTTbar_QCDpfRelIso02->Integral(1,100);
  double QCDInteTTbar1000 = hTTbar_QCDpfRelIso02->Integral(1,1000);

  double QCDIntetWbar       = htWbar_QCDpfRelIso02->Integral(1,100);
  double QCDIntetW          = htW_QCDpfRelIso02->Integral(1,100);
  double QCDInteWJets       = hWJets_QCDpfRelIso02->Integral(1,100);
  double QCDInteWW          = hWW_QCDpfRelIso02->Integral(1,100);
  double QCDInteWZ          = hWZ_QCDpfRelIso02->Integral(1,100);
  double QCDInteZJets       = hZJets_QCDpfRelIso02->Integral(1,100);
  double QCDInteZJets10To50 = hZJets10To50_QCDpfRelIso02->Integral(1,100);
  double QCDInteZZ          = hZZ_QCDpfRelIso02->Integral(1,100);
  double QCDInteMC100 = QCDIntetWbar + QCDIntetW + QCDInteWJets + QCDInteWW + QCDInteWZ + QCDInteZJets + QCDInteZJets10To50 + QCDInteZZ + QCDInteTTbar100;

  double QCDIntetWbar2       = htWbar_QCDpfRelIso02->Integral(1,1000);
  double QCDIntetW2          = htW_QCDpfRelIso02->Integral(1,1000);
  double QCDInteWJets2       = hWJets_QCDpfRelIso02->Integral(1,1000);
  double QCDInteWW2          = hWW_QCDpfRelIso02->Integral(1,1000);
  double QCDInteWZ2          = hWZ_QCDpfRelIso02->Integral(1,1000);
  double QCDInteZJets2       = hZJets_QCDpfRelIso02->Integral(1,1000);
  double QCDInteZJets10To502 = hZJets10To50_QCDpfRelIso02->Integral(1,1000);
  double QCDInteZZ2          = hZZ_QCDpfRelIso02->Integral(1,1000);
  double QCDInteMC1000 = QCDIntetWbar2 + QCDIntetW2 + QCDInteWJets2 + QCDInteWW2 + QCDInteWZ2 + QCDInteZJets2 + QCDInteZJets10To502 + QCDInteZZ2 + QCDInteTTbar1000;

  cout <<"======================================================================cone02"<<endl;
  cout <<"QCDInteMC100 = " << QCDInteMC100 << "       QCDInteRD100 = " << QCDInteRD100 << "     Purity(%) = " << 100*(1-QCDInteMC100/QCDInteRD100) << endl;
  cout <<"QCDInteMC1000 = " << QCDInteMC1000 << "     QCDInteRD1000 = " << QCDInteRD1000 << "     Purity(%) = " << 100*(1-QCDInteMC1000/QCDInteRD1000) << endl;
  cout <<"======================================================================cone02"<<endl;

///////////////////////////////////////////////////////////////////////////////////////////<QCDpurity02]
///////////////////////////////////////////////////////////////////////////////////////////[QCDpurity03>

  double QCDInteRD100  = hRD_QCDpfRelIso03->Integral(1,100);
  double QCDInteRD1000 = hRD_QCDpfRelIso03->Integral(1,1000);

  double QCDInteTTbar100 = hTTbar_QCDpfRelIso03->Integral(1,100);
  double QCDInteTTbar1000 = hTTbar_QCDpfRelIso03->Integral(1,1000);

  double QCDIntetWbar       = htWbar_QCDpfRelIso03->Integral(1,100);
  double QCDIntetW          = htW_QCDpfRelIso03->Integral(1,100);
  double QCDInteWJets       = hWJets_QCDpfRelIso03->Integral(1,100);
  double QCDInteWW          = hWW_QCDpfRelIso03->Integral(1,100);
  double QCDInteWZ          = hWZ_QCDpfRelIso03->Integral(1,100);
  double QCDInteZJets       = hZJets_QCDpfRelIso03->Integral(1,100);
  double QCDInteZJets10To50 = hZJets10To50_QCDpfRelIso03->Integral(1,100);
  double QCDInteZZ          = hZZ_QCDpfRelIso03->Integral(1,100);
  double QCDInteMC100 = QCDIntetWbar + QCDIntetW + QCDInteWJets + QCDInteWW + QCDInteWZ + QCDInteZJets + QCDInteZJets10To50 + QCDInteZZ + QCDInteTTbar100;

  double QCDIntetWbar2       = htWbar_QCDpfRelIso03->Integral(1,1000);
  double QCDIntetW2          = htW_QCDpfRelIso03->Integral(1,1000);
  double QCDInteWJets2       = hWJets_QCDpfRelIso03->Integral(1,1000);
  double QCDInteWW2          = hWW_QCDpfRelIso03->Integral(1,1000);
  double QCDInteWZ2          = hWZ_QCDpfRelIso03->Integral(1,1000);
  double QCDInteZJets2       = hZJets_QCDpfRelIso03->Integral(1,1000);
  double QCDInteZJets10To502 = hZJets10To50_QCDpfRelIso03->Integral(1,1000);
  double QCDInteZZ2          = hZZ_QCDpfRelIso03->Integral(1,1000);
  double QCDInteMC1000 = QCDIntetWbar2 + QCDIntetW2 + QCDInteWJets2 + QCDInteWW2 + QCDInteWZ2 + QCDInteZJets2 + QCDInteZJets10To502 + QCDInteZZ2 + QCDInteTTbar1000;

  cout <<"======================================================================cone03"<<endl;
  cout <<"QCDInteMC100 = " << QCDInteMC100 << "       QCDInteRD100 = " << QCDInteRD100 << "     Purity(%) = " << 100*(1-QCDInteMC100/QCDInteRD100) << endl;
  cout <<"QCDInteMC1000 = " << QCDInteMC1000 << "     QCDInteRD1000 = " << QCDInteRD1000 << "     Purity(%) = " << 100*(1-QCDInteMC1000/QCDInteRD1000) << endl;
  cout <<"======================================================================cone03"<<endl;

///////////////////////////////////////////////////////////////////////////////////////////<QCDpurity03]
///////////////////////////////////////////////////////////////////////////////////////////[QCDpurity04>

  double QCDInteRD100  = hRD_QCDpfRelIso04->Integral(1,100);
  double QCDInteRD1000 = hRD_QCDpfRelIso04->Integral(1,1000);

  double QCDInteTTbar100 = hTTbar_QCDpfRelIso04->Integral(1,100);
  double QCDInteTTbar1000 = hTTbar_QCDpfRelIso04->Integral(1,1000);

  double QCDIntetWbar       = htWbar_QCDpfRelIso04->Integral(1,100);
  double QCDIntetW          = htW_QCDpfRelIso04->Integral(1,100);
  double QCDInteWJets       = hWJets_QCDpfRelIso04->Integral(1,100);
  double QCDInteWW          = hWW_QCDpfRelIso04->Integral(1,100);
  double QCDInteWZ          = hWZ_QCDpfRelIso04->Integral(1,100);
  double QCDInteZJets       = hZJets_QCDpfRelIso04->Integral(1,100);
  double QCDInteZJets10To50 = hZJets10To50_QCDpfRelIso04->Integral(1,100);
  double QCDInteZZ          = hZZ_QCDpfRelIso04->Integral(1,100);
  double QCDInteMC100 = QCDIntetWbar + QCDIntetW + QCDInteWJets + QCDInteWW + QCDInteWZ + QCDInteZJets + QCDInteZJets10To50 + QCDInteZZ + QCDInteTTbar100;

  double QCDIntetWbar2       = htWbar_QCDpfRelIso04->Integral(1,1000);
  double QCDIntetW2          = htW_QCDpfRelIso04->Integral(1,1000);
  double QCDInteWJets2       = hWJets_QCDpfRelIso04->Integral(1,1000);
  double QCDInteWW2          = hWW_QCDpfRelIso04->Integral(1,1000);
  double QCDInteWZ2          = hWZ_QCDpfRelIso04->Integral(1,1000);
  double QCDInteZJets2       = hZJets_QCDpfRelIso04->Integral(1,1000);
  double QCDInteZJets10To502 = hZJets10To50_QCDpfRelIso04->Integral(1,1000);
  double QCDInteZZ2          = hZZ_QCDpfRelIso04->Integral(1,1000);
  double QCDInteMC1000 = QCDIntetWbar2 + QCDIntetW2 + QCDInteWJets2 + QCDInteWW2 + QCDInteWZ2 + QCDInteZJets2 + QCDInteZJets10To502 + QCDInteZZ2 + QCDInteTTbar1000;

  cout <<"======================================================================cone04"<<endl;
  cout <<"QCDInteMC100 = " << QCDInteMC100 << "       QCDInteRD100 = " << QCDInteRD100 << "     Purity(%) = " << 100*(1-QCDInteMC100/QCDInteRD100) << endl;
  cout <<"QCDInteMC1000 = " << QCDInteMC1000 << "     QCDInteRD1000 = " << QCDInteRD1000 << "     Purity(%) = " << 100*(1-QCDInteMC1000/QCDInteRD1000) << endl;
  cout <<"======================================================================con04"<<endl;

///////////////////////////////////////////////////////////////////////////////////////////<QCDpurity04]


}
