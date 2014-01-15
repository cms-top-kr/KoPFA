#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooCBShape.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooFitResult.h"
#include "RooThresholdCategory.h"
#include "RooBinningCategory.h"
#include "RooWorkspace.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TAxis.h"
#include "TGraphAsymmErrors.h"
#include "TPaveLabel.h"
#include "TPaveText.h"

using namespace RooFit;
using namespace std;

void readData(RooWorkspace&, TString);
void buildPdf(RooWorkspace&);

void fitYield(RooWorkspace&, TString, RooAbsData* d=0, bool);
void plotMass(TString, RooWorkspace&, RooAbsData* d=0, RooAbsPdf* p=0);

void xsectTot(RooWorkspace&);
void xsectDif(RooWorkspace&, bool, double*, int, double*, int);

void getInitialParValues(RooWorkspace&);
void setDefaultFitParValues(RooWorkspace&,RooAbsData* d=0);
double getWeightAv(RooWorkspace&, RooAbsData*);

void oniafitterMain  (const TString, const TString, const TString, double*, int);

vector<double> initParVal_;
vector<string> initParName_;

bool linearbg_ = true;
#define mmin_ 2.6 
#define mmax_ 3.5
TString figs_("figs/"); /* store location for produced file output */
const TString res_("results"); /* root folder in file for storing results */
const TString plt_("plots"); /* root folder in file for storing plots */
const TString dirname_(""); /* tree location in input file */
const TString treeName("JPsiTree");//("JPsiTree");
const TString ext_(".gif"); /* save plots format */
//double lumi_ = 589.74; /*sample lumi in nb-1*/
//double lumi_ = 2317.742658; /*sample lumi in nb-1*/
double lumi_ = 2861.185236; /*sample lumi in nb-1*/

const bool isMC        = false;//use thruth info
const bool restorepars = false;
const bool printPars   = false;
//const bool absoluteRap = true;

//double JpsiRapBinEdges[] = {-2.4,-1.6,-1.2,0.0,1.2,1.6,2.4};
double JpsiRapBinEdges[] = {-2.4,-1.4,0.0,1.4,2.4};
//double ptBinArr[] = {2.0, 3.5, 4.5, 5.5, 6.5, 8.0, 10.0, 30.0};
//double ptBinArr0[] = {4.0, 6.0, 8.0, 9.0, 10.0,30.0};
double ptBinArr[] = {0.0, 1.0, 1.5, 2.0, 3.0, 4.0, 6.0, 8.0, 9.0, 10.0,30.0};
//double ptBinArr[] = {0.0, 1.0, 1.5, 2.0, 3.0, 4.0, 6.0, 8.0, 10.0, 30.0};

void oniafitter(const TString finput  = "JpsiYieldWeighted_nominal.root", 
		const TString foutput = "xsection.root", 
		const TString dfigs = "figs/" 
		) {
  
  int nbin = sizeof(ptBinArr)  / sizeof(double);
  const int nptb = nbin;

  double JpsiPtBinEdges[nptb];
  for(int i=0; i<nptb; i++) {
      JpsiPtBinEdges[i] = ptBinArr[i];
  }

  ///full analysis fitting 
  oniafitterMain(finput, foutput, dfigs,JpsiPtBinEdges,nptb);

}


void oniafitterMain(
		     const TString finput,
		     const TString foutput,
		     const TString dfigs,
		     double *JpsiPtBinEdges, int nptb
		     ) { 

  figs_ = dfigs;
  cout << "oniafitter processing"
       << "\n\tinput:  \t" << finput
       << "\n\toutput: \t" << foutput
       << "\n\tresults:\t" << figs_
       << "\n\tnptbins:\t" << nptb
       << endl;
  
  /// roofit workspace to manage fitting info
  RooWorkspace* ws = new RooWorkspace("ws","Jpsi mass");
 
  /// create fitting model
  buildPdf(*ws);

  /// read the data
  readData(*ws,finput);
  //plotMass("data",*ws,ws->data("data"));
 
  /// cache the initial parameter
  getInitialParValues(*ws);

  /// open output root file
  TFile file(foutput,"recreate");
  //TFile file(foutput,"update");
  gDirectory->mkdir(res_);
  gDirectory->mkdir(plt_);
  gDirectory->Cd(res_);

  /* PLEASE UNCOMMENT BELOW ONLY THOSE FUNCTION CALLS
     YOU WANT TO BE EXECUTED EACH TIME THE MACRO IS RUN */
  /// fit raw yield

//  fitYield(*ws,"total",ws->data("data")); //1
//  plotMass("mass_raw",*ws, ws->data("data"), ws->pdf("pdf")); //1

//  fitYield(*ws,"total",ws->data("data")); //3
//  plotMass("mass_wei",*ws, ws->data("data"), ws->pdf("pdf")); //4

  /// cross section vs pT
  //int nptb  = sizeof(JpsiPtBinEdges)  / sizeof(double);
  int nrapb = sizeof(JpsiRapBinEdges) / sizeof(double);  

  //total cross section
//  xsectTot(*ws); //1

  //differential cross section and fits
  xsectDif(*ws,1, JpsiPtBinEdges, nptb, JpsiRapBinEdges, nrapb); //5
  //xsectDif(*ws,0, JpsiPtBinEdges, nptb, JpsiRapBinEdges, nrapb);

  file.Close();
}


