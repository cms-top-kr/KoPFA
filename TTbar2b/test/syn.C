void syn(){

  TFile * f_mm = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/paper/v1/vallot_Run2012MuMu.root");
  TFile * f_ee = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/paper/v1/vallot_Run2012ElEl.root");
  TFile * f_em = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/paper/v1/vallot_Run2012MuEl.root");

  TTree * t_mm = (TTree *) f_mm->Get("MuMu/tree");
  TTree * t_ee = (TTree *) f_ee->Get("ElEl/tree");
  TTree * t_em = (TTree *) f_em->Get("MuEl/tree");
 
  TH1F * h_mm = (TH1F *) f_mm->Get("MuMu/EventSummary");
  TH1F * h_ee = (TH1F *) f_ee->Get("ElEl/EventSummary");
  TH1F * h_em = (TH1F *) f_em->Get("MuEl/EventSummary");

  TCut run = "RUN >= 190456 && RUN <=196531";
  //TCut run = "";
 
  TCut step1 = "ZMass > 20 && isIso > 0 && PairSign < 0" + run;
  TCut step2 = "abs(ZMass-91.2) > 15";
  TCut step3 = "nJet30 >= 2";
  TCut step4 = "MET > 40";
  TCut step5 = "nbjets30_CSVL >= 1";

  cout << "step0a" << endl;
  cout << "MuMu = " << h_mm->GetBinContent(1) << endl;
  cout << "ElEl = " << h_ee->GetBinContent(1) << endl;
  cout << "MuEl = " << h_em->GetBinContent(1) << endl;

  cout << "step0b" << endl;
  cout << "MuMu = " << h_mm->GetBinContent(4) << endl;
  cout << "ElEl = " << h_ee->GetBinContent(4) << endl;
  cout << "MuEl = " << h_em->GetBinContent(4) << endl;

  cout << "step0c" << endl;
  cout << "MuMu = " << h_mm->GetBinContent(3) << endl;
  cout << "ElEl = " << h_ee->GetBinContent(3) << endl;
  cout << "MuEl = " << h_em->GetBinContent(3) << endl;

  cout << "step1" << endl;
  cout << "MuMu = " << t_mm->GetEntries(step1) << endl;
  cout << "ElEl = " << t_ee->GetEntries(step1) << endl;
  cout << "MuEl = " << t_em->GetEntries(step1) << endl;

  cout << "step2" << endl;
  cout << "MuMu = " << t_mm->GetEntries(step1 + step2) << endl;
  cout << "ElEl = " << t_ee->GetEntries(step1 + step2) << endl;
  cout << "MuEl = " << t_em->GetEntries(step1) << endl;

  cout << "step3" << endl;
  cout << "MuMu = " << t_mm->GetEntries(step1 + step2 + step3) << endl;
  cout << "ElEl = " << t_ee->GetEntries(step1 + step2 + step3) << endl;
  cout << "MuEl = " << t_em->GetEntries(step1 + step3) << endl;

  cout << "step4" << endl;
  cout << "MuMu = " << t_mm->GetEntries(step1 + step2 + step3 + step4) << endl;
  cout << "ElEl = " << t_ee->GetEntries(step1 + step2 + step3 + step4) << endl;
  cout << "MuEl = " << t_em->GetEntries(step1 + step3) << endl;

  cout << "step5" << endl;
  cout << "MuMu = " << t_mm->GetEntries(step1 + step2 + step3 + step4 + step5) << endl;
  cout << "ElEl = " << t_ee->GetEntries(step1 + step2 + step3 + step4 + step5) << endl;
  cout << "MuEl = " << t_em->GetEntries(step1 + step3 + step5) << endl;
  
}
