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
#include "HHStyle.h"
#include "unfolding.h"
vector<double> chi2;

void unfolding(int k=4){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0011);

  
  bool print = true;

  TFile * file = new TFile("preUnfolding_pas013.root");
  //response matrix
  TH2F * h2ResponseM = (TH2F*) file->Get("h2_response_m");
  //measured distribution
  TH1F * hDataDist = (TH1F*) file->Get("hData_vsum");
  TH1F * hPseudoDataMADGRAPH = (TH1F*) file->Get("hPseudoData_vsum_MadGraph");
  TH1F * hPseudoDataPOWHEG = (TH1F*) file->Get("hPseudoData_vsum_Powheg");
  //TH1F * hDataDistUp = (TH1F*) file->Get("hData_vsum_up");
  //TH1F * hDataDistDw = (TH1F*) file->Get("hData_vsum_dw");
  //truth level after reconstruction level selection
  TH1F * hGenDistMADGRAPH = (TH1F*) file->Get("hTruth_MadGraph");
  TH1F * hGenDistPOWHEG = (TH1F*) file->Get("hTruth_Powheg");
  TH1F * hAcceptDist = (TH1F*) file->Get("hAccept_vsum");
  //truth level for final
  TH1D * hGenMADGRAPH = (TH1D*) file->Get("hTruthFinalMADGRAPH");
  TH1D * hGenPOWHEG = (TH1D*) file->Get("hTruthFinalPOWHEG");
  TH1D * hGenTTbarM = (TH1D*) file->Get("hVisTTbarM");

  double lumi = 1143.22;
  bool print = false;
  bool pseudo = false;
  bool toytest = false;

  //RooUnfold::ErrorTreatment err = RooUnfold::kNoError;  //0
  //RooUnfold::ErrorTreatment err = RooUnfold::kErrors;  //1
  RooUnfold::ErrorTreatment err = RooUnfold::kCovariance; //2
  //RooUnfold::ErrorTreatment err = RooUnfold::kCovToy; //3

  int method = 2; // BinByBin:0 Invert:1 SVD:2 Bayes:3 
  TH1F* h_unfold = unfoldingPlot(method, h2ResponseM,  hDataDist, hGenDistMADGRAPH, "vusm", lumi, k, err, print, pseudo, toytest);
  //TH1F* h_unfoldup = unfoldingPlot(method, h2ResponseM,  hDataDistUp, hGenDist, "vusm_up", lumi, k, err, print, pseudo, toytest);
  //TH1F* h_unfolddw = unfoldingPlot(method, h2ResponseM,  hDataDistDw, hGenDist, "vusm_dw", lumi, k, err, print, pseudo, toytest);

  //for final plots
  bool norm =  true;
  bool log = true;
  bool bincorr = false;
  bool HBBstyle = false;

  TGraphAsymmErrors* de = FinalPlot(h_unfold, hGenDistMADGRAPH, hAcceptDist, lumi, "unfold_Normalized_simple", "dSigmadM",  0.00001, 0.06, norm, log, bincorr, print);
  //TGraphAsymmErrors* up = FinalPlot(h_unfoldup, hGenDist, hAcceptDist, lumi, "unfold_Normalized_simple_up", "dSigmadM",  0.00001, 0.06, norm, log, bincorr, print);
  //TGraphAsymmErrors* dw = FinalPlot(h_unfolddw, hGenDist, hAcceptDist, lumi, "unfold_Normalized_simple_dw", "dSigmadM",  0.00001, 0.06, norm, log, bincorr, print);

  FinalPlot(h_unfold, hGenDistMADGRAPH, hAcceptDist, hGenMADGRAPH, hGenPOWHEG, hVisTTbarM, lumi, "unfold_Normalized", "dSigmadM",  0.00001, 0.06, norm, log, bincorr, print, HBBstyle);
  
  //getUncertainty(de,up,dw); 
  //For PAS TOP-11-013
  bincorr = true;
  HBBstyle = true;
  if(HBBstyle){
    gROOT->SetStyle("Plain");
    setHHStyle(*gStyle);
  }

  //FinalPlot(h_unfold, hGenDistMADGRAPH, hAcceptDist, hGenMADGRAPH, hGenPOWHEG, hVisTTbarM, lumi, "unfold_Normalized", "dSigmadM",  0.00001, 0.06, norm, log, bincorr, print, HBBstyle);

  //chi2 test
  //int n = 5;
  //for(int i=1; i <=n ;i++){
  //  plot(h2ResponseM, hDataDist, hGenDist, hAcceptDist, "vsum", lumi, i, err, print, pseudo); 
  //}

  //for(int i=0; i<n ;i++){
  //  cout << "k term= " << i+1 << " : " << chi2[i] << endl;
  //}
}


