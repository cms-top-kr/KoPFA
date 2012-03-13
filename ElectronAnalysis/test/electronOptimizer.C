#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "TTree.h"
#include "TCut.h"

void cicHisto(TTree* t, TH1* h, TString electron, TCut cut){

  double n_eidVeryLooseMC = t->GetEntries(Form("%s_eidVeryLooseMC == 1",electron.Data()) + cut);
  double n_eidLooseMC = t->GetEntries(Form("%s_eidLooseMC == 1",electron.Data()) + cut);
  double n_eidMediumMC = t->GetEntries(Form("%s_eidMediumMC == 1",electron.Data()) + cut);
  double n_eidTightMC = t->GetEntries(Form("%s_eidTightMC == 1",electron.Data()) + cut);
  double n_eidSuperTightMC = t->GetEntries(Form("%s_eidSuperTightMC == 1",electron.Data()) + cut);
  double n_eidHyperTight1MC = t->GetEntries(Form("%s_eidHyperTight1MC == 1",electron.Data()) + cut);

  h->SetBinContent(1, n_eidVeryLooseMC);
  h->SetBinContent(2, n_eidLooseMC);
  h->SetBinContent(3, n_eidMediumMC);
  h->SetBinContent(4, n_eidTightMC);
  h->SetBinContent(5, n_eidSuperTightMC);
  h->SetBinContent(6, n_eidHyperTight1MC);

}

void simHisto(TTree* t, TH1* h, TString electron, TCut cut){

  double n_simpleEleId95relIso = t->GetEntries(Form("%s_simpleEleId95relIso == 1",electron.Data()) + cut);
  double n_simpleEleId90relIso = t->GetEntries(Form("%s_simpleEleId90relIso == 1",electron.Data()) + cut);
  double n_simpleEleId85relIso = t->GetEntries(Form("%s_simpleEleId85relIso == 1",electron.Data()) + cut);
  double n_simpleEleId80relIso = t->GetEntries(Form("%s_simpleEleId80relIso == 1",electron.Data()) + cut);
  double n_simpleEleId70relIso = t->GetEntries(Form("%s_simpleEleId70relIso == 1",electron.Data()) + cut);
  double n_simpleEleId60relIso = t->GetEntries(Form("%s_simpleEleId60relIso == 1",electron.Data()) + cut);

  h->SetBinContent(1, n_simpleEleId95relIso);
  h->SetBinContent(2, n_simpleEleId90relIso);
  h->SetBinContent(3, n_simpleEleId85relIso);
  h->SetBinContent(4, n_simpleEleId80relIso);
  h->SetBinContent(5, n_simpleEleId70relIso);
  h->SetBinContent(6, n_simpleEleId60relIso);

}

