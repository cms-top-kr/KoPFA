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

void unfolding(const TString& decayMode = "MuEl"){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  
  bool print = true;

  //const std::string mcPath = "/home/tjkim/ntuple/top/"+decayMode+"/MC/Fall10_bugfixed/vallot_TTbar.root";
  const std::string mcPath = "/data/common/Top/ntuple/"+decayMode+"/MC/v0/vallot_TTbar.root";
  const std::string rdPath = "MuEl.root";
  const std::string pseudoPath = "vallot_TTbar1fb_MuEl.root";

  TFile * file = new TFile(mcPath.c_str());
  TTree * tree = (TTree *) file->Get(decayMode+"/tree");

  TFile * f_data = new TFile(rdPath.c_str());
  TH1F *hData = (TH1F*) f_data->Get("Step_6/hDataSub_Step_6_vsumMAlt");

  TCut precut = "Z.mass() > 12 && relIso04lep1 < 0.21 && relIso04lep2 < 0.26 && Z.sign() < 0 && @jetspt30.size() >= 2";
  TCut mt2 = "maosMt2 > 140";
  TCut cut = precut;

  //to make pesudo data
  TFile * pseudofile = new TFile(pseudoPath.c_str());
  TTree * pseudotree = (TTree *) pseudofile->Get(decayMode+"/tree");
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  int nDet = sizeof(detBins)/sizeof(float) - 1;
  TH1F *hDataPseudo = new TH1F("hDataPseudo","hDataPseudo",nDet, detBins);
  pseudotree->Project("hDataPseudo","vsumttbarM",cut);
  
  plot(tree, hData, tree, "vsum", 1000000, 35.9, cut, true, false); //response tree, data, compared tree, variable, gen events, lumi, cut ,print, pseudo

  //plot(tree, hDataPseudo, tree, "vsum", 1000000, 1000, cut, true, true); //response tree, data, compared tree, variable, gen events, lumi, cut ,print, pseudo

}

void plot(TTree *t_response, TH1F* hData, TTree *t_compare, const TString &var, const double & genEvt, const double &lumi, TCut cut, bool print, bool pseudo){

  double lumiTTbar = genEvt/157.5; //pb-1
  double scale = lumi/lumiTTbar;

  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nGen = sizeof(genBins)/sizeof(float) - 1;
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  int entries = t_response->GetEntries();

  cout << "Entries= " << entries << endl;

  //For response matrix 
  TH1 *h_genMC = new TH1F(Form("h_genMC%s",var.Data()),"h_genMC",nGen,genBins);
  TH1 *h_recMC = new TH1F(Form("h_recMC%s",var.Data()),"h_recMC",nDet,detBins);
  TH2 *h2_response_m = new TH2F(Form("h2_response_m_%s",var.Data()),Form("h2_response_m_%s",var.Data()),nDet,detBins,nGen,genBins);
  t_response->Project(Form("h_genMC%s",var.Data()),"genttbarM",cut, "",entries/2, 0);
  t_response->Project(Form("h_recMC%s",var.Data()),Form("%sttbarM",var.Data()),cut, "",entries/2, 0);
  t_response->Project(Form("h2_response_m_%s",var.Data()),Form("genttbarM:%sttbarM",var.Data()),cut, "", entries/2, 0);

  //For comparison
  TH1 *h_genTTbar = new TH1F(Form("h_genTTbar%s",var.Data()),"h_genTTbar",nGen,genBins);
  TH1 *h_recTTbar = new TH1F(Form("h_recTTbar%s",var.Data()),"h_recTTbar",nDet,detBins);
  t_compare->Project(Form("h_genTTbar%s",var.Data()),"genttbarM", cut,"",entries/2, entries/2);
  t_compare->Project(Form("h_recTTbar%s",var.Data()),Form("%sttbarM",var.Data()), cut,"",entries/2, entries/2);

  //comparison before unfolding
  massPlot(h_genTTbar, h_recTTbar, hData, scale*2);

  //resolutionPlot(t,Form("rel%sM",var.Data()), cut, Form("%s",var.Data()), print);

  //comparison after unfolding
  unfoldingPlot(h_genMC, h_recMC, h2_response_m,  hData, h_genTTbar, scale*2, Form("%s",var.Data()), print, pseudo);

}

