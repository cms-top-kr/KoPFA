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

//default
float detBins[] = {0, 345, 400, 450, 500, 550, 600, 700, 800, 1400}; // 9 bins
float genBins[] = {0, 345, 400, 450, 500, 550, 600, 700, 800, 1400}; // 9 bins

int nDet = sizeof(detBins)/sizeof(float) - 1;
int nGen = sizeof(genBins)/sizeof(float) - 1;

#include "preUnfolding.h"

void crossXmass(int k=4){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0011);

  TFile * file = new TFile("preUnfolding.root");
  TFile * file_unfolded = new TFile("unfolded.root");
  TFile * file_acceptance = new TFile("acceptance.root");
  TFile * file_truthFinal = new TFile("truthFinal.root");
  TFile * file_zprime = new TFile("ZPrimeM1000W1.root");

  //truth level after reconstruction level selection
  TH1F * hGenDistMADGRAPH = (TH1F*) file->Get("hTruth_MadGraph");
  TH1F * hGenDistPOWHEG = (TH1F*) file->Get("hTruth_Powheg");
  //unfolded plot
  TH1F * h_unfold = (TH1F*) file_unfolded->Get("unfolded");
  //acceptance 
  TH1F * hAcceptDist = (TH1F*) file_acceptance->Get("hAccept_vsum");
  TH1F * hAcceptDistFull = (TH1F*) file_acceptance->Get("hAccept_vsum_Full");
  //truth level for final
  TH1D * hGenMADGRAPH = (TH1D*) file_truthFinal->Get("hTruthFinalMADGRAPH");
  TH1D * hGenPOWHEG = (TH1D*) file_truthFinal->Get("hTruthFinalPOWHEG");
  TH1D * hGenMADGRAPH_Full = (TH1D*) file_truthFinal->Get("hTruthFinalMADGRAPH_Full");
  TH1D * hGenPOWHEG_Full = (TH1D*) file_truthFinal->Get("hTruthFinalPOWHEG_Full");

  double lumi = 1143.22;
  double xsection = 0.820761719054490;

  bool printX = true; //print cross section

  bool norm = false;
  TH1F* hSigmaData = getMeasuredCrossSection(h_unfold, hAcceptDistFull,lumi,norm, true, "unfolded",false);   
  TH1F* hSigmaTruthHisto = getTruthCrossSection(hGenDistMADGRAPH, hGenMADGRAPH_Full, lumi, norm, false, 1, printX);

  TTree* genTree = (TTree*)file_zprime->Get("ttbarGenAna/tree");
  TH1D* hZPrime = new TH1D("hZPrime","hZPrime",nGen, genBins);
  genTree->Project("hZPrime", "mTT");
  TH1F* hSigmaZPrimeHisto = new TH1F("hSigmaZPrimeHisto","hSigmaZPrimeHisto", nGen, genBins);
  for(int i=1; i <= hSigmaZPrimeHisto->GetNbinsX(); i++){
    double dsigma = xsection * hZPrime->GetBinContent(i) / ( hZPrime->GetBinWidth(i) * hZPrime->Integral() );
    hSigmaZPrimeHisto->SetBinContent(i,dsigma);
  }

  TCanvas * c_Xmass = new TCanvas("c_Xmass","c_Xmass",1);
  c_Xmass->SetLogy();

  TH1F* h_Xmass = (TH1F*)h_unfold->Clone("hSigmaData");     
  TH1F* h_Xmass_ttbar = (TH1F*)h_unfold->Clone("hSigmaData");     
  TH1F* h_Xmass_zprime = (TH1F*)h_unfold->Clone("hSigmaData");     

  h_Xmass->Reset();
  h_Xmass_ttbar->Reset();
  h_Xmass_zprime->Reset();

  int nbins = h_unfold->GetNbinsX();
  double total = 0;
  double total_ttbar = 0;
  double total_zprime = 0;

  for(int i=nbins; i >= 1 ;i--){
    double sigma = hSigmaData->GetBinContent(i)*hSigmaData->GetBinWidth(i);
    double sigma_ttbar = hSigmaTruthHisto->GetBinContent(i)*hSigmaTruthHisto->GetBinWidth(i);
    double sigma_zprime = hSigmaZPrimeHisto->GetBinContent(i)*hSigmaZPrimeHisto->GetBinWidth(i);
    total += sigma;
    total_ttbar += sigma_ttbar;
    total_zprime += sigma_zprime;
    cout << hSigmaZPrimeHisto->GetBinContent(i)*hSigmaZPrimeHisto->GetBinWidth(i) << endl;
    h_Xmass->SetBinContent(i, total);
    h_Xmass_ttbar->SetBinContent(i, total_ttbar);
    h_Xmass_zprime->SetBinContent(i, total_zprime);
  }

  THStack *hs = new THStack("hs","zprime plus ttbar");
  h_Xmass_ttbar->SetFillColor(2);
  h_Xmass_zprime->SetLineColor(4);
  h_Xmass_zprime->SetLineWidth(2);
  hs->Add(h_Xmass_ttbar);
  hs->Add(h_Xmass_zprime);
  //h_Xmass->GetYaxis()->SetTitle("#int_{x}^{infty} d#sigma/dM_{t#bar{t}} dm_{t#bar{t}}");
  //h_Xmass->GetXaxis()->SetTitle(" M_{t#bar{t}}");
  hs->Draw();
  h_Xmass->Draw("same");

}


