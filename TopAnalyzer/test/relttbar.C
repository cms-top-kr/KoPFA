#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"

using namespace std;
bool print = false;

void resolutionPlot(TTree* t1, TString var, TCut cut, TString name){

  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1 *h[9];
  TF1 *g[9];

  TCanvas *c_res = new TCanvas(Form("c_res_%s",name.Data()),Form("c_res_%s",name.Data()),2000.1500);
  c_res->Divide(3,3);  

  for(int i=0; i < nDet; i++){
    c_res->cd(i+1);
    double lowEdge = detBins[i];
    double highEdge = detBins[i+1];
    std::ostringstream massCut;
    massCut.str(std::string());
    massCut << "(  genttbarM > " <<  lowEdge << ") && ( genttbarM < " << highEdge << ")" ;
    //cout << massCut.str().c_str() << endl; 
    TCut mCut = massCut.str().c_str();
    TCut tmpcut = cut && mCut;
    h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 60, -3,3);
    t1->Project(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()),Form("(%sttbarM-genttbarM)/genttbarM",var.Data()), tmpcut );
    h[i]->Draw();
    gStyle->SetStatH(0.4); 
    gStyle->SetStatW(0.2); 
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatBorderSize(1);
  }

  TCanvas *c_resvsmass = new TCanvas(Form("c_resvsmass_%s",name.Data()),Form("c_resvsmass_%s",name.Data()),400,400);
  TGraphAsymmErrors* gr = new TGraphAsymmErrors;
  for(int i=0; i < nDet; i++){
    h[i]->Fit("gaus");
    g[i]  = h[i]->GetFunction("gaus");
    double Mean = h[i]->GetMean();
    double rms = h[i]->GetRMS();
    double mean = g[i]->GetParameter(1);
    double sigma = g[i]->GetParameter(2);
    double mass = (detBins[i+1] + detBins[i])/2;
    gr->SetPoint(i,mass,sigma);
    cout <<  "point= " << mass <<  " MEAN= " <<  mean << " RMS= " << rms << " sigma= " << sigma << "\n";
  }
  gr->Draw("ALP");
  gr->GetXaxis()->SetTitle("Generated Mass (GeV)");
  gr->GetYaxis()->SetTitle("Resolution (#DeltaM/M)");

  if(print){

  }
}


void relttbar(){

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile * f = new TFile("/home/tjkim/ntuple/top/MuMu/MC/Spring11/vallot_TTbarTuneZ2.root");
  TTree * t = (TTree *) f->Get("MuMu/tree");

  TCut finalcut = "Z.mass() > 12 && relIso04lep1 < 0.20 && relIso04lep2 < 0.20 && Z.sign() < 0 && @jetspt30.size() >= 2 && abs(Z.mass() - 91 ) > 15 && MET > 30";
  TCut mt2 = "maosMt2 > 150 && maosMt2 < 250";
  TCut cut = finalcut && mt2;
 
  //resolutionPlot(t, "maos", cut, "maos");
  resolutionPlot(t, "vsum", finalcut, "vsum");

}
