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

  const std::string mcPath = "/data/cmskr-top/common/Top/ntuple/"+decayMode+"/MC/Summer11/";
  const std::string rdPath = "/data/cmskr-top/common/Top/ntuple/"+decayMode+"/RD/July06/";

  analyzer->addRealData(rdPath+"vallot.root", 1143.221);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"vallot_TTbarTuneZ2.root", 157.5, kRed+1);
  analyzer->addMCBkg("Wl", "W#rightarrowl#nu", mcPath+"vallot_WJetsToLNu.root", 31314, kGreen-3);
  analyzer->addMCBkg("VV", "VV", mcPath+"vallot_ZZ.root", 7.4 , kGray+4);
  analyzer->addMCBkg("WW", "VV", mcPath+"vallot_WW.root", 4.51, kGray+4);
  analyzer->addMCBkg("WZ", "VV", mcPath+"vallot_WZ.root", 0.61, kGray+4);
  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"vallot_SingleToptW.root", 7.87, kMagenta);

  if ( decayMode == "ElEl" )
  {
    analyzer->addMCBkg("QCDPt20to30BCtoE" , "QCD", mcPath+"vallot_QCDPt20to30BCtoE_*.root" , 17.0 , kYellow);
    analyzer->addMCBkg("QCDPt30to80BCtoE" , "QCD", mcPath+"vallot_QCDPt30to80BCtoE_*.root" , 14.6 , kYellow);
    analyzer->addMCBkg("QCDPt80to170BCtoE", "QCD", mcPath+"vallot_QCDPt80to170BCtoE_*.root", 111.5, kYellow);
  }
  else
  {
    analyzer->addMCBkg("QCDPt20MuPt15", "QCD", mcPath+"vallot_QCDPt20MuPt15_*.root", 347.6, kYellow);
  }

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

  if( decayMode == "MuMu" ){
    analyzer->setEventWeightDY(1.0,1.0,1.0,1.04,1.34,1.87,1.51);
  } else if( decayMode == "ElEl" ) {
    analyzer->setEventWeightDY(1.0,1.0,1.0,1.04,1.34,1.91,1.91);
  } else if( decayMode == "MuEl" ) {
    analyzer->setEventWeightDY(1.0,1.0,1.0,1.0,1.0,1.0,1.0);
  }

  //STEP1 : low invariant mass cut
  analyzer->addCutStep("Z.mass() > 12", "", 1.5);

  //STEP2 : isolation
  if ( decayMode == "MuMu" )
  {
    analyzer->addCutStep("Z.leg1().relpfIso03() < 0.20 && Z.leg2().relpfIso03() < 0.20", "");
  }
  else if ( decayMode == "ElEl" )
  {
    analyzer->addCutStep("Z.leg1().relpfIso03() < 0.20 && Z.leg2().relpfIso03() < 0.20", "");
  }
  else if ( decayMode == "MuEl" )
  {
    cout << "DEBUG: MuEl" << endl;
    analyzer->addCutStep("Z.leg1().relpfIso03() < 0.20 && Z.leg2().relpfIso03() < 0.20", "");
  }

  //STEP3 : opposite sign
  analyzer->addCutStep("Z.sign() < 0", "ZMass,nJetlog,METlog");

  //STEP4 : Z veto
  if ( decayMode == "MuEl") 
  {
    analyzer->addCutStep("abs(Z.mass() - 91.2) > -1", "nJetlog,METlog", 0.5);
  }else{
    analyzer->addCutStep("abs(Z.mass() - 91.2) > 15", "nJetlog,METlog", 0.5);
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
  analyzer->addCutStep("@bjets.size() >= 1", "MET,nbJet,vsumM,vsumMAlt,genttbarM", 0.5);  

  //analyzer->setEventWeightVar("weight");

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


