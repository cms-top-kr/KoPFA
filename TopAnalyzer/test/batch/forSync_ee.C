#include "TFile.h"
#include <fstream.h>

forSync_ee() {

  ofstream fout; 
  TString decay="ElEl";
//  TString sample="ZJets";
  TString sample="TTbarTuneZ2";
  fout.open(decay+"_"+sample+".txt"); 
//  fout.open(decay+"_"+sample+"_ALL.txt"); 

  TFile* f = TFile::Open("./"+decay+"/vallot_"+sample+".root");
//  TFile* f = TFile::Open("./"+decay+"/vallot_"+sample+"_ALL.root");
  TTree* tree = (TTree*)f->Get("ElEl/tree");

  bool scan=true;
  double step0, step1, step2, step3, step4, step5;
  TCut cut0 = "";
  TCut cut1 = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && pt1 > 20 && pt2 > 20";
  TCut cut2 = cut1 && "abs(ZMass - 91.2) > 15";  
  TCut cut3 = cut2 && "@jetspt30.size() >= 2";  
  TCut cut4 = cut3 && "MET > 30";  
  TCut cut5 = cut4 && "nbjets_CSVL >= 1";  

/*  step0=tree->GetEntries();
  step1=tree->GetEntries("ZMass > 12 && relIso1 < 0.2 && relIso2 < 0.2 && PairSign < 0 && pt1 > 20 && pt2 > 20");
  step2=tree->GetEntries("ZMass > 12 && relIso1 < 0.2 && relIso2 < 0.2 && PairSign < 0 && pt1 > 20 && pt2 > 20 && abs(ZMass - 91.2) > 15");
  step3=tree->GetEntries("ZMass > 12 && relIso1 < 0.2 && relIso2 < 0.2 && PairSign < 0 && pt1 > 20 && pt2 > 20 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 2");
  step4=tree->GetEntries("ZMass > 12 && relIso1 < 0.2 && relIso2 < 0.2 && PairSign < 0 && pt1 > 20 && pt2 > 20 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 2 && MET > 30");
  step5=tree->GetEntries("ZMass > 12 && relIso1 < 0.2 && relIso2 < 0.2 && PairSign < 0 && pt1 > 20 && pt2 > 20 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 2 && MET > 30 && nbjets_CSVL >= 1");
*/
  step0=tree->GetEntries();
  step1=tree->GetEntries(cut1);
  step2=tree->GetEntries(cut2);
  step3=tree->GetEntries(cut3);
  step4=tree->GetEntries(cut4);
  step5=tree->GetEntries(cut5);

  cout << "===================================================================================" << endl;
  cout << "Synchronization Exercise with MC  (Decay channel = "+decay+", Sample = "+sample+") " << endl;
  cout << "===================================================================================" << endl;
  cout << "Cut at step1 ; " << "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && pt1 > 20 && pt2 > 20" << endl;
  cout << "Cut at step2 ; " << "Cut at step1 + && abs(ZMass - 91.2) > 15" << endl;
  cout << "Cut at step3 ; " << "Cut at step2 + && @jetspt30.size() >= 2 " << endl;
  cout << "Cut at step4 ; " << "Cut at step3 + && MET > 30" << endl;
  cout << "Cut at step5 ; " << "Cut at step4 + && nbjets_CSVL >= 1" << endl;
  cout << "===================================================================================" << endl;
  cout << "Step0 = " << step0 << endl; 
  cout << "Step1 = " << step1 << endl; 
  cout << "Step2 = " << step2 << endl; 
  cout << "Step3 = " << step3 << endl; 
  cout << "Step4 = " << step4 << endl; 
  cout << "Step5 = " << step5 << endl; 
  cout << "===================================================================================" << endl;

  if (scan==true) {
    cout << tree->Scan("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET:nbjets_CSVL",cut4) << endl; 
  }

  fout << "===================================================================================" << endl;
  fout << "Synchronization Exercise with MC  (Decay channel = "+decay+", Sample = "+sample+") " << endl;
  fout << "===================================================================================" << endl;
  fout << "Cut at step1 ; " << "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && pt1 > 20 && pt2 > 20" << endl;
  fout << "Cut at step2 ; " << "Cut at step1 + && abs(ZMass - 91.2) > 15" << endl;
  fout << "Cut at step3 ; " << "Cut at step2 + && @jetspt30.size() >= 2 " << endl;
  fout << "Cut at step4 ; " << "Cut at step3 + && MET > 30" << endl;
  fout << "Cut at step5 ; " << "Cut at step4 + && nbjets_CSVL >= 1" << endl;
  fout << "===================================================================================" << endl;
  fout << "Step0 = " << step0 << endl; 
  fout << "Step1 = " << step1 << endl; 
  fout << "Step2 = " << step2 << endl; 
  fout << "Step3 = " << step3 << endl; 
  fout << "Step4 = " << step4 << endl; 
  fout << "Step5 = " << step5 << endl; 
  fout << "===================================================================================" << endl;
  fout << "" << endl;
  fout << "" << endl;

  if (scan==true) {
    const string tmpFileName = decay+"_"+sample+"_tmp.txt";
    ((TTreePlayer*)(tree->GetPlayer()))->SetScanRedirect(true);
    ((TTreePlayer*)(tree->GetPlayer()))->SetScanFileName(tmpFileName.c_str());
    tree->Scan("RUN:LUMI:EVENT:ZMass:@jetspt30.size():MET:pt1:pt2",cut1);
    ((TTreePlayer*)(tree->GetPlayer()))->SetScanRedirect(false);
  }

  fout.close();
}
