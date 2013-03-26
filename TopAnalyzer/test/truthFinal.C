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
#include "norm.h"
#include "DXSectionParameters.h"
#include "preUnfolding.h"

void defaultStyle();

void truthFinal(){

  defaultStyle();

  //mc truth level for full phase space or visible
  TFile * f_MadGraph = new TFile("$WORK/store/GenHisto/topGenHisto_madgraph.root");
  TFile * f_POWHEG = new TFile("$WORK/store/GenHisto/topGenHisto_powheg.root");
  TFile * f_MCNLO = new TFile("$WORK/store/GenHisto/topGenHisto_mcatnlo_v2.root");
  TFile * f_MCNLO_old = new TFile("$WORK/data/export/common/Top/ntuple/ttbar_ntuple_cteq6m_dilepton_v20111028.root");

  //truth level in visible phase space
  cout << "producing truth level plots..." << endl;

  //madgraoh
  TH1* hMadGraphFull = (TH1*) f_MadGraph->Get("topDecayGenHisto/hMtt_Full");
  TH1* hMadGraphPtcl = (TH1*) f_MadGraph->Get("topDecayGenHisto/hMtt_DIL_Ptcl_NoTau");
  TH1* hMadGraphPton = (TH1*) f_MadGraph->Get("topDecayGenHisto/hMtt_DIL_Pton_NoTau");

  //powheg
  TH1* hPOWHEGFull = (TH1*) f_POWHEG->Get("topDecayGenHisto/hMtt_Full");
  TH1* hPOWHEGPtcl = (TH1*) f_POWHEG->Get("topDecayGenHisto/hMtt_DIL_Ptcl_NoTau");
  TH1* hPOWHEGPton = (TH1*) f_POWHEG->Get("topDecayGenHisto/hMtt_DIL_Pton_NoTau");

  //mcatnlo
  TH1* hMCNLOFull = (TH1*) f_MCNLO->Get("topDecayGenHisto/hMtt_Full");
  TH1* hMCNLOPtcl = (TH1*) f_MCNLO->Get("topDecayGenHisto/hMtt_DIL_Ptcl_NoTau");
  TH1* hMCNLOPton = (TH1*) f_MCNLO->Get("topDecayGenHisto/hMtt_DIL_Pton_NoTau");
  TH1* hMCNLO = (TH1*) f_MCNLO_old->Get("hVisTTbarM");
  TH1* hMCNLO_Up = (TH1*) f_MCNLO_old->Get("hVisTTbarM_Up");
  TH1* hMCNLO_Down = (TH1*) f_MCNLO_old->Get("hVisTTbarM_Down");

  TFile* f = TFile::Open("truthFinal.root", "recreate");

  double lumi =  Lumi2011;
  double Xsection = X_TTbar_7TeV;

  double lumi_madgraph = hMadGraphFull->GetEntries() / Xsection;
  double lumi_powheg = hPOWHEGFull->GetEntries() / Xsection;
  double lumi_mcatnlo = hMCNLO->GetEntries() / Xsection;
  double scale_madgraph = lumi / lumi_madgraph;
  double scale_powheg = lumi / lumi_powheg;
  double scale_mcatnlo = lumi / lumi_mcatnlo;

  hMadGraphFull->Scale(scale_madgraph);
  hMadGraphPtcl->Scale(scale_madgraph);
  hMadGraphPton->Scale(scale_madgraph);
  hPOWHEGFull->Scale(scale_powheg);
  hPOWHEGPtcl->Scale(scale_powheg);
  hPOWHEGPton->Scale(scale_powheg);
  hMCNLOFull->Scale(scale_mcatnlo);
  hMCNLOPtcl->Scale(scale_mcatnlo);
  hMCNLOPton->Scale(scale_mcatnlo);
  hMadGraphFull->SetName("MadGraph_Full");
  hMadGraphPtcl->SetName("MadGraph_Ptcl");
  hMadGraphPton->SetName("MadGraph_Pton");
  hPOWHEGFull->SetName("POWHEG_Full");
  hPOWHEGPtcl->SetName("POWHEG_Ptcl");
  hPOWHEGPton->SetName("POWHEG_Pton");
  hMCNLOFull->SetName("MCNLO_Full");
  hMCNLOPtcl->SetName("MCNLO_Ptcl");
  hMCNLOPton->SetName("MCNLO_Pton");

  hMadGraphFull->Write();
  hMadGraphPtcl->Write();
  hMadGraphPton->Write();
  hPOWHEGFull->Write();
  hPOWHEGPtcl->Write();
  hPOWHEGPton->Write();
  hMCNLOFull->Write();
  hMCNLOPtcl->Write();
  hMCNLOPton->Write();

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

