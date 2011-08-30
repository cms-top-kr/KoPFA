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

  //response matrix
  mcPath.push_back("/data/export/common/Top/ntuple/MuEl/MC/Summer11_new/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/data/export/common/Top/ntuple/ElEl/MC/Summer11_new/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/data/export/common/Top/ntuple/MuMu/MC/Summer11_new/vallot_TTbarTuneZ2.root");

  //measured mc distribution after final cut
  mePath.push_back("/data/export/common/Top/ntuple/MuEl/MC/Summer11_new/vallot_TTbarTuneZ2.root");
  mePath.push_back("/data/export/common/Top/ntuple/ElEl/MC/Summer11_new/vallot_TTbarTuneZ2.root");
  mePath.push_back("/data/export/common/Top/ntuple/MuMu/MC/Summer11_new/vallot_TTbarTuneZ2.root");
  //mePath.push_back("ZPrime/MuEl/vallot_ZPrimeM500W50.root");
  //mePath.push_back("ZPrime/ElEl/vallot_ZPrimeM500W50.root");
  //mePath.push_back("ZPrime/MuMu/vallot_ZPrimeM500W50.root");
   
  //measured data distribution after final cut
  rdPath.push_back("/data/export/common/Top/finalHisto/v5/MuEl.root");
  rdPath.push_back("/data/export/common/Top/finalHisto/v5/ElEl.root");
  rdPath.push_back("/data/export/common/Top/finalHisto/v5/MuMu.root");

  //mc truth level for full phase space or visible
  TFile * f_MadGraph = new TFile("/data/export/common/Top/ntuple/ttbarGen.root");
  TFile * f_POWHEG = new TFile("/data/export/common/Top/ntuple/Gen/ttbarGen_TTTo2L2Nu2BTuneZ2_Powheg_Summer11_PUS4_v0.root");
  TFile * f_MCNLO = new TFile("/data/export/common/Top/ntuple/ttbar_ntuple_cteq6m_dilepton.root");

  const std::string cutStep = "Step_7";
  double lumi = 1194.22;
  double scale = lumi/22222.22;//normalized to 1.1 fb-1 
  bool split = false;//use full statistics if it is false
  string recon = "vsum";

  TCut lepton = "ttbarGen.leptons_[0].pt() > 20 && ttbarGen.leptons_[1].pt() > 20 && abs(ttbarGen.leptons_[0].eta()) < 2.4 && abs(ttbarGen.leptons_[1].eta()) < 2.4";
  TCut bquark = "ttbarGen.bQuarks_[0].pt() > 30 && ttbarGen.bQuarks_[1].pt() > 30 && abs(ttbarGen.bQuarks_[0].eta()) < 2.4 && abs(ttbarGen.bQuarks_[1].eta()) < 2.4";
  TCut visible = lepton && bquark;

  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "ttbar.M()", decayMode, split ,recon);
  
  //after final selection
  TH1F * hData = getMeasuredHisto(rdPath, cutStep, recon);  //real data
  TH1F * hDataPseudo = getMeasuredHistoPseudo(mePath, rdPath, cutStep, "ttbar.M()", decayMode, scale, recon+"_pseudo"); //pseudo data
  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, scale, split, recon);

  //acceptance to visible phase space
  TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon, visible);

  //truth level in visible phase space
  TH1D* hMadGraph = getTruthHisto(f_MadGraph, "MADGRAPH", visible);
  TH1D* hPOWHEG = getTruthHisto(f_POWHEG, "POWHEG", visible);
  TH1D* hMCNLO = (TH1D*) f_MCNLO->Get("MCatNLO/hVisTTbarM");

  //for full phase space definition
  //TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, recon);

  TFile* f = TFile::Open("preUnfolding.root", "recreate");

  h2ResponseM->Write();
  hData->Write();
  hDataPseudo->Write();
  hGenDist->Write();
  hAccept->Write();

  hMadGraph->Write();
  hPOWHEG->Write();
  hMCNLO->Write();

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

