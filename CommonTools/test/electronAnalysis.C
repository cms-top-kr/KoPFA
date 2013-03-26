#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

void iso(TH1* h_s, TH1* h_b, const TString & name){

  TCanvas * c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  c->SetLogy();

  TH1* h_dis_s = (TH1*) h_s->Clone("h_dis_s");
  TH1* h_dis_b = (TH1*) h_b->Clone("h_dis_b");

  h_dis_s->GetXaxis()->SetLimits(0,1);
  h_dis_b->GetXaxis()->SetLimits(0,1);

  h_dis_s->SetLineColor(2);
  h_dis_b->SetLineColor(4);

  h_dis_s->Draw();
  h_dis_b->Draw("same");

}

TGraphAsymmErrors* isoeff(TH1* h_s, TH1* h_b, const TString & name){

  TGraphAsymmErrors* out = new TGraphAsymmErrors;

  TCanvas * c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  c->SetLogy();

  double denS = h_s->GetEntries();
  double denB = h_b->GetEntries();

  TH1* h_eff_s =  (TH1*) h_s->Clone("h_eff_s");
  TH1* h_eff_b =  (TH1*) h_b->Clone("h_eff_b");

  h_eff_s->Rebin(10);
  h_eff_b->Rebin(10);

  for(int i=1; i < 51; i++){
    double numS = h_s->Integral(1,i);
    double numB = h_b->Integral(1,i);
    double effS = numS/denS;
    double effB = numB/denB;
    h_eff_s->SetBinContent(i,effS);
    h_eff_b->SetBinContent(i,effB);
    out->SetPoint(i-1,effB, effS);
  }

  h_eff_s->GetXaxis()->SetLimits(0,1);
  h_eff_b->GetXaxis()->SetLimits(0,1);

  h_eff_s->SetLineColor(2);
  h_eff_b->SetLineColor(4);

  h_eff_s->Draw();
  h_eff_b->Draw("same");

  return out;

}

void isoroc( TGraphAsymmErrors * roc, TGraphAsymmErrors * roc2, TGraphAsymmErrors * roc3, const TString & name ){

  TGraphAsymmErrors * roc_relPfIso03_barrel = ( TGraphAsymmErrors * ) roc->Clone();
  TGraphAsymmErrors * roc_relPfIso03db_barrel = ( TGraphAsymmErrors * ) roc2->Clone();
  TGraphAsymmErrors * roc_relPfIso03rho_barrel = ( TGraphAsymmErrors * ) roc3->Clone();

  TCanvas * c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  roc_relPfIso03_barrel->SetMarkerSize(0.8);
  roc_relPfIso03_barrel->SetMarkerStyle(20);
  roc_relPfIso03_barrel->SetMarkerColor(2);
  roc_relPfIso03_barrel->SetLineColor(2);
  roc_relPfIso03_barrel->SetLineWidth(2);
  roc_relPfIso03db_barrel->SetMarkerSize(0.8);
  roc_relPfIso03db_barrel->SetMarkerStyle(21);
  roc_relPfIso03db_barrel->SetMarkerColor(4);
  roc_relPfIso03db_barrel->SetLineColor(4);
  roc_relPfIso03db_barrel->SetLineWidth(2);
  roc_relPfIso03rho_barrel->SetMarkerSize(0.8);
  roc_relPfIso03rho_barrel->SetMarkerStyle(22);
  roc_relPfIso03rho_barrel->SetMarkerColor(3);
  roc_relPfIso03rho_barrel->SetLineColor(3);
  roc_relPfIso03rho_barrel->SetLineWidth(2);

  roc_relPfIso03_barrel->Draw("ALP");
  roc_relPfIso03db_barrel->Draw("sameLP");
  roc_relPfIso03rho_barrel->Draw("sameLP");

  TLegend *l_roc_iso = new TLegend(0.5,0.25,0.85,0.45);
  l_roc_iso->AddEntry(roc_relPfIso03_barrel,"PFIso","PL");
  l_roc_iso->AddEntry(roc_relPfIso03db_barrel,"PFIso+#Delta#beta","PL");
  l_roc_iso->AddEntry(roc_relPfIso03rho_barrel,"PFIso+#rho","PL");
  l_roc_iso->SetTextSize(0.04);
  l_roc_iso->SetFillColor(0);
  l_roc_iso->SetLineColor(0);
  l_roc_iso->Draw();

}