/* total cross section
   retrieve and normalize global fit results
*/
void xsectTot(RooWorkspace& w) {

  cout << "computing total cross section...\n" << std::flush;
  gDirectory->Cd("../"+res_);

  ///raw yield
  RooFitResult* fitres_r  = (RooFitResult *) gROOT->FindObject("fit_result_raw_total");

  //  cout << " average weight:" << ((RooDataSet*)w.data("data"))->mean(*w.var("weight")) << "\n";


  double nsigVal_r, nsigErr_r;
  double nsigVal_w, nsigErr_w;
  double xsec, xsecE;

  TString yieldn = TString::Format("nsignal");
  nsigVal_r      = ((RooRealVar*)fitres_r->floatParsFinal().find(yieldn))->getVal();
  nsigErr_r      = ((RooRealVar*)fitres_r->floatParsFinal().find(yieldn))->getError();

  /// check & print
  //this number varies whether the dataset is weighted or not(!)
  double mean_weight = ((RooDataSet*)w.data("data"))->mean(*w.var("weight"));
  cout << "mean_weight " <<  mean_weight << endl;
  //return;

  //this fails for weighted dataset, as weight stops being a variable, by becoming a weight 
  double mean2 = (w.data("data"))->createHistogram("weight",100) ->GetMean();
  cout << " mean2:" << mean2 << "\n";
  //cout << "xxx: "<< getWeightAv(w, w.data("data")) << " mean2:" << mean2 << "\n";

  cout << "raw  yield " << nsigVal_r << "+-" << nsigErr_r <<endl ;
  cout << "cross check raw / weight(" <<  mean_weight << ") = " 
       << nsigVal_r/mean_weight << "+-" << nsigErr_r/mean_weight << endl;
  cout << "xsection_r/w:" << nsigVal_r/mean_weight/lumi_ << "+-" << nsigErr_r/mean_weight/lumi_ << " (lumi: "<< lumi_ <<")"<<endl;
  //cout << "cross section:" << xsection << "+-" << xsection_err << " nb\n";

  xsec  = nsigVal_r/mean_weight/ lumi_;
  xsecE = nsigErr_r/mean_weight/ lumi_;
  cout << "cross section:" <<xsec<<endl;  
  /// save value as root object
/*  TGraphAsymmErrors xst;
  xst.SetPoint(0,0, xsec);
  xst.SetPointError(0,0.1,0.1, xsecE, xsecE);
  gDirectory->Cd("../"+plt_);
  xst.SetName(TString::Format("xsection_Jpsi_total"));
  xst.Write();*/
}

