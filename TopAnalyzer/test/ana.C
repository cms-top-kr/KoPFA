#include <iostream>
//#include "tdrstyle.C"

using namespace std;

void defaultStyle();

void ana()
{
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");
  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");

  defaultStyle();

  ana("MuMu", "result/MuMu");
  ana("ElEl", "result/ElEl");
  ana("MuEl", "result/MuEl");
}

void ana(string decayMode, string imageOutDir)
{
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/data/export/common/Top/ntuple/"+decayMode+"/MC/Summer11_new/";
  const std::string rdPath = "/data/export/common/Top/ntuple/"+decayMode+"/RD/Oct05/";

  analyzer->addRealData(rdPath+"vallot.root", 1143.221);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"vallot_TTbarTuneZ2.root", 157.5, kRed+1);
  analyzer->addMCBkg("Wl", "W#rightarrowl#nu", mcPath+"vallot_WJetsToLNu.root", 31314, kGreen-3);
  analyzer->addMCBkg("VV", "VV", mcPath+"vallot_ZZ.root", 7.4 , kGray+4);
  analyzer->addMCBkg("WW", "VV", mcPath+"vallot_WW.root", 4.51, kGray+4);
  analyzer->addMCBkg("WZ", "VV", mcPath+"vallot_WZ.root", 0.61, kGray+4);
  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"vallot_SingleToptW.root", 7.87, kMagenta);

  analyzer->addDataBkg("QCD", "QCD", rdPath+"vallot.root", 1.0, kYellow);
/*
  if ( decayMode == "ElEl" )
  {
    analyzer->addMCBkg("QCDPt20to30BCtoE" , "QCD", mcPath+"vallot_QCDPt20to30BCtoE.root" , 17.0 , kYellow);
    analyzer->addMCBkg("QCDPt30to80BCtoE" , "QCD", mcPath+"vallot_QCDPt30to80BCtoE.root" , 14.6 , kYellow);
    analyzer->addMCBkg("QCDPt80to170BCtoE", "QCD", mcPath+"vallot_QCDPt80to170BCtoE.root", 111.5, kYellow);
  }
  else
  {
    analyzer->addMCBkg("QCDPt20MuPt15", "QCD", mcPath+"vallot_QCDPt20MuPt15.root", 347.6, kYellow);
  }
*/

  analyzer->addMCBkg("DYtt"       , "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_ZtauDecay.root" , 3048, kAzure+8);
  analyzer->addMCBkg("DYtt_10to20", "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_DYtt10to20.root", 3457, kAzure+8);
  analyzer->addMCBkg("DYtt_20to50", "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_DYtt20to50.root", 1666, kAzure+8);

  analyzer->addMCBkg("DYll", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_ZJets.root", 3048, kAzure-2);
  if (decayMode == "ElEl")
  {
    analyzer->addMCBkg("DYee10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee10to20.root", 3457, kAzure-2);
    analyzer->addMCBkg("DYee20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee20to50.root", 1666, kAzure-2);
  }
  else if (decayMode == "MuMu")
  {
    analyzer->addMCBkg("DYmm10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm10to20.root", 3457, kAzure-2);
    analyzer->addMCBkg("DYmm20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm20to50.root", 1666, kAzure-2);
  }
  else if (decayMode == "MuEl")
  {
    analyzer->addMCBkg("DYee10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee10to20.root", 3457, kAzure-2);
    analyzer->addMCBkg("DYee20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee20to50.root", 1666, kAzure-2);
    analyzer->addMCBkg("DYmm10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm10to20.root", 3457, kAzure-2);
    analyzer->addMCBkg("DYmm20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm20to50.root", 1666, kAzure-2);
  }

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  analyzer->setScanVariables("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET");

  //STEP1 : low invariant mass cut
  analyzer->addCutStep("ZMass > 12", "", 1.5);

  //STEP2 : isolation
  analyzer->addCutStep("isIso", "");

  //STEP3 : opposite sign
  analyzer->addCutStep("PairSign < 0", "ZMass,nJetlog,METlog");

  //STEP4 : Z veto
  if ( decayMode == "MuEl") 
  {
    analyzer->addCutStep("abs(ZMass - 91.2) > -1", "nJetlog,METlog", 0.5);
  }else{
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", "nJetlog,METlog", 0.5);
  }

  //STEP5 : two jets requirement 
  analyzer->addCutStep("@jetspt30.size() >= 2", "MET", 0.5);

  //STEP6: MET cut
  if ( decayMode == "MuEl")
  {
    analyzer->addCutStep("MET > -999", "nJet,vsumM,vsumMAlt", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "nJet,vsumM,vsumMAlt", 0.5);
  }

  //STEP7 : b-tagging
  analyzer->addCutStep("nbjets >= 1", "MET,nbJet,vsumM,vsumMAlt,genttbarM", 0.5);  

  analyzer->setEventWeightVar("weightin");
  
  if ( decayMode == "MuMu"){
    analyzer->replaceDataBkgCut("QCD", "isIso", "relIso1 > 0.20 && relIso2 > 0.20");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.20");
  }else if( decayMode == "ElEl"){
    analyzer->replaceDataBkgCut("QCD", "isIso", "relIso1 > 0.17 && relIso2 > 0.17");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.17 && relIso2 > 0.17");
  }else if( decayMode == "MuEl"){
    analyzer->replaceDataBkgCut("QCD", "isIso", "relIso1 > 0.20 && relIso2 > 0.17");
    analyzer->replaceDataBkgCut("QCD", "ZMass > 12", "ZMass > 12 && relIso1 > 0.20 && relIso2 > 0.17");
  }

  const double wDYmm[] = {1.0,1.0,1.0,1.02,0.96,1.07,1.20};
  const double wDYee[] = {1.0,1.0,1.0,1.03,1.00,1.22,1.33};
  const double wQCDee[] = {1.0,1.0,1.70*0.1250,1.60*0.0679,1.21*0.0093,1.34*0.0303,1.40*0.0347};
  const double wQCDmm[] = {1.0,1.0,1.08*0.0071,1.08*0.0063,1.03*0.0019,1.03*0.0075,1.01*0.0064};
  const double wQCDem[] = {1.0,1.0,1.18*0.0149,1.18*0.0149,1.07*0.0020,1.07*0.0020,1.06*0.0017};
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
}

void defaultStyle()
{
  gROOT->SetStyle("Plain");
  //gStyle->SetOptStat(1110);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0); //remove statistics box
  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.15);

  gStyle->SetCanvasDefH(400);
  gStyle->SetCanvasDefW(400);

  // For the axis:
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

  // To make 2D contour colorful
  gStyle->SetPalette(1);

  //gStyle->SetOptTitle(0);
  // Margins:
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

  // For the axis titles:
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.1);

  // For the axis labels:
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");

}


