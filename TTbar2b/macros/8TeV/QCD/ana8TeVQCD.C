#include <iostream>

using namespace std;

void ana8TeVQCD()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  //for cone size 0.3
  ana("MuMu", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15/MuMu","lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15");
  ana("ElEl", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15_Zveto/ElEl","lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && abs(ZMass-91) > 30");
  ana("MuEl", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15/MuEl","lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15");

  ana("MuMu", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15/MuMu","lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15");
  ana("ElEl", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15_Zveto/ElEl","lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15 && abs(ZMass-91) > 30");
  ana("MuEl", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15/MuEl","lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15");

  //for cone size 0.4 
  ana("MuMu", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_20_cone04/MuMu","lep1_relIso04 < 0.20 && lep2_relIso04 < 0.20");
  ana("ElEl", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_20_cone04_Zveto/ElEl","lep1_relIso04 < 0.20 && lep2_relIso04 < 0.20 && abs(ZMass-91) > 30");
  ana("MuEl", "TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_20_cone04/MuEl","lep1_relIso04 < 0.20 && lep2_relIso04 < 0.20");

  ana("MuMu", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_20_cone04/MuMu","lep1_relIso04 > 0.20 && lep2_relIso04 > 0.20");
  ana("ElEl", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_20_cone04_Zveto/ElEl","lep1_relIso04 > 0.20 && lep2_relIso04 > 0.20 && abs(ZMass-91) > 30");
  ana("MuEl", "TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_20_cone04/MuEl","lep1_relIso04 > 0.20 && lep2_relIso04 > 0.20");

  //before applying cone size
  ana("MuMu", "TOPTTBB_8TeV_QCD_2j1b/MuMu","");
  ana("ElEl", "TOPTTBB_8TeV_QCD_2j1b_Zveto/ElEl","abs(ZMass-91) > 30");
  ana("MuEl", "TOPTTBB_8TeV_QCD_2j1b/MuEl","");

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

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130327_V00-00-08";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130327_V00-00-08";

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 19619);

//  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.5 && abs( genLep2_eta ) < 2.5" ;
//  TCut sigcut = "nGenbJet20 >= 4";
//  TCut ttcc = "nGencJet20 >= 2";
//  TCut dilepton = "ttbarGen_dileptonic == 1";

  //analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarFullLepMGDecays_csvid.root", 23.6196, kRed+2, true, visible && sigcut);
  //analyzer->addMCBkg("TTbarcc", "t#bar{t} + cc", mcPath+"/vallot_TTbarFullLepMGDecays_csvid.root", 23.6196, kRed+1, visible && !sigcut && ttcc );
  //analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarFullLepMGDecays_csvid.root", 23.6196, kRed, visible && !sigcut && !ttcc);

  //analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarFullLepMGDecays_csvid.root", 23.6196, kRed-7, !visible);
  //analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others", mcPath+"/vallot_TTbarTuneZ2_csvid.root", 225, kRed-7, !dilepton);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"/vallot_TTbarTuneZ2.root", 234, kRed+2, true);
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
  analyzer->addCutStep("nJet30 >= 2", "ZMass", 0.5);

  //STEP5 : b-tagging
  analyzer->addCutStep("nbjets30_CSVM >= 1", "ZMass", 0.5);  

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }

  analyzer->applyCutSteps();

  analyzer->saveHistograms();
}