void isoroc( TGraphAsymmErrors * roc, TGraphAsymmErrors * roc2, const TString & name ){

  TGraphAsymmErrors * roc_relPfIso03_barrel = ( TGraphAsymmErrors * ) roc->Clone();
  TGraphAsymmErrors * roc_relPfIso03rho_barrel = ( TGraphAsymmErrors * ) roc2->Clone();

  TCanvas * c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  roc_relPfIso03_barrel->SetMarkerSize(0.8);
  roc_relPfIso03_barrel->SetMarkerStyle(20);
  roc_relPfIso03_barrel->SetMarkerColor(2);
  roc_relPfIso03_barrel->SetLineColor(2);
  roc_relPfIso03_barrel->SetLineWidth(2);
  roc_relPfIso03rho_barrel->SetMarkerSize(0.8);
  roc_relPfIso03rho_barrel->SetMarkerStyle(22);
  roc_relPfIso03rho_barrel->SetMarkerColor(3);
  roc_relPfIso03rho_barrel->SetLineColor(3);
  roc_relPfIso03rho_barrel->SetLineWidth(2);

  roc_relPfIso03_barrel->Draw("ALP");
  roc_relPfIso03rho_barrel->Draw("sameLP");

  TLegend *l_roc_iso = new TLegend(0.5,0.25,0.85,0.45);
  l_roc_iso->AddEntry(roc_relPfIso03_barrel,"PFIso 0.3","PL");
  l_roc_iso->AddEntry(roc_relPfIso03rho_barrel,"PFIso 0.4","PL");
  l_roc_iso->SetTextSize(0.04);
  l_roc_iso->SetFillColor(0);
  l_roc_iso->SetLineColor(0);
  l_roc_iso->Draw();

}


