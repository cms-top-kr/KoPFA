void bDisWeight(){
  double YBins[] = {0.0, 0.05,  0.1, 0.15,  0.2, 0.25, 0.3,0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8,0.9};//8 bins
  int nY = sizeof(YBins)/sizeof(double) - 1;

  double YBins2[] = {0.0,  0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9};//8 bins
  int nY2 = sizeof(YBins2)/sizeof(double) - 1;

  plot("jets_bDiscriminatorCSV[csvd_jetid[0]]:jets_pt[csvd_jetid[0]]","csv_first", nY, YBins);
  plot("jets_bDiscriminatorCSV[csvd_jetid[1]]:jets_pt[csvd_jetid[1]]","csv_second", nY, YBins);
}

void plot(const TString & variable, const TString & name, int nY, double YBins[] ){

  TFile * f_MC[9];
  TFile * f_RD[2];

  f_MC[0] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_ZJets.root");
  f_MC[1] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_ZJets10To50.root");
  f_MC[2] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_TTbarTuneZ2.root");
  f_MC[3] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_WJetsToLNu.root");
  f_MC[4] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_WW.root");
  f_MC[5] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_WZ.root");
  f_MC[6] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_ZZ.root");
  f_MC[7] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_SingleToptW.root");
  f_MC[8] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_SingleTopBartW.root");

  f_RD[0] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_Run2012MuMu.root");
  f_RD[1] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_Run2012ElEl.root");
  //no need for emu
  //f_RD[2] = new TFile("/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/V5_10_0/V0_0_8/vallot_Run2012MuEl.root");

  double norm_MC[9];
  double lumi = 19619.0; 
  norm_MC[0] = getNorm( f_MC[0], 3503.0,   lumi, "MuMu");  
  norm_MC[1] = getNorm( f_MC[1], 860.0,    lumi, "MuMu");  
  norm_MC[2] = getNorm( f_MC[2], 234.0,    lumi, "MuMu");  
  norm_MC[3] = getNorm( f_MC[3], 36257.0,  lumi, "MuMu");  
  norm_MC[4] = getNorm( f_MC[4], 54.8,     lumi, "MuMu");  
  norm_MC[5] = getNorm( f_MC[5], 32.3,     lumi, "MuMu");  
  norm_MC[6] = getNorm( f_MC[6], 7.7,      lumi, "MuMu");  
  norm_MC[7] = getNorm( f_MC[7], 11.1,     lumi, "MuMu");  
  norm_MC[8] = getNorm( f_MC[8], 11.1,     lumi, "MuMu");  

  TTree * t_MC[2][9];
  TTree * t_RD[2];
  TH2F * h2_MC[2][9];
  TH2F * h2_RD[2];

  //pt
  //double XBins[] = {30, 40, 60, 300};//5 bins
  double XBins[] = {30, 300};//5 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;
  //b-Discriminator
  //double YBins[] = {0.0, 0.05,  0.1, 0.15,  0.2, 0.25, 0.3,0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8,0.9};//8 bins
  //int nY = sizeof(YBins)/sizeof(double) - 1;

  THStack * h_pt = new THStack();
  THStack * h_bDis = new THStack();
  TH2F * h2_CombinedMC[9];
  for(int j=0; j <9; j++){
    h2_CombinedMC[j] = new TH2F(Form("h2_%i",j),Form("h2_%i",j),nX, XBins, nY, YBins);
  }
 
  h2_DYMC = new TH2F("h2_DYMC","h2_DYMC",nX, XBins, nY, YBins);
  h2_Data = new TH2F("h2_Data","h2_Data",nX, XBins, nY, YBins);
  h2_SF = new TH2F("h2_SF","h2_SF",nX, XBins, nY, YBins);
 
  //Event selection 
  TCut cut = "ZMass > 12 && PairSign < 0 && nJet30 >= 2 && MET < 30 && abs(ZMass-91) < 15 && nbjets30_CSVT == 0";

  //filling histograms
  for(int i = 0; i < 2; i++){
    TString decay = "";
    if( i == 0 ) decay = "MuMu";
    if( i == 1 ) decay = "ElEl";
    if( i == 2 ) decay = "MuEl";

    for(int j = 0; j < 9; j++){
      t_MC[i][j] = (TTree *) f_MC[j]->Get(Form("%s/tree",decay.Data()));
      h2_MC[i][j] = new TH2F(Form("h2_%s_%i",decay.Data(),j),Form("h2_%s_%i",decay.Data(),j),nX, XBins, nY, YBins);
      t_MC[i][j]->Project(Form("h2_%s_%i",decay.Data(),j),Form("%s",variable.Data()), cut);
      h2_MC[i][j]->Scale(norm_MC[j]);
      h2_CombinedMC[j]->Add(h2_MC[i][j]);
      if( j == 0 || j == 1) h2_DYMC->Add(h2_MC[i][j]);
      else h2_DYMC->Add(h2_MC[i][j], -1);
    }

    t_RD[i] = (TTree *) f_RD[i]->Get(Form("%s/tree",decay.Data()));
    h2_RD[i] = new TH2F(Form("h2_%s",decay.Data()),Form("h2_%s",decay.Data()),nX, XBins, nY, YBins);
    t_RD[i]->Project(Form("h2_%s",decay.Data()),Form("%s",variable.Data()),cut);
    h2_Data->Add(h2_RD[i]);
  }

  for(int j=0; j < 9; j++){
    h2_CombinedMC[j]->SetFillColor(j+2);
    TH1D * h_pt_temp = h2_CombinedMC[j]->ProjectionX();
    TH1D * h_bDis_temp = h2_CombinedMC[j]->ProjectionY();
    h_pt->Add( h_pt_temp );
    h_bDis->Add( h_bDis_temp );
  }

  TH2F * h2_DataBeforeScale = h2_Data->Clone();

  h2_DYMC->Scale(1.0/h2_DYMC->Integral(0, nX+1, 0, nY+1));
  h2_Data->Scale(1.0/h2_Data->Integral(0, nX+1, 0, nY+1));
  h2_SF->Divide(h2_Data, h2_DYMC);

  //binned SF 
  TCanvas * c2_SF = new TCanvas(Form("c2_SF_%s",name.Data()),Form("c2_SF_%s",name.Data()),1);
  h2_SF->SetStats(0);
  h2_SF->Draw("colText");
  c2_SF->SetLogx();
  h2_SF->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h2_SF->GetYaxis()->SetTitle("b-Discriminator (CSV)");

  //stack for pt
  TCanvas * c_pt = new TCanvas(Form("c_pt_%s",name.Data()),Form("c_pt_%s",name.Data()),1);
  h_pt->Draw();
  TH1D * h_pt_data = h2_DataBeforeScale->ProjectionX();  
  h_pt_data->SetMarkerSize(1);
  h_pt_data->SetMarkerStyle(20);
  h_pt_data->Draw("sameP");

  //stack for bDis
  TCanvas * c_bDis = new TCanvas(Form("c_bDis_%s",name.Data()),Form("c_bDis_%s",name.Data()),1);
  h_bDis->Draw();
  TH1D * h_bDis_data = h2_DataBeforeScale->ProjectionY();
  h_bDis_data->SetMarkerSize(1);
  h_bDis_data->SetMarkerStyle(20);
  h_bDis_data->Draw("sameP");

  //fitting
  for(int i = 1; i <= nX; i++){
    TCanvas*  c_fit = new TCanvas(Form("c_fit_%s_%i",name.Data(),i),Form("c_fit_%s_%i",name.Data(),i),500,500);
    TH1D * h1_SF = h2_SF->ProjectionY(Form("h1_SF_%s_%i",name.Data(), i),i,i);
    TF1* function = new TF1("function", "pol4");
    function->SetLineColor(2);
    h1_SF->Fit(function);
    h1_SF->SetMinimum(0.0);
    h1_SF->SetMaximum(3.5);
    h1_SF->GetXaxis()->SetTitle("b-Discriminator (CSV)");
    h1_SF->GetYaxis()->SetTitle("Scale Factor (Data/MC)");
    h1_SF->SetStats(0);

    TH1F* function_err = (TH1F*) h1_SF->Clone();
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(function_err,0.68);
    function_err->SetFillColor(2);
    function_err->SetFillStyle(3005);
    function_err->SetStats(0);
    function_err->Draw("e3 same");
  }

}

double getNorm( TFile * file, double X, double lumi, const TString & dir){
     TH1F* h = (TH1F*) file->Get(Form("%s/EventSummary",dir.Data())); 
     double nTotal = h->GetBinContent(1);
     double SF = lumi * X / nTotal;
     return SF;
};

