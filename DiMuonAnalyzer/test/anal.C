#include <iostream>
#include "norm.h"
#include "THStack.h"
#include "TChain.h"
#include "TH1.h"
#include "TCut.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"


void anal(){
  using namespace std;
  TFile * fdata = new TFile("/home/tjkim/ntuple/data/top/Aug13/vallot.root");
  TFile * fZmumu = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_Zmumu.root");
  TFile * fZtautau = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_Ztautau.root");
  TFile * fWmunu = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_Wmunu.root");
  TFile * fQCD = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_QCD.root");  
  TFile * fTTbar = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_TTbar.root");

  TH1F * evtdata = (TH1F *) fdata->Get("DiMuon/EventSummary");
  TH1F * evtZmumu = (TH1F *) fZmumu->Get("DiMuon/EventSummary");
  TH1F * evtZtautau = (TH1F *) fZtautau->Get("DiMuon/EventSummary");
  TH1F * evtWmunu = (TH1F *) fWmunu->Get("DiMuon/EventSummary");
  TH1F * evtQCD = (TH1F *) fQCD->Get("DiMuon/EventSummary");
  TH1F * evtTTbar = (TH1F *) fTTbar->Get("DiMuon/EventSummary");

  TTree * data = (TTree *) fdata->Get("DiMuon/tree");
  TTree * Zmumu = (TTree *) fZmumu->Get("DiMuon/tree");
  TTree * Ztautau = (TTree *) fZtautau->Get("DiMuon/tree");
  TTree * Wmunu = (TTree *) fWmunu->Get("DiMuon/tree");
  TTree * QCD = (TTree *) fQCD->Get("DiMuon/tree");
  TTree * TTbar = (TTree *) fTTbar->Get("DiMuon/tree");

  int evnZmumu = evtZmumu->GetBinContent(1);
  int evnZtautau = evtZtautau->GetBinContent(1);
  int evnWmunu = evtWmunu->GetBinContent(1);
  int evnQCD = evtQCD->GetBinContent(1);
  int evnTTbar = evtTTbar->GetBinContent(1);

  totalevent( evnZmumu, evnZtautau, evnWmunu, evnQCD, evnTTbar);

  TCut step0;
  TCut step1 = "Z.mass() > 0";
  TCut step2 = "Z.mass() > 0 && Z.sign() < 0";
  TCut step3 = "Z.mass() > 0 && Z.sign() < 0 && !( Z.mass() > 76 && Z.mass() < 106)";
  TCut step4 = "Z.mass() > 0 && Z.sign() < 0 && !( Z.mass() > 76 && Z.mass() < 106) && @jets.size() >= 2";
  TCut step5 = "Z.mass() > 0 && Z.sign() < 0 && !( Z.mass() > 76 && Z.mass() < 106) && @jets.size() >= 2 && MET > 30";

  //numberOfEvents( data,Zmumu,Ztautau,Wmunu,QCD, TTbar, step1,"step0");

  plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step1, "step1"); 
  plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step2, "step2"); 
  plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step3, "step3"); 
  plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step4, "step4"); 
  plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step5, "step5"); 

}

void plotStep(TTree* data, TTree* Zmumu, TTree* Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TCut cut, TString& step){
 
  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_mass","Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40,0, 200, 1000,0.02, "dimuon",Form("mass_h_%s",step.Data()), true);
  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_leadingpt","Leading p_{T} (GeV/c)", "Events/5 GeV/c",20,0, 100, 30, 0, "leading",Form("pt_h_%s",step.Data()), false);

  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.mass()",cut, "Dimuon Mass (GeV/c^{2})", "Events/2 GeV/c^{2}",100, 0, 200, 1000,0.02, "dimuon",Form("mass_%s",step.Data()), true);
  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().pt()",cut, "Leading p_{T} (GeV/c)", "Events/2 GeV/c", 50, 0, 100, 40,0, "leading",Form("pt_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().eta()",cut, "Leading #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("eta_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().phi()",cut, "Leading #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("phi_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().pt()",cut, "Second p_{T} (GeV/c)", "Events/5 GeV/c", 20, 0, 100, 100,0, "second",Form("pt_h_%s",step.Data()), false); 
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().eta()",cut, "Second #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("eta_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().phi()",cut, "Second #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("phi_%s",step.Data()), false);
  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "@jets.size()",cut, "Jet Multiplicity", "Events", 10, 0, 10, 130 , -1, "jet",Form("multiplicity_%s",step.Data()), false);
  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "MET",cut, "Missing E_{T}", "Events", 40, 0, 80, 70 , -1, "met",Form("et_%s",step.Data()), false);

  numberOfEvents( data,Zmumu,Ztautau,Wmunu,QCD, TTbar, cut, step); 
}

void histStack(TFile* fdata, TFile * fZmumu, TFile * fZtautau, TFile* fWmunu, TFile* fQCD, TFile* fTTbar, TString var, TString & xtitle, TString & ytitle, const int& nbin, const double& xlow, const double& xmax, const double& max, const double & min, const TString& hName, const TString& name, bool & log){

  TH1F * h_data = (TH1F *) fdata->Get(Form("DiMuon/%s",var.Data()));
  TH1F * h_Zmumu = (TH1F *) fZmumu->Get(Form("DiMuon/%s",var.Data()));
  TH1F * h_Ztautau = (TH1F *) fZtautau->Get(Form("DiMuon/%s",var.Data()));
  TH1F * h_Wmunu = (TH1F *) fWmunu->Get(Form("DiMuon/%s",var.Data()));
  TH1F * h_QCD = (TH1F *) fQCD->Get(Form("DiMuon/%s",var.Data()));
  TH1F * h_TTbar = (TH1F *) fTTbar->Get(Form("DiMuon/%s",var.Data()));

  plotStackBase(h_data, h_Zmumu, h_Ztautau, h_Wmunu, h_QCD, h_TTbar, xtitle, ytitle, nbin, xlow, xmax, max, min, hName, name, log);

}


