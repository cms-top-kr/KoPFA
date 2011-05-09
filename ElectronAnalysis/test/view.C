void view(TString treeName = "HZZVeryLoose/tree")
{
  TFile* f = TFile::Open("analyzeEleId.root");

  TTree* tree = (TTree*)f->Get(treeName);

  TH1F* hGenPt = new TH1F("hGenPt", "hPt;p_{T} (GeV/c);Entries", 20, 0, 100);
  TH1F* hGsfPt = new TH1F("hGsfPt", "hPt;p_{T} (GeV/c);Entries", 20, 0, 100);
  TH1F* hPfaPt = new TH1F("hPfaPt", "hPt;p_{T} (GeV/c);Entries", 20, 0, 100);

  TH1F* hGenEta = new TH1F("hGenEta", "hEta;#eta;Entries", 20, -3.15, 3.15);
  TH1F* hGsfEta = new TH1F("hGsfEta", "hEta;#eta;Entries", 20, -3.15, 3.15);
  TH1F* hPfaEta = new TH1F("hPfaEta", "hEta;#eta;Entries", 20, -3.15, 3.15);

  TH1F* hGenPhi = new TH1F("hGenPhi", "hPhi;#phi;Entries", 20, -3.15, 3.15);
  TH1F* hGsfPhi = new TH1F("hGsfPhi", "hPhi;#phi;Entries", 20, -3.15, 3.15);
  TH1F* hPfaPhi = new TH1F("hPfaPhi", "hPhi;#phi;Entries", 20, -3.15, 3.15);

  TH1F* hGsfPtRes = new TH1F("hGsfPtRes", "hPtRes;#Deltap_{T}/p_{T}^{Gen};Entries", 20, -5, 5);
  TH1F* hPfaPtRes = new TH1F("hPfaPtRes", "hPtRes;#Deltap_{T}/p_{T}^{Gen};Entries", 20, -5, 5);

  hGenPt->SetLineColor(kBlack);
  hGsfPt->SetLineColor(kRed);
  hPfaPt->SetLineColor(kBlue);

  hGenEta->SetLineColor(kBlack);
  hGsfEta->SetLineColor(kRed);
  hPfaEta->SetLineColor(kBlue);

  hGenPhi->SetLineColor(kBlack);
  hGsfPhi->SetLineColor(kRed);
  hPfaPhi->SetLineColor(kBlue);

  hGsfPtRes->SetLineColor(kRed);
  hPfaPtRes->SetLineColor(kBlue);

  hGenEta->SetLineColor(kBlack);
  hGsfEta->SetLineColor(kRed);
  hPfaEta->SetLineColor(kBlue);

  hGenPt->SetMinimum(0);
  hGenEta->SetMinimum(0);
  hGenPhi->SetMinimum(0);
  hGsfPtRes->SetMinimum(0);

  tree->Project("hGenPt", "genElePt");
  tree->Project("hGsfPt", "gsfElePt");
  tree->Project("hPfaPt", "pfaElePt", "pfaElePt>10");

  tree->Project("hGenEta", "genEleEta");
  tree->Project("hGsfEta", "gsfEleEta");
  tree->Project("hPfaEta", "pfaEleEta", "pfaElePt>10");

  tree->Project("hGenPhi", "genElePhi");
  tree->Project("hGsfPhi", "gsfElePhi");
  tree->Project("hPfaPhi", "pfaElePhi", "pfaElePt>10");

  tree->Project("hGsfPtRes", "(gsfElePt-genElePt)/genElePt");
  tree->Project("hPfaPtRes", "(pfaElePt-genElePt)/genElePt", "pfaElePt>10");

  TCanvas* c = 0;

  c = new TCanvas("cPt", "cPt", 600, 600);
  hGenPt->Draw();
  hGsfPt->Draw("sames");
  hPfaPt->Draw("sames");
  c->Print("cPt.png");

  c = new TCanvas("cEta", "cEta", 600, 600);
  hGenEta->Draw();
  hGsfEta->Draw("sames");
  hPfaEta->Draw("sames");
  c->Print("cEta.png");

  c = new TCanvas("cPhi", "cPhi", 600, 600);
  hGenPhi->Draw();
  hGsfPhi->Draw("sames");
  hPfaPhi->Draw("sames");
  c->Print("cPhi.png");

  c = new TCanvas("cRes", "cRes", 600, 600);
  hGsfPtRes->Draw();
  hPfaPtRes->Draw("sames");
  c->Print("cRes.png");
  

}


