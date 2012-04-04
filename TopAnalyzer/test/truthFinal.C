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
float detBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins
float genBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins

int nDet = sizeof(detBins)/sizeof(float) - 1;
int nGen = sizeof(genBins)/sizeof(float) - 1;

#include "preUnfolding.h"

void defaultStyle();

void truthFinal(){

  defaultStyle();

  //mc truth level for full phase space or visible
  TFile * f_MadGraph = new TFile("$WORK/data/export/common/Top/ntuple/Gen/hist/Fall11/v0/hist_madgraph.root");
  TFile * f_POWHEG = new TFile("$WORK/data/export/common/Top/ntuple/Gen/hist/Fall11/v0/hist_powheg.root");
  //TFile * f_MCNLO = new TFile("$WORK/data/export/common/Top/ntuple/Gen/hist/Fall11/v0/hist_mcatnlo.root");
  //TFile * f_POWHEG = new TFile("$WORK/data/export/common/Top/ntuple/Gen/ttbarGen_TTTo2L2Nu2BTuneZ2_Powheg_Summer11_PUS4_v0.root");
  TFile * f_MCNLO = new TFile("$WORK/data/export/common/Top/ntuple/ttbar_ntuple_cteq6m_dilepton_v20111028.root");

  //truth level in visible phase space
  cout << "producing truth level plots..." << endl;
  TH1* hMadGraphFull = (TH1*) f_MadGraph->Get("all/hmTT_Full");
  TH1* hMadGraph = (TH1*) f_MadGraph->Get("all/hmTT_Pton");
  TH1* hPOWHEGFull = (TH1*) f_POWHEG->Get("all/hmTT_Full");
  TH1* hPOWHEG = (TH1*) f_POWHEG->Get("all/hmTT_Pton");
  TH1* hMCNLO = (TH1*) f_MCNLO->Get("hVisTTbarM");
  TH1* hMCNLO_Up = (TH1*) f_MCNLO->Get("hVisTTbarM_Up");
  TH1* hMCNLO_Down = (TH1*) f_MCNLO->Get("hVisTTbarM_Down");

  TFile* f = TFile::Open("truthFinal.root", "recreate");

  double lumi =  5000;

  double lumi_madgraph = hMadGraphFull->GetEntries() / 164.6;
  double lumi_powheg = hPOWHEGFull->GetEntries() / 164.6;
  double lumi_mcatnlo = hMCNLO->GetEntries() / 164.6;
  double scale_madgraph = lumi / lumi_madgraph;
  double scale_powheg = lumi / lumi_powheg;
  double scale_mcatnlo = lumi / lumi_mcatnlo;

  hMadGraphFull->Scale(scale_madgraph);
  hMadGraph->Scale(scale_madgraph);
  hPOWHEGFull->Scale(scale_powheg);
  hPOWHEG->Scale(scale_powheg);

  hMadGraphFull->SetName("MadGraph_Full");
  hMadGraph->SetName("MadGraph_Visible");
  hPOWHEGFull->SetName("POWHEG_Full");
  hPOWHEG->SetName("POWHEG_Visible");

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

