#include <iostream>

using namespace std;

void ana7TeVDY()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  ana("MuMu", "TOPTTBB_DY_IN_0j1b/MuMu","abs(ZMass - 91.2) <= 15");
  ana("ElEl", "TOPTTBB_DY_IN_0j1b/ElEl","abs(ZMass - 91.2) <= 15");
  ana("MuEl", "TOPTTBB_DY_IN_0j1b/MuEl","abs(ZMass - 91.2) <= 15");
  ana("MuMu", "TOPTTBB_DY_Out_0j1b/MuMu","abs(ZMass - 91.2) > 15");
  ana("ElEl", "TOPTTBB_DY_Out_0j1b/ElEl","abs(ZMass - 91.2) > 15");

}

void ana(string decayMode, string imageOutDir = "test", TCut mcut)
{
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");
  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");

  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/t/tjkim/public/store/top/"+decayMode+"/v2/";
  const std::string rdPath = "/afs/cern.ch/work/t/tjkim/public/store/top/"+decayMode+"/v2/";

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
 
  analyzer->addDataBkg("QCD", "QCD", rdPath+"vallot_Run2011.root", 1.0, kYellow);

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //analyzer->setScanVariables("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET");

  //Step1 -----------------------------------------------------------------------
  if ( decayMode == "MuMu" )
  {
    analyzer->addCutStep("ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0", "");
  }
  else if ( decayMode == "ElEl" )
  {
    analyzer->addCutStep("ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0", "");
  }else if ( decayMode == "MuEl" )
  {
    analyzer->addCutStep("ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0", "");
  }

  //STEP2 : Z veto
  analyzer->addCutStep(mcut, "ZMass", 0.5);

  //STEP3: MET cut
  analyzer->addCutStep("MET > 30", "ZMass", 0.5);

  //STEP4 : two jets requirement 
  analyzer->addCutStep("@jetspt30.size() == 0", "ZMass", 0.5);

  //STEP5 : b-tagging
  analyzer->addCutStep("nbjets30_CSVM >= 1", "ZMass", 0.5);  

  if ( decayMode == "MuMu"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.20", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.20");
  }else if( decayMode == "ElEl"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.17 && relIso2 < 0.17", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.17 && relIso2 > 0.17");
  }else if( decayMode == "MuEl"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.17", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.17");
  }

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar("puweight*bweight30CSVM*0.94");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*bweight30CSVM*0.95");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*bweight30CSVM*0.96");
  }

  //using NLO
  //Full 2011
  const double wQCDee[] = {2.3296*0.0959,2.3296*0.0959,2.3296*0.0959,2.3296*0.0959,2.3296*0.0959};
  const double wQCDmm[] = {1.0874*0.0071,1.0874*0.0071,1.0874*0.0071,1.0874*0.0071,1.0874*0.0071};
  const double wQCDem[] = {1.2741*0.0158,1.2741*0.0158,1.2741*0.0158,1.2741*0.0158,1.2741*0.0158};

  int n = sizeof(wQCDmm)/sizeof(wQCDmm[0]);
  if( decayMode == "MuMu" ){
    analyzer->setEventWeight("QCD", wQCDmm, n);
  } else if( decayMode == "ElEl" ) {
    analyzer->setEventWeight("QCD", wQCDee, n);
  } else if( decayMode == "MuEl" ) {
    analyzer->setEventWeight("QCD", wQCDem, n);
  }

  analyzer->applyCutSteps();

  analyzer->saveHistograms();
}
