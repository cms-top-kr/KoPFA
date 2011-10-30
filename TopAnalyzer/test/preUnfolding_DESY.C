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

//DESY binning
float detBins[] = {0, 345, 400, 475, 550, 700, 1000}; // 9 bins
float genBins[] = {0, 345, 400, 475, 550, 700, 1000}; // 9 bins

int nDet = sizeof(detBins)/sizeof(float) - 1;
int nGen = sizeof(genBins)/sizeof(float) - 1;

#include "preUnfolding.h"

void defaultStyle();

void preUnfolding_DESY(){

  defaultStyle();

  //mc truth level for full phase space or visible
  TFile * f_MadGraph = new TFile("/data/export/common/Top/ntuple/ttbarGen.root");
  TFile * f_POWHEG = new TFile("/data/export/common/Top/ntuple/Gen/ttbarGen_TTTo2L2Nu2BTuneZ2_Powheg_Summer11_PUS4_v0.root");
  TFile * f_MCNLO = new TFile("/data/export/common/Top/ntuple/ttbar_ntuple_cteq6m_dilepton_v20111028.root");

  TFile * f_DESY_input = new TFile("/data/export/common/Top/ntuple/DESY_Kin/tj.root");
  TFile * f_DESY_response = new TFile("/data/export/common/Top/ntuple/DESY_Kin/rebinned2d_andReallySwappedXY.root");
  TFile * f_DESY_accept = new TFile("/data/export/common/Top/ntuple/DESY_Kin/visibleAndCutsBinned.root");

  double lumi = 1143.22;
  double scale = lumi/22222.22;
  double scale_powheg = lumi/ ( 1000000.0 / (157.5 * 0.11) );

  TCut lepton = "ttbarGen.leptons_[0].pt() > 20 && ttbarGen.leptons_[1].pt() > 20 && abs(ttbarGen.leptons_[0].eta()) < 2.4 && abs(ttbarGen.leptons_[1].eta()) < 2.4";
  TCut bquark = "ttbarGen.bQuarks_[0].pt() > 30 && ttbarGen.bQuarks_[1].pt() > 30 && abs(ttbarGen.bQuarks_[0].eta()) < 2.4 && abs(ttbarGen.bQuarks_[1].eta()) < 2.4";
  TCut visible = lepton && bquark;

  //truth level in visible phase space
  cout << "producing truth level plots..." << endl;
  TH1D* hMadGraph = getTruthHisto(f_MadGraph, "MADGRAPH", scale, visible);
  TH1D* hPOWHEG = getTruthHisto(f_POWHEG, "POWHEG", scale_powheg, visible);
  TH1D* hMCNLO = (TH1D*) f_MCNLO->Get("hVisTTbarM");

  //SVD DESY input
  TH2F * h2ResponseM_DESY = new TH2F("h2ResponseM_DESY","h2ResponseM_DESY",nDet,detBins,nGen,genBins);

  TH2F * h2ResponseM_mm = (TH2F*) f_DESY_response->Get("mumu_rebinned");
  TH2F * h2ResponseM_ee = (TH2F*) f_DESY_response->Get("ee_rebinned");
  TH2F * h2ResponseM_em = (TH2F*) f_DESY_response->Get("emu_rebinned");

  h2ResponseM_DESY->Add(h2ResponseM_mm);
  h2ResponseM_DESY->Add(h2ResponseM_ee);
  h2ResponseM_DESY->Add(h2ResponseM_em);

  TH1F * hData_DESY = new TH1F("hData_DESY","hData_DESY",nDet,detBins);
  TH1F * temp = (TH1F*) f_DESY_input->Get("dataMinusBg_combined_FixedMt_Btag_Yield_TtBar_Mass");
  hData_DESY->SetBinContent(1,0);
  hData_DESY->SetBinContent(2,temp->GetBinContent(1));
  hData_DESY->SetBinContent(3,temp->GetBinContent(2));
  hData_DESY->SetBinContent(4,temp->GetBinContent(3));
  hData_DESY->SetBinContent(5,temp->GetBinContent(4));
  hData_DESY->SetBinContent(6,temp->GetBinContent(5));

  TH1F * hAccept_DESY = new TH1F("hAccept_DESY","hAccept_DESY",nDet,detBins);
  TH1F * hNum_DESY = new TH1F("hNum_DESY","hNum_DESY",nDet,detBins);
  TH1F * hDen_DESY = new TH1F("hDen_DESY","hDen_DESY",nDet,detBins);
  TH1D * hNum_mumu_DESY = (TH1D*) f_DESY_accept->Get("mumu_true_afterCuts");
  TH1D * hDen_mumu_DESY = (TH1D*) f_DESY_accept->Get("mumu_true_visible");
  TH1D * hNum_ee_DESY = (TH1D*) f_DESY_accept->Get("ee_true_afterCuts");
  TH1D * hDen_ee_DESY = (TH1D*) f_DESY_accept->Get("ee_true_visible");
  TH1D * hNum_emu_DESY = (TH1D*) f_DESY_accept->Get("emu_true_afterCuts");
  TH1D * hDen_emu_DESY = (TH1D*) f_DESY_accept->Get("emu_true_visible");

  hNum_DESY->Add(hNum_mumu_DESY);
  hNum_DESY->Add(hNum_ee_DESY);
  hNum_DESY->Add(hNum_emu_DESY);
  hDen_DESY->Add(hDen_mumu_DESY);
  hDen_DESY->Add(hDen_ee_DESY);
  hDen_DESY->Add(hDen_emu_DESY);
  hAccept_DESY->Divide(hNum_DESY,hDen_DESY,1,1);

  TFile* f = TFile::Open("preUnfolding_DESY.root", "recreate");

  //--------------Write into preUnfolding root file------------------------

  hData_DESY->Write();
  h2ResponseM_DESY->Write(); 
  hAccept_DESY->Write();

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

