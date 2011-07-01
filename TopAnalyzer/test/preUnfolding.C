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
#include "preUnfolding.h"

void preUnfolding(){

  vector<TString> decayMode;
  vector<std::string> mcPath;
  vector<std::string> rdPath;

  decayMode.push_back("MuEl");
  decayMode.push_back("ElEl");
  decayMode.push_back("MuMu");

  mcPath.push_back("/home/tjkim/ntuple/top/MuEl/MC/Spring11/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/home/tjkim/ntuple/top/ElEl/MC/Spring11/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_TTbarTuneZ2.root");

  rdPath.push_back("MuEl_204/MuEl.root");
  rdPath.push_back("ElEl_204/ElEl.root");
  rdPath.push_back("MuMu_204/MuMu.root");

  const std::string cutStep = "Step_7";
  //double scale = 204.2/6349.2; 
  double scale = 1000/6349.2; 
  bool split = true;

  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "ttbar.M()", decayMode, split ,"vsum");

  //TH1F * hData = getMeasuredHisto(rdPath, cutStep);  //real data
  TH1F * hData = getMeasuredHistoPseudo(mcPath, rdPath, cutStep, "ttbar.M()", decayMode, scale, "vsum"); //pseudo data

  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, scale, split, "vsum");
  TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, "vsum");

  TFile* f = TFile::Open("preUnfolding.root", "recreate");

  h2ResponseM->Write();
  hData->Write();
  hGenDist->Write();
  hAccept->Write();

  f->Write();  
  f->Close();

}


