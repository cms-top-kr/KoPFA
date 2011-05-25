#include "TH1F.h"
#include "THStack.h"
#include "TFile.h"
#include "TCanvas.h"
#include <iostream>
#include "TLegend.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"

using namespace std;

void defaultStyle();

void histPlot(){

  defaultStyle();

  TFile *fData = new TFile("/home/tjkim/ntuple/top/MuMu/RD/May13/vallot.root");
  TH1 * hData = (TH1F *) fData->Get("Muons/cutflow");

  TFile *fZJets = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_ZJets.root");
  TH1 * hZJets = (TH1F *) fZJets->Get("Muons/cutflow");

  TFile *fDYmm20to50 = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_DYmm20to50.root");
  TH1 * hDYmm20to50 = (TH1F *) fDYmm20to50->Get("Muons/cutflow");

  TFile *fDYmm10to20 = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_DYmm10to20.root");
  TH1 * hDYmm10to20 = (TH1F *) fDYmm10to20->Get("Muons/cutflow");

  TFile *fZtauDecay = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_ZtauDecay.root");
  TH1 * hZtauDecay = (TH1F *) fZtauDecay->Get("Muons/cutflow");
 
  TFile *fVVJets = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_VVJets.root");
  TH1 * hVVJets = (TH1F *) fVVJets->Get("Muons/cutflow");

  TFile *fWJets = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_WJetsToLNu.root");
  TH1 * hWJets = (TH1F *) fWJets->Get("Muons/cutflow");

  TFile *fQCD = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_QCD.root");
  TH1 * hQCD = (TH1F *) fQCD->Get("Muons/cutflow");

  TFile *fTTbar = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_TTbarTuneZ2.root");
  TH1 * hTTbar = (TH1F *) fTTbar->Get("Muons/cutflow");

  double lumi = 191.0;
  double lumiZJets = 764.252;
  double lumiDYmm20to50 = 1200.480; 
  double lumiDYmm10to20 = 578.536; 
  double lumiZtauDecay = 656.168; 
  double lumiVVJets = 41666.7;
  double lumiWJets = 479.019;
  double lumiQCD = 342.469;
  double lumiTTbar = 6549.206;

  hZJets->Scale(lumi/lumiZJets);
  hDYmm20to50->Scale(lumi/lumiDYmm20to50);
  hDYmm10to20->Scale(lumi/lumiDYmm10to20);
  hZtauDecay->Scale(lumi/lumiZtauDecay);
  hVVJets->Scale(lumi/lumiVVJets);
  hWJets->Scale(lumi/lumiWJets);
  hQCD->Scale(lumi/lumiQCD);
  hTTbar->Scale(lumi/lumiTTbar);
 
  hDYmm20to50->SetFillColor(2);
  hDYmm20to50->SetLineColor(2);
  hDYmm10to20->SetFillColor(2);
  hDYmm10to20->SetLineColor(2);
  hZJets->SetFillColor(2);
  hZtauDecay->SetFillColor(5);
  hVVJets->SetFillColor(6);
  hWJets->SetFillColor(46);
  hQCD->SetFillColor(3);
  hTTbar->SetFillColor(4);
 
  double mc = hZJets->Integral() + hDYmm10to20->Integral() + hDYmm20to50->Integral() + hZtauDecay->Integral() + hVVJets->Integral() + hWJets->Integral() + hQCD->Integral() + hTTbar->Integral();
  double data = hData->Integral();
  cout << "data= " << data << " mc= " << mc << endl;
  
  //hData->Scale(mc/data);

  THStack *hStack = new THStack("hStack","cutflow");
  hStack->Add(hTTbar);
  //hStack->Add(hVVJets);
  hStack->Add(hWJets);
  hStack->Add(hZtauDecay);
  hStack->Add(hQCD);
  hStack->Add(hDYmm20to50);
  hStack->Add(hZJets);

  TCanvas *c = new TCanvas("c_muon","c_muon",1);
  c->SetLogy();

  hStack->SetMaximum(3000000);
  hStack->SetMinimum(500);
  hStack->Draw();
  hStack->GetYaxis()->SetTitle("Entries");
  hData->SetMarkerSize(1);
  hData->SetMarkerStyle(20);
  hData->SetLineWidth(3);
  //hData->Sumw2();
  //hData->SetMarkerSize(1);
  //hData->SetMarkerStyle(20);
  hData->Draw("same");

  TLegend *legend = new TLegend(0.73,0.68,0.93,0.88);
  legend->AddEntry(hData,"Data","L");
  legend->AddEntry(hZJets, "Z/#gamma* #rightarrow #mu#mu", "F");
  legend->AddEntry(hQCD,"QCD","F");
  legend->AddEntry(hZtauDecay, "Z/#gamma* #rightarrow #tau#tau", "F");
  legend->AddEntry(hWJets, "W #rightarrow l#nu", "F");
  //legend->AddEntry(hVVJets, "Dibosons", "F");
  legend->AddEntry(hTTbar, "t#bar{t}", "F");
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->Draw();
 
  int nbins = hData->GetNbinsX();
  for(int i=1; i <= nbins; i++){
    //double sig = hTTbar->GetBinContent(i)+hZJets->GetBinContent(i) + hDYmm20to50->GetBinContent(i) + hDYmm10to20->GetBinContent(i);
    double sig = hTTbar->GetBinContent(i);
    //double bkg = hQCD->GetBinContent(i);
    double bkg= hQCD->GetBinContent(i)+ hWJets->GetBinContent(i) + hZtauDecay->GetBinContent(i);
    double sb = sig/sqrt( sig + bkg) ;
    cout << "sig= " << sig << " bkg= " << bkg << " sb= " << sb << endl;
  }

}

void defaultStyle()
{
    gROOT->SetStyle("Plain");
    //gStyle->SetOptStat(1110);

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0); //remove statistics box
    gStyle->SetOptFit(1);
    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.15);

    gStyle->SetCanvasDefH(500);
    gStyle->SetCanvasDefW(750);

    // For the axis:
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);

    // To make 2D contour colorful
    gStyle->SetPalette(1);

    //gStyle->SetOptTitle(0);
    // Margins:
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.05);

    // For the axis titles:
    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.06, "XYZ");
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.1);

    // For the axis labels:
    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");

}
