double weight(double x, bool isW=false)
{
   double ww = 0.749644+3.09749*x-9.98179*pow(x,2)+19.3428*pow(x,3)-19.6664*pow(x,4)+7.44382*pow(x,5);
   if(isW)    return pow(ww,1.0);
   else       return 1.;
}

double roofitR2(TString path, TString variable1, TString variable2, const int nobj, int nbinsch, double eR, TString xtitle, TString ytitle, bool isLgy=false, bool isW=false){
 
  //TString xtitle ="bDiscriminator of JP";
  //TString ytitle ="Events/0.1 bDiscriminator ";
 
  using namespace RooFit ;

  bool combine = false;
  //int nbinsch = 20; //number of bins for each histograms. for example, b-jets multiplicity = 5 , b-dscriminatorCSV = 20, b-discriminatorJP = 20
  const int ndecay = 3; // mm, em, ee
  //const int nobj = ; // 1: b-jet mulitplicity , 2 :jet1, jet2 

  //CSVM efficiency ratio
  //double eR = 0.473795;
  //CSVT efficiency ratio
  //double eR = 0.382948;
  //double eR = 0.750311; //nJet30 >= 4

  //TString path = "./TTBB_08Feb2013_CSVMv2puweight_bweight30CSVM";
  TString fileName[ndecay];
  fileName[0] = path+"/MuMu/MuMu.root";
  fileName[1] = path+"/MuEl/MuEl.root";
  fileName[2] = path+"/ElEl/ElEl.root";
  TString variable[nobj];
  variable[0]=variable1;
  if(nobj==2) variable[1]=variable2;
 
  //variable[0] = "nbJet30_CSVM";
  //variable[0] = "jet30bDiscriminator1b";
  //variable[1] = "jet30bDiscriminator1b";
  //variable[0] = "jet30bDiscriminator1bJP";
  //variable[1] = "jet30bDiscriminator1bJP";



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
  
  double Xmin, Xmax; 
  for(int i=0; i < ndecay; i++){
    TFile * f = new TFile(fileName[i]);
    for(int j=0; j < nobj ; j++){
      hdata[i][j]      = (TH1F*) f->Get(Form("Step_5/hData_Step_5_%s", variable[j].Data()));
      httbb[i][j]      = (TH1F*) f->Get(Form("Step_5/hMCSig_TTbarbb_Step_5_%s", variable[j].Data()));
      httll[i][j]      = (TH1F*) f->Get(Form("Step_5/hMC_TTbarll_Step_5_%s", variable[j].Data()));
      httcc[i][j]      = (TH1F*) f->Get(Form("Step_5/hMC_TTbarcc_Step_5_%s", variable[j].Data()));
      httothers[i][j]  = (TH1F*) f->Get(Form("Step_5/hMC_TTbarNonvis_Step_5_%s", variable[j].Data()));
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
      Xmin=hdata[i][j]->GetXaxis()->GetXmin(); 
      Xmax=hdata[i][j]->GetXaxis()->GetXmax();

      for(int k = 1; k <= Nbins; k++){
        int nb = k + i*nbinsch + j*3*nbinsch;
        if( k < Nbins || combine == false){
          double kk = 1.*k/Nbins-1./(2.*Nbins);
          h_ttbb->SetBinContent(nb, httbb[i][j]->GetBinContent(k));


          h_ttcc->SetBinContent(nb, httcc[i][j]->GetBinContent(k));
          h_ttll->SetBinContent(nb, httll[i][j]->GetBinContent(k)*weight(kk,isW) );
          h_ttccll->SetBinContent(nb, httcc[i][j]->GetBinContent(k) + httll[i][j]->GetBinContent(k)*weight(kk,isW) );
          h_dat->SetBinContent(nb, hdata[i][j]->GetBinContent(k) );
          h_bkg->SetBinContent(nb, hbkg[i][j]->GetBinContent(k)*weight(kk,isW) );
          h_dbg->SetBinContent(nb, hdbg[i][j]->GetBinContent(k)*weight(kk,isW) );


          /*h_ttbb->GetXaxis()->SetBinLabel(nb,httbb[i][j]->GetXaxis()->GetBinLabel(k));
          h_ttll->GetXaxis()->SetBinLabel(nb,httll[i][j]->GetXaxis()->GetBinLabel(k));
          h_ttccll->GetXaxis()->SetBinLabel(nb,httcc[i][j]->GetXaxis()->GetBinLabel(k));
          h_dat->GetXaxis()->SetBinLabel(nb,hdata[i][j]->GetXaxis()->GetBinLabel(k));
          h_bkg->GetXaxis()->SetBinLabel(nb,hbkg[i][j]->GetXaxis()->GetBinLabel(k));
          h_dbg->GetXaxis()->SetBinLabel(nb,hdbg[i][j]->GetXaxis()->GetBinLabel(k));*/

        }else if( k == Nbins && combine == true){
          h_ttbb->AddBinContent(nb-1, httbb[i][j]->GetBinContent(k)  );
          h_ttcc->AddBinContent(nb-1, httcc[i][j]->GetBinContent(k)  );
          h_ttll->AddBinContent(nb-1, httll[i][j]->GetBinContent(k)*weight(kk,isW)  );
          h_ttccll->AddBinContent(nb-1, httcc[i][j]->GetBinContent(k)  + httll[i][j]->GetBinContent(k)*weight(kk,isW)  );
          h_dat->AddBinContent(nb-1, hdata[i][j]->GetBinContent(k) );
          h_bkg->AddBinContent(nb-1, hbkg[i][j]->GetBinContent(k)*weight(kk,isW)  );
          h_dbg->AddBinContent(nb-1, hdbg[i][j]->GetBinContent(k)*weight(kk,isW)  );
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
 
  RooRealVar x("x",xtitle,0, nbins) ;
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

  TCanvas * c = new TCanvas("c","c",1000,550);
  int nnbins = nbins;
  if(nbins>30) nnbins=nbins/2.5; 
  RooPlot* xframe = x.frame(nnbins);
  int xFbin = xframe->GetNbinsX();
   xframe->SetTitle("");
  cout << "Xframe Nbin : " << xFbin << "------------------------------"<<endl;
  for(int i=1;i<=3*nobj;i++)
  {
     if(nobj>1)
     { 
        xframe->GetXaxis()->SetLabelSize(0.06);
        //xframe->GetXaxis()->SetLabelOffset(0.01); 
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/(3*nobj)+1,"0");
        xframe->GetXaxis()->SetBinLabel((int)i*nnbins/(3*nobj),Form("%.f",Xmax));
     }
     else
     {
        xframe->GetXaxis()->SetLabelSize(0.06);
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/3+1,"0");
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/3+2,"1");
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/3+3,"2");
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/3+4,"3");
        xframe->GetXaxis()->SetBinLabel((int)(i-1)*nnbins/3+5,"4");
        //xframe->GetXaxis()->SetBinLabel((int)i*nbins/3,Form("%.f",Xmax));
     }
 
  }



  data.plotOn(xframe,Name("data"));
  model3.paramOn(xframe, Layout(0.65,0.9,0.9) );
  model3.plotOn(xframe,Name("dbg"),Components("histpdf_ttbb,histpdf_ttccll,histpdf_bkg,histpdf_dbg"),LineColor(kAzure-2),FillColor(kAzure-2),DrawOption("F")) ;
  model3.plotOn(xframe,Name("ttccll"),Components("histpdf_ttbb,histpdf_ttccll"),LineColor(kRed),FillColor(kRed),DrawOption("F")) ;
  model3.plotOn(xframe,Name("ttbb"),Components("histpdf_ttbb"),LineColor(kRed+3),FillColor(kRed+3),DrawOption("F")) ;
  //model3.plotOn(xframe);
  data.plotOn(xframe); 

  xframe->Draw();
  xframe->SetMaximum(xframe->GetMaximum()*1.5);
  if(isLgy) xframe->SetMaximum(xframe->GetMaximum()*10);
  xframe->SetMinimum(0.1);
  if(isLgy) c->SetLogy();

  xframe->SetYTitle(ytitle);
  xframe->Draw();

  TLegend *leg1 = new TLegend(0.45,0.73,0.60,0.88);
  leg1->SetFillColor(kWhite);
  leg1->SetLineColor(kWhite);
  leg1->AddEntry("data","DATA", "P");
  leg1->AddEntry("ttbb","t#bar{t} + bb", "F");
  leg1->AddEntry("ttccll","t#bar{t} + cc/LF","F");
  leg1->AddEntry("dbg","Background","F");
  leg1->Draw();

  if(!isLgy)
  {
  if(isW)
  {
    c->Print(Form("%s/l_%s1n.eps", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1n.pdf", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1n.png", path.Data(), variable1.Data()));
  }
  else
  {
    c->Print(Form("%s/l_%s1.eps", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1.pdf", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1.png", path.Data(), variable1.Data()));
  }
  }
  else
  {
  if(isW)
  {
    c->Print(Form("%s/l_%s1nLog.eps", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1nLog.pdf", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1nLog.png", path.Data(), variable1.Data()));
  }
  else
  {
    c->Print(Form("%s/l_%s1Log.eps", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1Log.pdf", path.Data(), variable1.Data()));
    c->Print(Form("%s/l_%s1Log.png", path.Data(), variable1.Data()));
  }
  } 

  //cout << "R = " << R.getValV() << endl;

  return R.getValV();
}

void roofitR2(int ii, int jj, bool isLgY)
{
  const int nobj1=1;  const int nobj2=2;  const int nobj3=2; 

  TString variable11="nbJet30_CSVM";           TString variable12="nbJet30_CSVT";
  TString variable21="jet30bDiscriminator1b";  TString variable22="jet30bDiscriminator2b";
  TString variable31="jet30bDiscriminator1bJP"; TString variable32="jet30bDiscriminator2bJP";

  int nbinsch1=5;   int nbinsch2=20;  int nbinsch3=20;

  double eR_m=0.473795;   //CSVM efficiency ratio
  double eR_t=0.382948;   //CSVT efficiency ratio

  TString xtitle11="b-Jet Multiplicity (CSVM)";
  TString xtitle12="b-Jet Multiplicity (CSVT)";
  TString xtitle2="bDiscriminator of CSV";
  TString xtitle3="bDiscriminator of JP";

  TString ytitle="Events";

  TString path11 = "./csvm/TTBB_08Feb2013_CSVMv2puweight_bweight30CSVM";
  TString path12 = "./csvm3/TTBB_08Feb2013_CSVMv2puweight_bweight30CSVMup";
  TString path13 = "./csvm3/TTBB_08Feb2013_CSVMv2puweight_bweight30CSVMdw";
  TString path14 = "./csvm2/TTBB_08Feb2013_CSVMv2puweight_bweight30CSVMuplight";
  TString path15 = "./csvm2/TTBB_08Feb2013_CSVMv2puweight_bweight30CSVMdwlight";

  TString path21 = "./csvt/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVT";
  TString path22 = "./csvt3/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTup";
  TString path23 = "./csvt3/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTdw";
  TString path24 = "./csvt2/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTuplight";
  TString path25 = "./csvt2/TTBB_08Feb2013_CSVTv2puweight_bweight30CSVTdwlight";

  if(ii ==0)
  {
  /*    double R_N_1   = roofitR2(path11, variable11, variable11, nobj1, nbinsch1, eR_m,  xtitle11, ytitle );
      double R_up_1  = roofitR2(path12, variable11, variable11, nobj1, nbinsch1, eR_m,  xtitle11, ytitle );
      double R_dw_1  = roofitR2(path13, variable11, variable11, nobj1, nbinsch1, eR_m,  xtitle11, ytitle );
      double R_upl_1 = roofitR2(path14, variable11, variable11, nobj1, nbinsch1, eR_m,  xtitle11, ytitle );
      double R_dwl_1 = roofitR2(path15, variable11, variable11, nobj1, nbinsch1, eR_m,  xtitle11, ytitle );
    */  
     
/*      double R_N_3   = roofitR2(path11, variable31, variable32, nobj3, nbinsch3, eR_m,  xtitle3, ytitle );
      double R_up_3  = roofitR2(path12, variable31, variable32, nobj3, nbinsch3, eR_m,  xtitle3, ytitle );
      double R_dw_3  = roofitR2(path13, variable31, variable32, nobj3, nbinsch3, eR_m,  xtitle3, ytitle );
      double R_upl_3 = roofitR2(path14, variable31, variable32, nobj3, nbinsch3, eR_m,  xtitle3, ytitle );
      double R_dwl_3 = roofitR2(path15, variable31, variable32, nobj3, nbinsch3, eR_m,  xtitle3, ytitle );
*/
/*      cout << "CSVM Nbjet R = " << R_N_1 << endl;
      cout << " up : " <<  (R_up_1-R_N_1)/R_N_1 << endl;
      cout << " dw : " <<  (R_dw_1-R_N_1)/R_N_1 << endl;
      cout << " upl : " <<  (R_upl_1-R_N_1)/R_N_1 << endl;
      cout << " dwl : " <<  (R_dwl_1-R_N_1)/R_N_1 << endl;
*/
/*      cout << "CSVM B dicriminator JP R = " << R_N_3 << endl;
      cout << " up : " <<  (R_up_3-R_N_3)/R_N_3 << endl;
      cout << " dw : " <<  (R_dw_3-R_N_3)/R_N_3 << endl;
      cout << " upl : " <<  (R_upl_3-R_N_3)/R_N_3 << endl;
      cout << " dwl : " <<  (R_dwl_3-R_N_3)/R_N_3 << endl;
*/
     if(jj==0)
     {
      double R_N_2   = roofitR2(path11, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY);
      double R_up_2  = roofitR2(path12, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY);
      double R_dw_2  = roofitR2(path13, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY);
      double R_upl_2 = roofitR2(path14, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY);
      double R_dwl_2 = roofitR2(path15, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY);
 
      cout << "CSVM Bdicriminator CSV R = " << R_N_2 << endl;
      cout << " up : " <<  (R_up_2-R_N_2)/R_N_2 << endl;
      cout << " dw : " <<  (R_dw_2-R_N_2)/R_N_2 << endl;
      cout << " upl : " <<  (R_upl_2-R_N_2)/R_N_2 << endl;
      cout << " dwl : " <<  (R_dwl_2-R_N_2)/R_N_2 << endl;

      double upl = fabs((R_upl_2-R_N_2)/R_N_2);
      double dwl = fabs((R_dwl_2-R_N_2)/R_N_2);

      if(upl>dwl) cout << "Ratio : " << R_N_2*100. << " $\\pm$ " << R_N_2*100.*upl << endl;
      else        cout << "Ratio : " << R_N_2*100. << " $\\pm$ " << R_N_2*100.*dwl << endl;


     }
     else if(jj==1)
     {
      double R_N_2w   = roofitR2(path11, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY,true);
      double R_up_2w  = roofitR2(path12, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY,true);
      double R_dw_2w  = roofitR2(path13, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY,true);
      double R_upl_2w = roofitR2(path14, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY,true);
      double R_dwl_2w = roofitR2(path15, variable21, variable22, nobj2, nbinsch2, eR_m,  xtitle2, ytitle, isLgY,true);

      cout << "w CSVM Bdicriminator CSV R = " << R_N_2w << endl;
      cout << "w up : " <<  (R_up_2w-R_N_2w)/R_N_2w << endl;
      cout << "w dw : " <<  (R_dw_2w-R_N_2w)/R_N_2w << endl;
      cout << "w upl : " <<  (R_upl_2w-R_N_2w)/R_N_2w << endl;
      cout << "w dwl : " <<  (R_dwl_2w-R_N_2w)/R_N_2w << endl;

      double upl = fabs((R_upl_2w-R_N_2w)/R_N_2w);
      double dwl = fabs((R_dwl_2w-R_N_2w)/R_N_2w);

      if(upl>dwl) cout << "Ratio : " << R_N_2w*100. << " $\\pm$ " << R_N_2w*100.*upl << endl;
      else        cout << "Ratio : " << R_N_2w*100. << " $\\pm$ " << R_N_2w*100.*dwl << endl;

     }

  }
  else if(ii==1)
  {
     /* double R_N_1   = roofitR2(path21, variable12, variable12, nobj1, nbinsch1, eR_t,  xtitle12, ytitle );
      double R_up_1  = roofitR2(path22, variable12, variable12, nobj1, nbinsch1, eR_t,  xtitle12, ytitle );
      double R_dw_1  = roofitR2(path23, variable12, variable12, nobj1, nbinsch1, eR_t,  xtitle12, ytitle );
      double R_upl_1 = roofitR2(path24, variable12, variable12, nobj1, nbinsch1, eR_t,  xtitle12, ytitle );
      double R_dwl_1 = roofitR2(path25, variable12, variable12, nobj1, nbinsch1, eR_t,  xtitle12, ytitle );
      */

     
     /* double R_N_3   = roofitR2(path21, variable31, variable32, nobj3, nbinsch3, eR_t,  xtitle3, ytitle );
      double R_up_3  = roofitR2(path22, variable31, variable32, nobj3, nbinsch3, eR_t,  xtitle3, ytitle );
      double R_dw_3  = roofitR2(path23, variable31, variable32, nobj3, nbinsch3, eR_t,  xtitle3, ytitle );
      double R_upl_3 = roofitR2(path24, variable31, variable32, nobj3, nbinsch3, eR_t,  xtitle3, ytitle );
      double R_dwl_3 = roofitR2(path25, variable31, variable32, nobj3, nbinsch3, eR_t,  xtitle3, ytitle );

      cout << "CSVT Nbjet R = " << R_N_1 << endl;
      cout << " up : " <<  (R_up_1-R_N_1)/R_N_1 << endl;
      cout << " dw : " <<  (R_dw_1-R_N_1)/R_N_1 << endl;
      cout << " upl : " <<  (R_upl_1-R_N_1)/R_N_1 << endl;
      cout << " dwl : " <<  (R_dwl_1-R_N_1)/R_N_1 << endl;
*/
  /*    cout << "CSVT B dicriminator JP R = " << R_N_3 << endl;
      cout << " up : " <<  (R_up_3-R_N_3)/R_N_3 << endl;
      cout << " dw : " <<  (R_dw_3-R_N_3)/R_N_3 << endl;
      cout << " upl : " <<  (R_upl_3-R_N_3)/R_N_3 << endl;
      cout << " dwl : " <<  (R_dwl_3-R_N_3)/R_N_3 << endl;
*/

     if(jj==0)
     {
      double R_up_2  = roofitR2(path22, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY);
      double R_dw_2  = roofitR2(path23, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY);
      double R_upl_2 = roofitR2(path24, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY);
      double R_dwl_2 = roofitR2(path25, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY);
      double R_N_2   = roofitR2(path21, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY);
 
      cout << "CSVT Bdicriminator CSV R = " << R_N_2 << endl;
      cout << " up : " <<  (R_up_2-R_N_2)/R_N_2 << endl;
      cout << " dw : " <<  (R_dw_2-R_N_2)/R_N_2 << endl;
      cout << " upl : " <<  (R_upl_2-R_N_2)/R_N_2 << endl;
      cout << " dwl : " <<  (R_dwl_2-R_N_2)/R_N_2 << endl;
  
      double upl = fabs((R_upl_2-R_N_2)/R_N_2);
      double dwl = fabs((R_dwl_2-R_N_2)/R_N_2);

      if(upl>dwl) cout << "Ratio : " << R_N_2*100. << " $\\pm$ " << R_N_2*100.*upl << endl;
      else        cout << "Ratio : " << R_N_2*100. << " $\\pm$ " << R_N_2*100.*dwl << endl;

     }
     else if(jj==1)
     { 
      double R_up_2w  = roofitR2(path22, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY, true);
      double R_dw_2w  = roofitR2(path23, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY, true);
      double R_upl_2w = roofitR2(path24, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY, true);
      double R_dwl_2w = roofitR2(path25, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY, true);
      double R_N_2w   = roofitR2(path21, variable21, variable22, nobj2, nbinsch2, eR_t,  xtitle2, ytitle, isLgY, true);

      cout << "w CSVT Bdicriminator CSV R = " << R_N_2w << endl;
      cout << "w up : " <<  (R_up_2w-R_N_2w)/R_N_2w << endl;
      cout << "w dw : " <<  (R_dw_2w-R_N_2w)/R_N_2w << endl;
      cout << "w upl : " <<  (R_upl_2w-R_N_2w)/R_N_2w << endl;
      cout << "w dwl : " <<  (R_dwl_2w-R_N_2w)/R_N_2w << endl;

      double upl = fabs((R_upl_2w-R_N_2w)/R_N_2w);
      double dwl = fabs((R_dwl_2w-R_N_2w)/R_N_2w);

      if(upl>dwl) cout << "Ratio : " << R_N_2w*100. << " $\\pm$ " << R_N_2w*100.*upl << endl;
      else        cout << "Ratio : " << R_N_2w*100. << " $\\pm$ " << R_N_2w*100.*dwl << endl;


     }

  }


}
