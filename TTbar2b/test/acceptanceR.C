
double FrTTDIL = 0;
double FrTTDILVIS = 0;
double FrTTJJ = 0;
double FrTTBB = 0;
double FrTTCC = 0;

double FrTTDILVIS_parton = 0;
double FrTTJJ_parton = 0;
double FrTTBB_parton = 0;

void getFraction(const TString & path){

  TFile* f_ttbar2b = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/v2/vallot_%s.root",path.Data()));

  TH1* h_nGenJet = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJets");
  TH1* h_nGenJetDIL = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJetsDIL");
  TH1* h_nGenJetDILVIS = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJetsDILVIS");
  TH1* h_nGenJet20DILVIS = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJets20DILVIS");
  TH1* h_nGenJet20DILVISTTBB = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJets20DILVISTTBB");
  TH1* h_nGenJet20DILVISTTCC = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_multiplicity_GenJets20DILVISTTCC");
  TH1* h_nEvents = (TH1F*) f_ttbar2b->Get("ttbar2bFilterMuMu/h_nEvents");

  double nTT = h_nGenJet->GetEntries();
  double nTTDIL = h_nGenJetDIL->GetEntries();
  double nTTDILVIS = h_nGenJetDILVIS->GetEntries();
  double nTTBBDILVIS = h_nGenJet20DILVISTTBB->GetEntries();
  double nTTCCDILVIS = h_nGenJet20DILVISTTCC->GetEntries();
  double nTTJJ = nTTDILVIS - h_nGenJet20DILVIS->Integral(1,4);
  double nTTBB = nTTBBDILVIS - h_nGenJet20DILVISTTBB->Integral(1,4);
  double nTTCC = nTTCCDILVIS - h_nGenJet20DILVISTTCC->Integral(1,4);

  cout << "nTT= " << nTT << " nTTDIL= " << nTTDIL << " nTTJJ= " << nTTJJ << " nTTBB= " << nTTBB << " " << endl;

  double Br = 0.049382761;

  FrTTDIL = nTTDIL/nTT;
  FrTTDILVIS = nTTDILVIS/nTTDIL;
  FrTTJJ = nTTJJ/nTTDILVIS;
  FrTTBB = nTTBB/nTTJJ;
  FrTTCC = nTTCC/nTTJJ;

}

void acceptanceR(){

  //getFraction();

  //acceptance("TTbarMCATNLO");
  //acceptance("TTbarTuneZ2");
  acceptance("TTbarFullLepMGDecays");
  //acceptance("TTbarPOWHEG");
  //acceptance("TTbarScaleUp");
  //acceptance("TTbarScaleDw");

}

void acceptance(const TString & path){
  cout << path.Data() << endl;

  getFraction(path);

  TFile* f = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/v2/vallot_%s.root",path.Data()));

  TTree* t_mm = (TTree*) f->Get("MuMu/tree");
  TTree* t_ee = (TTree*) f->Get("ElEl/tree");
  TTree* t_em = (TTree*) f->Get("MuEl/tree");

  TH1* h_event_mm = (TH1F*) f->Get("MuMu/EventSummary");
  double total = h_event_mm->GetBinContent(1);

  TCut cut_em_S1 = "ZMass > 12 && isIso > 0 && PairSign < 0";
  TCut cut_S1 = cut_em_S1;
  
  TCut cut_em_S2 = "ZMass > 12 && isIso > 0 && PairSign < 0";
  TCut cut_S2 = cut_em_S2 + "abs(ZMass-91.2) > 15";
  
  TCut cut_em_S3 = "ZMass > 12 && isIso > 0 && PairSign < 0";
  TCut cut_S3 = cut_em_S3 + "abs(ZMass-91.2) > 15 && MET > 30";
  
  TCut cut_em_S4 = "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >=4";
  TCut cut_S4 = cut_em_S4 + "abs(ZMass-91.2) > 15 && MET > 30";

  TCut cut_em_S5 = "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >=4 && nbjets30_CSVT == 2";
  TCut cut_S5 = cut_em_S5 + "abs(ZMass-91.2) > 15 && MET > 30";

  TCut cut_em_S6 = "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >=4 && nbjets30_CSVT > 2";
  TCut cut_S6 = cut_em_S6 + "abs(ZMass-91.2) > 15 && MET > 30";

  TCut cut_em_S7 = "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >=4 && nbjets30_CSVT == 2 && ( jets[ttbarKin.jid(0)].secvtxMass() > 0 || jets[ttbarKin.jid(1)].secvtxMass() > 0)";
  TCut cut_S7 = cut_em_S7 + "abs(ZMass-91.2) > 15 && MET > 30";

  TCut cut_em_S8 = "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >=4 && nbjets30_CSVT > 2 && ( jets[ttbarKin.jid(0)].secvtxMass() > 0 || jets[ttbarKin.jid(1)].secvtxMass() > 0)";
  TCut cut_S8 = cut_em_S8 + "abs(ZMass-91.2) > 15 && MET > 30";

  //print(t_mm, t_ee, t_em, total, cut_S1, cut_em_S1,"S1");
  //print(t_mm, t_ee, t_em, total, cut_S2, cut_em_S2,"S2");
  //print(t_mm, t_ee, t_em, total, cut_S3, cut_em_S3,"S3");
  //print(t_mm, t_ee, t_em, total, cut_S4, cut_em_S4,"S4");
  //print(t_mm, t_ee, t_em, total, cut_S5, cut_em_S5,"S5");
  //print(t_mm, t_ee, t_em, total, cut_S6, cut_em_S6,"S6");
  print(t_mm, t_ee, t_em, total, cut_S7, cut_em_S7,"S7");
  print(t_mm, t_ee, t_em, total, cut_S8, cut_em_S8,"S8");

}