/* differential cross section, sigma vs pT
-split the dataset in pT regions
-fit the sub-samples, extract the yield, and normalize   
*/
void xsectDif(RooWorkspace& w, bool dofit, double *JpsiPtBinEdges, int nptb, double *JpsiRapBinEdges, int nrapb) {

  RooAbsPdf*  pdf   = w.pdf("pdf");
  RooDataSet* data  = (RooDataSet*)w.data("data");
  RooRealVar* Jpsi_Pt = w.var("Jpsi_Pt");
  RooRealVar* Jpsi_Rap = w.var("Jpsi_Rap");
  //cout<<"data_w->weight() ="<<data->weight()<<endl;

  //const int npte = sizeof(JpsiPtBinEdges)/sizeof(double);
  const int nptbins = nptb - 1;
  cout<<"nptbins :"<<nptbins<<endl;
  //const int nrapbins = sizeof(JpsiRapBinEdges)/sizeof(double)-1;
  const int nrapbins = nrapb - 1;
  cout<<"nrapbins :"<<nrapbins<<endl;

  bool absoluteRap = (nrapbins==1)?false:true;
  const int nrapregion = absoluteRap?nrapbins/2:nrapbins;

  cout << "nrapregion:" << nrapregion << " abs-y?" << absoluteRap << " nrapbins:" << nrapbins << " nrapbin:" << nrapb << "\n";


  double JpsiPtBinCenter[nrapregion][nptbins], JpsiPtBinEdgeLo[nrapregion][nptbins], JpsiPtBinEdgeHi[nrapregion][nptbins];
  RooThresholdCategory ptRegion("ptRegion","region of pt",*Jpsi_Pt);
  for(int i=0; i<nptbins; i++) {
    TString reg = TString::Format("PtBin%d",i+1);    
    ptRegion.addThreshold(JpsiPtBinEdges[i+1],reg) ;    
  }
  data->addColumn(ptRegion);

  RooThresholdCategory rapRegion("rapRegion","region of rap",*Jpsi_Rap) ;

  for(int i=0; i<nrapbins; i++) {
    int jj = (i<nrapregion)?nrapregion-i-1:i-nrapregion;
    jj = absoluteRap?jj:i;
    TString reg = TString::Format("RapBin%d",jj+1);    
    printf("edge:%d  name:%s\n",i,reg.Data());
    rapRegion.addThreshold(JpsiRapBinEdges[i+1],reg) ;    
  }
  data->addColumn(rapRegion);

  ///TBD: add kinematic plots of categories


  double countBinSumEntries[nrapregion][nptbins];
  double countBinNumEntries[nrapregion][nptbins];
  double averageWeight[nrapregion][nptbins];

  /// process each pt subsample
  RooDataSet* dataPt;
  for(int j=0; j<nrapregion; j++) {
    for(int i=0; i<nptbins; i++) {
      cout << "processing subsample pt" << i << " rap:" << j << "\n" << std::flush;
      dataPt = (RooDataSet*)  data->reduce(TString::Format("rapRegion==rapRegion::RapBin%d",j+1))->reduce(TString::Format("ptRegion==ptRegion::PtBin%d",i+1));
      //dataPt = (RooDataSet*) data->reduce(TString::Format("ptRegion==ptRegion::PtBin%d && rapRegion::RapBin%d",i+1,j+1));
      //averageWeight[j][i]= dataPt->mean(*w.var("weight"));
      averageWeight[j][i]=(dataPt->createHistogram("weight",100))->GetMean();
      //cout<<"mean_1 =" <<dataPt->mean(*w.var("weight"))<<" "<<"mean_2 ="<<averageWeight[j][i]<<endl;
      //TH1F* hh = new TH1F("h","h",1000,0,100);
      //hh->Fill(averageWeight[j][i]);
      //TCanvas bb;hh->Draw(); bb.SaveAs(TString::Format("weight_y%d_pt%d.gif",j,i));
      //delete hh;

      ///debug
      ////TH1F* hh = (TH1F*) dataPt->createHistogram("Jpsi_Mass",10000);
      ////TCanvas bb;hh->Draw(); bb.SaveAs(TString::Format("PPTT_y%d_pt%d.gif",j,i));
      ////delete hh;
      ///enddebug

      //dataPt->setWeightVar(*w.var("weight"));
      //sideband subtracted weighted yield
      // signal: 9.46-6*0.09+3*0.09; background: 8.8.54, 11-11.54; fraction: S/B = (6+3)*0.09 / 2*0.5 = 0.81 
////      countBinSumEntries[j][i] = dataPt->reduce(Cut("Jpsi_Mass>2.6 && Jpsi_Mass<3.4"))->sumEntries(); 
      ///////////	- 0.81 * ( dataPt->reduce(Cut("Jpsi_Mass>2.8 && Jpsi_Mass<3.4"))->sumEntries() +
      //////////	   dataPt->reduce(Cut("Jpsi_Mass>2.6 && Jpsi_Mass<3.6"))->sumEntries() ) ;
      
      //countBinSumEntries[j][i] = dataPt->sumEntries();
////      countBinNumEntries[j][i] = dataPt->numEntries();

      /////////////double mean_weight = ((RooDataSet*)w.data("data"))->mean(*w.var("weight"));
      ////////////double getWeightAv(w, w.data("data"))
      JpsiPtBinCenter[j][i] =  dataPt->mean(*w.var("Jpsi_Pt"));       
      JpsiPtBinEdgeLo[j][i] =  JpsiPtBinCenter[j][i] - JpsiPtBinEdges[i];
      JpsiPtBinEdgeHi[j][i] = -JpsiPtBinCenter[j][i] + JpsiPtBinEdges[i+1];
      //cout<<"JpsiPtBinCenter["<<j<<"]["<<i<<"] = "<<JpsiPtBinCenter[j][i]<<endl; 
      //Cout << "NTOTAL sample " << i << " = " << dataPt->sumEntries() << "\n";
      //if(i!=0) continue; /* re-fit sub-sample */
      //dofit=0;


      if(dofit) {
	fitYield(w, TString::Format("rap%d_pt%d",j,i), dataPt);
	plotMass(TString::Format("massfit_rap%d_pt%d",j,i),w, dataPt,pdf);  
      }
    }
  }
  //cout<<"step1"<<endl;
 
  /// store yield
  double JpsiYieldPt  [nrapregion][nptbins];
  double JpsiYieldPt_e[nrapregion][nptbins];
  double JpsiYieldPt_eh[nrapregion][nptbins];
  double JpsiYieldPt_el[nrapregion][nptbins];
  gDirectory->Cd("../"+res_);
  RooFitResult* fitresPt;
  for(int j=0; j<nrapregion; j++) {
    for(int i=0; i<nptbins; i++) {
      /////////////fitresPt = (RooFitResult *) gROOT->FindObject(TString::Format("fit_result_corrected_rap%d_pt%d",j,i));
      fitresPt = (RooFitResult *) gROOT->FindObject(TString::Format("fit_result_raw_rap%d_pt%d",j,i));
      TString yieldn = TString::Format("nsignal");
      JpsiYieldPt   [j][i] = ((RooRealVar*)fitresPt->floatParsFinal().find(yieldn))->getVal();
      cout<<"rap "<<j<<"& pt"<<i<<" nJpsi: "<<JpsiYieldPt[j][i]<<endl;
      JpsiYieldPt_e [j][i] = ((RooRealVar*)fitresPt->floatParsFinal().find(yieldn))->getError();
      JpsiYieldPt_eh[j][i] = ((RooRealVar*)fitresPt->floatParsFinal().find(yieldn))->getErrorHi();
      JpsiYieldPt_el[j][i] = ((RooRealVar*)fitresPt->floatParsFinal().find(yieldn))->getErrorLo();
    }
  }
  //cout<<"step2"<<endl;  

 //for(int j=0; j<nrapregion; j++) {
 //  for(int i=0; i<nptbins; i++) {
 //    double wei = averageWeight[j][i];
 //    double rr = countBinNumEntries[j][i]?countBinSumEntries[j][i]/countBinNumEntries[j][i]:0;
 //    rr = wei?rr/wei:0;
 //    double r = JpsiYieldPt[0][j][i]/countBinSumEntries[j][i];
 //    printf(" bin eta%d pt%d count:%8.0d fit:%8.0d r:%5.3f\n",
 //	    j,i,countBinSumEntries[j][i], JpsiYieldPt[0][j][i],r);
 //  }
 //}


  bool normalize=1;
  if(normalize){
    /// normalize yield
    for(int j=0; j<nrapregion; j++) {
      double rbinw =  JpsiRapBinEdges[j+1]-JpsiRapBinEdges[j];
      for(int i=0; i<nptbins; i++) {
	double binw =  JpsiPtBinEdges[i+1]-JpsiPtBinEdges[i];
          JpsiYieldPt   [j][i] *= 1./averageWeight[j][i]/lumi_/binw;///rbinw;
          JpsiYieldPt_e [j][i] *= 1./averageWeight[j][i]/lumi_/binw;///rbinw;
          JpsiYieldPt_eh[j][i] *= 1./averageWeight[j][i]/lumi_/binw;///rbinw;
          JpsiYieldPt_el[j][i] *= 1./averageWeight[j][i]/lumi_/binw;///rbinw;

          cout<<"lumi :"<<lumi_<<" ptbinw :"<<binw<<" rbinw :"<<rbinw<<endl;
          printf("cross-section bin[%d,%2d]=%4.1f ",j,i, JpsiPtBinCenter[j][i]);
          printf("  Jpsi %5.3f+/-%5.3f s/e=%2.0f" ,JpsiYieldPt[j][i], JpsiYieldPt_e[j][i],
               JpsiYieldPt[j][i] / JpsiYieldPt_e[j][i] );
          //cout<<endl<<"1/aveWgt : "<<1./averageWeight[j][i]<<endl;
          cout<<endl<<"aveWgt : "<<averageWeight[j][i]<<endl;
      }
    }
  }
  //cout<<"step3"<<endl;

  /// check
////  for(int j=0; j<nrapregion; j++) {
////    for(int i=0; i<nptbins; i++) {
////      printf("cross-section bin[%d,%2d]=%4.1f ",j,i, JpsiPtBinCenter[j][i]);
      ////for(int k=0; k<npeak; k++) {  
////	printf("  Jpsi %5.3f+/-%5.3f s/e=%2.0f" ,JpsiYieldPt[j][i], JpsiYieldPt_e[j][i], 
////	       JpsiYieldPt[j][i] / JpsiYieldPt_e[j][i] );
      ////}
////      cout << "\n";
////    }
////  }
  //cout<<"step4"<<endl;  

  /// plot cross section
  TGraphAsymmErrors *fitgr[nrapregion];
    
    for(int Y=0; Y<nrapregion; Y++) {
      
      double yield[nptbins], err[nptbins], err_h[nptbins], err_l[nptbins];
      double JpsiPtBinCenterY[nptbins], JpsiPtBinEdgeLoY[nptbins], JpsiPtBinEdgeHiY[nptbins]; 
      for(int i=0; i<nptbins; i++) {
	yield[i] = JpsiYieldPt   [Y][i];
	err  [i] = JpsiYieldPt_e [Y][i];
	err_h[i] = JpsiYieldPt_eh[Y][i];
	err_l[i] = JpsiYieldPt_el[Y][i];
	JpsiPtBinCenterY[i]=JpsiPtBinCenter[Y][i];
	JpsiPtBinEdgeLoY[i]=JpsiPtBinEdgeLo[Y][i];
	JpsiPtBinEdgeHiY[i]=JpsiPtBinEdgeHi[Y][i]; 
       }
      //cout<<"step5"<<endl;
      
      fitgr[Y] = new TGraphAsymmErrors(nptbins,   JpsiPtBinCenterY, yield,
				       JpsiPtBinEdgeLoY, JpsiPtBinEdgeHiY, 
   				       err_l, err_h);
      }
      gDirectory->Cd("../"+plt_);
      gROOT->SetStyle("Plain");
      //gStyle->SetTextSize(0.01908148);
      //gStyle->SetTitleFontSize(0.07);
      //gStyle->SetOptTitle(1);
      //gStyle->SetOptStat("e");
      //gStyle->SetTitleXOffset(1.65);
      //gStyle->SetTitleYOffset(1.65);
      //gStyle->SetPadTopMargin(0.15);
      //gStyle->SetPadBottomMargin(0.15);
      //gStyle->SetPadLeftMargin(0.15);

      TCanvas *c = new TCanvas("c","c",800,800);
      c->cd();
      double x[2] = {3, 30};
      double y[2] = {0.0008,1000};
      TGraph *frame = new TGraph (2, x, y);
      TString ytitle = 
	TString::Format("#frac{d#sigma}{dp_{T}} . BR(#Jpsi#rightarrow#mu#mu) [nb/GeV]");
      //frame->SetTitle( "J/#Psi" );
      //frame->GetXaxis()->SetTitle("p_{T} (#mu#mu) [GeV]");
      //frame->GetYaxis()->SetTitle(ytitle);
      //frame->Draw("AP");
      //fitgr->SetTitle("J/#Psi");
      //fitgr->GetXaxis()->SetTitle("p_{T} (#mu#mu) [GeV]");
      //fitgr->GetYaxis()->SetTitle(ytitle);
      frame->Draw("AP");
      fitgr[0]->SetMarkerStyle(20);
      fitgr[0]->SetMarkerSize(1);
      fitgr[0]->SetMarkerColor(kRed);
      fitgr[1]->SetMarkerStyle(21);
      fitgr[1]->SetMarkerSize(1);
      fitgr[1]->SetMarkerColor(kBlue);
      fitgr[0]->Draw("P");
      fitgr[1]->Draw("P");
      gPad->SetLogy();
      fitgr[1]->SetTitle("J/#Psi");
      fitgr[1]->GetXaxis()->SetTitleOffset(1.65);
      fitgr[1]->GetXaxis()->SetTitleSize(0.033);
      fitgr[1]->GetYaxis()->SetTitleOffset(1.65);
      fitgr[1]->GetYaxis()->SetTitleSize(0.033);
      fitgr[1]->GetXaxis()->SetTitle("p_{T} (#mu#mu) [GeV]");
      fitgr[1]->GetYaxis()->SetTitle(ytitle);

      TString htmp = TString::Format("xsection_Jpsi_rap%d_pt",Y);
      TLegend *legend = new TLegend(.75,.80,.95,.95);
      legend->AddEntry(fitgr[0],"|y|<1.4","p");
      legend->AddEntry(fitgr[1],"1.4<|y|<2.4","p");
      legend->Draw("same");
      //fitgr->SetName(htmp);
      //fitgr->Write();
      //c->SaveAs(TString::Format("%sxsecdiff_Jpsi_rap%d%s",figs_.Data(),Y,ext_.Data()));
      c->SaveAs(TString::Format("%sxsecdiff_Jpsi%s",figs_.Data(),ext_.Data()));
    //}
    //cout<<"step6_End"<<endl;
}


