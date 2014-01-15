#include <iostream>
#include <iomanip>
#include "tdrstyle.C"

TFile* fEE, * fME, * fMM;
TString outDirName = ".";

const int nBkg = 5;
const char* bkgNames[] = {"hMC_TTbarOthers", "hMC_Wl", "hMC_VV", "hMC_SingleTop", "hMC_DYll"};
const char* bkgLabels[] = {
  "t#bar{t} others", "W #rightarrow l#nu", "Dibosons", "Single top", "Z/#gamma* #rightarrow ll"
};

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbar"};
const char* sigLabels[] = {"t#bar{t}"};
bool stackSig = true;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void mkFinalPlots(TString noteNumber = "Plots")
{
  setTDRStyle();

  TString path = "TopMass";

  fEE = TFile::Open(path+"/ElEl2Mu/ElEl2Mu.root");
  fME = TFile::Open(path+"/MuEl2Mu/MuEl2Mu.root");
  fMM = TFile::Open(path+"/MuMu2Mu/MuMu2Mu.root");

  if ( !fEE || !fME || !fMM ) return;

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);

/*   cutStepPlots("Step_1","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_1","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_1","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_1","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_1", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_1", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_1", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_1", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_1", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_1", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_1", "ZMass", "Dilepton mass", 0.01,   2000, false);
   cutStepPlots("Step_1", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_1", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_1", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_1", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_1", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_1", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_1", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_1", "jetspt30", "jets p_{T}", 0.01,   2000, false);   
   cutStepPlots("Step_1", "nJet", "Jet Multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_1", "METlog", "MET", 0.01,   2000, false);

   cutStepPlots("Step_2","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_2","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_2","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_2","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_2", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_2", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_2", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_2", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_2", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_2", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_2", "ZMass", "Dilepton mass", 0.01,   2000, false);
   cutStepPlots("Step_2", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_2", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_2", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_2", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_2", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_2", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_2", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_2", "jetspt30", "jets p_{T}", 0.01,   2000, false);       
   cutStepPlots("Step_2", "nJet", "Jet Multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_2", "METlog", "MET", 0.01,   2000, false);

   cutStepPlots("Step_3","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_3","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_3","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_3","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_3", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_3", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_3", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_3", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_3", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_3", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_3", "ZMass", "Dilepton mass", 0.01,   2000, false);
   cutStepPlots("Step_3", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_3", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_3", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_3", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_3", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_3", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_3", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_3", "jetspt30", "jets p_{T}", 0.01,   2000, false);       
   cutStepPlots("Step_3", "nJet", "Jet Multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_3", "METlog", "MET", 0.01,   2000, false);
*/
   cutStepPlots("Step_4","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_4","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_4","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_4","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_5","JPsidlPVZoom","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_4", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_4", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_4", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_4", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_4", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_4", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_4", "ZMass", "Dilepton mass", 0.01,   2000, false);
   cutStepPlots("Step_4", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_4", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_4", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_4", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_4", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_4", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_4", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_4", "jetspt30", "jets p_{T}", 0.01,   2000, false);       
   cutStepPlots("Step_4", "nJet", "Jet Multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_4", "METlog", "MET", 0.01,   2000, false);

  /* cutStepPlots("Step_5","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_5", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_5", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
*/
  //printCutFlow(path,"MuMu2Mu", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM");
  //printCutFlow(path,"ElEl2Mu", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM" );
  //printCutFlow(path,"MuEl2Mu", "nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM,nbJet30_CSVM");

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
//cutStepPlots("Step_8", "JPsiMass", "Dilepton mass", 0.01,   2000, false);
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
    hDataEE->SetMaximum(YmaxEE*1.2);
    hDataME->SetMaximum(YmaxME*1.2);
    hDataMM->SetMaximum(YmaxMM*1.2);
    hDataLL->SetMaximum(YmaxLL*1.8);
  }

  /*hDataEE->SetMaximum(maxY*0.25);
  hDataME->SetMaximum(maxY*0.5);
  hDataMM->SetMaximum(maxY*0.25);
  hDataLL->SetMaximum(maxY);*/

  TCanvas* cEE = new TCanvas(TString("cEE_")+cutStep+"_"+histName, TString("cEE_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cEE->SetLogy();
  hDataEE->Draw();
  legEE->Draw();
  getHeader(19.6, "ee channel")->Draw();
  hStackEE->Draw("same");
  hSigEE->Draw("same");
  hDataEE->Draw("same");
  hDataEE->Draw("sameaxis");
  cEE->Print(Form("%s/cEE_%s_%s.png", outDirName.Data(), cutStep, histName));
  //cEE->Print(Form("%s/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));

  TCanvas* cME = new TCanvas(TString("cME_")+cutStep+"_"+histName, TString("cME_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cME->SetLogy();
  hDataME->Draw();
  legME->Draw();
  getHeader(19.6, "#mue channel")->Draw();
  hStackME->Draw("same");
  if( nSig > 0 ) hSigME->Draw("same");
  hDataME->Draw("same");
  hDataME->Draw("sameaxis");
  cME->Print(Form("%s/cME_%s_%s.png", outDirName.Data(), cutStep, histName));
  //cME->Print(Form("%s/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));

  TCanvas* cMM = new TCanvas(TString("cMM_")+cutStep+"_"+histName, TString("cMM_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cMM->SetLogy();
  hDataMM->Draw();
  legMM->Draw();
  getHeader(19.6, "#mu#mu channel")->Draw();
  hStackMM->Draw("same");
  hSigMM->Draw("same");
  hDataMM->Draw("same");
  hDataMM->Draw("sameaxis");
  cMM->Print(Form("%s/cMM_%s_%s.png", outDirName.Data(), cutStep, histName));
  //cMM->Print(Form("%s/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  hDataLL->Draw();
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();
  hStackLL->Draw("same");
  if( !stackSig ) hSigLL->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");
  cLL->Print(Form("%s/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  //cLL->Print(Form("%s/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));

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
  //pt->AddText("CMS Preliminary");
  pt->AddText(Form("%.1f fb^{-1} at  #sqrt{s} = 8 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}
