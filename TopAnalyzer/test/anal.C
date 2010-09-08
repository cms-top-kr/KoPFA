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
//#include "norm.h"
#include "style.h"

double lumi_e = 2.88;
TString dir = "TOPDIL_noPileupSequence";
//TString dir = "TOPDIL_NoPileupSequence";
bool print = false;
ofstream myfile;
std::vector<TTree*> trees;
std::vector<TString> hNames;
std::vector<TString> labels;
std::vector<double> norms;
std::vector<Color_t> colors;
TTree * data;

void numberOfEvents( TCut cut, const TString& s){

  double ndata = data->GetEntries(cut);
  vector<double> nbkg;
  double total = 0;
  double sumerr2 = 0;
  cout << s.Data() << " ------------------ " <<  endl;
  for(int i=0; i < (int) trees.size() ; i++){
    double numEvt = trees[i]->GetEntries(cut)*norms[i];
    double err = sqrt(numEvt*norms[i]);
    nbkg.push_back(numEvt);
    cout << hNames[i] << " = " << numEvt << " +- " << err << endl;
    total = total + numEvt;
    sumerr2 = sumerr2 + err*err;
  }

  double sig = nbkg[4];
  double bkg = total - sig;
  double soverb = sig/TMath::Sqrt(sig+bkg);

  double eTotal = sqrt(sumerr2);

  cout << "Total   = " << total << " +- " << eTotal << endl;
  cout << "------------------------ " <<  endl;
  cout << "Data    = " << ndata << endl;
  cout << "s/Sqrt(s+b) = " << soverb << endl;
  cout << "------------------------ " <<  endl;
 
}

//void plotStackBase(TH1* h_data, TH1 * h_Zmumu, TH1 * h_Ztautau, TH1* h_Wmunu, TH1* h_QCD, TH1* h_TTbar, const TString & xtitle, const TString & ytitle, const int& nbin,  const double& max, const double & min, const TString& hName, const TString& name, const bool & log){
void plotStackBase(TH1* h_data, vector<TH1*> h_mc, const TString & xtitle, const TString & ytitle, const int& nbin,  const double& max, const double & min, const TString& hName, const TString& name, const bool & log){

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  if(log)
    c->SetLogy();

  //overflow adding
  h_data->AddBinContent(nbin, h_data->GetBinContent(nbin+1)) ;
  for(int i=0; i < trees.size() ; i++){
    h_mc[i]->AddBinContent(nbin,h_mc[i]->GetBinContent(nbin+1)) ;
    h_mc[i]->Scale(norms[i]);
    h_mc[i]->SetFillColor(colors[i]);
  }

  h_data->Sumw2();
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(1);
  h_data->SetTitle(0);
  h_data->SetStats(0);
  h_data->GetXaxis()->SetTitle(xtitle.Data());
  h_data->GetYaxis()->SetTitle(ytitle.Data());

  THStack *stack = new THStack("stack","stack");
  
  stack->Add(h_mc[1]);
  stack->Add(h_mc[4]);
  stack->Add(h_mc[3]);
  stack->Add(h_mc[2]);
  stack->Add(h_mc[0]);

  stack->SetTitle(0);
  if(max != -1)
    stack->SetMaximum(max); 
  if(min != -1)
    stack->SetMinimum(min);
  stack->Draw();
  h_data->Draw("same");

  TLegend *l= new TLegend(0.75,0.65,0.90,0.88);
  l->AddEntry(h_data,"Data","p");
  for(int i=0 ;i < trees.size() ; i++){
    l->AddEntry(h_mc[i],labels[i],"f");
  }
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  Print(c, dir, hName, name, print);

}

//void histStack(TFile* fdata, TFile * fZmumu, TFile * fZtautau, TFile* fWmunu, TFile* fQCD, TFile* fTTbar, TString dir, TString var, TString & xtitle, TString & ytitle, const int& nbin, const double& max, const double & min, const TString& hName, const TString& name, const  bool & log){

//  TH1F * h_data = (TH1F *) fdata->Get(Form("%s/%s",dir.Data(),var.Data()));
//  TH1F * h_Zmumu = (TH1F *) fZmumu->Get(Form("%s/%s",dir.Data(),var.Data()));
//  TH1F * h_Ztautau = (TH1F *) fZtautau->Get(Form("%s/%s",dir.Data(),var.Data()));
//  TH1F * h_Wmunu = (TH1F *) fWmunu->Get(Form("%s/%s",dir.Data(),var.Data()));
//  TH1F * h_QCD = (TH1F *) fQCD->Get(Form("%s/%s",dir.Data(),var.Data()));
//  TH1F * h_TTbar = (TH1F *) fTTbar->Get(Form("%s/%s",dir.Data(),var.Data()));

//  plotStackBase(h_data, h_Zmumu, h_Ztautau, h_Wmunu, h_QCD, h_TTbar, xtitle, ytitle, nbin,  max, min, hName, name, log);

//}


