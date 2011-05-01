#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"
#include "TGraphAsymmErrors.h"

using namespace std;
bool print = false;

void resolutionPlot(TTree* t1, TString var, TCut cut, TString name){

  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1 *h[9];
  TF1 *g[9];

  TCanvas *c_res = new TCanvas(Form("c_res_%s",name.Data()),Form("c_res_%s",name.Data()),2000.1800);
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
    t1->Project(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()),Form("(%s-genttbarM)/genttbarM",var.Data()), tmpcut );
    h[i]->Draw();
    gStyle->SetStatH(0.4); 
    gStyle->SetStatW(0.2); 
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatBorderSize(1);
    h[i]->SetTitle(Form("%1.0f-%1.0f GeV",detBins[i],detBins[i+1]));
    h[i]->GetXaxis()->SetTitle("#DeltaM/M");
    h[i]->GetYaxis()->SetTitle("Events");
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
    c_res->Print(Form("c_resCanvas_%s.eps",name.Data()));
    c_res->Print(Form("c_resCanvas_%s.png",name.Data()));
    c_resvsmass->Print(Form("c_resolution_%s.eps",name.Data()));
    c_resvsmass->Print(Form("c_resolution_%s.png",name.Data()));
  }
}


TString decayMode = "MuEl";

void relttbar(){

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  const std::string mcPath = "/home/tjkim/ntuple/top/"+decayMode+"/MC/Spring11/vallot_TTbarTuneZ2.root";

  TFile * f = new TFile(mcPath.c_str());
  TTree * t = (TTree *) f->Get(decayMode+"/tree");

  TCut finalcut = "Z.mass() > 12 && relIso04lep1 < 0.20 && relIso04lep2 < 0.20 && Z.sign() < 0 && @jetspt30.size() >= 2 && abs(Z.mass() - 91 ) > 15 && MET > 30";
  //TCut mt2 = "maosMt2 > 150 && maosMt2 < 250";
  TCut mt2 = "ttbar.Mt2() > 120 && ttbar.Mt2() < 200";
  TCut cut = finalcut && mt2;
 
  //resolutionPlot(t, "maosttbarM", cut, "maos");
  //resolutionPlot(t, "vsumttbarM", finalcut, "vsum");
  resolutionPlot(t, "ttbar.M()", finalcut, "vsum");
  //resolutionPlot(t, "ttbar.maosM()", finalcut, "maos");

}
