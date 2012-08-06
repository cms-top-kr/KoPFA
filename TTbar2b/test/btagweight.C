void btagweight(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TString path = "TTbarTuneZ2";

  TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v1/vallot_%s.root",path.Data()));
  TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v1/vallot_%s.root",path.Data()));
  TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v1/vallot_%s.root",path.Data()));

  TTree * t_MuMu = (TTree*) f_mm->Get("MuMu/tree");
  TTree * t_ElEl = (TTree*) f_ee->Get("ElEl/tree");
  TTree * t_MuEl = (TTree*) f_em->Get("MuEl/tree");

  TCut cut = "ZMass > 12 && abs(ZMass - 91.2) > 15 && PairSign < 0 && isIso > 0 && MET > 30 && @jetspt30.size() >=4";
  TCut cut_em = "ZMass > 12 && abs(ZMass - 91.2) > 15 && PairSign < 0 && isIso > 0 && @jetspt30.size() >=4";

  TCut visible = "ttbarGen.NJets15() >= 4 && ttbarGen.NbJets15() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut sig = "ttbarGen.NbJets15() >= 4";
 
  TH1 * h_nbjets_ttbb_MuMu = new TH1F("h_nbjets_ttbb_MuMu","h_nbjets_ttbb_MuMu",5,0,5);
  TH1 * h_nbjets_ttll_MuMu = new TH1F("h_nbjets_ttll_MuMu","h_nbjets_ttll_MuMu",5,0,5);

  TH1 * h_nbjets_ttbb_ElEl = new TH1F("h_nbjets_ttbb_ElEl","h_nbjets_ttbb_ElEl",5,0,5);
  TH1 * h_nbjets_ttll_ElEl = new TH1F("h_nbjets_ttll_ElEl","h_nbjets_ttll_ElEl",5,0,5);

  TH1 * h_nbjets_ttbb_MuEl = new TH1F("h_nbjets_ttbb_MuEl","h_nbjets_ttbb_MuEl",5,0,5);
  TH1 * h_nbjets_ttll_MuEl = new TH1F("h_nbjets_ttll_MuEl","h_nbjets_ttll_MuEl",5,0,5);

  TH1 * h_nbjets_dwlight_ttbb_MuMu = new TH1F("h_nbjets_dwlight_ttbb_MuMu","h_nbjets_dwlight_ttbb_MuMu",5,0,5);
  TH1 * h_nbjets_dwlight_ttll_MuMu = new TH1F("h_nbjets_dwlight_ttll_MuMu","h_nbjets_dwlight_ttll_MuMu",5,0,5);

  TH1 * h_nbjets_dwlight_ttbb_ElEl = new TH1F("h_nbjets_dwlight_ttbb_ElEl","h_nbjets_dwlight_ttbb_ElEl",5,0,5);
  TH1 * h_nbjets_dwlight_ttll_ElEl = new TH1F("h_nbjets_dwlight_ttll_ElEl","h_nbjets_dwlight_ttll_ElEl",5,0,5);

  TH1 * h_nbjets_dwlight_ttbb_MuEl = new TH1F("h_nbjets_dwlight_ttbb_MuEl","h_nbjets_dwlight_ttbb_MuEl",5,0,5);
  TH1 * h_nbjets_dwlight_ttll_MuEl = new TH1F("h_nbjets_dwlight_ttll_MuEl","h_nbjets_dwlight_ttll_MuEl",5,0,5);

  TH1 * h_nbjets_uplight_ttbb_MuMu = new TH1F("h_nbjets_uplight_ttbb_MuMu","h_nbjets_uplight_ttbb_MuMu",5,0,5);
  TH1 * h_nbjets_uplight_ttll_MuMu = new TH1F("h_nbjets_uplight_ttll_MuMu","h_nbjets_uplight_ttll_MuMu",5,0,5);

  TH1 * h_nbjets_uplight_ttbb_ElEl = new TH1F("h_nbjets_uplight_ttbb_ElEl","h_nbjets_uplight_ttbb_ElEl",5,0,5);
  TH1 * h_nbjets_uplight_ttll_ElEl = new TH1F("h_nbjets_uplight_ttll_ElEl","h_nbjets_uplight_ttll_ElEl",5,0,5);

  TH1 * h_nbjets_uplight_ttbb_MuEl = new TH1F("h_nbjets_uplight_ttbb_MuEl","h_nbjets_uplight_ttbb_MuEl",5,0,5);
  TH1 * h_nbjets_uplight_ttll_MuEl = new TH1F("h_nbjets_uplight_ttll_MuEl","h_nbjets_uplight_ttll_MuEl",5,0,5);

  TH1 * h_nbjets_ttbb = new TH1F("h_nbjets_ttbb","h_nbjets_ttbb",5,0,5);
  TH1 * h_nbjets_ttll = new TH1F("h_nbjets_ttll","h_nbjets_ttll",5,0,5);

  TH1 * h_nbjets_dwlight_ttbb = new TH1F("h_nbjets_dwlight_ttbb","h_nbjets_dwlight_ttbb",5,0,5);
  TH1 * h_nbjets_dwlight_ttll = new TH1F("h_nbjets_dwlight_ttll","h_nbjets_dwlight_ttll",5,0,5);

  TH1 * h_nbjets_uplight_ttbb = new TH1F("h_nbjets_uplight_ttbb","h_nbjets_uplight_ttbb",5,0,5);
  TH1 * h_nbjets_uplight_ttll = new TH1F("h_nbjets_uplight_ttll","h_nbjets_uplight_ttll",5,0,5);


  TCut weight = "puweight*bweight30CSVT";

  t_MuMu->Project("h_nbjets_ttbb_MuMu","nbjets30_CSVT",weight*(visible + sig + cut));
  t_MuMu->Project("h_nbjets_ttll_MuMu","nbjets30_CSVT",weight*(visible + !sig + cut));

  t_ElEl->Project("h_nbjets_ttbb_ElEl","nbjets30_CSVT",weight*(visible + sig + cut));
  t_ElEl->Project("h_nbjets_ttll_ElEl","nbjets30_CSVT",weight*(visible + !sig + cut));

  t_MuEl->Project("h_nbjets_ttbb_MuEl","nbjets30_CSVT",weight*(visible + sig + cut_em));
  t_MuEl->Project("h_nbjets_ttll_MuEl","nbjets30_CSVT",weight*(visible + !sig + cut_em));

  TCut weightdwlight = "puweight*bweight30CSVTdwlight";

  t_MuMu->Project("h_nbjets_dwlight_ttbb_MuMu","nbjets30_CSVT",weightdwlight*(visible + sig + cut));
  t_MuMu->Project("h_nbjets_dwlight_ttll_MuMu","nbjets30_CSVT",weightdwlight*(visible + !sig + cut));

  t_ElEl->Project("h_nbjets_dwlight_ttbb_ElEl","nbjets30_CSVT",weightdwlight*(visible + sig + cut));
  t_ElEl->Project("h_nbjets_dwlight_ttll_ElEl","nbjets30_CSVT",weightdwlight*(visible + !sig + cut));

  t_MuEl->Project("h_nbjets_dwlight_ttbb_MuEl","nbjets30_CSVT",weightdwlight*(visible + sig + cut_em));
  t_MuEl->Project("h_nbjets_dwlight_ttll_MuEl","nbjets30_CSVT",weightdwlight*(visible + !sig + cut_em));

  TCut weightuplight = "puweight*bweight30CSVTuplight";

  t_MuMu->Project("h_nbjets_uplight_ttbb_MuMu","nbjets30_CSVT",weightuplight*(visible + sig + cut));
  t_MuMu->Project("h_nbjets_uplight_ttll_MuMu","nbjets30_CSVT",weightuplight*(visible + !sig + cut));

  t_ElEl->Project("h_nbjets_uplight_ttbb_ElEl","nbjets30_CSVT",weightuplight*(visible + sig + cut));
  t_ElEl->Project("h_nbjets_uplight_ttll_ElEl","nbjets30_CSVT",weightuplight*(visible + !sig + cut));

  t_MuEl->Project("h_nbjets_uplight_ttbb_MuEl","nbjets30_CSVT",weightuplight*(visible + sig + cut_em));
  t_MuEl->Project("h_nbjets_uplight_ttll_MuEl","nbjets30_CSVT",weightuplight*(visible + !sig + cut_em));

  h_nbjets_ttll->Add(h_nbjets_ttll_MuMu);
  h_nbjets_ttll->Add(h_nbjets_ttll_ElEl);
  h_nbjets_ttll->Add(h_nbjets_ttll_MuEl);

  h_nbjets_dwlight_ttll->Add(h_nbjets_dwlight_ttll_MuMu);
  h_nbjets_dwlight_ttll->Add(h_nbjets_dwlight_ttll_ElEl);
  h_nbjets_dwlight_ttll->Add(h_nbjets_dwlight_ttll_MuEl);

  h_nbjets_uplight_ttll->Add(h_nbjets_uplight_ttll_MuMu);
  h_nbjets_uplight_ttll->Add(h_nbjets_uplight_ttll_ElEl);
  h_nbjets_uplight_ttll->Add(h_nbjets_uplight_ttll_MuEl);

  TCanvas * c = new TCanvas("c","c",1);
  h_nbjets_dwlight_ttll->SetLineWidth(2);
  h_nbjets_uplight_ttll->SetLineWidth(2);
  h_nbjets_ttll->SetLineWidth(2);
  h_nbjets_dwlight_ttll->SetLineColor(2);
  h_nbjets_uplight_ttll->SetLineColor(4);
  h_nbjets_uplight_ttll->SetTitle("");
  h_nbjets_uplight_ttll->Draw();
  h_nbjets_dwlight_ttll->Draw("same");
  h_nbjets_ttll->Draw("same");
  debugPrint(h_nbjets_ttll, h_nbjets_dwlight_ttll, h_nbjets_uplight_ttll);

  TLegend *l = new TLegend(0.75,0.62,0.92,0.88);
  l->AddEntry(h_nbjets_uplight_ttll,"tt + ll Up","L");
  l->AddEntry(h_nbjets_ttll,"tt + ll","L");
  l->AddEntry(h_nbjets_dwlight_ttll,"tt + ll Dw","L");

  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();


  c->Print("lightSFvariation_CSVT.eps");

}

void debugPrint(TH1* h, TH1* hdw, TH1* hup){
  for(int i=1; i <= 5; i++){
    double tag = h->GetBinContent(i);      
    double tagdw = hdw->GetBinContent(i);      
    double tagup = hup->GetBinContent(i);      
    double ratiodw = (tagdw-tag)/tag;
    double ratioup = (tagup-tag)/tag;
    cout << "tag[" << i << "] = " << tag << " tagdw = " << tagdw << "[" << ratiodw << "]" << " tagup = " << tagup << "[" << ratioup << "]" << endl;
  } 
}
