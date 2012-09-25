#include "style.h"

void nbJet(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TString path = "TTbarTuneZ2";

  TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v3/vallot_%s.root",path.Data()));
  TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v3/vallot_%s.root",path.Data()));
  TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v3/vallot_%s.root",path.Data()));

  TTree * t_MuMu = (TTree*) f_mm->Get("MuMu/tree");
  TTree * t_ElEl = (TTree*) f_ee->Get("ElEl/tree");
  TTree * t_MuEl = (TTree*) f_em->Get("MuEl/tree");

  draw(t_MuMu, t_ElEl, t_MuEl, "CSVM");
  draw(t_MuMu, t_ElEl, t_MuEl, "CSVT");

}

void draw(TTree* t_MuMu, TTree* t_ElEl, TTree* t_MuEl, const TString & name){
 
  TCut cut = "ZMass > 12 && abs(ZMass - 91.2) > 15 && PairSign < 0 && isIso > 0 && MET > 30 && @jetspt30.size() >=4";  
  TCut cut_em = "ZMass > 12 && abs(ZMass - 91.2) > 15 && PairSign < 0 && isIso > 0 && @jetspt30.size() >=4";  

  TH1 * h_nbjets_ttcc_MuMu = new TH1F("h_nbjets_ttcc_MuMu","h_nbjets_ttcc_MuMu",5,0,5);
  TH1 * h_nbjets_ttbb_MuMu = new TH1F("h_nbjets_ttbb_MuMu","h_nbjets_ttbb_MuMu",5,0,5);
  TH1 * h_nbjets_ttll_MuMu = new TH1F("h_nbjets_ttll_MuMu","h_nbjets_ttll_MuMu",5,0,5);
  TH1 * h_nbjets_ttjj_MuMu = new TH1F("h_nbjets_ttjj_MuMu","h_nbjets_ttjj_MuMu",5,0,5);

  TH1 * h_nbjets_ttcc_ElEl = new TH1F("h_nbjets_ttcc_ElEl","h_nbjets_ttcc_ElEl",5,0,5);
  TH1 * h_nbjets_ttbb_ElEl = new TH1F("h_nbjets_ttbb_ElEl","h_nbjets_ttbb_ElEl",5,0,5);
  TH1 * h_nbjets_ttll_ElEl = new TH1F("h_nbjets_ttll_ElEl","h_nbjets_ttll_ElEl",5,0,5);
  TH1 * h_nbjets_ttjj_ElEl = new TH1F("h_nbjets_ttjj_ElEl","h_nbjets_ttjj_ElEl",5,0,5);

  TH1 * h_nbjets_ttcc_MuEl = new TH1F("h_nbjets_ttcc_MuEl","h_nbjets_ttcc_MuEl",5,0,5);
  TH1 * h_nbjets_ttbb_MuEl = new TH1F("h_nbjets_ttbb_MuEl","h_nbjets_ttbb_MuEl",5,0,5);
  TH1 * h_nbjets_ttll_MuEl = new TH1F("h_nbjets_ttll_MuEl","h_nbjets_ttll_MuEl",5,0,5);
  TH1 * h_nbjets_ttjj_MuEl = new TH1F("h_nbjets_ttjj_MuEl","h_nbjets_ttjj_MuEl",5,0,5);

  TH1 * h_nbjets_ttcc = new TH1F("h_nbjets_ttcc","h_nbjets_ttcc",5,0,5);
  TH1 * h_nbjets_ttbb = new TH1F("h_nbjets_ttbb","h_nbjets_ttbb",5,0,5);
  TH1 * h_nbjets_ttll = new TH1F("h_nbjets_ttll","h_nbjets_ttll",5,0,5);
  TH1 * h_nbjets_ttjj = new TH1F("h_nbjets_ttjj","h_nbjets_ttjj",5,0,5);

  TCut visible = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut sig = "ttbarGen.NbJets20() >= 4";
  TCut ttcc = "ttbarGen.NcJets20() >= 2";

  t_MuMu->Project("h_nbjets_ttbb_MuMu",Form("nbjets30_%s",name.Data()),visible + sig + cut);
  t_MuMu->Project("h_nbjets_ttcc_MuMu",Form("nbjets30_%s",name.Data()),visible + !sig + ttcc + cut);
  t_MuMu->Project("h_nbjets_ttll_MuMu",Form("nbjets30_%s",name.Data()),visible + !sig + !ttcc + cut);
  t_MuMu->Project("h_nbjets_ttjj_MuMu",Form("nbjets30_%s",name.Data()),visible + cut);

  t_ElEl->Project("h_nbjets_ttbb_ElEl",Form("nbjets30_%s",name.Data()),visible + sig + cut);
  t_ElEl->Project("h_nbjets_ttcc_ElEl",Form("nbjets30_%s",name.Data()),visible + !sig + ttcc + cut);
  t_ElEl->Project("h_nbjets_ttll_ElEl",Form("nbjets30_%s",name.Data()),visible + !sig + !ttcc + cut);
  t_ElEl->Project("h_nbjets_ttjj_ElEl",Form("nbjets30_%s",name.Data()),visible + cut);

  t_MuEl->Project("h_nbjets_ttbb_MuEl",Form("nbjets30_%s",name.Data()),visible + sig + cut_em);
  t_MuEl->Project("h_nbjets_ttcc_MuEl",Form("nbjets30_%s",name.Data()),visible + !sig + ttcc + cut_em);
  t_MuEl->Project("h_nbjets_ttll_MuEl",Form("nbjets30_%s",name.Data()),visible + !sig + !ttcc + cut_em);
  t_MuEl->Project("h_nbjets_ttjj_MuEl",Form("nbjets30_%s",name.Data()),visible + cut_em);

  h_nbjets_ttbb->Add( h_nbjets_ttbb_MuMu, 1);
  h_nbjets_ttbb->Add( h_nbjets_ttbb_ElEl, 1);
  h_nbjets_ttbb->Add( h_nbjets_ttbb_MuEl, 1);

  h_nbjets_ttcc->Add( h_nbjets_ttcc_MuMu, 1);
  h_nbjets_ttcc->Add( h_nbjets_ttcc_ElEl, 1);
  h_nbjets_ttcc->Add( h_nbjets_ttcc_MuEl, 1);

  h_nbjets_ttll->Add( h_nbjets_ttll_MuMu, 1);
  h_nbjets_ttll->Add( h_nbjets_ttll_ElEl, 1);
  h_nbjets_ttll->Add( h_nbjets_ttll_MuEl, 1);

  h_nbjets_ttjj->Add( h_nbjets_ttjj_MuMu, 1);
  h_nbjets_ttjj->Add( h_nbjets_ttjj_ElEl, 1);
  h_nbjets_ttjj->Add( h_nbjets_ttjj_MuEl, 1);

  TCanvas * c = new TCanvas("c","c",1);

  double N_ttbb = h_nbjets_ttbb->Integral(1,6);
  double N_ttcc = h_nbjets_ttcc->Integral(1,6);
  double N_ttll = h_nbjets_ttll->Integral(1,6);
  double N_ttjj = h_nbjets_ttjj->Integral(1,6);

  cout << "N_ttbb= " << N_ttbb << " N_ttcc= " << N_ttcc << " N_ttll= " << N_ttll << " N_ttjj= " << N_ttjj << endl;

  h_nbjets_ttbb->Scale(1.0/N_ttbb);
  h_nbjets_ttcc->Scale(1.0/N_ttcc);
  h_nbjets_ttll->Scale(1.0/N_ttll);
  h_nbjets_ttjj->Scale(1.0/N_ttjj);

  h_nbjets_ttll->SetTitle("");
  h_nbjets_ttll->SetStats(0);
  h_nbjets_ttll->SetMaximum(0.65);
  h_nbjets_ttll->GetXaxis()->SetTitle(Form("b-jet multiplcity (%s)",name.Data()));
  h_nbjets_ttll->GetYaxis()->SetTitle("Normalized entries");

  h_nbjets_ttll->SetLineColor(4);
  h_nbjets_ttbb->SetLineColor(2);
  h_nbjets_ttcc->SetLineColor(3);
  h_nbjets_ttjj->SetLineColor(1);

  h_nbjets_ttll->SetLineWidth(2);
  h_nbjets_ttbb->SetLineWidth(2);
  h_nbjets_ttcc->SetLineWidth(2);
  h_nbjets_ttjj->SetLineWidth(2);

  h_nbjets_ttll->Draw();
  h_nbjets_ttbb->Draw("same");
  h_nbjets_ttcc->Draw("same");
  //h_nbjets_ttjj->Draw("same");

  SetLabel(0.2, 0.82, 4982);
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.15,0.82,"CMS Simulation, at #sqrt{s} = 7 TeV");


  TLegend *l = new TLegend(0.80,0.70,0.92,0.88);
  l->AddEntry(h_nbjets_ttbb,"tt + bb","L");
  l->AddEntry(h_nbjets_ttcc,"tt + cc","L");
  l->AddEntry(h_nbjets_ttll,"tt + LF","L");
  //l->AddEntry(h_nbjets_ttjj,"tt + jj","L");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();

  c->Print(Form("c_reco_jet_ttbb_ttcc_ttll_%s.eps",name.Data()));
  c->Print(Form("c_reco_jet_ttbb_ttcc_ttll_%s.C",name.Data()));

}