/* plot the mass distribution and fitted model
 */
void plotMass(TString hname, RooWorkspace& w, RooAbsData *data, RooAbsPdf* pdf) {

  gROOT->SetStyle("Plain");

  bool dataonly = (data && !pdf);
  if(!data)
    data = (RooDataSet*)w.data("data");
  if(!pdf)
    pdf = (RooAbsPdf*)w.pdf("pdf");

  RooAbsPdf* bkgPdf_exp = (RooAbsPdf*)w.pdf("bkgPdf_exp"); 
  /*
  RooRealVar* psigma2 = ( RooRealVar*)pdf->getParameters(data)->find("sigma2");
  RooRealVar* psigmaFraction = ( RooRealVar*)pdf->getParameters(data)->find("sigmaFraction");
  //psigmaFraction->setVal(1.0); 
  //  psigma2->setConstant(kTRUE);  
  cout << "xxx " << psigmaFraction->getVal() << " " << psigma2->getVal() << "\n";
  RooArgSet* pars = (RooArgSet*)w.pdf("pdf")->getParameters(*w.data("data"));//->selectByAttrib("Constant",kFALSE);
  pars->Print("v");
  */

  //RooAbsPdf *pdf_ = (RooAbsPdf*)w.pdf("pdf");
  //pdf_->SetName("pdf");

  RooPlot* frame;
  if(printPars) 
    frame = w.var("Jpsi_Mass")->frame(Bins(40));
  else
    frame = w.var("Jpsi_Mass")->frame(Bins(40));
  //data->plotOn(frame, Name("aaa"));
  //pdf->plotOn(frame);
  //RooHist* hresid = frame->pullHist("aaa","pdf");
  //hresid->SetLineColor(2);

  //typedef RooAbsData::EType dataet;
  //dataet etype = data->isWeighted() ? RooAbsData::SumW2 : RooAbsData::Auto;
  if(!data->isWeighted()) 
    //data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E")); // DataError(etype));
    data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E")); // DataError(etype));
  else
    data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E"), DataError(RooAbsData::SumW2));

/*  if(!dataonly) {// not this case
    
    pdf->plotOn(frame,Name("thePdf"),Components("bkg"),
		 LineStyle(1),LineWidth(2),LineColor(16)) ; 
    if(printPars) {
      pdf->paramOn(frame,Layout(0.6));
    }

    ////pdf->plotOn(frame,Components(TString::Format("gauss%sS1",PEAK_.Data())),
	////	FillStyle(1001), VLines(),FillColor(kRed-8), DrawOption("F")) ; 
    ////pdf->plotOn(frame,Components(TString::Format("gauss%sS2",PEAK_.Data())),
	////	FillStyle(1001),FillColor(kRed-5), DrawOption("F")); 
    ////pdf->plotOn(frame,Components(TString::Format("gauss%sS1",PEAK_.Data())),
	////	LineColor(kWhite),LineWidth(1));
    pdf->plotOn(frame,Components(TString::Format("gauss1")),
                FillStyle(1001), VLines(),FillColor(kYellow-10), DrawOption("F")) ;
    pdf->plotOn(frame,Components(TString::Format("gauss2")),
                FillStyle(1001),FillColor(kYellow-10), DrawOption("F"));
    pdf->plotOn(frame,Components(TString::Format("gauss1")),
                LineColor(kWhite),LineWidth(1));
    
  } //not this case
*/
  pdf->plotOn(frame);
  //bkgPdf_exp->plotOn(frame);

  if(!data->isWeighted())
    data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E")); // DataError(etype));
  else
    data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E"), DataError(RooAbsData::SumW2));

  //data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E"), DataError(etype));
  //  data->plotOn(frame,Name("theData"), MarkerStyle(7), DrawOption("E"), 
  //	       DataError(RooAbsData::SumW2)); //needed in case of weights


  //  frame->SetNdivisions(1020,"X");
  //  frame->SetNdivisions(1020,"Y");

  frame->SetTitle( "" );
  frame->GetXaxis()->SetTitle("#mu^{+}#mu^{-} mass (GeV/c^{2})");
  frame->GetYaxis()->SetTitleOffset(1.65);
  frame->GetYaxis()->SetTitleSize(0.033);

  ///fit residuals
  RooPlot* rframe = w.var("Jpsi_Mass")->frame();
  //RooHist* hresid = frame->pullHist();
  //hresid->SetLineColor(2);
  //rframe->addObject(hresid);
  int nresid=4;
  rframe->SetTitle("");
  rframe->GetXaxis()->SetTitle("");
  rframe->GetYaxis()->SetLabelSize(0.12);
  rframe->GetYaxis()->SetNdivisions(2*nresid+1);
  rframe->SetAxisRange(-1*nresid,nresid,"Y");
  rframe->SetMarkerStyle(7);

  TCanvas c; c.cd();

  TPaveLabel *t2 = new TPaveLabel(0.01,0.1,0.07,0.9, "Residual pull", "brNDC"); 
  t2->SetFillColor(0);
  t2->SetTextAngle(90);
  t2->SetTextSize(0.2);
  t2->SetBorderSize(0);

  TPad *p1 = new TPad("p1","p1",0.1,0.25,0.9,0.901);// ,0,0,0); 
  //p1->SetBottomMargin(0.);
  p1->SetBorderMode(0); 
  p1->Draw(); 
   
  TPad *p2 = new TPad("p2","p2",0.1,0.1,0.9,0.24); 
  p2->SetTopMargin(0.);    
  p2->SetBorderMode(0); 
  p2->SetTicks(1,0); 
  p2->Draw(); 

  TPaveText *cms = new TPaveText(0.63,0.78,0.85,0.85,"brNDC");
  cms->SetFillColor(0);
  cms->SetBorderSize(0);
  cms->SetTextAlign(12);
  cms->SetTextSize(0.045);
  cms->AddText("CMS simulation");
  //cms->Draw();

  //p1->cd();
  frame->Draw();
  //p2->cd();
  //rframe->Draw();
  //t2->Draw();

  //gPad->SetLogy();
  //frame->Draw();
  c.SaveAs(figs_+hname+ext_);
  gDirectory->Cd("../"+plt_);
  frame->SetName(hname);
  frame->Write(hname);
}

