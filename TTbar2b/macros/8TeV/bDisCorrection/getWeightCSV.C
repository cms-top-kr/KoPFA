void getWeightCSV(){

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TString path = "../TTBB_03June2013_CSVWeight";
  TFile * f = new TFile(path+"/merged.root");

  double XBins[] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};//8 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;

  double XBins2[] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 1.0 };//8 bins
  int nX2 = sizeof(XBins2)/sizeof(double) - 1;

  plot(f, "jet1_bDisCSV","csv_first", nX, XBins);
  plot(f, "jet2_bDisCSV","csv_second", nX2, XBins2);

}

void plot(TFile *f, const TString & variable, const TString & name, int nX, double XBins[] ){

  TH1F * h_DataSub       = (TH1F * ) f->Get(Form("ZSel/hDataSub_ZSel_%s", variable.Data()));
  TH1F * h_MCSig_TTbar = (TH1F * ) f->Get(Form("ZSel/hMCSig_TTbar_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYb    = (TH1F * ) f->Get(Form("ZSel/hMC_DYb_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYc    = (TH1F * ) f->Get(Form("ZSel/hMC_DYc_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYLF    = (TH1F * ) f->Get(Form("ZSel/hMC_DYLF_ZSel_%s", variable.Data()));

  //remove Z+b process 
  TH1F * h_Data = h_DataSub->Clone();
  TH1F * h_MC = h_MC_DYLF->Clone();

  h_Data->Add(h_MCSig_TTbar, -1);
  h_Data->Add(h_MC_DYLF);
  h_Data->Add(h_MC_DYc);
  //h_Data->Add(h_MC_DYb);
  h_MC->Add(h_MC_DYc);
  //h_MC->Add(h_MC_DYb);

  //systematic uncertainty due to b-flavor
  TH1F * h_Data_Up_bFlavor = h_DataSub->Clone();
  TH1F * h_Data_Dw_bFlavor = h_DataSub->Clone();
  TH1F * h_MC_Up_bFlavor = h_MC_DYLF->Clone();
  TH1F * h_MC_Dw_bFlavor = h_MC_DYLF->Clone();
  h_Data_Up_bFlavor->Add(h_MCSig_TTbar, -1);
  h_Data_Up_bFlavor->Add(h_MC_DYLF);
  h_Data_Up_bFlavor->Add(h_MC_DYc);
  h_Data_Up_bFlavor->Add(h_MC_DYb, 0.05);
  h_MC_Up_bFlavor->Add(h_MC_DYc);
  h_MC_Up_bFlavor->Add(h_MC_DYb, 0.05);

  h_Data_Dw_bFlavor->Add(h_MCSig_TTbar, -1);
  h_Data_Dw_bFlavor->Add(h_MC_DYLF);
  h_Data_Dw_bFlavor->Add(h_MC_DYc);
  h_Data_Dw_bFlavor->Add(h_MC_DYb, -0.05);
  h_MC_Dw_bFlavor->Add(h_MC_DYc);
  h_MC_Dw_bFlavor->Add(h_MC_DYb, -0.05);

  //rebin
  h_MC = (TH1F*) h_MC->Rebin(nX, "h_MC", XBins);
  h_MC_Up_bFlavor = (TH1F*) h_MC->Rebin(nX, "h_MC_Up_bFlavor", XBins);
  h_MC_Dw_bFlavor = (TH1F*) h_MC->Rebin(nX, "h_MC_Dw_bFlavor", XBins);
  h_Data = (TH1F*) h_Data->Rebin(nX, "h_Data", XBins);
  h_Data_Up_bFlavor = (TH1F*) h_Data_Up_bFlavor->Rebin(nX, "h_Data_Up_bFlavor", XBins);
  h_Data_Dw_bFlavor = (TH1F*) h_Data_Dw_bFlavor->Rebin(nX, "h_Data_Dw_bFlavor", XBins);

  //normalization
  h_MC->Scale(1.0/h_MC->Integral());
  h_MC_Up_bFlavor->Scale(1.0/h_MC_Up_bFlavor->Integral());
  h_MC_Dw_bFlavor->Scale(1.0/h_MC_Dw_bFlavor->Integral());
  h_Data->Scale(1.0/h_Data->Integral());
  h_Data_Up_bFlavor->Scale(1.0/h_Data_Up_bFlavor->Integral());
  h_Data_Dw_bFlavor->Scale(1.0/h_Data_Dw_bFlavor->Integral());

  //draw control plots
  TCanvas * c = new TCanvas(Form("c_norm_%s", name.Data()) , Form("c_norm_%s", name.Data()) ,1);
  h_MC->SetTitle(""); 
  h_MC->GetYaxis()->SetTitle("Normalized Entries"); 
  h_MC->Draw();
  h_MC->SetMaximum(0.7);
  h_Data->Draw("same");
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.5,0.8,"8 TeV");

  TLegend *l = new TLegend(0.73,0.74,0.90,0.88);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->AddEntry(h_Data,"Data Z","P");
  l->AddEntry(h_MC,"MC Z","F");
  l->Draw();

  c->Print(Form("c_norm_%s.eps",name.Data()));

  //draw SF plots
  TCanvas * c_csv_SF = new TCanvas(Form("c_%s_SF", name.Data()),Form("c_%s_SF", name.Data()),1);

  TH1F * h_SF = h_MC->Clone();
  h_SF->Reset();
  h_SF->Sumw2();
  h_SF->Divide(h_Data, h_MC);

  h_SF->SetMinimum(0.4);
  h_SF->SetMaximum(2.0);
  h_SF->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_SF->GetYaxis()->SetTitle("Scale Factor (Data/MC)");
  h_SF->SetStats(0);
  h_SF->SetLineColor(4);
  h_SF->SetLineWidth(2);
  h_SF->SetLineStyle(20);
  h_SF->SetFillColor(0);
  h_SF->SetTitle("");
  h_SF->Draw("HIST");

  //TF1* functioncsv = new TF1("functioncsv", "pol4");
  //functioncsv->SetLineColor(2);
  //h_SF->Fit(functioncsv);
  //TH1F* functioncsv_err = (TH1F*) h_SF->Clone();
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(functioncsv_err,0.68);
  //functioncsv_err->SetFillColor(2);
  //functioncsv_err->SetFillStyle(3001);
  //functioncsv_err->SetStats(0);
  //functioncsv_err->Draw("e3 same");

  TH1F * h_SF_Up_bFlavor = h_MC->Clone();
  TH1F * h_SF_Dw_bFlavor = h_MC->Clone();
  h_SF_Up_bFlavor->Reset();
  h_SF_Dw_bFlavor->Reset();
  h_SF_Up_bFlavor->Sumw2();
  h_SF_Dw_bFlavor->Sumw2();
  h_SF_Up_bFlavor->Divide(h_Data_Up_bFlavor, h_MC_Up_bFlavor);
  h_SF_Dw_bFlavor->Divide(h_Data_Dw_bFlavor, h_MC_Dw_bFlavor);
  h_SF_Up_bFlavor->SetLineStyle(2);
  h_SF_Dw_bFlavor->SetLineStyle(2);
  h_SF_Up_bFlavor->SetLineWidth(1);
  h_SF_Dw_bFlavor->SetLineWidth(1);
  h_SF_Up_bFlavor->SetLineColor(2);
  h_SF_Dw_bFlavor->SetLineColor(2);
  h_SF_Up_bFlavor->SetFillColor(0);
  h_SF_Dw_bFlavor->SetFillColor(0);
  h_SF_Up_bFlavor->Draw("HISTsame");
  h_SF_Dw_bFlavor->Draw("HISTsame");

  //TF1* functioncsv_Up_bFlavor = new TF1("functioncsv_Up_bFlavor", "pol4");
  //functioncsv_Up_bFlavor->SetLineColor(4);
  //h_SF_Up_bFlavor->Fit(functioncsv_Up_bFlavor,"N", 0, 0.9);
  //functioncsv_Up_bFlavor->Draw("same");

  //TF1* functioncsv_Dw_bFlavor = new TF1("functioncsv_Dw_bFlavor", "pol4");
  //functioncsv_Dw_bFlavor->SetLineColor(4);
  //h_SF_Dw_bFlavor->Fit(functioncsv_Dw_bFlavor,"N", 0, 0.9);
  //functioncsv_Dw_bFlavor->Draw("same");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.2,0.8,"8 TeV");

  c_csv_SF->Print(Form("c_%s_SF.eps", name.Data()));

}
