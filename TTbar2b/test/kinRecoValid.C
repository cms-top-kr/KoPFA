#include "style.h"

void kinRecoValid(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TString path = "TTbarTuneZ2";

  TFile* f_mm = new TFile("vallot_TTbarTuneZ2.root");
  //TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v1/vallot_%s.root",path.Data()));
  //TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v1/vallot_%s.root",path.Data()));
  //TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v1/vallot_%s.root",path.Data()));

  TTree * t_MuMu = (TTree*) f_mm->Get("MuMu/tree");
  //TTree * t_ElEl = (TTree*) f_ee->Get("ElEl/tree");
  //TTree * t_MuEl = (TTree*) f_em->Get("MuEl/tree");

  TH1 * h      = new TH1F("h","h",25,0,25);
  TH1 * h_tag2 = new TH1F("h_tag2","h_tag2",25,0,25);
  TH1 * h_tag3 = new TH1F("h_tag3","h_tag3",25,0,25);

  t_MuMu->Project("h","abs(jetspt30flavor[bCSVM_ext])","kinttbarMCSVM > 0 && @bCSVM_ext.size() > 0");
  t_MuMu->Project("h_tag2","abs(jetspt30flavor[bCSVM_ext])","kinttbarMCSVM > 0 && @bCSVM_ext.size() > 0 && nbjets30_CSVM == 2");
  t_MuMu->Project("h_tag3","abs(jetspt30flavor[bCSVM_ext])","kinttbarMCSVM > 0 && @bCSVM_ext.size() > 0 && nbjets30_CSVM >= 3");

  double nb = h->GetBinContent(6);
  double nb_tag2 = h_tag2->GetBinContent(6);
  double nb_tag3 = h_tag3->GetBinContent(6);

  double nt = h->GetEntries();
  double nt_tag2 = h_tag2->GetEntries();
  double nt_tag3 = h_tag3->GetEntries();

  double f = (nt-nb)/nt;
  double f_tag2 = (nt_tag2-nb_tag2)/nt_tag2;
  double f_tag3 = (nt_tag3-nb_tag3)/nt_tag3;
 
  cout << "nb= " << nb << " nt= " << nt << " f= " << f << endl;
  cout << "tag2: nb= " << nb_tag2 << " nt= " << nt_tag2 << " f= " << f_tag2 << endl;
  cout << "tag3: nb= " << nb_tag3 << " nt= " << nt_tag3 << " f= " << f_tag3 << endl;
 
  TCanvas * c = new TCanvas("c","c",1);
  h->Scale(1.0/nt);
  h->SetTitle("3 b-tag bin");
  h->GetXaxis()->SetTitle("Parton Flavor");
  h->GetYaxis()->SetTitle("Norm. Extra Jets");
  h->Draw();

  TCanvas * c_tag2 = new TCanvas("c_tag2","c_tag2",1);
  h_tag2->Scale(1.0/nt_tag2);
  h_tag2->SetTitle("");
  h_tag2->GetXaxis()->SetTitle("Parton Flavor");
  h_tag2->GetYaxis()->SetTitle("Norm. Extra Jets");
  h_tag2->Draw();

  TCanvas * c_tag3 = new TCanvas("c_tag3","c_tag3",1);
  h_tag3->Scale(1.0/nt_tag3);
  h_tag3->SetTitle("");
  h_tag3->GetXaxis()->SetTitle("Parton Flavor");
  h_tag3->GetYaxis()->SetTitle("Norm. Extra Jets");
  h_tag3->Draw();

  c->Print("c_extrajet_flavor.eps");
  c_tag2->Print("c_extrajet_flavor_tag2.eps");
  c_tag3->Print("c_extrajet_flavor_tag3.eps");

 
}

