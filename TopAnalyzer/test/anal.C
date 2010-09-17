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
#include "style.h"
#include "TROOT.h"
#include "tdrstyle.C"

using namespace std;

double lumi_e = 2.88;
TString dir = "temp";
bool print = false;
TString type = "MuMu";
//ofstream myfile;

std::vector<TFile*> files;
std::vector<TTree*> trees;
std::vector<TString> hNames;
std::vector<TString> labels;
std::vector<double> norms;
std::vector<Color_t> colors;

TFile * fdata;
TTree * data;

void numberOfEvents( TCut cut, const TString& s){

  double ndata = data->GetEntries(cut);
  double total = 0;
  double sumerr2 = 0;
  double sig = 0;
  double Zn = 0;
  double Zerr2 = 0; 

  cout << s.Data() << "------------------------" << endl; 

  for(int i=0; i < (int) trees.size() ; i++){
    double numEvt = trees[i]->GetEntries(cut)*norms[i];
    if(hNames[i].Contains("TTbar")) sig = numEvt;
    double err = sqrt(numEvt*norms[i]);
    if(hNames[i].Contains("Zll") || hNames[i].Contains("ZJets")){
      Zn = Zn + numEvt;
      Zerr2 = err*err; 
    }else{
      cout << hNames[i] << " = " << numEvt << " +- " << err << endl;
    }
    total = total + numEvt;
    sumerr2 = sumerr2 + err*err;
  }
  cout << "Z = " << Zn << " +- " << sqrt(Zerr2) << endl;

  double bkg = total - sig;
  double soverb = sig/TMath::Sqrt(sig+bkg);

  double eTotal = sqrt(sumerr2);

  cout << "Total   = " << total << " +- " << eTotal << endl;
  cout << "----------------------------- " <<  endl;
  cout << "Data    = " << ndata << endl;
  cout << "s/Sqrt(s+b) = " << soverb << endl;
  cout << "----------------------------- " <<  endl;

}

void plotStackBase(TH1* h_data, vector<TH1*> h_mc, const TString & xtitle, const TString & ytitle, const int& nbin,  const double& max, const double & min, const TString& hName, const TString& name, const bool & log){

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  if(log)
    c->SetLogy();

  //overflow adding
  h_data->AddBinContent(nbin, h_data->GetBinContent(nbin+1)) ;
  for(int i=0; i < (int) trees.size() ; i++){
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


  for(int i=0; i < (int) h_mc.size(); i++){ 
    if(hNames[i].Contains("Zll") || hNames[i].Contains("ZJets")){
      continue;
    }else{
      stack->Add(h_mc[i]);
    }
  }
  
  int nhis = (int) h_mc.size();
  TH1 * h_Z = h_mc[nhis-1];
  if( hNames[nhis-2].Contains("ZJets")){ 
    h_Z->Add(h_mc[nhis-2]);
  }

  stack->Add(h_Z);

  if(max != -1)
    stack->SetMaximum(max); 
  if(min != -1)
    stack->SetMinimum(min);

  stack->SetTitle(0);
  stack->Draw();
  h_data->Draw("same");

  TLegend *l= new TLegend(0.73,0.57,0.88,0.88);
  l->AddEntry(h_data,"Data","p");
  for(int i= (int)trees.size()-1  ;i >= 0 ; i--){
    if(hNames[i].Contains("Zll")) continue;
    l->AddEntry(h_mc[i],labels[i],"f");
  }
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  Print(c, dir, hName, name, print);

}

void histStack(const TString& dir, const TString& var, const TString & xtitle, const TString & ytitle, const int& nbin, const double& max, const double & min, const TString& hName, const TString& name, const  bool & log){

  TH1F * h_data = (TH1F *) fdata->Get(Form("%s/%s",dir.Data(),var.Data()));
  std::vector<TH1*> h_mc;
  
  for(int i=0; i < (int) trees.size() ; i++){
    h_mc.push_back((TH1F *) files[i]->Get(Form("%s/%s",dir.Data(),var.Data())));
  }
  plotStackBase(h_data, h_mc, xtitle, ytitle, nbin,  max, min, hName, name, log);

}


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

  //histStack( "DiMuon", "h_mass","Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 1000,0.02, "dimuon",Form("mass_h_%s",step.Data()), true);
  //histStack( "DiMuon", "h_leadingpt","Leading p_{T} (GeV/c)", "Events/5 GeV/c",20, 30, 0, "leading",Form("pt_h_%s",step.Data()), false);
  if( step.Contains("step1") || step.Contains("step2") ){
    plotStack( "Z.mass()",cut, "Dimuon Mass (GeV/c^{2})", "Events/5 GeV/c^{2}",40, 0, 200, 1000, 0.1, "dimuon",Form("mass_%s",step.Data()), true);
  }

  plotStack("@jetspt30.size()",cut, "Jet Multiplicity", "Events", 5, 0, 5, 1200*r , -1, "jet",Form("multiplicity_%s",step.Data()), true);
  plotStack("MET",cut, "Missing E_{T}", "Events", 8, 0, 80, 1200*r , 0.02*r, "met",Form("et_%s",step.Data()), true);

  //plotStack("Z.leg1().pt()", cut, "Leading p_{T} (GeV/c)","Events/2 GeV/c", 20, 0, 100,    400,0.1, "leading",Form("pt_%s",step.Data()),  false);
  //plotStack("Z.leg1().eta()",cut, "Leading #eta (radian)","Events/0.1 rad.",35, -3.5, 3.5, 120, 0.1, "leading",Form("eta_%s",step.Data()), false);
  //plotStack("Z.leg1().phi()",cut, "Leading #phi (radian)","Events/0.1 rad.",35, -3.5, 3.5, 100, 0.1, "leading",Form("phi_%s",step.Data()), false);
  //plotStack("Z.leg2().pt()", cut, "Second p_{T} (GeV/c)", "Events/5 GeV/c", 20, 0, 100,    400,0.1, "second", Form("pt_h_%s",step.Data()),false); 
  //plotStack("Z.leg2().eta()",cut, "Second #eta (radian)", "Events/0.1 rad.",35, -3.5, 3.5, 120, 0.1, "second", Form("eta_%s",step.Data()), false);
  //plotStack("Z.leg2().phi()",cut, "Second #phi (radian)", "Events/0.1 rad.",35, -3.5, 3.5, 100, 0.1, "second", Form("phi_%s",step.Data()), false);

  numberOfEvents( cut, step);
}