/* fit the mass distribution
- save fit results to file
 */
void fitYield(RooWorkspace& w, TString name, RooAbsData* data) {
  
  cout << "fitting the Jpsi mass...\n" << std::flush;

  if(!data)
    data = (RooDataSet*)w.data("data");

  /// reset the fit parameters, retune the yields
  setDefaultFitParValues(w,data);

  cout<<"Start fitting..."<<endl;
  RooFitResult* fitres = w.pdf("pdf")->fitTo(*data, Save(), Extended(kTRUE), Minos(kTRUE), SumW2Error(kTRUE));//,Range(mmin_,mmax_));

  TString fres_n("fit_result_");
  fres_n += "raw";
  fres_n += ("_"+name);
  fitres->SetName(fres_n);
  gDirectory->Cd("../"+res_);
  fitres->Write();
  fitres->Print();
  cout << "/tsaved results in " << fres_n << "\n" << std::flush;
}

/* read the data from ttree
 */
void readData(RooWorkspace& w, TString fname) {
  TFile f(fname,"read");
  gDirectory->Cd(fname+":/"+dirname_);
  TTree* theTree     = (TTree*)gROOT->FindObject(treeName);
  RooRealVar* Jpsi_Mass  = w.var("Jpsi_Mass");
  RooRealVar* Jpsi_Pt  = new RooRealVar("Jpsi_Pt","p_{T}(#Jpsi)",0,50,"GeV");
  RooRealVar* wgt = new RooRealVar("weight",  "weight"  ,1,0,100);
  RooRealVar* Jpsi_Rap = new RooRealVar("Jpsi_Rap",  "JpsiRapidity"  ,-2.5,2.5);
  RooRealVar* dummyb = new RooRealVar("maxMuEta",  "maxMuEta"  ,-2.7,2.7);
  RooRealVar* dummyc = new RooRealVar("SampleFlag",  "SampleFlag"  ,0,4);
  RooDataSet* data0, *data1, *data, *data_w;
  //if(isMC) {
  //data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsPt,*weight,*dummy,*dummyb,*dummyc)); 
  //data = ( RooDataSet*) data0->reduce(Cut("SampleFlag>0"));//,EventRange(0,500000));
  //data = ( RooDataSet*) data0;//->reduce(EventRange(0,1000),Cut("Jpsi_Mass<9.8"));
  //}
  //else {
  data0 = new RooDataSet("data","raw data",theTree,RooArgSet(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Rap, *wgt)); 
  data1 = new RooDataSet("data_w","weighted data",theTree,RooArgSet(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Rap, *wgt),0,"weight"); 
  //  }
  data = data0;
  data_w = data1;
  w.import(*data);
  //w.import(*data_w);
  f.Close();
}


