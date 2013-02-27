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

void unfoldingbasic(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0011);

  TFile * file = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130208_V00-00-06/vallot_TTbarTuneZ2.root");
  TTree * tree = (TTree*) file->Get("MuMu/tree");

  TH2F * m = new TH2F("m","m",10,0,1000,10,0,1000);
  TH1F * h_input = new TH1F("h_input","h_input",10,0,1000);

  double n = tree->GetEntries();
  cout << "total = " << n << endl;

  tree->Project("h_input","vsumttbarM","");
  tree->Project("m","genttbarM:vsumttbarM","");

  const TH1* h_gen = m->ProjectionY();
  const TH1* h_rec = m->ProjectionX();

  RooUnfoldResponse *response = new RooUnfoldResponse(h_rec, h_gen, m);
  RooUnfold* unfold = 0;
  unfold = new RooUnfoldSvd(response, h_input, 2);

  RooUnfold::ErrorTreatment err = RooUnfold::kCovariance; //2
  TH1F* h_unfold = (TH1F*) unfold->Hreco(err);

  TCanvas *c = new TCanvas("c","c",1);
  h_unfold->SetLineColor(2);
  h_unfold->SetLineWidth(2);
  h_gen->SetLineColor(4);
  h_gen->SetLineWidth(2);
  h_gen->Draw();
  h_unfold->Draw("same");

}
