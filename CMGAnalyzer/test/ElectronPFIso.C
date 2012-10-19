#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void SetLabel(const TString & region){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.55,0.6,"t#bar{t} signal in 53X");
  //label->DrawLatex(0.55,0.6-0.05,Form("%s at #sqrt{s} = 8 TeV",region.Data()));
  label->DrawLatex(0.55,0.6-0.05,Form("%s",region.Data()));
  label->Draw();
}

void Style(TGraphAsymmErrors* g, int c, int style){
  g->SetLineWidth(2);
  g->SetLineStyle(style);
  g->SetLineColor(c);
  g->SetMarkerStyle(20);
  g->SetMarkerColor(c);
  g->SetMarkerSize(0.4);
  g->SetFillColor(c);
  g->SetFillStyle(3001);
  g->GetXaxis()->SetTitle("QCD efficiency");
  g->GetYaxis()->SetTitle("Signal efficiency");
}

TGraphAsymmErrors* ROC( TH1* hSignal, TH1* hQCD){
  TGraphAsymmErrors* out = new TGraphAsymmErrors();
  int nbins = hSignal->GetNbinsX();
  double totalS = hSignal->GetEntries();
  double totalB = hQCD->GetEntries();
  cout << hSignal->GetTitle() << endl;
  cout << "totalS = " << totalS << " totalB= " << totalB << endl;
  for(int i=0 ; i < 40; i++){
    double Bi = hQCD->Integral(1,i+1);
    double Si = hSignal->Integral(1,i+1);
    double eff_qcd = Bi / totalB;
    double eff_signal = Si/ totalS; 
    double err_qcd = sqrt(Bi) / totalB;
    //double purity = 0.9;
    //double eff_qcd_real = ( eff_qcd - eff_signal * ( 1- purity) ) / purity; 
    double soverb = Si/Bi;
    cout << "i= " << 0.01*(i+1) << " signal eff = " << eff_signal << " background eff = " << eff_qcd << " s/s+b= " << soverb << endl ;
    out->SetPoint(i, eff_qcd, eff_signal);
    out->SetPointEXhigh(i,err_qcd);
    out->SetPointEXlow(i, err_qcd);
  }   
  return out;
}

