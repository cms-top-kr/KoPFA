#include <iostream>
#include <iomanip>
#include "tdrstyle.C"

TFile* fEE, * fME, * fMM;
TString outDirName = ".";

const int nBkg = 5;
const char* bkgNames[] = {"hMC_TTbarOthersSL", "hMC_Wl", "hMC_VV", "hMC_SingleTop", "hMC_DYll"};
const char* bkgNamesPY[] = {"hMC_TTbarOthersPY", "hMC_Wl", "hMC_VV", "hMC_SingleTop", "hMC_DYll"};
const char* bkgLabels[] = {
  "t#bar{t} others (MG)", "W #rightarrow l#nu", "Dibosons", "Single top", "Z/#gamma* #rightarrow ll"
};

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbar","hMCSig_TTbarPY"};
const char* sigLabels[] = {"t#bar{t} (MG)","t#bar{t} (PY6)"};
bool stackSig = true;

void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void makeFinalPlots(TString noteNumber = "Plots")
{
  setTDRStyle();

  TString path = "TopMass_lowAg1_174";
  //TString path = "TopMass_Lcut002_PYMG";
  //TString path = "TopMass_noLcut_PYMG";

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
*/   cutStepPlots("Step_5", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_5", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
/*   cutStepPlots("Step_1", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_1", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   cutStepPlots("Step_1", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_1", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
*/   cutStepPlots("Step_5", "ZMass", "Dilepton mass", 0.01,   2000, false);
   //cutStepPlots("Step_1", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   cutStepPlots("Step_5", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_5", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_5", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_5", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_5", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_5", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
/*   cutStepPlots("Step_1", "jetspt30", "jets p_{T}", 0.01,   2000, false);   
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
*/   cutStepPlots("Step_5", "nJetlog5", "Jet Multiplicity", 0.01,   2000, false);
   //cutStepPlots("Step_3", "METlog", "MET", 0.01,   2000, false);

   cutStepPlots("Step_5","JPsiMassFull02","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_6","JPsiMassFull02","JPsi mass",0.01,2000,false);

   //cutStepPlots("Step_5","JPsiMassFit","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_4","JPsivProb","JPsi vertex probability",0.01,2000,false);
   cutStepPlots("Step_5","JPsivProb","JPsi vertex probability",0.01,2000,false);
   cutStepPlots("Step_5","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_5","ssJPsiMass","SS dimuon mass",0.01,2000,false);
   cutStepPlots("Step_5","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_5","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_5","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_5","JPsidlPVZoom","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_5","JPsidlErrPV","3D distance PV-J/#psi vertex/#sigma ",0.01,2000,false);
   cutStepPlots("Step_5", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_5", "JPsiJetDPtFrac", "(p_{T}(nearest jet)-p_{T}(J/#psi))/p_{T}(nearest jet)", 0.01,   2000, false);
   cutStepPlots("Step_5", "JPsiJetJPsiPtFrac", "p_{T}(J/#psi)/p_{T}(nearest jet)", 0.01,   2000, false);
   cutStepPlots("Step_5", "lep3_pixlayers", "leading lep. pixel layers", 0.01,   2000, false);
   cutStepPlots("Step_5", "lep4_pixlayers", "second lep. pixel layers", 0.01,   2000, false);
   cutStepPlots("Step_6","JPsivProb","JPsi vertex probability",0.01,2000,false);
   cutStepPlots("Step_6","JPsiMass","JPsi mass",0.01,2000,false);
   cutStepPlots("Step_6","ssJPsiMass","SS dimuon mass",0.01,2000,false);
   cutStepPlots("Step_6","JPsiPt","JPsi p_{T}",0.01,2000,false);
   cutStepPlots("Step_6","JPsiEta","JPsi #eta",0.01,2000,false);
   cutStepPlots("Step_6","JPsidlPV","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_6","JPsidlErrPV","3D distance PV-J/#psi vertex/#sigma ",0.01,2000,false);
   cutStepPlots("Step_6","JPsidlPVZoom","3D distance PV-J/#psi vertex ",0.01,2000,false);
   cutStepPlots("Step_6", "LepJPsiMass1", "Leading lep+JPsi mass", 0.01,   2000, false);
   cutStepPlots("Step_6", "LepJPsiMass2", "Second leading lep+JPsi mass", 0.01,   2000, false);
   //cutStepPlots("Step_5", "LepJPsidPhilower", "#Delta #phi(J/#psi-isolated lepton)", 0.01,   2000, false);
   //cutStepPlots("Step_5", "LepJPsidRlower", "#Delta R(J/#psi-isolated lepton)", 0.01,   2000, false);
   //cutStepPlots("Step_5", "JPsiJetMinDPhi", "#Delta #phi(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_6", "JPsiJetMinDR", "#Delta R(J/#psi-jet) min", 0.01,   2000, false);
   cutStepPlots("Step_6", "JPsiJetDPtFrac", "(p_{T}(nearest jet)-p_{T}(J/#psi))/p_{T}(nearest jet)", 0.01,   2000, false);
   cutStepPlots("Step_6", "JPsiJetJPsiPtFrac", "p_{T}(J/#psi)/p_{T}(nearest jet)", 0.01,   2000, false);
   cutStepPlots("Step_6", "lep3_pixlayers", "leading lep. pixel layers", 0.01,   2000, false);
   cutStepPlots("Step_6", "lep4_pixlayers", "second lep. pixel layers", 0.01,   2000, false);
   //cutStepPlots("Step_5", "ZMass", "Dilepton mass", 0.01,   2000, false);
   //cutStepPlots("Step_5", "nVertex", "Vertex multiplicity", 0.01,   2000, false);
   //cutStepPlots("Step_5", "pt1", "Leading lepton p_{T}", 0.01,   2000, false);
   /*cutStepPlots("Step_5", "pt2", "Second lepton p_{T}", 0.01,   2000, false);
   cutStepPlots("Step_5", "eta1", "Leading lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_5", "eta2", "Second lepton #eta", 0.01,   2000, false);
   cutStepPlots("Step_5", "Iso03lep1", "Leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_5", "Iso03lep2", "Second leading lepton Rel. Iso.", 0.01,   2000, false);
   cutStepPlots("Step_5", "jetspt30", "jets p_{T}", 0.01,   2000, false);       
   cutStepPlots("Step_5", "nJet", "Jet Multiplicity", 0.01,   2000, false);
*/   //cutStepPlots("Step_5", "METlog", "MET", 0.01,   2000, false);

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

  TH1F* hSigEEPY = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, sigNames[1], cutStep, histName));
  TH1F* hSigMEPY = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, sigNames[1], cutStep, histName));
  TH1F* hSigMMPY = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, sigNames[1], cutStep, histName));

  if ( !hSigEEPY || !hSigMEPY || !hSigMMPY ) { cout << "No PY6 signal hist for " << histName << "\n"; return; }

  TH1F* hSigLLPY = (TH1F*)hSigEEPY->Clone(Form("%s_%s_%s", sigNames[1], cutStep, histName));
  hSigLLPY->SetLineStyle(2);
  hSigLLPY->SetLineWidth(2);
  //hSigLLPY->SetFillColor(kRed);
  hSigLLPY->SetFillStyle(0);
  hSigLLPY->Reset();
  hSigLLPY->Add(hSigEEPY);
  hSigLLPY->Add(hSigMEPY);
  hSigLLPY->Add(hSigMMPY);

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

