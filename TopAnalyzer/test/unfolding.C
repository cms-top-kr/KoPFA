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

  plot(h2ResponseM, hDataDist, hGenDist, hAcceptDist, "vsum", 500000, 36, true, true); 

}

void plot(TH2* h2_response_m, TH1F* hData, TH1F* hGenDist, TH1F* accept, const TString &var, const double & genEvt, const double &lumi, bool print, bool pseudo){

  double lumiTTbar = genEvt/157.5; //pb-1
  double scale = lumi/lumiTTbar;

  const TH1* h_genMC = h2_response_m->ProjectionY();
  const TH1* h_recMC = h2_response_m->ProjectionX();

  unfoldingPlot(h_genMC, h_recMC, h2_response_m,  hData, hGenDist, accept, scale, Form("%s",var.Data()), lumi, print, pseudo);
  cout <<"ici" << endl;

}

