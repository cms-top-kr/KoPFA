void acceptance()
{
  TFile* fDen = TFile::Open("/home/bhlee/ntuple/top/MuMu/MC/genTTbar/ttbarGen.root");
  TFile* fNum = TFile::Open("/home/bhlee/ntuple/top/MuMu/MC/Fall10_Nov4ReReco/vallot_TTbar.root");

  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");
  TTree* genTreeNum = (TTree*)fNum->Get("MuMu/tree");
//  TTree* genTreeNum = (TTree*)fNum->Get("mm/tree");

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  gROOT->cd();
  TH1F* hDen = new TH1F("hDen", "Denominator", nBinsMass, binsMass);
  TH1F* hNum = new TH1F("hNum", "Numerator", nBinsMass, binsMass);

  TCut cut;
/*
  cut += "ttbar.zM() > 12";
  cut += "ttbar.relPFIso1() < 0.26 && ttbar.relPFIso2() < 0.26";
  cut += "ttbar.zSign() == 0";
  cut += "abs(ttbar.zM() - 91) > 15";
  cut += "ttbar.nGoodJetsEt_ >= 2";
  cut += "ttbar.unCorrMet_ > 30";
*/

  cut += "Z[0].mass() > 12";
  cut += "(chIso1[0]+nhIso1[0]+phIso1[0])/Z[0].leg1().pt() < 0.21 && (chIso2[0]+nhIso2[0]+phIso2[0])/Z[0].leg2().pt() < 0.21";
  cut += "Z[0].sign() < 0";
  cut += "abs(Z[0].mass() - 91) > 15";
  cut += "@jetspt30.size() >= 2";
  cut += "MET > 30";

  genTreeDen->Project("hDen", "tt.M()");
//  genTreeNum->Project("hNum", "ttbarGen.tt_.M()", cut);
  genTreeNum->Project("hNum", "genttbarM", cut);

  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors;
  grpAccept->BayesDivide(hNum, hDen);
  grpAccept->SetTitle("Acceptance;Generator level M(t#bar{t});Acceptance");
  grpAccept->SetMinimum(0);
  
  grpAccept->GetXaxis()->SetLimits(hDen->GetXaxis()->GetXmin(), hDen->GetXaxis()->GetXmax());
  grpAccept->Draw("AP");

  cout << "Overall acceptance = " << 100*hNum->GetEntries()/hDen->GetEntries() << "%" 
       << " (" << hNum->GetEntries() << "/" << hDen->GetEntries() << ")" << endl;
  for ( int i=1; i<=nBinsMass; ++i )
  {
    const double binLow = hDen->GetBinLowEdge(i);
    const double binUp = binLow + hDen->GetBinWidth(i);
    const double acceptanceVal = hNum->GetBinContent(i)/hDen->GetBinContent(i);
    cout << "[" << binLow << ":" << binUp << "] = " << acceptanceVal*100 << "%"
         << " (" << hNum->GetBinContent(i) << "/" << hDen->GetBinContent(i) << ")" << endl;
  }
}

