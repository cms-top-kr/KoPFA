#include <iostream>
using namespace std;

void ana(){
  ana("ElEl","ElEl_ttbb_v0");
  ana("MuMu","MuMu_ttbb_v0");
  ana("MuEl","MuEl_ttbb_v0");
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

  const std::string mcPath = "$WORK/data/export/common/Top/ntuple/"+decayMode+"/MC/Fall11_v4/";
  const std::string rdPath = "$WORK/data/export/common/Top/ntuple/"+decayMode+"/RD/2011Full_v2/";

  analyzer->addRealData(rdPath+"/vallot.root", 4982);

  analyzer->addMCSig("TTbarbb", "t#bar{t} + bb", mcPath+"/vallot_TTbarTuneZ2_ttbb.root", 161.9, kRed+1);
  analyzer->addMCBkg("TTbarll", "t#bar{t} + ll", mcPath+"/vallot_TTbarTuneZ2_ttll.root", 161.9, kRed);
  analyzer->addMCBkg("TTbarOthers", "t#bar{t} others", mcPath+"/vallot_TTbarOthers.root", 161.9, kRed-7); 
  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 31314, kGreen-3); 

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 7.4 , kGray+4);
  analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 4.51, kGray+4);
  analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 0.61, kGray+4);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleToptW.root", 15.74, kMagenta);
  analyzer->addMCBkg("DYtt"        , "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_ZtauDecay.root", 3048, kAzure+8);
  analyzer->addMCBkg("DYtt10To50"        , "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_ZtauDecay10To50.root", 11908.83, kAzure+8);
  analyzer->addMCBkg("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3048, kAzure-2); 
  analyzer->addMCBkg("DYll10To50", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets10To50.root", 11908.83, kAzure-2);

  analyzer->addDataBkg("QCD", "QCD", rdPath+"/vallot.root", 1.0, kYellow);

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "nbjets", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step1 -----------------------------------------------------------------------
  analyzer->addCutStep("ZMass > 12", "Iso03lep1,Iso03lep2", 1.5);

  //Step2 -----------------------------------------------------------------------
  if ( decayMode == "MuMu" )
  {
    analyzer->addCutStep("relIso1 < 0.20 && relIso2 < 0.20", "");
  }
  else if ( decayMode == "ElEl" )
  {
    analyzer->addCutStep("relIso1 < 0.17 && relIso2 < 0.17", "");
  }else if ( decayMode == "MuEl" )
  {
    analyzer->addCutStep("relIso1 < 0.20 && relIso2 < 0.17", "");
  }

  //Step3 -------------------------------------------------------------------------------------
  analyzer->addCutStep("PairSign < 0", "ZMass,nJetlog,METlog,pt1,pt2,eta1,eta2,jet1pt,jet2pt,jet1eta,jet2eta,nVertex");

  //Step4 ------------------------------------------------------------------------------------
  if ( decayMode == "MuEl") 
  {
    analyzer->addCutStep("abs(ZMass - 91.2) > -1", "nJetlog,METlog", 0.5);
  }else{ 
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", "nJetlog,METlog", 0.5);
  }

   //Step5 ---------------------------------------------------------------------------------------------
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("MET > -1", "nJet", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "nJet", 0.5);
  }

  //Step6 ----------------------------------------------------------------------------------------
  analyzer->addCutStep("@jetspt20.size() >= 4", "MET,nbJet_CSVL,nbJet_CSVM,nbJet_CSVT,jet1pt,jet2pt,jet3pt,jet4pt", 0.5);

  //Step7 ----------------------------------------------------------------------------------------------
  analyzer->addCutStep("nbjets_CSVL >= 2", "nJet,MET", 0.5);

  if ( decayMode == "MuMu"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.20", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.25 && relIso2 > 0.25");
  }else if( decayMode == "ElEl"){ 
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.17 && relIso2 < 0.17", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.25 && relIso2 > 0.25");
  }else if( decayMode == "MuEl"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.17", "relIso1 > 0.25 && relIso2 > 0.25");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.25 && relIso2 > 0.25");
  }

  analyzer->setEventWeightVar("weight");
  //Full 2011
  const double wDYmm[] = {1.0,1.0,1.0,0.94,0.91,1.18,1.32};
  const double wDYee[] = {1.0,1.0,1.0,0.97,0.94,1.24,1.41};
  //using NLO
  //Full 2011
  const double wQCDee[] = {1.0,1.0,2.3296*0.0959,2.2849*0.0747,1.5285*0.0102,1.7919*0.0339,1.70517*0.02230};
  const double wQCDmm[] = {1.0,1.0,1.0874*0.0071,1.0899*0.0071,1.0553*0.0025,1.0168*0.0081,1.01157*0.00602};
  const double wQCDem[] = {1.0,1.0,1.2741*0.0158,1.2741*0.0158,1.1494*0.0020,1.1494*0.0020,1.14127*0.00191};

  int n = sizeof(wDYmm)/sizeof(wDYmm[0]);
  if( decayMode == "MuMu" ){
    analyzer->setEventWeight("Z/#gamma* #rightarrow ll", wDYmm, n);
    analyzer->setEventWeight("QCD", wQCDmm, n);
  } else if( decayMode == "ElEl" ) {
    analyzer->setEventWeight("Z/#gamma* #rightarrow ll", wDYee, n);
    analyzer->setEventWeight("QCD", wQCDee, n);
  } else if( decayMode == "MuEl" ) {
    analyzer->setEventWeight("QCD", wQCDem, n);
  }

  analyzer->applyCutSteps();
  
  analyzer->saveHistograms();
  analyzer->printCutFlow();
}

