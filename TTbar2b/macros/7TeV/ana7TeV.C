#include <iostream>
#include <map>
#include "TCut.h"
#include "TROOT.h"
#include "TSystem.h"

using namespace std;

void ana7TeV(){

  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("$CMSSW_BASE/src/KoPFA/CommonTools/macros/TopAnalyzerLite.cc", "k");

  ana("ElEl","TTBB_27Apr2013/ElEl");
  ana("MuMu","TTBB_27Apr2013/MuMu");
  ana("MuEl","TTBB_27Apr2013/MuEl");
}


void ana(string decayMode = "ElEl", string imageOutDir = "")
{

  //gSystem->CompileMacro("$CMSSW_BASE/src/KoPFA/CommonTools/macros/TopAnalyzerLite.cc", "k");
  bool createplots = true;
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir, createplots);

  const std::string mcPath = "/afs/cern.ch/work/b/bhlee/public/store/top/ntuple/7TeV/v3_20130412_V00-00-08/";
  const std::string rdPath = "/afs/cern.ch/work/b/bhlee/public/store/top/ntuple/7TeV/v3_20130412_V00-00-08/";
 
  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2011"+decayMode+".root", 4982);

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.4 && abs( genLep2_eta ) < 2.4" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttcc = "nGencJet20 >= 2";

  //when you use inclusive sample
  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarTuneZ2.root", 165.6, kRed+2, true, visible && sigcut);
  analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarTuneZ2.root", 165.6, kRed+1, visible && !sigcut && ttcc );
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarTuneZ2.root", 165.6, kRed, visible && !sigcut && !ttcc);
  analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 165.6, kRed-7, !visible);

  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 31314, kGreen-3); 

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 7.4 , kGray+4);
  analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 4.51, kGray+4);
  analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 0.61, kGray+4);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleToptW.root", 7.87, kMagenta);
  analyzer->addMCBkg("SingleTopBar", "Single top", mcPath+"/vallot_SingleTopBartW.root", 7.87, kMagenta);
  analyzer->addMCBkg("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3048, kAzure-2);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets10To50.root", 11908.83, kAzure-2);

  analyzer->addDataBkg("QCD", "QCD", rdPath+"/vallot_Run2011"+decayMode+".root", 1.0, kYellow);

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "nbjets", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  TCut S1 = "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0";
  TCut S2 = "";
  TCut S3 = "";
  if( decayMode != "MuEl" ){
    S2 = "abs(ZMass - 91.2) > 15";
    S3 = "MET > 30";
  }
  TCut S4 = "nJet30 >= 4";
  TCut S5 = "nbjets30_CSVT >= 2";

  //Step1 -----------------------------------------------------------------------
  analyzer->addCutStep(S1, "ZMass", 0.5, "1", "Step_1");
  //Step2 --------------------------------------------------------------------------
  analyzer->addCutStep(S2, "MET",   0.5, "1", "Step_2");
  //Step3 --------------------------------------------------------------------------
  analyzer->addCutStep(S3, "nJet",  0.5, "1", "Step_3");
  //Step4 --------------------------------------------------------------------------
  analyzer->addCutStep(S4, "nbJet30_CSVM", 0.5, "bweight30CSVM", "Step_4");
  analyzer->addCutStep(S4, "nbJet30_CSVT", 0.5, "bweight30CSVT", "Step_4");
  //Step5 --------------------------------------------------------------------------
  analyzer->addCutStep(S5, "addjet1_bDisCSV,addjet1_bDisCSV_rebin", 0.5, "bweight30CSVT", "Step_5","noweight");
  analyzer->addCutStep(S5, "addjet2_bDisCSV,addjet2_bDisCSV_rebin", 0.5, "bweight30CSVT", "Step_5","noweight");
  analyzer->addCutStep(S5, "addjet1_bDisCSV,addjet1_bDisCSV_rebin", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]*bweight30CSVT", "Step_5");
  analyzer->addCutStep(S5, "addjet2_bDisCSV,addjet2_bDisCSV_rebin", 0.5, "jets_bDisCSVweight[csvd_jetid[3]]*bweight30CSVT", "Step_5");

  //QCD invert isolation for base shape
  analyzer->replaceDataBkgCut("QCD", "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0", "ZMass > 12 && lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15 && PairSign < 0");

  //global weight
  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar("puweight*0.94");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*0.95");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*0.96");
  }

  //TTBB weight for DY and QCD samples
  if( decayMode == "ElEl"){
    analyzer->setEventWeight("QCD", "Step_1", 0.311);
    analyzer->setEventWeight("QCD", "Step_2", 0.311);
    analyzer->setEventWeight("QCD", "Step_3", 0.591);
    analyzer->setEventWeight("QCD", "Step_4", 0.077);
    analyzer->setEventWeight("QCD", "Step_5", 0.0587);

    analyzer->setEventWeight("DYll", "Step_1", 1.0);
    analyzer->setEventWeight("DYll", "Step_2", 1.0);
    analyzer->setEventWeight("DYll", "Step_3", 1.410);
    analyzer->setEventWeight("DYll", "Step_4", 1.231);
    analyzer->setEventWeight("DYll", "Step_5", 1.459);

    analyzer->setEventWeight("DYll10To50", "Step_1", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_2", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_3", 1.410);
    analyzer->setEventWeight("DYll10To50", "Step_4", 1.231);
    analyzer->setEventWeight("DYll10To50", "Step_5", 1.459);

  }else if( decayMode == "MuMu") {
    analyzer->setEventWeight("QCD", "Step_1", 0.008);
    analyzer->setEventWeight("QCD", "Step_2", 0.008);
    analyzer->setEventWeight("QCD", "Step_3", 0.016);
    analyzer->setEventWeight("QCD", "Step_4", 0.007);
    analyzer->setEventWeight("QCD", "Step_5", 0.0043);

    analyzer->setEventWeight("DYll", "Step_1", 1.0);
    analyzer->setEventWeight("DYll", "Step_2", 1.0);
    analyzer->setEventWeight("DYll", "Step_3", 1.362);
    analyzer->setEventWeight("DYll", "Step_4", 1.231);
    analyzer->setEventWeight("DYll", "Step_5", 1.128);
 
    analyzer->setEventWeight("DYll10To50", "Step_1", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_2", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_3", 1.362);
    analyzer->setEventWeight("DYll10To50", "Step_4", 1.231);
    analyzer->setEventWeight("DYll10To50", "Step_5", 1.128);

  }else{
    analyzer->setEventWeight("QCD", "Step_1", 0.020);
    analyzer->setEventWeight("QCD", "Step_2", 0.020);
    analyzer->setEventWeight("QCD", "Step_3", 0.002);
    analyzer->setEventWeight("QCD", "Step_4", 0.002);
    analyzer->setEventWeight("QCD", "Step_5", 0.0018);
  }
  
  analyzer->applyCutSteps();
  analyzer->saveHistograms();
  analyzer->printCutFlow();
}

