void QCDestimation(){

  TString dir = "/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/8TeV/QCD/";

  TFile *fQCD_ee = new TFile(dir+"TOPTTBB_8TeV_QCD_2j1b_Zveto/ElEl/ElEl.root");
  TFile *fQCD_mm = new TFile(dir+"TOPTTBB_8TeV_QCD_2j1b/MuMu/MuMu.root");
  TFile *fQCD_em = new TFile(dir+"TOPTTBB_8TeV_QCD_2j1b/MuEl/MuEl.root");

  TFile *fQCD_iso_ee = new TFile(dir+"TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15_Zveto/ElEl/ElEl.root");
  TFile *fQCD_iso_mm = new TFile(dir+"TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15/MuMu/MuMu.root");
  TFile *fQCD_iso_em = new TFile(dir+"TOPTTBB_8TeV_QCD_iso_2j1b_fixiso_15/MuEl/MuEl.root");

  TFile *fQCD_noiso_ee = new TFile(dir+"TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15_Zveto/ElEl/ElEl.root");
  TFile *fQCD_noiso_mm = new TFile(dir+"TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15/MuMu/MuMu.root");
  TFile *fQCD_noiso_em = new TFile(dir+"TOPTTBB_8TeV_QCD_anti_iso_2j1b_fixiso_15/MuEl/MuEl.root");

  //let's calculate scale factor at the dilepton selection level only and apply this to all steps.
  //it should agree within uncertainty
  for(int i=2; i <= 2 ; i++){

    TH1 * h_ee_mc = (TH1F *) fQCD_ee->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));
    TH1 * h_mm_mc = (TH1F *) fQCD_mm->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));
    TH1 * h_em_mc = (TH1F *) fQCD_em->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));

    TH1 * h_ee_datasub = (TH1F *) fQCD_ee->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));
    TH1 * h_mm_datasub = (TH1F *) fQCD_mm->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));
    TH1 * h_em_datasub = (TH1F *) fQCD_em->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));

    h_ee_datasub->Add(h_ee_mc,-1.0);
    h_mm_datasub->Add(h_mm_mc,-1.0);
    h_em_datasub->Add(h_em_mc,-1.0);
 
    TH1 * h_iso_ee_mc = (TH1F *) fQCD_iso_ee->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));
    TH1 * h_iso_mm_mc = (TH1F *) fQCD_iso_mm->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));
    TH1 * h_iso_em_mc = (TH1F *) fQCD_iso_em->Get(Form("Step_%i/hMCSig_TTbar_Step_%i_ZMass",i,i));

    TH1 * h_iso_ee_datasub = (TH1F *) fQCD_iso_ee->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));
    TH1 * h_iso_mm_datasub = (TH1F *) fQCD_iso_mm->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));
    TH1 * h_iso_em_datasub = (TH1F *) fQCD_iso_em->Get(Form("Step_%i/hDataSub_Step_%i_ZMass",i,i));

    h_iso_ee_datasub->Add(h_iso_ee_mc,-1.0);
    h_iso_mm_datasub->Add(h_iso_mm_mc,-1.0);
    h_iso_em_datasub->Add(h_iso_em_mc,-1.0);

    TH1 * h_noiso_ee_data = (TH1F *) fQCD_noiso_ee->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));
    TH1 * h_noiso_mm_data = (TH1F *) fQCD_noiso_mm->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));
    TH1 * h_noiso_em_data = (TH1F *) fQCD_noiso_em->Get(Form("Step_%i/hData_Step_%i_ZMass",i,i));

    double f_ee = h_ee_datasub->Integral()/h_noiso_ee_data->Integral();
    double f_mm = h_mm_datasub->Integral()/h_noiso_mm_data->Integral();
    double f_em = h_em_datasub->Integral()/h_noiso_em_data->Integral();

    double isoEff_ee = h_iso_ee_datasub->Integral()/h_ee_datasub->Integral();
    double isoEff_mm = h_iso_mm_datasub->Integral()/h_mm_datasub->Integral();
    double isoEff_em = h_iso_em_datasub->Integral()/h_em_datasub->Integral();

    double sf_ee = f_ee*isoEff_ee;
    double sf_mm = f_mm*isoEff_mm;
    double sf_em = f_em*isoEff_em;

    cout << "Step_" << i << endl; 
    cout << "ee decay--------------------------------" << endl;
    cout << "fQCD= " << f_ee << endl;
    cout << "isoEff= " << isoEff_ee << endl;
    cout << "sf= " << sf_ee << endl;

    cout << "mm decay--------------------------------" << endl;
    cout << "fQCD= " << f_mm << endl;
    cout << "isoEff= " << isoEff_mm << endl;
    cout << "sf= " << sf_mm << endl;

    cout << "em decay--------------------------------" << endl;
    cout << "fQCD= " << f_em << endl;
    cout << "isoEff= " << isoEff_em << endl;
    cout << "sf= " << sf_em << endl;

  }
}
