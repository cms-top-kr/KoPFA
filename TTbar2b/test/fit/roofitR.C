void roofitR(){
  
  using namespace RooFit ;

  bool combine = false;
  int nbinsch = 50; //number of bins for each histograms. for example, b-jets multiplicity = 5 , b-dscriminatorCSV = 20, b-discriminatorJP = 50
  const int ndecay = 3; // mm, em, ee
  const int nobj = 2; // 1: b-jet mulitplicity , 2 :jet1, jet2 

  //CSVM efficiency ratio
  //double eR = 0.473795;
  //CSVT efficiency ratio
  double eR = 0.382948;
  //double eR = 0.750311; //nJet30 >= 4

  TString path = "../TTBB_10Feb_CSVT";
  TString fileName[ndecay];
  fileName[0] = path+"/MuMu/MuMu.root";
  fileName[1] = path+"/MuEl/MuEl.root";
  fileName[2] = path+"/ElEl/ElEl.root";
  TString variable[nobj];
  //variable[0] = "nbJet30_CSVT";
  //variable[0] = "addjet1_bDisCSV";
  //variable[1] = "addjet2_bDisCSV";
  variable[0] = "addjet1_bDisJP";
  variable[1] = "addjet2_bDisJP";



  TH1F * hdata[ndecay][nobj];
  TH1F * httbb[ndecay][nobj];
  TH1F * httll[ndecay][nobj];
  TH1F * httcc[ndecay][nobj];
  TH1F * httothers[ndecay][nobj];
  TH1F * hWl[ndecay][nobj];
  TH1F * hVV[ndecay][nobj];
  TH1F * hSingleTop[ndecay][nobj];
  TH1F * hDYll[ndecay][nobj];

  //combine background
  TH1F * hbkg[ndecay][nobj];
  TH1F * hdbg[ndecay][nobj];

  int nbins = 3*nbinsch*nobj;
  TH1F * h_ttbb = new TH1F("h_ttbb","h_ttbb", nbins , 0, nbins);
  TH1F * h_ttcc = new TH1F("h_ttcc","h_ttcc", nbins , 0, nbins);
  TH1F * h_ttll = new TH1F("h_ttll","h_ttll", nbins , 0, nbins);
  TH1F * h_ttccll = new TH1F("h_ttccll","h_ttccll", nbins , 0, nbins);
  TH1F * h_dat = new TH1F("h_dat","h_dat",nbins , 0, nbins);
  TH1F * h_bkg = new TH1F("h_bkg","h_bkg",nbins , 0, nbins);
  TH1F * h_dbg = new TH1F("h_dbg","h_dbg",nbins , 0, nbins);
  
  for(int i=0; i < ndecay; i++){
    TFile * f = new TFile(fileName[i]);
    for(int j=0; j < nobj ; j++){
      hdata[i][j]      = (TH1F*) f->Get(Form("Step_5/hData_Step_5_%s", variable[j].Data()));
      httbb[i][j]      = (TH1F*) f->Get(Form("Step_5/hMCSig_TTbarbb_Step_5_%s", variable[j].Data()));
      httll[i][j]      = (TH1F*) f->Get(Form("Step_5/hMC_TTbarll_Step_5_%s", variable[j].Data()));
      httcc[i][j]      = (TH1F*) f->Get(Form("Step_5/hMC_TTbarcc_Step_5_%s", variable[j].Data()));
      httothers[i][j]  = (TH1F*) f->Get(Form("Step_5/hMC_TTbarOthers_Step_5_%s", variable[j].Data()));
      hWl[i][j]        = (TH1F*) f->Get(Form("Step_5/hMC_Wl_Step_5_%s", variable[j].Data()));
      hVV[i][j]        = (TH1F*) f->Get(Form("Step_5/hMC_VV_Step_5_%s", variable[j].Data()));
      hSingleTop[i][j] = (TH1F*) f->Get(Form("Step_5/hMC_SingleTop_Step_5_%s", variable[j].Data()));
      hDYll[i][j]      = (TH1F*) f->Get(Form("Step_5/hMC_DYll_Step_5_%s", variable[j].Data())); 
      //MC background
      TH1F * htmpbkg = httothers[i][j]->Clone();
      htmpbkg->Add(hWl[i][j]);
      htmpbkg->Add(hVV[i][j]);
      htmpbkg->Add(hSingleTop[i][j]);
      //htmpbkg->Add(hDYll[i][j]);
      hbkg[i][j] = htmpbkg;
      //data driven background
      TH1F * htmpdbg = hDYll[i][j]->Clone();
      hdbg[i][j] = htmpdbg;

      int Nbins = hdata[i][j]->GetNbinsX();

      for(int k = 1; k <= Nbins; k++){
        int nb = k + i*nbinsch + j*3*nbinsch;
        if( k < Nbins || combine == false){
          h_ttbb->SetBinContent(nb, httbb[i][j]->GetBinContent(k) );
          h_ttcc->SetBinContent(nb, httcc[i][j]->GetBinContent(k) );
          h_ttll->SetBinContent(nb, httll[i][j]->GetBinContent(k) );
          h_ttccll->SetBinContent(nb, httcc[i][j]->GetBinContent(k) + httll[i][j]->GetBinContent(k) );
          h_dat->SetBinContent(nb, hdata[i][j]->GetBinContent(k) );
          h_bkg->SetBinContent(nb, hbkg[i][j]->GetBinContent(k) );
          h_dbg->SetBinContent(nb, hdbg[i][j]->GetBinContent(k) );
        }else if( k == Nbins && combine == true){
          h_ttbb->AddBinContent(nb-1, httbb[i][j]->GetBinContent(k) );
          h_ttcc->AddBinContent(nb-1, httcc[i][j]->GetBinContent(k) );
          h_ttll->AddBinContent(nb-1, httll[i][j]->GetBinContent(k) );
          h_ttccll->AddBinContent(nb-1, httcc[i][j]->GetBinContent(k) + httll[i][j]->GetBinContent(k) );
          h_dat->AddBinContent(nb-1, hdata[i][j]->GetBinContent(k) );
          h_bkg->AddBinContent(nb-1, hbkg[i][j]->GetBinContent(k) );
          h_dbg->AddBinContent(nb-1, hdbg[i][j]->GetBinContent(k) );
        }
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
 
  RooRealVar x("x","x",0, nbins) ;
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
  //RooRealVar effR("effR","acceptance ratio",0.38,0.0,1.0);
  RooFormulaVar fsig("fsig","fraction of signal","R/effR",RooArgList(R,effR));
  RooRealVar fbkg("fbkg","fraction of background", rbkg , rbkg, rbkg) ;
  //RooRealVar fbkg("fbkg","fraction of background", 0.1 , 0, 1) ;
  RooRealVar nMC("nMC","number of MC events", 1000 , 500, 20000) ;
  RooRealVar nDataBkg("nDataBkg","number of data-driven events", ndbg , ndbg, ndbg) ;
  //RooRealVar nDataBkg("nDataBkg","number of data-driven events", 10 , 0, 1000) ;

  // Sum the composite signal and background 
  RooAddPdf model("model", "R*sig+(1-R)*bkg",RooArgList( histpdf_ttbb, histpdf_ttccll), RooArgList(fsig));
  RooAddPdf model2("model2","(1-fbkg)*(R*sig+(1-R)*bkg)+fbkg*MC",RooArgList(histpdf_bkg, model), fbkg) ;
  RooAddPdf model3("model3","nMC*(1-fbkg)*(R*sig+(1-R)*bkg)+fbkg*MC+ndbkg",RooArgList(model2, histpdf_dbg), RooArgList(nMC,nDataBkg)) ;

  RooFitResult* fitResult = model3.fitTo( data );

  TCanvas * c = new TCanvas("c","c",1);
  RooPlot* xframe = x.frame() ; 
  data.plotOn(xframe); 
  model3.paramOn(xframe, Layout(0.65,0.9,0.9) );
  model3.plotOn(xframe);
  xframe->Draw();   

}
