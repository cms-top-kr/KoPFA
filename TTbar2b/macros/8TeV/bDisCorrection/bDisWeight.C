void bDisWeight(){
  double YBins[] = {0.0, 0.05,  0.1, 0.15,  0.2, 0.25, 0.3,0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8,0.9};//8 bins
  int nY = sizeof(YBins)/sizeof(double) - 1;

  double YBins2[] = {0.0,  0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9};//8 bins
  int nY2 = sizeof(YBins2)/sizeof(double) - 1;

  plot("jets_bDiscriminatorCSV[csvd_jetid[0]]:jets_pt[csvd_jetid[0]]","csv_first", nY, YBins);
  plot("jets_bDiscriminatorCSV[csvd_jetid[1]]:jets_pt[csvd_jetid[1]]","csv_second", nY, YBins);
  //plot("jets_bDiscriminatorCSV:jets_pt","csv_all", nY, YBins);
}

void plot(const TString & variable, const TString & name, int nY, double YBins[] ){

  TFile * f_MC[9];
  TFile * f_RD[2];

  TString path = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130327_V00-00-08/";

  f_MC[0] = new TFile(path+"vallot_ZJets.root");
  f_MC[1] = new TFile(path+"vallot_ZJets10To50.root");
  f_MC[2] = new TFile(path+"vallot_TTbarTuneZ2.root");
  f_MC[3] = new TFile(path+"vallot_WJetsToLNu.root");
  f_MC[4] = new TFile(path+"vallot_WW.root");
  f_MC[5] = new TFile(path+"vallot_WZ.root");
  f_MC[6] = new TFile(path+"vallot_ZZ.root");
  f_MC[7] = new TFile(path+"vallot_SingleToptW.root");
  f_MC[8] = new TFile(path+"vallot_SingleTopBartW.root");

  f_RD[0] = new TFile(path+"vallot_Run2012MuMu.root");
  f_RD[1] = new TFile(path+"vallot_Run2012ElEl.root");
  //no need for emu
  //f_RD[2] = new TFile(path+"vallot_Run2012MuEl.root");

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
  double XBins[] = {30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 140, 150, 160, 180, 200, 230, 260, 300};//5 bins
  int nX = sizeof(XBins)/sizeof(double) - 1;
  //b-Discriminator
  //double YBins[] = {0.0, 0.05,  0.1, 0.15,  0.2, 0.25, 0.3,0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8,0.9};//8 bins
  //int nY = sizeof(YBins)/sizeof(double) - 1;

  THStack * h_pt = new THStack();
  THStack * h_bDis = new THStack();
  TH2F * h2_CombinedMC[5];
  for(int j=0; j <5; j++){
    h2_CombinedMC[j] = new TH2F(Form("h2_%i",j),Form("h2_%i",j),nX, XBins, nY, YBins);
  }
 
  TH2F * h2_DYMC = new TH2F("h2_DYMC","h2_DYMC",nX, XBins, nY, YBins);
  TH2F * h2_Data = new TH2F("h2_Data","h2_Data",nX, XBins, nY, YBins);
  TH2F * h2_SF = new TH2F("h2_SF","h2_SF",nX, XBins, nY, YBins);

  TH1D * h1_DYMC = new TH1D("h1_DYMC","h1_DYMC",nY, YBins);
  TH1D * h1_Data = new TH1D("h1_Data","h1_Data",nY, YBins);
  TH1D * h1_SF = new TH1D("h1_SF","h1_SF",nY, YBins);

  TH1D * h1_pt_DYMC = new TH1D("h1_pt_DYMC","h1_pt_DYMC",nX, XBins);
  TH1D * h1_pt_Data = new TH1D("h1_pt_Data","h1_pt_Data",nX, XBins);
  TH1D * h1_pt_SF = new TH1D("h1_pt_SF","h1_pt_SF",nX, XBins);

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
      if( j == 0 || j == 1)           h2_CombinedMC[0]->Add(h2_MC[i][j]);
      if( j == 2 )                    h2_CombinedMC[1]->Add(h2_MC[i][j]);
      if( j == 3 )                    h2_CombinedMC[2]->Add(h2_MC[i][j]);
      if( j == 4 || j == 5 || j ==6 ) h2_CombinedMC[3]->Add(h2_MC[i][j]);
      if( j == 7 || j == 8 )          h2_CombinedMC[4]->Add(h2_MC[i][j]);
      if( j == 0 || j == 1) h2_DYMC->Add(h2_MC[i][j]);
      //else h2_DYMC->Add(h2_MC[i][j], -1);
    }

    t_RD[i] = (TTree *) f_RD[i]->Get(Form("%s/tree",decay.Data()));
    h2_RD[i] = new TH2F(Form("h2_%s",decay.Data()),Form("h2_%s",decay.Data()),nX, XBins, nY, YBins);
    t_RD[i]->Project(Form("h2_%s",decay.Data()),Form("%s",variable.Data()),cut);
    h2_Data->Add(h2_RD[i]);
  }


  for(int j=0; j < 5; j++){
    h2_CombinedMC[j]->SetFillColor(2+j); 
    TH1D * h_pt_temp = h2_CombinedMC[j]->ProjectionX();
    TH1D * h_bDis_temp = h2_CombinedMC[j]->ProjectionY();
    h_pt->Add( h_pt_temp );
    h_bDis->Add( h_bDis_temp );
  }

  TH2F * h2_DataBeforeScale = h2_Data->Clone();

  h2_Data->Add(h2_CombinedMC[1], -1);
  h2_Data->Add(h2_CombinedMC[2], -1);
  h2_Data->Add(h2_CombinedMC[3], -1);
  h2_Data->Add(h2_CombinedMC[4], -1);

  h1_Data = h2_Data->ProjectionY();
  h1_DYMC = h2_DYMC->ProjectionY();
  h1_Data->Scale(1.0/h1_Data->Integral(0,nX+1));
  h1_DYMC->Scale(1.0/h1_DYMC->Integral(0,nX+1));
  h1_SF->Divide(h1_Data, h1_DYMC);

  h1_pt_Data = h2_Data->ProjectionX();
  h1_pt_DYMC = h2_DYMC->ProjectionX();
  h1_pt_Data->Scale(1.0/h1_pt_Data->Integral(0,nY+1));
  h1_pt_DYMC->Scale(1.0/h1_pt_DYMC->Integral(0,nY+1));
  h1_pt_SF->Divide(h1_pt_Data, h1_pt_DYMC);

  h2_DYMC->Scale(1.0/h2_DYMC->Integral(0, nX+1, 0, nY+1));
  h2_Data->Scale(1.0/h2_Data->Integral(0, nX+1, 0, nY+1));
  h2_SF->Divide(h2_Data, h2_DYMC);

  //binned 2D MC 
  TCanvas * c2_DYMC = new TCanvas(Form("c2_DYMC_%s",name.Data()),Form("c2_DYMC_%s",name.Data()),700,700);
  h2_DYMC->SetStats(0);
  h2_DYMC->Draw("colz");
  c2_DYMC->SetLogx();
  h2_DYMC->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h2_DYMC->GetYaxis()->SetTitle("b-Discriminator (CSV)");
  c2_DYMC->Print(Form("c2_DYMC_%s.eps",name.Data() ) );

  //binned SF 
  TCanvas * c2_SF = new TCanvas(Form("c2_SF_%s",name.Data()),Form("c2_SF_%s",name.Data()),700,700);
  h2_SF->SetStats(0);
  h2_SF->Draw("colText");
  c2_SF->SetLogx();
  h2_SF->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h2_SF->GetYaxis()->SetTitle("b-Discriminator (CSV)");
  c2_SF->Print(Form("c2_SF_%s.eps",name.Data() ) );

  //stack for pt
  TCanvas * c_pt = new TCanvas(Form("c_pt_%s",name.Data()),Form("c_pt_%s",name.Data()),700,700);
  TGaxis::SetMaxDigits(4);
  TH1D * h_pt_data = h2_DataBeforeScale->ProjectionX();
  h_pt_data->Draw();
  h_pt_data->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_pt_data->GetYaxis()->SetTitle("Events");

  h_pt->Draw();
  h_pt->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_pt->GetYaxis()->SetTitle("Events");
  h_pt_data->SetMarkerSize(1);
  h_pt_data->SetMarkerStyle(20);
  h_pt_data->Draw("sameP");

  TLegend *l = new TLegend(0.72,0.64,0.90,0.87);
  l->AddEntry(h_pt_data,"Data","P");
  l->AddEntry(h2_CombinedMC[0],"Z+jets","F");
  l->AddEntry(h2_CombinedMC[1],"t#bar{t}","F");
  l->AddEntry(h2_CombinedMC[2],"W+jets","F");
  l->AddEntry(h2_CombinedMC[3],"Dibosons","F");
  l->AddEntry(h2_CombinedMC[4],"Signle-top","F");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c_pt->Print(Form("c_pt_%s.eps",name.Data() ) );

  //stack for bDis
  TCanvas * c_bDis = new TCanvas(Form("c_bDis_%s",name.Data()),Form("c_bDis_%s",name.Data()),700,700);
  TGaxis::SetMaxDigits(4);
  TH1D * h_bDis_data = h2_DataBeforeScale->ProjectionY();
  h_bDis_data->Draw();
  h_bDis_data->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_bDis_data->GetYaxis()->SetTitle("Events");

  h_bDis->Draw();
  h_bDis->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h_bDis->GetYaxis()->SetTitle("Events");
  h_bDis_data->SetMarkerSize(1);
  h_bDis_data->SetMarkerStyle(20);
  h_bDis_data->Draw("sameP");

  l->Draw();

  c_bDis->Print(Form("c_bDis_%s.eps",name.Data() ) );

