void acceptance2(){
  getAcceptance("TTbarTuneZ2");
  getAcceptance("TTbarPOWHEG");
  getAcceptance("TTbarMCATNLO");
  getAcceptance("TTbarScaleUp");
  getAcceptance("TTbarScaleDw");
  getAcceptance("TTbarMatchingUp");
  getAcceptance("TTbarMatchingDw");
}

void getAcceptance(TString path="TTbarTuneZ2"){
 
  cout << path << endl;

  TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v1/vallot_%s.root",path.Data()));
  TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v1/vallot_%s.root",path.Data()));
  TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v1/vallot_%s.root",path.Data()));

  TTree* t_mm = (TTree*) f_mm->Get("MuMu/tree");
  TTree* t_ee = (TTree*) f_ee->Get("ElEl/tree");
  TTree* t_em = (TTree*) f_em->Get("MuEl/tree");

  TCut visible = "ttbarGen.NJets15() >= 4 && ttbarGen.NbJets15() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets15() >= 4";
  //TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt20.size() >=4 && nbjets20_CSVT >= 1";
  //TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt20.size() >=4 && nbjets20_CSVT >= 1";

  //TCut visible = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  //TCut ttbb = "ttbarGen.NbJets20() >= 4";
  TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt30.size() >=4 && nbjets30_CSVM >= 1";
  TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt30.size() >=4 && nbjets30_CSVM >= 1";

  //TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt20.size() >=4 ";
  //TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt20.size() >=4 ";

  double numTTJJ_mm = t_mm->GetEntries( visible + final ) ;
  double numTTJJ_ee = t_ee->GetEntries( visible + final ) ;
  double numTTJJ_em = t_em->GetEntries( visible + final_em );
  double numTTJJ = numTTJJ_mm + numTTJJ_ee + numTTJJ_em;
  double denTTJJ_mm = t_mm->GetEntries( visible );
  double denTTJJ_ee = t_ee->GetEntries( visible );
  double denTTJJ_em = t_em->GetEntries( visible );
  double denTTJJ = denTTJJ_mm + denTTJJ_ee + numTTJJ_em;

  double numTTBB_mm = t_mm->GetEntries( visible + ttbb + final ) ;
  double numTTBB_ee = t_ee->GetEntries( visible + ttbb + final ) ;
  double numTTBB_em = t_em->GetEntries( visible + ttbb + final_em );
  double numTTBB = numTTBB_mm + numTTBB_ee + numTTBB_em;
  double denTTBB_mm = t_mm->GetEntries( visible + ttbb );
  double denTTBB_ee = t_ee->GetEntries( visible + ttbb );
  double denTTBB_em = t_em->GetEntries( visible + ttbb );
  double denTTBB = denTTBB_mm + denTTBB_ee + numTTBB_em;

  double acceptTTJJ_mm = numTTJJ_mm/denTTJJ;
  double acceptTTBB_mm = numTTBB_mm/denTTBB;
  double acceptTTJJ_ee = numTTJJ_ee/denTTJJ;
  double acceptTTBB_ee = numTTBB_ee/denTTBB;
  double acceptTTJJ_em = numTTJJ_em/denTTJJ;
  double acceptTTBB_em = numTTBB_em/denTTBB;

  double acceptTTJJ = numTTJJ/denTTJJ;
  double acceptTTBB = numTTBB/denTTBB;

  double ratio_mm = acceptTTJJ_mm/acceptTTBB_mm;
  double ratio_ee = acceptTTJJ_ee/acceptTTBB_ee;
  double ratio_em = acceptTTJJ_em/acceptTTBB_em;
  double ratio = acceptTTJJ/acceptTTBB;

  cout << "mm : acceptance (TTJJ) " << acceptTTJJ_mm << " acceptance (TTBB) = " << acceptTTBB_mm << " ratio = " << ratio_mm << endl;
  cout << "ee : acceptance (TTJJ) " << acceptTTJJ_ee << " acceptance (TTBB) = " << acceptTTBB_ee << " ratio = " << ratio_ee << endl;
  cout << "em : acceptance (TTJJ) " << acceptTTJJ_em << " acceptance (TTBB) = " << acceptTTBB_em << " ratio = " << ratio_em << endl;
  cout << "ll : acceptance (TTJJ) " << acceptTTJJ << " acceptance (TTBB) = " << acceptTTBB << " ratio = " << ratio << endl;

}
