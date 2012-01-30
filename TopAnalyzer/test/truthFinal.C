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
float detBins[] = {0, 345, 400, 450, 500, 550, 600, 700, 800, 1400}; // 9 bins
float genBins[] = {0, 345, 400, 450, 500, 550, 600, 700, 800, 1400}; // 9 bins

int nDet = sizeof(detBins)/sizeof(float) - 1;
int nGen = sizeof(genBins)/sizeof(float) - 1;

#include "preUnfolding.h"

void defaultStyle();

void truthFinal(){

  defaultStyle();

  //mc truth level for full phase space or visible
  TFile * f_MadGraph = new TFile("/data/export/common/Top/ntuple/ttbarGen.root");
  TFile * f_POWHEG = new TFile("/data/export/common/Top/ntuple/Gen/ttbarGen_TTTo2L2Nu2BTuneZ2_Powheg_Summer11_PUS4_v0.root");
  TFile * f_MCNLO = new TFile("/data/export/common/Top/ntuple/ttbar_ntuple_cteq6m_dilepton_v20111028.root");

  double lumi = 1143.22;
  double scale = lumi/22222.22;
  double scale_powheg = lumi/ ( 1000000.0 / (157.5 * 0.11) );
  bool split = false;//use full statistics if it is false

  TCut lepton = "ttbarGen.leptons_[0].pt() > 20 && ttbarGen.leptons_[1].pt() > 20 && abs(ttbarGen.leptons_[0].eta()) < 2.4 && abs(ttbarGen.leptons_[1].eta()) < 2.4";
  TCut bquark = "ttbarGen.bQuarks_[0].pt() > 30 && ttbarGen.bQuarks_[1].pt() > 30 && abs(ttbarGen.bQuarks_[0].eta()) < 2.4 && abs(ttbarGen.bQuarks_[1].eta()) < 2.4";
  TCut visible = lepton && bquark;

  //truth level in visible phase space
  cout << "producing truth level plots..." << endl;
  TH1D* hMadGraph = getTruthHisto(f_MadGraph, "MADGRAPH", scale, visible);
  TH1D* hPOWHEG = getTruthHisto(f_POWHEG, "POWHEG", scale_powheg, visible);
  TH1D* hMadGraphFull = getTruthHisto(f_MadGraph, "MADGRAPH_Full", scale);
  TH1D* hPOWHEGFull = getTruthHisto(f_POWHEG, "POWHEG_Full", scale_powheg);
  TH1D* hMCNLO = (TH1D*) f_MCNLO->Get("hVisTTbarM");
  TH1D* hMCNLO_Up = (TH1D*) f_MCNLO->Get("hVisTTbarM_Up");
  TH1D* hMCNLO_Down = (TH1D*) f_MCNLO->Get("hVisTTbarM_Down");

  TFile* f = TFile::Open("truthFinal.root", "recreate");

  hMadGraph->Write();
  hPOWHEG->Write();
  hMadGraphFull->Write();
  hPOWHEGFull->Write();
  hMCNLO->Write();
  hMCNLO_Up->Write();
  hMCNLO_Down->Write();

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

