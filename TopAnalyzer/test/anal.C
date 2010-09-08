#include <iostream>
#include <fstream>
#include "THStack.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TChain.h"
#include "TH1.h"
#include "TCut.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "norm.h"
#include "style.h"

TString dir = "TOPDIL_noPileupSequence";
//TString dir = "TOPDIL_NoPileupSequence";
bool print = false;
ofstream myfile;

std::vector<TTree*> test;

void numberOfEvents( TTree* data, TTree * Zmumu, TTree * Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TCut cut,TString& s){
  double ndata = data->GetEntries(cut);
  double nZmm = Zmumu->GetEntries(cut)*norm_Zmm;
  double nQCD = QCD->GetEntries(cut)*norm_QCD;
  double nZtautau = Ztautau->GetEntries(cut)*norm_Ztautau;
  double nWmunu = Wmunu->GetEntries(cut)*norm_Wmunu;
  double nTTbar = TTbar->GetEntries(cut)*norm_tt;

  double sig = nTTbar;
  double bkg = nZmm+nQCD+nZtautau+nWmunu;
  double soverb = sig/TMath::Sqrt(sig+bkg);

  double eZmm = sqrt(nZmm*norm_Zmm);
  double eQCD = sqrt(nQCD*norm_QCD);
  double eZtautau = sqrt(nZtautau*norm_Ztautau);
  double eWmunu = sqrt(nWmunu*norm_Wmunu);
  double eTTbar = sqrt(nTTbar*norm_tt);
  double eTotal = sqrt(eZmm*eZmm+eQCD*eQCD+eZtautau*eZtautau+eWmunu*eWmunu+eTTbar*eTTbar);

  cout << s.Data() << " ------------------ " <<  endl;
  cout << "Zmumu   = " << nZmm << " +- " << eZmm << endl;
  cout << "QCD     = " << nQCD << " +- " << eQCD << endl;
  cout << "Ztautau = " << nZtautau << " +- " << eZtautau << endl;
  cout << "Wmunu   = " << nWmunu << " +- " << eWmunu << endl;
  cout << "TTbar   = " << nTTbar << " +- " << eTTbar << endl;
  cout << "Total   = " << nZmm + nQCD + nZtautau + nWmunu + nTTbar << " +- " << eTotal << endl;
  cout << "------------------------ " <<  endl;
  cout << "Data    = " << ndata << endl;
  cout << "s/Sqrt(s+b) = " << soverb << endl;
  cout << "------------------------ " <<  endl;

  myfile << s.Data() << " ------------------ " <<  endl;
  myfile << "Zmumu   = " << nZmm << " +- " << eZmm << endl;
  myfile << "QCD     = " << nQCD << " +- " << eQCD << endl;
  myfile << "Ztautau = " << nZtautau << " +- " << eZtautau << endl;
  myfile << "Wmunu   = " << nWmunu << " +- " << eWmunu << endl;
  myfile << "TTbar   = " << nTTbar << " +- " << eTTbar << endl;
  myfile << "Total   = " << nZmm + nQCD + nZtautau + nWmunu + nTTbar << " +- " << eTotal << endl;
  myfile << "------------------------ " <<  endl;
  myfile << "Data    = " << ndata << endl;
  myfile << "s/Sqrt(s+b) = " << soverb << endl;
  myfile << "------------------------ " <<  endl;


}


void plotStackBase(TH1* h_data, TH1 * h_Zmumu, TH1 * h_Ztautau, TH1* h_Wmunu, TH1* h_QCD, TH1* h_TTbar, const TString & xtitle, const TString & ytitle, const int& nbin,  const double& max, const double & min, const TString& hName, const TString& name, const bool & log){
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  if(log)
    c->SetLogy();

  //overflow adding
  double overflow_data = h_data->GetBinContent(nbin+1); 
  double overflow_Zmumu = h_Zmumu->GetBinContent(nbin+1); 
  double overflow_Ztautau = h_Ztautau->GetBinContent(nbin+1); 
  double overflow_Wmunu = h_Wmunu->GetBinContent(nbin+1); 
  double overflow_QCD = h_QCD->GetBinContent(nbin+1); 
  double overflow_TTbar = h_TTbar->GetBinContent(nbin+1); 
 
  h_data->AddBinContent(nbin,overflow_data) ;
  h_Zmumu->AddBinContent(nbin,overflow_Zmumu) ;
  h_Ztautau->AddBinContent(nbin,overflow_Ztautau) ;
  h_Wmunu->AddBinContent(nbin,overflow_Wmunu) ;
  h_QCD->AddBinContent(nbin,overflow_QCD) ;
  h_TTbar->AddBinContent(nbin,overflow_TTbar) ;

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

  Print(c, dir, hName, name, print);

}

void histStack(TFile* fdata, TFile * fZmumu, TFile * fZtautau, TFile* fWmunu, TFile* fQCD, TFile* fTTbar, TString dir, TString var, TString & xtitle, TString & ytitle, const int& nbin, const double& max, const double & min, const TString& hName, const TString& name, const  bool & log){

  TH1F * h_data = (TH1F *) fdata->Get(Form("%s/%s",dir.Data(),var.Data()));
  TH1F * h_Zmumu = (TH1F *) fZmumu->Get(Form("%s/%s",dir.Data(),var.Data()));
  TH1F * h_Ztautau = (TH1F *) fZtautau->Get(Form("%s/%s",dir.Data(),var.Data()));
  TH1F * h_Wmunu = (TH1F *) fWmunu->Get(Form("%s/%s",dir.Data(),var.Data()));
  TH1F * h_QCD = (TH1F *) fQCD->Get(Form("%s/%s",dir.Data(),var.Data()));
  TH1F * h_TTbar = (TH1F *) fTTbar->Get(Form("%s/%s",dir.Data(),var.Data()));

  plotStackBase(h_data, h_Zmumu, h_Ztautau, h_Wmunu, h_QCD, h_TTbar, xtitle, ytitle, nbin,  max, min, hName, name, log);

}


