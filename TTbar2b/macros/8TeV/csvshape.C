void csvshape(){

  TFile * f = new TFile("TTBB_12June2013_FinalPlots/LL.root");
 
  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  plot(f, "addjet1");
  plot(f, "addjet2");

}

void plot(TFile* f, const TString & variable){

  TH1F * h_ttbb = (TH1F*) f->Get(Form("Step_5/hMCSig_TTbarbb_Step_5_%s_bDisCSV_rebin2_tthweight", variable.Data()));
  TH1F * h_ttcc = (TH1F*) f->Get(Form("Step_5/hMC_TTbarcc_Step_5_%s_bDisCSV_rebin2_tthweight", variable.Data()));
  TH1F * h_ttll = (TH1F*) f->Get(Form("Step_5/hMC_TTbarll_Step_5_%s_bDisCSV_rebin2_tthweight", variable.Data()));

  cout << "canvas" << endl;
  TCanvas * c = new TCanvas(Form("c_%s",variable.Data()),Form("c_%s",variable.Data()),600,600);

  double N_ttbb = h_ttbb->Integral();
  double N_ttcc = h_ttcc->Integral();
  double N_ttll = h_ttll->Integral();

  cout << "N_ttbb= " << N_ttbb << " N_ttcc= " << N_ttcc << " N_ttll= " << N_ttll << endl;

  h_ttbb->Scale(1.0/N_ttbb);
  h_ttcc->Scale(1.0/N_ttcc);
  h_ttll->Scale(1.0/N_ttll);

  h_ttll->SetTitle("");
  h_ttll->SetStats(0);
  h_ttll->SetMaximum(0.65);
  h_ttll->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_ttll->GetYaxis()->SetTitle("Normalized entries");

  h_ttll->SetLineColor(4);
  h_ttbb->SetLineColor(2);
  h_ttcc->SetLineColor(3);
  h_ttll->SetFillColor(0);
  h_ttbb->SetFillColor(0);
  h_ttcc->SetFillColor(0);


  h_ttll->SetLineWidth(2);
  h_ttbb->SetLineWidth(2);
  h_ttcc->SetLineWidth(2);

  h_ttll->Draw("HIST");
  h_ttbb->Draw("HISTsame");
  h_ttcc->Draw("HISTsame");

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.25,0.82,"CMS Simulation, at #sqrt{s} = 8 TeV");

  TLegend *l = new TLegend(0.78,0.65,0.88,0.80);
  l->AddEntry(h_ttbb,"tt + bb","L");
  l->AddEntry(h_ttcc,"tt + cc","L");
  l->AddEntry(h_ttll,"tt + LF","L");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();

  c->Print(Form("csvshape_%s.eps",variable.Data()));

}