void addFile(const TString& name, const TString& h, const TString& l, const double & sigma, Color_t c){
  TFile * f = new TFile(name);
  TH1F * evt = (TH1F *) f->Get(type+"/EventSummary");
  double nevents = evt->GetBinContent(1);
  double lumi = nevents/sigma;
  double norm = lumi_e/lumi; 
  cout << h << " = " << lumi << " pb-1 ( " << nevents << " events) " << endl; 
  TTree * tree = (TTree *) f->Get(type+"/tree");

  files.push_back(f);
  trees.push_back(tree);
  hNames.push_back(h);
  labels.push_back(l);
  norms.push_back(norm);
  colors.push_back(c);
}  

void anal(const TString& t="MuMu", bool p= false, const TString& d="temp"){
  type = t;
  print = p;
  dir = d;
  TString mcpath = "/home/tjkim/ntuple/top/"+type+"/MC/Spring10/";
  gROOT->LoadMacro("tdrstyle.C");
  defaultStyle();
  
  //myfile.open (Form("Info_%s.txt",dir.Data()));

  fdata = new TFile("/home/tjkim/ntuple/top/"+type+"/RD/Sep11/vallot.root");
  data = (TTree *) fdata->Get(type+"/tree");

  addFile(mcpath+"vallot_TTbar.root", "TTbar", "t#bar{t}", 157.5, 4);//Blue
  if(type == "MuMu") addFile(mcpath+"vallot_InclusiveMu15.root", "QCD", "QCD", 79688, 3);//Green
  //else if(type == "ElEl") addFile(mcpath+"vallot_QCD_BCtoE_Pt20to30.root", "QCD", "QCD", 79688, 3);//Green
  addFile(mcpath+"vallot_WJets.root", "Wlnu", "W #rightarrow l#nu", 31314, 46);// brown
  addFile(mcpath+"vallot_VVJets.root", "Dibosons", "Dibosons", 4.8 ,6 );//Magenta
  addFile(mcpath+"vallot_SingleTop.root", "SingleTop", "single top", 10.6 ,7 );// sky
  addFile(mcpath+"vallot_Ztautau.root", "Ztautau", "Z/#gamma* #rightarrow #tau#tau", 1660, 5);//Yellow
  addFile(mcpath+"vallot_ZJets.root", "ZJets", "Z/#gamma* #rightarrow ll", 3048, 2);//Red 
  if(type == "MuMu") addFile(mcpath+"vallot_Zmumu.root", "Zll", "Z/#gamma* #rightarrow ll", 1660, 2);//Red  
  else if(type == "ElEl") addFile(mcpath+"vallot_Zee.root", "Zll", "Z/#gamma* #rightarrow ll", 1660, 2);//Red  

  TCut pfiso = "(chIso1+nhIso1/0.33+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2/0.33+phIso2)/Z.leg2().pt() < 0.21 ";

  TCut step1 = "Z.mass() > 10";
  TCut step2 = step1 && pfiso;
  TCut step3 = step2 && "Z.sign() < 0";
  TCut step4 = step3 && "abs(Z.mass() - 91) > 15";
  TCut step5 = step4 && "@jetspt30.size() >= 1";
  TCut step6 = step5 && "MET > 30";

  //histStack("Muons", "cutflow","cutflow", "Muons",6, 60000, 1, "muon","cutflow", false);

  bool isoPlot = false;
  if(isoPlot){
    int max = 1200;
    int min = -1;
    plotStack( "chIso1",step1, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso1", true);
    plotStack( "nhIso1/0.33",step1, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso1", true);
    plotStack( "phIso1",step1, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso1", true);
    plotStack( "chIso2",step1, "chIso", "Events", 40, 0, 4, max , min, "iso","chIso2", true);
    plotStack( "nhIso2/0.33",step1, "nhIso/0.33", "Events", 40, 0, 4, max , min, "iso","nhIso2", true);
    plotStack( "phIso2",step1, "phIso", "Events", 40, 0, 4, max , min, "iso","phIso2", true);
  }

  plotStep( step1, "step1",1); 
  plotStep( step2, "step2",1); 
  plotStep( step3, "step3",1); 
  plotStep( step4, "step4",0.1); 
  plotStep( step5, "step5",0.1); 
  plotStep( step6, "step6",0.1); 

  cout <<"Final" << endl;
  data->Scan("RUN:LUMI:EVENT",step6);

  //myfile.close();
}

