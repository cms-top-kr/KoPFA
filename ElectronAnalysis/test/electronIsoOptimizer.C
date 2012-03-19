#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "TTree.h"
#include "TCut.h"

void GetROC(TGraphAsymmErrors* roc_relIso, TH1* h_relIso_ttbar, TH1* h_relIso_qcd, TH1* h_relIso_ttbar_eff, TH1* h_relIso_qcd_eff, TString name){

  cout << "Get ROC for " << name.Data() << endl;

  int relIsonbins = h_relIso_ttbar->GetNbinsX();
  double nDen_relIso_ttbar = h_relIso_ttbar->Integral();
  double nDen_relIso_qcd = h_relIso_qcd->Integral();
  cout << "signal total = " << nDen_relIso_ttbar << " background total = " << nDen_relIso_qcd << endl; 
  for(int i=0 ; i < relIsonbins ; i++){
    double num_ttbar = h_relIso_ttbar->Integral(1,i+1);
    double eff_ttbar = num_ttbar/nDen_relIso_ttbar;
    double num_qcd = h_relIso_qcd->Integral(1,i+1);
    double eff_qcd = num_qcd/nDen_relIso_qcd;
    double purity = 0.9;
    double real_eff_qcd = ( eff_qcd - eff_ttbar*(1-purity) ) / purity;
    h_relIso_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_relIso_qcd_eff->SetBinContent(i+1,real_eff_qcd);
    //std::cout << "RelIso : " << " ( " << relIsonbins-i << " ) " << " QCD = ( " << num_qcd << " ) " << eff_qcd << " corr: " << real_eff_qcd << " Signal= ( " << num_ttbar << " ) " << eff_ttbar << endl;
    roc_relIso->SetPoint(relIsonbins-i-1, real_eff_qcd, eff_ttbar);
  }

}

void Draw(TH1* h1, TH1* h2, TString leg1, TString leg2, TString ytitle, TString xtitle, TString name, bool setrange = false, double min = 0, double max = 1, bool log = true){

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()), Form("c_%s",name.Data()) , 1);
  if(log) c->SetLogy();

  h1->SetLineColor(2);
  h1->SetStats(0);
  h1->SetTitle(0);
  h1->GetYaxis()->SetTitle(ytitle.Data());
  h1->GetXaxis()->SetTitle(xtitle.Data());
  h1->GetXaxis()->SetLimits(0,2);
  if(setrange){
    h1->SetMaximum(max);
    h1->SetMinimum(min);
  }
  h1->Draw();
  h2->Draw("same");

  TLegend *l = new TLegend(0.7,0.65,0.9,0.85);
  l->AddEntry(h1,leg1.Data(),"L");
  l->AddEntry(h2,leg2.Data(),"L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print(Form("c_%s.eps",name.Data()));
}

