#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TCut.h"
#include "TLegend.h"
#include <iostream>
#include "TMarker.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"


using namespace std;
void defaultStyle();

double dx = 0;
double dy = 0;
double point03 = 0;

void getHisto(TFile* file, TH1F *h_sig, TH1F * h_bkg, TString s){

  TH1F * h_ttbar = (TH1F*) file->Get("Step_1/hMCSig_TTbar_Step_1_"+s+"lep1");
  TH1F * h_ttbar2 = (TH1F*) file->Get("Step_1/hMCSig_TTbar_Step_1_"+s+"lep2");
  TH1F * h_zll = (TH1F*) file->Get("Step_1/hMC_Zll_Step_1_"+s+"lep1");
  TH1F * h_zll2 = (TH1F*) file->Get("Step_1/hMC_Zll_Step_1_"+s+"lep2");
  TH1F * h_qcd = (TH1F*) file->Get("Step_1/hMC_qcd_Step_1_"+s+"lep1");
  TH1F * h_qcd2 = (TH1F*) file->Get("Step_1/hMC_qcd_Step_1_"+s+"lep2");
  TH1F * h_wjet = (TH1F*) file->Get("Step_1/hMC_Wl_Step_1_"+s+"lep1");
  TH1F * h_wjet2 = (TH1F*) file->Get("Step_1/hMC_Wl_Step_1_"+s+"lep2");

  //Signal  
  h_sig->Add(h_ttbar);
  //h_sig->Add(h_ttbar2);
  //h_sig->Add(h_zll);
  //h_sig->Add(h_zll2);
  //h_sig->Add(h_wjet);
  //h_sig->Add(h_wjet2);

  //Background
  h_bkg->Add(h_qcd);
  //h_bkg->Add(h_qcd2);
  //h_bkg->Add(h_wjet);
  //h_bkg->Add(h_wjet2);

}

void getGraph(TGraph * gr_opt, TGraph * gr_roc, TH1F * h_sig, TH1F * h_bkg, TString name){

  cout << name.Data() << endl;

  double optsoverb = 0;
  double optval = 0;
  double opteff = 0;

  int nbin = h_sig->GetNbinsX();
  cout << "sig= " << h_sig->Integral(1,nbin) << endl;
  cout << "bkg= " << h_bkg->Integral(1,nbin) << endl;

  for(int i=0 ; i < nbin ; i++){
    double bin = i+1;
    double point = h_bkg->GetBinLowEdge(bin)+h_bkg->GetBinWidth(bin);
    double eff_sig = h_sig->Integral(1,bin)/h_sig->Integral(1,nbin+1);
    double eff_bkg = h_bkg->Integral(1,bin)/h_bkg->Integral(1,nbin+1);

    double soverb =  h_sig->Integral(1,bin) / sqrt( h_sig->Integral(1,bin) +  h_bkg->Integral(1,bin));
    //double soverb =  eff_sig / sqrt( eff_bkg + eff_sig);
 
    //debug
    cout << ":[" << point << "]:" << "bkg eff= " << eff_bkg << "(" << h_bkg->Integral(1,bin) << "/" << h_bkg->Integral(1,nbin+2) << ")"  << " sig eff= " << eff_sig << "(" << h_sig->Integral(1,bin) << "/" <<  h_sig->Integral(1,nbin+2) << ")" << " : s/sqrt(s+b)= " << soverb << endl;

    gr_opt->SetPoint(i-1, point, soverb);

    //set max just to make plot pretty
    int max =40;
    if(name.Contains("03")) {
      max = 26;
      if( eff_sig > dy && eff_bkg < dx) cout << "point= " << point << endl;
    }
    if(name.Contains("04")) { 
      max = 29;
      //get the point for circle from last year
      if(point > 0.20 && point < 0.22 ) {
        dx = eff_bkg;
        dy = eff_sig;
        cout << "bkg = " << eff_bkg << " sig= " <<  eff_sig << endl;
      }
    }
    if(name.Contains("05")) max = 30;
    if(name.Contains("Det")) {
      //if(point > 0.14 && point < 0.16 ) {
      //  dx = eff_bkg; 
      //  dy = eff_sig;
      //  cout << "bkg = " << eff_bkg << " sig= " <<  eff_sig << endl;
      //}
    }

    if( i < max ){
      gr_roc->SetPoint(i-1, eff_bkg, eff_sig);
    }

    if( soverb > optsoverb){
      optsoverb = soverb;
      optval = point;
      opteff = eff_sig;
    }
  }

}

