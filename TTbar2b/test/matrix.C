#include "TH2.h"
#include "tdrstyle.C"

void matrix(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile* f1 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v3/vallot_TTbarTuneZ2.root");
  TFile* f2 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v3/vallot_TTbarTuneZ2.root");
  TFile* f3 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v3/vallot_TTbarTuneZ2.root");

  TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
  TTree* treeElEl = (TTree*)f2->Get("ElEl/tree");
  TTree* treeMuEl = (TTree*)f3->Get("MuEl/tree");

  TH2F* h2_mm = new TH2F("h2_mm","h2_mm",5,-0.5,4.5,5,-0.5,4.5);
  TH2F* h2_ee = new TH2F("h2_ee","h2_ee",5,-0.5,4.5,5,-0.5,4.5);
  TH2F* h2_em = new TH2F("h2_em","h2_em",5,-0.5,4.5,5,-0.5,4.5);
  TH2F* h2 = new TH2F("h2","h2",5,-0.5,4.5,5,-0.5,4.5);

  TH1F* h_mm = new TH1F("h_mm","h_mm",5,-0.5,4.5);
  TH1F* h_ee = new TH1F("h_ee","h_ee",5,-0.5,4.5);
  TH1F* h_em = new TH1F("h_em","h_em",5,-0.5,4.5);
  TH1F* h = new TH1F("h","h",5,-0.5,4.5);

  TCut precut_em =    "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt30.size() >= 4";
  TCut precut = precut_em + "abs(ZMass - 91.2) > 15 && MET > 30";

  treeMuMu->Project("h2_mm","nbjets30_CSVT:nbjets30_CSVM", precut);
  treeElEl->Project("h2_ee","nbjets30_CSVT:nbjets30_CSVM", precut);
  treeMuEl->Project("h2_em","nbjets30_CSVT:nbjets30_CSVM", precut_em);

  h2->Add(h2_mm); 
  h2->Add(h2_ee); 
  h2->Add(h2_em); 
 
  treeMuMu->Project("h1_mm","nbjets30_CSVM", precut);
  treeElEl->Project("h1_ee","nbjets30_CSVM", precut);
  treeMuEl->Project("h1_em","nbjets30_CSVM", precut_em);

  h1->Add(h1_mm);
  h1->Add(h1_ee);
  h1->Add(h1_em);
 
  TCanvas * c= new TCanvas("c","c",1);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle("b-Jet multiplicity (CSVM)");
  h2->GetYaxis()->SetTitle("b-Jet multiplicity (CSVT)");
  h2->Draw("Textcolz");
  c->Print("matrix.png");
  c->Print("matrix.eps");
 
  TFile* f = TFile::Open("matrix.root", "recreate");
  h1->Write();
  h2->Write();
  f->Write();
  f->Close(); 
}