void electronAnalysis(){

  TFile* f_data = new TFile("$WORK/data/export/tjkim/store/RD/Run2012/v1/vallot_Run2012ElEl.root");
  TFile* f_ttbar = new TFile("$WORK/data/export/tjkim/store/MC/Summer12/v1/vallot_TTbarTuneZ2.root");

  TH1* h_relPfISo03_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso03");
  TH1* h_relPfISo03_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso03");

  TH1* h_relPfISo03_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso03");
  TH1* h_relPfISo03_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso03");

  TH1* h_relPfISo03db_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso03db");
  TH1* h_relPfISo03db_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso03db");

  TH1* h_relPfISo03db_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso03db");
  TH1* h_relPfISo03db_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso03db");

  TH1* h_relPfISo03rho_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso03rho");
  TH1* h_relPfISo03rho_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso03rho");

  TH1* h_relPfISo03rho_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso03rho");
  TH1* h_relPfISo03rho_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso03rho");

  TH1* h_relPfISo04_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso04");
  TH1* h_relPfISo04_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso04");

  TH1* h_relPfISo04_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso04");
  TH1* h_relPfISo04_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso04");

  TH1* h_relPfISo04db_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso04db");
  TH1* h_relPfISo04db_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso04db");

  TH1* h_relPfISo04db_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso04db");
  TH1* h_relPfISo04db_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso04db");

  TH1* h_relPfISo04rho_qcd_barrel = (TH1*) f_data->Get("ElectronAnalysis/Iso/Barrel/QCD/h_pfRelIso04rho");
  TH1* h_relPfISo04rho_qcd_endcap = (TH1*) f_data->Get("ElectronAnalysis/Iso/Endcap/QCD/h_pfRelIso04rho");

  TH1* h_relPfISo04rho_ttbar_barrel = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Barrel/h_pfRelIso04rho");
  TH1* h_relPfISo04rho_ttbar_endcap = (TH1*) f_ttbar->Get("ElectronAnalysis/Iso/Endcap/h_pfRelIso04rho");


  iso( h_relPfISo03_ttbar_barrel , h_relPfISo03_qcd_barrel, "barrel03");
  iso( h_relPfISo03_ttbar_endcap , h_relPfISo03_qcd_endcap, "endcap03");

  iso( h_relPfISo03db_ttbar_barrel , h_relPfISo03db_qcd_barrel, "barreldb03");
  iso( h_relPfISo03db_ttbar_endcap , h_relPfISo03db_qcd_endcap, "endcapdb03");

  iso( h_relPfISo03rho_ttbar_barrel , h_relPfISo03rho_qcd_barrel, "barrelrho03");
  iso( h_relPfISo03rho_ttbar_endcap , h_relPfISo03rho_qcd_endcap, "endcaprho03");

  iso( h_relPfISo04_ttbar_barrel , h_relPfISo04_qcd_barrel, "barrel04");
  iso( h_relPfISo04_ttbar_endcap , h_relPfISo04_qcd_endcap, "endcap04");

  iso( h_relPfISo04db_ttbar_barrel , h_relPfISo04db_qcd_barrel, "barreldb04");
  iso( h_relPfISo04db_ttbar_endcap , h_relPfISo04db_qcd_endcap, "endcapdb04");

  iso( h_relPfISo04rho_ttbar_barrel , h_relPfISo04rho_qcd_barrel, "barrelrho04");
  iso( h_relPfISo04rho_ttbar_endcap , h_relPfISo04rho_qcd_endcap, "endcaprho04");


  TGraphAsymmErrors * roc_relPfIso03_barrel = isoeff( h_relPfISo03_ttbar_barrel , h_relPfISo03_qcd_barrel, "barreleff03");
  TGraphAsymmErrors * roc_relPfIso03_endcap = isoeff( h_relPfISo03_ttbar_endcap , h_relPfISo03_qcd_endcap, "endcapeff03");

  TGraphAsymmErrors * roc_relPfIso03db_barrel = isoeff( h_relPfISo03db_ttbar_barrel , h_relPfISo03db_qcd_barrel, "barreldbeff03");
  TGraphAsymmErrors * roc_relPfIso03db_endcap = isoeff( h_relPfISo03db_ttbar_endcap , h_relPfISo03db_qcd_endcap, "endcapdbeff03");

  TGraphAsymmErrors * roc_relPfIso03rho_barrel = isoeff( h_relPfISo03rho_ttbar_barrel , h_relPfISo03rho_qcd_barrel, "barrelrhoeff03");
  TGraphAsymmErrors * roc_relPfIso03rho_endcap = isoeff( h_relPfISo03rho_ttbar_endcap , h_relPfISo03rho_qcd_endcap, "endcaprhoeff03");

  TGraphAsymmErrors * roc_relPfIso04_barrel = isoeff( h_relPfISo04_ttbar_barrel , h_relPfISo04_qcd_barrel, "barreleff04");
  TGraphAsymmErrors * roc_relPfIso04_endcap = isoeff( h_relPfISo04_ttbar_endcap , h_relPfISo04_qcd_endcap, "endcapeff04");

  TGraphAsymmErrors * roc_relPfIso04db_barrel = isoeff( h_relPfISo04db_ttbar_barrel , h_relPfISo04db_qcd_barrel, "barreldbeff04");
  TGraphAsymmErrors * roc_relPfIso04db_endcap = isoeff( h_relPfISo04db_ttbar_endcap , h_relPfISo04db_qcd_endcap, "endcapdbeff04");

  TGraphAsymmErrors * roc_relPfIso04rho_barrel = isoeff( h_relPfISo04rho_ttbar_barrel , h_relPfISo04rho_qcd_barrel, "barrelrhoeff04");
  TGraphAsymmErrors * roc_relPfIso04rho_endcap = isoeff( h_relPfISo04rho_ttbar_endcap , h_relPfISo04rho_qcd_endcap, "endcaprhoeff04");

  isoroc( roc_relPfIso03_barrel, roc_relPfIso03db_barrel, roc_relPfIso03rho_barrel, "barrelroc");
  isoroc( roc_relPfIso03_endcap, roc_relPfIso03db_endcap, roc_relPfIso03rho_endcap, "endcaproc");
  isoroc( roc_relPfIso03_barrel, roc_relPfIso04_barrel, "barrelroc_conesize");
  isoroc( roc_relPfIso03_endcap, roc_relPfIso04_endcap, "endcaproc_conesize");

}
