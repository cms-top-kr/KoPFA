#include <iostream>
using namespace std;

void ana8TeV_uncertainty(){


//  ana("ElEl","TTBB_CSVT/ElEl","puweight","MET > 30","nJet30 >= 4");
//  ana("ElEl","TTBB_CSVT/ElEl","puweight","MET > 30","nJet30 >= 4");
//  ana("ElEl","TTBB_CSVT/ElEl","puweight","MET > 30","nJet30 >= 4");

  ana("ElEl","TTBB_CSVT_METUp/ElEl","puweight","METUp > 30","nJet30Up >= 4");
  ana("MuMu","TTBB_CSVT_METUp/MuMu","puweight","METUp > 30","nJet30Up >= 4");
  ana("MuEl","TTBB_CSVT_METUp/MuEl","puweight","METUp > 30","nJet30Up >= 4");

  ana("MuMu","TTBB_CSVT_METDw/MuMu","puweight","METDw > 30","nJet30Dw >= 4");
  ana("ElEl","TTBB_CSVT_METDw/ElEl","puweight","METDw > 30","nJet30Dw >= 4");
  ana("MuEl","TTBB_CSVT_METDw/MuEl","puweight","METDw > 30","nJet30Dw >= 4");


  ana("MuMu","TTBB_CSVT_puweightplus/MuMu","puweightplus","MET > 30","nJet30 >= 4");
  ana("ElEl","TTBB_CSVT_puweightplus/ElEl","puweightplus","MET > 30","nJet30 >= 4");
  ana("MuEl","TTBB_CSVT_puweightplus/MuEl","puweightplus","MET > 30","nJet30 >= 4");

  ana("MuMu","TTBB_CSVT_puweightminus/MuMu","puweightminus","MET > 30","nJet30 >= 4");
  ana("ElEl","TTBB_CSVT_puweightminus/ElEl","puweightminus","MET > 30","nJet30 >= 4");
  ana("MuEl","TTBB_CSVT_puweightminus/MuEl","puweightminus","MET > 30","nJet30 >= 4");
}

void ana(string decayMode = "ElEl", string imageOutDir = "", TString weight = "", TCut cuts3 = "", TCut cuts4)
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("$CMSSW_BASE/src/KoPFA/CommonTools/macros/TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130406_V00-00-08fixed/";
  const std::string rdPath = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130406_V00-00-08fixed/";

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2012"+decayMode+".root", 19619);

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.5 && abs( genLep2_eta ) < 2.5" ;
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

  bool onlyfinal = true;

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "nbjets", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L ../addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step1 -----------------------------------------------------------------------
  analyzer->addCutStep("ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0", "");

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
    analyzer->addCutStep("", "MET,nJet", 0.5);
  }else{
    analyzer->addCutStep(cuts3, "nJet,MET", 0.5);
  }

  //Step4 ----------------------------------------------------------------------------------------
  analyzer->addCutStep(cuts4, "nJet,MET", 0.1);

  //Step5
  analyzer->addCutStep("nbjets30_CSVT >= 2", "nJet,MET", 0.5);

  //Step6
  analyzer->addCutStep("nbjets30_CSVT >= 2", "addjet1_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]");

//Step7
  analyzer->addCutStep("nbjets30_CSVT >= 2", "addjet2_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[3]]");

  //QCD invert isolation for base shape
  analyzer->replaceDataBkgCut("QCD", "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0", "ZMass > 12 && lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15 && PairSign < 0");

  if( decayMode == "MuMu"){
    analyzer->setEventWeightVar(Form("%s*lepweight*bweight30CSVT", weight.Data()));
  }else if( decayMode == "MuEl"){
    analyzer->setEventWeightVar(Form("%s*lepweight*bweight30CSVT", weight.Data()));
  }else if( decayMode == "ElEl"){
    analyzer->setEventWeightVar(Form("%s*lepweight*bweight30CSVT", weight.Data()));
  }

  //TTBB
  //Full 2012
  const double wDYmm[] = {1.0,  1.02685,1.30272,1.28784,  1.73553,1.73553,1.73553};
  const double wDYee[] = {1.0,  1.0505 ,1.34471,1.36888,  1.87588,1.87588,1.87588};

  //TTBB
  //Full 2012
  const double wQCDee[] = {0.657, 0.657, 0.657, 0.657, 0.657, 0.657, 0.657 };
  const double wQCDmm[] = {0.028, 0.028, 0.028, 0.028, 0.028, 0.028, 0.028 };
  const double wQCDem[] = {0.064, 0.064, 0.064, 0.064, 0.064, 0.064, 0.064 };

  int n = sizeof(wQCDmm)/sizeof(wQCDmm[0]);
  if( decayMode == "MuMu" ){
    analyzer->setEventWeight("DYll10To50", wDYmm, n);
    analyzer->setEventWeight("DYll1", wDYmm, n);
    analyzer->setEventWeight("QCD", wQCDmm, n);
  } else if( decayMode == "ElEl" ) {
    analyzer->setEventWeight("DYll10To50", wDYee, n);
    analyzer->setEventWeight("DYll", wDYee, n);
    analyzer->setEventWeight("QCD", wQCDee, n);
  } else if( decayMode == "MuEl" ) {
    analyzer->setEventWeight("QCD", wQCDem, n);
  }

  analyzer->applyCutSteps();
  
  analyzer->saveHistograms();
  //analyzer->printCutFlow();
}

