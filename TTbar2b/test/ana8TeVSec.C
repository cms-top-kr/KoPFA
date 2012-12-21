#include <iostream>
using namespace std;

void ana8TeVSec(){
  ana("ElEl","TTBB_15Dec2012_CSVT_tag2/ElEl","CSVT");
  ana("MuMu","TTBB_15Dec2012_CSVT_tag2/MuMu","CSVT");
  ana("MuEl","TTBB_15Dec2012_CSVT_tag2/MuEl","CSVT");

  ana("ElEl","TTBB_15Dec2012_CSVTdwlight_tag2/ElEl","CSVTdwlight");
  ana("MuMu","TTBB_15Dec2012_CSVTdwlight_tag2/MuMu","CSVTdwlight");
  ana("MuEl","TTBB_15Dec2012_CSVTdwlight_tag2/MuEl","CSVTdwlight");

  ana("ElEl","TTBB_15Dec2012_CSVTuplight_tag2/ElEl","CSVTuplight");
  ana("MuMu","TTBB_15Dec2012_CSVTuplight_tag2/MuMu","CSVTuplight");
  ana("MuEl","TTBB_15Dec2012_CSVTuplight_tag2/MuEl","CSVTuplight");
}

void ana(string decayMode = "ElEl", string imageOutDir = "", TString weight = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121214_V00-00-04_S5/";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121214_V00-00-04_S5/";
 
  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 12000);

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttcc = "nGencJet20 >= 2";
  TCut dilepton = "diLeptonic() == 1";

  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed+2, true, visible && sigcut);
  analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed+1, visible && !sigcut && ttcc );
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed, visible && !sigcut && !ttcc);

  analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed-7, !visible); 
  analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed-7, !dilepton); 

  //analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed+2, true, visible && sigcut);
  //analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed+1, visible && !sigcut && ttcc );
  //analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed, visible && !sigcut && !ttcc);
  //analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed-7, !visible);

  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 36257, kGreen-3); 

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 7.7 , kGray+4);
  analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 54.8, kGray+4);
  analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 32.3, kGray+4);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleToptW.root", 11.1, kMagenta);
  analyzer->addMCBkg("SingleTopBar", "Single top", mcPath+"/vallot_SingleTopBartW.root", 11.1, kMagenta);
  analyzer->addMCBkg("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3503, kAzure-2);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets10To50.root", 860.5, kAzure-2);
  //analyzer->addMCBkg("DYtt"        , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZtauDecay.root", 3048, kAzure-2);
  //analyzer->addMCBkg("DYtt10To50"        , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZtauDecay10To50.root", 11908.83, kAzure-2);

  //analyzer->addDataBkg("QCD", "QCD", rdPath+"/vallot_Run2012.root", 1.0, kYellow);

  bool onlyfinal = true;

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "nbjets", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariablesNew.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step5
  analyzer->addCutStep("nbjets30_CSVT == 2", "secM1,secM2", 0.5);

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar(Form("puweight*bweight30%s", weight.Data()));
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar(Form("puweight*bweight30%s", weight.Data()));
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar(Form("puweight*bweight30%s", weight.Data()));
  }


  //TTBB
  //Full 2011
  //const double wDYmm[] = {1.0,1.0,1.362,1.231,1.128};
  //const double wDYee[] = {1.0,1.0,1.410,1.326,1.459};

  //TTBB
  //Full 2011
  //const double wQCDee[] = {0.311, 0.311, 0.591, 0.077, 0.0587 };
  //const double wQCDmm[] = {0.008, 0.008, 0.016, 0.007, 0.0043 };
  //const double wQCDem[] = {0.020, 0.020, 0.020, 0.002, 0.0018 };

  int n = sizeof(wQCDmm)/sizeof(wQCDmm[0]);
  //if( decayMode == "MuMu" ){
  //  analyzer->setEventWeight("DYll10To50", wDYmm, n);
  //  analyzer->setEventWeight("DYll1", wDYmm, n);
  //  analyzer->setEventWeight("QCD", wQCDmm, n);
  //} else if( decayMode == "ElEl" ) {
  //  analyzer->setEventWeight("DYll10To50", wDYee, n);
  //  analyzer->setEventWeight("DYll", wDYee, n);
   // analyzer->setEventWeight("QCD", wQCDee, n);
  //} else if( decayMode == "MuEl" ) {
  //  analyzer->setEventWeight("QCD", wQCDem, n);
  //}

  analyzer->applyCutSteps();
  
  analyzer->saveHistograms();
  //analyzer->printCutFlow();
}