/* define the fit model
+ signal
for each Jpsi 1S/2S/3S: double gaussian, or gaussian + 'crystal ball' 
at each peak, the two gaussians have common center
default fitting parameters:
- mass of Jpsi 1S floats
- mass shift between three peaks are fixed to pdg (or common scale factor allowed to float)
- the three peaks have a common shape 
- relative rates of three peaks float
+ background
- second order polynominal
*/
void buildPdf(RooWorkspace& w) {

  RooRealVar* mass  = new RooRealVar("Jpsi_Mass","#mu#mu mass",mmin_,mmax_,"GeV/c^{2}"); 

  const double M =  3.096;  //Jpsipgd mass value

  RooRealVar *mean    = new RooRealVar("mass_mean","#Jpsiilon mean",M,3.05,3.15,"GeV");

  ////RooRealVar *mscale  = new RooRealVar("mscale","mass scale factor",1.,0.7,1.3);
  ////mscale->setConstant(kTRUE); /* the def. parameter value is fixed in the fit */

  RooFormulaVar *mean1 = new RooFormulaVar("mean1","@0",
  					    RooArgList(*mean));

  RooRealVar *sigma1 = new RooRealVar("sigma1","Sigma 1",0.02,0.008,0.20);
  RooRealVar *sigma2 = new RooRealVar("sigma2","Sigma 2",0.03,0.008,0.20);

  /// to describe final state radiation tail on the left of the peaks
  RooRealVar *alpha  = new RooRealVar("alpha","tail shift",0.5,0.1,5);
  //RooRealVar *alpha  = new RooRealVar("alpha","tail shift",1.7,0.2,4);
  RooRealVar *npow   = new RooRealVar("npow","power order",10.,1.,60.);
  //npow ->setConstant(kTRUE);
  //alpha->setConstant(kTRUE);
 
  /// relative fraction of the two peak components 
  RooRealVar *sigmaFraction = new RooRealVar("sigmaFraction","Sigma Fraction",0.5,0.,1.);

  /// Jpsi 
  RooGaussian *gauss1 = new RooGaussian("gauss1","Signal Gaussian1",*mass,*mean1,*sigma1);
  RooGaussian *gauss2 = new RooGaussian("gauss2","Signal Gaussian2",*mass,*mean1,*sigma2);
  RooCBShape  *cb1 = new RooCBShape ("cb1", "Signal CB1", 
					  *mass,*mean1,*sigma1,*alpha,*npow); 
  RooCBShape  *cb2 = new RooCBShape ("cb2", "Signal CB2", 
					  *mass,*mean1,*sigma2,*alpha,*npow); 
  RooAddPdf *sigPdf_g1g2      = new RooAddPdf  ("sigG1G2","Jpsimass pdf Gaussian1+Gaussian2",
					  RooArgList(*gauss1,*gauss2),*sigmaFraction);
  RooAddPdf *sigPdf_g1c1      = new RooAddPdf  ("sigG1C1","Jpsimass pdf Gaussian1+CrystalBall1",
                                          RooArgList(*gauss1,*cb1),*sigmaFraction);
  RooAddPdf *sigPdf_g2c1      = new RooAddPdf  ("sigG2C1","Jpsimass pdf Gaussian2+CrystalBall1",
                                          RooArgList(*gauss2,*gauss2),*sigmaFraction);

  /// Background
  RooRealVar *pol_c1  = new RooRealVar("pol_c1", "polinomialcoefficient c1", 0., -15., 15.);
  RooRealVar *pol_c2  = new RooRealVar("pol_c2", "polinomialcoefficient c2", -0.03, -15., 15.);
  RooAbsPdf  *bkgPdf_pol  = new RooPolynomial("bkg_pol","polinomial background",
					 *mass, RooArgList(*pol_c1,*pol_c2));

  RooRealVar *exp_c1  = new RooRealVar("exp_c1", "Exponential coefficient c1", -1., -3, 0.1);
  RooAbsPdf  *bkgPdf_exp  = new RooExponential("bkg_exp","Exponential background",
                                         *mass, *exp_c1);

  /// Combined pdf
  RooRealVar *nsignal = new RooRealVar("nsignal","signal(JPsi) yield",5000.,10.,10000000.); 
  RooRealVar *nbkgd = new RooRealVar("nbkgd","brackground yield",2000.,10.,10000000.); 
  RooAbsPdf  *pdf   = new RooAddPdf ("pdf","total signal+background pdf", 
				     RooArgList(*sigPdf_g1c1,*bkgPdf_exp),
				     RooArgList(*nsignal,*nbkgd));
 
  bool nobg = isMC;
  bool varycb = false;
////  bool singlecb = true; //jkim
  //bool linearbg = true;

  if(linearbg_)
    pol_c2->setConstant(kTRUE);    

  if(!varycb) {
    alpha->setConstant(kTRUE);
    npow ->setConstant(kTRUE);
  }

  if(nobg) {
    nbkgd->setVal(0); nbkgd->setConstant(kTRUE);
    pol_c1->setConstant(kTRUE);    
    pol_c2->setConstant(kTRUE);    
    exp_c1->setConstant(kTRUE);    
  }

////  if(singlecb) {
////    sigmaFraction->setVal(1.); sigmaFraction->setConstant(kTRUE);
////    sigma2->setConstant(kTRUE);
////  }

  w.import(*pdf);
  w.import(*bkgPdf_exp);
}

