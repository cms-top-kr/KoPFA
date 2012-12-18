#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void isoNorm2012(){

  gROOT->LoadMacro("tdrStyle.C");
  setTDRStyle();

//  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/Out/MuMuDec18/";
  TString srcDir ="/afs/cern.ch/work/t/taeyeon/cmssw/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/IsoAnalyzer/test/Out/ElMuDec18_2/";
  TString plots ="./plots/";
/*
-rw-r--r-- 1 taeyeon zh 11950463 Dec 17 09:08 MuonIso_Run2012MuMu.root
-rw-r--r-- 1 taeyeon zh      731 Dec 17 10:10 selection.txt
-rw-r--r-- 1 taeyeon zh  2759188 Dec 17 01:51 vallot_QCDMuon.root
-rw-r--r-- 1 taeyeon zh  4521949 Dec 17 01:58 vallot_Run2012AMuMu.root
-rw-r--r-- 1 taeyeon zh  8925148 Dec 17 02:19 vallot_Run2012BMuMu.root
-rw-r--r-- 1 taeyeon zh 10098501 Dec 17 02:51 vallot_Run2012CMuMu.root
-rw-r--r-- 1 taeyeon zh  1632826 Dec 17 01:53 vallot_SingleTopBartW.root
-rw-r--r-- 1 taeyeon zh  1623720 Dec 17 01:53 vallot_SingleToptW.root
-rw-r--r-- 1 taeyeon zh  7869878 Dec 17 01:22 vallot_TTbarTuneZ2.root
-rw-r--r-- 1 taeyeon zh  1333103 Dec 17 00:29 vallot_WJetsToLNu.root
-rw-r--r-- 1 taeyeon zh  1779189 Dec 17 00:41 vallot_WW.root
-rw-r--r-- 1 taeyeon zh  2026032 Dec 17 00:52 vallot_WZ.root
-rw-r--r-- 1 taeyeon zh  2594724 Dec 16 23:24 vallot_ZJets.root
-rw-r--r-- 1 taeyeon zh  1477961 Dec 16 23:32 vallot_ZJets10To50.root
-rw-r--r-- 1 taeyeon zh  2365547 Dec 17 01:02 vallot_ZZ.root
*/

  TFile * fRD           = new TFile(srcDir+"MuonIso_Run2012MuEl.root");
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

///////////////////////////////////////////////////////////////////////////////////////////

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

  cdimass=new TCanvas("cdimass","cdimass",1200,900);
  cdimass->Divide(4,3);

  cdimass->cd(1); 
  hRD_dimass->Draw();  

  cdimass->cd(2); 
  hQCD_dimass->Scale(sfQCD);  
  hQCD_dimass->Draw();  
  cdimass->cd(3); 
  htWbar_dimass->Scale(sftWbar);  
  htWbar_dimass->Draw();  
  cdimass->cd(4); 
  htW_dimass->Scale(sftW);  
  htW_dimass->Draw();  
  cdimass->cd(5); 
  hTTbar_dimass->Scale(sfTTbar);  
  hTTbar_dimass->Draw();  
  cdimass->cd(6); 
  hWJets_dimass->Scale(sfWJets);  
  hWJets_dimass->Draw();  
  cdimass->cd(7); 
  hWW_dimass->Scale(sfWW);  
  hWW_dimass->Draw();  
  cdimass->cd(8); 
  hWZ_dimass->Scale(sfWZ);  
  hWZ_dimass->Draw();  
  cdimass->cd(9); 
  hZJets_dimass->Scale(sfZJets);  
  hZJets_dimass->Draw();  
  cdimass->cd(10); 
  hZJets10To50_dimass->Scale(sfZJets10To50);  
  hZJets10To50_dimass->Draw();  
  cdimass->cd(11); 
  hZZ_dimass->Scale(sfZZ);  
  hZZ_dimass->Draw();  

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

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

  cpfRelIso03st=new TCanvas("cpfRelIso03st","cpfRelIso03st",600,600);
  cpfRelIso03st->SetLogy();

  THStack *hs = new THStack("hs","Stacked histograms");

  hRD_pfRelIso03->SetLineColor(1);
  hRD_pfRelIso03->SetLineWidth(1);
  hRD_pfRelIso03->SetMarkerStyle(22);
  hRD_pfRelIso03->SetMarkerColor(1);
  hRD_pfRelIso03->SetMarkerSize(1.1);

  hTTbar_pfRelIso03->SetLineColor(2);
  hTTbar_pfRelIso03->SetLineWidth(1);
  hTTbar_pfRelIso03->SetFillColor(2);

  hWW_pfRelIso03->SetLineColor(4);
  hWW_pfRelIso03->SetLineWidth(4);
  hWW_pfRelIso03->SetFillColor(4);
  hWZ_pfRelIso03->SetLineColor(4);
  hWZ_pfRelIso03->SetLineWidth(1);
  hWZ_pfRelIso03->SetFillColor(4);
  hZZ_pfRelIso03->SetLineColor(4);
  hZZ_pfRelIso03->SetLineWidth(1);
  hZZ_pfRelIso03->SetFillColor(4);

  hZJets_pfRelIso03->SetLineColor(6);
  hZJets_pfRelIso03->SetLineWidth(1);
  hZJets_pfRelIso03->SetFillColor(6);
  hZJets10To50_pfRelIso03->SetLineColor(6);
  hZJets10To50_pfRelIso03->SetLineWidth(1);
  hZJets10To50_pfRelIso03->SetFillColor(6);

  hWJets_pfRelIso03->SetLineColor(7);
  hWJets_pfRelIso03->SetLineWidth(1);
  hWJets_pfRelIso03->SetFillColor(7);

  htWbar_pfRelIso03->SetLineColor(8);
  htWbar_pfRelIso03->SetLineWidth(1);
  htWbar_pfRelIso03->SetFillColor(8);
  htW_pfRelIso03->SetLineColor(8);
  htW_pfRelIso03->SetLineWidth(1);
  htW_pfRelIso03->SetFillColor(8);


  hs->Add(htWbar_pfRelIso03);  
  hs->Add(htW_pfRelIso03);  
  hs->Add(hWJets_pfRelIso03);  
  hs->Add(hWW_pfRelIso03);  
  hs->Add(hWZ_pfRelIso03);  
  hs->Add(hZJets_pfRelIso03);  
  hs->Add(hZJets10To50_pfRelIso03);  
  hs->Add(hZZ_pfRelIso03);  
  hs->Add(hTTbar_pfRelIso03);  
  hs->SetMinimum(0.1);

  hs->Draw();
  hRD_pfRelIso03->Draw("E1Psame");

///////////////////////////////////////////////////////////////////////////////////////////
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



}
