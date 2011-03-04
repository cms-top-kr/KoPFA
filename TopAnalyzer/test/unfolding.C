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

#include "unfold.h"

void unfolding(const TString& decayMode = "MuEl"){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  
  bool print = true;

  const std::string mcPath = "/home/tjkim/ntuple/top/"+decayMode+"/MC/Fall10_bugfixed/vallot_TTbar.root";
  const std::string rdPath = "MuEl.root";

  TFile * file = new TFile(mcPath.c_str());
  TTree * tree = (TTree *) file->Get(decayMode+"/tree");

  TFile * f_data = new TFile(rdPath.c_str());
  TH1F *hData = (TH1F*) f_data->Get("Step_6/hData_Step_6_vsumMAlt");

  TCut precut = "Z.mass() > 12 && relIso04lep1 < 0.21 && relIso04lep2 < 0.26 && Z.sign() < 0 && @jetspt30.size() >= 2";
  TCut mt2 = "maosMt2 > 140";
  TCut cut = precut;
  double lumi = 36.1; //pb-1
  //double lumi = 1000; //pb-1
  double lumi_ttbar = 1000000/157.5; //pb-1
  double scale_ttbar = lumi/lumi_ttbar;

  plot(tree, hData, tree, "vsum", scale_ttbar, cut, true);
  //plot(t,t_data,t_ttbar1fb, "maos",scale_ttbar, cut, true);
 
}

