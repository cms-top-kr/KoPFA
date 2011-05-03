void plotElectron(){
  TFile * fhisto = new TFile("analyzeEleId_default.root");

  TH1F * h_gsf_pt = (TH1F *) fhisto->Get("e/h_gsf_pt");
  TH1F * h_gsf_eta = (TH1F *) fhisto->Get("e/h_gsf_eta");
  TH1F * h_gsf_mva = (TH1F *) fhisto->Get("e/h_gsf_mva");
  
  TH1F * h_pf_pt = (TH1F *) fhisto->Get("e/h_pf_pt");
  TH1F * h_pf_eta = (TH1F *) fhisto->Get("e/h_pf_eta");
  TH1F * h_pf_mva = (TH1F *) fhisto->Get("e/h_pf_mva");

  makePlot(h_gsf_pt,h_pf_pt,200, "Events", "p_{T} (GeV)","pt");
  makePlot(h_gsf_eta,h_pf_eta,100, "Events", "#eta", "eta");
  makePlot(h_gsf_mva,h_pf_mva,700, "Events", "mva", "mva");

}

void makePlot(TH1F * h1, TH1F * h2, int max, TString & ytitle, TString & xtitle, TString &name){
  TCanvas * c = new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  h1->SetTitle("");
  h1->SetStats(0);
  h1->SetMaximum(max);
  h1->GetYaxis()->SetTitle(ytitle);
  h1->GetXaxis()->SetTitle(xtitle);
  h1->Draw();
  h2->SetLineColor(2);
  h2->Draw("same");
  double c1 = h1->GetEntries();
  double c2 = h2->GetEntries();

  TLegend *l= new TLegend(0.6,0.7,0.9,0.85);
  l->AddEntry(h1,Form("gsf=%1.0f",c1),"L");
  l->AddEntry(h2,Form("pf=%1.0f",c2),"L");
  l->SetTextSize(0.05);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print(Form("c_%s.png",name.Data()));
} 
