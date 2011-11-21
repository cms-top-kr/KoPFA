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
#include "preUnfolding.h"

void defaultStyle();

void preUnfolding(){

  defaultStyle();

  vector<TString> decayMode;
  vector<std::string> mcPath;
  vector<std::string> mePath;
  vector<std::string> rdPath;

  decayMode.push_back("MuEl");
  decayMode.push_back("ElEl");
  decayMode.push_back("MuMu");

  mcPath.push_back("/data/export/common/Top/ntuple/MuEl/MC/Summer11/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/data/export/common/Top/ntuple/ElEl/MC/Summer11/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/data/export/common/Top/ntuple/MuMu/MC/Summer11/vallot_TTbarTuneZ2.root");

  mePath.push_back("/data/export/common/Top/ntuple/MuEl/MC/Summer11/vallot_TTbarTuneZ2.root");
  mePath.push_back("/data/export/common/Top/ntuple/ElEl/MC/Summer11/vallot_TTbarTuneZ2.root");
  mePath.push_back("/data/export/common/Top/ntuple/MuMu/MC/Summer11/vallot_TTbarTuneZ2.root");
  //mePath.push_back("ZPrime/MuEl/vallot_ZPrimeM500W50.root");
  //mePath.push_back("ZPrime/ElEl/vallot_ZPrimeM500W50.root");
  //mePath.push_back("ZPrime/MuMu/vallot_ZPrimeM500W50.root");

  rdPath.push_back("MuEl_1fb_notrigger/MuEl.root");
  rdPath.push_back("ElEl_1fb_notrigger/ElEl.root");
  rdPath.push_back("MuMu_1fb_notrigger/MuMu.root");

  const std::string cutStep = "Step_7";
  double scale = 1091.94/19047.62;//normalized to 1.1 fb-1 
  bool split = false;//use full statistics if it is false
  string recon = "vsum";

  TCut lepton = "ttbarGen.leptons_[0].pt() > 20 && ttbarGen.leptons_[1].pt() > 20 && abs(ttbarGen.leptons_[0].eta()) < 2.4 && abs(ttbarGen.leptons_[1].eta()) < 2.4";
  TCut bquark = "ttbarGen.bQuarks_[0].pt() > 30 && ttbarGen.bQuarks_[1].pt() > 30 && abs(ttbarGen.bQuarks_[0].eta()) < 2.4 && abs(ttbarGen.bQuarks_[1].eta()) < 2.4";
  TCut visible = lepton && bquark;

  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "ttbar.M()", decayMode, split ,recon);

  TH1F * hData = getMeasuredHisto(rdPath, cutStep);  //real data
  //TH1F * hData = getMeasuredHistoPseudo(mePath, rdPath, cutStep, "ttbar.M()", decayMode, scale, recon); //pseudo data

  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, scale, split, recon);
  TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon);

  //for visible phase space definition
  //TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon, visible);

  TFile* f = TFile::Open("preUnfolding.root", "recreate");

  h2ResponseM->Write();
  hData->Write();
  hGenDist->Write();
  hAccept->Write();

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

