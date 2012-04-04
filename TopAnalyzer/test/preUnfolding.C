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

void preUnfolding(){

  defaultStyle();

  vector<TString> decayMode;
  vector<std::string> mcPath;
  vector<std::string> mePath;
  vector<std::string> mePath2;
  vector<std::string> mePath3;
  vector<std::string> rdPath;

  decayMode.push_back("MuEl");
  decayMode.push_back("ElEl");
  decayMode.push_back("MuMu");

  //response matrix
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/MuEl/MC/Fall11_v1/vallot_TTbarTuneZ2.root");
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/ElEl/MC/Fall11_v1/vallot_TTbarTuneZ2.root");
  mcPath.push_back("$WORK/data/export/common/Top/ntuple/MuMu/MC/Fall11_v1/vallot_TTbarTuneZ2.root");

  //measured mc distribution after final cut
  //mePath.push_back("$WORK/data/export/common/Top/ntuple/MuEl/MC/Summer11_new/vallot_TTbarPowheg.root");
  //mePath.push_back("$WORK/data/export/common/Top/ntuple/ElEl/MC/Summer11_new/vallot_TTbarPowheg.root");
  //mePath.push_back("$WORK/data/export/common/Top/ntuple/MuMu/MC/Summer11_new/vallot_TTbarPowheg.root");

  //mePath2.push_back("$WORK/data/export/common/Top/ntuple/MuEl/MC/Summer11_new/vallot_TTbarPowhegPythia.root");
  //mePath2.push_back("$WORK/data/export/common/Top/ntuple/ElEl/MC/Summer11_new/vallot_TTbarPowhegPythia.root");
  //mePath2.push_back("$WORK/data/export/common/Top/ntuple/MuMu/MC/Summer11_new/vallot_TTbarPowhegPythia.root");

  //mePath3.push_back("$WORK/data/export/common/Top/ntuple/MuEl/MC/Summer11_new/vallot_TTbarPowhegHerwig.root");
  //mePath3.push_back("$WORK/data/export/common/Top/ntuple/ElEl/MC/Summer11_new/vallot_TTbarPowhegHerwig.root");
  //mePath3.push_back("$WORK/data/export/common/Top/ntuple/MuMu/MC/Summer11_new/vallot_TTbarPowhegHerwig.root");

  //measured data distribution after final cut:version 6->take into account QCD
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/MuEl.root");
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/ElEl.root");
  //rdPath.push_back("/data/export/common/Top/finalHisto/v6/MuMu.root");
  rdPath.push_back("result_Apr2/MuEl_Apr2/MuEl.root");
  rdPath.push_back("result_Apr2/ElEl_Apr2/ElEl.root");
  rdPath.push_back("result_Apr2/MuMu_Apr2/MuMu.root");

  const std::string cutStep = "Step_7";
  double lumi = 5000.00;
  double ttbarX = 164.6;
  double powhegX = ttbarX * 0.11; //branching ratio as this is dilepton decay mode only
  bool split = false;//use full statistics if it is false
  string recon = "vsum";

  //response matrix
  cout << "producing repsonse matrix..." << endl;
  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "ttbar.M()", decayMode, split ,recon);
  
  //after final selection
  cout << "producing reconstructed level distributions..." << endl;
  TH1F * hData = getMeasuredHisto(rdPath, cutStep, "vsumMAlt", recon);  //real data
  TH1F * hDataPseudo = getMeasuredHistoPseudo(mcPath, rdPath, cutStep, "ttbar.M()", decayMode, lumi, ttbarX, recon+"_MadGraph"); //pseudo data
  TH1F * hDataPseudoWeighted = getMeasuredHistoPseudo(mcPath, rdPath, cutStep, "ttbar.M()", decayMode, lumi, ttbarX, recon+"_MadGraph_Weighted", "1.0+(genttbarM-450)*0.005"); //pseudo data
  //TH1F * hDataPseudoPowheg = getMeasuredHistoPseudo(mePath, rdPath, cutStep, "ttbar.M()", decayMode, lumi, powhegX, recon+"_Powheg"); //pseudo data
  //TH1F * hDataPseudoPowhegPythia = getMeasuredHistoPseudo(mePath2, rdPath, cutStep, "ttbar.M()", decayMode, lumi, powhegX, recon+"_PowhegPythia"); //pseudo data
  //TH1F * hDataPseudoPowhegHerwig = getMeasuredHistoPseudo(mePath3, rdPath, cutStep, "ttbar.M()", decayMode, lumi, powhegX, recon+"_PowhegHerwig"); //pseudo data
  
  //truth level after final selection
  cout << "producing truth level plots before correcting acceptance..." << endl;
  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, lumi, ttbarX, split, "MadGraph");
  TH1F * hGenDistWeighted = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, lumi, ttbarX, split, "MadGraph_Weighted", "1.0+(genttbarM-450)*0.005");
  //TH1F * hGenDistPowheg = getGenDistHisto(mePath, rdPath, cutStep, decayMode, lumi, powhegX, split, "Powheg");

  TFile* f = TFile::Open("preUnfolding.root", "recreate");

  //--------------Write into preUnfolding root file------------------------

  h2ResponseM->Write();
  hData->Write();

//Different MC sample for pseudo data
  hDataPseudo->Write();
  hDataPseudoWeighted->Write();
  //hDataPseudoPowheg->Write();
  //hDataPseudoPowhegPythia->Write();
  //hDataPseudoPowhegHerwig->Write();

  hGenDist->Write();
  hGenDistWeighted->Write();
  //hGenDistPowheg->Write();

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

