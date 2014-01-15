//////////////////////////////////////////////////////////////////////////
//
// 'BASIC FUNCTIONALITY' RooFit tutorial macro #102
// 
// Importing data from ROOT TTrees and THx histograms
//
//
//
// 07/2008 - Wouter Verkerke 
// 
/////////////////////////////////////////////////////////////////////////

/*#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"

using namespace RooFit ;
*/
TH1* makeDataTH1();
TH1* makeData2TH1();
TH1* makeMCSigTH1();
TH1* makeMCSig2TH1();
///void drawHisto(const TH1F& hData, const TH1F& hMCSig, const char& title, const TLegend& legLL);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");
TTree* makeTTree() ;

TFile* fEE1, * fME1, * fMM1, * fEE2, * fME2, * fMM2;
TString outDirName = ".";
const char* sigNames[] = {"hMCSig_TTbar"};
const char* sigLabels[] = {"t#bar{t}"};

void fitLepJPsi()
{
  ////////////////////////////////////////////////////////
  // I m p o r t i n g   R O O T   h i s t o g r a m s  //
  ////////////////////////////////////////////////////////

  // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
  // ---------------------------------------------------------

  TString path1 = "TopMass_1soft_wlxycut_lowAg1";
  TString path2 = "TopMass_1soft_wlxycut_lowAg2";
  
  fEE1 = TFile::Open(path1+"/ElEl2Mu/ElEl2Mu.root");
  fME1 = TFile::Open(path1+"/MuEl2Mu/MuEl2Mu.root");
  fMM1 = TFile::Open(path1+"/MuMu2Mu/MuMu2Mu.root");
  fEE2 = TFile::Open(path2+"/ElEl2Mu/ElEl2Mu.root");
  fME2 = TFile::Open(path2+"/MuEl2Mu/MuEl2Mu.root");
  fMM2 = TFile::Open(path2+"/MuMu2Mu/MuMu2Mu.root");

  if ( !fEE1 || !fME1 || !fMM1 || !fEE2 || !fME2 || !fMM2 ) return;

  //outDirName += "FitResults";
  //gSystem->Exec("rm -rf "+outDirName);
  //gSystem->Exec("mkdir "+outDirName);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0111);

  //TCanvas* c = new TCanvas("c","c", 600,600);
  
  // Create a ROOT TH1 histogram
  TH1F* hDataLepJPlowAg = makeDataTH1("Step_5", "LepJPsiMass1", "LepJPsiMass2") ;
  TH1F* hMCSigLepJPlowAg = makeMCSigTH1("Step_5", "LepJPsiMass1", "LepJPsiMass2") ;

  TH1F* hDataLepJP = makeData2TH1("Step_4", "LepJPsiMass1", "LepJPsiMass2") ;
  TH1F* hMCSigLepJP = makeMCSig2TH1("Step_4", "LepJPsiMass1", "LepJPsiMass2") ;
  
  cout<<"N hDataLepJP : "<< hDataLepJP->Integral()<<endl;
  cout<<"N hMCSigLepJP : "<< hMCSigLepJP->Integral()<<endl;
  cout<<"N hDataLepJPlowAg : "<< hDataLepJPlowAg->Integral()<<endl;
  cout<<"N hMCSigLepJPlowAg : "<< hMCSigLepJPlowAg->Integral()<<endl;

  TLegend* legLL = buildLegend();
  if ( hDataLepJPlowAg->GetEntries() > 0 && hDataLepJP->GetEntries() > 0 ) 
  legLL->AddEntry(hDataLepJPlowAg, "Data", "p"); 
  legLL->AddEntry(hMCSigLepJPlowAg, sigLabels[0], "f");

  //drawHisto(hDataLepJPlowAg,hMCSigLepJPlowAg,"M_lJPsi(lower angle);M_{lJ/#psi} (GeV/c^2)", legLL);
  //drawHisto(hDataLepJP,hMCSigLepJP,"M_lJPsi(wrong+correct);M_{lJ/#psi} (GeV/c^2)", legLL);
  

  double YmaxSig=0, YmaxData=0, Ymax=0;
  YmaxSig = hDataLepJPlowAg->GetMaximum();
  YmaxData = hMCSigLepJPlowAg->GetMaximum();
  if(YmaxSig >YmaxData) Ymax=YmaxSig;
  else               Ymax=YmaxData;

  TCanvas* c1 = new TCanvas("c1","M_lJ/Psi(lower angle)");
  
  //hDataLepJPlowAg->SetLineColor(kRed);
  hMCSigLepJPlowAg->SetMaximum(Ymax*1.3);
  hDataLepJPlowAg->SetMaximum(Ymax*1.3);
  hDataLepJPlowAg->SetTitle("M_lJPsi(lower angle);M_{lJ/#psi} (GeV/c^2)");
  //hMCSigLepJP->SetFillColor(kYellow);
  //hMCSigLepJPlowAg->Draw();
 // hDataLepJPlowAg->Draw("same");
  //legLL->Draw();
  //getHeader(19.6, "All channel")->Draw();
  hMCSigLepJPlowAg->Fit("gaus","","",20,120);
  hDataLepJPlowAg->Draw("same");
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();

/*
 //hDataLepJP->SetLineColor(kRed);
  hMCSigLepJP->SetMaximum(Ymax*2.5);
  hDataLepJP->SetMaximum(Ymax*2.5);
  //hMCSigLepJP->SetFillColor(kYellow);
  //hMCSigLepJP->Draw();
 // hDataLepJP->Draw("same");
  hMCSigLepJP->Fit("gaus","","",20,120);
  hDataLepJP->Draw("same");
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();
*/
  // Declare observable x
////  RooRealVar x("x","x", 0,120) ;

  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
////  RooDataHist dh("dh","dh",x,Import(*hMCSigLepJP)) ;


  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------

  // Make plot of binned dataset showing Poisson error bars (RooFit default)
////  RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
////  dh.plotOn(frame) ; 

  // Fit a Gaussian p.d.f to the data
///  RooRealVar mean("mean","mean",60,0,120) ;
///  RooRealVar sigma("sigma","sigma",27,0.1,30) ;
///  RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
///  gauss.fitTo(dh) ;
///  gauss.plotOn(frame) ;

  // P l o t   a n d   f i t   a   R o o D a t a H i s t   w i t h   i n t e r n a l   e r r o r s
  // ---------------------------------------------------------------------------------------------

  // If histogram has custom error (i.e. its contents is does not originate from a Poisson process
  // but e.g. is a sum of weighted events) you can data with symmetric 'sum-of-weights' error instead
  // (same error bars as shown by ROOT)
///  RooPlot* frame2 = x.frame(Title("Imported TH1 with internal errors")) ;
///  dh.plotOn(frame2,DataError(RooAbsData::SumW2)) ; 
///  gauss.plotOn(frame2) ;

  // Please note that error bars shown (Poisson or SumW2) are for visualization only, the are NOT used
  // in a maximum likelihood fit
  //
  // A (binned) ML fit will ALWAYS assume the Poisson error interpretation of data (the mathematical definition 
  // of likelihood does not take any external definition of errors). Data with non-unit weights can only be correctly
  // fitted with a chi^2 fit (see rf602_chi2fit.C) 


  ////////////////////////////////////////////////
  // I m p o r t i n g   R O O T  T T r e e s   //
  ////////////////////////////////////////////////


  // I m p o r t   T T r e e   i n t o   a   R o o D a t a S e t
  // -----------------------------------------------------------

/*  TTree* tree = makeTTree() ;
  
  // Define 2nd observable y
  RooRealVar y("y","y",-10,10) ;

  // Construct unbinned dataset importing tree branches x and y matching between branches and RooRealVars 
  // is done by name of the branch/RRV 
  // 
  // Note that ONLY entries for which x,y have values within their allowed ranges as defined in 
  // RooRealVar x and y are imported. Since the y values in the import tree are in the range [-15,15]
  // and RRV y defines a range [-10,10] this means that the RooDataSet below will have less entries than the TTree 'tree'

  RooDataSet ds("ds","ds",RooArgSet(x,y),Import(*tree)) ;


  // P l o t   d a t a s e t   w i t h   m u l t i p l e   b i n n i n g   c h o i c e s
  // ------------------------------------------------------------------------------------
  
  // Print number of events in dataset
  ds.Print() ;

  // Print unbinned dataset with default frame binning (100 bins)
  RooPlot* frame3 = y.frame(Title("Unbinned data shown in default frame binning")) ;
  ds.plotOn(frame3) ;
  
  // Print unbinned dataset with custom binning choice (20 bins)
  RooPlot* frame4 = y.frame(Title("Unbinned data shown with custom binning")) ;
  ds.plotOn(frame4,Binning(20)) ;
*/  
  // Draw all frames on a canvas
///  TCanvas* c = new TCanvas("rf102_dataimport","rf102_dataimport",800,800) ;
///  c->Divide(2,2) ;
///  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
///  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
  /////c->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
  /////c->cd(4) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
  
}