void ElectronPFIso(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_Signal = new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/vallot_TTbarTuneZ2.root");
  TFile * f_QCD =new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0/vallot_Run2012ElEl.root");

  TH2F *h2Signal_pfRelIso03_barrel = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h2_pfRelIso03");
  TH2F *h2Signal_pfRelIso03_endcap = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h2_pfRelIso03");
  TH2F *h2Signal_pfRelIso03db_barrel = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h2_pfRelIso03db");
  TH2F *h2Signal_pfRelIso03db_endcap = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h2_pfRelIso03db");
  TH2F *h2Signal_pfRelIso03rho_barrel = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h2_pfRelIso03rho");
  TH2F *h2Signal_pfRelIso03rho_endcap = (TH2F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h2_pfRelIso03rho");

  TH2F *h2Signal_pfRelIso03 = h2Signal_pfRelIso03_barrel->Clone();
  TH2F *h2Signal_pfRelIso03db = h2Signal_pfRelIso03db_barrel->Clone();
  TH2F *h2Signal_pfRelIso03rho = h2Signal_pfRelIso03rho_barrel->Clone();

  h2Signal_pfRelIso03->Add(h2Signal_pfRelIso03_endcap);
  h2Signal_pfRelIso03db->Add(h2Signal_pfRelIso03db_endcap);
  h2Signal_pfRelIso03rho->Add(h2Signal_pfRelIso03rho_endcap);

  int npu = 15;

  TH1D* hSignal_pfRelIso03_lowPU = h2Signal_pfRelIso03->ProjectionY("hSignal_pfRelIso03_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03db_lowPU = h2Signal_pfRelIso03db->ProjectionY("hSignal_pfRelIso03db_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03rho_lowPU = h2Signal_pfRelIso03rho->ProjectionY("hSignal_pfRelIso03rho_lowPU",1,npu);
  TH1D* hSignal_pfRelIso03_highPU = h2Signal_pfRelIso03->ProjectionY("hSignal_pfRelIso03_highPU",npu,50);
  TH1D* hSignal_pfRelIso03db_highPU = h2Signal_pfRelIso03db->ProjectionY("hSignal_pfRelIso03db_highPU",npu,50);
  TH1D* hSignal_pfRelIso03rho_highPU = h2Signal_pfRelIso03rho->ProjectionY("hSignal_pfRelIso03rho_highPU",npu,50);

  TH2F *h2QCD_pfRelIso03_barrel = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h2_pfRelIso03");
  TH2F *h2QCD_pfRelIso03_endcap = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h2_pfRelIso03");
  TH2F *h2QCD_pfRelIso03db_barrel = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h2_pfRelIso03db");
  TH2F *h2QCD_pfRelIso03db_endcap = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h2_pfRelIso03db");
  TH2F *h2QCD_pfRelIso03rho_barrel = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h2_pfRelIso03rho");
  TH2F *h2QCD_pfRelIso03rho_endcap = (TH2F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h2_pfRelIso03rho");

  TH2F *h2QCD_pfRelIso03 = h2QCD_pfRelIso03_barrel->Clone();
  TH2F *h2QCD_pfRelIso03db = h2QCD_pfRelIso03db_barrel->Clone();
  TH2F *h2QCD_pfRelIso03rho = h2QCD_pfRelIso03rho_barrel->Clone();

  h2QCD_pfRelIso03->Add(h2QCD_pfRelIso03_endcap);
  h2QCD_pfRelIso03db->Add(h2QCD_pfRelIso03db_endcap);
  h2QCD_pfRelIso03rho->Add(h2QCD_pfRelIso03rho_endcap);

  /// 1D plots

  TH1D* hQCD_pfRelIso03_lowPU = h2QCD_pfRelIso03->ProjectionY("hQCD_pfRelIso03_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03db_lowPU = h2QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03rho_lowPU = h2QCD_pfRelIso03rho->ProjectionY("hQCD_pfRelIso03rho_lowPU",1,npu); 
  TH1D* hQCD_pfRelIso03_highPU = h2QCD_pfRelIso03->ProjectionY("hQCD_pfRelIso03_highPU",npu,50);
  TH1D* hQCD_pfRelIso03db_highPU = h2QCD_pfRelIso03db->ProjectionY("hQCD_pfRelIso03db_highPU",npu,50);
  TH1D* hQCD_pfRelIso03rho_highPU = h2QCD_pfRelIso03rho->ProjectionY("hQCD_pfRelIso03rho_highPU",npu,50);

  TH1F *hSignal_pfRelIso02_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso02");
  TH1F *hSignal_pfRelIso02_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso02");
  TH1F *hSignal_pfRelIso02db_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso02db");
  TH1F *hSignal_pfRelIso02db_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso02db");
  
  TH1F *hSignal_pfRelIso02 = hSignal_pfRelIso02_barrel->Clone();
  TH1F *hSignal_pfRelIso02db = hSignal_pfRelIso02db_barrel->Clone();
  
  hSignal_pfRelIso02->Add(hSignal_pfRelIso02_endcap);
  hSignal_pfRelIso02db->Add(hSignal_pfRelIso02db_endcap);

  TH1F *hQCD_pfRelIso02_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso02");
  TH1F *hQCD_pfRelIso02_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso02");
  TH1F *hQCD_pfRelIso02db_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso02db");
  TH1F *hQCD_pfRelIso02db_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso02db");
  
  TH1F *hQCD_pfRelIso02 = hQCD_pfRelIso02_barrel->Clone();
  TH1F *hQCD_pfRelIso02db = hQCD_pfRelIso02db_barrel->Clone();
  
  hQCD_pfRelIso02->Add(hQCD_pfRelIso02_endcap);
  hQCD_pfRelIso02db->Add(hQCD_pfRelIso02db_endcap);

  TH1F *hSignal_pfRelIso04_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04");
  TH1F *hSignal_pfRelIso04_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04");
  TH1F *hSignal_pfRelIso04db_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04db");
  TH1F *hSignal_pfRelIso04db_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04db");
  TH1F *hSignal_pfRelIso04rho_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso04rho");
  TH1F *hSignal_pfRelIso04rho_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso04rho");

  TH1F *hSignal_pfRelIso04 = hSignal_pfRelIso04_barrel->Clone();
  TH1F *hSignal_pfRelIso04db = hSignal_pfRelIso04db_barrel->Clone();
  TH1F *hSignal_pfRelIso04rho = hSignal_pfRelIso04rho_barrel->Clone();

  hSignal_pfRelIso04->Add(hSignal_pfRelIso04_endcap);
  hSignal_pfRelIso04db->Add(hSignal_pfRelIso04db_endcap);
  hSignal_pfRelIso04rho->Add(hSignal_pfRelIso04rho_endcap);

  TH1F *hQCD_pfRelIso04_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04");
  TH1F *hQCD_pfRelIso04_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04");
  TH1F *hQCD_pfRelIso04db_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04db");
  TH1F *hQCD_pfRelIso04db_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04db");
  TH1F *hQCD_pfRelIso04rho_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso04rho");
  TH1F *hQCD_pfRelIso04rho_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso04rho");

  TH1F *hQCD_pfRelIso04 = hQCD_pfRelIso04_barrel->Clone();
  TH1F *hQCD_pfRelIso04db = hQCD_pfRelIso04db_barrel->Clone();
  TH1F *hQCD_pfRelIso04rho = hQCD_pfRelIso04rho_barrel->Clone();

  hQCD_pfRelIso04->Add(hQCD_pfRelIso04_endcap);
  hQCD_pfRelIso04db->Add(hQCD_pfRelIso04db_endcap);
  hQCD_pfRelIso04rho->Add(hQCD_pfRelIso04rho_endcap);

  TH1F *hSignal_pfRelIso03_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03");
  TH1F *hSignal_pfRelIso03_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03");
  TH1F *hSignal_pfRelIso03db_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03db");
  TH1F *hSignal_pfRelIso03db_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03db");
  TH1F *hSignal_pfRelIso03rho_barrel = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Barrel/h_pfRelIso03rho");
  TH1F *hSignal_pfRelIso03rho_endcap = (TH1F *) f_Signal->Get("ElectronAnalysis/Signal/IDPF/Endcap/h_pfRelIso03rho");

  TH1F *hSignal_pfRelIso03 = hSignal_pfRelIso03_barrel->Clone();
  TH1F *hSignal_pfRelIso03db = hSignal_pfRelIso03db_barrel->Clone();
  TH1F *hSignal_pfRelIso03rho = hSignal_pfRelIso03rho_barrel->Clone();

  hSignal_pfRelIso03->Add(hSignal_pfRelIso03_endcap);
  hSignal_pfRelIso03db->Add(hSignal_pfRelIso03db_endcap);
  hSignal_pfRelIso03rho->Add(hSignal_pfRelIso03rho_endcap);

  TH1F *hQCD_pfRelIso03_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03");
  TH1F *hQCD_pfRelIso03_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03");
  TH1F *hQCD_pfRelIso03db_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03db");
  TH1F *hQCD_pfRelIso03db_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03db");
  TH1F *hQCD_pfRelIso03rho_barrel = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Barrel/h_pfRelIso03rho");
  TH1F *hQCD_pfRelIso03rho_endcap = (TH1F *) f_QCD->Get("ElectronAnalysis/QCD/IDPF/Endcap/h_pfRelIso03rho");

  TH1F *hQCD_pfRelIso03 = hQCD_pfRelIso03_barrel->Clone();
  TH1F *hQCD_pfRelIso03db = hQCD_pfRelIso03db_barrel->Clone();
  TH1F *hQCD_pfRelIso03rho = hQCD_pfRelIso03rho_barrel->Clone();

  hQCD_pfRelIso03->Add(hQCD_pfRelIso03_endcap);
  hQCD_pfRelIso03db->Add(hQCD_pfRelIso03db_endcap);
  hQCD_pfRelIso03rho->Add(hQCD_pfRelIso03rho_endcap);

  ROC_pfRelIso02 = ROC( hSignal_pfRelIso02, hQCD_pfRelIso02);
  ROC_pfRelIso02db = ROC( hSignal_pfRelIso02db, hQCD_pfRelIso02db);

  ROC_pfRelIso03 = ROC( hSignal_pfRelIso03, hQCD_pfRelIso03);
  ROC_pfRelIso03db = ROC( hSignal_pfRelIso03db, hQCD_pfRelIso03db);
  ROC_pfRelIso03rho = ROC( hSignal_pfRelIso03rho, hQCD_pfRelIso03rho);

  ROC_pfRelIso04 = ROC( hSignal_pfRelIso04, hQCD_pfRelIso04);
  ROC_pfRelIso04db = ROC( hSignal_pfRelIso04db, hQCD_pfRelIso04db);
  ROC_pfRelIso04rho = ROC( hSignal_pfRelIso04rho, hQCD_pfRelIso04rho);

  ROC_pfRelIso03_lowPU = ROC( hSignal_pfRelIso03_lowPU, hQCD_pfRelIso03_lowPU);
  ROC_pfRelIso03db_lowPU = ROC( hSignal_pfRelIso03db_lowPU, hQCD_pfRelIso03db_lowPU);
  ROC_pfRelIso03rho_lowPU = ROC( hSignal_pfRelIso03rho_lowPU, hQCD_pfRelIso03rho_lowPU);

  ROC_pfRelIso03_highPU = ROC( hSignal_pfRelIso03_highPU, hQCD_pfRelIso03_highPU);
  ROC_pfRelIso03db_highPU = ROC( hSignal_pfRelIso03db_highPU, hQCD_pfRelIso03db_highPU);
  ROC_pfRelIso03rho_highPU = ROC( hSignal_pfRelIso03rho_highPU, hQCD_pfRelIso03rho_highPU);

  TCanvas * c_dR = new TCanvas("c_dR","c_dR",500,500);
  Style( ROC_pfRelIso02db, 1, 1);
  Style( ROC_pfRelIso03db, 2, 1);
  Style( ROC_pfRelIso04db, 4, 1);
  ROC_pfRelIso02db->Draw("ALP");
  ROC_pfRelIso03db->Draw("sameLP");
  ROC_pfRelIso04db->Draw("sameLP");
  SetLabel("");

  TLegend *l= new TLegend(0.6,0.3,0.9,0.5);
  l->AddEntry(ROC_pfRelIso02db,"dR = 0.2","LP");
  l->AddEntry(ROC_pfRelIso03db,"dR = 0.3","LP");
  l->AddEntry(ROC_pfRelIso04db,"dR = 0.4","LP");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c_dR->Print("c_iso_dR.eps");

  TCanvas * c = new TCanvas("c","c",500,500);
  Style( ROC_pfRelIso03, 1, 1);
  Style( ROC_pfRelIso03db, 2, 1);
  Style( ROC_pfRelIso03rho, 4, 1);
  ROC_pfRelIso03->Draw("ALP");
  ROC_pfRelIso03db->Draw("sameLP");
  ROC_pfRelIso03rho->Draw("sameLP");

  TLegend *l= new TLegend(0.6,0.3,0.9,0.5);
  l->AddEntry(ROC_pfRelIso03,"CHS only","LP");
  l->AddEntry(ROC_pfRelIso03db,"+dbeta","LP");
  l->AddEntry(ROC_pfRelIso03rho,"+rho","LP");
  SetLabel("");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print("c_iso_corrtype.eps");

  TCanvas * c_lowPU = new TCanvas("c_lowPU","c_lowPU",500,500);
  Style( ROC_pfRelIso03_lowPU, 1, 1);
  Style( ROC_pfRelIso03db_lowPU, 2, 1);
  Style( ROC_pfRelIso03rho_lowPU, 4, 1);
  ROC_pfRelIso03_lowPU->Draw("ALP");
  ROC_pfRelIso03db_lowPU->Draw("sameLP");
  ROC_pfRelIso03rho_lowPU->Draw("sameLP");
  SetLabel("PU < 15");
  l->Draw();

  TCanvas * c_highPU = new TCanvas("c_highPU","c_highPU",500,500);
  Style( ROC_pfRelIso03_highPU, 1, 1);
  Style( ROC_pfRelIso03db_highPU, 2, 1);
  Style( ROC_pfRelIso03rho_highPU, 4, 1);
  ROC_pfRelIso03_highPU->Draw("ALP");
  ROC_pfRelIso03db_highPU->Draw("sameLP");
  ROC_pfRelIso03rho_highPU->Draw("sameLP");
  SetLabel("PU #geq 15");
  l->Draw();

}
