void acceptance(){

  //TFile* f_ttbar2b = new TFile("vallot_ttbar2b.root");
  TString path = "TTbarTuneZ2";

  TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v1/vallot_%s.root",path.Data()));
  TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v1/vallot_%s.root",path.Data()));
  TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v1/vallot_%s.root",path.Data()));

  //TFile* f_ttbar2b = new TFile("../../TopAnalyzer/test/crabforttbb/result/vallot_ttbar2b.root");
  TFile* f_ttbar2b = new TFile("../../TopAnalyzer/test/crabforttbb/vallot_ttbar2b.root");

  TH1* h_nGenJet = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJets");
  TH1* h_nGenJetDIL = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJetsDIL");
  TH1* h_nGenJetDILVIS = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJetsDILVIS");
  TH1* h_nGenJet15DILVIS = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJets15DILVIS");
  TH1* h_nGenJet15DILVISTTBB = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJets15DILVISTTBB");
  TH1* h_nGenJet15DILVISTTCC = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_multiplicity_GenJets15DILVISTTCC");
  TH1* h_nEvents = (TH1F*) f_ttbar2b->Get("ttbar2bFilter/h_nEvents");

  double nTT = h_nGenJet->GetEntries();
  double nTTDIL = h_nGenJetDIL->GetEntries();
  double nTTDILVIS = h_nGenJetDILVIS->GetEntries();
  double nTTBBDILVIS = h_nGenJet15DILVISTTBB->GetEntries();
  double nTTCCDILVIS = h_nGenJet15DILVISTTCC->GetEntries();
  double nTTJJ = nTTDILVIS - h_nGenJet15DILVIS->Integral(1,4);
  double nTTBB = nTTBBDILVIS - h_nGenJet15DILVISTTBB->Integral(1,4);
  double nTTCC = nTTCCDILVIS - h_nGenJet15DILVISTTCC->Integral(1,4);

  cout << nTT << " " << nTTDIL << " " << nTTJJ << " " << nTTBB << " " << endl; 
  TTree* t_mm = (TTree*) f_mm->Get("MuMu/tree");
  TH1* h_event_mm = (TH1F*) f_mm->Get("MuMu/EventSummary");
  TTree* t_ee = (TTree*) f_ee->Get("ElEl/tree");
  TH1* h_event_ee = (TH1F*) f_ee->Get("ElEl/EventSummary");
  TTree* t_em = (TTree*) f_em->Get("MuEl/tree");
  TH1* h_event_em = (TH1F*) f_em->Get("MuEl/EventSummary");

  //double nTT = t->GetEntries(); 
  //double nTTJJ = t->GetEntries("ttbarGen.NJets20() >= 4");
  //double nTTBB = t->GetEntries("ttbarGen.NJets20() >= 4 && ttbarGen.NbQuarks() >= 4");
  
  double total = h_event_mm->GetBinContent(1);

  double Br = 0.049382761;

  double FrTTDIL = nTTDIL/nTT;
  double FrTTDILVIS = nTTDILVIS/nTTDIL;
  double FrTTJJ = nTTJJ/nTTDILVIS; 
  double FrTTBB = nTTBB/nTTJJ; 
  double FrTTCC = nTTCC/nTTJJ; 

  TCut vis = "ttbarGen.NJets15() >= 4 && ttbarGen.NbJets15() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut cut = "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt30.size() >=4 && nbjets30_CSVM >= 2";
  TCut cut_em = "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt30.size() >=4 && nbjets30_CSVM >= 2";

  TCut ttbb = "ttbarGen.NbJets15() >= 4";
  TCut ttcc = "ttbarGen.NcJets15() >= 2";

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

  cout << "MuMu= " << t_mm->GetEntries(cut + vis) << " ElEl= " << t_ee->GetEntries(cut + vis) << " MuEl= " << t_em->GetEntries(cut_em + vis) << endl;
  cout << "total= " << total << " den(TTJJ)= " << denTTJJ << " den(TTBB)= " << denTTBB << endl;

  double AccRatio = acceptanceTTJJ/acceptanceTTBB;

  cout << "Ratio (nTTDIL/nTT)   = " << FrTTDIL << endl;
  cout << "Ratio (nTTDILVIS/nTTDIL)   = " << FrTTDILVIS << endl;
  cout << "Ratio (nTTJJ/nTTDILVIS)   = " << FrTTJJ << endl;
  cout << "Ratio (nTTBB/nTTJJ) = " << FrTTBB << endl;
  cout << "acceptance preselection (ttjj)   = " << acceptancePreTTJJ << endl;
  cout << "acceptance preselection (ttbb)   = " << acceptancePreTTBB << endl;
  cout << "acceptance postselection (ttjj)   = " << acceptancePosTTJJ << "(" << numTTJJ << "/" << preTTJJ << ")" << endl;
  cout << "acceptance postselection (ttbb)   = " << acceptancePosTTBB << "(" << numTTBB << "/" << preTTBB << ")" << endl;
  cout << "acceptance (ttjj)   = " << acceptanceTTJJ << endl;
  cout << "acceptance (ttbb)   = " << acceptanceTTBB << endl;
  cout << "acceptance (ttcc)   = " << acceptanceTTCC << "(" << numTTCC << "/" << denTTCC << ")" << endl;
  cout << "Ratio (Attjj/Attbb) = " << AccRatio << endl;


}
