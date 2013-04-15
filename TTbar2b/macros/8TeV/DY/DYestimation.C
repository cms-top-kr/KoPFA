void DYestimation(){

  TFile *fDY_ee = new TFile("TOPTTBB_DY_IN_0j1b/ElEl/ElEl.root");
  TFile *fDY_mm = new TFile("TOPTTBB_DY_IN_0j1b/MuMu/MuMu.root");
  TFile *fDY_em = new TFile("TOPTTBB_DY_IN_0j1b/MuEl/MuEl.root");
  TFile *fDY_out_ee = new TFile("TOPTTBB_DY_Out_0j1b/ElEl/ElEl.root");
  TFile *fDY_out_mm = new TFile("TOPTTBB_DY_Out_0j1b/MuMu/MuMu.root");

  TH1 * h_ee = (TH1F *) fDY_ee->Get("Step_3/hData_Step_3_ZMass");
  TH1 * h_mm = (TH1F *) fDY_mm->Get("Step_3/hData_Step_3_ZMass");

  double k = h_mm->Integral()/h_ee->Integral();

  for(int i=2; i <= 5 ; i++){
    TH1 * h_ee_mc = (TH1F *) fDY_ee->Get(Form("Step_%i/hMC_DYll_Step_%i_ZMass",i,i));
    TH1 * h_mm_mc = (TH1F *) fDY_mm->Get(Form("Step_%i/hMC_DYll_Step_%i_ZMass",i,i));
    TH1 * h_ee_data = (TH1F *) fDY_ee->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));
    TH1 * h_mm_data = (TH1F *) fDY_mm->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));
    TH1 * h_em_data = (TH1F *) fDY_em->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));
    TH1 * h_ee_out_mc = (TH1F *) fDY_out_ee->Get(Form("Step_%i/hMC_DYll_Step_%i_ZMass",i,i));
    TH1 * h_mm_out_mc = (TH1F *) fDY_out_mm->Get(Form("Step_%i/hMC_DYll_Step_%i_ZMass",i,i));

    double bkg = h_em_data->Integral();
    double R_mm = h_mm_out_mc->Integral()/h_mm_mc->Integral();
    double R_ee = h_ee_out_mc->Integral()/h_ee_mc->Integral();
    double data_in_mm = h_mm_data->Integral();
    double data_in_ee = h_ee_data->Integral();

    double estimation_mm = R_mm*(data_in_mm - 0.5*bkg*k);
    double estimation_ee = R_ee*(data_in_ee - 0.5*bkg*1.0/k);
    double prediction_mm = h_mm_out_mc->Integral();
    double prediction_ee = h_ee_out_mc->Integral();

    cout << "Step_" << i << endl; 
    cout << "mm decay--------------------------------" << endl;
    cout << "R= " << R_mm << " k= " << k << endl;
    cout << "Data in= " << data_in_mm << endl;
    cout << "Bkg in= " << bkg << endl;
    cout << "Prediction = " << prediction_mm << endl;
    cout << "Estimation = " << estimation_mm << endl;
    cout << "scale= " << estimation_mm/prediction_mm << endl;

    cout << "ee decay--------------------------------" << endl;
    cout << "R= " << R_ee << " k= " << 1.0/k << endl;
    cout << "Data in= " << data_in_ee << endl;
    cout << "Bkg in= " << bkg << endl;
    cout << "Prediction = " << prediction_ee << endl;
    cout << "Estimation = " << estimation_ee << endl;
    cout << "scale= " << estimation_ee/prediction_ee << endl;
  }
}