void electronIsoOptimizer(){
  TFile* f_data = new TFile("batch/Out/ElEl/Res/vallot_newIso.root");
  TFile* f_ttbar = new TFile("batch/Out/ElEl/Res/vallot_TTbarTuneZ2_newIso_filter.root");

  TString signalName = "ttbar";
  TString electronType = "PF";

  TTree* t_data = (TTree*)f_data->Get("eleOpt/tree");
  TTree* t_ttbar = (TTree*)f_ttbar->Get("eleOpt/tree");

  TH1 * h_relIso_qcd = new TH1F("h_relIso_qcd","h_relIso_qcd",2000,0.0,20.0);
  TH1 * h_relIso_qcd1 = (TH1F*) h_relIso_qcd->Clone("h_relIso_qcd1");
  TH1 * h_relIso_qcd2 = (TH1F*) h_relIso_qcd->Clone("h_relIso_qcd2");
  TH1 * h_relIso_qcd_eff = (TH1F*) h_relIso_qcd->Clone("h_relIso_qcd_eff");
  TH1 * h_relIsoDbeta_qcd = new TH1F("h_relIsoDbeta_qcd","h_relIsoDbeta_qcd",2000,0.0,20.0);
  TH1 * h_relIsoDbeta_qcd1 = (TH1F*) h_relIsoDbeta_qcd->Clone("h_relIsoDbeta_qcd1");
  TH1 * h_relIsoDbeta_qcd2 = (TH1F*) h_relIsoDbeta_qcd->Clone("h_relIsoDbeta_qcd2");
  TH1 * h_relIsoDbeta_qcd_eff = (TH1F*) h_relIsoDbeta_qcd->Clone("h_relIsoDbeta_qcd_eff");
  TH1 * h_relIsoNoVetoDbeta_qcd = new TH1F("h_relIsoNoVetoDbeta_qcd","h_relIsoNoVetoDbeta_qcd",2000,0.0,20.0);
  TH1 * h_relIsoNoVetoDbeta_qcd1 = (TH1F*) h_relIsoNoVetoDbeta_qcd->Clone("h_relIsoNoVetoDbeta_qcd1");
  TH1 * h_relIsoNoVetoDbeta_qcd2 = (TH1F*) h_relIsoNoVetoDbeta_qcd->Clone("h_relIsoNoVetoDbeta_qcd2");
  TH1 * h_relIsoNoVetoDbeta_qcd_eff = (TH1F*) h_relIsoNoVetoDbeta_qcd->Clone("h_relIsoNoVetoDbeta_qcd_eff");

  TH1 * h_relIso_ttbar = new TH1F("h_relIso_ttbar","h_relIso_ttbar",2000,0.0,20.0);
  TH1 * h_relIso_ttbar1 = (TH1F*) h_relIso_ttbar->Clone("h_relIso_ttbar1");
  TH1 * h_relIso_ttbar2 = (TH1F*) h_relIso_ttbar->Clone("h_relIso_ttbar2");
  TH1 * h_relIso_ttbar_eff = (TH1F*) h_relIso_ttbar->Clone("h_relIso_ttbar_eff");
  TH1 * h_relIsoDbeta_ttbar = new TH1F("h_relIsoDbeta_ttbar","h_relIsoDbeta_ttbar",2000,0.0,20.0);
  TH1 * h_relIsoDbeta_ttbar1 = (TH1F*) h_relIsoDbeta_ttbar->Clone("h_relIsoDbeta_ttbar1");
  TH1 * h_relIsoDbeta_ttbar2 = (TH1F*) h_relIsoDbeta_ttbar->Clone("h_relIsoDbeta_ttbar2");
  TH1 * h_relIsoDbeta_ttbar_eff = (TH1F*) h_relIsoDbeta_ttbar->Clone("h_relIsoDbeta_ttbar_eff");
  TH1 * h_relIsoNoVetoDbeta_ttbar = new TH1F("h_relIsoNoVetoDbeta_ttbar","h_relIsoNoVetoDbeta_ttbar",2000,0.0,20.0);
  TH1 * h_relIsoNoVetoDbeta_ttbar1 = (TH1F*) h_relIsoNoVetoDbeta_ttbar->Clone("h_relIsoNoVetoDbeta_ttbar1");
  TH1 * h_relIsoNoVetoDbeta_ttbar2 = (TH1F*) h_relIsoNoVetoDbeta_ttbar->Clone("h_relIsoNoVetoDbeta_ttbar2");
  TH1 * h_relIsoNoVetoDbeta_ttbar_eff = (TH1F*) h_relIsoNoVetoDbeta_ttbar->Clone("h_relIsoNoVetoDbeta_ttbar_eff");

  TCut geo;// = "abs(ele1_eta) < 1.49 && abs(ele2_eta) < 1.49";
  TCut vertex;// = "nVertex <= 8";
  //TCut vertex;
  TCut acceptance = geo + vertex;
  TCut qcd1;// = acceptance + "ele2_relIso > 0.5 && abs(dimass-91.2) > 30 && ele1_charge*ele2_charge > 0";
  TCut qcd2;// = acceptance + "ele1_relIso > 0.5 && abs(dimass-91.2) > 30 && ele1_charge*ele2_charge > 0";
  qcd1 = acceptance + "ele2_relIso > 0.5 &&  mt < 20 && MET < 50 && ele1_charge*ele1_charge > 0 ";
  qcd2 = acceptance + "ele1_relIso > 0.5 &&  mt < 20 && MET < 50 && ele1_charge*ele2_charge > 0 ";
  //for single electron skim
  //qcd1 = "multiplicity == 1 && njets >=1 && mt < 20 && dphi < 1.0 && MET < 20";
  //qcd2 = "multiplicity == 1 && njets >=1 && mt < 20 && dphi < 1.0 && MET < 20";

  TCut signal1 = acceptance + "ele1_isFromW == 1"; // && ele2_relIso < 0.2";
  TCut signal2 = acceptance + "ele2_isFromW == 1"; // && ele1_relIso < 0.2";

  //default isolation///////////////////////////////////////////////
  t_data->Project("h_relIso_qcd1","ele1_relIso",qcd1);
  t_data->Project("h_relIso_qcd2","ele2_relIso",qcd2);
  t_ttbar->Project("h_relIso_ttbar1","ele1_relIso", signal1);
  t_ttbar->Project("h_relIso_ttbar2","ele2_relIso", signal2);
  h_relIso_qcd = h_relIso_qcd1;
  h_relIso_qcd->Add(h_relIso_qcd2);
  h_relIso_ttbar = h_relIso_ttbar1;
  h_relIso_ttbar->Add(h_relIso_ttbar2);

  //delta beta isolation/////////////////////////////////////////////////
  TString cut_relIso1_dbeta = "(ele1_chIso + max(0.0, ele1_nhIso + ele1_phIso - 0.4*ele1_puChIso) )/ ele1_pt";
  TString cut_relIso2_dbeta = "(ele2_chIso + max(0.0, ele2_nhIso + ele2_phIso - 0.4*ele2_puChIso) )/ ele2_pt";
  t_data->Project("h_relIsoDbeta_qcd1",Form("%s",cut_relIso1_dbeta.Data()),qcd1);
  t_data->Project("h_relIsoDbeta_qcd2",Form("%s",cut_relIso2_dbeta.Data()),qcd2);
  t_ttbar->Project("h_relIsoDbeta_ttbar1",Form("%s",cut_relIso1_dbeta.Data()), signal1);
  t_ttbar->Project("h_relIsoDbeta_ttbar2",Form("%s",cut_relIso2_dbeta.Data()), signal2);
  
  h_relIsoDbeta_qcd = h_relIsoDbeta_qcd1;
  h_relIsoDbeta_qcd->Add(h_relIsoDbeta_qcd2);
  h_relIsoDbeta_ttbar = h_relIsoDbeta_ttbar1;
  h_relIsoDbeta_ttbar->Add(h_relIsoDbeta_ttbar2);

  //delta beta isolation with no veto/////////////////////////////////////////
  TString cut_relIsoNoVeto1_dbeta = "(ele1_chIsoNoVeto + max(0.0, ele1_nhIsoNoVeto + ele1_phIsoNoVeto - 0.5*ele1_puChIsoNoVeto) )/ ele1_pt";
  TString cut_relIsoNoVeto2_dbeta = "(ele2_chIsoNoVeto + max(0.0, ele2_nhIsoNoVeto + ele2_phIsoNoVeto - 0.5*ele2_puChIsoNoVeto) )/ ele2_pt";

  t_data->Project("h_relIsoNoVetoDbeta_qcd1",Form("%s",cut_relIsoNoVeto1_dbeta.Data()),qcd1);
  t_data->Project("h_relIsoNoVetoDbeta_qcd2",Form("%s",cut_relIsoNoVeto2_dbeta.Data()),qcd2);
  t_ttbar->Project("h_relIsoNoVetoDbeta_ttbar1",Form("%s",cut_relIsoNoVeto1_dbeta.Data()), signal1);
  t_ttbar->Project("h_relIsoNoVetoDbeta_ttbar2",Form("%s",cut_relIsoNoVeto2_dbeta.Data()), signal2);
  h_relIsoNoVetoDbeta_qcd = h_relIsoNoVetoDbeta_qcd1;
  h_relIsoNoVetoDbeta_qcd->Add(h_relIsoNoVetoDbeta_qcd2);
  h_relIsoNoVetoDbeta_ttbar = h_relIsoNoVetoDbeta_ttbar1;
  h_relIsoNoVetoDbeta_ttbar->Add(h_relIsoNoVetoDbeta_ttbar2);


  //Draw///////////////////////////////////////////////////
  Draw(h_relIso_ttbar, h_relIso_qcd, signalName, "QCD", "Entries", "relIso", "relIso");
  Draw(h_relIsoDbeta_ttbar, h_relIsoDbeta_qcd, signalName, "QCD", "Entries", "relIso", "relIsoDbeta");
  Draw(h_relIsoNoVetoDbeta_ttbar, h_relIsoNoVetoDbeta_qcd, signalName, "QCD", "Entries", "relIso", "relIsoNoVetoDbeta");
  
  TGraphAsymmErrors* roc_relIso = new TGraphAsymmErrors;
  GetROC(roc_relIso, h_relIso_ttbar, h_relIso_qcd, h_relIso_ttbar_eff, h_relIso_qcd_eff, "PFIso");
  
  TGraphAsymmErrors* roc_relIsoDbeta = new TGraphAsymmErrors;
  GetROC(roc_relIsoDbeta, h_relIsoDbeta_ttbar, h_relIsoDbeta_qcd, h_relIsoDbeta_ttbar_eff, h_relIsoDbeta_qcd_eff, "PFIsoDbeta");

  TGraphAsymmErrors* roc_relIsoNoVetoDbeta = new TGraphAsymmErrors;
  GetROC(roc_relIsoNoVetoDbeta, h_relIsoNoVetoDbeta_ttbar, h_relIsoNoVetoDbeta_qcd, h_relIsoNoVetoDbeta_ttbar_eff, h_relIsoNoVetoDbeta_qcd_eff, "PFIsoNoVetoDbeta");

  //Draw ROC canvas
  TCanvas *c_roc_iso = new TCanvas("c_roc_iso","c_roc_iso",1);
  //c_roc_iso->SetLogx();
  roc_relIso->SetMinimum(0.4);
  roc_relIso->GetXaxis()->SetLimits(0.015,0.5);
  roc_relIso->Draw("ALP");
  roc_relIso->SetMarkerSize(0.8);
  roc_relIso->SetMarkerStyle(20);
  roc_relIso->SetMarkerColor(3);
  roc_relIso->SetLineWidth(2);
  roc_relIso->SetLineColor(3);
  roc_relIso->GetYaxis()->SetTitle("Signal Efficiency");
  roc_relIso->GetXaxis()->SetTitle("Background Efficiency");
  roc_relIsoDbeta->SetLineColor(2);
  roc_relIsoDbeta->SetLineWidth(2);
  roc_relIsoDbeta->SetMarkerColor(2);
  roc_relIsoDbeta->SetMarkerSize(0.8);
  roc_relIsoDbeta->SetMarkerStyle(20);
  roc_relIsoDbeta->Draw("SameLP");
  roc_relIsoNoVetoDbeta->SetLineColor(4);
  roc_relIsoNoVetoDbeta->SetLineWidth(2);
  roc_relIsoNoVetoDbeta->SetMarkerColor(4);
  roc_relIsoNoVetoDbeta->SetMarkerSize(0.8);
  roc_relIsoNoVetoDbeta->SetMarkerStyle(20);
  roc_relIsoNoVetoDbeta->Draw("SameLP");

  TLegend *l_roc_iso= new TLegend(0.5,0.25,0.85,0.45);
  l_roc_iso->AddEntry(roc_relIso,"PFIso","PL");
  l_roc_iso->AddEntry(roc_relIsoDbeta,"PFIso+#Delta#beta","PL");
  l_roc_iso->AddEntry(roc_relIsoNoVetoDbeta,"PFIso+#Delta#beta+no Veto","PL");
  l_roc_iso->SetTextSize(0.04);
  l_roc_iso->SetFillColor(0);
  l_roc_iso->SetLineColor(0);
  l_roc_iso->Draw();

  c_roc_iso->Print("c_roc_iso.eps");
}
