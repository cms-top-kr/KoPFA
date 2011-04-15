#include <iostream>
//#include "tdrstyle.C"

using namespace std;

void defaultStyle();

void ana(string decayMode = "MuMu", string imageOutDir = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  //AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/home/bhlee/ntuple/top/"+decayMode+"/MC/Fall10_Nov4ReReco/";
  const std::string rdPath = "/home/bhlee/ntuple/top/"+decayMode+"/RD/Mar29PromptReco/";


  defaultStyle();

  //analyzer->addRealData(rdPath+"/vallot_Run2010A_Sep17ReReco.root", 3.1);
  //analyzer->addRealData(rdPath+"/vallot_Run2010B_PromptReco.root", 4.0);
  //analyzer->addRealData(rdPath+"/vallot.root", 5.06671);
  analyzer->addRealData(rdPath+"/vallot.root", 19.50160);

  analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"/vallot_TTbar.root", 157.5, 1000000, 4);
  //analyzer->addMCSig("TTbar", "t#bar{t}", mcPath+"/vallot_TTbar_PU.root", 157.5, 1000000, 4);

  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_We.root", 10438, 2500000, 46);
  analyzer->addMCBkg("Wm", "W #rightarrow l#nu", mcPath+"/vallot_Wmu.root", 10438, 2500000, 46);
  analyzer->addMCBkg("Wt", "W #rightarrow l#nu", mcPath+"/vallot_Wtau.root", 10438, 2500000, 46);

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_WW.root", 4.51, 100000, 6);
  analyzer->addMCBkg("ZW", "Dibosons", mcPath+"/vallot_ZW.root", 0.61, 100000, 6);
  analyzer->addMCBkg("ZZ", "Dibosons", mcPath+"/vallot_ZZ.root", 7.40, 100000, 6);
  //analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_WW_PU.root", 4.51, 100000, 6);
  //analyzer->addMCBkg("ZW", "Dibosons", mcPath+"/vallot_ZW_PU.root", 0.61, 100000, 6);
  //analyzer->addMCBkg("ZZ", "Dibosons", mcPath+"/vallot_ZZ_PU.root", 7.40, 100000, 6);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleTop.root", 10.6, 100000, 7);
  //analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleTop_PU.root", 10.6, 100000, 7);

  analyzer->addMCBkg("DYtt", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_DYtautau.root", 3457, 1000000, 5);
  analyzer->addMCBkg("DYtt_20to50", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_Ztautau.root", 1666, 1000000, 5);
  analyzer->addMCBkg("Ztt"        , "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_ZtauDecay.root", 3048, 2500000, 5);
  //analyzer->addMCBkg("DYtt", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_DYtautau_PU.root", 3457, 1000000, 5);
  //analyzer->addMCBkg("DYtt_20to50", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_Ztautau_PU.root", 1666, 1000000, 5);
  //analyzer->addMCBkg("Ztt"        , "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_ZtauDecay_PU.root", 3048, 2500000, 5);

  analyzer->addMCBkg("DYll",  "Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYee.root", 3457, 1000000, 2);
  analyzer->addMCBkg("DYmumu","Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYmumu.root", 3457, 1000000, 2);
  analyzer->addMCBkg("Zee"  , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zee.root", 1666, 1000000, 2);
  analyzer->addMCBkg("Zmumu", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zmumu.root", 1666, 1000000, 2);
  analyzer->addMCBkg("ZJets", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3048, 2500000, 2);
  //analyzer->addMCBkg("DYll",  "Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYee_PU.root", 3457, 1000000, 2);
  //analyzer->addMCBkg("DYmumu","Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYmumu_PU.root", 3457, 1000000, 2);
  //analyzer->addMCBkg("Zee"  , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zee_PU.root", 1666, 1000000, 2);
  //analyzer->addMCBkg("Zmumu", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zmumu_PU.root", 1666, 1000000, 2);
  //analyzer->addMCBkg("ZJets", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets_PU.root", 3048, 2500000, 2);

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //STEP1 : low invariant mass cut
  analyzer->addCutStep("Z.mass() > 12", "", 1.5);

  //STEP2 : isolation
  if ( decayMode == "MuMu" )
  {
    analyzer->addCutStep("(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.21", "");
  }
  else if ( decayMode == "ElEl" )
  {
    analyzer->addCutStep("(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.26 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.26", "");
  }
  else if ( decayMode == "MuEl" )
  {
    cout << "DEBUG: MuEl" << endl;
    analyzer->addCutStep("(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.26", "");
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

  analyzer->applyCutSteps();

  //analyzer->applySingleCut("Z.mass() > 12 && (chIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+phIso2)/Z.leg2().pt() < 0.21 && Z.sign() < 0 && abs(Z.mass() - 91) > 15 && @jetspt30.size() >= 2 && MET > 30", "nJet,MET,ZMass");
  //analyzer->applySingleCut("Z.mass() > 12 && (chIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+phIso2)/Z.leg2().pt() < 0.21 && Z.sign() < 0 && abs(Z.mass() - 91) < 15 && @jetspt30.size() >= 2 && MET > 30", "nJet,MET,ZMass");

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


