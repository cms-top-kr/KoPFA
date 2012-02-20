void pileupdata(){

  TFile *fData = new TFile("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Pileup_2011_EPS_8_jul.root");
  TH1 * hData = (TH1F *) fData->Get("pileup");

  int nbins = hData->GetNbinsX();

  for(int i=1; i <= nbins ; i++){
    cout << hData->GetBinContent(i) << endl;
  }

}
