#include "TFile.h"

void isoOpt(){

  TFile * fQCD = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_QCD.root");
  TFile * fTTbar = new TFile("/home/tjkim/ntuple/mc/top/Summer10/vallot_TTbar.root");

  TTree * QCD = (TTree *) fQCD->Get("MuonIso/tree");
  TTree * TTbar = (TTree *) fTTbar->Get("MuonIso/tree");

  TH1* h_QCD = new TH1F("h_QCD","h_QCD",40,0,0.4);
  TH1* h_TTbar = new TH1F("h_TTbar","h_TTbar",40,0,0.4);

  QCD->Project("h_QCD","chIso+nhIso+phIso/pt");
  TTbar->Project("h_TTbar","chIso+nhIso+phIso/pt");

  for(int i=1 ; i <40 ; i++){
    cout << "QCD eff= " << h_QCD->Integral(1,i)/h_QCD->Integral() << " TTbar eff= " << h_TTbar->Integral(1,i)/h_TTbar->Integral() << endl;
  }
}
