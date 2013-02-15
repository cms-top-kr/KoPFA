void bVariation(int ii, int jj){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TString samples[2] = {"hMC_TTbarll","hMCSig_TTbarbb"};
  TString histNames[2] = {"jet30bDiscriminator1b","nbJet30_CSVT"};
  TString xtitles[2] = {"CSV distriminator","b-Jet Multiplicity (CSVT)"};

  TString sample = samples[ii];
  TString histName = histNames[jj];
  TString xtitle = xtitles[jj];  

  TString histN =Form("Step_5/%s_Step_5_%s",sample.Data(),histName.Data());


  TH1* h = bHist("csvt/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVT", histN);
  TH1* h_up = bHist("csvt2/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTuplight", histN);
  TH1* h_dw = bHist("csvt2/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTdwlight", histN);

  double s = h->Integral();
  double s_up = h_up->Integral();
  double s_dw = h_dw->Integral();

  h->Scale(1.0/s);
  h_up->Scale(1.0/s_up);
  h_dw->Scale(1.0/s_dw);

  TCanvas * c = new TCanvas("c","c",1);
//  c->SetLogy();
  h->SetTitle("");
  h->GetXaxis()->SetTitle(xtitle.Data());
  h->GetYaxis()->SetTitle("Normalized Entries");
  h_up->SetLineColor(4);
  h_dw->SetLineColor(2);

    double ymax = h->GetMaximum(); 
    if(ymax< h_up->GetMaximum()) ymax=h_up->GetMaximum();
    if(ymax< h_dw->GetMaximum()) ymax=h_dw->GetMaximum();
    
    ymax=ymax*1.5; // for linear
    //ymax=ymax*100; // for logy

    h->SetMaximum(ymax);

  h->Draw();
  h_up->Draw("same");
  h_dw->Draw("same");


  for(int i=1; i <= h->GetNbinsX() ;i++){
    double central = h->GetBinContent(i);
    double up = h_up->GetBinContent(i);
    double dw = h_dw->GetBinContent(i);
    double r_up = (up-central)/central;
    double r_dw = (dw-central)/central;
    cout << "bin= " << i << " : up= " << r_up << " , dw= " << r_dw << endl;
  }

  TLegend *l = new TLegend(0.78,0.76,0.89,0.88);
  l->AddEntry(h_up,"l SF up","L");
  l->AddEntry(h,   "l SF","L");
  l->AddEntry(h_dw,"l SF dw","L");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();

  c->Print(Form("bVariation_CSVT_%s_%s.eps",sample.Data(), histName.Data()));

}

TH1* bHist(const TString & path, TString & name){

  TFile * f_MuMu = new TFile(path+"/MuMu/MuMu.root");
  TFile * f_MuEl = new TFile(path+"/MuEl/MuEl.root");
  TFile * f_ElEl = new TFile(path+"/ElEl/ElEl.root");

  TH1* h_ttbb_MuMu = (TH1*) f_MuMu->Get(name.Data());
  TH1* h_ttbb_MuEl = (TH1*) f_MuEl->Get(name.Data());
  TH1* h_ttbb_ElEl = (TH1*) f_ElEl->Get(name.Data());

  TH1* h_ttbb = new TH1F("h_ttbb","h_ttbb",h_ttbb_MuMu->GetNbinsX(),h_ttbb_MuMu->GetXaxis()->GetXmin() ,h_ttbb_MuMu->GetXaxis()->GetXmax() );

  h_ttbb->Add(h_ttbb_MuMu);
  h_ttbb->Add(h_ttbb_MuEl);
  h_ttbb->Add(h_ttbb_ElEl);

  return h_ttbb;  

}
