#include <iostream>
using namespace std;

void ana8TeV(){

  ana("ElEl2Mu","TopMass/ElEl2Mu","CSVM","nbjets30_CSVM >= 1");
  ana("ElEl2El","TopMass/ElEl2El","CSVM","nbjets30_CSVM >= 1");
  ana("MuMu2Mu","TopMass/MuMu2Mu","CSVM","nbjets30_CSVM >= 1");
  ana("MuMu2El","TopMass/MuMu2El","CSVM","nbjets30_CSVM >= 1");
  ana("MuEl2Mu","TopMass/MuEl2Mu","CSVM","nbjets30_CSVM >= 1");
  ana("MuEl2El","TopMass/MuEl2El","CSVM","nbjets30_CSVM >= 1");

}

void ana(string decayMode = "ElEl2Mu", string imageOutDir = "", TString weight = "", TCut cut = "")
{
  gSystem->Load("libFWCoreFWLite.so");
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("libPhysicsToolsRooStatsCms.so");

  AutoLibraryLoader::enable();

  gSystem->CompileMacro("TopAnalyzerLite.cc", "k");
  TopAnalyzerLite* analyzer = new TopAnalyzerLite(decayMode, imageOutDir);

  const std::string mcPath = "/pnfs/user/geonmo/CMSSW_5_3_12_patch1/src/KoPFA/CMGAnalyzer/prod/Out/ZJets/Res/"; //Out_Lsigma_rereco"; //Out_2pfmuptFrac"; //Out_2pfmu"; //Out_1softmulxy";
  //const std::string rdPath = "/afs/cern.ch/work/j/jkim/537_V00-00-09/CMGTools/CMSSW_5_3_7_patch4/src/KoPFA/CMGAnalyzer/prod/Out_2el_rereco"; //Out_2pfmuptFrac";//Out_2pfmu"; //Out_1softmulxy";

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  if(decayMode == "MuMu2Mu" || decayMode == "MuMu2El"){
    analyzer->addRealData(rdPath+"/vallot_Run2012MuMu_rereco.root", 19619);
    cout<<"Run2012MuMu Data input" <<endl;
  }

  if(decayMode == "ElEl2Mu" || decayMode == "ElEl2El"){
    analyzer->addRealData(rdPath+"/vallot_Run2012ElEl_rereco.root", 19619);
    cout<<"Run2012ElEl Data input" <<endl;
  }

  if(decayMode == "MuEl2Mu" || decayMode == "MuEl2El"){
    analyzer->addRealData(rdPath+"/vallot_Run2012MuEl_rereco.root", 19619);
    cout<<"Run2012MuEG Data input" <<endl;
  }

  TCut dilepton = "ttbarGen_dileptonic == 1";

  analyzer->addMCSig("TTbar", "t#bar{t} (MG)", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kRed, true);
  //analyzer->addMCSig("TTbar", "t#bar{t} (MG)", mcPath+"/vallot_TTbarFullLepMGDecays.root", 25.8, kRed, true); //LYON
  //analyzer->addMCSig("TTbarSL", "t#bar{t}(SL)", mcPath+"/vallot_TTbarSemiLeptMGDecays.root", 104, kSpring-8, true, visible);
  //analyzer->addMCSig("TTbarFH", "t#bar{t}(FH)", mcPath+"/vallot_TTbarHadronicMGDecays.root", 104, kBlue, true, visible);
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_158.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_163.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_167.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_170.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_171.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_172.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_173.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_174.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_175.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_176.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_177.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_179.root", 0.2337, 46, true);//LYON
/////  analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_183.root", 0.2337, 46, true);//LYON
  //analyzer->addMCSig("TTbarPY", "t#bar{t}(PYTHIA6)", mcPath+"/vallot_FullttbarPythia6_wptFrac_188.root", 0.2337, 46, true);//LYON

  //analyzer->addMCBkg("TTbarOthers", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kTeal-6, !dilepton); 
  //analyzer->addMCBkg("TTbarNonvis", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarFullLepMGDecays.root", 26, kTeal-6, !dilepton); 
  //analyzer->addMCBkg("TTbarOthersSL", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarSemiLeptMGDecays.root", 104, kTeal-6, !dilepton);
  analyzer->addMCBkg("TTbarOthersSL", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarSemiLeptMGDecays.root", 107.7, kTeal-6, !dilepton); //LYON
  //analyzer->addMCBkg("TTbarNonvisSL", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarSemiLeptMGDecays.root", 104, kTeal-6, !dilepton);
  //analyzer->addMCBkg("TTbarOthersFH", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarHadronicMGDecays.root", 104, kTeal-6, !dilepton);
  analyzer->addMCBkg("TTbarOthersFH", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarHadronicMGDecays.root", 112.3, kTeal-6, !dilepton); //LYON
  //analyzer->addMCBkg("TTbarNonvisFH", "t#bar{t} others (MG)", mcPath+"/vallot_TTbarHadronicMGDecays.root", 104, kTeal-6, !dilepton);
/////  analyzer->addMCBkg("TTbarOthersPY", "t#bar{t} others (PYTHIA6)", mcPath+"/vallot_FullttbarPythia6.root", 0.2337, kTeal-6, !dilepton); //LYON
  //analyzer->addMCBkg("TTbarNonvisPY", "t#bar{t} others (PYTHIA6)", mcPath+"/vallot_FullttbarPythia6.root", 0.2337, kTeal-6, !dilepton);

  analyzer->addMCBkg("Wl", "W #rightarrow l#nu", mcPath+"/vallot_WJetsToLNu.root", 37509, kGray+4); 

  analyzer->addMCBkg("VV", "Dibosons", mcPath+"/vallot_ZZ.root", 8.1 , kYellow-7);
  analyzer->addMCBkg("WW", "Dibosons", mcPath+"/vallot_WW.root", 54.8, kYellow-7);
  analyzer->addMCBkg("WZ", "Dibosons", mcPath+"/vallot_WZ.root", 33.2, kYellow-7);

  analyzer->addMCBkg("SingleTop", "Single top", mcPath+"/vallot_SingleToptW.root", 11.1, 28);
  analyzer->addMCBkg("SingleTopBar", "Single top", mcPath+"/vallot_SingleTopBartW.root", 11.1, 28);
  analyzer->addMCBkg("DYll", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets.root", 3503, kAzure+10);
  analyzer->addMCBkg("DYll10To50", "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZJets10To50.root", 860, kAzure+10);
  //analyzer->addMCBkg("DYtt"        , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZtauDecay.root", 3048, 28);
  //analyzer->addMCBkg("DYtt10To50"        , "Z/#gamma* #rightarrow ll", mcPath+"/vallot_ZtauDecay10To50.root", 11908.83, 28);

  //analyzer->addDataBkg("QCD", "QCD", rdPath+"/vallot_Run2012.root", 1.0, kYellow);

  bool onlyfinal = true;

  //addMonitorPlot
  //analyzer->addMonitorPlot("nbJet", "nbjets", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  //use common histogram names for top analysis
  gROOT->ProcessLine(".L addVariables.h");
  addTopVariables(analyzer); //add Top analysis related variables for plotting

  //Step1 iso, pair sign -----------------------------------------------------------------------
  analyzer->addCutStep(/*"ZMass > 12 &&*/ "isIso > 0  && PairSign < 0",/*"Iso03lep1,Iso03lep2,ZMass,JPsidlPV,JPsiJetMinDPhi,JPsiJetMinDR,pt1,pt2,eta1,eta2,jetspt30,nJet,JPsiMass,JPsiPt,JPsiEta,LepJPsidPhilower,LepJPsidRlower,METlog,nVertex,LepJPsiMass1,LepJPsiMass2""pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,ZMass"*/"");// "nJetlog");

  //analyzer->addCutStep("ZMass > 12 && isIso > 0  && PairSign < 0", "addjet1_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]*lepweight");

  //Step2  Z veto ------------------------------------------------------------------------------------
  if ( decayMode == "MuEl2Mu" || decayMode == "MuEl2El")
  {
    analyzer->addCutStep("", /*"Iso03lep1,Iso03lep2,ZMass,JPsidlPV,JPsiJetMinDPhi,JPsiJetMinDR,pt1,pt2,eta1,eta2,jetspt30,nJet,JPsiMass,JPsiPt,JPsiEta,LepJPsidPhilower,LepJPsidRlower,METlog,nVertex,LepJPsiMass1,LepJPsiMass2""ZMass"*/"", 0.5);
  }else{
    analyzer->addCutStep("abs(ZMass - 91.2) > 15", /*"Iso03lep1,Iso03lep2,ZMass,JPsidlPV,JPsiJetMinDPhi,JPsiJetMinDR,pt1,pt2,eta1,eta2,jetspt30,nJet,JPsiMass,JPsiPt,JPsiEta,LepJPsidPhilower,LepJPsidRlower,METlog,nVertex,LepJPsiMass1,LepJPsiMass2""ZMass"*/"", 0.5);
  }

 //Step3 Met ---------------------------------------------------------------------------------------------
/*  if ( decayMode == "MuEl2Mu" || decayMode == "MuEl2El")
 {
    analyzer->addCutStep("", "JPsiMassFull,MET,nJetlog5,nbJet30_CSVM", 0.5);
  }else{
    analyzer->addCutStep("MET > 30", "JPsiMassFull,MET,nJetlog5,nbJet30_CSVM", 0.5);
  }
*/

  //Step3 Jet ----------------------------------------------------------------------------------------
  //analyzer->addCutStep("nJet30 >= 4", "nbJet30_CSVM,nbJet30_CSVT", 0.1);
  analyzer->addCutStep("nJet30 >= 1", /*"Iso03lep1,Iso03lep2,ZMass,JPsidlPV,JPsiJetMinDPhi,JPsiJetMinDR,pt1,pt2,eta1,eta2,jetspt30,nJet,JPsiMass,JPsiPt,JPsiEta,LepJPsidPhilower,LepJPsidRlower,METlog,nVertex,LepJPsiMass1,LepJPsiMass2"nJetlog5"*/"", 0.1);

  //TCut JPsiCut = "nJPsiCand > 0 && JPsiPairSign < 0 && abs(lep3_eta) < 2.4 && abs(lep4_eta) < 2.4 && lep3_pt>4 && lep4_pt>4  && JPsidlPV <2 && JPsivProb> 0.001 && JPsiMass > 0.0 && JPsiMass < 10.0 && JPsiJetMinDR<0.9";
  //TCut JPsiCut = "nJPsiCand > 0 && JPsiPairSign < 0 && abs(lep3_eta) < 2.4 && abs(lep4_eta) < 2.4 && lep3_pt>4 && lep4_pt>4  && JPsidlPV > 0.02 && JPsidlPV <2 && JPsivProb> 0.001 && JPsiMass > 0.0 && JPsiMass < 10.0 && JPsiJetMinDR<0.9";
  //TCut JPsiCut = "nJPsiCand > 0 && JPsiPairSign < 0 && abs(lep3_eta) < 2.4 && abs(lep4_eta) < 2.4 && lep3_pt>4 && lep4_pt>4  && JPsidlErrPV >0.1 && JPsivProb> 0.001 && JPsiMass > 0.0 && JPsiMass < 10.0 && JPsiJetMinDR<0.9";
  TCut JPsiMuMuCut = "nJPsiCand > 0 &&JPsiPairSign > -9 && JPsiPairSign < 0 && abs(lep3_eta) < 2.4 && abs(lep4_eta) < 2.4 && lep3_pt>4 && lep4_pt>4 && JPsiMass > 3.0 && JPsiMass < 3.2 && JPsiJetMinDR<0.5 && JPsidlPV <2";
  TCut JPsiElElCut = "nJPsiCand > 0 &&JPsiPairSign > -9 && JPsiPairSign < 0 && abs(lep3_eta) < 2.4 && abs(lep4_eta) < 2.4 && lep3_pt>4 && lep4_pt>4 && JPsiMass > 3.0 && JPsiMass < 3.2 && JPsiJetMinDR<0.5 && JPsidlPV <2";

 //Step4 JPsi 
  if ( decayMode == "ElEl2Mu" || decayMode == "MuEl2Mu" || decayMode == "MuMu2Mu")
  {
     analyzer->addCutStep(JPsiMuMuCut,/*"JPsivProb,JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers"*/"", 0.5);

  }else if ( decayMode == "ElEl2El" || decayMode == "MuEl2El" || decayMode == "MuMu2El") {
   
     analyzer->addCutStep(JPsiElElCut,/*"JPsivProb,JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers"*/"", 0.5);
  }

  //analyzer->addCutStep("nJPsiCand > 0 && JPsiPairSign < 0 && JPsiMass > 0.0 && JPsiMass < 7.0","JPsiMassFull,LepJPsiMass1,LepJPsiMass2,ZMass,pt1,pt2,pt3,pt4,eta1,eta2,eta3,eta4,nbJet30_CSVM,nbJet30_CSVT,jet1pt30,jet1eta30,jets_pt[1],jets_eta[1],nJetlog5", 0.5);

 //Step5 JPsi Vertex probability
 if ( decayMode == "ElEl2Mu" || decayMode == "MuEl2Mu" || decayMode == "MuMu2Mu")
 {
    analyzer->addCutStep("JPsivProb > 0.001 && nLepJPsiCand1>0 && nLepJPsiCand2>0",/*"pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,ZMass,nJetlog5,JPsivProb,JPsidlPVZoom,JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,JPsiMassFull02,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers,LepJPsiMass1,LepJPsiMass2,LepJPsidPhilower,LepJPsidPhibigger,LepJPsidRlower,LepJPsidRbigger,LepJPsidThetalower,LepJPsidThetabigger,nJPsiCand,nLepJPsiCand1,nLepJPsiCand2"*/"JPsiMass,LepJPsiMass1,LepJPsiMass2",0.5);
  }else if ( decayMode == "ElEl2El" || decayMode == "MuEl2El" || decayMode == "MuMu2El") {
    analyzer->addCutStep("nLepJPsiCand1>0 && nLepJPsiCand2>0",/*"pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,ZMass,nJetlog5,JPsivProb,JPsidlPVZoom,JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,JPsiMassFull02,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers,LepJPsiMass1,LepJPsiMass2,LepJPsidPhilower,LepJPsidPhibigger,LepJPsidRlower,LepJPsidRbigger,LepJPsidThetalower,LepJPsidThetabigger,nJPsiCand,nLepJPsiCand1,nLepJPsiCand2"*/"JPsiMass,LepJPsiMass1,LepJPsiMass2",0.5);
  }

  //analyzer->addCutStep("JPsidlPV > 0.0 && JPsidlPV <= 0.1", "JPsidlPVZoom");
 
 //Step6 JPsi L>0.02
  //analyzer->addCutStep("JPsidlErrPV > 0.1","JPsivProb,JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers",0.5);
  //analyzer->addCutStep("JPsidlPV > 0.02","JPsivProb,JPsidlPV,JPsidlPVZoom,JPsidlErrPV,JPsiJetMinDR,JPsiMass,JPsiMassFull02,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers",0.5);

 //Step7 JPsi Fit
 // analyzer->addCutStep("JPsiMass > 2.8 && JPsiMass < 3.4","JPsiMassFit");

 //Step8 JPsimass
 //analyzer->addCutStep("JPsiMass > 3.0 && JPsiMass < 3.2","JPsidlPV,JPsidlErrPV,JPsiJetMinDR,JPsiMass,ssJPsiMass,JPsiPt,JPsiEta,JPsiJetDPtFrac,JPsiJetJPsiPtFrac,lep3_pixlayers,lep4_pixlayers", 0.5);
 //analyzer->addCutStep("JPsiMass > 3.0 && JPsiMass < 3.2","Iso03lep1,Iso03lep2,ZMass,JPsidlPV,JPsiJetMinDPhi,JPsiJetMinDR,pt1,pt2,eta1,eta2,jetspt30,nJet,JPsiMass,JPsiPt,JPsiEta,LepJPsidPhilower,LepJPsidRlower,METlog,nVertex,LepJPsiMass1,LepJPsiMass2", 0.5);

  //Step7 JPsiPV
  //analyzer->addCutStep("JPsidlPV > 0.0 && JPsidlPV <= 0.1", "JPsidlPVZoom");

  //Step7 JPsi mass Step5
//    analyzer->addCutStep("JPsiMass >3.0 && JPsiMass < 3.2","JPsiMass,LepJPsiMass1,LepJPsiMass2,ZMass,pt1,pt2,pt3,pt4,eta1,eta2,eta3,eta4,nbJet30_CSVM,jet1pt30,jet1eta30,jet2pt30,jet2eta30,Iso03lep1,Iso03lep2,nVertex,nJetlog5"/*"JPsiMass,LepJPsiMass1,LepJPsiMass2"*/, 0.5);

  //Step6 bjet
/*  analyzer->addCutStep(cut, "JPsiMassFull,LepJPsiMass1,LepJPsiMass2,ZMass,pt1,pt2,pt3,pt4,eta1,eta2,eta3,eta4,nbJet30_CSVM,jet1pt30,jet1eta30,jet2pt30,jet2eta30,Iso03lep1,Iso03lep2,nVertex,nJetlog5", 0.5);*/

 TCut lowerAng1 = "LepJPsidR1<LepJPsidR2"; //"LepJPsidPhi1<LepJPsidPhi2";
 TCut lowerAng2 = "LepJPsidR2<LepJPsidR1"; //"LepJPsidPhi2<LepJPsidPhi1";

  //Step6  lower angle Lep+ JPsi
  //analyzer->addCutStep(lowerAng1,"JPsiMass,LepJPsiMass1,LepJPsiMass2,nJPsiCand,nLepJPsiCand1,nLepJPsiCand2",0.5);
  analyzer->addCutStep(lowerAng2,"JPsiMass,LepJPsiMass1,LepJPsiMass2,nJPsiCand,nLepJPsiCand1,nLepJPsiCand2",0.5);

  //analyzer->addCutStep(cut, "addjet2_bDisJP", 0.5);
  //analyzer->addCutStep("JPsiMass > 3.0 && JPsiMass < 3.2","nbJet30_CSVM,nJetlog5,JPsiMassFull,LepJPsiMass1,LepJPsiMass2",0.5);
 
  if( decayMode == "MuMu2Mu"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "MuMu2El"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "MuEl2Mu"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "MuEl2El"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "ElEl2Mu"){
    analyzer->setEventWeightVar("puweight*lepweight");
  }else if( decayMode == "ElEl2El"){
    analyzer->setEventWeightVar("puweight*lepweight");    
  } 


  analyzer->applyCutSteps();
  
  analyzer->saveHistograms();
  //analyzer->printCutFlow();
}

