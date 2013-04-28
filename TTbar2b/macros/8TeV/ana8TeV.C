#include <iostream>
#include <map>
#include "TCut.h"
#include "TROOT.h"
#include "TSystem.h"

using namespace std;

void ana8TeV(){

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

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130406_V00-00-08fixed/";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130406_V00-00-08fixed/";

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 19619);

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.4 && abs( genLep2_eta ) < 2.4" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttcc = "nGencJet20 >= 2";
  TCut dilepton = "ttbarGen_dileptonic == 1";

  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kBlue+2, true, visible && sigcut);
  analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kRed+2, visible && !sigcut && ttcc );
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kRed, visible && !sigcut && !ttcc);

  analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kRed-7, !visible);
  analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed-7, !dilepton);

  //when you use inclusive sample
  //analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed+2, true, visible && sigcut);
  //analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed+1, visible && !sigcut && ttcc );
  //analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed, visible && !sigcut && !ttcc);
  //analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed-7, !visible);

  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 37509, kGreen-3);

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 8.059 , kGray+4);
  analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 54.8, kGray+4);
  analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 33.21, kGray+4);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleToptW.root", 11.1, kMagenta);
  analyzer->addMCBkg("SingleTopBar", "Single top", mcPath+"/vallot_SingleTopBartW.root", 11.1, kMagenta);
  analyzer->addMCBkg("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3503, kAzure-2);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets10To50.root", 860.5, kAzure-2);

  analyzer->addDataBkg("QCD", "QCD", rdPath+"/vallot_Run2012"+decayMode+".root", 1.0, kYellow);

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
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }

  //TTBB weight for DY and QCD samples
  if( decayMode == "ElEl"){
    analyzer->setEventWeight("QCD", "Step_1", 0.657);
    analyzer->setEventWeight("QCD", "Step_2", 0.657);
    analyzer->setEventWeight("QCD", "Step_3", 0.657);
    analyzer->setEventWeight("QCD", "Step_4", 0.657);
    analyzer->setEventWeight("QCD", "Step_5", 0.657);

    analyzer->setEventWeight("DYll", "Step_1", 1.0);
    analyzer->setEventWeight("DYll", "Step_2", 1.0505);
    analyzer->setEventWeight("DYll", "Step_3", 1.34471);
    analyzer->setEventWeight("DYll", "Step_4", 1.36888);
    analyzer->setEventWeight("DYll", "Step_5", 1.87588);

    analyzer->setEventWeight("DYll10To50", "Step_1", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_2", 1.0505);
    analyzer->setEventWeight("DYll10To50", "Step_3", 1.34471);
    analyzer->setEventWeight("DYll10To50", "Step_4", 1.36888);
    analyzer->setEventWeight("DYll10To50", "Step_5", 1.87588);

  }else if( decayMode == "MuMu") {
    analyzer->setEventWeight("QCD", "Step_1", 0.028);
    analyzer->setEventWeight("QCD", "Step_2", 0.028);
    analyzer->setEventWeight("QCD", "Step_3", 0.028);
    analyzer->setEventWeight("QCD", "Step_4", 0.028);
    analyzer->setEventWeight("QCD", "Step_5", 0.028);

    analyzer->setEventWeight("DYll", "Step_1", 1.0);
    analyzer->setEventWeight("DYll", "Step_2", 1.02685);
    analyzer->setEventWeight("DYll", "Step_3", 1.30272);
    analyzer->setEventWeight("DYll", "Step_4", 1.28784);
    analyzer->setEventWeight("DYll", "Step_5", 1.173553);
 
    analyzer->setEventWeight("DYll10To50", "Step_1", 1.0);
    analyzer->setEventWeight("DYll10To50", "Step_2", 1.02685);
    analyzer->setEventWeight("DYll10To50", "Step_3", 1.30272);
    analyzer->setEventWeight("DYll10To50", "Step_4", 1.28784);
    analyzer->setEventWeight("DYll10To50", "Step_5", 1.73553);

  }else{
    analyzer->setEventWeight("QCD", "Step_1", 0.064);
    analyzer->setEventWeight("QCD", "Step_2", 0.064);
    analyzer->setEventWeight("QCD", "Step_3", 0.064);
    analyzer->setEventWeight("QCD", "Step_4", 0.064);
    analyzer->setEventWeight("QCD", "Step_5", 0.064);
  }

  analyzer->applyCutSteps();
  analyzer->saveHistograms();
  analyzer->printCutFlow();
}

