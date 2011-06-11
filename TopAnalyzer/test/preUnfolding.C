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

  //decayMode.push_back("MuEl");
  //decayMode.push_back("ElEl");
  decayMode.push_back("MuMu");

  //mcPath.push_back("/home/tjkim/ntuple/top/MuEl/MC/Spring11/vallot_TTbarTuneZ2.root");
  //mcPath.push_back("/home/tjkim/ntuple/top/ElEl/MC/Spring11/vallot_TTbarTuneZ2.root");
  mcPath.push_back("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_TTbarTuneZ2.root");

  //rdPath.push_back("MuEl_204/MuEl.root");
  //rdPath.push_back("ElEl_204/ElEl.root");
  rdPath.push_back("MuMu_204/MuMu.root");

  //mcPath.push_back("/data/common/Top/ntuple/MuEl/MC/v0/vallot_TTbar.root");
  //mcPath.push_back("/data/common/Top/ntuple/ElEl/MC/v1/vallot_TTbar.root"); 
  //mcPath.push_back("/data/common/Top/ntuple/MuMu/MC/v0/vallot_TTbar.root");
  //rdPath.push_back("/data/common/Top/finalHisto/v0/MuEl.root");
  //rdPath.push_back("/data/common/Top/finalHisto/v0/ElEl.root");
  //rdPath.push_back("/data/common/Top/finalHisto/v0/MuMu.root");

  const std::string cutStep = "Step_6";

  TH2F * h2ResponseM = getResponseM(mcPath, rdPath, cutStep,  "ttbar.M()", decayMode, "vsum");
  TH1F * hData = getMeasuredHisto(rdPath, cutStep);
  TH1F * hGenDist = getGenDistHisto(mcPath, rdPath, cutStep, decayMode, "vsum");
  TH1F * hAccept =  getAcceptanceHisto(mcPath, rdPath, cutStep,  decayMode, "vsum");
  TGraphAsymmErrors*  gAccept =  getAcceptance(mcPath, rdPath, cutStep, decayMode, "vsum");

  //vector<std::string> pseudoPath;
  //pseudoPath.push_back("vallot_TTbar1fb_MuEl.root");
  //TH1F *hDataPseudo = getMeasuredHistoPseudo(pseudoPath, rdPath, cutStep,  "vsum", decayMode, 3.6/10.0);

  TFile* f = TFile::Open("preUnfolding.root", "recreate");

  h2ResponseM->Write();
  hData->Write();
  hGenDist->Write();
  hAccept->Write();
  gAccept->Write();

  f->Write();  
  f->Close();

}


