#include "EffSource.h"

void ROCTnP(){
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile * fbkg = new TFile("/home/tjkim/ntuple/iso/data/QCD_tight/vallot.root");
  TTree * tbkg = (TTree *) fbkg->Get("MuonAna/tree");

  //from normalized histos
  TFile * fhisto = new TFile("MuonAna_backup.root");
  TH1F * h_TTbar = (TH1F *) fhisto->Get("Step_1/hMCSig_TTbar_Step_1_relIso");
  TH1F * h_Wm = (TH1F *) fhisto->Get("Step_1/hMC_Wm_Step_1_relIso");
  TH1F * h_Zmm = (TH1F *) fhisto->Get("Step_1/hMC_Zmumu_Step_1_relIso");
  TH1F * h_QCD = (TH1F *) fhisto->Get("Step_1/hMC_QCD_Step_1_relIso");
  TH1F * h_Data = (TH1F *) fhisto->Get("Step_1/hData_Step_1_relIso");

  h_QCD->Add(h_TTbar);  
  h_QCD->Add(h_Wm);  
  h_QCD->Add(h_Zmm);  

  TCut cutbkg = "pt > 20 && pt < 50"; 
  
  TH1* h_bkg = new TH1F("h_bkg","h_bkg",50,0,0.5);
  tbkg->Project("h_bkg","(chIsoOpt04+phIsoOpt04+nhIsoOpt04)/pt", cutbkg);

  //Data vs PU
  plot(h_Data, h_QCD, "Data (T&P)", "MC (T&P)" , "QCD_MC_pt20_50_PU" , "p_{T}=20-50 GeV" );
  
}

