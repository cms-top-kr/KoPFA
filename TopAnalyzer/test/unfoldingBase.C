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

#include <iostream>
#include "TUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/TSVDUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldResponse.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBayes.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldSvd.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBinByBin.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldInvert.h"
#include "unfolding.h"

void unfoldingBase(int k=4){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0011);

  TFile * file = new TFile("preUnfolding.root");
  //response matrix
  TH2F * h2ResponseM = (TH2F*) file->Get("h2_response_m");
  //measured distribution
  TH1F * hDataDist = (TH1F*) file->Get("hData_vsum");
  //truth level after reconstruction level selection to be compared
  TH1F * hGenDistMADGRAPH = (TH1F*) file->Get("hTruth_MadGraph");

  double lumi = 4684;
  bool print = true; //save plots
  bool pseudo = false;
  bool toytest = false;

  RooUnfold::ErrorTreatment err = RooUnfold::kCovariance; //2

  int method = 2; // BinByBin:0 Invert:1 SVD:2 Bayes:3 
  TH1F* h_unfold = unfoldingPlot(method, h2ResponseM,  hDataDist, hGenDistMADGRAPH, "vusm", lumi, k, err, print, pseudo, toytest);

  TFile* f = TFile::Open("unfolded.root", "recreate");
  h_unfold->Write(); 
  f->Write();
  f->Close();

}