void Draw(TH1* h1, TH1* h2, TString leg1, TString leg2, TString ytitle, TString xtitle, TString name, bool setrange = false, double min = 0, double max = 1){

  TCanvas *c = new TCanvas(Form("c_%s",name.Data()), Form("c_%s",name.Data()) , 1);
  h1->SetLineColor(2);
  h1->SetStats(0);
  h1->SetTitle(0);
  h1->GetYaxis()->SetTitle(ytitle.Data());
  h1->GetXaxis()->SetTitle(xtitle.Data());
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

void electronOptimizer(){
  TFile* f_data = new TFile("batch/Out/ElEl/Res/vallot.root");
  TFile* f_ttbar = new TFile("batch/Out/ElEl/Res/vallot_TTbarTuneZ2.root");

  TString signalName = "ttbar";
  TString electronType = "PF";

  TTree* t_data = (TTree*)f_data->Get("eleOpt/tree");
  TTree* t_ttbar = (TTree*)f_ttbar->Get("eleOpt/tree");

  TH1 * h_mva_qcd = new TH1F("h_mva_qcd","h_mva_qcd",200, -1,1) ;
  TH1 * h_mva_qcd1 = (TH1F*) h_mva_qcd->Clone("h_mva_qcd1");
  TH1 * h_mva_qcd2 = (TH1F*) h_mva_qcd->Clone("h_mva_qcd2");
  TH1 * h_cic_qcd = new TH1F("h_cic_qcd","h_cic_qcd",6,-0.5,5.5);
  TH1 * h_cic_qcd1 = (TH1F*) h_cic_qcd->Clone("h_cic_qcd1");
  TH1 * h_cic_qcd2 = (TH1F*) h_cic_qcd->Clone("h_cic_qcd2");
  TH1 * h_sim_qcd = new TH1F("h_sim_qcd","h_sim_qcd",6,-0.5,5.5);
  TH1 * h_sim_qcd1 = (TH1F*) h_sim_qcd->Clone("h_sim_qcd1");
  TH1 * h_sim_qcd2 = (TH1F*) h_sim_qcd->Clone("h_sim_qcd2");

  TH1 * h_mva_ttbar = new TH1F("h_mva_ttbar","h_mva_ttbar",200, -1,1) ;
  TH1 * h_mva_ttbar1 = (TH1F*) h_mva_ttbar->Clone("h_mva_ttbar1");
  TH1 * h_mva_ttbar2 = (TH1F*) h_mva_ttbar->Clone("h_mva_ttbar2");
  TH1 * h_cic_ttbar = new TH1F("h_cic_ttbar","h_cic_ttbar",6,-0.5,5.5);
  TH1 * h_cic_ttbar1 = (TH1F*) h_cic_ttbar->Clone("h_cic_ttbar1");
  TH1 * h_cic_ttbar2 = (TH1F*) h_cic_ttbar->Clone("h_cic_ttbar2");
  TH1 * h_sim_ttbar = new TH1F("h_sim_ttbar","h_sim_ttbar",6,-0.5,5.5);
  TH1 * h_sim_ttbar1 = (TH1F*) h_sim_ttbar->Clone("h_sim_ttbar1");
  TH1 * h_sim_ttbar2 = (TH1F*) h_sim_ttbar->Clone("h_sim_ttbar2");

  //TCut acceptance = "abs(ele1_eta) < 1.49 && abs(ele2_eta) < 1.49";
  TCut acceptance;
  TCut qcd1;
  TCut qcd2;

  if( electronType == "PF" ){
    qcd1 = "ele2_relIso > 1 && abs(dimass - 91.2) > 30 && mt < 20 && dphi < 1.0 ";
    qcd2 = "ele1_relIso > 1 && abs(dimass - 91.2) > 30 && mt < 20 && dphi < 1.0 ";
  }else if ( electronType == "Gsf" ){
    qcd1 = "ele2_reco_relIso > 0.5 && abs(dimass - 91.2) > 30";
    qcd2 = "ele1_reco_relIso > 0.5 && abs(dimass - 91.2) > 30";
  }

  //for single electron skim
  //qcd1 = "multiplicity == 1 && njets >=1 && mt < 20 && dphi < 1.5";
  //qcd2 = "multiplicity == 1 && njets >=1 && mt < 20 && dphi < 1.5";

  TCut signal = "ele1_relIso < 0.2 && ele2_relIso < 0.2";

  t_data->Project("h_mva_qcd1","ele1_mva",qcd1 + acceptance);  
  t_data->Project("h_mva_qcd2","ele2_mva",qcd2 + acceptance);  
  t_ttbar->Project("h_mva_ttbar1","ele1_mva", signal + acceptance);  
  t_ttbar->Project("h_mva_ttbar2","ele2_mva", signal + acceptance);  

  cicHisto(t_data, h_cic_qcd1, "ele1", qcd1 + acceptance);
  cicHisto(t_data, h_cic_qcd2, "ele2", qcd2 + acceptance);

  simHisto(t_data, h_sim_qcd1, "ele1", qcd1 + acceptance);
  simHisto(t_data, h_sim_qcd2, "ele2", qcd2 + acceptance);

  h_mva_qcd = h_mva_qcd1;
  h_mva_qcd->Add(h_mva_qcd2);

  h_cic_qcd = h_cic_qcd1;
  h_cic_qcd->Add(h_cic_qcd2);
 
  h_sim_qcd = h_sim_qcd1;
  h_sim_qcd->Add(h_sim_qcd2); 

  cicHisto(t_ttbar, h_cic_ttbar1, "ele1", signal + acceptance);
  cicHisto(t_ttbar, h_cic_ttbar2, "ele2", signal + acceptance);

  simHisto(t_ttbar, h_sim_ttbar1, "ele1", signal + acceptance);
  simHisto(t_ttbar, h_sim_ttbar2, "ele2", signal + acceptance);

  h_mva_ttbar = h_mva_ttbar1; 
  h_mva_ttbar->Add(h_mva_ttbar2); 

  h_cic_ttbar = h_cic_ttbar1;
  h_cic_ttbar->Add(h_cic_ttbar2);

  h_sim_ttbar = h_sim_ttbar1;
  h_sim_ttbar->Add(h_sim_ttbar2);

  TH1 *h_mva_qcd_eff = (TH1F*) h_mva_qcd->Clone("h_mva_qcd_eff");  
  TH1 *h_mva_ttbar_eff = (TH1F*) h_mva_ttbar->Clone("h_mva_qcd_eff");  
  h_mva_qcd_eff->Reset();
  h_mva_ttbar_eff->Reset();

  TH1 *h_cic_qcd_eff = (TH1F*) h_cic_qcd->Clone("h_cic_qcd_eff");
  TH1 *h_cic_ttbar_eff = (TH1F*) h_cic_ttbar->Clone("h_cic_qcd_eff");
  h_cic_qcd_eff->Reset();
  h_cic_ttbar_eff->Reset();

  TH1 *h_sim_qcd_eff = (TH1F*) h_sim_qcd->Clone("h_sim_qcd_eff");
  TH1 *h_sim_ttbar_eff = (TH1F*) h_sim_ttbar->Clone("h_sim_qcd_eff");
  h_sim_qcd_eff->Reset();
  h_sim_ttbar_eff->Reset();

  double nDen_ttbar = h_mva_ttbar->Integral();
  double nDen_qcd = h_mva_qcd->Integral();

  cout << "Number of ttbar electrons = " << nDen_ttbar << " : Number of QCD electrosn = " << nDen_qcd << endl;

  TGraphAsymmErrors* roc_mva = new TGraphAsymmErrors; 

  int nbins =  h_mva_ttbar->GetNbinsX();
  for(int i=0 ; i < nbins ; i++){
    double num_ttbar = h_mva_ttbar->Integral(i+1,nbins);
    double eff_ttbar = num_ttbar/nDen_ttbar;
    double num_qcd = h_mva_qcd->Integral(i+1,nbins);
    double eff_qcd = num_qcd/nDen_qcd;
    h_mva_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_mva_qcd_eff->SetBinContent(i+1,eff_qcd);
    roc_mva->SetPoint(nbins-i-1, eff_qcd, eff_ttbar);
  }

  h_mva_ttbar->Scale(1.0/nDen_ttbar);
  h_mva_qcd->Scale(1.0/nDen_qcd);

  Draw(h_mva_ttbar, h_mva_qcd, signalName, "QCD", "Entries", "MVA", "mva");
  Draw(h_mva_ttbar_eff, h_mva_qcd_eff, signalName, "QCD", "Efficiency", "MVA Id", "mva_eff", true, 0, 1.2);

  TGraphAsymmErrors* roc_cic = new TGraphAsymmErrors;
  int cicnbins = h_cic_ttbar->GetNbinsX();

  for(int i=0 ; i < cicnbins ; i++){
    double num_ttbar = h_cic_ttbar->Integral(i+1,i+1);
    double eff_ttbar = num_ttbar/nDen_ttbar;
    double num_qcd = h_cic_qcd->Integral(i+1,i+1);
    double eff_qcd = num_qcd/nDen_qcd;
    h_cic_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_cic_qcd_eff->SetBinContent(i+1,eff_qcd);
    std::cout << "CiC : " << " ( " << cicnbins-i << " ) " << " QCD = ( " << num_qcd << " ) " << eff_qcd << " Signal= ( " << num_ttbar << " ) " << eff_ttbar << endl;
    roc_cic->SetPoint(cicnbins-i-1, eff_qcd, eff_ttbar);
  }

  Draw(h_cic_ttbar_eff, h_cic_qcd_eff, signalName, "QCD", "Efficiency", "CiC Id", "cic_eff", true, 0, 1.2);

  TGraphAsymmErrors* roc_sim = new TGraphAsymmErrors;
  int simnbins = h_sim_ttbar->GetNbinsX();

  for(int i=0 ; i < simnbins ; i++){
    double num_ttbar = h_sim_ttbar->Integral(i+1,i+1);
    double eff_ttbar = num_ttbar/nDen_ttbar;
    double num_qcd = h_sim_qcd->Integral(i+1,i+1);
    double eff_qcd = num_qcd/nDen_qcd; 
    h_sim_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_sim_qcd_eff->SetBinContent(i+1,eff_qcd);
    std::cout << "Sim : " << " ( " << simnbins-i << " ) " << " QCD = ( " << num_qcd << " ) " << eff_qcd << " Signal= ( " << num_ttbar << " ) " << eff_ttbar << endl;
    roc_sim->SetPoint(simnbins-i-1, eff_qcd, eff_ttbar);
  } 

  //Draw ROC canvas
  TCanvas *c_roc = new TCanvas("c_roc","c_roc",1);
  roc_mva->Draw("ALP");
  roc_mva->SetMarkerSize(0.8);
  roc_mva->SetMarkerStyle(20);
  roc_mva->SetMarkerColor(2);
  roc_mva->SetLineWidth(2);
  roc_mva->SetLineColor(2);
  roc_mva->GetYaxis()->SetTitle("Signal Efficiency");
  roc_mva->GetXaxis()->SetTitle("Background Efficiency");
  roc_cic->SetLineWidth(2);
  roc_cic->SetMarkerSize(0.8);
  roc_cic->SetMarkerStyle(20);
  roc_cic->Draw("SameLP");
  roc_sim->SetLineColor(4);
  roc_sim->SetLineWidth(2);
  roc_sim->SetMarkerSize(0.8);
  roc_sim->SetMarkerStyle(20);
  roc_sim->Draw("SameLP");

  TLegend *l_roc= new TLegend(0.7,0.4,0.9,0.6);
  l_roc->AddEntry(roc_mva,"Mva","L");
  l_roc->AddEntry(roc_cic,"CiC","L");
  l_roc->AddEntry(roc_sim,"Sim","L");
  l_roc->SetTextSize(0.04);
  l_roc->SetFillColor(0);
  l_roc->SetLineColor(0);
  l_roc->Draw();

  c_roc->Print("c_roc.eps");

}
