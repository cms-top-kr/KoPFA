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

void isoNorm2012Pre(){

  gROOT->LoadMacro("tdrStyle.C");
//  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/MuonOut/MuMuDec25Pre/"; // preselecrion for MM
  TString plots ="./plots_isoNorm2012Pre/";

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
  //double xQCD         = 125000;
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

  cpfRelIso03=new TCanvas("cpfRelIso03","cpfRelIso03",1200,900);
  cpfRelIso03->SetLogy();
  cpfRelIso03->Divide(4,3);

  cpfRelIso03->cd(1); 
  hRD_pfRelIso03->Draw();  

/*  hRD_pfRelIso03->Rebin(2);  
  hQCD_pfRelIso03->Rebin(2);  
  htWbar_pfRelIso03->Rebin(2);  
  htW_pfRelIso03->Rebin(2);  
  hTTbar_pfRelIso03->Rebin(2);  
  hWJets_pfRelIso03->Rebin(2);  
  hWW_pfRelIso03->Rebin(2);  
  hWZ_pfRelIso03->Rebin(2);  
  hZJets_pfRelIso03->Rebin(2);  
  hZJets10To50_pfRelIso03->Rebin(2);  
  hZZ_pfRelIso03->Rebin(2);  
*/
  cpfRelIso03->cd(2); 
  hQCD_pfRelIso03->Scale(sfQCD);  
  hQCD_pfRelIso03->Draw();  
  cpfRelIso03->cd(3); 
  htWbar_pfRelIso03->Scale(sftWbar);  
  htWbar_pfRelIso03->Draw();  
  cpfRelIso03->cd(4); 
  htW_pfRelIso03->Scale(sftW);  
  htW_pfRelIso03->Draw();  
  cpfRelIso03->cd(5); 
  hTTbar_pfRelIso03->Scale(sfTTbar);  
  hTTbar_pfRelIso03->Draw();  
  cpfRelIso03->cd(6); 
  hWJets_pfRelIso03->Scale(sfWJets);  
  hWJets_pfRelIso03->Draw();  
  cpfRelIso03->cd(7); 
  hWW_pfRelIso03->Scale(sfWW);  
  hWW_pfRelIso03->Draw();  
  cpfRelIso03->cd(8); 
  hWZ_pfRelIso03->Scale(sfWZ);  
  hWZ_pfRelIso03->Draw();  
  cpfRelIso03->cd(9); 
  hZJets_pfRelIso03->Scale(sfZJets);  
  hZJets_pfRelIso03->Draw();  
  cpfRelIso03->cd(10); 
  hZJets10To50_pfRelIso03->Scale(sfZJets10To50);  
  hZJets10To50_pfRelIso03->Draw();  
  cpfRelIso03->cd(11); 
  hZZ_pfRelIso03->Scale(sfZZ);  
  hZZ_pfRelIso03->Draw();  

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

  hRD_pfRelIso03->SetMinimum(9.9);// for pre-selection
  hRD_pfRelIso03->GetXaxis()->SetRangeUser(0,1.0);
  hRD_pfRelIso03->GetXaxis()->SetTitleSize(0.06);
  hRD_pfRelIso03->GetYaxis()->SetTitleSize(0.06);
  hRD_pfRelIso03->GetXaxis()->SetTitle("Relative Isolation");
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

  cpfRelIso03st->Print(plots+"PFiso03Pre.pdf");
  cpfRelIso03st->Print(plots+"PFiso03Pre.png");
///////////////////////////////////////////////////////////////////////////////////////////<isolation]
///////////////////////////////////////////////////////////////////////////////////////////[isolation04>

  TH1F * hRD_pfRelIso04          = (TH1F*) fRD->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hQCD_pfRelIso04         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * htWbar_pfRelIso04       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * htW_pfRelIso04          = (TH1F*) ftW->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hTTbar_pfRelIso04       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hWJets_pfRelIso04       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hWW_pfRelIso04          = (TH1F*) fWW->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hWZ_pfRelIso04          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hZJets_pfRelIso04       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hZJets10To50_pfRelIso04 = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");
  TH1F * hZZ_pfRelIso04          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/IDLoose/h_pfRelIso04");

/*  hRD_pfRelIso04->Rebin(2);  
  hQCD_pfRelIso04->Rebin(2);  
  htWbar_pfRelIso04->Rebin(2);  
  htW_pfRelIso04->Rebin(2);  
  hTTbar_pfRelIso04->Rebin(2);  
  hWJets_pfRelIso04->Rebin(2);  
  hWW_pfRelIso04->Rebin(2);  
  hWZ_pfRelIso04->Rebin(2);  
  hZJets_pfRelIso04->Rebin(2);  
  hZJets10To50_pfRelIso04->Rebin(2);  
  hZZ_pfRelIso04->Rebin(2);  
*/
  hQCD_pfRelIso04->Scale(sfQCD);  
  htWbar_pfRelIso04->Scale(sftWbar);  
  htW_pfRelIso04->Scale(sftW);  
  hTTbar_pfRelIso04->Scale(sfTTbar);  
  hWJets_pfRelIso04->Scale(sfWJets);  
  hWW_pfRelIso04->Scale(sfWW);  
  hWZ_pfRelIso04->Scale(sfWZ);  
  hZJets_pfRelIso04->Scale(sfZJets);  
  hZJets10To50_pfRelIso04->Scale(sfZJets10To50);  
  hZZ_pfRelIso04->Scale(sfZZ);  

  cpfRelIso04st=new TCanvas("cpfRelIso04st","cpfRelIso04st",400,400);
  cpfRelIso04st->SetLogy();

  THStack *hs = new THStack("hs","Stacked histograms");

  hRD_pfRelIso04->SetLineColor(1);
  hRD_pfRelIso04->SetLineWidth(1);
  hRD_pfRelIso04->SetMarkerStyle(22);
  hRD_pfRelIso04->SetMarkerColor(1);
  hRD_pfRelIso04->SetMarkerSize(1.1);

  hQCD_pfRelIso04->SetLineColor(5);
  hQCD_pfRelIso04->SetLineWidth(1);
  hQCD_pfRelIso04->SetFillColor(5);

  hTTbar_pfRelIso04->SetLineColor(2);
  hTTbar_pfRelIso04->SetLineWidth(1);
  hTTbar_pfRelIso04->SetFillColor(2);

  hWW_pfRelIso04->SetLineColor(17);
  hWW_pfRelIso04->SetLineWidth(1);
  hWW_pfRelIso04->SetFillColor(17);
  hWZ_pfRelIso04->SetLineColor(17);
  hWZ_pfRelIso04->SetLineWidth(1);
  hWZ_pfRelIso04->SetFillColor(17);
  hZZ_pfRelIso04->SetLineColor(17);
  hZZ_pfRelIso04->SetLineWidth(1);
  hZZ_pfRelIso04->SetFillColor(17);

  hZJets_pfRelIso04->SetLineColor(4);
  hZJets_pfRelIso04->SetLineWidth(1);
  hZJets_pfRelIso04->SetFillColor(4);
  hZJets10To50_pfRelIso04->SetLineColor(4);
  hZJets10To50_pfRelIso04->SetLineWidth(1);
  hZJets10To50_pfRelIso04->SetFillColor(4);

  hWJets_pfRelIso04->SetLineColor(3);
  hWJets_pfRelIso04->SetLineWidth(1);
  hWJets_pfRelIso04->SetFillColor(3);

  htWbar_pfRelIso04->SetLineColor(6);
  htWbar_pfRelIso04->SetLineWidth(1);
  htWbar_pfRelIso04->SetFillColor(6);
  htW_pfRelIso04->SetLineColor(6);
  htW_pfRelIso04->SetLineWidth(1);
  htW_pfRelIso04->SetFillColor(6);


  hs->Add(hTTbar_pfRelIso04);  
  hs->Add(hWJets_pfRelIso04);  
  hs->Add(hWW_pfRelIso04);  
  hs->Add(hWZ_pfRelIso04);  
  hs->Add(hZZ_pfRelIso04);  
  hs->Add(htWbar_pfRelIso04);  
  hs->Add(htW_pfRelIso04);  
  hs->Add(hZJets_pfRelIso04);  
  hs->Add(hZJets10To50_pfRelIso04);  
  hs->Add(hQCD_pfRelIso04);  

  hRD_pfRelIso04->SetMinimum(9.9);// for pre-selection
  hRD_pfRelIso04->GetXaxis()->SetRangeUser(0,1.0);
  hRD_pfRelIso04->GetXaxis()->SetTitleSize(0.06);
  hRD_pfRelIso04->GetYaxis()->SetTitleSize(0.06);
  hRD_pfRelIso04->GetXaxis()->SetTitle("Relative Isolation");
  hRD_pfRelIso04->GetYaxis()->SetTitle("Events");
  hRD_pfRelIso04->Draw("E1P");
  hs->Draw("same");
  hRD_pfRelIso04->Draw("E1Psame");

  TLegend *l= new TLegend(0.6,0.62,0.9,0.92);
  l->AddEntry(hRD_pfRelIso04, " Data","P");
  l->AddEntry(hZJets_pfRelIso04, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_pfRelIso04, " Single top","F2");
  l->AddEntry(hWW_pfRelIso04, " Dibosons","F2");
  l->AddEntry(hWJets_pfRelIso04, " W #rightarrow l#nu","F2");
  l->AddEntry(hTTbar_pfRelIso04, " t#bar{t}","F2");
  l->AddEntry(hQCD_pfRelIso04, " QCD Multijet","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cpfRelIso04st->Print(plots+"PFiso04Pre.pdf");
  cpfRelIso04st->Print(plots+"PFiso04Pre.png");
///////////////////////////////////////////////////////////////////////////////////////////<isolation04]
///////////////////////////////////////////////////////////////////////////////////////////[mtW>

  cmtW=new TCanvas("cmtW","cmtW",400,400);
  cmtW->SetLogy();

  TH1F * hRD_mtW          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hQCD_mtW         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * htWbar_mtW       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * htW_mtW          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hTTbar_mtW       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hWJets_mtW       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hWW_mtW          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hWZ_mtW          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hZJets_mtW       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hZJets10To50_mtW = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_mtW");
  TH1F * hZZ_mtW          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_mtW");

/*  hQCD_mtW->Rebin(5);  
  htWbar_mtW->Rebin(5);  
  htW_mtW->Rebin(5);  
  hTTbar_mtW->Rebin(5);  
  hWJets_mtW->Rebin(5);  
  hWW_mtW->Rebin(5);  
  hWZ_mtW->Rebin(5);  
  hZJets_mtW->Rebin(5);  
  hZJets10To50_mtW->Rebin(5);  
  hZZ_mtW->Rebin(5);  
  hRD_mtW->Rebin(5);
*/
  hQCD_mtW->Scale(sfQCD);  
  htWbar_mtW->Scale(sftWbar);  
  htW_mtW->Scale(sftW);  
  hTTbar_mtW->Scale(sfTTbar);  
  hWJets_mtW->Scale(sfWJets);  
  hWW_mtW->Scale(sfWW);  
  hWZ_mtW->Scale(sfWZ);  
  hZJets_mtW->Scale(sfZJets);  
  hZJets10To50_mtW->Scale(sfZJets10To50);  
  hZZ_mtW->Scale(sfZZ);  
  hZZ_mtW->Draw();  

  THStack *hs_mtW = new THStack("hs_mtW","Stacked histograms (mtW)");

  hRD_mtW->SetLineColor(1);
  hRD_mtW->SetLineWidth(1);
  hRD_mtW->SetMarkerStyle(22);
  hRD_mtW->SetMarkerColor(1);
  hRD_mtW->SetMarkerSize(1.1);

  hQCD_mtW->SetLineColor(5);
  hQCD_mtW->SetLineWidth(1);
  hQCD_mtW->SetFillColor(5);

  hTTbar_mtW->SetLineColor(2);
  hTTbar_mtW->SetLineWidth(1);
  hTTbar_mtW->SetFillColor(2);

  hWW_mtW->SetLineColor(17);
  hWW_mtW->SetLineWidth(1);
  hWW_mtW->SetFillColor(17);
  hWZ_mtW->SetLineColor(17);
  hWZ_mtW->SetLineWidth(1);
  hWZ_mtW->SetFillColor(17);
  hZZ_mtW->SetLineColor(17);
  hZZ_mtW->SetLineWidth(1);
  hZZ_mtW->SetFillColor(17);

  hZJets_mtW->SetLineColor(4);
  hZJets_mtW->SetLineWidth(1);
  hZJets_mtW->SetFillColor(4);
  hZJets10To50_mtW->SetLineColor(4);
  hZJets10To50_mtW->SetLineWidth(1);
  hZJets10To50_mtW->SetFillColor(4);

  hWJets_mtW->SetLineColor(3);
  hWJets_mtW->SetLineWidth(1);
  hWJets_mtW->SetFillColor(3);

  htWbar_mtW->SetLineColor(6);
  htWbar_mtW->SetLineWidth(1);
  htWbar_mtW->SetFillColor(6);
  htW_mtW->SetLineColor(6);
  htW_mtW->SetLineWidth(1);
  htW_mtW->SetFillColor(6);


  hs_mtW->Add(hTTbar_mtW);  
  hs_mtW->Add(hWJets_mtW);  
  hs_mtW->Add(hWW_mtW);  
  hs_mtW->Add(hWZ_mtW);  
  hs_mtW->Add(hZZ_mtW);  
  hs_mtW->Add(htWbar_mtW);  
  hs_mtW->Add(htW_mtW);  
  hs_mtW->Add(hZJets_mtW);  
  hs_mtW->Add(hZJets10To50_mtW);  
  hs_mtW->Add(hQCD_mtW);  
  //hs_mtW->SetMaximum(250);
  //hs_mtW->SetMinimum(10);

  hRD_mtW->GetXaxis()->SetTitleSize(0.06);
  hRD_mtW->GetYaxis()->SetTitleSize(0.06);
  hRD_mtW->GetXaxis()->SetTitle("W Transverse Mass(GeV)");
  hRD_mtW->GetYaxis()->SetTitle("Events");
  hRD_mtW->Draw("E1P");
  hs_mtW->Draw("same");
  hRD_mtW->Draw("E1Psame");

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

  cmtW->Print(plots+"cmtWPre.pdf");
  cmtW->Print(plots+"cmtWPre.png");
///////////////////////////////////////////////////////////////////////////////////////////<mtW]
///////////////////////////////////////////////////////////////////////////////////////////[dimass>

  cdimass=new TCanvas("cdimass","cdimass",400,400);
  cdimass->SetLogy();

  TH1F * hRD_dimass          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hQCD_dimass         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * htWbar_dimass       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * htW_dimass          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hTTbar_dimass       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hWJets_dimass       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hWW_dimass          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hWZ_dimass          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hZJets_dimass       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hZJets10To50_dimass = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_dimass");
  TH1F * hZZ_dimass          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_dimass");

/*  hQCD_dimass->Rebin(5);  
  htWbar_dimass->Rebin(5);  
  htW_dimass->Rebin(5);  
  hTTbar_dimass->Rebin(5);  
  hWJets_dimass->Rebin(5);  
  hWW_dimass->Rebin(5);  
  hWZ_dimass->Rebin(5);  
  hZJets_dimass->Rebin(5);  
  hZJets10To50_dimass->Rebin(5);  
  hZZ_dimass->Rebin(5);  
  hRD_dimass->Rebin(5);
*/
  hQCD_dimass->Scale(sfQCD);  
  htWbar_dimass->Scale(sftWbar);  
  htW_dimass->Scale(sftW);  
  hTTbar_dimass->Scale(sfTTbar);  
  hWJets_dimass->Scale(sfWJets);  
  hWW_dimass->Scale(sfWW);  
  hWZ_dimass->Scale(sfWZ);  
  hZJets_dimass->Scale(sfZJets);  
  hZJets10To50_dimass->Scale(sfZJets10To50);  
  hZZ_dimass->Scale(sfZZ);  
  hZZ_dimass->Draw();  

  THStack *hs_dimass = new THStack("hs_dimass","Stacked histograms (dimass)");

  hRD_dimass->SetLineColor(1);
  hRD_dimass->SetLineWidth(1);
  hRD_dimass->SetMarkerStyle(22);
  hRD_dimass->SetMarkerColor(1);
  hRD_dimass->SetMarkerSize(1.1);

  hQCD_dimass->SetLineColor(5);
  hQCD_dimass->SetLineWidth(1);
  hQCD_dimass->SetFillColor(5);

  hTTbar_dimass->SetLineColor(2);
  hTTbar_dimass->SetLineWidth(1);
  hTTbar_dimass->SetFillColor(2);

  hWW_dimass->SetLineColor(17);
  hWW_dimass->SetLineWidth(1);
  hWW_dimass->SetFillColor(17);
  hWZ_dimass->SetLineColor(17);
  hWZ_dimass->SetLineWidth(1);
  hWZ_dimass->SetFillColor(17);
  hZZ_dimass->SetLineColor(17);
  hZZ_dimass->SetLineWidth(1);
  hZZ_dimass->SetFillColor(17);

  hZJets_dimass->SetLineColor(4);
  hZJets_dimass->SetLineWidth(1);
  hZJets_dimass->SetFillColor(4);
  hZJets10To50_dimass->SetLineColor(4);
  hZJets10To50_dimass->SetLineWidth(1);
  hZJets10To50_dimass->SetFillColor(4);

  hWJets_dimass->SetLineColor(3);
  hWJets_dimass->SetLineWidth(1);
  hWJets_dimass->SetFillColor(3);

  htWbar_dimass->SetLineColor(6);
  htWbar_dimass->SetLineWidth(1);
  htWbar_dimass->SetFillColor(6);
  htW_dimass->SetLineColor(6);
  htW_dimass->SetLineWidth(1);
  htW_dimass->SetFillColor(6);


  hs_dimass->Add(hTTbar_dimass);  
  hs_dimass->Add(hWJets_dimass);  
  hs_dimass->Add(hWW_dimass);  
  hs_dimass->Add(hWZ_dimass);  
  hs_dimass->Add(hZZ_dimass);  
  hs_dimass->Add(htWbar_dimass);  
  hs_dimass->Add(htW_dimass);  
  hs_dimass->Add(hZJets_dimass);  
  hs_dimass->Add(hZJets10To50_dimass);  
  hs_dimass->Add(hQCD_dimass);  
  //hs_dimass->SetMaximum(200);

  hRD_dimass->SetMinimum(10); // for pre-selection
  hRD_dimass->GetXaxis()->SetTitleSize(0.06);
  hRD_dimass->GetYaxis()->SetTitleSize(0.06);
  hRD_dimass->GetXaxis()->SetTitle("Invaiant Mass of Di-Lepton (GeV)");
  hRD_dimass->GetYaxis()->SetTitle("Events");
  hRD_dimass->Draw("E1P");
  hs_dimass->Draw("same");
  hRD_dimass->Draw("E1Psame");

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

  cdimass->Print(plots+"cdimassPre.pdf");
  cdimass->Print(plots+"cdimassPre.png");
///////////////////////////////////////////////////////////////////////////////////////////<dimass]
///////////////////////////////////////////////////////////////////////////////////////////[met>

  cmet=new TCanvas("cmet","cmet",400,400);
  cmet->SetLogy();

  TH1F * hRD_met          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_met");
  TH1F * hQCD_met         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_met");
  TH1F * htWbar_met       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_met");
  TH1F * htW_met          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_met");
  TH1F * hTTbar_met       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_met");
  TH1F * hWJets_met       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_met");
  TH1F * hWW_met          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_met");
  TH1F * hWZ_met          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_met");
  TH1F * hZJets_met       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_met");
  TH1F * hZJets10To50_met = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_met");
  TH1F * hZZ_met          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_met");

  hQCD_met->Scale(sfQCD);  
  htWbar_met->Scale(sftWbar);  
  htW_met->Scale(sftW);  
  hTTbar_met->Scale(sfTTbar);  
  hWJets_met->Scale(sfWJets);  
  hWW_met->Scale(sfWW);  
  hWZ_met->Scale(sfWZ);  
  hZJets_met->Scale(sfZJets);  
  hZJets10To50_met->Scale(sfZJets10To50);  
  hZZ_met->Scale(sfZZ);  
  hZZ_met->Draw();  

  THStack *hs_met = new THStack("hs_met","Stacked histograms (met)");

  hRD_met->SetLineColor(1);
  hRD_met->SetLineWidth(1);
  hRD_met->SetMarkerStyle(22);
  hRD_met->SetMarkerColor(1);
  hRD_met->SetMarkerSize(1.1);

  hQCD_met->SetLineColor(5);
  hQCD_met->SetLineWidth(1);
  hQCD_met->SetFillColor(5);

  hTTbar_met->SetLineColor(2);
  hTTbar_met->SetLineWidth(1);
  hTTbar_met->SetFillColor(2);

  hWW_met->SetLineColor(17);
  hWW_met->SetLineWidth(1);
  hWW_met->SetFillColor(17);
  hWZ_met->SetLineColor(17);
  hWZ_met->SetLineWidth(1);
  hWZ_met->SetFillColor(17);
  hZZ_met->SetLineColor(17);
  hZZ_met->SetLineWidth(1);
  hZZ_met->SetFillColor(17);

  hZJets_met->SetLineColor(4);
  hZJets_met->SetLineWidth(1);
  hZJets_met->SetFillColor(4);
  hZJets10To50_met->SetLineColor(4);
  hZJets10To50_met->SetLineWidth(1);
  hZJets10To50_met->SetFillColor(4);

  hWJets_met->SetLineColor(3);
  hWJets_met->SetLineWidth(1);
  hWJets_met->SetFillColor(3);

  htWbar_met->SetLineColor(6);
  htWbar_met->SetLineWidth(1);
  htWbar_met->SetFillColor(6);
  htW_met->SetLineColor(6);
  htW_met->SetLineWidth(1);
  htW_met->SetFillColor(6);


  hs_met->Add(hTTbar_met);  
  hs_met->Add(hWJets_met);  
  hs_met->Add(hWW_met);  
  hs_met->Add(hWZ_met);  
  hs_met->Add(hZZ_met);  
  hs_met->Add(htWbar_met);  
  hs_met->Add(htW_met);  
  hs_met->Add(hZJets_met);  
  hs_met->Add(hZJets10To50_met);  
  hs_met->Add(hQCD_met);  
  //hs_met->SetMinimum(10);
  //hs_met->SetMaximum(240);

  hRD_met->GetXaxis()->SetTitleSize(0.06);
  hRD_met->GetYaxis()->SetTitleSize(0.06);
  hRD_met->GetXaxis()->SetTitle("Missing Transverse Energy(GeV)");
  hRD_met->GetYaxis()->SetTitle("Events");
  hRD_met->Draw("E1P");
  hs_met->Draw("same");
  hRD_met->Draw("E1Psame");

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

  cmet->Print(plots+"cmetPre.pdf");
  cmet->Print(plots+"cmetPre.png");
///////////////////////////////////////////////////////////////////////////////////////////<met]
///////////////////////////////////////////////////////////////////////////////////////////[nJet>

  cnJet=new TCanvas("cnJet","cnJet",400,400);
  cnJet->SetLogy();

  TH1F * hRD_nJet          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hQCD_nJet         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * htWbar_nJet       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * htW_nJet          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hTTbar_nJet       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hWJets_nJet       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hWW_nJet          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hWZ_nJet          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hZJets_nJet       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hZJets10To50_nJet = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_nJet");
  TH1F * hZZ_nJet          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_nJet");

  hQCD_nJet->Scale(sfQCD);  
  htWbar_nJet->Scale(sftWbar);  
  htW_nJet->Scale(sftW);  
  hTTbar_nJet->Scale(sfTTbar);  
  hWJets_nJet->Scale(sfWJets);  
  hWW_nJet->Scale(sfWW);  
  hWZ_nJet->Scale(sfWZ);  
  hZJets_nJet->Scale(sfZJets);  
  hZJets10To50_nJet->Scale(sfZJets10To50);  
  hZZ_nJet->Scale(sfZZ);  
  hZZ_nJet->Draw();  

  THStack *hs_nJet = new THStack("hs_nJet","Stacked histograms (nJet)");

  hRD_nJet->SetLineColor(1);
  hRD_nJet->SetLineWidth(1);
  hRD_nJet->SetMarkerStyle(22);
  hRD_nJet->SetMarkerColor(1);
  hRD_nJet->SetMarkerSize(1.1);

  hQCD_nJet->SetLineColor(5);
  hQCD_nJet->SetLineWidth(1);
  hQCD_nJet->SetFillColor(5);

  hTTbar_nJet->SetLineColor(2);
  hTTbar_nJet->SetLineWidth(1);
  hTTbar_nJet->SetFillColor(2);

  hWW_nJet->SetLineColor(17);
  hWW_nJet->SetLineWidth(1);
  hWW_nJet->SetFillColor(17);
  hWZ_nJet->SetLineColor(17);
  hWZ_nJet->SetLineWidth(1);
  hWZ_nJet->SetFillColor(17);
  hZZ_nJet->SetLineColor(17);
  hZZ_nJet->SetLineWidth(1);
  hZZ_nJet->SetFillColor(17);

  hZJets_nJet->SetLineColor(4);
  hZJets_nJet->SetLineWidth(1);
  hZJets_nJet->SetFillColor(4);
  hZJets10To50_nJet->SetLineColor(4);
  hZJets10To50_nJet->SetLineWidth(1);
  hZJets10To50_nJet->SetFillColor(4);

  hWJets_nJet->SetLineColor(3);
  hWJets_nJet->SetLineWidth(1);
  hWJets_nJet->SetFillColor(3);

  htWbar_nJet->SetLineColor(6);
  htWbar_nJet->SetLineWidth(1);
  htWbar_nJet->SetFillColor(6);
  htW_nJet->SetLineColor(6);
  htW_nJet->SetLineWidth(1);
  htW_nJet->SetFillColor(6);

  hs_nJet->Add(hTTbar_nJet);  
  hs_nJet->Add(hWJets_nJet);  
  hs_nJet->Add(hWW_nJet);  
  hs_nJet->Add(hWZ_nJet);  
  hs_nJet->Add(hZZ_nJet);  
  hs_nJet->Add(htWbar_nJet);  
  hs_nJet->Add(htW_nJet);  
  hs_nJet->Add(hZJets_nJet);  
  hs_nJet->Add(hZJets10To50_nJet);  
  hs_nJet->Add(hQCD_nJet);  
  //hs_nJet->SetMinimum(0.1);

  hRD_nJet->GetXaxis()->SetTitleSize(0.06);
  hRD_nJet->GetYaxis()->SetTitleSize(0.06);
  hRD_nJet->GetXaxis()->SetTitle("Number of Jets");
  hRD_nJet->GetYaxis()->SetTitle("Events");
  hRD_nJet->Draw("E1P");
  hs_nJet->Draw("same");
  hRD_nJet->Draw("E1Psame");

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

  cnJet->Print(plots+"cnJetPre.pdf");
  cnJet->Print(plots+"cnJetPre.png");

///////////////////////////////////////////////////////////////////////////////////////////<nJet]
///////////////////////////////////////////////////////////////////////////////////////////[nMuon>

  cnMuon=new TCanvas("cnMuon","cnMuon",400,400);
  cnMuon->SetLogy();

  TH1F * hRD_nMuon          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hQCD_nMuon         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * htWbar_nMuon       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * htW_nMuon          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hTTbar_nMuon       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hWJets_nMuon       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hWW_nMuon          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hWZ_nMuon          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hZJets_nMuon       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hZJets10To50_nMuon = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_nMuon");
  TH1F * hZZ_nMuon          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_nMuon");

  hQCD_nMuon->Scale(sfQCD);  
  htWbar_nMuon->Scale(sftWbar);  
  htW_nMuon->Scale(sftW);  
  hTTbar_nMuon->Scale(sfTTbar);  
  hWJets_nMuon->Scale(sfWJets);  
  hWW_nMuon->Scale(sfWW);  
  hWZ_nMuon->Scale(sfWZ);  
  hZJets_nMuon->Scale(sfZJets);  
  hZJets10To50_nMuon->Scale(sfZJets10To50);  
  hZZ_nMuon->Scale(sfZZ);  
  hZZ_nMuon->Draw();  

  THStack *hs_nMuon = new THStack("hs_nMuon","Stacked histograms (nMuon)");

  hRD_nMuon->SetLineColor(1);
  hRD_nMuon->SetLineWidth(1);
  hRD_nMuon->SetMarkerStyle(22);
  hRD_nMuon->SetMarkerColor(1);
  hRD_nMuon->SetMarkerSize(1.1);

  hQCD_nMuon->SetLineColor(5);
  hQCD_nMuon->SetLineWidth(1);
  hQCD_nMuon->SetFillColor(5);

  hTTbar_nMuon->SetLineColor(2);
  hTTbar_nMuon->SetLineWidth(1);
  hTTbar_nMuon->SetFillColor(2);

  hWW_nMuon->SetLineColor(17);
  hWW_nMuon->SetLineWidth(1);
  hWW_nMuon->SetFillColor(17);
  hWZ_nMuon->SetLineColor(17);
  hWZ_nMuon->SetLineWidth(1);
  hWZ_nMuon->SetFillColor(17);
  hZZ_nMuon->SetLineColor(17);
  hZZ_nMuon->SetLineWidth(1);
  hZZ_nMuon->SetFillColor(17);

  hZJets_nMuon->SetLineColor(4);
  hZJets_nMuon->SetLineWidth(1);
  hZJets_nMuon->SetFillColor(4);
  hZJets10To50_nMuon->SetLineColor(4);
  hZJets10To50_nMuon->SetLineWidth(1);
  hZJets10To50_nMuon->SetFillColor(4);

  hWJets_nMuon->SetLineColor(3);
  hWJets_nMuon->SetLineWidth(1);
  hWJets_nMuon->SetFillColor(3);

  htWbar_nMuon->SetLineColor(6);
  htWbar_nMuon->SetLineWidth(1);
  htWbar_nMuon->SetFillColor(6);
  htW_nMuon->SetLineColor(6);
  htW_nMuon->SetLineWidth(1);
  htW_nMuon->SetFillColor(6);


  hs_nMuon->Add(hTTbar_nMuon);  
  hs_nMuon->Add(hWJets_nMuon);  
  hs_nMuon->Add(hWW_nMuon);  
  hs_nMuon->Add(hWZ_nMuon);  
  hs_nMuon->Add(hZZ_nMuon);  
  hs_nMuon->Add(htWbar_nMuon);  
  hs_nMuon->Add(htW_nMuon);  
  hs_nMuon->Add(hZJets_nMuon);  
  hs_nMuon->Add(hZJets10To50_nMuon);  
  hs_nMuon->Add(hQCD_nMuon);  
  hRD_nMuon->SetMinimum(0.1); // for Signal

  hRD_nMuon->GetXaxis()->SetTitleSize(0.06);
  hRD_nMuon->GetYaxis()->SetTitleSize(0.06);
  hRD_nMuon->GetXaxis()->SetTitle("Number of Muons");
  hRD_nMuon->GetYaxis()->SetTitle("Events");
  hRD_nMuon->Draw("E1P");
  hs_nMuon->Draw("same");
  hRD_nMuon->Draw("E1Psame");

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

  cnMuon->Print(plots+"cnMuonPre.pdf");
  cnMuon->Print(plots+"cnMuonPre.png");
///////////////////////////////////////////////////////////////////////////////////////////<nMuon]
///////////////////////////////////////////////////////////////////////////////////////////[nElectron>
/*
  cnElectron=new TCanvas("cnElectron","cnElectron",400,400);
  cnElectron->SetLogy();

  TH1F * hRD_nElectron          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hQCD_nElectron         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * htWbar_nElectron       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * htW_nElectron          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hTTbar_nElectron       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hWJets_nElectron       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hWW_nElectron          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hWZ_nElectron          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hZJets_nElectron       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hZJets10To50_nElectron = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_nElectron");
  TH1F * hZZ_nElectron          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_nElectron");

  hQCD_nElectron->Scale(sfQCD);  
  htWbar_nElectron->Scale(sftWbar);  
  htW_nElectron->Scale(sftW);  
  hTTbar_nElectron->Scale(sfTTbar);  
  hWJets_nElectron->Scale(sfWJets);  
  hWW_nElectron->Scale(sfWW);  
  hWZ_nElectron->Scale(sfWZ);  
  hZJets_nElectron->Scale(sfZJets);  
  hZJets10To50_nElectron->Scale(sfZJets10To50);  
  hZZ_nElectron->Scale(sfZZ);  
  hZZ_nElectron->Draw();  

  THStack *hs_nElectron = new THStack("hs_nElectron","Stacked histograms (nElectron)");

  hRD_nElectron->SetLineColor(1);
  hRD_nElectron->SetLineWidth(1);
  hRD_nElectron->SetMarkerStyle(22);
  hRD_nElectron->SetMarkerColor(1);
  hRD_nElectron->SetMarkerSize(1.1);

  hQCD_nElectron->SetLineColor(5);
  hQCD_nElectron->SetLineWidth(1);
  hQCD_nElectron->SetFillColor(5);

  hTTbar_nElectron->SetLineColor(2);
  hTTbar_nElectron->SetLineWidth(1);
  hTTbar_nElectron->SetFillColor(2);

  hWW_nElectron->SetLineColor(17);
  hWW_nElectron->SetLineWidth(1);
  hWW_nElectron->SetFillColor(17);
  hWZ_nElectron->SetLineColor(17);
  hWZ_nElectron->SetLineWidth(1);
  hWZ_nElectron->SetFillColor(17);
  hZZ_nElectron->SetLineColor(17);
  hZZ_nElectron->SetLineWidth(1);
  hZZ_nElectron->SetFillColor(17);

  hZJets_nElectron->SetLineColor(4);
  hZJets_nElectron->SetLineWidth(1);
  hZJets_nElectron->SetFillColor(4);
  hZJets10To50_nElectron->SetLineColor(4);
  hZJets10To50_nElectron->SetLineWidth(1);
  hZJets10To50_nElectron->SetFillColor(4);

  hWJets_nElectron->SetLineColor(3);
  hWJets_nElectron->SetLineWidth(1);
  hWJets_nElectron->SetFillColor(3);

  htWbar_nElectron->SetLineColor(6);
  htWbar_nElectron->SetLineWidth(1);
  htWbar_nElectron->SetFillColor(6);
  htW_nElectron->SetLineColor(6);
  htW_nElectron->SetLineWidth(1);
  htW_nElectron->SetFillColor(6);


  hs_nElectron->Add(hTTbar_nElectron);  
  hs_nElectron->Add(hWJets_nElectron);  
  hs_nElectron->Add(hWW_nElectron);  
  hs_nElectron->Add(hWZ_nElectron);  
  hs_nElectron->Add(hZZ_nElectron);  
  hs_nElectron->Add(htWbar_nElectron);  
  hs_nElectron->Add(htW_nElectron);  
  hs_nElectron->Add(hZJets_nElectron);  
  hs_nElectron->Add(hZJets10To50_nElectron);  
  hs_nElectron->Add(hQCD_nElectron);  
  //hs_nElectron->SetMinimum(1);

  hRD_nElectron->Draw("E1P");
  hs_nElectron->Draw("same");
  hRD_nElectron->Draw("E1Psame");

  TLegend *l= new TLegend(0.6,0.62,0.9,0.92);
  l->AddEntry(hRD_pfRelIso03, " Data","P");
  l->AddEntry(hZJets_pfRelIso03, " Z/#gamma* #rightarrow ll","F2");
  l->AddEntry(htW_pfRelIso03, " Single top","F2");
  l->AddEntry(hWW_pfRelIso03, " Dibosons","F2");
  l->AddEntry(hWJets_pfRelIso03, " W #rightarrow l#nu","F2");
  l->AddEntry(hQCD_pfRelIso03, " QCD Multijet","F2");
  l->AddEntry(hTTbar_pfRelIso03, " t#bar{t}","F2");
  l->AddEntry(hQCD_pfRelIso03, " QCD Multijet","F2");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  cnElectron->Print(plots+"cnElectronPre.pdf");
  cnElectron->Print(plots+"cnElectronPre.png");
*/
///////////////////////////////////////////////////////////////////////////////////////////<nElectron]
///////////////////////////////////////////////////////////////////////////////////////////[delphi>

  cdelphi=new TCanvas("cdelphi","cdelphi",400,400);
  cdelphi->SetLogy();

  TH1F * hRD_delphi          = (TH1F*) fRD->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hQCD_delphi         = (TH1F*) fQCD->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * htWbar_delphi       = (TH1F*) ftWbar->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * htW_delphi          = (TH1F*) ftW->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hTTbar_delphi       = (TH1F*) fTTbar->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hWJets_delphi       = (TH1F*) fWJets->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hWW_delphi          = (TH1F*) fWW->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hWZ_delphi          = (TH1F*) fWZ->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hZJets_delphi       = (TH1F*) fZJets->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hZJets10To50_delphi = (TH1F*) fZJets10To50->Get("MuonAnalysis/Signal/h_delphi");
  TH1F * hZZ_delphi          = (TH1F*) fZZ->Get("MuonAnalysis/Signal/h_delphi");

  hQCD_delphi->Scale(sfQCD);  
  htWbar_delphi->Scale(sftWbar);  
  htW_delphi->Scale(sftW);  
  hTTbar_delphi->Scale(sfTTbar);  
  hWJets_delphi->Scale(sfWJets);  
  hWW_delphi->Scale(sfWW);  
  hWZ_delphi->Scale(sfWZ);  
  hZJets_delphi->Scale(sfZJets);  
  hZJets10To50_delphi->Scale(sfZJets10To50);  
  hZZ_delphi->Scale(sfZZ);  
  hZZ_delphi->Draw();  

  THStack *hs_delphi = new THStack("hs_delphi","Stacked histograms (delphi)");

  hRD_delphi->SetLineColor(1);
  hRD_delphi->SetLineWidth(1);
  hRD_delphi->SetMarkerStyle(22);
  hRD_delphi->SetMarkerColor(1);
  hRD_delphi->SetMarkerSize(1.1);

  hQCD_delphi->SetLineColor(5);
  hQCD_delphi->SetLineWidth(1);
  hQCD_delphi->SetFillColor(5);

  hTTbar_delphi->SetLineColor(2);
  hTTbar_delphi->SetLineWidth(1);
  hTTbar_delphi->SetFillColor(2);

  hWW_delphi->SetLineColor(17);
  hWW_delphi->SetLineWidth(1);
  hWW_delphi->SetFillColor(17);
  hWZ_delphi->SetLineColor(17);
  hWZ_delphi->SetLineWidth(1);
  hWZ_delphi->SetFillColor(17);
  hZZ_delphi->SetLineColor(17);
  hZZ_delphi->SetLineWidth(1);
  hZZ_delphi->SetFillColor(17);

  hZJets_delphi->SetLineColor(4);
  hZJets_delphi->SetLineWidth(1);
  hZJets_delphi->SetFillColor(4);
  hZJets10To50_delphi->SetLineColor(4);
  hZJets10To50_delphi->SetLineWidth(1);
  hZJets10To50_delphi->SetFillColor(4);

  hWJets_delphi->SetLineColor(3);
  hWJets_delphi->SetLineWidth(1);
  hWJets_delphi->SetFillColor(3);

  htWbar_delphi->SetLineColor(6);
  htWbar_delphi->SetLineWidth(1);
  htWbar_delphi->SetFillColor(6);
  htW_delphi->SetLineColor(6);
  htW_delphi->SetLineWidth(1);
  htW_delphi->SetFillColor(6);


  hs_delphi->Add(hTTbar_delphi);  
  hs_delphi->Add(hWJets_delphi);  
  hs_delphi->Add(hWW_delphi);  
  hs_delphi->Add(hWZ_delphi);  
  hs_delphi->Add(hZZ_delphi);  
  hs_delphi->Add(htWbar_delphi);  
  hs_delphi->Add(htW_delphi);  
  hs_delphi->Add(hZJets_delphi);  
  hs_delphi->Add(hZJets10To50_delphi);  
  hs_delphi->Add(hQCD_delphi);  

  hRD_delphi->SetMaximum(1000001); // for pre-selection
  hRD_delphi->SetMinimum(99999); // for pre-selection
  hRD_delphi->GetXaxis()->SetTitleSize(0.06);
  hRD_delphi->GetYaxis()->SetTitleSize(0.06);
  hRD_delphi->GetXaxis()->SetTitle("Delta R(mu,Jet)");
  hRD_delphi->GetYaxis()->SetTitle("Events");
  hRD_delphi->Draw("E1P");
  hs_delphi->Draw("same");
  hRD_delphi->Draw("E1Psame");

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

  cdelphi->Print(plots+"cdelphiPre.pdf");
  cdelphi->Print(plots+"cdelphiPre.png");
///////////////////////////////////////////////////////////////////////////////////////////<delphi]
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
///////////////////////////////////////////////////////////////////////////////////////////[QCDpurity>

  double QCDInteRD20  = hRD_QCDpfRelIso03->Integral(1,20);
  double QCDInteRD40  = hRD_QCDpfRelIso03->Integral(1,40);
  double QCDInteRD100  = hRD_QCDpfRelIso03->Integral(1,100);
  double QCDInteRD1000 = hRD_QCDpfRelIso03->Integral(1,1000);
  double QCDInteTTbar20 = hTTbar_QCDpfRelIso03->Integral(1,20);
  double QCDInteTTbar40 = hTTbar_QCDpfRelIso03->Integral(1,40);
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

///////////////////////////////////////////////////////////////////////////////////////////<QCDpurity]
///////////////////////////////////////////////////////////////////////////////////////////[QCDpurity04>

  double QCDInteRD20  = hRD_QCDpfRelIso04->Integral(1,20);
  double QCDInteRD40  = hRD_QCDpfRelIso04->Integral(1,40);
  double QCDInteRD100  = hRD_QCDpfRelIso04->Integral(1,100);
  double QCDInteRD1000 = hRD_QCDpfRelIso04->Integral(1,1000);
  double QCDInteTTbar20 = hTTbar_QCDpfRelIso04->Integral(1,20);
  double QCDInteTTbar40 = hTTbar_QCDpfRelIso04->Integral(1,40);
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
