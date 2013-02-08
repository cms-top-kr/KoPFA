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

  const std::string mcPath = "/data/export/common/Top/ntuple/"+decayMode+"/MC/Fall11_v1/";
  const std::string rdPath = "/data/export/common/Top/ntuple/"+decayMode+"/RD/2011Full_v0/";

  analyzer->addRealData(rdPath+"vallot.root", 5000);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"vallot_TTbarTuneZ2.root", 164.6, kRed+1);
  analyzer->addMCBkg("TTbarOthers", "t#bar{t} other", mcPath+"vallot_TTbarOthers.root", 164.6, kRed-7);
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
  analyzer->addMCBkg("DYtt10To50"       , "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_ZtauDecay10To50.root" , 11098.83, kAzure+8);
 // analyzer->addMCBkg("DYtt_10to20", "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_DYtt10to20.root", 3457, kAzure+8);
 // analyzer->addMCBkg("DYtt_20to50", "Z/#gamma*#rightarrow#tau^{+}#tau^{-}", mcPath+"vallot_DYtt20to50.root", 1666, kAzure+8);

  analyzer->addMCBkg("DYll", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_ZJets.root", 3048, kAzure-2);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"/vallot_ZJets10To50.root", 11908.83, kAzure-2);


  if (decayMode == "ElEl")
  {
  //  analyzer->addMCBkg("DYee10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee10to20.root", 3457, kAzure-2);
  //  analyzer->addMCBkg("DYee20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee20to50.root", 1666, kAzure-2);
  }
  else if (decayMode == "MuMu")
  {
  //  analyzer->addMCBkg("DYmm10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm10to20.root", 3457, kAzure-2);
  //  analyzer->addMCBkg("DYmm20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm20to50.root", 1666, kAzure-2);
  }
  else if (decayMode == "MuEl")
  {
   // analyzer->addMCBkg("DYee10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee10to20.root", 3457, kAzure-2);
   // analyzer->addMCBkg("DYee20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYee20to50.root", 1666, kAzure-2);
  //  analyzer->addMCBkg("DYmm10to20", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm10to20.root", 3457, kAzure-2);
  //  analyzer->addMCBkg("DYmm20to50", "Z/#gamma*#rightarrowl^{+}l^{-}", mcPath+"vallot_DYmm20to50.root", 1666, kAzure-2);
  }

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  analyzer->setScanVariables("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET");

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
  analyzer->addCutStep("PairSign < 0", "pt1,pt2,eta1,eta2,jet1pt,jet2pt,jet1eta,jet2eta,nVertex,ZMass,nJetlog,METlog");

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
    analyzer->addCutStep("MET > -999", "nJet,nbJet_CSVL, nbJet_CSVM, nbJet_CVST, vsumM,vsumMAlt", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "nJet,nbJet_CSVL, nbJet_CSVM, nbJet_CVST, vsumM,vsumMAlt", 0.5);
  }

  //STEP7 : b-tagging
  analyzer->addCutStep("nbjets_CSVL >= 1", "MET,nbJet_CSVL,vsumM,vsumMAlt,genttbarM", 0.5);  

  analyzer->setEventWeightVar("weight");
  
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

  analyzer->setEventWeightVar("weight");
  //Full 2011
  const double wDYmm[] = {1.0,1.0,1.0,1.01,1.01,1.66,1.66};
  const double wDYee[] = {1.0,1.0,1.0,0.98,1.01,1.77,1.82};
  //using NLO
  //Full 2011
  const double wQCDee[] = {1.0,1.0,1.6306*0.0695,1.6115*0.0700,1.1924*0.0101,1.1249*0.0305,1.0971*0.0231};
  const double wQCDmm[] = {1.0,1.0,1.0696*0.0068,1.0678*0.0067,1.0222*0.0021,1.0297*0.0067,1.0220*0.0036};
  const double wQCDem[] = {1.0,1.0,1.1775*0.0158,1.1775*0.0158,1.0714*0.0023,1.0714*0.0023,1.0609*0.0021};
  //using 169.9 pb-1
  //const double wQCDee[] = {1.0,1.0,1.6268*0.0694,1.6077*0.0698,1.1881*0.0097,1.0956*0.0280,1.0441*0.0181};
  //const double wQCDmm[] = {1.0,1.0,1.0620*0.0068,1.0605*0.0067,1.0151*0.0021,1.0052*0.0066,0.9954*0.0036};
  //const double wQCDem[] = {1.0,1.0,1.1730*0.0158,1.1730*0.0158,1.0668*0.0022,1.0668*0.0022,1.0550*0.0019};

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