/*
  //fitting
  for(int i = 1; i <= nX; i++){
    TCanvas*  c_fit = new TCanvas(Form("c_fit_%s_%i",name.Data(),i),Form("c_fit_%s_%i",name.Data(),i),700,700);
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
    c_fit->Print(Form("c_fit_%s_%i.eps",name.Data(),i));
  }
*/

  TCanvas*  c_fit = new TCanvas(Form("c_fit_%s",name.Data()),Form("c_fit_%s",name.Data()),700,700);
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
  c_fit->Print(Form("c_fit_%s.eps",name.Data()));

  TCanvas*  c_pt_fit = new TCanvas(Form("c_pt_fit_%s",name.Data()),Form("c_pt_fit_%s",name.Data()),700,700);
  TF1* functionpt = new TF1("functionpt", "pol1");
  functionpt->SetLineColor(2);
  h1_pt_SF->Fit(functionpt);
  h1_pt_SF->SetMinimum(0.0);
  h1_pt_SF->SetMaximum(3.5);
  h1_pt_SF->GetXaxis()->SetTitle("b-Discriminator (CSV)");
  h1_pt_SF->GetYaxis()->SetTitle("Scale Factor (Data/MC)");
  h1_pt_SF->SetStats(0);
  TH1F* functionpt_err = (TH1F*) h1_pt_SF->Clone();
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(functionpt_err,0.68);
  functionpt_err->SetFillColor(2);
  functionpt_err->SetFillStyle(3005);
  functionpt_err->SetStats(0);
  functionpt_err->Draw("e3 same");
  c_pt_fit->Print(Form("c_pt_fit_%s.eps",name.Data()));


}

double getNorm( TFile * file, double X, double lumi, const TString & dir){
     TH1F* h = (TH1F*) file->Get(Form("%s/EventSummary",dir.Data())); 
     double nTotal = h->GetBinContent(1);
     double SF = lumi * X / nTotal;
     return SF;
};