void plot(TGraph * gr, TString name){
  TCanvas *c = new TCanvas(Form("c%s",name.Data()),Form("c%s",name.Data()),1);
  gr->SetLineColor(2);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(2);
  gr->SetMarkerSize(1.1);
  gr->SetMarkerStyle(20);
  gr->Draw("ALP");
}
void isoOpt(){

  TFile * file = new TFile("iso/MuMuforIso.root");
  //TFile * fileQCD = new TFile("ElEl_QCDEnhanced.root");

  defaultStyle();

  TH1F * h_sig03 = new TH1F("h_sig03","h_sig",40,0,0.4);
  TH1F * h_bkg03 = new TH1F("h_bkg03","h_bkg",40,0,0.4);
  TH1F * h_sig04 = new TH1F("h_sig04","h_sig",40,0,0.4);
  TH1F * h_bkg04 = new TH1F("h_bkg04","h_bkg",40,0,0.4);
  TH1F * h_sig05 = new TH1F("h_sig05","h_sig",40,0,0.4);
  TH1F * h_bkg05 = new TH1F("h_bkg05","h_bkg",40,0,0.4);
  TH1F * h_sigdet = new TH1F("h_sigdet","h_sig",40,0,0.4);
  TH1F * h_bkgdet = new TH1F("h_bkgdet","h_bkg",40,0,0.4); 

  getHisto(file, h_sig03, h_bkg03, "Iso03");
  getHisto(file, h_sig04, h_bkg04, "Iso04");
  getHisto(file, h_sig05, h_bkg05, "Iso05");
  getHisto(file, h_sigdet, h_bkgdet, "DetIso");

  TGraph *gr_opt03 = new TGraph();
  TGraph *gr_opt04 = new TGraph();
  TGraph *gr_opt05 = new TGraph();
  TGraph *gr_optdet = new TGraph();

  TGraph *gr_roc03 = new TGraph();
  TGraph *gr_roc04 = new TGraph();
  TGraph *gr_roc05 = new TGraph();
  TGraph *gr_rocdet = new TGraph();

  TCanvas *c_roc = new TCanvas("c_roc","c_roc",1);

  getGraph(gr_optdet, gr_rocdet, h_sigdet, h_bkgdet, "DetIso");
  getGraph(gr_opt04, gr_roc04, h_sig04, h_bkg04, "Iso04");
  getGraph(gr_opt03, gr_roc03, h_sig03, h_bkg03, "Iso03");
  getGraph(gr_opt05, gr_roc05, h_sig05, h_bkg05, "Iso05");

  plot(gr_opt03, "iso03");
  plot(gr_opt04, "iso04");
  plot(gr_opt05, "iso05");
  plot(gr_optdet, "DetIso");

  gr_roc03->GetYaxis()->SetTitle("t#bar{t} Isolation Efficiency");
  gr_roc03->GetXaxis()->SetTitle("QCD Isolation Efficiency");
  gr_roc03->SetLineColor(2);
  gr_roc03->SetLineWidth(2);
  gr_roc03->SetMarkerColor(2);
  gr_roc03->SetMarkerSize(0.9);
  gr_roc03->SetMarkerStyle(20);
  gr_roc03->Draw("ALP");

  gr_roc04->SetLineColor(3);
  gr_roc04->SetLineWidth(2);
  gr_roc04->SetMarkerColor(3);
  gr_roc04->SetMarkerSize(0.9);
  gr_roc04->SetMarkerStyle(20);
  gr_roc04->Draw("LP");

  gr_roc05->SetLineColor(4);
  gr_roc05->SetLineWidth(2);
  gr_roc05->SetMarkerColor(4);
  gr_roc05->SetMarkerSize(0.9);
  gr_roc05->SetMarkerStyle(20);
  gr_roc05->Draw("LP");

  gr_rocdet->SetLineColor(6);
  gr_rocdet->SetLineWidth(2);
  gr_rocdet->SetMarkerColor(6);
  gr_rocdet->SetMarkerSize(0.9);
  gr_rocdet->SetMarkerStyle(20);
  gr_rocdet->Draw("LP");

  TMarker *m = new TMarker(dx,dy,24);
  m->SetMarkerSize(2);
  m->Draw();


  TLegend *l= new TLegend(0.58,0.30,0.68,0.50);
  //l->SetHeader("Particle-based");
  l->AddEntry(gr_roc03," pfIso. R= 0.3","p");
  l->AddEntry(gr_roc04," pfIso. R= 0.4","p");
  l->AddEntry(gr_roc05," pfIso. R= 0.5","p");
  l->AddEntry(gr_rocdet," detIso. R= 0.3","p");
  l->SetTextSize(0.05);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  //c_roc->Print("c_roc_ttbar_QCD.eps");
  //c_roc->Print("c_roc_ttbar_QCD.png");

  
}


void defaultStyle()
{
    gROOT->SetStyle("Plain");
    gStyle->SetOptStat(1110);

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0); //remove statistics box
    gStyle->SetOptFit(1);
    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.15);

    gStyle->SetCanvasDefH(500);
    gStyle->SetCanvasDefW(500);

    // For the axis:
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);

    // To make 2D contour colorful
    gStyle->SetPalette(1);

    //gStyle->SetOptTitle(0);
    // Margins:
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.05);

    // For the axis titles:
    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.06, "XYZ");
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.3);

    // For the axis labels:
    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");

}

