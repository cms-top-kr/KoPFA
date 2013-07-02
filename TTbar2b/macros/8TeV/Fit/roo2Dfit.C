void roo2Dfit(){

  TFile* f = new TFile("output.root");

  TH1* x_data = (TH1*) f->Get("x_data_all");
  TH1* y_data = (TH1*) f->Get("x_data_all");
  TH2* xy_data = (TH2*) f->Get("xy_data_all");
  TH1* x_DY = (TH1*) f->Get("x_DY_all");
  TH1* y_DY = (TH1*) f->Get("x_DY_all");
  TH2* xy_DY = (TH2*) f->Get("xy_DY_all");
  TH1* x_ttbb = (TH1*) f->Get("x_ttbb_all");
  TH1* y_ttbb = (TH1*) f->Get("x_ttbb_all");
  TH2* xy_ttbb = (TH2*) f->Get("xy_ttbb_all");
  TH1* x_ttb = (TH1*) f->Get("x_ttb_all");
  TH1* y_ttb = (TH1*) f->Get("x_ttb_all");
  TH2* xy_ttb = (TH2*) f->Get("xy_ttb_all");
  TH1* x_ttLF = (TH1*) f->Get("x_ttLF_all");
  TH1* y_ttLF = (TH1*) f->Get("x_ttLF_all");
  TH2* xy_ttLF = (TH2*) f->Get("xy_ttLF_all");
  TH1* x_ttOthers = (TH1*) f->Get("x_ttOthers_all");
  TH1* y_ttOthers = (TH1*) f->Get("x_ttOthers_all");
  TH2* xy_ttOthers = (TH2*) f->Get("xy_ttOthers_all");
  TH1* x_bkg = (TH1*) f->Get("x_bkg_all");
  TH1* y_bkg = (TH1*) f->Get("x_bkg_all");
  TH2* xy_bkg = (TH2*) f->Get("xy_bkg_all");
  TH1* x_singleTop = (TH1*) f->Get("x_singleTop_all");
  TH1* y_singleTop = (TH1*) f->Get("x_singleTop_all");
  TH2* xy_singleTop = (TH2*) f->Get("xy_singleTop_all");
  TH1* x_QCD = (TH1*) f->Get("x_QCD_all");
  TH1* y_QCD = (TH1*) f->Get("x_QCD_all");
  TH2* xy_QCD = (TH2*) f->Get("xy_QCD_all");

  TH2F * xy_mcbkg = new TH2F("x_mcbkg","x_mcbkg",10,0.0,1.0,10,0.0,1.0);
  TH2F * xy_databkg = new TH2F("x_databkg","x_databkg",10,0.0,1.0,10,0.0,1.0);
  xy_mcbkg->Add(xy_bkg);
  xy_mcbkg->Add(xy_ttOthers);
  // to include single top
  xy_mcbkg->Add(xy_singleTop);
  // combine data-driven backgrounds
  xy_databkg->Add(xy_DY);
  xy_databkg->Add(xy_QCD);

  double nVisible = xy_ttbb->Integral() + xy_ttLF->Integral() + xy_ttb->Integral();
  double nTtLF = xy_ttLF->Integral();
  double nTtb = xy_ttb->Integral();
  double rttb = nTtb/nVisible;
  double nOthers = xy_ttOthers->Integral();
  double nTtbar = nVisible + nOthers;
  double nSingleTop = xy_singleTop->Integral();
  double nMCBkg = xy_mcbkg->Integral();
  double nDataBkg = xy_databkg->Integral();
  double nDY  = xy_DY->Integral();
  double nQCD = xy_QCD->Integral();
  double eR = 0.382948;
  //double eR = 0.3888;
  //basic
  RooRealVar x("x","x",0,1) ; 
  RooRealVar y("y","y",0,1) ; 
  RooRealVar R("R","R",0.1,0.,1.);
  RooRealVar effR("effR","acceptance ratio",eR,eR,eR);
  RooFormulaVar fsig("fsig","fraction of signal","R/effR",RooArgList(R,effR));
  RooRealVar fttb("fttb","fraction of ttb",rttb,0.0,1.0);
  RooRealVar k("k","normalization factor", 1.0, 0.0, 2.0) ;
  RooRealVar nttjj("nttjj","number of nttjj events", nVisible, nVisible, nVisible) ;
  RooFormulaVar knttjj("knttjj","number of ttjj events after fitting","k*nttjj",RooArgList(k,nttjj));
  RooRealVar nmcbkg("nmcbkg","number of mc background events", nMCBkg, nMCBkg, nMCBkg) ;
  RooFormulaVar knmcbkg("knmcbkg","number of mc background events after fitting","k*nmcbkg",RooArgList(k,nmcbkg) );

  //ttbar and single top separate
  RooRealVar nttbar("nttbar","number of ttbar events", nTtbar , nTtbar, nTtbar) ;
  RooFormulaVar kttbar("kttbar","number of ttbar events after fitting","k*nttbar",RooArgList(k,nttbar) );
  RooRealVar s("s","normalization factor", 1.0, 0.0, 2.0) ;
  RooRealVar nsingleTop("nsingleTop","number of single top events", nSingleTop , nSingleTop, nSingleTop) ;
  RooFormulaVar snsingleTop("snsingleTop","number of single top events after fitting","k*nsingleTop",RooArgList(s,nsingleTop) );
  
  //data-driven background
  RooRealVar ndatabkg("ndatabkg","number of data-driven events", nDataBkg , nDataBkg, nDataBkg) ;

  //histograms
  RooDataHist data("data","data set with (x,y)", RooArgList(x,y), xy_data);
  RooDataHist ttbb("ttbb","ttbb set with (x,y)", RooArgList(x,y), xy_ttbb);
  RooDataHist ttb("ttb","ttb set with (x,y)", RooArgList(x,y), xy_ttb);
  RooDataHist ttLF("ttLF","ttLF set with (x,y)", RooArgList(x,y), xy_ttLF);
  RooDataHist ttOthers("ttOthers","ttOthers set with (x,y)", RooArgList(x,y), xy_ttOthers);
  RooDataHist singleTop("singleTop","singleTop set with (x,y)", RooArgList(x,y), xy_singleTop);
  RooDataHist mcbkg("mcbkg","bkg set with (x,y)", RooArgList(x,y), xy_mcbkg);
  RooDataHist databkg("databkg","bkg set with (x,y)", RooArgList(x,y), xy_databkg);

  //pdf 
  RooHistPdf ttbbpdf("ttbbpdf","ttbbpdf", RooArgList(x,y), ttbb);
  RooHistPdf ttbpdf("ttbpdf","ttbpdf", RooArgList(x,y), ttb);
  RooHistPdf ttLFpdf("ttLFpdf","ttLFpdf", RooArgList(x,y), ttLF);
  RooHistPdf ttOtherspdf("ttOtherspdf","ttOtherspdf", RooArgList(x,y), ttOthers);
  RooHistPdf singleToppdf("singleToppdf","singleToppdf", RooArgList(x,y), singleTop);
  RooHistPdf mcbkgpdf("mcbkgpdf","mcbkgpdf", RooArgList(x,y), mcbkg);
  RooHistPdf databkgpdf("databkgpdf","databkgpdf", RooArgList(x,y), databkg);

  //RooAddPdf ttLFmodel("ttLF", "R*ttb+(1-R)*ttLF",RooArgList( ttbpdf, ttLFpdf), RooArgList(fttb));
  //RooAddPdf model("model", "R*sig+(1-R)*bkg",RooArgList( ttbbpdf, ttLFmodel), RooArgList(fsig));
  RooAddPdf model("model", "R*sig+Rb*ttb+(1-R-Rb)*bkg",RooArgList( ttbbpdf, ttbpdf, ttLFpdf), RooArgList(fsig,fttb));
  RooAddPdf model2("model2","k*nttjj*(R*sig+(1-R)*bkg)+k*nmcbkg*bkgpdf",RooArgList( model, mcbkgpdf), RooArgList(knttjj, knmcbkg) );
  RooAddPdf model3("model3","k*nttjj*(R*sig+(1-R)*bkg)+k*nmcbkg*bkgpdf+ndatabkg*databkgpdf",RooArgList( model, mcbkgpdf, databkgpdf), RooArgList(knttjj, knmcbkg, ndatabkg) ) ;
  //separate single top
  RooAddPdf model4("model4","k*nttjj*(R*sig+(1-R)*bkg)+k*nmcbkg*bkgpdf+s*nsingeTop*singleToppdf+ndatabkg*databkgpdf",RooArgList( model, mcbkgpdf, singleToppdf, databkgpdf), RooArgList(knttjj, knmcbkg, snsingleTop, ndatabkg) ) ;

  model3.fitTo(data);

  RooPlot * xframe = x.frame();
  //data.plotOn(xframe, DataError(RooAbsData::SumW2) ) ;
  //model3.plotOn(xframe,Components("ttbbpdf,ttLFpdf,mcbkgpdf,databkgdf"),LineColor(4),FillColor(4),DrawOption("F")) ;
  //model3.plotOn(xframe,Components("ttbbpdf,ttLFpdf"),LineColor(3),FillColor(3),DrawOption("F")) ;
  //model3.plotOn(xframe,Components("ttbb"),LineColor(2),FillColor(2),DrawOption("F")) ;
  data.plotOn(xframe ) ;
  model3.plotOn(xframe);

  RooPlot * yframe = y.frame();
  //data.plotOn(yframe, DataError(RooAbsData::SumW2) ) ;
  //model3.plotOn(yframe,Components("ttbbpdf,ttLFpdf,mcbkgpdf,databkgdf"),LineColor(4),FillColor(4),DrawOption("F")) ;
  //model3.plotOn(yframe,Components("ttbbpdf,ttLFpdf"),LineColor(3),FillColor(3),DrawOption("F")) ;
  //model3.plotOn(yframe,Components("ttbb"),LineColor(2),FillColor(2),DrawOption("F")) ;
  data.plotOn(yframe ) ;
  model3.plotOn(yframe);

  TCanvas *c = new TCanvas("c","c",800,400);
  c->Divide(2) ; 
  c->cd(1) ; xframe->Draw() ; 
  c->cd(2) ; yframe->Draw() ; 

  RooArgSet* params = model3.getVariables() ; 
  params->Print("v"); 
/*
  RooAbsReal* nll = model3.createNLL(data);

  RooPlot* RFrame = R.frame();
  nll->plotOn(RFrame);
  TCanvas* cR = new TCanvas("R", "R", 500, 500);
  RFrame->Draw();

  RooPlot* kFrame = k.frame();
  nll->plotOn(kFrame);
  TCanvas* ck = new TCanvas("k", "k", 500, 500);
  kFrame->Draw();
*/
}
