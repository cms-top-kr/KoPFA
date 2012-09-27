void ratioMC(){

  getFraction("Out_partonJet","TTbarTuneZ2");
  getFraction("Out_finalstateJet","TTbarTuneZ2");

}



void getFraction(const TString& dir, const TString & path){

  cout << dir.Data() << " : " << path.Data() << endl;

  TFile* f = new TFile(Form("../../TopAnalyzer/test/crabforttbb/%s/%s/vallot_ttbar2b.root",dir.Data(),path.Data()));

  TTree* t = (TTree* ) f->Get("ttbar2bFilter/tree"); 

  TCut vis = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets20() >=4" ;

  //double nTTJJ = t->GetEntries(vis);
  //double nTTBB = t->GetEntries(ttbb);

  t->Draw(">>visentry", vis, "entrylist");
  TEntryList *vislist = (TEntryList *)gDirectory->Get("visentry");
  if (vislist==0) cout << "error!" << endl;
  t->SetEntryList(vislist);
  double nTTJJ = vislist->GetN();

  t->Draw(">>ttbbentry", ttbb, "entrylist");
  TEntryList *ttbblist = (TEntryList *)gDirectory->Get("ttbbentry");
  if (ttbblist==0) cout << "error!" << endl;
  t->SetEntryList(ttbblist);
  double nTTBB = ttbblist->GetN();

  double ratio = nTTBB/nTTJJ;
  double error = sqrt(nTTBB)/nTTJJ;

  cout << "ratio MC(ttbb/ttjj) = " << ratio << "(" << nTTBB << "/" << nTTJJ << ")" << " +- " << error << endl;

}
