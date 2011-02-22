void accept(const TString& decayMode = "MuEl"){
  TFile * f_ttbar_deno = new TFile("/home/tjkim/ntuple/top/genTTbar/ttbarGen.root");
  TTree * t_ttbar_deno = (TTree *) f_ttbar_deno->Get("ttbarGenAna/tree");

  TFile * f_ttbar = new TFile("/home/tjkim/ntuple/top/"+decayMode+"/ntuple_bugfixed/TTbar/vallot_0.root");
  TTree * t_ttbar = (TTree *) f_ttbar->Get(decayMode+"/tree");

  float bins[] = {0,350,400,450,500,550,600,700,800,1400};
  int nBin = sizeof(bins)/sizeof(float) - 1;

  TH1* h_accept = new TH1F("h_accept","h_accept",nBin,bins);
 
  TH1* h_nomi = new TH1F("h_nomi","h_nomi",nBin,bins);
  TH1* h_deno = new TH1F("h_deno","h_deno",nBin,bins);

  TCut cut = "Z.mass() > 12 && Z.sign() < 0 && relIso04lep1 < 0.21 && relIso04lep2 < 0.26 && @jetspt30.size() >= 2";
  t_ttbar->Project("h_nomi","genttbarM",cut);
  t_ttbar_deno->Project("h_deno","tt.M()");

  cout << "total final events = " << t_ttbar->GetEntries() << endl;
  cout << "total       events = " << t_ttbar_deno->GetEntries() << endl;
 
  h_accept->Divide(h_nomi,h_deno);
  TCanvas* c = new TCanvas("c","c",1);
  h_nomi->SetLineColor(2);
  h_deno->SetLineColor(4);
  h_deno->Draw("");
  h_nomi->Draw("Same");

  TCanvas* c_accept = new TCanvas("c_accept","c_accept",1);
  h_accept->SetMarkerSize(1);
  h_accept->SetMarkerStyle(20);
  h_accept->Draw("P");

  for(int i=0 ; i < nBin; i++){
    cout << "acceptance[" << i << "] = " << h_accept->GetBinContent(i+1) << endl; 
  }
}

