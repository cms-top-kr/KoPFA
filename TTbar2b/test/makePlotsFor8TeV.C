#include <iostream>
#include <iomanip>
#include "tdrstyle.C"

TFile* fEE, * fME, * fMM;
TString outDirName = ".";

const int nBkg = 8;
const char* bkgNames[] = {"hMCSig_TTbarbb",
 "hMC_TTbarcc","hMC_TTbarll","hMC_TTbarOthers","hMC_Wl", "hMC_VV", "hMC_SingleTop", "hMC_DYll"
//,"hDataBkg_QCD"
};
const char* bkgLabels[] = {"t#bar{t}+bb",
  "t#bar{t}+cc", "t#bar{t}+LF","t#bar{t} others","W #rightarrow l#nu", "Dibosons", "Single top", "Z/#gamma* #rightarrow ll"
//,"QCD"
};
const Color_t color_sig = kBlue+2;
const int style_sig = 1001;
const Color_t color[] = {kRed+3,
    kOrange+2,kRed,kRed-7,kGreen-3,kGray+4,kMagenta,kAzure-2
//,kYellow
};
const int     style[] = {1001,
1001,  1001,  1001,    1001,   1001,    1001,    1001
//,   1001
};

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbarH125"};
const char* sigLabels[] = {"t#bar{t}+H"};
bool stackSig = false;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlotsFor8TeV(TString noteNumber = "TTBB_05Nov2012_CSVM_Plots/v1")
{
  setTDRStyle();

  TString path = "TTBB_05Nov2012_CSVM"; 

  fEE = TFile::Open(path+"/ElEl/ElEl.root");
  fME = TFile::Open(path+"/MuEl/MuEl.root");
  fMM = TFile::Open(path+"/MuMu/MuMu.root");

  if ( !fEE || !fME || !fMM ) return;

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);

