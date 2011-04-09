void acceptance(string decayMode = "MuMu")
{

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile* fDen = TFile::Open("/home/bhlee/ntuple/top/MuMu/MC/genTTbar/ttbarGen.root");
  TFile* fNum = TFile::Open("/home/bhlee/ntuple/top/MuMu/MC/Fall10_Nov4ReReco/vallot_TTbar.root");
  //string filepath = "/home/tjkim/ntuple/top/"+decayMode+"/MC/Fall10_bugfixed/vallot_TTbar.root"; 
  //TFile * fDen = new TFile("/home/tjkim/ntuple/top/genTTbar/ttbarGen.root");
  //TFile * fNum = new TFile(filepath.c_str());

  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");
  string dir = decayMode + "/tree";
  TTree* genTreeNum = (TTree*)fNum->Get(dir.c_str());
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
  if(decayMode == "MuMu"){
    cut += "(chIso1[0]+nhIso1[0]+phIso1[0])/Z[0].leg1().pt() < 0.21 && (chIso2[0]+nhIso2[0]+phIso2[0])/Z[0].leg2().pt() < 0.21";
  }else if(decayMode == "ElEl"){
    cut += "(chIso1[0]+nhIso1[0]+phIso1[0])/Z[0].leg1().pt() < 0.26 && (chIso2[0]+nhIso2[0]+phIso2[0])/Z[0].leg2().pt() < 0.26";
  }else{
    cut += "(chIso1[0]+nhIso1[0]+phIso1[0])/Z[0].leg1().pt() < 0.21 && (chIso2[0]+nhIso2[0]+phIso2[0])/Z[0].leg2().pt() < 0.26";
  }
  cut += "Z[0].sign() < 0";
  if(decayMode != "MuEl"){
   cut += "abs(Z[0].mass() - 91) > 15";
  }
  cut += "@jetspt30.size() >= 2";
  if(decayMode != "Muel"){
    cut += "MET > 30";
  }

  genTreeDen->Project("hDen", "tt.M()");
//  genTreeNum->Project("hNum", "ttbarGen.tt_.M()", cut);
  genTreeNum->Project("hNum", "genttbarM", cut);

  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors;
  for(int i=0; i < nBinsMass; i++){
    double acc = 100*hNum->GetBinContent(i+1)/hDen->GetBinContent(i+1);
    double center = hNum->GetBinCenter(i+1);
    double width = hNum->GetBinWidth(i+1);
    double err = 100*sqrt(hNum->GetBinContent(i+1))/hDen->GetBinContent(i+1);
    grpAccept->SetPoint(i, center, acc );
    grpAccept->SetPointEXhigh(i, width/2);
    grpAccept->SetPointEXlow(i, width/2);
    grpAccept->SetPointEYhigh(i, err);
    grpAccept->SetPointEYlow(i, err);
  } 

  //grpAccept->BayesDivide(hNum, hDen);
  grpAccept->SetTitle("Acceptance (%);Generator level M(t#bar{t});Acceptance (%)");
  grpAccept->SetMinimum(0);
  
  grpAccept->GetXaxis()->SetLimits(hDen->GetXaxis()->GetXmin(), hDen->GetXaxis()->GetXmax());
  grpAccept->SetMarkerSize(1.1);
  grpAccept->SetMarkerStyle(20);
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