//hData_Step_8_LepJPsiMass1 + hData_Step_8_LepJPsiMass2
TH1* makeDataTH1(const char* cutStep, const char* histName1, const char* histName2 ) 
{
  // Create ROOT TH1 filled with a Gaussian distribution

  TH1F* hDataEE1 = (TH1F*)fEE1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataME1 = (TH1F*)fME1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataMM1 = (TH1F*)fMM1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataEE2 = (TH1F*)fEE2->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));
  TH1F* hDataME2 = (TH1F*)fME2->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));
  TH1F* hDataMM2 = (TH1F*)fMM2->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));

  if ( !hDataEE1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for EE1 " << "\n"; return; }
  if ( !hDataME1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for ME1 " << "\n"; return; }
  if ( !hDataMM1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for MM1 " << "\n"; return; }
  if ( !hDataEE2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for EE2 " << "\n"; return; }
  if ( !hDataME2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for ME2 " << "\n"; return; }
  if ( !hDataMM2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for MM2 " << "\n"; return; }

  TH1F* hDataLL = (TH1F*)hDataEE1->Clone(Form("hDataSub_%s_%s", cutStep, histName1));
  hDataLL->Reset();
  hDataLL->Add(hDataEE1);
  hDataLL->Add(hDataEE2);
  hDataLL->Add(hDataME1);
  hDataLL->Add(hDataME2);
  hDataLL->Add(hDataMM1);
  hDataLL->Add(hDataMM2);

  return hDataLL ;
}

TH1* makeData2TH1(const char* cutStep, const char* histName1, const char* histName2 )
{
  // Create ROOT TH1 filled with a Gaussian distribution

  TH1F* hDataEE1 = (TH1F*)fEE1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataME1 = (TH1F*)fME1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataMM1 = (TH1F*)fMM1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName1));
  TH1F* hDataEE2 = (TH1F*)fEE1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));
  TH1F* hDataME2 = (TH1F*)fME1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));
  TH1F* hDataMM2 = (TH1F*)fMM1->Get(Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName2));

  if ( !hDataEE1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for EE1 " << "\n"; return; }
  if ( !hDataME1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for ME1 " << "\n"; return; }
  if ( !hDataMM1 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for MM1 " << "\n"; return; }
  if ( !hDataEE2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for EE2 " << "\n"; return; }
  if ( !hDataME2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for ME2 " << "\n"; return; }
  if ( !hDataMM2 ) { cout << Form("%s/hDataSub_%s_%s", cutStep, cutStep, histName) << " for MM2 " << "\n"; return; }

  TH1F* hDataLL = (TH1F*)hDataEE1->Clone(Form("hDataSub_%s_%s_2TH1", cutStep, histName1));
  hDataLL->Reset();
  hDataLL->Add(hDataEE1);
  hDataLL->Add(hDataEE2);
  hDataLL->Add(hDataME1);
  hDataLL->Add(hDataME2);
  hDataLL->Add(hDataMM1);
  hDataLL->Add(hDataMM2);

  return hDataLL ;
}

TH1* makeMCSigTH1(const char* cutStep, const char* histName1, const char* histName2)
{
  // Create ROOT TH1 filled with a Gaussian distribution
  
  TH1F* hSigEE1 = (TH1F*)fEE1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigME1 = (TH1F*)fME1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigMM1 = (TH1F*)fMM1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigEE2 = (TH1F*)fEE2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));
  TH1F* hSigME2 = (TH1F*)fME2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));
  TH1F* hSigMM2 = (TH1F*)fMM2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));

  if ( !hSigEE1 || !hSigME1 || !hSigMM1 || !hSigEE2 || !hSigME2 || !hSigMM2) 
  { 
      cout << "No signal hist for " << histName << "\n"; return; 
  }

  TH1F* hSigLL = (TH1F*)hSigEE1->Clone(Form("%s_%s_%s", sigNames[0], cutStep, histName1));
  hSigLL->Reset();
  hSigLL->Add(hSigEE1);
  hSigLL->Add(hSigEE2);
  hSigLL->Add(hSigME1);
  hSigLL->Add(hSigME2);
  hSigLL->Add(hSigMM1);
  hSigLL->Add(hSigMM2);

  return hSigLL ;
}

