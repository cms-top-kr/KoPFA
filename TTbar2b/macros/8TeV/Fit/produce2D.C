void produce2D(){

  TFile * f_MC[11];
  TFile * f_RD[3];

  TString path = "/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130613_HFupdw/";

  f_MC[0] = new TFile(path+"vallot_ZJets.root");
  f_MC[1] = new TFile(path+"vallot_ZJets10To50.root");
  f_MC[2] = new TFile(path+"vallot_TTbarFullLepMGDecays.root");
  f_MC[3] = new TFile(path+"vallot_TTbarSemiLeptMGDecays.root");
  f_MC[4] = new TFile(path+"vallot_TTbarHadronicMGDecays.root");
  f_MC[5] = new TFile(path+"vallot_WJetsToLNu.root");
  f_MC[6] = new TFile(path+"vallot_WW.root");
  f_MC[7] = new TFile(path+"vallot_WZ.root");
  f_MC[8] = new TFile(path+"vallot_ZZ.root");
  f_MC[9] = new TFile(path+"vallot_SingleToptW.root");
  f_MC[10] = new TFile(path+"vallot_SingleTopBartW.root");

  double norm[11];
  double lumi = 19619.0;
  norm[0] = getNorm( f_MC[0], 3503.0,   lumi, "MuMu");
  norm[1] = getNorm( f_MC[1], 860.0,    lumi, "MuMu");
  norm[2] = getNorm( f_MC[2], 26.0,     lumi, "MuMu");
  norm[3] = getNorm( f_MC[3], 104.0,    lumi, "MuMu");
  norm[4] = getNorm( f_MC[4], 104.0,    lumi, "MuMu");
  norm[5] = getNorm( f_MC[5], 37509.0,  lumi, "MuMu");
  norm[6] = getNorm( f_MC[6], 54.8,     lumi, "MuMu");
  norm[7] = getNorm( f_MC[7], 32.3,     lumi, "MuMu");
  norm[8] = getNorm( f_MC[8], 8.1,      lumi, "MuMu");
  norm[9] = getNorm( f_MC[9], 11.1,     lumi, "MuMu");
  norm[10]= getNorm( f_MC[10], 11.1,     lumi, "MuMu");

  f_RD[0] = new TFile(path+"vallot_Run2012MuMu.root");
  f_RD[1] = new TFile(path+"vallot_Run2012ElEl.root");
  f_RD[2] = new TFile(path+"vallot_Run2012MuEl.root");

  TTree * t_MC[3][11];
  TTree * t_RD[3];

  TCut visible = "nGenJet20 >= 4 && nGenbJet20 >=2 && genLep1_pt > 20 && genLep2_pt > 20 && abs( genLep1_eta ) < 2.4 && abs( genLep2_eta ) < 2.4" ;
  TCut sigcut = "nGenbJet20 >= 4";
  TCut ttb = "nGenbJet20 == 3";
  TCut ttcc = "nGencJet20 >= 2";

  TCut final_em    = "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0 && nJet30 >= 4 && nbjets30_CSVT >= 2";
  TCut final       = "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0 && nJet30 >= 4 && nbjets30_CSVT >= 2 && abs(ZMass-91.2) > 15 && MET > 30";
  TCut finalqcd_em = "ZMass > 12 && lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15 && PairSign < 0 && nJet30 >= 4 && nbjets30_CSVT >= 2";
  TCut finalqcd    = "ZMass > 12 && lep1_relIso03 > 0.15 && lep2_relIso03 > 0.15 && PairSign < 0 && nJet30 >= 4 && nbjets30_CSVT >= 2 && abs(ZMass-91.2) > 15 && MET > 30";

  TH1F * x_data[3];
  TH1F * y_data[3];
  TH2F * xy_data[3];
  TH1F * x_DY10To50[3];
  TH1F * y_DY10To50[3];
  TH2F * xy_DY10To50[3];
  TH1F * x_DY[3];
  TH1F * y_DY[3];
  TH2F * xy_DY[3];
  TH1F * x_ttbb[3];
  TH1F * y_ttbb[3];
  TH2F * xy_ttbb[3];
  TH1F * x_ttb[3];
  TH1F * y_ttb[3];
  TH2F * xy_ttb[3];
  TH1F * x_ttLF[3];
  TH1F * y_ttLF[3];
  TH2F * xy_ttLF[3];
  TH1F * x_ttOthers[3];
  TH1F * y_ttOthers[3];
  TH2F * xy_ttOthers[3];
  TH1F * x_ttSemi[3];
  TH1F * y_ttSemi[3];
  TH2F * xy_ttSemi[3];
  TH1F * x_ttHad[3];
  TH1F * y_ttHad[3];
  TH2F * xy_ttHad[3];
  TH1F * x_wjets[3];
  TH1F * y_wjets[3];
  TH2F * xy_wjets[3];
  TH1F * x_ww[3];
  TH1F * y_ww[3];
  TH2F * xy_ww[3];
  TH1F * x_wz[3];
  TH1F * y_wz[3];
  TH2F * xy_wz[3];
  TH1F * x_zz[3];
  TH1F * y_zz[3];
  TH2F * xy_zz[3];
  TH1F * x_bkg[3];
  TH1F * y_bkg[3];
  TH2F * xy_bkg[3];
  TH1F * x_singleTop[3];
  TH1F * y_singleTop[3];
  TH2F * xy_singleTop[3];
  TH1F * x_singleTopBar[3];
  TH1F * y_singleTopBar[3];
  TH2F * xy_singleTopBar[3]; 
  TH1F * x_QCD[3];
  TH1F * y_QCD[3];
  TH2F * xy_QCD[3];
 
  TH1F * x_data_all = new TH1F("x_data_all","x_data_all",10,0.0,1.0);
  TH1F * y_data_all = new TH1F("y_data_all","y_data_all",10,0.0,1.0);
  TH2F * xy_data_all = new TH2F("xy_data_all","xy_data_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_DY_all = new TH1F("x_DY_all","x_DY_all",10,0.0,1.0);
  TH1F * y_DY_all = new TH1F("y_DY_all","y_DY_all",10,0.0,1.0);
  TH2F * xy_DY_all = new TH2F("xy_DY_all","xy_DY_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_ttbb_all = new TH1F("x_ttbb_all","x_ttbb_all",10,0.0,1.0);
  TH1F * y_ttbb_all = new TH1F("y_ttbb_all","y_ttbb_all",10,0.0,1.0);
  TH2F * xy_ttbb_all = new TH2F("xy_ttbb_all","xy_ttbb_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_ttb_all = new TH1F("x_ttb_all","x_ttb_all",10,0.0,1.0);
  TH1F * y_ttb_all = new TH1F("y_ttb_all","y_ttb_all",10,0.0,1.0);
  TH2F * xy_ttb_all = new TH2F("xy_ttb_all","xy_ttb_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_ttLF_all = new TH1F("x_ttLF_all","x_ttLF_all",10,0.0,1.0);
  TH1F * y_ttLF_all = new TH1F("y_ttLF_all","y_ttLF_all",10,0.0,1.0);
  TH2F * xy_ttLF_all = new TH2F("xy_ttLF_all","xy_ttLF_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_ttOthers_all = new TH1F("x_ttOthers_all","x_ttOthers_all",10,0.0,1.0);
  TH1F * y_ttOthers_all = new TH1F("y_ttOthers_all","y_ttOthers_all",10,0.0,1.0);
  TH2F * xy_ttOthers_all = new TH2F("xy_ttOthers_all","xy_ttOthers_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_bkg_all = new TH1F("x_bkg_all","x_bkg_all",10,0.0,1.0);
  TH1F * y_bkg_all = new TH1F("y_bkg_all","y_bkg_all",10,0.0,1.0);
  TH2F * xy_bkg_all = new TH2F("xy_bkg_all","xy_bkg_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_singleTop_all = new TH1F("x_singleTop_all","x_singleTop_all",10,0.0,1.0);
  TH1F * y_singleTop_all = new TH1F("y_singleTop_all","y_singleTop_all",10,0.0,1.0);
  TH2F * xy_singleTop_all = new TH2F("xy_singleTop_all","xy_singleTop_all",10,0.0,1.0,10,0.0,1.0);
  TH1F * x_QCD_all = new TH1F("x_QCD_all","x_QCD_all",10,0.0,1.0);
  TH1F * y_QCD_all = new TH1F("y_QCD_all","y_QCD_all",10,0.0,1.0);
  TH2F * xy_QCD_all = new TH2F("xy_QCD_all","xy_QCD_all",10,0.0,1.0,10,0.0,1.0);

  cout << "fill...." << endl; 
  for(int i=0 ; i < 3; i++){
    cout << "i= " << i << endl;

    double qcdscale = 1.0;
    double dyscale = 1.0;
    TCut sel = final;
    TCut qcdsel = finalqcd;
    TString decay = "";
    if(i == 0) {
      decay = "MuMu";
      qcdscale = 0.028;
      dyscale = 1.73553;
    }
    if(i == 1) {
      decay = "ElEl";
      qcdscale = 0.657;
      dyscale = 1.87588; 
    }
    if(i == 2) {
      decay = "MuEl";
      qcdscale = 0.064; 
      sel = final_em;
      qcdsel = finalqcd_em;
    }

    t_RD[i] = (TTree*) f_RD[i]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][0] = (TTree*) f_MC[0]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][1] = (TTree*) f_MC[1]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][2] = (TTree*) f_MC[2]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][3] = (TTree*) f_MC[3]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][4] = (TTree*) f_MC[4]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][5] = (TTree*) f_MC[5]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][6] = (TTree*) f_MC[6]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][7] = (TTree*) f_MC[7]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][8] = (TTree*) f_MC[8]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][9] = (TTree*) f_MC[9]->Get(Form("%s/tree",decay.Data()));
    t_MC[i][10] = (TTree*) f_MC[10]->Get(Form("%s/tree",decay.Data()));

    x_data[i] = new TH1F(Form("x_data_%s",decay.Data()),Form("x_data_%s",decay.Data()),10,0.0,1.0);
    y_data[i] = new TH1F(Form("y_data_%s",decay.Data()),Form("y_data_%s",decay.Data()),10,0.0,1.0);
    xy_data[i] = new TH2F(Form("xy_data_%s",decay.Data()),Form("xy_data_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_DY10To50[i] = new TH1F(Form("x_DY10To50_%s",decay.Data()),Form("x_DY10To50_%s",decay.Data()),10,0.0,1.0);
    y_DY10To50[i] = new TH1F(Form("y_DY10To50_%s",decay.Data()),Form("y_DY10To50_%s",decay.Data()),10,0.0,1.0);
    xy_DY10To50[i] = new TH2F(Form("xy_DY10To50_%s",decay.Data()),Form("xy_DY10To50_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_DY[i] = new TH1F(Form("x_DY_%s",decay.Data()),Form("x_DY_%s",decay.Data()),10,0.0,1.0);
    y_DY[i] = new TH1F(Form("y_DY_%s",decay.Data()),Form("y_DY_%s",decay.Data()),10,0.0,1.0);
    xy_DY[i] = new TH2F(Form("xy_DY_%s",decay.Data()),Form("xy_DY_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttbb[i] = new TH1F(Form("x_ttbb_%s",decay.Data()),Form("x_ttbb_%s",decay.Data()),10,0.0,1.0);
    y_ttbb[i] = new TH1F(Form("y_ttbb_%s",decay.Data()),Form("y_ttbb_%s",decay.Data()),10,0.0,1.0);
    xy_ttbb[i] = new TH2F(Form("xy_ttbb_%s",decay.Data()),Form("xy_ttbb_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttb[i] = new TH1F(Form("x_ttb_%s",decay.Data()),Form("x_ttb_%s",decay.Data()),10,0.0,1.0);
    y_ttb[i] = new TH1F(Form("y_ttb_%s",decay.Data()),Form("y_ttb_%s",decay.Data()),10,0.0,1.0);
    xy_ttb[i] = new TH2F(Form("xy_ttb_%s",decay.Data()),Form("xy_ttb_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttLF[i] = new TH1F(Form("x_ttLF_%s",decay.Data()),Form("x_ttLF_%s",decay.Data()),10,0.0,1.0);
    y_ttLF[i] = new TH1F(Form("y_ttLF_%s",decay.Data()),Form("y_ttLF_%s",decay.Data()),10,0.0,1.0);
    xy_ttLF[i] = new TH2F(Form("xy_ttLF_%s",decay.Data()),Form("xy_ttLF_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttOthers[i] = new TH1F(Form("x_ttOthers_%s",decay.Data()),Form("x_ttOthers_%s",decay.Data()),10,0.0,1.0);
    y_ttOthers[i] = new TH1F(Form("y_ttOthers_%s",decay.Data()),Form("y_ttOthers_%s",decay.Data()),10,0.0,1.0);
    xy_ttOthers[i] = new TH2F(Form("xy_ttOthers_%s",decay.Data()),Form("xy_ttOthers_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttSemi[i] = new TH1F(Form("x_ttSemi_%s",decay.Data()),Form("x_ttSemi_%s",decay.Data()),10,0.0,1.0);
    y_ttSemi[i] = new TH1F(Form("y_ttSemi_%s",decay.Data()),Form("y_ttSemi_%s",decay.Data()),10,0.0,1.0);
    xy_ttSemi[i] = new TH2F(Form("xy_ttSemi_%s",decay.Data()),Form("xy_ttSemi_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ttHad[i] = new TH1F(Form("x_ttHad_%s",decay.Data()),Form("x_ttHad_%s",decay.Data()),10,0.0,1.0);
    y_ttHad[i] = new TH1F(Form("y_ttHad_%s",decay.Data()),Form("y_ttHad_%s",decay.Data()),10,0.0,1.0);
    xy_ttHad[i] = new TH2F(Form("xy_ttHad_%s",decay.Data()),Form("xy_ttHad_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_wjets[i] = new TH1F(Form("x_wjets_%s",decay.Data()),Form("x_wjets_%s",decay.Data()),10,0.0,1.0);
    y_wjets[i] = new TH1F(Form("y_wjets_%s",decay.Data()),Form("y_wjets_%s",decay.Data()),10,0.0,1.0);
    xy_wjets[i] = new TH2F(Form("xy_wjets_%s",decay.Data()),Form("xy_wjets_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_ww[i] = new TH1F(Form("x_ww_%s",decay.Data()),Form("x_ww_%s",decay.Data()),10,0.0,1.0);
    y_ww[i] = new TH1F(Form("y_ww_%s",decay.Data()),Form("y_ww_%s",decay.Data()),10,0.0,1.0);
    xy_ww[i] = new TH2F(Form("xy_ww_%s",decay.Data()),Form("xy_ww_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);
 
    x_wz[i] = new TH1F(Form("x_wz_%s",decay.Data()),Form("x_wz_%s",decay.Data()),10,0.0,1.0);
    y_wz[i] = new TH1F(Form("y_wz_%s",decay.Data()),Form("y_wz_%s",decay.Data()),10,0.0,1.0);
    xy_wz[i] = new TH2F(Form("xy_wz_%s",decay.Data()),Form("xy_wz_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_zz[i] = new TH1F(Form("x_zz_%s",decay.Data()),Form("x_zz_%s",decay.Data()),10,0.0,1.0);
    y_zz[i] = new TH1F(Form("y_zz_%s",decay.Data()),Form("y_zz_%s",decay.Data()),10,0.0,1.0);
    xy_zz[i] = new TH2F(Form("xy_zz_%s",decay.Data()),Form("xy_zz_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);
 
    x_bkg[i] = new TH1F(Form("x_bkg_%s",decay.Data()),Form("x_bkg_%s",decay.Data()),10,0.0,1.0);
    y_bkg[i] = new TH1F(Form("y_bkg_%s",decay.Data()),Form("y_bkg_%s",decay.Data()),10,0.0,1.0);
    xy_bkg[i] = new TH2F(Form("xy_bkg_%s",decay.Data()),Form("xy_bkg_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_singleTop[i] = new TH1F(Form("x_singleTop_%s",decay.Data()),Form("x_singleTop_%s",decay.Data()),10,0.0,1.0);
    y_singleTop[i] = new TH1F(Form("y_singleTop_%s",decay.Data()),Form("y_singleTop_%s",decay.Data()),10,0.0,1.0);
    xy_singleTop[i] = new TH2F(Form("xy_singleTop_%s",decay.Data()),Form("xy_singleTop_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_singleTopBar[i] = new TH1F(Form("x_singleTopBar_%s",decay.Data()),Form("x_singleTopBar_%s",decay.Data()),10,0.0,1.0);
    y_singleTopBar[i] = new TH1F(Form("y_singleTopBar_%s",decay.Data()),Form("y_singleTopBar_%s",decay.Data()),10,0.0,1.0);
    xy_singleTopBar[i] = new TH2F(Form("xy_singleTopBar_%s",decay.Data()),Form("xy_singleTopBar_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    x_QCD[i] = new TH1F(Form("x_QCD_%s",decay.Data()),Form("x_QCD_%s",decay.Data()),10,0.0,1.0);
    y_QCD[i] = new TH1F(Form("y_QCD_%s",decay.Data()),Form("y_QCD_%s",decay.Data()),10,0.0,1.0);
    xy_QCD[i] = new TH2F(Form("xy_QCD_%s",decay.Data()),Form("xy_QCD_%s",decay.Data()),10,0.0,1.0,10,0.0,1.0);

    t_RD[i]->Project(Form("xy_data_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",sel);
    t_RD[i]->Project(Form("x_data_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",sel);
    t_RD[i]->Project(Form("y_data_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",sel);

    t_RD[i]->Project(Form("xy_QCD_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",qcdsel);
    t_RD[i]->Project(Form("x_QCD_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",qcdsel);
    t_RD[i]->Project(Form("y_QCD_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",qcdsel);

    TCut cut_sel = sel;
    TString cutStr_sel ;
    cutStr_sel = cut_sel;
    TCut cut_selStr = Form("puweight*lepweight*csvweight*(%s)", cutStr_sel.Data());

    TCut cut_ttbb = sel+visible+sigcut;
    TString cutStr_ttbb ;
    cutStr_ttbb = cut_ttbb;
    TCut cut_ttbbStr = Form("puweight*lepweight*csvweight*(%s)", cutStr_ttbb.Data());

    TCut cut_ttb = sel+visible+ttb;
    TString cutStr_ttb ;
    cutStr_ttb = cut_ttb;
    TCut cut_ttbStr = Form("puweight*lepweight*csvweight*(%s)", cutStr_ttb.Data()); 
 
    TCut cut_ttLF = sel+visible+!sigcut+!ttb;
    TString cutStr_ttLF ;
    cutStr_ttLF = cut_ttLF;
    TCut cut_ttLFStr = Form("puweight*lepweight*csvweight*(%s)", cutStr_ttLF.Data());

    TCut cut_ttOthers = sel+!visible;
    TString cutStr_ttOthers ;
    cutStr_ttOthers = cut_ttOthers;
    TCut cut_ttOthersStr = Form("puweight*lepweight*csvweight*(%s)", cutStr_ttOthers.Data());

    t_MC[i][0]->Project(Form("xy_DY_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][0]->Project(Form("x_DY_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][0]->Project(Form("y_DY_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][1]->Project(Form("xy_DY10To50_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][1]->Project(Form("x_DY10To50_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][1]->Project(Form("y_DY10To50_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);
 
    t_MC[i][2]->Project(Form("xy_ttbb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttbbStr);
    t_MC[i][2]->Project(Form("x_ttbb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttbbStr);
    t_MC[i][2]->Project(Form("y_ttbb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_ttbbStr);

    t_MC[i][2]->Project(Form("xy_ttb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttbStr);
    t_MC[i][2]->Project(Form("x_ttb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttbStr);
    t_MC[i][2]->Project(Form("y_ttb_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_ttbStr);

    t_MC[i][2]->Project(Form("xy_ttLF_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]", cut_ttLFStr);
    t_MC[i][2]->Project(Form("x_ttLF_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttLFStr);
    t_MC[i][2]->Project(Form("y_ttLF_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_ttLFStr);

    t_MC[i][2]->Project(Form("xy_ttOthers_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttOthersStr);
    t_MC[i][2]->Project(Form("x_ttOthers_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_ttOthersStr);
    t_MC[i][2]->Project(Form("y_ttOthers_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_ttOthersStr);

    t_MC[i][3]->Project(Form("xy_ttSemi_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][3]->Project(Form("x_ttSemi_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][3]->Project(Form("y_ttSemi_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][4]->Project(Form("xy_ttHad_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("x_ttHad_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("y_ttHad_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][4]->Project(Form("xy_wjets_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("x_wjets_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("y_wjets_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][4]->Project(Form("xy_ww_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("x_ww_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("y_ww_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][4]->Project(Form("xy_wz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("x_wz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("y_wz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    t_MC[i][4]->Project(Form("xy_zz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("x_zz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][4]->Project(Form("y_zz_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);
 
    t_MC[i][9]->Project(Form("xy_singleTop_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][9]->Project(Form("x_singleTop_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][9]->Project(Form("y_singleTop_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);
  
    t_MC[i][10]->Project(Form("xy_singleTopBar_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]:jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][10]->Project(Form("x_singleTopBar_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[2]]",cut_selStr);
    t_MC[i][10]->Project(Form("y_singleTopBar_%s",decay.Data()),"jets_bDiscriminatorCSV[csvd_jetid[3]]",cut_selStr);

    cout << "scale" << endl;
    y_DY[i]->Scale(norm[0]);
    x_DY[i]->Scale(norm[0]);
    xy_DY[i]->Scale(norm[0]);
    y_DY10To50[i]->Scale(norm[1]);
    x_DY10To50[i]->Scale(norm[1]);
    xy_DY10To50[i]->Scale(norm[1]);
    y_ttbb[i]->Scale(norm[2]);
    x_ttbb[i]->Scale(norm[2]);
    xy_ttbb[i]->Scale(norm[2]);
    y_ttb[i]->Scale(norm[2]);
    x_ttb[i]->Scale(norm[2]);
    xy_ttb[i]->Scale(norm[2]);
    y_ttLF[i]->Scale(norm[2]);
    x_ttLF[i]->Scale(norm[2]);
    xy_ttLF[i]->Scale(norm[2]);
    y_ttOthers[i]->Scale(norm[2]);
    x_ttOthers[i]->Scale(norm[2]);
    xy_ttOthers[i]->Scale(norm[2]);
    y_ttSemi[i]->Scale(norm[3]);
    x_ttSemi[i]->Scale(norm[3]);
    xy_ttSemi[i]->Scale(norm[3]);
    y_ttHad[i]->Scale(norm[4]);
    x_ttHad[i]->Scale(norm[4]);
    xy_ttHad[i]->Scale(norm[4]);
    y_wjets[i]->Scale(norm[5]);
    x_wjets[i]->Scale(norm[5]);
    xy_wjets[i]->Scale(norm[5]);
    y_ww[i]->Scale(norm[6]);
    x_ww[i]->Scale(norm[6]);
    xy_ww[i]->Scale(norm[6]);
    y_wz[i]->Scale(norm[7]);
    x_wz[i]->Scale(norm[7]);
    xy_wz[i]->Scale(norm[7]);
    y_zz[i]->Scale(norm[8]);
    x_zz[i]->Scale(norm[8]);
    xy_zz[i]->Scale(norm[8]);
    y_singleTop[i]->Scale(norm[9]);
    x_singleTop[i]->Scale(norm[9]);
    xy_singleTop[i]->Scale(norm[9]);
    y_singleTopBar[i]->Scale(norm[10]);
    x_singleTopBar[i]->Scale(norm[10]);
    xy_singleTopBar[i]->Scale(norm[10]);

    y_QCD[i]->Scale(qcdscale);
    x_QCD[i]->Scale(qcdscale);
    xy_QCD[i]->Scale(qcdscale);

    x_DY[i]->Add(x_DY10To50[i]);
    y_DY[i]->Add(y_DY10To50[i]);
    xy_DY[i]->Add(xy_DY10To50[i]);

    x_DY[i]->Scale(dyscale);
    y_DY[i]->Scale(dyscale);
    xy_DY[i]->Scale(dyscale);

    x_ttOthers[i]->Add(x_ttSemi[i]);
    x_ttOthers[i]->Add(x_ttHad[i]);
    y_ttOthers[i]->Add(y_ttSemi[i]);
    y_ttOthers[i]->Add(y_ttHad[i]);
    xy_ttOthers[i]->Add(xy_ttSemi[i]);
    xy_ttOthers[i]->Add(xy_ttHad[i]);

    x_bkg[i]->Add(x_wjets[i]);
    y_bkg[i]->Add(y_wjets[i]);
    xy_bkg[i]->Add(xy_wjets[i]);
    x_bkg[i]->Add(x_ww[i]);
    y_bkg[i]->Add(y_ww[i]);
    xy_bkg[i]->Add(xy_ww[i]);
    x_bkg[i]->Add(x_wz[i]);
    y_bkg[i]->Add(y_wz[i]);
    xy_bkg[i]->Add(xy_wz[i]);
    x_bkg[i]->Add(x_zz[i]);
    y_bkg[i]->Add(y_zz[i]);
    xy_bkg[i]->Add(xy_zz[i]);

    x_singleTop[i]->Add(x_singleTopBar[i]);
    y_singleTop[i]->Add(y_singleTopBar[i]);
    xy_singleTop[i]->Add(xy_singleTopBar[i]);

    cout << "add..." << endl;
    double ndata = xy_data[i]->GetEntries();
    double nttbb = xy_ttbb[i]->GetEntries();
    double nttLF = xy_ttLF[i]->GetEntries();
    double nttOthers = xy_ttOthers[i]->GetEntries();
    cout << "ndata= " << ndata << " nttbb= " << nttbb << " nttLF= " << nttLF << " nttOthers= " << nttOthers << endl;
    x_data_all->Add(x_data[i]);
    y_data_all->Add(y_data[i]);
    xy_data_all->Add(xy_data[i]);
    x_DY_all->Add(x_DY[i]);
    y_DY_all->Add(y_DY[i]);
    xy_DY_all->Add(xy_DY[i]);
    x_ttbb_all->Add(x_ttbb[i]);
    y_ttbb_all->Add(y_ttbb[i]);
    xy_ttbb_all->Add(xy_ttbb[i]);
    x_ttb_all->Add(x_ttb[i]);
    y_ttb_all->Add(y_ttb[i]);
    xy_ttb_all->Add(xy_ttb[i]);
    x_ttLF_all->Add(x_ttLF[i]);
    y_ttLF_all->Add(y_ttLF[i]);
    xy_ttLF_all->Add(xy_ttLF[i]);
    x_ttOthers_all->Add(x_ttOthers[i]);
    y_ttOthers_all->Add(y_ttOthers[i]);
    xy_ttOthers_all->Add(xy_ttOthers[i]);
    x_bkg_all->Add(x_bkg[i]);
    y_bkg_all->Add(y_bkg[i]);
    xy_bkg_all->Add(xy_bkg[i]);
    x_singleTop_all->Add(x_singleTop[i]);
    y_singleTop_all->Add(y_singleTop[i]);
    xy_singleTop_all->Add(xy_singleTop[i]);
    x_QCD_all->Add(x_QCD[i]);
    y_QCD_all->Add(y_QCD[i]);
    xy_QCD_all->Add(xy_QCD[i]);

  }
   
  cout << "write..." << endl;
  double ndataall = xy_data_all->Integral();
  cout << "all data= " << ndataall << endl;
  TFile * f = new TFile("output.root","recreate");
  xy_data_all->Write();
  x_data_all->Write();
  y_data_all->Write();
  xy_DY_all->Write();
  x_DY_all->Write();
  y_DY_all->Write();
  xy_ttbb_all->Write();
  x_ttbb_all->Write();
  y_ttbb_all->Write();
  xy_ttb_all->Write();
  x_ttb_all->Write();
  y_ttb_all->Write();
  xy_ttLF_all->Write();
  x_ttLF_all->Write();
  y_ttLF_all->Write();
  xy_ttOthers_all->Write();
  x_ttOthers_all->Write();
  y_ttOthers_all->Write();
  xy_bkg_all->Write();
  x_bkg_all->Write();
  y_bkg_all->Write();
  xy_singleTop_all->Write();
  x_singleTop_all->Write();
  y_singleTop_all->Write();
  xy_QCD_all->Write();
  x_QCD_all->Write();
  y_QCD_all->Write();

  
}

double getNorm( TFile * file, double X, double lumi, const TString & dir){
     TH1F* h = (TH1F*) file->Get(Form("%s/EventSummary",dir.Data()));
     double nTotal = h->GetBinContent(1);
     double SF = lumi * X / nTotal;
     return SF;
};