void plot(TH1* h_bkg_Data, TH1* h_bkg_MC, const TString& leg1, const TString& leg2, const TString& name, const TString &header){

  double eff_sig_mc[23];
  double mc_errY_high[23];
  double mc_errY_low[23];

  double eff_sig_data[23];
  double data_errY_high[23];
  double data_errY_low[23];

  memcpy(eff_sig_mc, eff_sig_mc_tight, sizeof(eff_sig_mc_tight));
  memcpy(mc_errY_high, mc_errY_high_tight, sizeof(mc_errY_high_tight));
  memcpy(mc_errY_low, mc_errY_low_tight, sizeof(mc_errY_low_tight));

  memcpy(eff_sig_data, eff_sig_data_tight, sizeof(eff_sig_data_tight));
  memcpy(data_errY_high, data_errY_high_tight, sizeof(data_errY_high_tight));
  memcpy(data_errY_low, data_errY_low_tight, sizeof(data_errY_low_tight));

  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_mc = new TGraphAsymmErrors();

  TGraphAsymmErrors *gr_data_sigeff = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_mc_sigeff = new TGraphAsymmErrors();

  TGraphAsymmErrors *gr_data_qcdeff = new TGraphAsymmErrors();

  cout << "QCD (data)=" << h_bkg_Data->GetEntries() << endl;
  cout << "QCD (mc)=" << h_bkg_MC->Integral() << endl;

  for(int i=0 ; i < 23 ; i++  ){
    double bin = i*1+6;
    double point = h_bkg_Data->GetBinLowEdge(bin)+h_bkg_Data->GetBinWidth(bin);
    double eff_bkg_data = h_bkg_Data->Integral(1,bin)/h_bkg_Data->GetEntries();
    double eff_bkg_mc = h_bkg_MC->Integral(1,bin)/h_bkg_MC->Integral();

    cout << "[" << point << "]:" << "bkg eff (data)= " << eff_bkg_data << " bkg eff (mc)= " << eff_bkg_mc << " sig eff (data)= " << eff_sig_data[i] << " sig eff (mc)= " << eff_sig_mc[i] << endl;

    gr_data->SetPoint(i, eff_bkg_data, eff_sig_data[i]);
    gr_data->SetPointEYhigh(i, data_errY_high[i]);    
    gr_data->SetPointEYlow(i, data_errY_low[i]);    
    gr_data->SetPointEXhigh(i, sqrt(h_bkg_Data->Integral(1,bin))/h_bkg_Data->GetEntries());
    gr_data->SetPointEXlow(i, sqrt(h_bkg_Data->Integral(1,bin))/h_bkg_Data->GetEntries());

    gr_mc->SetPoint(i, eff_bkg_mc, eff_sig_mc[i]);
    gr_mc->SetPointEYhigh(i, mc_errY_high[i]);
    gr_mc->SetPointEYlow(i, mc_errY_low[i]);
    gr_mc->SetPointEXhigh(i, sqrt(h_bkg_MC->Integral(1,bin))/h_bkg_MC->GetEntries());
    gr_mc->SetPointEXlow(i, sqrt(h_bkg_MC->Integral(1,bin))/h_bkg_MC->GetEntries());

    gr_data_sigeff->SetPoint(i, point, eff_sig_data[i]);
    gr_data_sigeff->SetPointEYhigh(i, data_errY_high[i]);
    gr_data_sigeff->SetPointEYlow(i, data_errY_low[i]);

    gr_mc_sigeff->SetPoint(i, point, eff_sig_mc[i]);
    gr_mc_sigeff->SetPointEYhigh(i, mc_errY_high[i]);
    gr_mc_sigeff->SetPointEYlow(i, mc_errY_low[i]);
    
    gr_data_qcdeff->SetPoint(i, point, eff_bkg_data);
    gr_data_qcdeff->SetPointEYhigh(i, sqrt(h_bkg_Data->Integral(1,bin))/h_bkg_Data->GetEntries());
    gr_data_qcdeff->SetPointEYlow(i, sqrt(h_bkg_Data->Integral(1,bin))/h_bkg_Data->GetEntries());

  }

  TCanvas* c_qcdeff= new TCanvas(Form("c_qcdeff_%s",name.Data()),Form("c_qcdeff_%s",name.Data()),1);
  gr_data_qcdeff->GetYaxis()->SetTitle("Isolation Efficiency");
  gr_data_qcdeff->GetXaxis()->SetTitle("RelIso");
  gr_data_qcdeff->SetLineColor(1);
  gr_data_qcdeff->SetLineWidth(2);
  gr_data_qcdeff->SetMarkerColor(1);
  gr_data_qcdeff->SetMarkerSize(1.1);
  gr_data_qcdeff->SetMarkerStyle(20);
  gr_data_qcdeff->Draw("ACP");
  gr_data_qcdeff->SetFillColor(30);
  gr_data_qcdeff->SetFillStyle(3001);
  c_qcdeff->Print(Form("c_qcdeff_%s.eps",name.Data()));
  c_qcdeff->Print(Form("c_qcdeff_%s.C",name.Data()));
  c_qcdeff->Print(Form("c_qcdeff_%s.png",name.Data()));

  TCanvas* c_eff= new TCanvas(Form("c_eff_%s",name.Data()),Form("c_eff_%s",name.Data()),1);
  gr_data_sigeff->GetYaxis()->SetTitle("Isolation Efficiency");
  gr_data_sigeff->GetXaxis()->SetTitle("RelIso");
  gr_data_sigeff->SetLineColor(1);
  gr_data_sigeff->SetLineWidth(2);
  gr_data_sigeff->SetMarkerColor(1);
  gr_data_sigeff->SetMarkerSize(1.1);
  gr_data_sigeff->SetMarkerStyle(20);
  gr_data_sigeff->Draw("ACP");
  gr_data_sigeff->SetFillColor(30);
  gr_data_sigeff->SetFillStyle(3001);

  gr_mc_sigeff->SetLineColor(2);
  gr_mc_sigeff->SetLineWidth(2);
  gr_mc_sigeff->SetMarkerColor(2);
  gr_mc_sigeff->SetMarkerSize(1.1);
  gr_mc_sigeff->SetMarkerStyle(21);
  gr_mc_sigeff->Draw("CPSame");
  gr_mc_sigeff->SetFillColor(5);
  gr_mc_sigeff->SetFillStyle(3001);

  TLegend *l_eff= new TLegend(0.6,0.3,0.9,0.45);
  l_eff->SetHeader(Form("%s",header.Data()));
  l_eff->AddEntry(gr_data_sigeff,Form("%s",leg1.Data()),"PL");
  l_eff->AddEntry(gr_mc_sigeff,Form("%s",leg2.Data()),"PL");
  l_eff->SetTextSize(0.04);
  l_eff->SetFillColor(0);
  l_eff->SetLineColor(0);
  l_eff->Draw();
  c_eff->Print(Form("c_eff_%s.eps",name.Data()));
  c_eff->Print(Form("c_eff_%s.C",name.Data()));
  c_eff->Print(Form("c_eff_%s.png",name.Data()));

  TCanvas* c= new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  gr_data->GetYaxis()->SetTitle("Signal Efficiency");
  gr_data->GetXaxis()->SetTitle("QCD Efficiency");
  gr_data->SetLineColor(1);
  gr_data->SetLineWidth(2);
  gr_data->SetMarkerColor(1);
  gr_data->SetMarkerSize(1.1);
  gr_data->SetMarkerStyle(20);
  gr_data->Draw("ACP");
  gr_data->SetFillColor(30);
  gr_data->SetFillStyle(1001);


  gr_mc->SetLineColor(2);
  gr_mc->SetLineWidth(2);
  gr_mc->SetMarkerColor(2);
  gr_mc->SetMarkerSize(1.1);
  gr_mc->SetMarkerStyle(21);
  gr_mc->Draw("CPSame");
  gr_mc->SetFillColor(5);
  gr_mc->SetFillStyle(3001);
 
  TLegend *l= new TLegend(0.6,0.3,0.9,0.45);
  l->SetHeader(Form("%s",header.Data()));
  l->AddEntry(gr_data,Form("%s",leg1.Data()),"PL");
  l->AddEntry(gr_mc,Form("%s",leg2.Data()),"PL");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  c->Print(Form("c_ROCtnp_%s.eps",name.Data()));
  c->Print(Form("c_ROCtnp_%s.C",name.Data()));
  c->Print(Form("c_ROCtnp_%s.png",name.Data()));

}


