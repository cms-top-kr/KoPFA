#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "tdrstyle.C"
#include "TString.h"
#include "THStack.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>
#include <vector>

TString dir_ = "";

struct Sample{
  TFile *file;
  TString name;
  double norm;
  int fillcolor;
  int linecolor;
  TString label;
};

double getNorm( double nTotal, double X, double lumi){

  double SF = lumi * X / nTotal;
  return SF;

}

Sample Add(TFile * file, const TString & name, const TString & label, int fillcolor, double X = -1.0, int linecolor = 1){
  Sample out;
  out.file = file;
  out.name = name;
  out.label = label;
  out.fillcolor = fillcolor;
  out.linecolor = linecolor;
  if( X == -1.0){
    out.norm = 1.0;
  }else{
    TH1F* h = (TH1F*) file->Get(Form("%s/EventSummary",dir_.Data()));
    double nTotal = h->GetBinContent(1); 
    out.norm = getNorm( nTotal, X, 10000) ;
  }
  return out;
}

void plot( std::vector<Sample> sample, const TString & histName, const TString & canvasName, const TString & title,  double min, double max, bool log = false){

  TCanvas * c = new TCanvas(Form("c_%s",canvasName.Data()), Form("c_%s",canvasName.Data()) ,1);
  if(log) c->SetLogy();

  TLegend *l= new TLegend(0.7,0.7,0.87,0.87);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw(); 

  TH1F *hData = (TH1F *) sample[0].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
  hData->SetMarkerSize(0.4);
  hData->SetMarkerStyle(20);
  l->AddEntry(hData, sample[0].label, "P");
  cout << "Data = " << hData->Integral() << endl;
  double totalBkg = 0;

  THStack *hs = new THStack("hs",Form("%s",histName.Data()));
  for( unsigned int i = 1 ; i < sample.size() ; i++){
    TH1F *h = (TH1F *) sample[i].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
    h->SetFillColor( sample[i].fillcolor );
    h->SetLineColor( sample[i].linecolor );
    h->Scale( sample[i].norm );
    hs->Add(h);
    if( sample[i].linecolor == 1 ){
      l->AddEntry( h, sample[i].label, "F" );
    }
    cout << sample[i].name << "(" << histName.Data() << ") = " << h->Integral() << endl;
    totalBkg += h->Integral();
  }

  double DataSub = hData->Integral() - totalBkg;
  cout << "DataSub= " << DataSub << endl;

  hs->SetMaximum( max );
  hs->SetMinimum( min );
  hs->SetTitle(title.Data());

  hs->Draw();
  hData->Draw("sameP");
  l->Draw();

  c->Print(Form("c_%s.eps",canvasName.Data()));
}

void ElectronQCD(){
 
  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();
  dir_ = "ElectronAnalysis";

  std::vector<Sample> Samples;
  Samples.push_back( Add( new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/pfelectrons2/nhits0/njets2/vallot_Run2012ElEl.root") , "Run2012ElEl", "Data",  1 ) );
  Samples.push_back( Add( new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/pfelectrons2/nhits0/njets2/vallot_TTbarTuneZ2.root") , "TTbarTuneZ2", "t#bar{t}", 2 , 225 ) );
  Samples.push_back( Add( new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/pfelectrons2/nhits0/njets2/vallot_WJetsToLNu.root") , "WJetsToLNu",   "W+jets", 3 , 36257 ) );
  Samples.push_back( Add( new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/pfelectrons2/nhits0/njets2/vallot_ZJets10To50.root") , "ZJets10To50", "Z+jets", 4 , 860, 4) );
  Samples.push_back( Add( new TFile("/afs/cern.ch/work/t/tjkim/public/store/electron/pfelectrons2/nhits0/njets2/vallot_ZJets.root") ,       "ZJets",       "Z+jets", 4 , 3503.71 ) );
  

  plot( Samples, "Signal/h_dimass" , "signal_dimass", " Dimass;Dimass (GeV);Entries", 0.1, 10e7, true);  
  plot( Samples, "Signal/h_met" ,    "signal_met",  " MET;MET (GeV);Entries", 0.1, 10e7, true);  
  plot( Samples, "Signal/h_nJet" ,   "signal_nJet", " nJet;Jet multiplicity;Entries", 0.1, 10e7, true);  
  plot( Samples, "Signal/h_delphi" , "signal_delphi", " delphi;#Delta(l,MET);Entries", 0.1, 10e7, true);  

  plot( Samples, "QCD/h_dimass" , "qcd_dimass", " Dimass;Dimass (GeV);Entries", 0.1, 10e7, true);
  plot( Samples, "QCD/h_met" ,    "qcd_met",  " MET;MET (GeV);Entries", 0.1, 10e7, true);
  plot( Samples, "QCD/h_nJet" ,   "qcd_nJet", " nJet;Jet multiplicity;Entries", 0.1, 10e7, true);
  plot( Samples, "QCD/h_delphi" , "qcd_delphi", " delphi;#Delta(l,MET);Entries", 0.1, 10e7, true);

}

