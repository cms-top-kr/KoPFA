#include <iostream>

using namespace std;

void anaTOP11013()
{

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  ana("MuMu", "TOP11013_08072012/MuMu");
  ana("ElEl", "TOP11013_08072012/ElEl");
  ana("MuEl", "TOP11013_08072012/MuEl");
}

void ana(string decayMode, string imageOutDir = "test")
{
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");
  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");

  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "$WORK/data/export/common/Top/ntuple/"+decayMode+"/MC/Fall11_v9/";
  const std::string rdPath = "$WORK/data/export/common/Top/ntuple/"+decayMode+"/RD/2011Full_v7/";

  analyzer->addRealData(rdPath+"vallot_Run2011.root", 4982);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"vallot_TTbarTuneZ2.root", 165.0, kRed+1);
  analyzer->addMCBkg("TTbarOthers", "t#bar{t} other", mcPath+"vallot_TTbarOthers.root", 165.0, kRed-7);

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

  //STEP1 : low invariant mass cut
  analyzer->addCutStep("ZMass > 12", "Iso03lep1,Iso03lep2", 1.5);

  //STEP2 : isolation
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

  //STEP3 : opposite sign
  analyzer->addCutStep("PairSign < 0", "pt1,pt2,eta1,eta2,jet1pt30,jet2pt30,jet1eta30,jet2eta30,nVertex,ZMass,nJet30log,METlog");

  //STEP4 : Z veto
  if ( decayMode == "MuEl") 
  {
    analyzer->addCutStep("abs(ZMass - 91.2) > -1", "nJet30log,METlog", 0.5);
  }else{
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", "nJet30log,METlog", 0.5);
  }

  //STEP5 : two jets requirement 
  analyzer->addCutStep("@jetspt30.size() >= 2", "MET", 0.5);

  //STEP6: MET cut
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("MET > -999", "nJet30,nbJet30_CSVL", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "nJet30,nbJet30_CSVL", 0.5);
  }

  //STEP7 : b-tagging
  analyzer->addCutStep("nbjets30_CSVL >= 1", "MET,nbJet30_CSVL,vsumM,nVertex", 0.5);  

  //STEP8 : kin. reconstruction
  analyzer->addCutStep("kinttbarM > 0", "kinM,kinMAlt,kinMAltOld,genttbarM,genttbarMOld", 0.5);


  if ( decayMode == "MuMu"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.20", "relIso1 > 0.20 && relIso2 > 0.20");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.20");
  }else if( decayMode == "ElEl"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.17 && relIso2 < 0.17", "relIso1 > 0.17 && relIso2 > 0.17");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.17 && relIso2 > 0.17");
  }else if( decayMode == "MuEl"){
    analyzer->replaceDataBkgCut("QCD", "relIso1 < 0.20 && relIso2 < 0.17", "relIso1 > 0.20 && relIso2 > 0.17");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.17");
  }

  analyzer->setEventWeightVar("bweight30CSVL");

  //Full 2011 using Fall11
  const double wDYmm[] = {1.0,1.0,1.0,0.94,0.91,1.18,1.32,1.32};
  const double wDYee[] = {1.0,1.0,1.0,0.97,0.94,1.24,1.41,1.41};
  //using NLO
  //Full 2011
  const double wQCDee[] = {1.0,1.0,2.3296*0.0959,2.2849*0.0747,1.5285*0.0102,1.7919*0.0339,1.70517*0.02230,1.70517*0.02230};
  const double wQCDmm[] = {1.0,1.0,1.0874*0.0071,1.0899*0.0071,1.0553*0.0025,1.0168*0.0081,1.01157*0.00602,1.01157*0.00602};
  const double wQCDem[] = {1.0,1.0,1.2741*0.0158,1.2741*0.0158,1.1494*0.0020,1.1494*0.0020,1.14127*0.00191,1.14127*0.00191};


  int n = sizeof(wDYmm)/sizeof(wDYmm[0]);
  if( decayMode == "MuMu" ){
    analyzer->setEventWeight("Z/#gamma*#rightarrowl^{+}l^{-}", wDYmm, n);
    analyzer->setEventWeight("QCD", wQCDmm, n);
  } else if( decayMode == "ElEl" ) {
    analyzer->setEventWeight("Z/#gamma*#rightarrowl^{+}l^{-}", wDYee, n);
    analyzer->setEventWeight("QCD", wQCDee, n);
  } else if( decayMode == "MuEl" ) {
    analyzer->setEventWeight("QCD", wQCDem, n);
  }

  analyzer->applyCutSteps();

  analyzer->saveHistograms();
  analyzer->printCutFlow();
}
