#include "tdrstyle.C"
TFile* fEE, * fME, * fMM;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlots(TString noteNumber = "AN-11-076")
{
  if ( noteNumber == "AN-11-076") makePlots_AN_11_076();
}

void makePlots_AN_11_076()
{
  setTDRStyle();

  fEE = TFile::Open("/data/cmskr-top/common/Top/finalHisto/v0/ElEl.root");
  fME = TFile::Open("/data/cmskr-top/common/Top/finalHisto/v0/MuEl.root");
  fMM = TFile::Open("/data/cmskr-top/common/Top/finalHisto/v0/MuMu.root");

  if ( !fEE || !fME || !fMM ) return;

  cutStepPlots("Step_3", "ZMass", "Z mass", 0.1, 1e6, true);
  cutStepPlots("Step_6", "nJet", "Jet multiplicity", 0.1, 1e6, true);
}

// Function to draw EE, ME, MM channel and all channel merged plot
void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY)
{
  TH1F* hDataEE = (TH1F*)fEE->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataME = (TH1F*)fME->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataMM = (TH1F*)fMM->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));

  if ( !hDataEE || !hDataME || !hDataMM ) { cout << "No data hist\n"; return; }

  TH1F* hDataLL = (TH1F*)hDataEE->Clone(Form("hData_%s_%s", cutStep, histName));
  hDataLL->Reset();
  hDataLL->Add(hDataEE);
  hDataLL->Add(hDataME);
  hDataLL->Add(hDataMM);

  THStack* hStackEE = new THStack(TString("hEE_")+cutStep+"_"+histName, histTitle);
  THStack* hStackME = new THStack(TString("hME_")+cutStep+"_"+histName, histTitle);
  THStack* hStackMM = new THStack(TString("hMM_")+cutStep+"_"+histName, histTitle);
  THStack* hStackLL = new THStack(TString("hLL_")+cutStep+"_"+histName, histTitle);

  TH1F* hSigEE = (TH1F*)fEE->Get(Form("%s/hMCSig_TTbar_%s_%s", cutStep, cutStep, histName));
  TH1F* hSigME = (TH1F*)fME->Get(Form("%s/hMCSig_TTbar_%s_%s", cutStep, cutStep, histName));
  TH1F* hSigMM = (TH1F*)fMM->Get(Form("%s/hMCSig_TTbar_%s_%s", cutStep, cutStep, histName));

  if ( !hSigEE || !hSigME || !hSigMM ) { cout << "No signal hist\n"; return; }

  TH1F* hSigLL = (TH1F*)hSigEE->Clone(Form("hMCSig_TTbar_%s_%s", cutStep, histName));
  hSigLL->Reset();
  hSigLL->Add(hSigEE);
  hSigLL->Add(hSigME);
  hSigLL->Add(hSigMM);

  hStackEE->Add(hSigEE);
  hStackME->Add(hSigME);
  hStackMM->Add(hSigMM);
  hStackLL->Add(hSigLL);

  const int nBkg = 5;
  const char* bkgNames[nBkg] = {"Wl", "VV", "SingleTop", "DYtt", "DYll"};
  const char* bkgLabels[nBkg] = {
    "W #rightarrow l#nu", "Dibosons", "Single top",
    "Z/#gamma* #rightarrow #tau#tau", "Z/#gamma* #rightarrow ll"
  };

  // Build legends
  TLegend* legEE = buildLegend();
  TLegend* legME = buildLegend();
  TLegend* legMM = buildLegend();
  TLegend* legLL = buildLegend();

  if ( hDataEE->GetEntries() > 0 ) legEE->AddEntry(hDataEE, "Data", "p");
  if ( hDataME->GetEntries() > 0 ) legME->AddEntry(hDataME, "Data", "p");
  if ( hDataMM->GetEntries() > 0 ) legMM->AddEntry(hDataMM, "Data", "p");
  if ( hDataLL->GetEntries() > 0 ) legLL->AddEntry(hDataLL, "Data", "p");

  TH1F* hEEs[nBkg];
  TH1F* hMEs[nBkg];
  TH1F* hMMs[nBkg];
  TH1F* hLLs[nBkg];

  for ( int i=0; i<nBkg; ++i )
  {
    TH1F* hEE = (TH1F*)fEE->Get(Form("%s/hMC_%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hME = (TH1F*)fME->Get(Form("%s/hMC_%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hMM = (TH1F*)fMM->Get(Form("%s/hMC_%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));

    if ( !hEE || !hME || !hMM ) { cout << "No bkg hist " << bkgNames[i] << endl; continue; }

    TH1F* hLL = (TH1F*)hEE->Clone(Form("hMC_%s_%s_%s", bkgNames[i], cutStep, histName));
    hLL->Reset();
    hLL->Add(hEE);
    hLL->Add(hME);
    hLL->Add(hMM);

    hEEs[i] = hEE;
    hMEs[i] = hME;
    hMMs[i] = hMM;
    hLLs[i] = hLL;

    hStackEE->Add(hEE);
    hStackME->Add(hME);
    hStackMM->Add(hMM);
    hStackLL->Add(hLL);
  }

  for ( int i=nBkg-1; i>=0; --i )
  {
    legEE->AddEntry(hEEs[i], bkgLabels[i], "f");
    legME->AddEntry(hMEs[i], bkgLabels[i], "f");
    legMM->AddEntry(hMMs[i], bkgLabels[i], "f");
    legLL->AddEntry(hLLs[i], bkgLabels[i], "f");
  }

  legEE->AddEntry(hSigEE, "t#bar{t}", "f");
  legME->AddEntry(hSigME, "t#bar{t}", "f");
  legMM->AddEntry(hSigMM, "t#bar{t}", "f");
  legLL->AddEntry(hSigLL, "t#bar{t}", "f");

  // Be ready for draw
  hDataEE->SetMinimum(minY);
  hDataME->SetMinimum(minY);
  hDataMM->SetMinimum(minY);
  hDataLL->SetMinimum(minY);

  hDataEE->SetMaximum(maxY);
  hDataME->SetMaximum(maxY);
  hDataMM->SetMaximum(maxY);
  hDataLL->SetMaximum(maxY);

  TCanvas* cEE = new TCanvas(TString("cEE_")+cutStep+"_"+histName, TString("cEE_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cEE->SetLogy();
  hDataEE->Draw();
  legEE->Draw();
  getHeader(35.9, "ee channel")->Draw();
  hStackEE->Draw("same");
  hDataEE->Draw("same");
  hDataEE->Draw("sameaxis");
  cEE->Print(Form("cEE_%s_%s.eps", cutStep, histName));

  TCanvas* cME = new TCanvas(TString("cME_")+cutStep+"_"+histName, TString("cME_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cME->SetLogy();
  hDataME->Draw();
  legME->Draw();
  getHeader(35.9, "#mue channel")->Draw();
  hStackME->Draw("same");
  hDataME->Draw("same");
  hDataME->Draw("sameaxis");
  cME->Print(Form("cME_%s_%s.eps", cutStep, histName));

  TCanvas* cMM = new TCanvas(TString("cMM_")+cutStep+"_"+histName, TString("cMM_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cMM->SetLogy();
  hDataMM->Draw();
  legMM->Draw();
  getHeader(35.9, "#mu#mu channel")->Draw();
  hStackMM->Draw("same");
  hDataMM->Draw("same");
  hDataMM->Draw("sameaxis");
  cMM->Print(Form("cMM_%s_%s.eps", cutStep, histName));

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  hDataLL->Draw();
  legLL->Draw();
  getHeader(35.9, "All channel")->Draw();
  hStackLL->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");
  cLL->Print(Form("cLL_%s_%s.eps", cutStep, histName));

}

TLegend* buildLegend()
{
  TLegend* leg = new TLegend(0.73,0.57,0.85,0.90,NULL,"brNDC");

  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  return leg;
}

TPaveText* getHeader(double lumi, TString channelName)
{
  TPaveText* pt = new TPaveText(0.18,0.75,0.18,0.90,"brNDC");

  pt->SetBorderSize(1);
  pt->SetTextFont(42);
  pt->SetTextSize(0.04);
  pt->SetLineColor(0);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->SetTextAlign(12);
  pt->AddText("CMS Preliminary");
  pt->AddText(Form("%.1f pb^{-1} at  #sqrt{s} = 7 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}
