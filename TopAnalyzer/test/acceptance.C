#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TVectorD.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TTree.h"
#include "TCut.h"
#include "TGraphAsymmErrors.h"
#include "style.h"
#include "TGraph.h"
#include "TROOT.h"
#include <iostream>
//default
double detBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins
double genBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins

int nDet = sizeof(detBins)/sizeof(double) - 1;
int nGen = sizeof(genBins)/sizeof(double) - 1;

#include "preUnfolding.h"

void defaultStyle();

void acceptance(){

  defaultStyle();

  vector<TString> decayMode;
  vector<std::string> mcPath;
  vector<std::string> rdPath;

  decayMode.push_back("ElEl");
  decayMode.push_back("MuMu");
  decayMode.push_back("MuEl");

  //MC
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/ElEl/MC/Fall11_v1/vallot_TTbarTuneZ2.root");
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/MuMu/MC/Fall11_v1/vallot_TTbarTuneZ2.root");
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/MuEl/MC/Fall11_v1/vallot_TTbarTuneZ2.root");

  //measured data distribution after final cut:version 6->take into account QCD
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/ElEl.root");
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/MuMu.root");
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/MuEl.root");

  rdPath.push_back("result_Apr2/ElEl_Apr2/ElEl.root");
  rdPath.push_back("result_Apr2/MuMu_Apr2/MuMu.root");
  rdPath.push_back("result_Apr2/MuEl_Apr2/MuEl.root");


  const std::string cutStep = "Step_7";
  string recon = "vsum";

  TFile * fDen = new TFile("$WORK/data/export/common/Top/ntuple/Gen/hist/Fall11/v0/hist_madgraph.root");
  TH1F* full = (TH1F*) fDen->Get("all/hmTT_Full");
  TH1F* visi = (TH1F*) fDen->Get("all/hmTT_Pton");

  double total = full->GetEntries() ;
  cout << "total for den = " << total << endl; 
  cout << "Rebinning..." << " n bins = " << nGen << endl;
  TH1F *fullnew = (TH1F*) full->Rebin(nGen, "fullnew", genBins);
  TH1F *visinew = (TH1F*) visi->Rebin(nGen, "visinew", genBins);

  fullnew->Draw();

  //acceptance to visible phase space
  cout << "producing acceptance plots..." << endl;
  TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon, visinew, total);
  TH1F * hAcceptFull =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon+"_Full", fullnew, total);

  TFile* f = TFile::Open("acceptance.root", "recreate");

  //--------------Write into preUnfolding root file------------------------

  hAccept->Write();
  hAcceptFull->Write();

  f->Write();  
  f->Close();

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

    gStyle->SetCanvasDefH(400);
    gStyle->SetCanvasDefW(400);

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

