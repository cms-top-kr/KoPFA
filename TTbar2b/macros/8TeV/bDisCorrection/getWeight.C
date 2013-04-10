void getWeight(){

  //TString path = "TTBB_ptweight_TTbarEnriched";
  TString path = "TTBB_ptweight_ZEnriched";

  TFile * f = new TFile(path+"/merged.root");

  TH1F * h_DataSub       = (TH1F * ) f->Get("Step_5/hDataSub_Step_5_jetpt30");
  TH1F * h_MCSig_TTbarbb = (TH1F * ) f->Get("Step_5/hMCSig_TTbarbb_Step_5_jetpt30");
  TH1F * h_MC_TTbarcc    = (TH1F * ) f->Get("Step_5/hMC_TTbarcc_Step_5_jetpt30");
  TH1F * h_MC_TTbarll    = (TH1F * ) f->Get("Step_5/hMC_TTbarll_Step_5_jetpt30");
  TH1F * h_MC_TTbarOthers    = (TH1F * ) f->Get("Step_5/hMC_TTbarOthers_Step_5_jetpt30");
  TH1F * h_MC_DYll    = (TH1F * ) f->Get("Step_5/hMC_DYll_Step_5_jetpt30");

  /*
  TH1F * h_Data = h_DataSub->Clone();
  h_Data->Add(h_MC_TTbarcc);  
  h_Data->Add(h_MC_TTbarll);  
  h_Data->Add(h_MC_TTbarOthers);  

  TH1F * h_MC = h_MCSig_TTbarbb->Clone();
  h_MC->Add(h_MC_TTbarcc);
  h_MC->Add(h_MC_TTbarll);
  h_MC->Add(h_MC_TTbarOthers);
  */

  TH1F * h_Data = h_DataSub->Clone();
  h_Data->Add(h_MC_DYll);  
  h_Data->Add(h_MCSig_TTbarbb, -1);  

  TH1F * h_MC = h_MC_DYll->Clone();

  double XBins[] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 280, 300, 320, 400, 500};//5 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;

  h_MC = (TH1F*) h_MC->Rebin(nX, "h_MC", XBins);
  h_Data = (TH1F*) h_Data->Rebin(nX, "h_Data", XBins);
 
  TCanvas * c = new TCanvas("c","c",1);
  h_MC->Scale(1.0/h_MC->Integral());
  h_Data->Scale(1.0/h_Data->Integral());

  h_MC->Draw();
  h_MC->SetMaximum(0.5);
  h_Data->Draw("same");
  c->Print(path+"/c_pt.eps");

  TCanvas * c_pt_SF = new TCanvas("c_pt_SF","c_pt_SF",1);

  TH1F * h_SF = h_MC->Clone();
  h_SF->Sumw2();
  h_SF->Reset();
  h_SF->Divide(h_Data, h_MC);

  TF1* functionpt = new TF1("functionpt", "pol2");
  functionpt->SetLineColor(2);
  h_SF->Fit(functionpt);
  h_SF->SetMinimum(0.0);
  h_SF->SetMaximum(3.5);
  h_SF->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_SF->GetYaxis()->SetTitle("Scale Factor (Data/MC)");
  h_SF->SetStats(0);
  h_SF->SetLineColor(4);
  h_SF->SetLineWidth(2);
  h_SF->Draw("H");
  TH1F* functionpt_err = (TH1F*) h_SF->Clone();
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(functionpt_err,0.68);
  functionpt_err->SetFillColor(2);
  functionpt_err->SetFillStyle(3005);
  functionpt_err->SetStats(0);
  functionpt_err->Draw("e3 same");
  c_pt_SF->Print(path+"/c_pt_SF.eps");
  

}