/*    TH1F* hEEPY = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, bkgNamesPY[i], cutStep, histName));
    TH1F* hMEPY = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, bkgNamesPY[i], cutStep, histName));
    TH1F* hMMPY = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, bkgNamesPY[i], cutStep, histName));

    if ( !hEEPY || !hMEPY || !hMMPY ) {
        cout << "No PY6 bkg hist " << bkgNamesPY[i] << endl; continue; 
    }

    TH1F* hLLPY = (TH1F*)hEEPY->Clone(Form("%s_%s_%s", bkgNamesPY[i], cutStep, histName));
    hLLPY->Reset();
    hLLPY->Add(hEEPY);
    hLLPY->Add(hMEPY);
    hLLPY->Add(hMMPY);
    hSigLLPY->Add(hLLPY);*/

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
  legLL->AddEntry(hSigLLPY, sigLabels[1], "l");


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
  cEE->Print(Form("%s/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cEE->Print(Form("%s/cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));

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
  cME->Print(Form("%s/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cME->Print(Form("%s/cME_%s_%s.eps", outDirName.Data(), cutStep, histName));

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
  cMM->Print(Form("%s/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cMM->Print(Form("%s/cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  /*if(histName=="JPsiMassFull") {
    hDataLL->SetLineStyle(1);
    hDataLL->SetLineWidth(2);
  }*/
  hDataLL->Draw();
  legLL->Draw();
  getHeader(19.6, "Dilepton channel")->Draw();
  hStackLL->Draw("same");
  if( !stackSig ) hSigLL->Draw("same");
  hSigLLPY->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");
  cLL->Print(Form("%s/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  cLL->Print(Form("%s/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
  cLL->Print(Form("%s/cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
  cLL->Print(Form("%s/cLL_%s_%s.C", outDirName.Data(), cutStep, histName));
  if(histName=="JPsiMassFull"){
     //gStyle->SetOptStat(1111);
     TFile *f =  new TFile(Form("%s/dimuonmass-2l1jpsi1jet.root",outDirName.Data()),"recreate");
     hDataLL->Write();
     //hStackLL->Write();
     //hSigLLPY->Write();
     f->Close();
  }
  //cout<<"histName: "<<histName<<endl;
  /*if(histName=="JPsiMassFull"){

    RooRealVar mass("mass","mass",0,7) ;

    RooRealVar mean("mean","Gaussian mean",3.096,3.0,3.2) ;
    RooRealVar sigma("sigma","sigma",0.03,0.02,0.04) ;
    RooGaussian gauss("gauss","gauss",mass,mean,sigma);

    RooRealVar lmean("lmean","Landau mean",1.15,1.0,1.5);
    RooRealVar lsigma("lsigma","Landau sigma",0.5,0.0,1.0);
    RooLandau  landau("landau","Landau",x,lmean,lsigma);

    RooRealVar sigfrac("sigfrac","fraction of signal",0.1,0.,1.) ;
    //RooRealVar bkgfrac("bkgfrac","fraction of background",0.9,0.,1.) ;

    RooAddPdf  model("model","g+l",RooArgList(gauss,landau),sigfrac);

    RooDataHist dhdata("dhdata","dhdata",mass,Import(*hDataLL)) ;
    //RooDataHist dhstack("dhstack","dhstack",mass,Import(*hStackLL)) ;
    //RooDataHist dhpy("dhpy","dhpy",mass,Import(*hSigLLPY)) ;

    model.fitTo(dhdata) ;

    RooPlot* frame = mass.frame(Title("Fit JPsi mass with Poisson error bars")) ;
    dhdata.plotOn(frame) ;
    //dhstack.plotOn(frame) ;
    //dhpy.plotOn(frame) ;
    model.plotOn(frame) ;
    
    TCanvas* c = new TCanvas("jpsifull","JPsi Mass Full",800,600) ;
    frame->Draw();
    c->Print(Form("%s/cLL_%s_%s_fit.pdf", outDirName.Data(), cutStep, histName));
  } */
}

TLegend* buildLegend()
{
  TLegend* leg = new TLegend(0.67,0.57,0.85,0.90,NULL,"brNDC");

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