void print(TTree* t_mm, TTree* t_ee, TTree* t_em, double total, TCut cut, TCut cut_em, const TString & step){

  cout << "CUT: " << step << endl;

  TCut vis = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets20() >= 4";
  TCut ttcc = "ttbarGen.NcJets20() >= 2";

  TCut vis_parton = "ttbarGen.NJets20() >= 4 && ttbarGen.NbQuarks20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb_parton = "ttbarGen.NbQuarks20() >= 4";

  double numTTJJ = t_mm->GetEntries(cut + vis) + t_ee->GetEntries(cut + vis) + t_em->GetEntries(cut_em + vis);
  double preTTJJ = t_mm->GetEntries(vis) + t_ee->GetEntries(vis) + t_em->GetEntries(vis);
  double denTTJJ = total * FrTTDIL * FrTTDILVIS * FrTTJJ;
  double acceptancePreTTJJ =preTTJJ/denTTJJ;
  double acceptancePosTTJJ =numTTJJ/preTTJJ;
  double acceptanceTTJJ =numTTJJ/denTTJJ;

  double numTTBB = t_mm->GetEntries(cut + vis + ttbb) + t_ee->GetEntries(cut + vis + ttbb) + t_em->GetEntries(cut_em + vis + ttbb); 
  double preTTBB = t_mm->GetEntries(vis + ttbb) + t_ee->GetEntries(vis + ttbb) + t_em->GetEntries(vis + ttbb); 
  double denTTBB = total * FrTTDIL * FrTTDILVIS * FrTTJJ * FrTTBB;
  double acceptancePreTTBB = preTTBB / denTTBB; 
  double acceptancePosTTBB = numTTBB / preTTBB; 
  double acceptanceTTBB = numTTBB / denTTBB; 

  double numTTCC = t_mm->GetEntries(cut + vis + ttcc) + t_ee->GetEntries(cut + vis + ttcc) + t_em->GetEntries(cut_em + vis+ ttcc);
  double denTTCC = total * FrTTDIL * FrTTDILVIS * FrTTJJ * FrTTCC;
  double acceptanceTTCC = numTTCC / denTTCC;

  cout << "total= " << total << " den(TTJJ)= " << denTTJJ << " den(TTBB)= " << denTTBB << endl;

  double AccRatio = acceptanceTTJJ/acceptanceTTBB;
  double recoR =  numTTBB/numTTJJ;

  cout << "Ratio (nTTDIL/nTT)   = " << FrTTDIL << endl;
  cout << "Ratio (nTTDILVIS/nTTDIL)   = " << FrTTDILVIS << endl;
  cout << "Ratio (nTTJJ/nTTDILVIS)   = " << FrTTJJ << endl;
  cout << "Ratio (nTTBB/nTTJJ) = " << FrTTBB << endl;
  cout << "Ratio (in reco nTTBB/nTTKK) = " << recoR << endl;
  cout << "acceptance preselection (ttjj)   = " << acceptancePreTTJJ << endl;
  cout << "acceptance preselection (ttbb)   = " << acceptancePreTTBB << endl;
  cout << "acceptance postselection (ttjj)   = " << acceptancePosTTJJ << "(" << numTTJJ << "/" << preTTJJ << ")" << endl;
  cout << "acceptance postselection (ttbb)   = " << acceptancePosTTBB << "(" << numTTBB << "/" << preTTBB << ")" << endl;
  cout << "acceptance (ttjj)   = " << acceptanceTTJJ << endl;
  cout << "acceptance (ttbb)   = " << acceptanceTTBB << endl;
  cout << "acceptance (ttcc)   = " << acceptanceTTCC << "(" << numTTCC << "/" << denTTCC << ")" << endl;
  cout << "Ratio (Attjj/Attbb) = " << AccRatio << endl;

  cout << "total= " << total << " den(TTJJ)= " << denTTJJ << " den(TTBB)= " << denTTBB << endl;

}
