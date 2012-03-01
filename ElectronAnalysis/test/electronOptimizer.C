#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "TTree.h"
#include "TCut.h"

void electronOptimizer(){
  TFile* f_data = new TFile("batch/Out/ElEl/Res/vallot_Run2011B.root");
  TFile* f_ttbar = new TFile("batch/Out/ElEl/Res/vallot_TTbarTuneZ2.root");

  TTree* t_data = (TTree*)f_data->Get("eleOpt/tree");
  TTree* t_ttbar = (TTree*)f_ttbar->Get("eleOpt/tree");

  TH1 * h_mva_qcd = new TH1F("h_mva_qcd","h_mva_qcd",200, -1,1) ;
  TH1 * h_cic_qcd = new TH1F("h_cic_qcd","h_cic_qcd",6,-0.5,5.5);

  TH1 * h_mva_ttbar = new TH1F("h_mva_ttbar","h_mva_ttbar",200, -1,1) ;
  TH1 * h_mva_ttbar1 = new TH1F("h_mva_ttbar1","h_mva_ttbar1",200, -1,1) ;
  TH1 * h_mva_ttbar2 = new TH1F("h_mva_ttbar2","h_mva_ttbar2",200, -1,1) ;
  TH1 * h_cic_ttbar = new TH1F("h_cic_ttbar","h_cic_ttbar",6,-0.5,5.5);
  TH1 * h_cic_ttbar1 = new TH1F("h_cic_ttbar1","h_cic_ttbar1",6,-0.5,5.5);
  TH1 * h_cic_ttbar2 = new TH1F("h_cic_ttbar2","h_cic_ttbar2",6,-0.5,5.5);

  //TCut kinematic = "ele1_pt < 30 && ele2_pt < 30";
  TCut kinematic;
  TCut qcd = "ele2_relIso > 0.5 && abs(dimass - 91.2) > 30";

  t_data->Project("h_mva_qcd","ele1_mva",qcd + kinematic);  
  t_ttbar->Project("h_mva_ttbar1","ele1_mva", kinematic);  
  t_ttbar->Project("h_mva_ttbar2","ele2_mva", kinematic);  

  double n_eidVeryLooseMC_qcd = t_data->GetEntries("ele1_eidVeryLooseMC == 1" + qcd + kinematic);  
  double n_eidLooseMC_qcd = t_data->GetEntries("ele1_eidLooseMC == 1" + qcd + kinematic);  
  double n_eidMediumMC_qcd = t_data->GetEntries("ele1_eidMediumMC == 1" + qcd + kinematic);  
  double n_eidTightMC_qcd = t_data->GetEntries("ele1_eidTightMC == 1" + qcd + kinematic);  
  double n_eidSuperTightMC_qcd = t_data->GetEntries("ele1_eidSuperTightMC == 1" + qcd + kinematic);  
  double n_eidHyperTight1MC_qcd = t_data->GetEntries("ele1_eidHyperTight1MC == 1" + qcd + kinematic);  

  h_cic_qcd->SetBinContent(1, n_eidVeryLooseMC_qcd);
  h_cic_qcd->SetBinContent(2, n_eidLooseMC_qcd);
  h_cic_qcd->SetBinContent(3, n_eidMediumMC_qcd);
  h_cic_qcd->SetBinContent(4, n_eidTightMC_qcd);
  h_cic_qcd->SetBinContent(5, n_eidSuperTightMC_qcd);
  h_cic_qcd->SetBinContent(6, n_eidHyperTight1MC_qcd);
 
  double n_eidVeryLooseMC_ttbar1 = t_ttbar->GetEntries("ele1_eidVeryLooseMC == 1" + kinematic);
  double n_eidLooseMC_ttbar1 = t_ttbar->GetEntries("ele1_eidLooseMC == 1" + kinematic);
  double n_eidMediumMC_ttbar1 = t_ttbar->GetEntries("ele1_eidMediumMC == 1" + kinematic);
  double n_eidTightMC_ttbar1 = t_ttbar->GetEntries("ele1_eidTightMC == 1" + kinematic);
  double n_eidSuperTightMC_ttbar1 = t_ttbar->GetEntries("ele1_eidSuperTightMC == 1" + kinematic);
  double n_eidHyperTight1MC_ttbar1 = t_ttbar->GetEntries("ele1_eidHyperTight1MC == 1" + kinematic);

  h_cic_ttbar1->SetBinContent(1, n_eidVeryLooseMC_ttbar1);
  h_cic_ttbar1->SetBinContent(2, n_eidLooseMC_ttbar1);
  h_cic_ttbar1->SetBinContent(3, n_eidMediumMC_ttbar1);
  h_cic_ttbar1->SetBinContent(4, n_eidTightMC_ttbar1);
  h_cic_ttbar1->SetBinContent(5, n_eidSuperTightMC_ttbar1);
  h_cic_ttbar1->SetBinContent(6, n_eidHyperTight1MC_ttbar1);
 
  double n_eidVeryLooseMC_ttbar2 = t_ttbar->GetEntries("ele1_eidVeryLooseMC == 1" + kinematic);
  double n_eidLooseMC_ttbar2 = t_ttbar->GetEntries("ele1_eidLooseMC == 1" + kinematic);
  double n_eidMediumMC_ttbar2 = t_ttbar->GetEntries("ele1_eidMediumMC == 1" + kinematic);
  double n_eidTightMC_ttbar2 = t_ttbar->GetEntries("ele1_eidTightMC == 1" + kinematic);
  double n_eidSuperTightMC_ttbar2 = t_ttbar->GetEntries("ele1_eidSuperTightMC == 1" + kinematic);
  double n_eidHyperTight1MC_ttbar2 = t_ttbar->GetEntries("ele1_eidHyperTight1MC == 1" + kinematic);

  h_cic_ttbar2->SetBinContent(1, n_eidVeryLooseMC_ttbar2);
  h_cic_ttbar2->SetBinContent(2, n_eidLooseMC_ttbar2);
  h_cic_ttbar2->SetBinContent(3, n_eidMediumMC_ttbar2);
  h_cic_ttbar2->SetBinContent(4, n_eidTightMC_ttbar2);
  h_cic_ttbar2->SetBinContent(5, n_eidSuperTightMC_ttbar2);
  h_cic_ttbar2->SetBinContent(6, n_eidHyperTight1MC_ttbar2);

  h_mva_ttbar = h_mva_ttbar1; 
  h_mva_ttbar->Add(h_mva_ttbar2); 

  h_cic_ttbar = h_cic_ttbar1;
  h_cic_ttbar->Add(h_cic_ttbar2);

  TH1 *h_mva_qcd_eff = (TH1F*) h_mva_qcd->Clone("h_mva_qcd_eff");  
  TH1 *h_mva_ttbar_eff = (TH1F*) h_mva_ttbar->Clone("h_mva_qcd_eff");  
  h_mva_qcd_eff->Reset();
  h_mva_ttbar_eff->Reset();

  TH1 *h_cic_qcd_eff = (TH1F*) h_cic_qcd->Clone("h_cic_qcd_eff");
  TH1 *h_cic_ttbar_eff = (TH1F*) h_cic_ttbar->Clone("h_cic_qcd_eff");
  h_cic_qcd_eff->Reset();
  h_cic_ttbar_eff->Reset();

  double nDen_ttbar = h_mva_ttbar->Integral();
  double nDen_qcd = h_mva_qcd->Integral();

  TGraphAsymmErrors* roc_mva = new TGraphAsymmErrors; 
  int nbins =  h_mva_ttbar->GetNbinsX();
  for(int i=0 ; i < nbins ; i++){
    double nNum_ttbar = h_mva_ttbar->Integral(i+1,nbins);
    double eff_ttbar = nNum_ttbar/nDen_ttbar;
    double nNum_qcd = h_mva_qcd->Integral(i+1,nbins);
    double eff_qcd = nNum_qcd/nDen_qcd;
    h_mva_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_mva_qcd_eff->SetBinContent(i+1,eff_qcd);
    roc_mva->SetPoint(nbins-i-1, eff_qcd, eff_ttbar);
  }

  TCanvas *c_mva = new TCanvas("c_mva","c_mva",1);
  h_mva_ttbar->Scale(1.0/nDen_ttbar);
  h_mva_qcd->Scale(1.0/nDen_qcd);
  h_mva_ttbar->SetLineColor(2);
  h_mva_ttbar->Draw();
  h_mva_qcd->Draw("same");

  TLegend *l_mva= new TLegend(0.7,0.7,0.9,0.9);
  l_mva->AddEntry(h_mva_ttbar,"t#bar{t}","L");
  l_mva->AddEntry(h_mva_qcd,"QCD","L");
  l_mva->SetTextSize(0.04);
  l_mva->SetFillColor(0);
  l_mva->SetLineColor(0);
  l_mva->Draw();

  TCanvas *c_eff = new TCanvas("c_eff","c_eff",1);
  h_mva_ttbar_eff->SetLineColor(2);
  h_mva_ttbar_eff->Draw();
  h_mva_qcd_eff->Draw("same");

  TLegend *l_eff= new TLegend(0.7,0.7,0.9,0.9);
  l_eff->AddEntry(h_mva_ttbar_eff,"t#bar{t}","L");
  l_eff->AddEntry(h_mva_qcd_eff,"QCD","L");
  l_eff->SetTextSize(0.04);
  l_eff->SetFillColor(0);
  l_eff->SetLineColor(0);
  l_eff->Draw();

  TGraphAsymmErrors* roc_cic = new TGraphAsymmErrors;
  int cicnbins = h_cic_ttbar->GetNbinsX();

  for(int i=0 ; i < cicnbins ; i++){
    double nNum_ttbar = h_cic_ttbar->GetBinContent(i+1);
    double eff_ttbar = nNum_ttbar/nDen_ttbar;
    double nNum_qcd = h_cic_qcd->GetBinContent(i+1);
    double eff_qcd = nNum_qcd/nDen_qcd;
    h_cic_ttbar_eff->SetBinContent(i+1,eff_ttbar);
    h_cic_qcd_eff->SetBinContent(i+1,eff_qcd);
    std::cout << "CiC : " << " ( " << cicnbins-i << " ) " << " QCD = " << eff_qcd << " Signal= " << eff_ttbar << endl;
    roc_cic->SetPoint(cicnbins-i-1, eff_qcd, eff_ttbar);
  }

  TCanvas *c_roc = new TCanvas("c_roc","c_roc",1);
  roc_mva->Draw("ALP");
  roc_mva->SetMarkerSize(2);
  roc_mva->SetLineWidth(2);
  roc_mva->SetLineColor(2);
  roc_mva->GetYaxis()->SetTitle("Signal Eff.");
  roc_mva->GetXaxis()->SetTitle("Background Eff.");
  roc_cic->SetLineWidth(2);
  roc_cic->Draw("SameLP");
  roc_cic->SetMarkerSize(2);

  TLegend *l_roc= new TLegend(0.7,0.4,0.9,0.6);
  l_roc->AddEntry(roc_mva,"Mva","L");
  l_roc->AddEntry(roc_cic,"CiC","L");
  l_roc->SetTextSize(0.04);
  l_roc->SetFillColor(0);
  l_roc->SetLineColor(0);
  l_roc->Draw();

}
