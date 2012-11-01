#include <iostream>
using namespace std;

void ana8TeV(){
  ana("ElEl","TTBB_01Sep2012_CSVT/ElEl");
  ana("MuMu","TTBB_01Sep2012_CSVT/MuMu");
  ana("MuEl","TTBB_01Sep2012_CSVT/MuEl");
}


void ana(string decayMode = "ElEl", string imageOutDir = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121031";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121031/";
 
  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 12000);

  TCut visible = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut sigcut = "ttbarGen.NbJets20() >= 4";
  TCut ttcc = "ttbarGen.NcJets20() >= 2";

  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed+2, true, visible && sigcut);
  analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed+1, visible && !sigcut && ttcc );
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed, visible && !sigcut && !ttcc);

  //analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarOthers.root", 225, kRed-7); 
  analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2.root", 225, kRed-7, !visible); 
  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 36257, kGreen-3); 

  //analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 7.4 , kGray+4);
  //analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 4.51, kGray+4);
  //analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 0.61, kGray+4);

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
  gROOT->ProcessLine(".L addVariables8TeV.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step1 -----------------------------------------------------------------------
  analyzer->addCutStep("ZMass > 12 && lep1.relIso03() < 0.15 && lep2.relIso03() < 0.15 && PairSign < 0", "");

  //Step2 ------------------------------------------------------------------------------------
  if ( decayMode == "MuEl") 
  {
    analyzer->addCutStep("", "nJet", 0.5);
  }else{ 
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", "nJetlog", 0.5);
  }

   //Step3 ---------------------------------------------------------------------------------------------
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("", "nJet", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "nJetlog", 0.5);
  }

  //Step4 ----------------------------------------------------------------------------------------
  analyzer->addCutStep("nJet30 >= 4", "nbJet30_CSVT", 0.1);

  //Step5
  analyzer->addCutStep("nbjets30_CSVT >= 2", "Mbb", 0.5);

  //analyzer->replaceDataBkgCut("QCD", "lep1.relIso03() < 0.15 && lep2.relIso03() < 0.15", "lep1.relIso03() > 0.25 && lep2.relIso03() > 0.25");

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar("puweight*bweight30CSVT");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*bweight30CSVT");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*bweight30CSVT");
  }

  //TTBB
  //Full 2011
  const double wDYmm[] = {1.0,1.0,1.362,1.231,1.128};
  const double wDYee[] = {1.0,1.0,1.410,1.326,1.459};

  //TTBB
  //Full 2011
  const double wQCDee[] = {0.311, 0.311, 0.591, 0.077, 0.0587 };
  const double wQCDmm[] = {0.008, 0.008, 0.016, 0.007, 0.0043 };
  const double wQCDem[] = {0.020, 0.020, 0.020, 0.002, 0.0018 };

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

