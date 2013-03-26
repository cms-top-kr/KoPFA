#include <iostream>
using namespace std;

void ana8TeV(){

  ana("ElEl","TTBB_26Mar_CSVT/ElEl","CSVT","nbjets30_CSVT >= 2");
  ana("MuMu","TTBB_26Mar_CSVT/MuMu","CSVT","nbjets30_CSVT >= 2");
  ana("MuEl","TTBB_26Mar_CSVT/MuEl","CSVT","nbjets30_CSVT >= 2");

//systematic plots
//  ana("ElEl","TTBB_26Mar_CSVTdwlight/ElEl","CSVTdwlight","nbjets30_CSVT >= 2");
//  ana("MuMu","TTBB_26Mar_CSVTdwlight/MuMu","CSVTdwlight","nbjets30_CSVT >= 2");
//  ana("MuEl","TTBB_26Mar_CSVTdwlight/MuEl","CSVTdwlight","nbjets30_CSVT >= 2");

//  ana("ElEl","TTBB_26Mar_CSVTuplight/ElEl","CSVTuplight","nbjets30_CSVT >= 2");
//  ana("MuMu","TTBB_26Mar_CSVTuplight/MuMu","CSVTuplight","nbjets30_CSVT >= 2");
//  ana("MuEl","TTBB_26Mar_CSVTuplight/MuEl","CSVTuplight","nbjets30_CSVT >= 2");
/*
  ana("ElEl","TTBB_18Mar_CSVTdw/ElEl","CSVTdw","nbjets30_CSVT >= 2");
  ana("MuMu","TTBB_18Mar_CSVTdw/MuMu","CSVTdw","nbjets30_CSVT >= 2");
  ana("MuEl","TTBB_18Mar_CSVTdw/MuEl","CSVTdw","nbjets30_CSVT >= 2");

  ana("ElEl","TTBB_18Mar_CSVTup/ElEl","CSVTup","nbjets30_CSVT >= 2");
  ana("MuMu","TTBB_18Mar_CSVTup/MuMu","CSVTup","nbjets30_CSVT >= 2");
  ana("MuEl","TTBB_18Mar_CSVTup/MuEl","CSVTup","nbjets30_CSVT >= 2");
*/
}

void ana(string decayMode = "ElEl", string imageOutDir = "", TString weight = "", TCut cut = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130321_V00-00-07/";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130321_V00-00-07/";

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 19619);

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.5 && abs( genLep2_eta ) < 2.5" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttcc = "nGencJet20 >= 2";
  TCut dilepton = "ttbarGen_dileptonic == 1";

  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kBlue+2, true, visible && sigcut);
  analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed+2, visible && !sigcut && ttcc );
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed, visible && !sigcut && !ttcc);

  analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarFullLepMGDecays.root", 23.6196, kRed-7, !visible); 
  analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed-7, !dilepton); 

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
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step1 -----------------------------------------------------------------------
  analyzer->addCutStep("ZMass > 12 && isIso > 0  && PairSign < 0", "");

  //analyzer->addCutStep("ZMass > 12 && isIso > 0  && PairSign < 0", "addjet1_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]*lepweight");

  //Step2 ------------------------------------------------------------------------------------
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("", "", 0.5);
  }else{
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", "", 0.5);
  }

   //Step3 ---------------------------------------------------------------------------------------------
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("", "", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "", 0.5);
  }

  //Step4 ----------------------------------------------------------------------------------------
  //analyzer->addCutStep("nJet30 >= 4", "nbJet30_CSVM,nbJet30_CSVT", 0.1);
  analyzer->addCutStep("nJet30 >= 4", "nbJet30_CSVT", 0.1);

  //Step5
  analyzer->addCutStep(cut, "nbJet30_CSVT,addjet1_bDisCSV,addjet2_bDisCSV", 0.5);

  //Step6
  analyzer->addCutStep(cut, "addjet1_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]");

  //Step7
  analyzer->addCutStep(cut, "addjet2_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[3]]");

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar(Form("puweight*lepweight*bweight30%s", weight.Data()));
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar(Form("puweight*lepweight*bweight30%s", weight.Data()));
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar(Form("puweight*lepweight*bweight30%s", weight.Data()));
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

  //int n = sizeof(wQCDmm)/sizeof(wQCDmm[0]);
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