/* cache the default fit parameters
 */
void getInitialParValues(RooWorkspace& w) {
  RooArgSet* pars = (RooArgSet*)w.pdf("pdf")->getParameters(*w.data("data"));//->selectByAttrib("Constant",kFALSE);
  TIterator* coefIter = pars->createIterator() ;
  RooRealVar* coef ;
  while((coef = (RooRealVar*)coefIter->Next())) {
    cout << "caching parameter " << coef->GetName() << "\t" << flush;
    coef->Print();
    initParVal_.push_back(coef->getVal());
    initParName_.push_back(coef->GetName());
  }  
}

/* reset initial parameters of the fit pdf
- to their default values
- if the dataset is specified, retune the yield to counting-based estimates
 */
void setDefaultFitParValues(RooWorkspace& w,RooAbsData* data) {
  if(!restorepars)
    return;
  RooArgSet* pars = (RooArgSet*)w.pdf("pdf")->getParameters(*w.data("data"));
  //->selectByAttrib("Constant",kFALSE);
  RooRealVar* par = 0;
  for(int i=0; i<pars->getSize();i++) {
    par = (RooRealVar*)pars->find(initParName_[i].data());
    cout << "reseting parameter " << par->GetName() << " " << par->getVal() << " ->\t" << flush;
    par->setVal(initParVal_[i]);
    par->Print();
  }
  if(data) {
    double nsig = data->sumEntries("Jpsi_Mass>3.05 & Jpsi_Mass<3.15");
    ((RooRealVar*)w.pdf("pdf")->getParameters(data)->find("nsignal"))->setMax(nsig*50);
    ((RooRealVar*)w.pdf("pdf")->getParameters(data)->find("nbkgd"))->setMax(nsig*50);
  }
}

double getWeightAv(RooWorkspace& w, RooAbsData* data) {
  RooAbsData* data0(data);
  TH1* hall = (TH1*)data0->createHistogram("weight",100);//,0,10) ;
  double wei=hall->GetMean();
  std::cout << "average signal weight " << wei << "\n";
  return wei;
}
