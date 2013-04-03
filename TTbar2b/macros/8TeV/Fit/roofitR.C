void roofitR(){

  gROOT->ProcessLine(".L $CMSSW_BASE/src/KoPFA/CommonTools/macros/tdrstyle.C");
  defaultStyle();
 
  using namespace RooFit ;

  bool combine = true;
  int nbinsch = 20; //number of bins for each histograms. for example, b-jets multiplicity = 5 , b-dscriminatorCSV = 20, b-discriminatorJP = 50
  const int ndecay = 3; // mm, em, ee
  const int nobj = 2; // 1: b-jet mulitplicity , 2 :jet1, jet2 

  //CSVM efficiency ratio
  //double eR = 0.473795;
  //CSVT efficiency ratio
  double eR = 0.382948;
  //double eR = 0.750311; //nJet30 >= 4

  TString path = "/afs/cern.ch/work/t/tjkim/public/store/ttbb/paper/8TeV/histos/TTBB_CSVT";
  TString decay[ndecay];
  decay[0] = "MuMu";
  decay[1] = "MuEl";
  decay[2] = "ElEl";

  TString fileName[ndecay];
  fileName[0] = path+"/"+decay[0]+"/"+decay[0]+".root";
  fileName[1] = path+"/"+decay[1]+"/"+decay[1]+".root";
  fileName[2] = path+"/"+decay[2]+"/"+decay[2]+".root";
  TString variable[nobj];
  //variable[0] = "nbJet30_CSVT";
  variable[0] = "addjet1_bDisCSV";
  variable[1] = "addjet2_bDisCSV";
  //variable[0] = "addjet1_bDisJP";
  //variable[1] = "addjet2_bDisJP";
  TString step[nobj];
  step[0] = "Step_6";
  step[1] = "Step_7";

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
  if( combine ) nbins = nbinsch*nobj;
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
      hdata[i][j]      = (TH1F*) f->Get(Form("%s/hData_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      httbb[i][j]      = (TH1F*) f->Get(Form("%s/hMCSig_TTbarbb_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      httll[i][j]      = (TH1F*) f->Get(Form("%s/hMC_TTbarll_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      httcc[i][j]      = (TH1F*) f->Get(Form("%s/hMC_TTbarcc_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      httothers[i][j]  = (TH1F*) f->Get(Form("%s/hMC_TTbarOthers_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      hWl[i][j]        = (TH1F*) f->Get(Form("%s/hMC_Wl_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      hVV[i][j]        = (TH1F*) f->Get(Form("%s/hMC_VV_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      hSingleTop[i][j] = (TH1F*) f->Get(Form("%s/hMC_SingleTop_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data()));
      hDYll[i][j]      = (TH1F*) f->Get(Form("%s/hMC_DYll_%s_%s", step[j].Data(), step[j].Data(), variable[j].Data())); 

/*
      hdata[i][j]->Rebin(2);
      httbb[i][j]->Rebin(2);
      httll[i][j]->Rebin(2);
      httcc[i][j]->Rebin(2);
      httothers[i][j]->Rebin(2);
      hWl[i][j]->Rebin(2);
      hVV[i][j]->Rebin(2);
      hSingleTop[i][j]->Rebin(2);
      hDYll[i][j]->Rebin(2);
*/

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
        if(combine) nb = k + j*nbinsch;
        if( i == 0 || combine == false){
          h_ttbb->SetBinContent(nb, httbb[i][j]->GetBinContent(k) );
          h_ttcc->SetBinContent(nb, httcc[i][j]->GetBinContent(k) );
          h_ttll->SetBinContent(nb, httll[i][j]->GetBinContent(k) );
          h_ttccll->SetBinContent(nb, httcc[i][j]->GetBinContent(k) + httll[i][j]->GetBinContent(k) );
          h_dat->SetBinContent(nb, hdata[i][j]->GetBinContent(k) );
          h_bkg->SetBinContent(nb, hbkg[i][j]->GetBinContent(k) );
          h_dbg->SetBinContent(nb, hdbg[i][j]->GetBinContent(k) );
        }else if( i > 0 && combine == true){
          h_ttbb->AddBinContent(nb, httbb[i][j]->GetBinContent(k) );
          h_ttcc->AddBinContent(nb, httcc[i][j]->GetBinContent(k) );
          h_ttll->AddBinContent(nb, httll[i][j]->GetBinContent(k) );
          h_ttccll->AddBinContent(nb, httcc[i][j]->GetBinContent(k) + httll[i][j]->GetBinContent(k) );
          h_dat->AddBinContent(nb, hdata[i][j]->GetBinContent(k) );
          h_bkg->AddBinContent(nb, hbkg[i][j]->GetBinContent(k) );
          h_dbg->AddBinContent(nb, hdbg[i][j]->GetBinContent(k) );
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
  double nttjj     =  nttbb + nttcc + nttll;
  double rsig    =  nttbb/nttjj;
  double rbkg    =  (nbkg)/(nttjj + nbkg);
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
  data.plotOn(xframe, DataError(RooAbsData::SumW2) );
  model3.paramOn(xframe, Layout(0.65,0.9,0.9) );
  model3.plotOn(xframe,Components("histpdf_ttbb,histpdf_ttccll,histpdf_bkg,histpdf_dbg"),LineColor(4),FillColor(4),DrawOption("F")) ;
  model3.plotOn(xframe,Components("histpdf_ttbb,histpdf_ttccll"),LineColor(3),FillColor(3),DrawOption("F")) ;
  model3.plotOn(xframe,Components("histpdf_ttbb"),LineColor(2),FillColor(2),DrawOption("F")) ;
  model3.plotOn(xframe);
  data.plotOn(xframe, DataError(RooAbsData::SumW2) ) ; 
  xframe->Draw();
  
  double recoR = R.getVal()/eR;
  double scaleMC = nMC.getVal()/nMCtotal;

  TH1F* h_combined_data[2];
  TH1F* h_combined_ttbb[2];
  TH1F* h_combined_ttcc[2];
  TH1F* h_combined_ttll[2];
  TH1F* h_combined_dbg[2];
  TH1F* h_combined_bkg[2];

  for(int j = 0 ; j < 2 ; j++){

    h_combined_ttbb[j] = new TH1F(Form("h_combined_%s_ttbb", variable[j].Data()),Form("h_combined_%s_ttbb", variable[j].Data()), nbinsch , 0, 1);
    h_combined_ttll[j] = new TH1F(Form("h_combined_%s_ttll", variable[j].Data()),Form("h_combined_%s_ttll", variable[j].Data()), nbinsch , 0, 1);
    h_combined_ttcc[j] = new TH1F(Form("h_combined_%s_ttcc", variable[j].Data()),Form("h_combined_%s_ttcc", variable[j].Data()), nbinsch , 0, 1);
    h_combined_data[j] = new TH1F(Form("h_combined_%s_data", variable[j].Data()),Form("h_combined_%s_data", variable[j].Data()),nbinsch , 0, 1);
    h_combined_dbg[j] = new TH1F(Form("h_combined_%s_dbg", variable[j].Data()),Form("h_combined_%s_dbg", variable[j].Data()),nbinsch , 0, 1);
    h_combined_bkg[j] = new TH1F(Form("h_combined_%s_bkg", variable[j].Data()),Form("h_combined_%s_bkg", variable[j].Data()),nbinsch , 0, 1);

    for(int i = 0 ; i < 3; i++){
      h_combined_data[j]->Add(hdata[i][j]);
      h_combined_ttbb[j]->Add(httbb[i][j]);
      h_combined_ttcc[j]->Add(httcc[i][j]);
      h_combined_ttll[j]->Add(httll[i][j]);
      h_combined_dbg[j]->Add(hdbg[i][j]);
      h_combined_bkg[j]->Add(hbkg[i][j]);
    }
  }

/*
  TCanvas * c_fit = new TCanvas("c_fit","c_fit",1200,800);
  c_fit->Divide(3,2); 

  for(int i = 0 ; i < 3; i++){
    for(int j = 0 ; j < 2; j++){ 
      //TCanvas * c_fit = new TCanvas(Form("c_fit_%s_%s",decay[i].Data(),variable[j].Data()),Form("c_fit_%s_%s",decay[i].Data(),variable[j].Data()),1);
      //c_fit->SetLogy();
      int num = i+1+j*3;
      c_fit->cd(num);      
      gPad->SetLogy();

      TH1F* hist_data = hdata[i][j]->Clone();
      TH1F* hist_ttbb = httbb[i][j]->Clone();
      TH1F* hist_ttccll = httcc[i][j]->Clone();
      TH1F* hist_ttll = httll[i][j]->Clone();
      TH1F* hist_background   = hdbg[i][j]->Clone();
      TH1F* hist_mcbackground = hbkg[i][j]->Clone();

      hist_ttccll->Add(hist_ttll);
      hist_ttbb->Scale( scaleMC*recoR*nttjj/nttbb);
      hist_ttccll->Scale( scaleMC*(1-recoR)*nttjj/(nttll+nttcc));
      hist_mcbackground->Scale( scaleMC );

      hist_background->Add(hist_mcbackground); 
      hist_data->Add(hist_background, -1);

      hist_ttbb->SetFillColor(kBlue+2);
      hist_ttbb->SetFillStyle(3354);
      hist_ttccll->SetFillColor(kRed);
      hist_background->SetFillColor(4);

      hist_data->Draw();
      hist_data->GetXaxis()->SetTitle("b-Discriminator (CSV)");
      if( j == 0 ) hist_data->GetYaxis()->SetTitle("First Additional Jets");
      if( j == 1 ) hist_data->GetYaxis()->SetTitle("Second Additional Jets");

      THStack *MC = new THStack();
      MC->Add(hist_ttbb);
      MC->Add(hist_ttccll);
      //MC->Add(h_final_background);

      MC->Draw();
      MC->SetMinimum(0.2);
      //MC->SetMaximum(1000);
      MC->SetMaximum(1800);

      MC->GetXaxis()->SetTitle("b-Discriminator (CSV)");
      if( j == 0 ) MC->GetYaxis()->SetTitle("First Additional Jets");
      if( j == 1 ) MC->GetYaxis()->SetTitle("Second Additional Jets");

      hist_data->SetMarkerSize(1);
      hist_data->SetMarkerStyle(20);
      hist_data->Draw("samePE");

      TLatex *label= new TLatex;
      label->SetNDC();
      label->SetTextSize(0.05);
      label->DrawLatex(0.22,0.82,"CMS");
      label->DrawLatex(0.22,0.82-0.05,"19.6 fb^{-1} at #sqrt{s} = 8 TeV");

      TLegend *l = new TLegend(0.73,0.74,0.90,0.88);
      l->AddEntry(hist_data,"Data","PL");
      l->AddEntry(hist_ttccll,"t#bar{t} + cc/LF","F");
      l->AddEntry(hist_ttbb,"t#bar{t} + bb","F");
      l->SetTextSize(0.04);
      l->SetFillColor(0);
      l->SetLineColor(0);
      l->Draw();


    }
  }
*/

  TCanvas * c_fit_combined = new TCanvas("c_fit_combined","c_fit_combined",1200,600);
  c_fit_combined->Divide(2,1);    

  for(int j = 0 ; j < 2; j++){
    int num = 1+j;
    c_fit_combined->cd(num);      
    gPad->SetLogy();
  
    TH1F* hist_combined_data = h_combined_data[j]->Clone();
    TH1F* hist_combined_ttbb = h_combined_ttbb[j]->Clone();
    TH1F* hist_combined_ttccll = h_combined_ttcc[j]->Clone();
    TH1F* hist_combined_ttll = h_combined_ttll[j]->Clone();
    TH1F* hist_combined_background   = h_combined_dbg[j]->Clone();
    TH1F* hist_combined_mcbackground = h_combined_bkg[j]->Clone();
  
    hist_combined_ttccll->Add(hist_combined_ttll);
    hist_combined_ttbb->Scale( scaleMC*recoR*nttjj/nttbb);
    hist_combined_ttccll->Scale( scaleMC*(1-recoR)*nttjj/(nttll+nttcc));
    hist_combined_mcbackground->Scale( scaleMC );
  
    hist_combined_background->Add(hist_combined_mcbackground);
    hist_combined_data->Add(hist_combined_background, -1);

    hist_combined_ttbb->SetFillColor(kBlue+2);
    hist_combined_ttbb->SetFillStyle(3354);
    hist_combined_ttccll->SetFillColor(kRed);
    hist_combined_background->SetFillColor(4);
    
    hist_combined_data->Draw();
    hist_combined_data->GetXaxis()->SetTitle("b-Discriminator (CSV)");
    if( j == 0 ) hist_combined_data->GetYaxis()->SetTitle("First Additional Jets");
    if( j == 1 ) hist_combined_data->GetYaxis()->SetTitle("Second Additional Jets");

    THStack *MC = new THStack();
    MC->Add(hist_combined_ttbb);
    MC->Add(hist_combined_ttccll);
    //MC->Add(h_final_background);
    
    MC->Draw();
    MC->SetMinimum(0.2);
    //MC->SetMaximum(1000);
    MC->SetMaximum(1800);
  
    MC->GetXaxis()->SetTitle("b-Discriminator (CSV)");
    if( j == 0 ) MC->GetYaxis()->SetTitle("First Additional Jets");
    if( j == 1 ) MC->GetYaxis()->SetTitle("Second Additional Jets");

    hist_combined_data->SetMarkerSize(1);
    hist_combined_data->SetMarkerStyle(20);
    hist_combined_data->Draw("samePE");

    TLatex *label= new TLatex;
    label->SetNDC();
    label->SetTextSize(0.05);
    label->DrawLatex(0.22,0.82,"CMS");
    label->DrawLatex(0.22,0.82-0.05,"19.6 fb^{-1} at #sqrt{s} = 8 TeV");

    TLegend *l = new TLegend(0.73,0.74,0.90,0.88);
    l->AddEntry(hist_combined_data,"Data","PL");
    l->AddEntry(hist_combined_ttccll,"t#bar{t} + cc/LF","F");
    l->AddEntry(hist_combined_ttbb,"t#bar{t} + bb","F");
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();

  }
 
  //c_fit->Print("c_final_fit.eps");
  c_fit_combined->Print("c_final_fit_combined.eps");

}