void plotStack(TTree* data, TTree * Zmumu, TTree * Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TString var, TCut cut, TString & xtitle, TString & ytitle, const int& nbin, const double& xlow, const double& xmax, const double& max, const double & min, const TString& hName, const TString& name, bool & log){

  TH1 *h_data = new TH1D(Form("h_data_%s_%s",hName.Data(),name.Data()),"h_data",nbin,xlow,xmax);
  TH1 *h_Zmumu = new TH1F(Form("h_Zmumu_%s_%s",hName.Data(),name.Data()),"h_Zmumu",nbin,xlow,xmax);
  TH1 *h_Ztautau = new TH1F(Form("h_Ztautau_%s_%s",hName.Data(),name.Data()),"h_Ztautau",nbin,xlow,xmax);
  TH1 *h_Wmunu = new TH1F(Form("h_Wmunu_%s_%s",hName.Data(),name.Data()),"h_Wmunu",nbin,xlow,xmax);
  TH1 *h_QCD = new TH1F(Form("h_QCD_%s_%s",hName.Data(),name.Data()),"h_QCD",nbin,xlow,xmax);
  TH1 *h_TTbar = new TH1F(Form("h_TTbar_%s_%s",hName.Data(),name.Data()),"h_TTbar",nbin,xlow,xmax);

  data->Project(Form("h_data_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut); 
  Zmumu->Project(Form("h_Zmumu_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut);
  Ztautau->Project(Form("h_Ztautau_%s_%s",hName.Data(), name.Data()),Form("%s",var.Data()),cut);
  Wmunu->Project(Form("h_Wmunu_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut);
  QCD->Project(Form("h_QCD_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut);
  TTbar->Project(Form("h_TTbar_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut);

  plotStackBase(h_data, h_Zmumu, h_Ztautau, h_Wmunu, h_QCD, h_TTbar, xtitle, ytitle, nbin, xlow, xmax, max, min, hName, name, log);

}

void plotStackBase(TH1* h_data, TH1 * h_Zmumu, TH1 * h_Ztautau, TH1* h_Wmunu, TH1* h_QCD, TH1* h_TTbar, TString & xtitle, TString & ytitle, const int& nbin, const double& xlow, const double& xmax, const double& max, const double & min, const TString& hName, const TString& name, bool & log){
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  if(log)
    c->SetLogy();

  h_data->Sumw2();
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(1);
  h_data->SetTitle(0);
  h_data->SetStats(0);
  h_data->GetXaxis()->SetTitle(xtitle.Data());
  h_data->GetYaxis()->SetTitle(ytitle.Data());


  h_Zmumu->Scale(norm_Zmm);
  h_Ztautau->Scale(norm_Ztautau);
  h_Wmunu->Scale(norm_Wmunu);
  h_QCD->Scale(norm_QCD);
  h_TTbar->Scale(norm_tt);

  h_Zmumu->SetFillColor(2);
  h_Ztautau->SetFillColor(5);
  h_Wmunu->SetFillColor(6);
  h_QCD->SetFillColor(3);
  h_TTbar->SetFillColor(4);

  THStack *stack = new THStack("stack","stack");
  
  stack->Add(h_QCD);
  stack->Add(h_TTbar);
  stack->Add(h_Wmunu);
  stack->Add(h_Ztautau);
  stack->Add(h_Zmumu);
  stack->SetTitle(0);
  if(max != -1)
    stack->SetMaximum(max); 
  if(min != -1)
    stack->SetMinimum(min);
  stack->Draw();
  h_data->Draw("same");

  TLegend *l= new TLegend(0.75,0.65,0.90,0.88);
  l->AddEntry(h_data,"Data","p");
  l->AddEntry(h_Zmumu,"Z #rightarrow #mu#mu","f");
  l->AddEntry(h_Ztautau,"Z #rightarrow #tau#tau","f");
  l->AddEntry(h_Wmunu,"W #rightarrow #mu#nu","f");
  l->AddEntry(h_QCD,"QCD","f");
  l->AddEntry(h_TTbar,"t#bar{t}","f");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  //c->Print("dimuon.eps"); 

}


void numberOfEvents( TTree* data, TTree * Zmumu, TTree * Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TCut cut,TString& s){
  double ndata = data->GetEntries(cut);  
  double nZmm = Zmumu->GetEntries(cut)*norm_Zmm;
  double nQCD = QCD->GetEntries(cut)*norm_QCD;  
  double nZtautau = Ztautau->GetEntries(cut)*norm_Ztautau;
  double nWmunu = Wmunu->GetEntries(cut)*norm_Wmunu;
  double nTTbar = TTbar->GetEntries(cut)*norm_tt;  
  cout << s.Data() << endl; 
  cout << "Zmumu   = " << nZmm << endl;
  cout << "QCD     = " << nQCD << endl;
  cout << "Ztautau = " << nZtautau << endl;
  cout << "Wmunu   = " << nWmunu << endl;
  cout << "TTbar   = " << nTTbar << endl;
  cout << "Total   = " << nZmm + nQCD + nZtautau + nWmunu + nTTbar << endl;
  cout << "Data    = " << ndata << endl;
}
