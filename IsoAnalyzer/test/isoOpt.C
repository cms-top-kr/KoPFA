#include "TFile.h"

TGraph* getGraph(TTree *ts, TTree *tb, const TString & var, TCut csig, TCut cbkg, int low, int max, int start, const TString & name, int color, int style){

  TH1* h_sig = new TH1F(Form("h_sig_%s",name.Data()),Form("h_sig_%s",name.Data()),50,0,0.5);
  TH1* h_bkg = new TH1F(Form("h_bkg_%s",name.Data()),Form("h_bkg_%s",name.Data()),50,0,0.5);

  ts->Project(Form("h_sig_%s",name.Data()),Form("%s",var.Data()), csig);
  tb->Project(Form("h_bkg_%s",name.Data()),Form("%s",var.Data()), cbkg);

  TGraph *gr = new TGraph();
  TGraph *gr_opt = new TGraph();

  double optsoverb = 0;
  double optval = 0;
  for(int i=low ; i < max ; i++){
    double bin = i*1+start;
    double point = h_bkg->GetBinLowEdge(bin)+h_bkg->GetBinWidth(bin);
    double eff_bkg = h_bkg->Integral(1,bin)/h_bkg->GetEntries();
    double eff_sig = h_sig->Integral(1,bin)/h_sig->GetEntries();
    double soverb = eff_sig/sqrt(eff_sig+eff_bkg);

    cout << name.Data() << ":[" << point << "]:" << "bkg eff= " << eff_bkg << " sig eff= " << eff_sig << " : s/sqrt(s+b)= " << soverb << endl;

    gr->SetPoint(i-1, eff_bkg, eff_sig);
    gr_opt->SetPoint(i-1, point, soverb);

    if( soverb > optsoverb){
      optsoverb = soverb;
      optval = point;
    }
  }

  gr->SetLineColor(color);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(color);
  gr->SetMarkerSize(1.1);
  gr->SetMarkerStyle(style);

  TCanvas *c_opt = new TCanvas(Form("c_opt_%s",name.Data()),Form("c_opt_%s",name.Data()),1);
  gr_opt->Draw("ACP");
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.5,0.5,Form("%f at %5.2f",optsoverb,optval));
  
  return gr;
}

void isoOpt(){

  TFile * fbkg = new TFile("batch/MuMu/test/vallot_QCD.root");
  TFile * fsig = new TFile("batch/MuMu/test/vallot_ZJets.root");

  TTree * tbkg = (TTree *) fbkg->Get("MuMu/tree");
  TTree * tsig = (TTree *) fsig->Get("MuMu/tree");

  TCut cutsig = "Z.mass() > 12  && Z.sign() < 0";
  TCut cutbkg = "Z.mass() > 12  && Z.sign() < 0";
  TString pfiso03 = "relIso03lep1";
  TString pfiso04 = "relIso04lep1";
  TString pfiso05 = "relIso05lep1";
  TString deiso = "(trackIso1+ecalIso1+hcalIso1)/Z.leg1().pt()";

  TGraph *gr_pf03 = getGraph(tsig, tbkg, pfiso03, cutsig, cutbkg, 1, 25 , 1, "pf03", 3, 20);
  TGraph *gr_pf04 = getGraph(tsig, tbkg, pfiso04, cutsig, cutbkg, 1, 28 , 3, "pf04", 4, 20);
  TGraph *gr_pf05 = getGraph(tsig, tbkg, pfiso05, cutsig, cutbkg, 1, 28 , 3, "pf05", 7, 20);
  TGraph *gr_de = getGraph(tsig, tbkg, deiso, cutsig, cutbkg, 1, 25, 1, "de", 2, 23);

  TCanvas *c = new TCanvas("c","c",1);

  gr_pf03->Draw("ACP");
  gr_pf04->Draw("CPsame");
  gr_pf05->Draw("CPsame");
  gr_de->Draw("CPsame");

  TLegend *l= new TLegend(0.4,0.3,0.7,0.45);
  l->AddEntry(gr_pf03,"particle based, 0.3","PL");
  l->AddEntry(gr_pf04,"particle based, 0.4","PL");
  l->AddEntry(gr_pf05,"particle based, 0.5","PL");
  l->AddEntry(gr_de,"detector based, 0.3","PL");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  
}
