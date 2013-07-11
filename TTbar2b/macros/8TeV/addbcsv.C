void addbcsv(){

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TFile * f = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130612_genjet/vallot_TTbarFullLepMGDecays.root");
  TTree * t = (TTree*) f->Get("MuEl/tree");
  
  TH1F * h_bfromtop =  new TH1F("h_bfromtop","h_bfromtop",20,0,1);
  TH1F * h_bnotfromtop =  new TH1F("h_bnotfromtop","h_bnotfromtop",20,0,1);

  t->Project("h_bfromtop","jets_bDiscriminatorCSV","jets_fromtop == 1 && abs(jets_flavor) == 5");
  t->Project("h_bnotfromtop","jets_bDiscriminatorCSV","jets_fromtop == 0 && abs(jets_flavor) == 5");

  h_bfromtop->Scale(1.0/h_bfromtop->Integral());
  h_bnotfromtop->Scale(1.0/h_bnotfromtop->Integral());

  TCanvas * c = new TCanvas("c","c",1);

  h_bfromtop->Draw();
  h_bfromtop->SetStats(0);
  h_bfromtop->SetTitle("");
  h_bfromtop->SetLineColor(2);
  h_bfromtop->SetLineWidth(2);
  h_bnotfromtop->Draw("same");
  h_bnotfromtop->SetLineColor(4);
  h_bnotfromtop->SetLineWidth(2);

  TLegend *l = new TLegend(0.48,0.65,0.58,0.80);
  l->AddEntry(h_bfromtop,"b from top","L");
  l->AddEntry(h_bnotfromtop,"b not from top","L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.20,0.82,"CMS Simulation, at #sqrt{s} = 8 TeV");

  c->Print("csvshape_addb.eps");
}