void plotStack(TTree* data, TTree * Zmumu, TTree * Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TString var, TCut cut, const TString & xtitle, const TString & ytitle, const int& nbin, const double& xlow, const double& xmax, const double& max, const double & min, const TString& hName, const TString& name, const bool & log){

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

  plotStackBase(h_data, h_Zmumu, h_Ztautau, h_Wmunu, h_QCD, h_TTbar, xtitle, ytitle, nbin, max, min, hName, name, log);

}

void plotStep(TTree* data, TTree* Zmumu, TTree* Ztautau, TTree* Wmunu, TTree* QCD, TTree* TTbar, TCut cut, TString& step, const double & r){

  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_mass","Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 1000,0.02, "dimuon",Form("mass_h_%s",step.Data()), true);
  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_leadingpt","Leading p_{T} (GeV/c)", "Events/5 GeV/c",20, 30, 0, "leading",Form("pt_h_%s",step.Data()), false);

  if( step.Contains("step0") || step.Contains("step1") || step.Contains("step2") ){
    plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.mass()",cut, "Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 0, 200, 1000*r,0.02*r, "dimuon",Form("mass_%s",step.Data()), true);
  }

  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "@jetspt30.size()",cut, "Jet Multiplicity", "Events", 5, 0, 5, 1200*r , -1, "jet",Form("multiplicity_%s",step.Data()), true);
  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "MET",cut, "Missing E_{T}", "Events", 8, 0, 80, 1200*r , 0.02*r, "met",Form("et_%s",step.Data()), true);

  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().pt()",cut, "Leading p_{T} (GeV/c)", "Events/2 GeV/c", 50, 0, 100, 40,0, "leading",Form("pt_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().eta()",cut, "Leading #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("eta_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg1().phi()",cut, "Leading #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("phi_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().pt()",cut, "Second p_{T} (GeV/c)", "Events/5 GeV/c", 20, 0, 100, 100,0, "second",Form("pt_h_%s",step.Data()), false); 
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().eta()",cut, "Second #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("eta_%s",step.Data()), false);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "Z.leg2().phi()",cut, "Second #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("phi_%s",step.Data()), false);

  numberOfEvents( data,Zmumu,Ztautau,Wmunu,QCD, TTbar, cut, step);
}

void anal(){
  myfile.open (Form("Info_%s.txt",dir.Data()));

  using namespace std;
  //TFile * fdata = new TFile("/home/tjkim/ntuple/data/top/Aug13/vallot_presentedAug26.root");
  //TFile * fdata = new TFile("/home/tjkim/ntuple/data/top/Aug13/vallot.root");
  TFile * fdata = new TFile("/home/tjkim/ntuple/data/top/Sep3_noPileupSequence/vallot.root");
  //TFile * fZmumu = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_Zmumu.root");
  TFile * fZmumu = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_ZJets.root");
  TFile * fZtautau = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_Ztautau.root");
  TFile * fWmunu = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_WJets.root");
  TFile * fQCD = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_QCD.root");
  TFile * fTTbar = new TFile("/home/tjkim/ntuple/mc/top/Spring10/vallot_TTbar.root");

  TTree * data = (TTree *) fdata->Get("DiMuon/tree");
  TTree * Zmumu = (TTree *) fZmumu->Get("DiMuon/tree");
  TTree * Ztautau = (TTree *) fZtautau->Get("DiMuon/tree");
  TTree * Wmunu = (TTree *) fWmunu->Get("DiMuon/tree");
  TTree * QCD = (TTree *) fQCD->Get("DiMuon/tree");
  TTree * TTbar = (TTree *) fTTbar->Get("DiMuon/tree");

  totalevent( fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar);

  TCut pfiso = "(chIso1+nhIso1/0.33+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2/0.33+phIso2)/Z.leg2().pt() < 0.21 ";

  TCut pre;
  TCut step0 = "Z.mass() > 10";
  TCut step1 = step0 && pfiso;
  TCut step2 = step1 && "Z.sign() < 0";
  TCut step3 = step2 && "abs(Z.mass() - 91) > 15";
  TCut step4 = step3 && "@jetspt30.size() >= 1";
  TCut step5 = step4 && "MET > 30";

    //numberOfEvents( data,Zmumu,Ztautau,Wmunu,QCD, TTbar, pre,"pre");
  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "Muons", "cutflow","cutflow", "Muons",6, 60000, 1, "muon","cutflow", false);
  int max = 1200;
  int min = -1;
  plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "chIso1",step0, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso1", true);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "nhIso1/0.33",step0, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso1", true);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "phIso1",step0, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso1", true);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "chIso2",step0, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso2", true);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "nhIso2/0.33",step0, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso2", true);
  //plotStack(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, "phIso2",step0, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso2", true);
  //numberOfEvents( data,Zmumu,Ztautau,Wmunu,QCD, TTbar, forIso, "forIsoStudy");

  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step0, "step0",1); 
  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step1, "step1",1); 
  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step2, "step2",1); 
  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step3, "step3",0.1); 
  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step4, "step4",0.1); 
  //plotStep(data, Zmumu, Ztautau, Wmunu, QCD, TTbar, step5, "step5",0.1); 

  cout <<"step5" << endl;
  data->Scan("RUN:LUMI:EVENT",step5);

  myfile.close();
}

