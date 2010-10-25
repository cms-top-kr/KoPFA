#include <iostream>
//#include "tdrstyle.C"

using namespace std;

void ana(string decayMode = "MuMu")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode);
  //TopAnalyzerLite* analyzer = new TopAnalyzerLite("topElElAnalyzer");

  const std::string mcPath = "batch/" + decayMode;
  const std::string rdPath = "batch/" + decayMode;

  gROOT->LoadMacro("/afs/cern.ch/cms/slc5_ia32_gcc434/cms/cmssw/CMSSW_3_8_4/bin/slc5_ia32_gcc434/tdrstyle.C");
  //defaultStyle();

  //analyzer->addRealData(rdPath+"/vallot_Run2010A_Sep17ReReco.root", 3.1);
  //analyzer->addRealData(rdPath+"/vallot_Run2010B_PromptReco.root", 4.0);
  analyzer->addRealData(rdPath+"/vallot.root", 7.1);

  analyzer->addMC("TTbar", "t#bar{t}", mcPath+"/vallot_TTbar.root", 157.5, 4);
  analyzer->addMC("Wlnu", "W #rightarrow l#nu", mcPath+"/vallot_WJets.root", 31314, 46);
  analyzer->addMC("VVJets" "Dibosons", "Dibosons", mcPath+"/vallot_VVJets.root", 4.8, 6);
  analyzer->addMC("SingleTop", "Single top", mcPath+"/vallot_SingleTop.root", 10.6, 7);
  analyzer->addMC("Ztautau", "Z/#gamma* #rightarrow #tau#tau", mcPath+"/vallot_Ztautau.root", 1660, 5);

  analyzer->addMC("Zll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_Zmumu.root", 1660, 2);
  analyzer->addMC("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_DYmumu.root", 3457, 2);
  analyzer->addMC("ZJets", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3048, 2);

  analyzer->addMonitorPlot("ZMass", "Z.mass()", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/5 GeV/c^{2}", 40, 0, 200);
  analyzer->addMonitorPlot("nJet", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 5, 0, 5);
  analyzer->addMonitorPlot("MET", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 8, 0, 80);
  analyzer->addMonitorPlot("pt1", "Z.leg1().pt()", "Leading p_{T};p_{T} (GeV/c);Events/2 GeV/c", 20, 0, 100);
  analyzer->addMonitorPlot("eta1", "Z.leg1().eta()", "Leading #eta;#eta (Radian);Events/0.1 rad.", 35, -3.5, 3.5);
  analyzer->addMonitorPlot("phi1", "Z.leg1().phi()", "Leading #phi;#phi (Radian);Events/0.1 rad.", 35, -3.5, 3.5);
  analyzer->addMonitorPlot("pt2", "Z.leg2().pt()", "Leading p_{T};p_{T} (GeV/c);Events/2 GeV/c", 20, 0, 200);
  analyzer->addMonitorPlot("eta2", "Z.leg2().eta()", "Leading #eta;#eta (Radian);Events/0.2 rad.", 35, -3.5, 3.5);
  analyzer->addMonitorPlot("phi2", "Z.leg2().phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5);

  analyzer->addCutStep("Z.mass() > 12", "");//, "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
  analyzer->addCutStep("(chIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+phIso2)/Z.leg2().pt() < 0.21", "");//, "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
  //analyzer->addCutStep("(chIso1+phIso1)/Z.leg1().pt() < 0.15 && (chIso2+phIso2)/Z.leg2().pt() < 0.15", "");//, "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
  analyzer->addCutStep("Z.sign() < 0", "ZMass,nJet,MET,pt1,eta1,phi1,pt2,eta2,phi2");
  analyzer->addCutStep("abs(Z.mass() - 91) > 15", "nJet,MET");
  analyzer->addCutStep("@jetspt30.size() >= 2", "nJet,MET");
  analyzer->addCutStep("MET > 30", "nJet,MET");

  //analyzer->addCutStep("Z.mass() > 12 && (chIso1+phIso1)/Z.leg1().pt() < 0.15 && (chIso2+phIso2)/Z.leg2().pt() < 0.15 && Z.sign() < 0 && abs(Z.mass() - 91) > 15 && @jetspt30.size() >= 2 && MET > 30", "nJet,MET");

  analyzer->applyCutSteps();
}

