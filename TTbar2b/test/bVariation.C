void bVariation(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TH1* h = bHist("TTBB_01Sep2012_CSVT_addb");
  TH1* h_up = bHist("TTBB_01Sep2012_CSVTup_addb");
  TH1* h_dw = bHist("TTBB_01Sep2012_CSVTdw_addb");

  double s = h->Integral();
  double s_up = h_up->Integral();
  double s_dw = h_dw->Integral();

  h->Scale(1.0/s);
  h_up->Scale(1.0/s_up);
  h_dw->Scale(1.0/s_dw);

  TCanvas * c = new TCanvas("c","c",1);
  c->SetLogy();
  h->SetTitle("");
  h->GetXaxis()->SetTitle("b-Jet Multiplicity");
  h->GetYaxis()->SetTitle("Normalized Entries");
  h_up->SetLineColor(4);
  h_dw->SetLineColor(2);
  h->Draw();
  h_up->Draw("same");
  h_dw->Draw("same");


  for(int i=1; i <= 5 ;i++){
    double central = h->GetBinContent(i);
    double up = h_up->GetBinContent(i);
    double dw = h_dw->GetBinContent(i);
    double r_up = (up-central)/central;
    double r_dw = (dw-central)/central;
    cout << "bin= " << i << " : up= " << r_up << " , dw= " << r_dw << endl;
  }

  TLegend *l = new TLegend(0.78,0.76,0.89,0.88);
  l->AddEntry(h_up,"b SF up","L");
  l->AddEntry(h,   "b SF","L");
  l->AddEntry(h_dw,"b SF dw","L");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();

  c->Print("bVariation_CSVT.eps");
}

TH1* bHist(const TString & path){

  TFile * f_MuMu = new TFile(path+"/MuMu/MuMu.root");
  TFile * f_MuEl = new TFile(path+"/MuEl/MuEl.root");
  TFile * f_ElEl = new TFile(path+"/ElEl/ElEl.root");

  TH1* h_ttbb_MuMu = (TH1*) f_MuMu->Get("Step_4/hMCSig_TTbarbb_Step_4_nbJet30_CSVT");
  TH1* h_ttbb_MuEl = (TH1*) f_MuEl->Get("Step_4/hMCSig_TTbarbb_Step_4_nbJet30_CSVT");
  TH1* h_ttbb_ElEl = (TH1*) f_ElEl->Get("Step_4/hMCSig_TTbarbb_Step_4_nbJet30_CSVT");

  TH1* h_ttbb = new TH1F("h_ttbb","h_ttbb",5,0,5);

  h_ttbb->Add(h_ttbb_MuMu);
  h_ttbb->Add(h_ttbb_MuEl);
  h_ttbb->Add(h_ttbb_ElEl);

  return h_ttbb;  

}
