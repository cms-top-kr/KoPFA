#include <iostream>

using namespace std;

void ana7TeVQCD()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  ana("MuMu", "TOPTTBB_QCD_iso_2j1b_fixiso_25/MuMu","relIso1 < 0.20 && relIso2 < 0.20");
  ana("ElEl", "TOPTTBB_QCD_iso_2j1b_fixiso_25/ElEl","relIso1 < 0.17 && relIso2 < 0.17");
  ana("MuEl", "TOPTTBB_QCD_iso_2j1b_fixiso_25/MuEl","relIso1 < 0.20 && relIso2 < 0.17");

  ana("MuMu", "TOPTTBB_QCD_noiso_2j1b_fixiso_25/MuMu","relIso1 > 0.25 && relIso2 > 0.25");
  ana("ElEl", "TOPTTBB_QCD_noiso_2j1b_fixiso_25/ElEl","relIso1 > 0.25 && relIso2 > 0.25");
  ana("MuEl", "TOPTTBB_QCD_noiso_2j1b_fixiso_25/MuEl","relIso1 > 0.25 && relIso2 > 0.25");

  ana("MuMu", "TOPTTBB_QCD_2j1b_fixiso_25/MuMu","");
  ana("ElEl", "TOPTTBB_QCD_2j1b_fixiso_25/ElEl","");
  ana("MuEl", "TOPTTBB_QCD_2j1b_fixiso_25/MuEl","");

}

void ana(string decayMode, string imageOutDir = "test", TCut isoCut)
{
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");
  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");

  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/t/tjkim/public/store/top/"+decayMode+"/v1/";
  const std::string rdPath = "/afs/cern.ch/work/t/tjkim/public/store/top/"+decayMode+"/v0/";

  analyzer->addRealData(rdPath+"vallot_Run2011.root", 4982);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"vallot_TTbarTuneZ2.root", 165.6, kRed+1);
  analyzer->addMCBkg("TTbarOthers", "t#bar{t} other", mcPath+"vallot_TTbarOthers.root", 165.6, kRed-7);

  analyzer->addMCBkg("Wl", "W#rightarrowl#nu", mcPath+"vallot_WJetsToLNu.root", 31314, kGreen-3);

  analyzer->addMCBkg("VV", "VV", mcPath+"vallot_ZZ.root", 7.4 , kGray+4);
  analyzer->addMCBkg("WW", "VV", mcPath+"vallot_WW.root", 4.51, kGray+4);
  analyzer->addMCBkg("WZ", "VV", mcPath+"vallot_WZ.root", 0.61, kGray+4);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"vallot_SingleToptW.root", 15.74, kMagenta);

  analyzer->addMCBkg("DYtt"       , "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_ZtauDecay.root" , 3048, kAzure+8 );
  analyzer->addMCBkg("DYtt10To50"       , "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_ZtauDecay10To50.root" , 11098.83, kAzure+8);

  analyzer->addMCBkg("DYll", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_ZJets.root", 3048, kAzure-2);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_ZJets10To50.root", 11908.83, kAzure-2);
 
  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //analyzer->setScanVariables("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET");

  //STEP0
  analyzer->addCutStep(isoCut, "ZMass");

  //STEP1:
  analyzer->addCutStep("ZMass > 12 && PairSign > 0", "ZMass");

  //STEP2:
  //We will treat Step2 z mass veto same as Step1;

  //STEP3: MET cut
  if(decayMode == "MuEl") analyzer->addCutStep("MET > 0", "ZMass", 0.5);
  else analyzer->addCutStep("MET > 30", "ZMass", 0.5);

  //STEP4 : two jets requirement 
  analyzer->addCutStep("@jetspt30.size() >= 2", "ZMass", 0.5);

  //STEP5 : b-tagging
  analyzer->addCutStep("nbjets30_CSVM >= 1", "ZMass", 0.5);  

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar("puweight*0.94");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*0.95");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*0.96");
  }

  analyzer->applyCutSteps();

  analyzer->saveHistograms();
}
