void getWeightCSV(){

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TString path = "../TTBB_03June2013_CSVWeight";
  TFile * f = new TFile(path+"/merged.root");

  double XBins[] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};//8 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;

  double XBins2[] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.5, 1.0 };//8 bins
  int nX2 = sizeof(XBins2)/sizeof(double) - 1;

  //to calculate normalization factor
  TH1F * h_data = getDataSub(f, "ZMass", 0);
  TH1F * h_data_up_bflavor = getDataSub(f, "ZMass", -0.05);
  TH1F * h_data_dw_bflavor = getDataSub(f, "ZMass", 0.05);
  TH1F * h_mc   = getMC(f, "ZMass"); 

  double ndata = h_data->Integral(); 
  double ndata_up_bflavor = h_data_up_bflavor->Integral(); 
  double ndata_dw_bflavor = h_data_dw_bflavor->Integral(); 
  double nmc = h_mc->Integral(); 
 
  //plots 
  //inclusive
/*
  plot(f, "jet1_bDisCSV","csv_first",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV","csv_second", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

  //pt 30-35
  plot(f, "jet1_bDisCSV_30_35","csv_first_30_35",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_30_35","csv_second_30_35", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

  //pt 35-40
  plot(f, "jet1_bDisCSV_35_40","csv_first_35_40",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_35_40","csv_second_35_40", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

  //pt 40-50
  plot(f, "jet1_bDisCSV_40_50","csv_first_40_50",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_40_50","csv_second_40_50", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

  //pt 50
  plot(f, "jet1_bDisCSV_50","csv_first_50",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_50","csv_second_50", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
*/
  //center
  //pt 30-35
  plot(f, "jet1_bDisCSV_30_35_center","csv_first_30_35_center",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_30_35_center","csv_second_30_35_center", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 35-40
  plot(f, "jet1_bDisCSV_35_40_center","csv_first_35_40_center",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_35_40_center","csv_second_35_40_center", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 40-50
  plot(f, "jet1_bDisCSV_40_50_center","csv_first_40_50_center",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_40_50_center","csv_second_40_50_center", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 50
  plot(f, "jet1_bDisCSV_50_center","csv_first_50_center",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_50_center","csv_second_50_center", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

  //forward
  //pt 30-35
  plot(f, "jet1_bDisCSV_30_35_forward","csv_first_30_35_forward",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_30_35_forward","csv_second_30_35_forward", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 35-40
  plot(f, "jet1_bDisCSV_35_40_forward","csv_first_35_40_forward",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_35_40_forward","csv_second_35_40_forward", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 40-50
  plot(f, "jet1_bDisCSV_40_50_forward","csv_first_40_50_forward",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_40_50_forward","csv_second_40_50_forward", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  //pt 50
  plot(f, "jet1_bDisCSV_50_forward","csv_first_50_forward",   nX, XBins,  ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);
  plot(f, "jet2_bDisCSV_50_forward","csv_second_50_forward", nX2, XBins2, ndata,nmc,ndata_up_bflavor,ndata_dw_bflavor);

}

TH1F * getDataSub(TFile *f, const TString & variable, double bflavorweight ){
  TH1F * h_DataSub       = (TH1F * ) f->Get(Form("ZSel/hDataSub_ZSel_%s", variable.Data()));
  TH1F * h_MCSig_TTbar = (TH1F * ) f->Get(Form("ZSel/hMCSig_TTbar_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYb    = (TH1F * ) f->Get(Form("ZSel/hMC_DYb_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYc    = (TH1F * ) f->Get(Form("ZSel/hMC_DYc_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYLF    = (TH1F * ) f->Get(Form("ZSel/hMC_DYLF_ZSel_%s", variable.Data()));

  //remove Z+b process 
  TH1F * h_Data = h_DataSub->Clone();
  h_Data->Add(h_MCSig_TTbar, -1.0);
  h_Data->Add(h_MC_DYLF);
  h_Data->Add(h_MC_DYc);
  h_Data->Add(h_MC_DYb, bflavorweight);

  return h_Data;
}

TH1F * getMC(TFile *f, const TString & variable ){
  TH1F * h_MC_DYb    = (TH1F * ) f->Get(Form("ZSel/hMC_DYb_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYc    = (TH1F * ) f->Get(Form("ZSel/hMC_DYc_ZSel_%s", variable.Data()));
  TH1F * h_MC_DYLF    = (TH1F * ) f->Get(Form("ZSel/hMC_DYLF_ZSel_%s", variable.Data()));
  TH1F * h_MC = h_MC_DYLF->Clone();
  h_MC->Add(h_MC_DYc);

  return h_MC;
}

void plot(TFile *f, const TString & variable, const TString & name, int nX, double XBins[], double ndata, double nmc, double ndata_up_bflavor, double ndata_dw_bflavor ){
  
  TH1F * h_Data = getDataSub(f, variable, 0);
  TH1F * h_Data_Up_bFlavor = getDataSub(f, variable, -0.05);
  TH1F * h_Data_Dw_bFlavor = getDataSub(f, variable, 0.05);
  TH1F * h_MC   = getMC(f, variable);

  //rebin
  h_MC = (TH1F*) h_MC->Rebin(nX, "h_MC", XBins);
  h_Data = (TH1F*) h_Data->Rebin(nX, "h_Data", XBins);
  h_Data_Up_bFlavor = (TH1F*) h_Data_Up_bFlavor->Rebin(nX, "h_Data_Up_bFlavor", XBins);
  h_Data_Dw_bFlavor = (TH1F*) h_Data_Dw_bFlavor->Rebin(nX, "h_Data_Dw_bFlavor", XBins);

  //normalization
  h_MC->Scale(1.0/nmc);
  h_Data->Scale(1.0/ndata);
  h_Data_Up_bFlavor->Scale(1.0/ndata_up_bflavor);
  h_Data_Dw_bFlavor->Scale(1.0/ndata_dw_bflavor);

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
  h_SF->SetMaximum(2.5);
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
  h_SF_Up_bFlavor->Divide(h_Data_Up_bFlavor, h_MC);
  h_SF_Dw_bFlavor->Divide(h_Data_Dw_bFlavor, h_MC);
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

  //printing out
  int nb = h_SF->GetNbinsX();
  for(int i=1; i <= nb;i++){
    double SF = h_SF->GetBinContent(i);
    double center = h_SF->GetBinCenter(i);
    double center_up = h_SF_Up_bFlavor->GetBinContent(i) ;
    double center_dw = h_SF_Dw_bFlavor->GetBinContent(i) ;
    
    cout << center << " && " << SF << " && " << "up: " << center_up << " && " << "dw: " << center_dw << endl;
  }

  //fitting turned off
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
