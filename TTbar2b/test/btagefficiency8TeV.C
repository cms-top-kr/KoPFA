#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
//using namespace std;
void btagefficiency8TeV(int ii)
{
    gROOT->ProcessLine(".L tdrstyle.C");
    defaultStyle();
    TFile* f1 = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130205_S4/vallot_TTbarFullLepMGDecays.root");
	
    TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
    TTree* treeElEl = (TTree*)f1->Get("ElEl/tree");
    TTree* treeMuEl = (TTree*)f1->Get("MuEl/tree");
	
    float binspt[] = {20,30,40,50,60,70,80,100,120,160,210,260,320,400,450};
    int nBinpt = sizeof(binspt)/sizeof(float) - 1;
    float binseta[] = {0.,0.4,0.8,1.2,1.6,2.0,2.4};
    int nBineta = sizeof(binseta)/sizeof(float) - 1;

    TCut precut_em = "ZMass > 12 && lep1.relIso03() < 0.15 && lep2.relIso03() < 0.15 && PairSign < 0 && nJet30 >= 4";
    TCut precut = precut_em + "abs(ZMass - 91.2) > 15 && MET > 30"; 
    TCut bcut =  "abs(jets.flavor()) == 5";
    TCut ccut =  "abs(jets.flavor()) == 4";
    TCut lcut =  "abs(jets.flavor()) < 4";

    TCut csvm =  "jets.bDiscriminator() > 0.679";
    TCut csvt =  "jets.bDiscriminator() > 0.898";
   
 if(ii ==0)
 {
    TH1F* eff_b_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, "b_pt_CSVM","CSVM",2,"p_{T}(GeV/c)"); 
    TH1F* eff_b_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, "b_pt_CSVT","CSVT",2,"p_{T}(GeV/c)"); 

    TH1F* eff_c_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, "c_pt_CSVM","CSVM",4,"p_{T}(GeV/c)");
    TH1F* eff_c_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, "c_pt_CSVT","CSVT",4,"p_{T}(GeV/c)");

    TH1F* eff_l_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, lcut, csvm, "l_pt_CSVM","CSVM",5,"p_{T}(GeV/c)");
    TH1F* eff_l_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.pt()", nBinpt, binspt, precut, precut_em, lcut, csvt, "l_pt_CSVT","CSVT",5,"p_{T}(GeV/c)");


    TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
    eff_b_pt_CSVM->Draw("e3");
    eff_c_pt_CSVM->Draw("e3 same");
    eff_l_pt_CSVM->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVM,"b-flavor","F");
    l->AddEntry(eff_c_pt_CSVM,"c-flavor","F");
    l->AddEntry(eff_l_pt_CSVM,"LF-flavor","F");
    SetLegend(l);
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.png");
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.eps");

    TCanvas * c_b_pt_CSVT = new TCanvas("c_b_pt_CSVT","c_b_pt_CSVT",500,500);
    eff_b_pt_CSVT->Draw("e3");
    eff_c_pt_CSVT->Draw("e3 same");
    eff_l_pt_CSVT->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVT,"b-flavor","F");
    l->AddEntry(eff_c_pt_CSVT,"c-flavor","F");
    l->AddEntry(eff_l_pt_CSVT,"LF-flavor","F");
    SetLegend(l);
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.png");
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.eps");
 }
 else if(ii==1)
 {

    TH1F* eff_b_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, bcut, csvm, "b_eta_CSVM","CSVM",2, "#eta"); 
    TH1F* eff_b_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, bcut, csvt, "b_eta_CSVT","CSVT",2, "#eta"); 

    TH1F* eff_c_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, ccut, csvm, "c_eta_CSVM","CSVM",4, "#eta");
    TH1F* eff_c_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, ccut, csvt, "c_eta_CSVT","CSVT",4, "#eta");

    TH1F* eff_l_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, lcut, csvm, "l_eta_CSVM","CSVM",5, "#eta");
    TH1F* eff_l_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets.eta()", nBineta, binseta, precut, precut_em, lcut, csvt, "l_eta_CSVT","CSVT",5, "#eta");


    TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
    eff_b_eta_CSVM->Draw("e3");
    eff_c_eta_CSVM->Draw("e3 same");
    eff_l_eta_CSVM->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVM,"b-flavor","F");
    l->AddEntry(eff_c_eta_CSVM,"c-flavor","F");
    l->AddEntry(eff_l_eta_CSVM,"LF-flavor","F");
    SetLegend(l);
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.png");
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.eps");

    TCanvas * c_b_eta_CSVT = new TCanvas("c_b_eta_CSVT","c_b_eta_CSVT",500,500);
    eff_b_eta_CSVT->Draw("e3");
    eff_c_eta_CSVT->Draw("e3 same");
    eff_l_eta_CSVT->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVT,"b-flavor","F");
    l->AddEntry(eff_c_eta_CSVT,"c-flavor","F");
    l->AddEntry(eff_l_eta_CSVT,"LF-flavor","F");
    SetLegend(l);
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.png");
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.eps");
  }

}

