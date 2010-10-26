#include "TFile.h"

void isoWZ(){
  TFile *f1 = new TFile("vallot_QCD.root");
  TFile *f2 = new TFile("vallot_WJets.root");
  TFile *f3 = new TFile("vallot_ZJets.root");
  TString v =  "(chIso+nhIso+phIso)/pt"; 
  plot(f1,f2,f3,v);
}

void plot(TFile* f1, TFile* f2, TFile* f3, const TString & v){

  TCanvas *c = new TCanvas("c","c",1);
  TH1* h_QCD = new TH1F("h_QCD","h_QCD",120,0,1.2);
  TH1* h_W = new TH1F("h_W","h_W",120,0,1.2);
  TH1* h_Z = new TH1F("h_Z","h_Z",120,0,1.2);
 
  TTree * QCD = (TTree *) f1->Get("MuonAna/tree");
  TTree * W = (TTree *) f2->Get("MuonAna/tree");
  TTree * Z = (TTree *) f3->Get("MuonAna/tree");
 
  QCD->Project("h_QCD",Form("%s",v.Data()));
  W->Project("h_W",Form("%s",v.Data()));
  Z->Project("h_Z",Form("%s",v.Data()));

  TGraph *gr_W = new TGraph();  
  TGraph *gr_Z = new TGraph();  
  double wpQCD = 0;
  double wpW =0;
  double wpZ =0;
  for(int i=1 ; i < 20 ; i++){
    double bin = i*2+3;
    double point = h_QCD->GetBinLowEdge(bin)+h_QCD->GetBinWidth(bin);
    double effQCD = h_QCD->Integral(1,bin)/h_QCD->GetEntries(); 
    double effW = h_W->Integral(1,bin)/h_W->GetEntries();
    double effZ = h_Z->Integral(1,bin)/h_Z->GetEntries();

    cout << "[" << point << "]:" << "QCD eff= " << effQCD << " W eff= " << effW << " Z eff= " << effZ << endl;
    if( point == 0.21 ){
      wpQCD = effQCD;
      wpW = effW;
      wpZ = effZ;
    }
    gr_W->SetPoint(i-1, effQCD, effW);
    gr_Z->SetPoint(i-1, effQCD, effZ);
  }

  gr_W->SetLineColor(4);
  gr_W->SetLineWidth(2);
  gr_W->SetMarkerColor(4);
  gr_W->SetMarkerSize(1.1);
  gr_W->SetMarkerStyle(20);

  gr_Z->SetLineColor(2);
  gr_Z->SetLineWidth(2);
  gr_Z->SetMarkerColor(2);
  gr_Z->SetMarkerSize(1.1);
  gr_Z->SetMarkerStyle(20);

  gr_W->GetYaxis()->SetTitle("Signal");
  gr_W->GetXaxis()->SetTitle("QCD");

  gr_W->Draw("ACPsame");
  gr_Z->Draw("CPsame");

  //lineW = new TArrow(0.0, wpW, wpQCD , wpW);
  //lineZ = new TArrow(0.0, wpZ, wpQCD , wpZ);
  //lineW->Draw("same");
  //lineW->SetLineColor(2);
  //lineW->SetLineWidth(3);
  //lineW->SetLineStyle(2);
  //lineZ->Draw("same");
  //lineZ->SetLineColor(4);
  //lineZ->SetLineWidth(3);
  //lineZ->SetLineStyle(2);

  pointW = new TEllipse(wpQCD,wpW,0.0035,0.0035);
  pointZ = new TEllipse(wpQCD,wpZ,0.0035,0.0035);
  pointW->SetFillColor(3);
  pointZ->SetFillColor(3);
  pointW->Draw("same");
  pointZ->Draw("same");

  TLegend *l= new TLegend(0.4,0.3,0.7,0.45);
  l->AddEntry(gr_Z,"Z #rightarrow #mu#mu","PL");
  l->AddEntry(gr_W,"W #rightarrow #mu#nu","PL");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  
}
