#include <iostream>
//#include "tdrstyle.C"

using namespace std;

void defaultStyle();

void ana(string decayMode = "MuMu", string imageOutDir = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "batch/" + decayMode;
  const std::string rdPath = "batch/" + decayMode;

  defaultStyle();

  analyzer->addRealData(rdPath+"/vallot_Run2010A_Sep17ReReco.root", 3.1);
  //analyzer->addRealData(rdPath+"/vallot_Run2010A_Sep17ReReco.root", 3.1*1047/2850);
  analyzer->addRealData(rdPath+"/vallot_Run2010B_PromptReco.root", 4.0);
  //analyzer->addRealData(rdPath+"/vallot_Run2010B_PromptReco.root", 4.0*781/3382);
  //analyzer->addRealData(rdPath+"/vallot.root", 7.1);

  analyzer->addMC("TTbar", "t#bar{t}", mcPath+"/vallot_TTbar.root", 157.5, 10000, 4);
  analyzer->addMC("Wlnu", "W #rightarrow l#nu", mcPath+"/vallot_WJets.root", 31314, 500000, 46);
  analyzer->addMC("VVJets" "Dibosons", "Dibosons", mcPath+"/vallot_VVJets.root", 4.8, 10000, 6);
  analyzer->addMC("SingleTop", "Single top", mcPath+"/vallot_SingleTop.root", 10.6, 10000, 7);
  analyzer->addMC("Ztautau", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_Ztautau.root", 1660, 50000, 5);
  analyzer->addMC("ZTauDecay", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_ZtauDecay.root", 3048, 50000, 5);

  if ( decayMode == "MuMu" )
  {
    analyzer->addMC("Zll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zmumu.root", 1660, 50000, 2);
    analyzer->addMC("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYmumu.root", 3457, 100000, 2);
  }
  else if ( decayMode == "ElEl" )
  {
    analyzer->addMC("Zll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zee.root", 1660, 50000, 2);
    analyzer->addMC("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYee.root", 3457, 100000, 2);
  }
  analyzer->addMC("ZJets", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3048, 50000, 2);

  analyzer->addMonitorPlot("ZMass", "Z.mass()", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/5 GeV/c^{2}", 40, 0, 200, 0.1, 1500);
  analyzer->addMonitorPlot("ZMassFinal", "Z.mass()", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/40 GeV/c^{2}", 5, 0, 200, 0.1, 1500);
  analyzer->addMonitorPlot("nJet", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 5, 0, 5, 0.05, 600);
  analyzer->addMonitorPlot("MET", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 8, 0, 80, 0.1, 400);

  analyzer->addMonitorPlot("pt1", "Z.leg1().pt()", "Leading p_{T};p_{T} (GeV/c);Events/2 GeV/c", 20, 0, 100, 0.1, 1500);
  analyzer->addMonitorPlot("pt2", "Z.leg2().pt()", "Leading p_{T};p_{T} (GeV/c);Events/2 GeV/c", 20, 0, 200, 0.1, 1500);
  analyzer->addMonitorPlot("eta1", "Z.leg1().eta()", "Leading #eta;#eta (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 5000);
  analyzer->addMonitorPlot("eta2", "Z.leg2().eta()", "Leading #eta;#eta (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 5000);
  analyzer->addMonitorPlot("phi1", "Z.leg1().phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 5000);
  analyzer->addMonitorPlot("phi2", "Z.leg2().phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 5000);

  analyzer->addMonitorPlot("metPhi", "met[0].phi()", "MET phi", 50, -3.15, 3.15, 0.1, 5000);
  analyzer->addMonitorPlot("dphi1", "asin(sin(Z.leg1().phi()-met[0].phi()))", "Angle diff", 50, -2, 2, 0.1, 5000);
  analyzer->addMonitorPlot("dphi2", "asin(sin(Z.leg2().phi()-met[0].phi()))", "Angle diff", 50, -2, 2, 0.1, 5000);

  //analyzer->addCutStep("Z.mass() > 12", "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2", 1.5);
  analyzer->addCutStep("Z.mass() > 12", "metPhi,dphi1,dphi2", 1.5);
  if ( decayMode == "MuMu" )
  {
    //analyzer->addCutStep("(chIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+phIso2)/Z.leg2().pt() < 0.21", "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
    analyzer->addCutStep("(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.21", "");
  }
  else if ( decayMode == "ElEl" )
  {
    //analyzer->addCutStep("(chIso1+phIso1)/Z.leg1().pt() < 0.15 && (chIso2+phIso2)/Z.leg2().pt() < 0.20", "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
    analyzer->addCutStep("(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.20 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.20", "");
  }
  analyzer->addCutStep("Z.sign() < 0", "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2,dphi1,metPhi");
  analyzer->addCutStep("abs(Z.mass() - 91) > 15", "nJet,MET", 0.5);
  analyzer->addCutStep("@jetspt30.size() >= 2", "MET,ZMassFinal", 0.5);
  analyzer->addCutStep("MET > 30", "nJet,ZMassFinal", 0.5);

  //analyzer->addCutStep("Z.mass() > 12 && (chIso1+phIso1)/Z.leg1().pt() < 0.15 && (chIso2+phIso2)/Z.leg2().pt() < 0.15 && Z.sign() < 0 && abs(Z.mass() - 91) > 15 && @jetspt30.size() >= 2 && MET > 30", "nJet,MET");
:
  analyzer->applyCutSteps();

  TObjArray histograms = analyzer->getHistograms();
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


