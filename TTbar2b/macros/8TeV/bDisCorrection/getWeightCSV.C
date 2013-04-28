void getWeightCSV(){

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TString path = "../TTBB_27Apr2013_CSVWeight";
  TFile * f = new TFile(path+"/merged.root");

  double XBins[] = {0.0, 0.05,  0.1, 0.15,  0.2, 0.25, 0.3,0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8,0.9};//8 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;

  double XBins2[] = {0.0,  0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9};//8 bins
  int nX2 = sizeof(XBins2)/sizeof(double) - 1;

  plot(f, "jet1_bDisCSV","csv_first", nX, XBins);
  plot(f, "jet2_bDisCSV","csv_second", nX2, XBins2);

}

void plot(TFile *f, const TString & variable, const TString & name, int nX, double XBins[] ){

  TH1F * h_DataSub       = (TH1F * ) f->Get(Form("Step_5/hDataSub_Step_5_%s", variable.Data()));
  TH1F * h_MCSig_TTbarbb = (TH1F * ) f->Get(Form("Step_5/hMCSig_TTbarbb_Step_5_%s", variable.Data()));
  TH1F * h_MC_TTbarcc    = (TH1F * ) f->Get(Form("Step_5/hMC_TTbarcc_Step_5_%s", variable.Data()));
  TH1F * h_MC_TTbarll    = (TH1F * ) f->Get(Form("Step_5/hMC_TTbarll_Step_5_%s", variable.Data()));
  TH1F * h_MC_TTbarOthers    = (TH1F * ) f->Get(Form("Step_5/hMC_TTbarOthers_Step_5_%s", variable.Data()));
  TH1F * h_MC_DYll    = (TH1F * ) f->Get(Form("Step_5/hMC_DYll_Step_5_%s", variable.Data()));

  TH1F * h_Data = h_DataSub->Clone();
  h_Data->Add(h_MC_DYll);  
  h_Data->Add(h_MCSig_TTbarbb, -1);  
  TH1F * h_MC = h_MC_DYll->Clone();

  h_MC = (TH1F*) h_MC->Rebin(nX, "h_MC", XBins);
  h_Data = (TH1F*) h_Data->Rebin(nX, "h_Data", XBins);
 
  TCanvas * c = new TCanvas(Form("c_norm_%s", name.Data()) , Form("c_norm_%s", name.Data()) ,1);
  h_MC->Scale(1.0/h_MC->Integral());
  h_Data->Scale(1.0/h_Data->Integral());
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

  TCanvas * c_csv_SF = new TCanvas(Form("c_%s_SF", name.Data()),Form("c_%s_SF", name.Data()),1);

  TH1F * h_SF = h_MC->Clone();
  h_SF->Reset();
  h_SF->Sumw2();
  h_SF->Divide(h_Data, h_MC);

  TF1* functioncsv = new TF1("functioncsv", "pol2");
  functioncsv->SetLineColor(2);
  h_SF->Fit(functioncsv);
  h_SF->SetMinimum(0.0);
  h_SF->SetMaximum(3.5);
  h_SF->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_SF->GetYaxis()->SetTitle("Scale Factor (Data/MC)");
  h_SF->SetStats(0);
  h_SF->SetLineColor(4);
  h_SF->SetLineWidth(2);
  h_SF->SetLineStyle(20);
  h_SF->SetFillColor(0);
  h_SF->SetTitle("");
  h_SF->Draw("HIST");
  TH1F* functioncsv_err = (TH1F*) h_SF->Clone();
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(functioncsv_err,0.68);
  functioncsv_err->SetFillColor(2);
  functioncsv_err->SetFillStyle(3005);
  functioncsv_err->SetStats(0);
  functioncsv_err->Draw("e3 same");
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.2,0.8,"8 TeV");

  c_csv_SF->Print(Form("c_%s_SF.eps", name.Data()));
  

}