TH1* makeMCSig2TH1(const char* cutStep, const char* histName1, const char* histName2)
{
  // Create ROOT TH1 filled with a Gaussian distribution

  TH1F* hSigEE1 = (TH1F*)fEE1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigME1 = (TH1F*)fME1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigMM1 = (TH1F*)fMM1->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName1));
  TH1F* hSigEE2 = (TH1F*)fEE2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));
  TH1F* hSigME2 = (TH1F*)fME2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));
  TH1F* hSigMM2 = (TH1F*)fMM2->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName2));

  if ( !hSigEE1 || !hSigME1 || !hSigMM1 || !hSigEE2 || !hSigME2 || !hSigMM2)
  {
      cout << "No signal hist for " << histName << "\n"; return;
  }

  TH1F* hSigLL = (TH1F*)hSigEE1->Clone(Form("%s_%s_%s_2TH1", sigNames[0], cutStep, histName1));
  hSigLL->Reset();
  hSigLL->Add(hSigEE1);
  hSigLL->Add(hSigEE2);
  hSigLL->Add(hSigME1);
  hSigLL->Add(hSigME2);
  hSigLL->Add(hSigMM1);
  hSigLL->Add(hSigMM2);

  return hSigLL ;
}

TTree* makeTTree() 
{
  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y

  TTree* tree = new TTree("tree","tree") ;
  Double_t* px = new Double_t ;
  Double_t* py = new Double_t ;
  tree->Branch("x",px,"x/D") ;
  tree->Branch("y",py,"y/D") ;
  for (int i=0 ; i<100 ; i++) {
    *px = gRandom->Gaus(0,3) ;
    *py = gRandom->Uniform()*30 - 15 ;
    tree->Fill() ;
  }
  return tree ;
}

