#include "TFile.h"

void isoOpt(){

  //TFile * fQCD = new TFile("vallot_data_QCDPt15TOPDIL.root");
  //TFile * fW = new TFile("vallot_data_WJetsMt70Pt15TOPDIL.root");
  TFile * fQCD = new TFile("vallot_QCD.root");
  TFile * fW = new TFile("vallot_WJetsMt70.root");


  TTree * QCD = (TTree *) fQCD->Get("MuonAna/tree");
  TTree * W = (TTree *) fW->Get("MuonAna/tree");

  TH1* h_pf_QCD = new TH1F("h_pf_QCD","h_pf_QCD",120,0,1.2);
  TH1* h_pf_W = new TH1F("h_pf_W","h_pf_W",120,0,1.2);
  TH1* h_de_QCD = new TH1F("h_de_QCD","h_de_QCD",120,0,1.2);
  TH1* h_de_W = new TH1F("h_de_W","h_de_W",120,0,1.2);
  
  //TString pfiso = "(chIsoOpt05+nhIsoOpt05+phIsoOpt05)/pt";
  TString pfiso = "(chIso+nhIso+phIso)/pt";
  TString deiso = "(trackIso+ecalIso+hcalIso)/pt";
  QCD->Project("h_pf_QCD",Form("%s",pfiso.Data()));
  W->Project("h_pf_W",Form("%s",pfiso.Data()));
  QCD->Project("h_de_QCD",Form("%s",deiso.Data()));
  W->Project("h_de_W",Form("%s",deiso.Data()));

  TCanvas *c = new TCanvas("c","c",1);
  TGraph *gr_pf = new TGraph();  
  TGraph *gr_de = new TGraph();  

  for(int i=1 ; i < 50 ; i++){
    double bin = i*2+3;
    double point = h_pf_QCD->GetBinLowEdge(bin)+h_pf_QCD->GetBinWidth(bin);
    double effQCD_pf = h_pf_QCD->Integral(1,bin)/h_pf_QCD->GetEntries(); 
    double effW_pf = h_pf_W->Integral(1,bin)/h_pf_W->GetEntries();

    cout << "pf:[" << point << "]:" << "QCD eff= " << effQCD_pf << " W eff= " << effW_pf << endl;
 
    gr_pf->SetPoint(i-1, effQCD_pf, effW_pf);
  }

  for(int i=1 ; i < 50 ; i++){
    double bin = i*2+1;
    double point = h_de_QCD->GetBinLowEdge(bin)+h_de_QCD->GetBinWidth(bin);
    double effQCD_de = h_de_QCD->Integral(1,bin)/h_de_QCD->GetEntries();
    double effW_de = h_de_W->Integral(1,bin)/h_de_W->GetEntries();

    cout << "de:[" << point << "]:" << "QCD eff= " << effQCD_de << " W eff= " << effW_de << endl;

    gr_de->SetPoint(i-1, effQCD_de, effW_de);
  }


  gr_pf->SetLineColor(2);
  gr_pf->SetLineWidth(2);
  gr_pf->SetMarkerColor(2);
  gr_pf->SetMarkerSize(1.1);
  gr_pf->SetMarkerStyle(20);

  gr_de->SetLineColor(4);
  gr_de->SetLineWidth(2);
  gr_de->SetMarkerColor(4);
  gr_de->SetMarkerSize(1.1);
  gr_de->SetMarkerStyle(20);

  gr_pf->Draw("ACP");
  gr_de->Draw("CPsame");

  TLegend *l= new TLegend(0.4,0.3,0.7,0.45);
  l->AddEntry(gr_pf,"particle based","PL");
  l->AddEntry(gr_de,"detector based","PL");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  
}
