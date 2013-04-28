#include <iostream>
#include <iomanip>

TFile* f;
TString outDirName = ".";

const int nBkg = 9;
const char* bkgNames[]  = {"hMCSig_TTbarbb", "hMC_TTbarcc", "hMC_TTbarll","hMC_TTbarOthers", "hMC_Wl",             "hMC_VV",   "hMC_SingleTop", "hMC_DYll", "hDataBkg_QCD"};
const char* bkgLabels[] = {"t#bar{t}+bb",    "t#bar{t}+cc", "t#bar{t}+ll","t#bar{t} others", "W #rightarrow l#nu", "Dibosons", "Single top",    "Z/#gamma* #rightarrow ll", "QCD" };
const Color_t color[]   = { kBlue+2,         kOrange+2,      kRed,        kRed-7,            kGreen-3,              kGray+4,    kMagenta,       kAzure-2                   ,kYellow };
const int     style[]   = { 3354,            1001,           1001,        1001,              1001,                  1001,       1001,           1001,                      1001 };
int nExclude = 3;
const char* Exclude[] = { "hMC_Wl", "hMC_VV", "hDataBkg_QCD" }

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbarbb"};
const char* sigLabels[] = {"t#bar{t}+bb"};
const Color_t color_sig[] = {kBlue+2};
const int style_sig[] = {3354};
bool stackSig = true;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend( double y);
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlots(TString noteNumber = "TTBB_27Apr2013/v1")
{

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  TString path = "TTBB_27Apr2013";

  f = TFile::Open(path+"/merged.root");

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);

  nExclude = 0;
  cutStepPlots("Step_1", "ZMass", "Dilepton mass" ," Events/5 GeV/c^{2}", "Dilepton Mass (GeV/c^{2})", "LL", 0.1, 50000000, false);
  cutStepPlots("Step_1", "ZMass", "Dilepton mass" ," Events/5 GeV/c^{2}", "Dilepton Mass (GeV/c^{2})", "LL", 0.1, 4000000000, true, "log");

  cutStepPlots("Step_3", "nJet", "Jet Multiplicity", "Events", "Jet Multiplicity", "LL", 0.1, 2000000, false);
  cutStepPlots("Step_3", "nJet", "Jet Multiplicity", "Events", "Jet Multiplicity", "LL", 0.1, 100000000, true, "log");

  nExclude = 3;
  cutStepPlots("Step_4", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", "Events", "b-Jet Multiplicity (CSVT)", "LL", 0.1, 40000, false);
  cutStepPlots("Step_4", "nbJet30_CSVM", "b-Jet Multiplicity (CSVM)", "Events", "b-Jet Multiplicity (CSVM)", "LL", 0.1, 40000, false);
  cutStepPlots("Step_4", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", "Events", "b-Jet Multiplicity (CSVT)", "LL", 0.1, 400000, true, "log");
  cutStepPlots("Step_4", "nbJet30_CSVM", "b-Jet Multiplicity (CSVM)", "Events", "b-Jet Multiplicity (CSVM)", "LL", 0.1, 400000, true, "log");

  cutStepPlots("Step_5", "addjet1_bDisCSVnoweight", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 2000, false);
  cutStepPlots("Step_5", "addjet2_bDisCSVnoweight", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 4000, false);
  cutStepPlots("Step_5", "addjet1_bDisCSVnoweight", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 400000, true, "log");
  cutStepPlots("Step_5", "addjet2_bDisCSVnoweight", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 70000, true, "log");

  cutStepPlots("Step_5", "addjet1_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 2000, false);
  cutStepPlots("Step_5", "addjet2_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 4000, false);
  cutStepPlots("Step_5", "addjet1_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 400000, true, "log");
  cutStepPlots("Step_5", "addjet2_bDisCSV", "b-Discriminator (CSV)", "Events/0.05", "b-Discriminator (CSV)", "LL", 0.1, 70000, true, "log");

  cutStepPlots("Step_5", "addjet1_bDisCSV_rebin", "b-Discriminator (CSV)", "Events", "b-Discriminator (CSV)", "LL", 0.1, 2000, false);
  cutStepPlots("Step_5", "addjet2_bDisCSV_rebin", "b-Discriminator (CSV)", "Events", "b-Discriminator (CSV)", "LL", 0.1, 4000, false);
  cutStepPlots("Step_5", "addjet1_bDisCSV_rebin", "b-Discriminator (CSV)", "Events", "b-Discriminator (CSV)", "LL", 0.1, 400000, true, "log");
  cutStepPlots("Step_5", "addjet2_bDisCSV_rebin", "b-Discriminator (CSV)", "Events", "b-Discriminator (CSV)", "LL", 0.1, 70000, true, "log");

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
  TPaveText* pt = new TPaveText(0.18,0.75,0.18,0.87,"brNDC");

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
