void plot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"same");

  h_1->Scale(1.0/h_1->Integral());
  h_2->Scale(1.0/h_2->Integral());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  StyleSimple(h_1, h_2, ytitle,xtitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

void normalized2Eventplot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"same");

  h_1->Scale(1.0/tree1->GetEntries());
  h_2->Scale(1.0/tree2->GetEntries());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  StyleSimple(h_1, h_2, ytitle,xtitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

void normalized2EventIsoplot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"psame");

  h_1->Scale(1.0/tree1->GetEntries());
  h_2->Scale(1.0/tree2->GetEntries());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  Style(h_1, h_2, xtitle, ytitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "p", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

void plotFromHist(TFile * file1, TFile * file2, const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, double max, bool print){
  TH1F * h_1 = (TH1F *) file1->Get(Form("DiMuon/h_%s",hName.Data()));
  TH1F * h_2 = (TH1F *) file2->Get(Form("DiMuon/h_%s",hName.Data()));

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  h_1->Draw();
  h_2->Draw("same");

  h_1->Scale(1.0/h_1->Integral());
  h_2->Scale(1.0/h_2->Integral());

  StyleSimple(h_1, h_2, "Jet Multiplicity","Normalized Entries");
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);
}

