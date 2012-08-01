void acceptance3(){
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

  TCut visible = "ttbarGen.diLeptonic() == 1 && ttbarGen.NJets15() >= 4 && ttbarGen.NbJets15() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets15() >= 4";
  //TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt20.size() >=4 && nbjets20_CSVT >= 1";
  //TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt20.size() >=4 && nbjets20_CSVT >= 1";

  //TCut visible = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  //TCut ttbb = "ttbarGen.NbJets20() >= 4";
  TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt30.size() >=4 && nbjets30_CSVM >= 2";
  TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt30.size() >=4 && nbjets30_CSVM >= 2";

  //TCut final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt20.size() >=4 ";
  //TCut final_em= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt20.size() >=4 ";

  TH1F* h_den_ttbb_mm = new TH1F("h_den_ttbb_mm","h_den_ttbb_mm",5,0,5);
  TH1F* h_den_ttbb_ee = new TH1F("h_den_ttbb_ee","h_den_ttbb_ee",5,0,5);
  TH1F* h_den_ttbb_em = new TH1F("h_den_ttbb_em","h_den_ttbb_em",5,0,5);
  TH1F* h_den_ttbb_ll = new TH1F("h_den_ttbb_ll","h_den_ttbb_ll",5,0,5);

  TH1F* h_den_ttjj_mm = new TH1F("h_den_ttjj_mm","h_den_ttjj_mm",5,0,5);
  TH1F* h_den_ttjj_ee = new TH1F("h_den_ttjj_ee","h_den_ttjj_ee",5,0,5);
  TH1F* h_den_ttjj_em = new TH1F("h_den_ttjj_em","h_den_ttjj_em",5,0,5);
  TH1F* h_den_ttjj_ll = new TH1F("h_den_ttjj_ll","h_den_ttjj_ll",5,0,5);

  TH1F* h_num_ttbb_mm = new TH1F("h_num_ttbb_mm","h_num_ttbb_mm",5,0,5);
  TH1F* h_num_ttbb_ee = new TH1F("h_num_ttbb_ee","h_num_ttbb_ee",5,0,5);
  TH1F* h_num_ttbb_em = new TH1F("h_num_ttbb_em","h_num_ttbb_em",5,0,5);
  TH1F* h_num_ttbb_ll = new TH1F("h_num_ttbb_ll","h_num_ttbb_ll",5,0,5);

  TH1F* h_num_ttjj_mm = new TH1F("h_num_ttjj_mm","h_num_ttjj_mm",5,0,5);
  TH1F* h_num_ttjj_ee = new TH1F("h_num_ttjj_ee","h_num_ttjj_ee",5,0,5);
  TH1F* h_num_ttjj_em = new TH1F("h_num_ttjj_em","h_num_ttjj_em",5,0,5);
  TH1F* h_num_ttjj_ll = new TH1F("h_num_ttjj_ll","h_num_ttjj_ll",5,0,5);

  TCut weight = "puweight*bweight30CSVM";

  t_mm->Project("h_den_ttbb_mm","nbjets30_CSVT", weight*(visible + ttbb) );
  t_ee->Project("h_den_ttbb_ee","nbjets30_CSVT", weight*(visible + ttbb) );
  t_em->Project("h_den_ttbb_em","nbjets30_CSVT", weight*(visible + ttbb) );

  t_mm->Project("h_den_ttjj_mm","nbjets30_CSVT", weight*(visible) );
  t_ee->Project("h_den_ttjj_ee","nbjets30_CSVT", weight*(visible) );
  t_em->Project("h_den_ttjj_em","nbjets30_CSVT", weight*(visible) );

  t_mm->Project("h_num_ttbb_mm","nbjets30_CSVT", weight*(visible + ttbb + final) );
  t_ee->Project("h_num_ttbb_ee","nbjets30_CSVT", weight*(visible + ttbb + final) );
  t_em->Project("h_num_ttbb_em","nbjets30_CSVT", weight*(visible + ttbb + final_em) );

  t_mm->Project("h_num_ttjj_mm","nbjets30_CSVT", weight*(visible + final) );
  t_ee->Project("h_num_ttjj_ee","nbjets30_CSVT", weight*(visible + final) );
  t_em->Project("h_num_ttjj_em","nbjets30_CSVT", weight*(visible + final_em) );

  double numTTJJ_mm = h_num_ttjj_mm->Integral() ; 
  double numTTJJ_ee = h_num_ttjj_ee->Integral() ; 
  double numTTJJ_em = h_num_ttjj_em->Integral() ; 
  double numTTJJ = numTTJJ_mm + numTTJJ_ee + numTTJJ_em;
  double denTTJJ_mm = h_den_ttjj_mm->Integral() ; 
  double denTTJJ_ee = h_den_ttjj_ee->Integral() ; 
  double denTTJJ_em = h_den_ttjj_em->Integral() ; 
  double denTTJJ = denTTJJ_mm + denTTJJ_ee + denTTJJ_em;

  double numTTBB_mm = h_num_ttbb_mm->Integral() ;
  double numTTBB_ee = h_num_ttbb_ee->Integral() ;
  double numTTBB_em = h_num_ttbb_em->Integral();
  double numTTBB = numTTBB_mm + numTTBB_ee + numTTBB_em;
  double denTTBB_mm = h_den_ttbb_mm->Integral() ; 
  double denTTBB_ee = h_den_ttbb_ee->Integral() ; 
  double denTTBB_em = h_den_ttbb_em->Integral() ; 
  double denTTBB = denTTBB_mm + denTTBB_ee + denTTBB_em;

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
  cout << "ll : acceptance (TTJJ) " << acceptTTJJ << "(" << numTTJJ << "/" << denTTJJ << ")" << " acceptance (TTBB) = " << acceptTTBB << "(" << numTTBB << "/" << denTTBB << ")" << " ratio = " << ratio << endl;

}
