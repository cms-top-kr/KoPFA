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
bool print = true;

void SetLatex(double x, double y, TString decayMode){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(x,y,"at #sqrt{s} = 7 TeV");
  if( decayMode.Contains("MuMu")) text = "in #mu#mu decay mode";
  if( decayMode.Contains("MuEl")) text = "in e#mu decay mode";
  if( decayMode.Contains("ElEl")) text = "in ee decay mode";
  label->DrawLatex(x,y-0.05,text);
}

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

  TGraphAsymmErrors* gr = new TGraphAsymmErrors;
  TGraphAsymmErrors* grmean = new TGraphAsymmErrors;
  for(int i=0; i < nDet; i++){
    h[i]->Fit("gaus");
    g[i]  = h[i]->GetFunction("gaus");
    double Mean = h[i]->GetMean();
    double rms = h[i]->GetRMS();
    double mean = g[i]->GetParameter(1);
    double sigma = g[i]->GetParameter(2);
    double mass = (detBins[i+1] + detBins[i])/2;
    double meanerr = g[i]->GetParError(1);
    double sigmaerr = g[i]->GetParError(2);
    gr->SetPoint(i,mass,sigma);
    gr->SetPointEYhigh(i,sigmaerr);
    gr->SetPointEYlow(i,sigmaerr);
    grmean->SetPoint(i,mass,mean);
    grmean->SetPointEYhigh(i,meanerr);
    grmean->SetPointEYlow(i,meanerr);
    cout <<  "point= " << mass <<  " MEAN= " <<  mean << " RMS= " << rms << " sigma= " << sigma << " error= " << sigmaerr << " mean= " << mean << " error= " << meanerr << "\n";
  }

  TCanvas *c_resvsmass = new TCanvas(Form("c_resvsmass_%s",name.Data()),Form("c_resvsmass_%s",name.Data()),400,400);
  gr->Draw("ALP");
  gr->GetXaxis()->SetTitle("Generated Mass (GeV)");
  gr->GetYaxis()->SetTitle("Resolution (#DeltaM/M)");
  gr->SetMaximum(0.48);
  gr->SetMinimum(0.08);
  SetLatex(0.55,0.85,decayMode);

  TCanvas *c_meanvsmass = new TCanvas(Form("c_meanvsmass_%s",name.Data()),Form("c_meanvsmass_%s",name.Data()),400,400);
  grmean->Draw("ALP");
  grmean->GetXaxis()->SetTitle("Generated Mass (GeV)");
  grmean->GetYaxis()->SetTitle("Mean <#DeltaM/M>");
  grmean->SetMaximum(0.1);
  grmean->SetMinimum(-0.3);
  SetLatex(0.55,0.85,decayMode);

  if(print){
    c_res->Print(Form("c_resCanvas_%s_%s.eps",name.Data(),decayMode.Data()));
    c_res->Print(Form("c_resCanvas_%s_%s.png",name.Data(),decayMode.Data()));
    c_resvsmass->Print(Form("c_resolution_%s_%s.eps",name.Data(),decayMode.Data()));
    c_resvsmass->Print(Form("c_resolution_%s_%s.png",name.Data(),decayMode.Data()));
    c_meanvsmass->Print(Form("c_mean_%s_%s.eps",name.Data(),decayMode.Data()));
    c_meanvsmass->Print(Form("c_mean_%s_%s.png",name.Data(),decayMode.Data()));
  }
}


TString decayMode = "MuMu";

void relttbar(){

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  const std::string mcPath = "/home/tjkim/ntuple/top/"+decayMode+"/MC/Spring11/vallot_TTbarTuneZ2.root";

  TFile * f = new TFile(mcPath.c_str());
  TTree * t = (TTree *) f->Get(decayMode+"/tree");

  TCut finalcut = "Z.mass() > 12 && relIso04lep1 < 0.20 && relIso04lep2 < 0.20 && Z.sign() < 0 && @jetspt30.size() >= 2 && abs(Z.mass() - 91 ) > 15 && MET > 30";
  //TCut finalcut = "Z.mass() > 12 && relIso04lep1 < 0.20 && relIso04lep2 < 0.20 && Z.sign() < 0 && @jetspt30.size() >= 2 && abs(Z.mass() - 91 ) > 15";
  TCut mt2 = "maosMt2 > 120 && maosMt2 < 230";
  //TCut mt2 = "ttbar.Mt2() > 120 && ttbar.Mt2() < 230";
  TCut cut = finalcut && mt2;
 
  //resolutionPlot(t, "maosttbarM", finalcut, "maos");
  //resolutionPlot(t, "vsumttbarM", finalcut, "vsum");
  resolutionPlot(t, "ttbar.M()", cut, "vsum");
  //resolutionPlot(t, "ttbar.maosM()", cut, "maos");

}
