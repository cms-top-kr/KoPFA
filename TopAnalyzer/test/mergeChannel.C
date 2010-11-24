void merge (TString filename, TString step, TString histotype, Int_t hscale=10)
{

  TFile *_file0 = TFile::Open(filename);

  const int n = 6;

  TString hist = TString(step) + TString("_") + TString(histotype);
  TString data = TString("hData_Step_") + TString(hist);
  TString mc[n];
  mc[0] = TString("hMC_TTbar_Step_") + TString(hist);
  mc[1] = TString("hMC_Wl_Step_") + TString(hist);
  mc[2] = TString("hMC_VV_Step_") + TString(hist);
  mc[3] = TString("hMC_SingleTop_Step_") + TString(hist);
  mc[4] = TString("hMC_DYtt_Step_") + TString(hist);
  mc[5] = TString("hMC_DYll_Step_") + TString(hist);

  TH1F* hdata = (TH1F*)(gROOT->FindObject(data));
  hdata->GetXaxis()->SetTitleOffset(0.8);
  hdata->GetYaxis()->SetTitleOffset(0.8);

  TH1F* hmc[n];
  for(int i=0; i<n; i++) {
    cout << mc[i] << endl;
    hmc[i] = (TH1F*)(gROOT->FindObject(mc[i]));
    hmc[i]->SetTitle("");
    hmc[i]->GetXaxis()->SetTitleOffset(1.2);
    hmc[i]->GetYaxis()->SetTitleOffset(1.2);
    hmc[i]->SetStats(0);
  }

  THStack *stack = new THStack("stack","stack");
  for(int i=0; i<n; i++) {
    stack->Add(hmc[i]);
  }

  TCanvas *c1 = new TCanvas("c1","c1",0,0,700,500);
  c1->Divide(2,3);
  for(int i=0; i<n; i++) {
    c1->cd(i+1); hmc[i]->Draw();
  }

  TCanvas *c2 = new TCanvas("c2","c2",100,100,700,500);
  hdata->Draw();
  stack->Draw("same");
  hdata->Draw("same");
  //hdata->SetTitle("");

  Int_t hmax = hdata->GetMaximum();
  hdata->SetMaximum(hscale*hmax);
  hdata->SetMinimum(0.02);

  gPad->SetLogy();

  //c2->BuildLegend();
}