void plotStack( TString var, TCut cut, const TString & xtitle, const TString & ytitle, const int& nbin, const double& xlow, const double& xmax, const double& max, const double & min, const TString& hName, const TString& name, const bool & log){

  TH1 *h_data = new TH1D(Form("h_data_%s_%s",hName.Data(),name.Data()),"data histo",nbin,xlow,xmax);
  std::vector<TH1*> h_mc;

  for(int i=0 ; i < (int)trees.size() ; i++){
    h_mc.push_back(new TH1F(Form("h_%s_%s_%s",hNames[i].Data(),hName.Data(),name.Data()),"MC histo",nbin,xlow,xmax));
  }

  data->Project(Form("h_data_%s_%s",hName.Data(),name.Data()),Form("%s",var.Data()),cut);
  for(int i=0 ; i < (int)trees.size() ; i++){
     trees[i]->Project(Form("h_%s_%s_%s",hNames[i].Data(), hName.Data(),name.Data()),Form("%s",var.Data()),cut);
  }

  plotStackBase(h_data, h_mc, xtitle, ytitle, nbin, max, min, hName, name, log);

}

void plotStep(TCut cut, const TString& step, const double & r){

  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_mass","Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 1000,0.02, "dimuon",Form("mass_h_%s",step.Data()), true);
  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "h_leadingpt","Leading p_{T} (GeV/c)", "Events/5 GeV/c",20, 30, 0, "leading",Form("pt_h_%s",step.Data()), false);

  if( step.Contains("step0") || step.Contains("step1") || step.Contains("step2") ){
    plotStack( "Z.mass()",cut, "Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 0, 200, 1000*r,0.02*r, "dimuon",Form("mass_%s",step.Data()), true);
  }

  plotStack("@jetspt30.size()",cut, "Jet Multiplicity", "Events", 5, 0, 5, 1200*r , -1, "jet",Form("multiplicity_%s",step.Data()), true);
  plotStack("MET",cut, "Missing E_{T}", "Events", 8, 0, 80, 1200*r , 0.02*r, "met",Form("et_%s",step.Data()), true);

  //plotStack("Z.leg1().pt()",cut, "Leading p_{T} (GeV/c)", "Events/2 GeV/c", 50, 0, 100, 40,0, "leading",Form("pt_%s",step.Data()), false);
  //plotStack("Z.leg1().eta()",cut, "Leading #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("eta_%s",step.Data()), false);
  //plotStack("Z.leg1().phi()",cut, "Leading #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "leading",Form("phi_%s",step.Data()), false);
  //plotStack("Z.leg2().pt()",cut, "Second p_{T} (GeV/c)", "Events/5 GeV/c", 20, 0, 100, 100,0, "second",Form("pt_h_%s",step.Data()), false); 
  //plotStack("Z.leg2().eta()",cut, "Second #eta (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("eta_%s",step.Data()), false);
  //plotStack("Z.leg2().phi()",cut, "Second #phi (radian)", "Events/0.1 rad.", 70, -3.5, 3.5, 20,0, "second",Form("phi_%s",step.Data()), false);

  numberOfEvents( cut, step);
}

void addFile(TFile* f, const TString& h, const TString& l, const double & sigma, Color_t c){
  TH1F * evt = (TH1F *) f->Get("DiMuon/EventSummary");
  double nevents = evt->GetBinContent(1);
  double lumi = nevents/sigma;
  double norm = lumi_e/lumi; 
  cout << h << " = " << lumi << " pb-1 ( " << nevents << " events) " << endl; 
  TTree * tree = (TTree *) f->Get("DiMuon/tree");
  trees.push_back(tree);
  hNames.push_back(h);
  labels.push_back(l);
  norms.push_back(norm);
  colors.push_back(c);
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

  data = (TTree *) fdata->Get("DiMuon/tree");

  addFile(fZmumu, "Zmumu", "Z #rightarrow #mu#mu", 3048, 2);
  addFile(fQCD, "QCD", "QCD", 79688, 3);
  addFile(fZtautau, "Ztautau", "Z #rightarrow #tau#tau", 1660, 5);
  addFile(fWmunu, "Wmunu", "W #rightarrow #mu#nu", 31314, 6);
  addFile(fTTbar, "TTbar", "t#bar{t}", 157.5, 4); 


  TCut pfiso = "(chIso1+nhIso1/0.33+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2/0.33+phIso2)/Z.leg2().pt() < 0.21 ";

  TCut pre;
  TCut step0 = "Z.mass() > 10";
  TCut step1 = step0 && pfiso;
  TCut step2 = step1 && "Z.sign() < 0";
  TCut step3 = step2 && "abs(Z.mass() - 91) > 15";
  TCut step4 = step3 && "@jetspt30.size() >= 1";
  TCut step5 = step4 && "MET > 30";

  //histStack(fdata, fZmumu, fZtautau, fWmunu, fQCD, fTTbar, "Muons", "cutflow","cutflow", "Muons",6, 60000, 1, "muon","cutflow", false);

  bool isoPlot = false;
  if(isoPlot){
    int max = 1200;
    int min = -1;
    plotStack( "chIso1",step0, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso1", true);
    plotStack( "nhIso1/0.33",step0, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso1", true);
    plotStack( "phIso1",step0, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso1", true);
    plotStack( "chIso2",step0, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso2", true);
    plotStack( "nhIso2/0.33",step0, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso2", true);
    plotStack( "phIso2",step0, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso2", true);
  }

  //plotStep(step0, "step0",1); 
  plotStep( step1, "step1",1); 
  //plotStep( step2, "step2",1); 
  //plotStep( step3, "step3",0.1); 
  //plotStep( step4, "step4",0.1); 
  //plotStep( step5, "step5",0.1); 

  cout <<"step5" << endl;
  data->Scan("RUN:LUMI:EVENT",step5);

  myfile.close();
}

