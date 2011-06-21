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

void unfolding(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  
  bool print = true;

  TFile * file = new TFile("preUnfolding.root");
  TH2F * h2ResponseM = (TH2F*) file->Get("h2_response_m");
  TH1F * hDataDist = (TH1F*) file->Get("hData");
  TH1F * hGenDist = (TH1F*) file->Get("hGen");
  TH1F * hAcceptDist = (TH1F*) file->Get("hAccept");

  double lumi = 204.2;
  bool print = false;
  bool pseudo = false;
  int k = 3; //from 2 to 9

  RooUnfold::ErrorTreatment err = "RooUnfold::kCovariance";
  //RooUnfold::ErrorTreatment err = RooUnfold::kCovToy;
  //RooUnfold::ErrorTreatment err = "RooUnfold::kErrors";
 
  plot(h2ResponseM, hDataDist, hGenDist, hAcceptDist, "vsum", lumi, k, err, print, pseudo); 

}

void plot(TH2* h2_response_m, TH1F* hData, TH1F* hGenDist, TH1F* accept, const TString &var, const double & lumi, int & k, RooUnfold::ErrorTreatment& err, bool print, bool pseudo){

  const TH1* h_genMC = h2_response_m->ProjectionY();
  const TH1* h_recMC = h2_response_m->ProjectionX();
 
  unfoldingPlot(h_genMC, h_recMC, h2_response_m,  hData, hGenDist, accept, Form("%s",var.Data()), lumi, k, err, print, pseudo);

}

