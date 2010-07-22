#include "norm.h"

void anal(){
  TChain * data = new TChain("DiMuonPFlow/tree");
  TChain * Zmumu = new TChain("DiMuonPFlow/tree");
  TChain * Ztautau = new TChain("DiMuonPFlow/tree");
  TChain * Wmunu = new TChain("DiMuonPFlow/tree");
  TChain * QCD = new TChain("DiMuonPFlow/tree");
  TChain * TTbar = new TChain("DiMuonPFlow/tree");

  //data->Add("vallot_RD.root");
  Zmumu->Add("vallot_Zmumu.root");
  Ztautau->Add("vallot_Ztautau.root");
  Wmunu->Add("vallot_Wmunu.root");
  QCD->Add("vallot_QCD.root");
  TTbar->Add("vallot_TTbar2l.root");

 data->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/July11th_v5/Commissioning10-SD_Mu-Jun14thSkim_v1/vallot_*.root");
 data->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/July11th_v5/Run2010A-Jun14thReReco_v1/vallot_*.root");
 data->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/July11th_v5/Run2010A-PromptReco-v4/vallot_*.root");
 //Zmumu->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/MC/Summer10/Zmumu/vallot_*.root");
 //Ztautau->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/MC/Summer10/Ztautau/vallot_*.root");
 //Wmunu->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/MC/Summer10/Wmunu/vallot_*.root");
 //QCD->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/MC/Summer10/InclusiveMu15/vallot_*.root");
  //TTbar->Add("rfio:/castor/cern.ch/user/t/tjkim/SDMUONFILTER/MC/Summer10/TTbar/vallot_*.root");

  TCut cut = "muon1.pt() > 15 && muon2.pt() > 15 && Z.mass() > 20 && Z.sign() < 0";

  int nbin = 40;
  double xlow = 0;
  double xmax = 200;
  TCanvas *c = new TCanvas("c","c",1);
  gPad->SetLogy();

  TH1 *dimuon_data = new TH1F("dimuon_data","dimuon_data",nbin,xlow,xmax); 
  data->Project("dimuon_data","Z.mass()",cut);
  dimuon_data->Sumw2();
  dimuon_data->SetMarkerStyle(20);
  dimuon_data->SetMarkerSize(1);
  dimuon_data->SetTitle(0);
  dimuon_data->SetStats(0);

  dimuon_data->GetXaxis()->SetTitle("Dimuon Mass (GeV/c^{2})");
  dimuon_data->GetYaxis()->SetTitle("Events/5 GeV/c^{2}");

 
  TH1 *dimuon_Zmumu = new TH1F("dimuon_Zmumu","dimuon_Zmumu",nbin,xlow,xmax);
  TH1 *dimuon_Ztautau = new TH1F("dimuon_Ztautau","dimuon_Ztautau",nbin,xlow,xmax);
  TH1 *dimuon_Wmunu = new TH1F("dimuon_Wmunu","dimuon_Wmunu",nbin,xlow,xmax);
  TH1 *dimuon_QCD = new TH1F("dimuon_QCD","dimuon_QCD",nbin,xlow,xmax);
  TH1 *dimuon_TTbar = new TH1F("dimuon_TTbar","dimuon_TTbar",nbin,xlow,xmax);  

  Zmumu->Project("dimuon_Zmumu","Z.mass()",cut);
  Ztautau->Project("dimuon_Ztautau","Z.mass()",cut);
  Wmunu->Project("dimuon_Wmunu","Z.mass()",cut);
  QCD->Project("dimuon_QCD","Z.mass()",cut);
  TTbar->Project("dimuon_TTbar","Z.mass()",cut);

  dimuon_Zmumu->Scale(norm_Zmm);
  dimuon_Ztautau->Scale(norm_Ztautau);
  dimuon_Wmunu->Scale(norm_Wmunu);
  dimuon_QCD->Scale(norm_QCD);
  dimuon_TTbar->Scale(norm_tt2l);

  dimuon_Zmumu->SetFillColor(2);
  dimuon_Ztautau->SetFillColor(5);
  dimuon_Wmunu->SetFillColor(6);
  dimuon_QCD->SetFillColor(3);
  dimuon_TTbar->SetFillColor(4);

  THStack *stack = new THStack("stack","stack");
  
  stack->Add(dimuon_QCD);
  stack->Add(dimuon_TTbar);
  stack->Add(dimuon_Wmunu);
  stack->Add(dimuon_Ztautau);
  stack->Add(dimuon_Zmumu);
  stack->SetTitle(0);
  stack->SetMaximum(1000); 
  stack->SetMinimum(0.001);
  stack->Draw();
  dimuon_data->Draw("same");

  TLegend *l= new TLegend(0.75,0.65,0.90,0.88);
  l->AddEntry(dimuon_data,"Data","p");
  l->AddEntry(dimuon_Zmumu,"Z #rightarrow #mu#mu","f");
  l->AddEntry(dimuon_Ztautau,"Z #rightarrow #tau#tau","f");
  l->AddEntry(dimuon_Wmunu,"W #rightarrow #mu#nu","f");
  l->AddEntry(dimuon_QCD,"QCD","f");
  l->AddEntry(dimuon_TTbar,"t#bar{t}","f");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
 
 
}
