#include <iostream>
#include <iomanip>
#include "tdrstyle.C"

TFile* fEE, * fME, * fMM;
TString outDirName = ".";
    
const int nBkg = 8;
const char* bkgNames[] = {//"hMCSig_TTbarbb",
 "hMC_TTbarcc","hMC_TTbarll","hMC_TTbarOthers","hMC_Wl", "hMC_VV", "hMC_SingleTop", "hMC_DYll"
,"hDataBkg_QCD"
};
const char* bkgLabels[] = {//"t#bar{t}+bb",
  "t#bar{t}+cc", "t#bar{t}+LF","t#bar{t} others","W #rightarrow l#nu", "Dibosons", "Single top", "Z/#gamma* #rightarrow ll"
,"QCD"
};
const Color_t color_sig = kBlue+2;
const int style_sig = 1001;
const Color_t color[] = {//kRed+3,
    kOrange+2,kRed,kRed-7,kGreen-3,kGray+4,kMagenta,kAzure-2
//,kYellow
};
const int     style[] = {//1001,
1001,  1001,  1001,    1001,   1001,    1001,    1001
,   1001
};

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbarbb"};//"hMCSig_TTbarH125"};
const char* sigLabels[] = {"t#bar{t}+bb"};//"t#bar{t}+H"};
bool stackSig = true;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlotsFor8TeV(TString noteNumber = "TTBB_26Mar_CSVT_Plots")
{
  setTDRStyle();

  TString path = "TTBB_26Mar_CSVT"; 

  fEE = TFile::Open(path+"/ElEl/ElEl.root");
  fME = TFile::Open(path+"/MuEl/MuEl.root");
  fMM = TFile::Open(path+"/MuMu/MuMu.root");

  if ( !fEE || !fME || !fMM ) return;

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);
/////////////

  cutStepPlot2l();
  cutStepPlot2();
}
void cutStepPlot2l()
{
      cutStepPlots("Step_4", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, false);

      cutStepPlots("Step_5", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, false); 

      cutStepPlots("Step_5", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, false);
      cutStepPlots("Step_5", "addjet1_bDisCSV", "b-Discriminator (CSV)", 0.01,   2000, false);
      cutStepPlots("Step_5", "addjet2_bDisCSV", "b-Discriminator (CSV)", 0.01,   2000, false);
//////////////
}


void cutStepPlot2()
{

      cutStepPlots("Step_4", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, true);

      cutStepPlots("Step_5", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, true);

      cutStepPlots("Step_5", "nbJet30_CSVT", "b-Jet Multiplicity (CSVT)", 0.01,   2000, true);
      cutStepPlots("Step_5", "addjet1_bDisCSV", "b-Discriminator (CSV)", 0.01,   2000, true);
      cutStepPlots("Step_5", "addjet2_bDisCSV", "b-Discriminator (CSV)", 0.01,   2000, true);
//////////////
}


void rescalePlots(TString cutStep, TString bkgName, TString histNamesStr, double mumuScale, double elelScale, double muelScale)
{
  TObjArray* histNames = histNamesStr.Tokenize(",");

  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    TString histName = histNames->At(i)->GetName();

    TH1F* hEE = (TH1F*)fEE->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));
    TH1F* hME = (TH1F*)fME->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));
    TH1F* hMM = (TH1F*)fMM->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));

    if ( !hEE || !hME || !hMM ) continue;

    hEE->Scale(elelScale);
    hMM->Scale(mumuScale);
    hME->Scale(muelScale);
  }
}

