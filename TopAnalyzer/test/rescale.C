void rescale()
{
  const double wDYmm[] = {1.0, 1.0, 1,0, 1.04, 1.34, 1.87, 1.51};
  const double wDYee[] = {1.0, 1.0, 1,0, 1.04, 1.34, 1.91, 1.91};
  const int nDYmm = sizeof(wDYmm)/sizeof(wDYmm[0]);
  const int nDYee = sizeof(wDYee)/sizeof(wDYee[0]);

  rescale("MuMu.root", "MuMu_DYll_up.root", "hMC_DYll_", wDYmm, nDYmm, +0.2);
  rescale("MuMu.root", "MuMu_DYll_dw.root", "hMC_DYll_", wDYmm, nDYmm, -0.2);

  rescale("ElEl.root", "ElEl_DYll_up.root", "hMC_DYll_", wDYee, nDYee, +0.2);
  rescale("ElEl.root", "ElEl_DYll_dw.root", "hMC_DYll_", wDYee, nDYee, -0.2);

}

void rescale(TString inFileName, TString outFileName, TString histNamePrefix,
             const double* wDYll, const int nDYll, const double variation = 0)
{
  TFile* inFile = TFile::Open(inFileName);
  TFile* outFile = TFile::Open(outFileName, "RECREATE");
  
  TList* inDirs = inFile->GetListOfKeys();
  for ( int i=0; i<nDYll; ++i )
  {
    TDirectory* inDir = dynamic_cast<TDirectory*>(inFile->Get(Form("Step_%d", i)));
    if ( !inDir ) continue;

    TDirectory* outDir = outFile->mkdir(Form("Step_%d", i));

    TList* inHists = inDir->GetListOfKeys();
    for ( int j=0; j<inHists->GetSize(); ++j )
    {
      TString histName = inHists->At(j)->GetName();

      TH1F* hSrc = dynamic_cast<TH1F*>(inDir->Get(histName));
      if ( !hSrc ) continue;

      outDir->cd();
      TH1F* h = (TH1F*)hSrc->Clone();

      if ( histName.BeginsWith(histNamePrefix) )
      {
        h->Scale(1.+(wDYll[i]-1.)*(1.+variation));
      }
    }
  }

  outFile->Write();
  outFile->Close();

  inFile->Close();
}