//  cutStepPlots("Step_1", "Iso03lep1", "Relative Isolation (GeV)", 1, 1e12, true);
//  cutStepPlots("Step_1", "Iso03lep2", "Relative Isolation (GeV)", 1, 1e12, true);
  cutStepPlots("Step_1", "pt1", "Leading lepton p_{T};p_{T} (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
  cutStepPlots("Step_1", "pt2", "Second leading lepton p_{T};p_{T} (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
  cutStepPlots("Step_1", "eta1", "Leading lepton #eta;#eta (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
  cutStepPlots("Step_1", "eta2", "Second leading lepton #eta;#eta (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);

  cutStepPlots("Step_1", "nVertex", "Vertex multiplicity", 0.1, 2.5*1e10, true);
//  cutStepPlots("Step_1", "METlog", "Missing E_{T}", 1, 1e9, true);
//  cutStepPlots("Step_1", "nJetlog", "Jet multiplicity", 1, 1e9, true);
  cutStepPlots("Step_1", "ZMass", "Z mass", 1, 1e9, true);


//  cutStepPlots("Step_2", "pt1", "Leading lepton p_{T};p_{T} (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
//  cutStepPlots("Step_2", "pt2", "Second leading lepton p_{T};p_{T} (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
//  cutStepPlots("Step_2", "eta1", "Leading lepton #eta;#eta (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);
//  cutStepPlots("Step_2", "eta2", "Second leading lepton #eta;#eta (GeV/c);Events/10 GeV/c", 0.1, 1e12, true);

//  cutStepPlots("Step_2", "nVertex", "Vertex multiplicity", 0, 2e6, true);
  cutStepPlots("Step_2", "METlog", "Missing E_{T}", 1, 1e9, true);
//  cutStepPlots("Step_2", "nJetlog", "Jet multiplicity", 1, 1e9, true);
  cutStepPlots("Step_2", "ZMass", "Z mass", 1, 1e9, true);


  cutStepPlots("Step_3", "nJet", "Jet multiplicity", 1, 1e9, true);
  cutStepPlots("Step_3", "MET", "Missing E_{T}", 1, 1e10, true);
  cutStepPlots("Step_3", "ZMass", "Z mass", 1, 1e9, true);
//  cutStepPlots("Step_3", "nVertex", "Vertex multiplicity", 0, 2e6, true);
//  cutStepPlots("Step_4", "nbJet30_CSVM", "b-Jet multiplicity(CSVM)", 1, 1e6, true);


  cutStepPlots("Step_4", "METlog", "Missing E_{T}", 1, 1e10, false);
  cutStepPlots("Step_4", "nJet", "Jet multiplicity", 1, 1e9, false);
  cutStepPlots("Step_4", "MET", "Missing E_{T}", 1, 1e10, false);
  cutStepPlots("Step_4", "nbJet30_CSVM", "b-Jet multiplicity(CSVM)", 1, 1e6, false);
/*
  cutStepPlots("Step_4", "Mbb", "M_{bb}", 1, 1e6, false);
  cutStepPlots("Step_4", "Top1M", "kin Top Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "Top2M", "kin Top Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "TTM", "kin ttbar Mass (GeV/c^{2}", 1, 1e6, false);
  cutStepPlots("Step_4", "secTM1", "Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "secTM2", "Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "secM1", "Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "secM2", "Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);

  cutStepPlots("Step_4", "maosMbb", "M M_{bb}", 1, 1e6, false);
  cutStepPlots("Step_4", "maosTop1M", "M Top Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "maosTop2M", "M Top Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "maosTTM", "M ttbar Mass (GeV/c^{2}", 1, 1e6, false);
  cutStepPlots("Step_4", "maossecTM1", "M Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "maossecTM2", "M Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "maossecM1", "M Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
  cutStepPlots("Step_4", "maossecM2", "M Secondary Vertex Mass (GeV/c^{2})", 1, 1e6, false);
*/
/////////////
//  cutStepPlots("Step_5", "METlog", "Missing E_{T}", 1, 1e10, false);
//  cutStepPlots("Step_5", "nJetlog", "Jet multiplicity", 1, 1e9, false);
//  cutStepPlots("Step_5", "MET", "Missing E_{T}", 1, 1e10, false);
//  cutStepPlots("Step_5", "nbJet30_CSVM", "b-Jet multiplicity(CSVM)", 1, 1e6, true);

/*
  cutStepPlots("Step_5", "Mbb", "M_{bb}", 1, 250, false);
  cutStepPlots("Step_5", "Top1M", "kin Top Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "Top2M", "kin Top Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "TTM", "kin ttbar Mass (GeV/c^{2}", 1, 150, false);
  cutStepPlots("Step_5", "secTM1", "Secondary Vertex Mass (GeV/c^{2})", 1, 400, false);
  cutStepPlots("Step_5", "secTM2", "Secondary Vertex Mass (GeV/c^{2})", 1, 400, false);
  cutStepPlots("Step_5", "secM1", "Secondary Vertex Mass (GeV/c^{2})", 1, 100, false);
  cutStepPlots("Step_5", "secM2", "Secondary Vertex Mass (GeV/c^{2})", 1, 100, false);
*/
  cutStepPlots("Step_5", "maosMbb", "M M_{bb}", 1, 200, false);
  cutStepPlots("Step_5", "maosTop1M", "M Top Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "maosTop2M", "M Top Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "maosTTM", "M ttbar Mass (GeV/c^{2}", 1, 100, false);
  cutStepPlots("Step_5", "maossecTM1", "M Secondary Vertex Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "maossecTM2", "M Secondary Vertex Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "maossecM1", "M Secondary Vertex Mass (GeV/c^{2})", 1, 300, false);
  cutStepPlots("Step_5", "maossecM2", "M Secondary Vertex Mass (GeV/c^{2})", 1, 300, false);




  //cutStepPlots("Step_4", "", "", 1, 1e6, true);

//  cutStepPlots("Step_5", "nJet", "Jet multiplicity", 1, 1e6, true);


//  cutStepPlots("Step_6", "nbJet_CSVL", "b-Jet multiplicity(CSVL)", 1, 1e6, true);
//  cutStepPlots("Step_5", "nbJet30_CSVM", "b-Jet multiplicity(CSVM)", 1, 1e6, true);
//  cutStepPlots("Step_6", "nbJet_CSVM", "b-Jet multiplicity(CSVM)", 1, 1e6, true);

/*
  cutStepPlots("Step_1", "nJet", "Jet multiplicity", 0, 5000000, false);
  cutStepPlots("Step_2", "nJet", "Jet multiplicity", 0, 500000, false);
  cutStepPlots("Step_3", "nJet", "Jet multiplicity", 0, 5000, false);
  cutStepPlots("Step_4", "nJet", "Jet multiplicity", 0, 5000, false);
  cutStepPlots("Step_5", "nJet", "Jet multiplicity", 0, 5000, false);
*/

  //printCutFlow(path,"MuMu", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM");
  //printCutFlow(path,"ElEl", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM" );
  //printCutFlow(path,"MuEl", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM");

  // Restore back DY scaling again, and apply -50%
  //rescalePlots("Step_3", "DYll", "METlog,nJetlog,ZMass", 1/(1+.04*.5)*(1-.04*.5), 1/(1+.04*.5)*(1-.04*.5), 1);
  //rescalePlots("Step_4", "DYll", "METlog"              , 1/(1+.34*.5)*(1-.34*.5), 1/(1+.34*.5)*(1-.34*.5), 1);
  //rescalePlots("Step_5", "DYll", "MET"                 , 1/(1+.87*.5)*(1-.87*.5), 1/(1+.91*.5)*(1-.91*.5), 1);
  //rescalePlots("Step_6", "DYll", "nJet,vsumMAlt"       , 1/(1+.51*.5)*(1-.51*.5), 1/(1+.91*.5)*(1-.91*.5), 1);
  //rescalePlots("Step_7", "DYll", "nbJet,vsumMAlt,MET"  , 1/(1+.51*.5)*(1-.51*.5), 1/(1+.91*.5)*(1-.91*.5), 1);

  //printCutFlow("MuMu", "-,-,METlog,METlog,MET,vsumMAlt,vsumMAlt");
  //printCutFlow("ElEl", "-,-,METlog,METlog,MET,vsumMAlt,vsumMAlt");
  //printCutFlow("MuEl", "-,-,METlog,METlog,MET,vsumMAlt,vsumMAlt");
}

void printCutFlow(TString path, TString decayMode, TString histNamesStr)
{
  TFile* f = gROOT->GetFile(path + "/"+decayMode+"/"+decayMode+".root");
  if ( !f ) f = TFile::Open(path + "/"+decayMode+"/"+decayMode+".root");

  TObjArray* histNames = histNamesStr.Tokenize(",");
  std::vector<double> nBkgTotal(histNames->GetEntries());
  std::vector<double> nMCTotal(histNames->GetEntries());

  // Pretty printing
  int maxLabelWidth = 0;
  for ( int i=0; i<nBkg; ++i )
  {
    const int labelWidth = strlen(bkgLabels[i]);
    if ( labelWidth > maxLabelWidth ) maxLabelWidth = labelWidth;
  }
  TString labelForm = Form("%%%ds", maxLabelWidth);

  cout << "========================================= " << decayMode << " =========================================\n";
  cout << Form(labelForm.Data(), "-");
  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    cout << Form("\tStep_%d", i+1);
  }

  cout << "\n----------------------------------------------------------------------------------------\n";

  for ( int i=0; i<nBkg; ++i )
  {
    cout << Form(labelForm.Data(), bkgLabels[i]);
    for ( int j=0; j<histNames->GetEntries(); ++j )
    {
      TString histName = histNames->At(j)->GetName();
      TH1F* hMC = (TH1F*)f->Get(Form("Step_%d/%s_Step_%d_%s", j+1, bkgNames[i], j+1, histName.Data()));
      if ( !hMC ) 
      {
        cout << "\t-";
        continue;
      }

      nBkgTotal[j] += hMC->Integral();
      if( hMC->Integral() > 1000 ) cout << fixed << setprecision (0) << '\t' << hMC->Integral(); 
      else cout << fixed << setprecision (2) << '\t' << hMC->Integral();
    }
    cout << "\n";
  }

  cout << "----------------------------------------------------------------------------------------\n";
  const char* sigName = sigNames[0];
  cout << Form(labelForm.Data(), sigLabels[0]);
  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    TString histName = histNames->At(i)->GetName();

    TH1F* hSig = (TH1F*)f->Get(Form("Step_%d/%s_Step_%d_%s", i+1, sigName, i+1, histName.Data()));
    if ( !hSig )
    {
      cout << "\t-";
      continue;
    }

    nMCTotal[i] = nBkgTotal[i]+hSig->Integral();
    if( hSig->Integral() > 1000) cout << fixed << setprecision(0) << '\t' << hSig->Integral();
    else cout << fixed << setprecision(2) << '\t' << hSig->Integral();
  }

  cout << "\n----------------------------------------------------------------------------------------\n";
  cout << Form(labelForm.Data(), "Bkg total");
  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    if( nBkgTotal[i] > 1000) cout << fixed << setprecision(0) << '\t' << nBkgTotal[i];
    else cout << fixed << setprecision(2) << '\t' << nBkgTotal[i];
  }
  cout << '\n';
  cout << Form(labelForm.Data(), "MC total");
  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    if( nMCTotal[i] > 1000) cout << fixed << setprecision(0) << '\t' << nMCTotal[i];
    else cout << fixed << setprecision(2) << '\t' << nMCTotal[i];
  }
  cout << "\n----------------------------------------------------------------------------------------\n";

  cout << Form(labelForm.Data(), "Data");
  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    TString histName = histNames->At(i)->GetName();

    TH1F* hData = (TH1F*)f->Get(Form("Step_%d/hData_Step_%d_%s", i+1, i+1, histName.Data()));
    if ( !hData )
    {
      cout << "\t-";
      continue;
    }

    cout << fixed << setprecision(0) << '\t' << hData->Integral();
  }
  cout << "\n========================================================================================\n\n";
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

 // hSigEE->SetLineColor(color_sig);
 // hSigME->SetLineColor(color_sig);
 // hSigMM->SetLineColor(color_sig);




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
  hDataEE->SetMinimum(minY);
  hDataME->SetMinimum(minY);
  hDataMM->SetMinimum(minY);
  hDataLL->SetMinimum(minY);

  hDataEE->SetMaximum(maxY*0.25);
  hDataME->SetMaximum(maxY*0.5);
  hDataMM->SetMaximum(maxY*0.25);
  hDataLL->SetMaximum(maxY);

  TCanvas* cEE = new TCanvas(TString("cEE_")+cutStep+"_"+histName, TString("cEE_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cEE->SetLogy();
  hDataEE->Draw();
  legEE->Draw();
  getHeader(12.0, "ee channel")->Draw();
  hStackEE->Draw("same");
  hSigEE->Draw("same");
  hDataEE->Draw("same");
  hDataEE->Draw("sameaxis");
  cEE->Print(Form("%s/cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));
  cEE->Print(Form("%s/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cEE->Print(Form("%s/cEE_%s_%s.png", outDirName.Data(), cutStep, histName));

  TCanvas* cME = new TCanvas(TString("cME_")+cutStep+"_"+histName, TString("cME_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cME->SetLogy();
  hDataME->Draw();
  legME->Draw();
  getHeader(12.0, "#mue channel")->Draw();
  hStackME->Draw("same");
  if( nSig > 0 ) hSigME->Draw("same");
  hDataME->Draw("same");
  hDataME->Draw("sameaxis");
  cME->Print(Form("%s/cME_%s_%s.eps", outDirName.Data(), cutStep, histName));
  cME->Print(Form("%s/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cME->Print(Form("%s/cME_%s_%s.png", outDirName.Data(), cutStep, histName));

  TCanvas* cMM = new TCanvas(TString("cMM_")+cutStep+"_"+histName, TString("cMM_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cMM->SetLogy();
  hDataMM->Draw();
  legMM->Draw();
  getHeader(12.0, "#mu#mu channel")->Draw();
  hStackMM->Draw("same");
  hSigMM->Draw("same");
  hDataMM->Draw("same");
  hDataMM->Draw("sameaxis");
  cMM->Print(Form("%s/cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));
  cMM->Print(Form("%s/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cMM->Print(Form("%s/cMM_%s_%s.png", outDirName.Data(), cutStep, histName));

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  hDataLL->Draw();
  legLL->Draw();
  getHeader(12.0, "All channel")->Draw();
  hStackLL->Draw("same");
  if( !stackSig ) hSigLL->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");
  cLL->Print(Form("%s/cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
  cLL->Print(Form("%s/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cLL->Print(Form("%s/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));

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