// Function to draw EE, ME, MM channel and all channel merged plot
void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY)
{
  TH1F* hDataEE = (TH1F*)fEE->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataME = (TH1F*)fME->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataMM = (TH1F*)fMM->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));

  if ( !hDataEE ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for EE " << "\n"; return; }
  if ( !hDataME ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for ME " << "\n"; return; }
  if ( !hDataMM ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for MM " << "\n"; return; }

  TH1F* hDataLL = (TH1F*)hDataEE->Clone(Form("hData_%s_%s", cutStep, histName));
  hDataLL->Reset();
  hDataLL->Add(hDataEE);
  hDataLL->Add(hDataME);
  hDataLL->Add(hDataMM);

  THStack* hStackEE = new THStack(TString("hEE_")+cutStep+"_"+histName, histTitle);
  THStack* hStackME = new THStack(TString("hME_")+cutStep+"_"+histName, histTitle);
  THStack* hStackMM = new THStack(TString("hMM_")+cutStep+"_"+histName, histTitle);
  THStack* hStackLL = new THStack(TString("hLL_")+cutStep+"_"+histName, histTitle);

  TH1F* hSigEE = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));
  TH1F* hSigME = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));
  TH1F* hSigMM = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));

  hSigEE->SetFillColor(color_sig);
  hSigME->SetFillColor(color_sig);
  hSigMM->SetFillColor(color_sig);

  hSigEE->SetFillStyle(style_sig);
  hSigME->SetFillStyle(style_sig);
  hSigMM->SetFillStyle(style_sig);

  //hSigEE->SetLineColor(color_sig);
  //hSigME->SetLineColor(color_sig);
  //hSigMM->SetLineColor(color_sig);




  if ( !hSigEE || !hSigME || !hSigMM ) { cout << "No signal hist for " << histName << "\n"; return; }

  TH1F* hSigLL = (TH1F*)hSigEE->Clone(Form("%s_%s_%s", sigNames[0], cutStep, histName));
  hSigLL->Reset();
  hSigLL->Add(hSigEE);
  hSigLL->Add(hSigME);
  hSigLL->Add(hSigMM);

  if( stackSig ){
    hStackEE->Add(hSigEE);
    hStackME->Add(hSigME);
    hStackMM->Add(hSigMM);
    hStackLL->Add(hSigLL);
  }

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
    TH1F* hEE = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hME = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hMM = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));

    hEE->SetFillColor(color[i]);
    hME->SetFillColor(color[i]);
    hMM->SetFillColor(color[i]);

    hEE->SetFillStyle(style[i]);
    hME->SetFillStyle(style[i]);
    hMM->SetFillStyle(style[i]);

   // hEE->SetLineColor(color[i]);
   // hME->SetLineColor(color[i]);
   // hMM->SetLineColor(color[i]);


    if ( !hEE || !hME || !hMM ) { cout << "No bkg hist " << bkgNames[i] << endl; continue; }

    TH1F* hLL = (TH1F*)hEE->Clone(Form("%s_%s_%s", bkgNames[i], cutStep, histName));
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

  legEE->AddEntry(hSigEE, sigLabels[0], "f");
  legME->AddEntry(hSigME, sigLabels[0], "f");
  legMM->AddEntry(hSigMM, sigLabels[0], "f");
  legLL->AddEntry(hSigLL, sigLabels[0], "f");


  // Be ready for draw
  double YmaxEE = 0, YmaxMM=0, YmaxME=0, YmaxLL=0;
  YmaxEE = hDataEE->GetMaximum();
  YmaxMM = hDataMM->GetMaximum();
  YmaxME = hDataME->GetMaximum();
  YmaxLL = hDataLL->GetMaximum();

  hDataEE->SetMinimum(minY);
  hDataME->SetMinimum(minY);
  hDataMM->SetMinimum(minY);
  hDataLL->SetMinimum(minY);

  if(YmaxEE >YmaxMM) YmaxMM=YmaxEE;
  else               YmaxEE=YmaxMM;

  if(doLogY)
  {
    hDataEE->SetMaximum(YmaxEE*100);
    hDataME->SetMaximum(YmaxME*100);
    hDataMM->SetMaximum(YmaxMM*100);
    hDataLL->SetMaximum(YmaxLL*100);
  }
  else
  {
    hDataEE->SetMaximum(YmaxEE*2.5);
    hDataME->SetMaximum(YmaxME*2.5);
    hDataMM->SetMaximum(YmaxMM*2.5);
    hDataLL->SetMaximum(YmaxLL*2.5);
  }


  TCanvas* cEE = new TCanvas(TString("cEE_")+cutStep+"_"+histName, TString("cEE_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cEE->SetLogy();
  hDataEE->Draw();
  legEE->Draw();
  getHeader(19.6, "ee channel")->Draw();
  hStackEE->Draw("same");
  hSigEE->Draw("same");
  hDataEE->Draw("same");
  hDataEE->Draw("sameaxis");

  if(doLogY)
  {
    cEE->Print(Form("%s/l_cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/l_cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/l_cEE_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cEE->Print(Form("%s/cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/cEE_%s_%s.png", outDirName.Data(), cutStep, histName));
  }

  TCanvas* cME = new TCanvas(TString("cME_")+cutStep+"_"+histName, TString("cME_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cME->SetLogy();
  hDataME->Draw();
  legME->Draw();
  getHeader(19.6, "#mue channel")->Draw();
  hStackME->Draw("same");
  if( nSig > 0 ) hSigME->Draw("same");
  hDataME->Draw("same");
  hDataME->Draw("sameaxis");

  if(doLogY)
  {
    cME->Print(Form("%s/l_cME_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/l_cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/l_cME_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cME->Print(Form("%s/cME_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/cME_%s_%s.png", outDirName.Data(), cutStep, histName));
  }


  TCanvas* cMM = new TCanvas(TString("cMM_")+cutStep+"_"+histName, TString("cMM_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cMM->SetLogy();
  hDataMM->Draw();
  legMM->Draw();
  getHeader(19.6, "#mu#mu channel")->Draw();
  hStackMM->Draw("same");
  hSigMM->Draw("same");
  hDataMM->Draw("same");
  hDataMM->Draw("sameaxis");

  if(doLogY)
  {
    cMM->Print(Form("%s/l_cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/l_cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/l_cMM_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cMM->Print(Form("%s/cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/cMM_%s_%s.png", outDirName.Data(), cutStep, histName));
  } 

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  hDataLL->Draw();
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();
  hStackLL->Draw("same");
  if( !stackSig ) hSigLL->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");

  if(doLogY)
  {
    cLL->Print(Form("%s/l_cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/l_cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/l_cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  } 
  else
  {
    cLL->Print(Form("%s/cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
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
  pt->AddText(Form("%.1f fb^{-1} at  #sqrt{s} = 8 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}
