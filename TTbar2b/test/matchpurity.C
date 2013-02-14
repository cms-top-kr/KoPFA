void matchpurity(){

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.5 && abs( genLep2_eta ) < 2.5" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttcc = "nGencJet20 >= 2";
  TCut dilepton = "ttbarGen_dileptonic == 1";

  cout << "ttbb" << endl;
  print(visible + sigcut);
  cout << "ttjj" << endl;
  print("");


}

void print(TCut process){
  TFile* f = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130208_V00-00-06/vallot_TTbarFullLepMGDecays.root");

  TTree* treeMuMu = (TTree*)f->Get("MuMu/tree");
  TTree* treeElEl = (TTree*)f->Get("ElEl/tree");
  TTree* treeMuEl = (TTree*)f->Get("MuEl/tree");

  TCut eventcutem = process + "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >= 4 && nbjets30_CSVT >= 2";
  TCut eventcut = eventcutem + "MET > 30 && abs(ZMass-91) > 15"; 

  TCut matchKin = "jets_fromtop[kin_jetid[0]] == 1 && jets_fromtop[kin_jetid[1]] == 1";
  TCut matchCSV = "jets_fromtop[csvd_jetid[0]] == 1 && jets_fromtop[csvd_jetid[1]] == 1";

  double totalMuMu = treeMuMu->GetEntries(eventcut);
  double totalMuEl = treeMuEl->GetEntries(eventcut);
  double totalElEl = treeElEl->GetEntries(eventcut);

  double matchedKinMuMu = treeMuMu->GetEntries(eventcut + matchKin);
  double matchedKinMuEl = treeMuEl->GetEntries(eventcut + matchKin);
  double matchedKinElEl = treeElEl->GetEntries(eventcut + matchKin);

  double matchedCSVMuMu = treeMuMu->GetEntries(eventcut + matchCSV);
  double matchedCSVMuEl = treeMuEl->GetEntries(eventcut + matchCSV);
  double matchedCSVElEl = treeElEl->GetEntries(eventcut + matchCSV);

  double purityKin = (matchedKinMuMu + matchedKinMuEl + matchedKinElEl) / (totalMuMu + totalMuEl + totalElEl);

  double purityKinMuMu = matchedKinMuMu / totalMuMu;
  double purityKinMuEl = matchedKinMuEl / totalMuEl;
  double purityKinElEl = matchedKinElEl / totalElEl;

  double purityCSVMuMu = matchedCSVMuMu / totalMuMu;
  double purityCSVMuEl = matchedCSVMuEl / totalMuEl;
  double purityCSVElEl = matchedCSVElEl / totalElEl;

  double purityCSV = (matchedCSVMuMu + matchedCSVMuEl + matchedCSVElEl) / (totalMuMu + totalMuEl + totalElEl);

  cout << "purity kin solution" << endl;
  cout << "MuMu = " << purityKinMuMu << endl; 
  cout << "MuEl = " << purityKinMuEl << endl; 
  cout << "ElEl = " << purityKinElEl << endl; 
  cout << "Total = " << purityKin << endl; 

  cout << "purity csv solution" << endl;
  cout << "MuMu = " << purityCSVMuMu << endl;
  cout << "MuEl = " << purityCSVMuEl << endl;
  cout << "ElEl = " << purityCSVElEl << endl;
  cout << "Total = " << purityCSV << endl;

}