TH1F* eff(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int nBin, float * bins, TCut precut, TCut precut_em, TCut fcut, TCut wcut, const TString & name, const TString & tagName, int color, const TString & xtitle){

  TCut dencut_em =  precut_em + fcut;
  TCut dencut    =  precut    + fcut;
  TCut numcut_em =  dencut_em + wcut;
  TCut numcut    =  dencut    + wcut;

  TH1F* h_eff = new TH1F(Form("h_eff_%s",name.Data()),"h_eff",nBin,bins);

  TH1F* hden = new TH1F(Form("hden_%s",name.Data()),"hden",nBin,bins);
  TH1F* hnum = new TH1F(Form("hnum_%s",name.Data()),"hnum",nBin,bins);

  TH1F* hden_ee = new TH1F(Form("hden_%s_ee",name.Data()),"hden_ee",nBin,bins);
  TH1F* hnum_ee = new TH1F(Form("hnum_%s_ee",name.Data()),"hnum_ee",nBin,bins);

  TH1F* hden_mm = new TH1F(Form("hden_%s_mm",name.Data()),"hden_mm",nBin,bins);
  TH1F* hnum_mm = new TH1F(Form("hnum_%s_mm",name.Data()),"hnum_mm",nBin,bins);

  TH1F* hden_em = new TH1F(Form("hden_%s_em",name.Data()),"hden_em",nBin,bins);
  TH1F* hnum_em = new TH1F(Form("hnum_%s_em",name.Data()),"hnum_em",nBin,bins);

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeElEl->Project(Form("hnum_%s_ee",name.Data()),Form("%s",variable.Data()),numcut,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeMuMu->Project(Form("hnum_%s_mm",name.Data()),Form("%s",variable.Data()),numcut,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em,"");
  treeMuEl->Project(Form("hnum_%s_em",name.Data()),Form("%s",variable.Data()),numcut_em,"");

  hnum->Add(hnum_ee,1);
  hnum->Add(hnum_mm,1);
  hnum->Add(hnum_em,1);
  hden->Add(hden_ee,1);
  hden->Add(hden_mm,1);
  hden->Add(hden_em,1);

  TCanvas*  tag_eff = new TCanvas(Form("eff_%s",name.Data()),Form("eff_%s",name.Data()),500,500);
  h_eff->Sumw2();
  h_eff->SetStats(0);
  h_eff->SetTitle(Form("b-tagging efficiency (%s)",tagName.Data()));
  h_eff->Divide(hnum,hden,1,1,"B");
  TF1* function = new TF1("function","pol4");
  function->SetLineColor(color);
  h_eff->Fit(function);
  h_eff->SetMinimum(0.0);
  h_eff->SetMaximum(1.0);
  h_eff->GetXaxis()->SetTitle(xtitle);
  h_eff->GetYaxis()->SetTitle("Efficiency");
  h_eff->SetStats(0);
  //h_eff->Draw("AXIS");
  TH1F* h_effint = h_eff->Clone(); 
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_effint,0.68);
  h_effint->SetFillColor(color);
  h_effint->SetFillStyle(3005);
  h_effint->SetStats(0);
  h_effint->Draw("e3 same");

  tag_eff->Print(Form("eff_%s.png",name.Data()));
  return h_effint;

}

void SetLegend(TLegend* l){
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}
