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
  
  bool print = false;

  vector<TString> decayMode;
  decayMode.push_back("MuEl");
  //decayMode.push_back("ElEl");
  //decayMode.push_back("MuMu");

  vector<std::string> mcPath;
  vector<std::string> rdPath;
  vector<std::string> pseudoPath;

  mcPath.push_back("/data/common/Top/ntuple/MuEl/MC/v0/vallot_TTbar.root");
  //mcPath.push_back("/data/common/Top/ntuple/ElEl/MC/v1/vallot_TTbar.root"); 
  //mcPath.push_back("/data/common/Top/ntuple/MuMu/MC/v0/vallot_TTbar.root");
  rdPath.push_back("/data/common/Top/finalHisto/v0/MuEl.root");
  //rdPath.push_back("/data/common/Top/finalHisto/v0/ElEl.root");
  //rdPath.push_back("/data/common/Top/finalHisto/v0/MuMu.root");

  pseudoPath.push_back("vallot_TTbar1fb_MuEl.root");

  const std::string cutStep = "Step_6";

  TH1F *hData = getMeasuredHisto(rdPath, cutStep);
  TH1F *hDataPseudo = getMeasuredHistoPseudo(pseudoPath, rdPath, cutStep,  "vsum", decayMode, 3.6/10.0);
  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "vsum", decayMode);
  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep,  "vsum", decayMode);

  TGraphAsymmErrors* accept =  getAcceptance(mcPath, rdPath, cutStep,  "vsum", decayMode);
  
  //response tree, data, compared histo, variable, gen events, lumi, print, pseudo
  //plot(h2ResponseM, hData, hGenDist, accept, "vsum", 1000000, 35.9, true, false); 
  plot(h2ResponseM, hDataPseudo, hGenDist, accept, "vsum", 1000000, 360, false, true); 

}

void plot(TH2F* h2_response_m, TH1F* hData, TH1F* hGenDist, TGraphAsymmErrors* accept, const TString &var, const double & genEvt, const double &lumi, bool print, bool pseudo){

  double lumiTTbar = genEvt/157.5; //pb-1
  double scale = lumi/lumiTTbar;

  h_genMC = h2_response_m->ProjectionY();
  h_recMC = h2_response_m->ProjectionX();

  unfoldingPlot(h_genMC, h_recMC, h2_response_m,  hData, hGenDist, accept, scale*2, Form("%s",var.Data()), lumi, print, pseudo);

}

