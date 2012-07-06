void purity(){
  TFile *f = new TFile("note_v4/preUnfolding.root");

  TH2* h2 = (TH2F*) f->Get("h2_response_m");

  //default
  //float detBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins
  //float genBins[] = {0, 345, 400, 450, 500, 550, 600, 680, 800, 1800}; // 9 bins

  //float detBins[] = {0, 345, 400, 450, 510, 600, 700, 800, 1800};//8 bins
  //float genBins[] = {0, 345, 400, 450, 510, 600, 700, 800, 1800};//8 bins
  float detBins[] = {0, 345, 400, 470, 550, 650, 800, 1100, 1600};//8 bins
  float genBins[] = {0, 345, 400, 470, 550, 650, 800, 1100, 1600};//8 bins



  int nDet = sizeof(detBins)/sizeof(float) - 1;
  int nGen = sizeof(genBins)/sizeof(float) - 1;


  TH1* h_stability = new TH1F("h_stability","h_stability",nGen,genBins);
  TH1* h_purity = new TH1F("h_purity","h_purity",nGen,genBins);

  int nbins = 8;

  for(int i = 1 ; i <= nbins ; i++){
    double n_gen = h2->Integral(1,nbins,i,i);
    double n_reco = h2->Integral(i,i,1,nbins);
    double n_gen_reco = h2->Integral(i,i,i,i);
    double stability = n_gen_reco/n_gen;
    double purity = n_gen_reco/n_reco;

    cout << "bin : " << i << " stability= " << stability << " purity= " << purity << endl;
    h_stability->SetBinContent(i, stability);
    h_purity->SetBinContent(i, purity);
  }

  TCanvas * c= new TCanvas("c","c",1);
  //h_stability->Draw();
  h_purity->SetLineColor(2);
  h_purity->Draw();

}