//void drawHisto(const TH1F& hData, const TH1F& hMCSig, const char& title, const TLegend& legLL)
//{
/*  TCanvas* c = new TCanvas("c", "c", 700, 500);

  //TH1F* hData = hDataName; //gDirectory->Get(Form("%s", hDataName));
  //TH1F* hMCSig = hMCSigName; //gDirectory->Get(Form("%s", hMCSigName));

  double YmaxSig=0, YmaxData=0, Ymax=0;
  YmaxSig = hData->GetMaximum();
  YmaxData = hMCSig->GetMaximum();
  if(YmaxSig >YmaxData) Ymax=YmaxSig;
  else               Ymax=YmaxData;

  if ( hData->GetEntries() > 0  )
  legLL->AddEntry(hData, "Data", "p");
  legLL->AddEntry(hMCSig, sigLabels[0], "f");

  //hData->SetLineColor(kRed);
  hMCSig->SetMaximum(Ymax*1.3);
  hData->SetMaximum(Ymax*1.3);
  hData->SetTitle(title);
  hMCSig->SetTitle(title);
  //hMCSig->SetFillColor(kYellow);
  hMCSig->Fit("gaus","","",20,120);
  hData->Draw("same");
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();

  c->Print(Form("./png/%s.png", hData.Name()));
*/
//}

TLegend* buildLegend()
{
  TLegend* leg = new TLegend(0.73,0.60,0.85,0.85,NULL,"brNDC");

  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  return leg;
}

TPaveText* getHeader(double lumi, TString channelName)
{
  TPaveText* pt = new TPaveText(0.18,0.75,0.18,0.90,"brNDC");

  pt->SetBorderSize(1);
  pt->SetTextFont(42);
  pt->SetTextSize(0.04);
  pt->SetLineColor(0);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->SetTextAlign(12);
  //pt->AddText("CMS Preliminary");
  pt->AddText(Form("%.1f fb^{-1} at  #sqrt{s} = 8 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}

