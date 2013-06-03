#include <iostream>
#include <iomanip>

TFile* f;
TString outDirName = ".";

const int nBkg = 8;
const char* bkgNames[]  = {"hMCSig_TTbar", "hMC_Wl",             "hMC_VV",   "hMC_SingleTop", "hMC_DYb",       "hMC_DYc", "hMC_DYLF", "hDataBkg_QCD"};
const char* bkgLabels[] = {"t#bar{t}",     "W #rightarrow l#nu", "Dibosons", "Single top",    "Z/#gamma* + b", "Z/#gamma* + c", "Z/#gamma* +LF", "QCD" };
const Color_t color[]   = { kRed+2,       kGreen-3,              kGray+4,    kMagenta,       kAzure+7,        kAzure,        kAzure-2                   ,kYellow };
const int     style[]   = { 1001,          1001,                  1001,       1001,           1001,            1001,          1001,          1001 };
int nExclude = 1;
const char* Exclude[] = { "hDataBkg_QCD" }

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend(double y);
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlotsCSVWeight(TString noteNumber = "TTBB_03June2013_CSVWeight/v1")
{

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TString path = "TTBB_03June2013_CSVWeight";

  f = TFile::Open(path+"/merged.root");

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);

  cutStepPlots("ZSel", "ZMass", "M_{ll} Invariant Mass (GeV)", "Events", "M_{ll} Invariant Mass (GeV)", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "ZMass", "M_{ll} Invariant Mass (GeV)", "Events", "M_{ll} Invariant Mass (GeV)", "LL", 1, 70000000, true, "log");


  cutStepPlots("ZSel", "jet1_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 500000, false);
  cutStepPlots("ZSel", "jet2_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "jet1_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 70000000, true, "log");

  cutStepPlots("ZSel", "jet1pt_bDisCSV", "First Additional Jet p_{T} (GeV)", "Events/10 GeV", "First Additional Jet p_{T} (GeV)", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "jet2pt_bDisCSV", "Second Additional Jet p_{T} (GeV)", "Events/10 GeV", "Second Additional Jet p_{T} (GeV)", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "jet1pt_bDisCSV", "First Additional Jet p_{T} (GeV)", "Events/10 GeV", "First Additional Jet p_{T} (GeV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2pt_bDisCSV", "Second Additional Jet p_{T} (GeV)", "Events/10 GeV", "Second Additional Jet p_{T} (GeV)", "LL", 1, 40000000, true, "log");

  cutStepPlots("ZSel", "jet1eta_bDisCSV", "First Additional Jet #eta", "Events", "First Additional Jet #eta", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "jet2eta_bDisCSV", "Second Additional Jet #eta", "Events", "Second Additional Jet #eta", "LL", 1, 700000, false);
  cutStepPlots("ZSel", "jet1eta_bDisCSV", "First Additional Jet #eta", "Events", "First Additional Jet #eta", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2eta_bDisCSV", "Second Additional Jet #eta", "Events", "Second Additional Jet #eta", "LL", 1, 40000000, true, "log");

  cutStepPlots("ZSel", "jet1_bDisCSV_30_35", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2_bDisCSV_30_35", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 70000000, true, "log");

  cutStepPlots("ZSel", "jet1_bDisCSV_35_40", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2_bDisCSV_35_40", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 70000000, true, "log");

  cutStepPlots("ZSel", "jet1_bDisCSV_40_50", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2_bDisCSV_40_50", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 70000000, true, "log");

  cutStepPlots("ZSel", "jet1_bDisCSV_50", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 400000000, true, "log");
  cutStepPlots("ZSel", "jet2_bDisCSV_50", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 1, 70000000, true, "log");


}

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle, const TString & ytitle, const TString & xtitle, const TString & decayMode, 
                  double minY, double maxY, bool doLogY, const TString & postfix = "")
{
  TString channelName = "All";
  if( decayMode == "MM") channelName = "#mu#mu";
  if( decayMode == "EE") channelName = "ee";
  if( decayMode == "ME") channelName = "e#mu";
  
  TH1F* hData = (TH1F*)f->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  if ( !hData ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << "\n"; return; }

  THStack* hStack = new THStack(TString("h_")+cutStep+"_"+histName, histTitle);

  TLegend* leg = buildLegend( (double) nExclude*0.02 );

  if ( hData->GetEntries() > 0 ) leg->AddEntry(hData, "Data", "p");

  TH1F* hs[nBkg];
 
  for ( int i=0; i<nBkg; ++i )
  {
    TH1F* h = (TH1F*)f->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    hs[i] = h;
    h->SetFillColor(color[i]);
    h->SetFillStyle(style[i]);

    ///remove indicated backgrounds
    bool exclude = false;
    for(int k = 0 ; k < nExclude ; k++) {
      if( bkgNames[i] == Exclude[k] ) exclude = true;
    }
    if( exclude ) continue;

    hStack->Add(h);
  }

  for ( int i=nBkg-1; i>=0; --i )
  {
    ///remove indicated backgrounds
    bool exclude = false;
    for(int k = 0 ; k < nExclude ; k++) {
      if( bkgNames[i] == Exclude[k] ) exclude = true;
    }
    if( exclude ) continue;

    leg->AddEntry(hs[i], bkgLabels[i], "f");
  }


  // Be ready for draw
  hData->SetMinimum(minY);
  hData->SetMaximum(maxY*0.25);

  TCanvas* c = new TCanvas(Form("c%s_%s_%s%s", decayMode.Data(), cutStep , histName, postfix.Data() ), Form("c%s_%s_%s%s", decayMode.Data(), cutStep , histName, postfix.Data()), 1);
  if ( doLogY ) c->SetLogy();
  hData->Draw();
  hData->GetXaxis()->SetTitle(xtitle);
  hData->GetYaxis()->SetTitle(ytitle);
  leg->Draw();
  getHeader(19.6, Form("%s channel",channelName.Data()))->Draw();
  hStack->Draw("same");
  hData->Draw("same");
  hData->Draw("sameaxis");
  c->Print(Form("%s/c%s_%s_%s%s.eps", outDirName.Data(), decayMode.Data(), cutStep, histName, postfix.Data() ));
  c->Print(Form("%s/c%s_%s_%s%s.pdf", outDirName.Data(), decayMode.Data(), cutStep, histName, postfix.Data() ));

}

TLegend* buildLegend(double y)
{
  TLegend* leg = new TLegend(0.73,0.55+y,0.85,0.88,NULL,"brNDC");

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
  TPaveText* pt = new TPaveText(0.18,0.75,0.18,0.88,"brNDC");

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
  pt->AddText(Form("%.1f fb^{-1} at  #sqrt{s} = 8 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}
