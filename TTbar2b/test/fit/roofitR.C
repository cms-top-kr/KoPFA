void roofitR(){

  bool combine = false;
  int nbinsch = 5;

  //CSVM efficiency ratio
  double eR = 0.47;

  using namespace RooFit ;

  TString path = "../TTBB_13Jan2013_CSVM";
  TString fileName[3];
  fileName[0] = path+"/MuMu/MuMu.root";
  fileName[1] = path+"/MuEl/MuEl.root";
  fileName[2] = path+"/ElEl/ElEl.root";

  TH1F * hdata[3];
  TH1F * httbb[3];
  TH1F * httll[3];
  TH1F * httcc[3];
  TH1F * httothers[3];
  TH1F * hWl[3];
  TH1F * hVV[3];
  TH1F * hSingleTop[3];
  TH1F * hDYll[3];

  //combine background
  TH1F * hbkg[3];
  TH1F * hdbg[3];

  int nbins = 3*nbinsch;
  TH1F * h_ttbb = new TH1F("h_ttbb","h_ttbb", nbins , 0, nbins);
  TH1F * h_ttcc = new TH1F("h_ttcc","h_ttcc", nbins , 0, nbins);
  TH1F * h_ttll = new TH1F("h_ttll","h_ttll", nbins , 0, nbins);
  TH1F * h_ttccll = new TH1F("h_ttccll","h_ttccll", nbins , 0, nbins);
  TH1F * h_dat = new TH1F("h_dat","h_dat",nbins , 0, nbins);
  TH1F * h_bkg = new TH1F("h_bkg","h_bkg",nbins , 0, nbins);
  TH1F * h_dbg = new TH1F("h_dbg","h_dbg",nbins , 0, nbins);

  for(int i=0; i < 3; i++){

    TFile * f = new TFile(fileName[i]);
    hdata[i]      = (TH1F*) f->Get("Step_1/hData_Step_1_nbJet30_CSVM");
    httbb[i]      = (TH1F*) f->Get("Step_1/hMCSig_TTbarbb_Step_1_nbJet30_CSVM");
    httll[i]      = (TH1F*) f->Get("Step_1/hMC_TTbarll_Step_1_nbJet30_CSVM");
    httcc[i]      = (TH1F*) f->Get("Step_1/hMC_TTbarcc_Step_1_nbJet30_CSVM");
    httothers[i]  = (TH1F*) f->Get("Step_1/hMC_TTbarOthers_Step_1_nbJet30_CSVM");
    hWl[i]        = (TH1F*) f->Get("Step_1/hMC_Wl_Step_1_nbJet30_CSVM");
    hVV[i]        = (TH1F*) f->Get("Step_1/hMC_VV_Step_1_nbJet30_CSVM");
    hSingleTop[i] = (TH1F*) f->Get("Step_1/hMC_SingleTop_Step_1_nbJet30_CSVM");
    hDYll[i]      = (TH1F*) f->Get("Step_1/hMC_DYll_Step_1_nbJet30_CSVM"); 

    //MC background
    TH1F * htmpbkg = httothers[i]->Clone();
    htmpbkg->Add(hWl[i]);
    htmpbkg->Add(hVV[i]);
    htmpbkg->Add(hSingleTop[i]);
    hbkg[i] = htmpbkg;
    //data driven background
    TH1F * htmpdbg = hDYll[i]->Clone();
    hdbg[i] = htmpdbg;

    int Nbins = hdata[i]->GetNbinsX();
 
    for(int k = 1; k <= Nbins; k++){
      int nb = k + i*nbinsch;
      if( k < Nbins || combine == false){
        h_ttbb->SetBinContent(nb, httbb[i]->GetBinContent(k) );
        h_ttcc->SetBinContent(nb, httcc[i]->GetBinContent(k) );
        h_ttll->SetBinContent(nb, httll[i]->GetBinContent(k) );
        h_ttccll->SetBinContent(nb, httcc[i]->GetBinContent(k) + httll[i]->GetBinContent(k) );
        h_dat->SetBinContent(nb, hdata[i]->GetBinContent(k) );
        h_bkg->SetBinContent(nb, hbkg[i]->GetBinContent(k) );
        h_dbg->SetBinContent(nb, hdbg[i]->GetBinContent(k) );
      }else if( k == Nbins && combine == true){
        h_ttbb->AddBinContent(nb-1, httbb[i]->GetBinContent(k) );
        h_ttcc->AddBinContent(nb-1, httcc[i]->GetBinContent(k) );
        h_ttll->AddBinContent(nb-1, httll[i]->GetBinContent(k) );
        h_ttccll->AddBinContent(nb-1, httcc[i]->GetBinContent(k) + httll[i]->GetBinContent(k) );
        h_dat->AddBinContent(nb-1, hdata[i]->GetBinContent(k) );
        h_bkg->AddBinContent(nb-1, hbkg[i]->GetBinContent(k) );
        h_dbg->AddBinContent(nb-1, hdbg[i]->GetBinContent(k) );
      }
    }

  }

  double nttbb   =  h_ttbb->Integral();
  double nttll   =  h_ttll->Integral();
  double nttcc   =  h_ttcc->Integral();
  double nbkg    =  h_bkg->Integral();
  double ndbg    =  h_dbg->Integral();
  double nMCtotal = nttbb + nttll + nttcc + nbkg;
  double rsig    =  nttbb/(nttbb + nttcc + nttll);
  double rbkg    =  (nbkg)/(nttbb + nttcc + nttll + nbkg);
  cout << "ttbb= " << nttbb << " ttcc= " << nttcc << " ttll= " << nttll << " R(ttbb/ttjj)= " <<  rsig << "  nbkg= " << nbkg << " fbkg= " << rbkg << " total MC = " << nMCtotal << " data-driven bkg= " << ndbg << endl;
 
  RooRealVar x("x","x",0,15) ;

  RooDataHist data("data","data",x,h_dat) ; 
  RooDataHist ttbb("ttbb","ttbb",x,h_ttbb) ; 
  RooDataHist ttcc("ttcc","ttcc",x,h_ttcc) ; 
  RooDataHist ttll("ttll","ttll",x,h_ttll) ; 
  RooDataHist ttccll("ttccll","ttccll",x,h_ttccll) ; 
  RooDataHist bkg("bkg","bkg",x,h_bkg); 
  RooDataHist dbg("dbg","dbg",x,h_dbg); 

  RooHistPdf histpdf_ttbb("histpdf_ttbb","histpdf_ttbb",x, ttbb) ;
  RooHistPdf histpdf_ttcc("histpdf_ttcc","histpdf_ttcc",x, ttcc) ;
  RooHistPdf histpdf_ttll("histpdf_ttll","histpdf_ttll",x, ttll) ;
  RooHistPdf histpdf_ttccll("histpdf_ttccll","histpdf_ttccll",x, ttccll) ;
  RooHistPdf histpdf_bkg("histpdf_bkg","histpdf_bkg",x, bkg) ;
  RooHistPdf histpdf_dbg("histpdf_dbg","histpdf_dbg",x, dbg) ;

  RooRealVar R("R","R",0.1,0.,1.);
  RooRealVar effR("effR","acceptance ratio",eR,eR,eR);
  RooFormulaVar fsig("fsig","fraction of signal","R/effR",RooArgList(R,effR));
  RooRealVar fbkg("fbkg","fraction of background", rbkg , rbkg, rbkg) ;
  RooRealVar nMC("nMC","number of MC events", 1000 , 500, 5000) ;
  RooRealVar nDataBkg("nDataBkg","number of data-driven events", ndbg , ndbg, ndbg) ;

  // Sum the composite signal and background 
  RooAddPdf model("model", "R*sig+(1-R)*bkg",RooArgList( histpdf_ttbb, histpdf_ttccll), RooArgList(fsig));
  RooAddPdf model2("model2","(1-fbkg)*(R*sig+(1-R)*bkg)+fbkg*MCbkg",RooArgList(histpdf_bkg, model), fbkg) ;
  RooAddPdf model3("model3","nMC*(1-fbkg)*(R*sig+(1-R)*bkg)+fbkg*MCbkg+ndbkg",RooArgList(model2, histpdf_dbg), RooArgList(nMC,nDataBkg)) ;

  RooFitResult* fitResult = model3.fitTo( data );

  TCanvas * c = new TCanvas("c","c",1);
  RooPlot* xframe = x.frame() ; 
  data.plotOn(xframe); 
  model3.paramOn(xframe, Layout(0.6,0.9,0.9) );
  model3.plotOn(xframe);
  xframe->Draw();   

}
