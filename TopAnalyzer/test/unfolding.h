#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TVectorD.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TTree.h"
#include "TCut.h"
#include "TGraphAsymmErrors.h"
#include "style.h"
#include "TGraph.h"
#include "TMatrixD.h"
#include <iomanip>
#include <iostream>

//double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
double binsMass[] = {0,50,100,150,200,250,300, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

void unfoldingPlot(TH1* h_gen, TH1* h_rec, TH2* m, TH1* h_mea, TH1* h_genTTbar, TH1F* accept, TString name, double lumi, int k, RooUnfold::ErrorTreatment & err, bool print, bool pseudo){

  RooUnfoldResponse *response = new RooUnfoldResponse(h_rec, h_gen, m);

  TH1F *hgen = (TH1F*)h_genTTbar->Clone("hgen");
  TH1F *hmea = (TH1F*)h_mea->Clone("hmea");
  TH1F *hrec = (TH1F*)h_rec->Clone("hrec");
  hgen->SetLineColor(2);
  hmea->SetLineColor(4);


  //response matrix plot ====================================================================================
  TCanvas *c_response = new TCanvas(Form("c_response_%s",name.Data()),Form("c_response_%s",name.Data()),1);
  TMatrixD * Mres = (TMatrixD *) response->Mresponse();
  TH2D* hResponse = new TH2D(*Mres);
  hResponse->GetXaxis()->SetTitle("Generated M_{t#bar{t}} bin number");
  hResponse->GetYaxis()->SetTitle("Reconstructed M_{t#bar{t}} bin number");
  hResponse->Draw("box");
  //==========================================================================================================

  //unfolded result to be compare with truth level============================================================
  TCanvas *c = new TCanvas(Form("c_unfold_%s",name.Data()),Form("c_unfold_%s",name.Data()), 1);
  c->SetLogy();
  //unfolding
  hgen->SetLineWidth(2);
  hgen->SetStats(0);
  hgen->SetTitle(""); 
  hgen->GetYaxis()->SetTitle("Events");
  hgen->GetXaxis()->SetTitle("Unfolded M_{t#bar{t}}");

  RooUnfold* unfold = 0;
  //unfold = new RooUnfoldBayes(response, h_mea, 4);    // OR
  unfold = new RooUnfoldSvd(response, h_mea, k);   // OR
  //unfold = new RooUnfoldBinByBin(response, h_mea);
  //unfold = new RooUnfoldInvert(response, h_mea);
  TH1F* h_unfold = (TH1F*) unfold->Hreco(err);
 
  int nbins = h_unfold->GetNbinsX();
 
  TMatrixD m_unfoldE = unfold->Ereco();
  //TVectorD v_unfoldE = unfold->ErecoV(RooUnfold::kCovariance);

  TH1* truthDist = getTruthDist(hgen);
  truthDist->Draw();
  truthDist->GetXaxis()->SetTitle("M_{t#bar{t}} (GeV/c^{2})");
  truthDist->SetFillColor(6);
  if(pseudo){
    hmea->SetLineStyle(2);
    hmea->SetLineWidth(2);
    hmea->Draw("Same");  
    hmea->SetStats(0);
  }
  h_unfold->Draw("Psame");
  h_unfold->SetLineColor(1);
  h_unfold->SetLineWidth(2);
  h_unfold->SetMarkerStyle(20);
  h_unfold->SetMarkerSize(1.0);
  h_unfold->SetStats(0);  

  TLegend *l_unfold= new TLegend(0.58,0.68,0.80,0.8);
  l_unfold->AddEntry(truthDist,"MC Truth t#bar{t}","F");
  if(pseudo){
    l_unfold->AddEntry(hmea,"Pseudo-Data t#bar{t}","l");
  }
  l_unfold->AddEntry(h_unfold,"Unfolded t#bar{t}","p");
  l_unfold->SetTextSize(0.05);
  l_unfold->SetFillColor(0);
  l_unfold->SetLineColor(0);
  l_unfold->Draw();

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  //label->DrawLatex(x,y,"CMS Preliminary 2010");
  label->DrawLatex(0.50,0.88,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));
  //===============================================================================================

  //Toy Test =======================================================================================
  bool toy=false;
  if(toy){
    unfold->RooUnfoldSvd::SetNtoysSVD(1000);
    cout << "n. of toys= " << unfold->RooUnfoldSvd::GetNtoysSVD() << endl;
    TCanvas *c_toy =  new TCanvas(Form("c_toy_%s",name.Data()),Form("c_toy_%s",name.Data()),800,800);
    c_toy->Divide(3,3);
    //float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
    //int nDet = sizeof(detBins)/sizeof(float) - 1;

    TH1 *h[9];
    TF1 *g[9];

    for(int i=0; i <nbins; i++){
       double center = hgen->GetBinContent(i+1);
       //h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 200, (center+10)-100,(center+10)+100);
       h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 1000,-10,10);
    } 

    for(int i=0 ; i < 10000 ; i++){
      double *chi2_ = 0;
      //TH1* unfoldedToy =  unfold->Runtoy(RooUnfold::kCovariance,chi2_,hGen);
      TH1* unfoldedToy =  unfold->Runtoy();
      for(int j=0; j <nbins; j++){
        double rec_ = RooUnfoldResponse::GetBinContent(unfoldedToy,j+1,true);
        double toyerror_ = RooUnfoldResponse::GetBinError(unfoldedToy,j+1,true);
        double error_ = h_unfold->GetBinError(j+1);
        if( i == 9999) cout << "toy error= " << toyerror_ << " error = " << error_ << endl; 
        double gen_ = hgen->GetBinContent(j+1);
        //double pull_ = (gen_ - rec_)/gen_;
        double pull_ = (gen_ - rec_)/error_;
        //h[j]->Fill(rec_);
        h[j]->Fill(pull_);
      }
    }
  
    for(int i=0; i<nbins; i++){
      c_toy->cd(i+1);
      h[i]->Fit("gaus");
      g[i]  = h[i]->GetFunction("gaus");
      h[i]->Draw();
      gStyle->SetStatH(0.4);
      gStyle->SetStatW(0.2);
      gStyle->SetStatFontSize(0.05);
      gStyle->SetStatBorderSize(1);
      h[i]->SetTitle(Form("%1.0f-%1.0f GeV",detBins[i],detBins[i+1]));
      //h[i]->GetXaxis()->SetTitle("Unfolded number of events");
      //h[i]->GetXaxis()->SetTitle("N_{true}-N_{unfolded}/N_{true}");
      h[i]->GetXaxis()->SetTitle("(N_{true}-N_{unfolded})/#sigma");
      h[i]->GetYaxis()->SetTitle("Number of toy MC");
    }

    for(int i=0; i<nbins; i++){
      double Mean = h[i]->GetMean();
      double rms = h[i]->GetRMS();
      double mean = g[i]->GetParameter(1);
      double sigma = g[i]->GetParameter(2);
      double mass = (detBins[i+1] + detBins[i])/2;
      double meanerr = g[i]->GetParError(1);
      double sigmaerr = g[i]->GetParError(2);
      cout << "$" << hgen->GetBinCenter(i+1)-hgen->GetBinWidth(i+1)/2 << "-" << hgen->GetBinCenter(i+1)+hgen->GetBinWidth(i+1)/2 << "$   ~&~ "
           << setprecision (4) << mean << " $\\pm$ " << sigma 
           << " \\\\" <<  endl;
    }
  }
  //==================================================================================================

  //err after unfolding =============================================================================

  TCanvas *c_err = new TCanvas(Form("c_err_%s",name.Data()),Form("c_err_%s",name.Data()),1); 

  TGraph *gerr = new TGraph(nbins);  
  TGraph *gerrbefore = new TGraph(nbins);  

  for(int i=1; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
    } else{
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), -1);
    }

    if( hmea->GetBinContent(i) != 0){
      gerrbefore->SetPoint(i-1, hmea->GetBinCenter(i), 100*hmea->GetBinError(i)/hmea->GetBinContent(i));
    } else {
      gerrbefore->SetPoint(i-1, hmea->GetBinCenter(i), -1);
    }
  }

  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  label->DrawLatex(0.30,0.88,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));

  //====================================================================================================

  //err before unfolding ===============================================================================
  TCanvas *c_meaerr = new TCanvas(Form("c_meaerr_%s",name.Data()),Form("c_meaerr_%s",name.Data()),1);
  gerrbefore->SetTitle(0);
  gerrbefore->Draw("ALP");
  gerrbefore->SetMarkerStyle(20);
  gerrbefore->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerrbefore->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  //====================================================================================================
  //covariance matrix =============================================================================
  TCanvas *c_errmat = new TCanvas(Form("c_errmat_%s",name.Data()),Form("c_errmat_%s",name.Data()),1);
  //m_unfoldE.Draw("colz");
  TH2D* hErrMat = new TH2D(m_unfoldE);
  hErrMat->GetXaxis()->SetTitle("Generated M_{t#bar{t}} bin number");
  hErrMat->GetYaxis()->SetTitle("Reconstructed M_{t#bar{t}} bin number");
  hErrMat->Draw("colz");
  //================================================================================================== 

  //log d plot =====================================================================================
  TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  c_d->SetLogy();
  TH1D* h_d = unfold->RooUnfoldSvd::Impl()->GetD();
  h_d->SetTitle(0);
  h_d->Draw("PC");
  h_d->GetYaxis()->SetTitle("log|d_{i}|");
  h_d->GetXaxis()->SetTitle("i");
  //================================================================================================

  //cross section plot ================================================================================================
  cout << "Unfolded: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaData = printFinal(nbins, h_unfold, accept, lumi, false);
  cout << "Truth: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaTruth = printFinal(nbins, hgen, accept, lumi, true);
  TH1* hSigmaTruth = getSigmaTruth(hgen, accept, lumi);

  TCanvas *c_dsigma = new TCanvas(Form("c_dsigma_%s",name.Data()),Form("c_dsigma_%s",name.Data()));
  c_dsigma->SetLogy();
  hSigmaTruth->SetLineWidth(1);
  hSigmaTruth->SetLineStyle(1);
  hSigmaTruth->SetTitle(0);
  hSigmaTruth->Draw();
  hSigmaTruth->SetMaximum(9);
  hSigmaTruth->GetXaxis()->SetTitle("Unfolded t#bar{t} invariant mass (GeV/c^{2})");
  hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}} (pb/GeV/c^{2})");
  dsigmaTruth->SetFillColor(30);
  dsigmaTruth->SetFillStyle(3001);
  dsigmaTruth->SetLineColor(0);
  dsigmaTruth->Draw("2same");
  dsigmaData->Draw("Psame");

  TLegend *l_dsigma= new TLegend(0.58,0.68,0.80,0.8);
  l_dsigma->AddEntry(hSigmaTruth, "SM Expectation","L");
  l_dsigma->AddEntry(dsigmaTruth, "SM Uncertainties","F");
  l_dsigma->AddEntry(dsigmaData, "Unfolded Data","P");
  l_dsigma->SetTextSize(0.04);
  l_dsigma->SetFillColor(0);
  l_dsigma->SetLineColor(0);
  l_dsigma->Draw();

  label->DrawLatex(0.47,0.88,"CMS Preliminary");
  label->DrawLatex(0.47,0.82.5,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));
  //======================================================================================================================  

  //normalized cross section plot ================================================================================================
  cout << "Unfolded: evt number / probability" << endl;
  TGraphAsymmErrors* NormdsigmaData = printFinal(nbins, h_unfold, accept, lumi, false,true);
  cout << "Truth: evt number / probability" << endl;
  TGraphAsymmErrors* NormdsigmaTruth = printFinal(nbins, hgen, accept, lumi, true,true);
  TH1* NormhSigmaTruth = getSigmaTruth(hgen, accept, lumi, true);

  TCanvas *c_Normdsigma = new TCanvas(Form("c_Normdsigma_%s",name.Data()),Form("c_Normdsigma_%s",name.Data()));
  c_Normdsigma->SetLogy();
  NormhSigmaTruth->SetLineWidth(1);
  NormhSigmaTruth->SetLineStyle(1);
  NormhSigmaTruth->SetTitle(0);
  NormhSigmaTruth->Draw();
  NormhSigmaTruth->SetMaximum(0.05);
  NormhSigmaTruth->SetMinimum(0.00001);
  NormhSigmaTruth->GetXaxis()->SetTitle("Unfolded t#bar{t} invariant mass (GeV/c^{2})");
  NormhSigmaTruth->GetYaxis()->SetTitle("1/#sigma_{t#bar{t}} d#sigma/dM_{t#bar{t}} (1/GeV/c^{2})");
  NormdsigmaTruth->SetFillColor(30);
  NormdsigmaTruth->SetFillStyle(3001);
  NormdsigmaTruth->SetLineColor(0);
  NormdsigmaTruth->Draw("2same");
  NormdsigmaData->Draw("Psame");

  TLegend *l_Normdsigma= new TLegend(0.58,0.68,0.80,0.8);
  l_Normdsigma->AddEntry(NormhSigmaTruth, "SM Expectation","L");
  l_Normdsigma->AddEntry(NormdsigmaTruth, "SM Uncertainties","F");
  l_Normdsigma->AddEntry(NormdsigmaData, "Unfolded Data","P");
  l_Normdsigma->SetTextSize(0.04);
  l_Normdsigma->SetFillColor(0);
  l_Normdsigma->SetLineColor(0);
  l_Normdsigma->Draw();

  label->DrawLatex(0.47,0.88,"CMS Preliminary");
  label->DrawLatex(0.47,0.82.5,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));
  //================================================================================================================


  //Printing chi2
  chi2.push_back(unfold->Chi2(hgen, err)); 
  cout << "chi2 : " << unfold->Chi2(hgen, err) << endl;

  //Saving canvas 
  if(print){
    c_response->Print(Form("cUF_response_%s.eps",name.Data()));
    c->Print(Form("cUF_unfold_%s.eps",name.Data()));
    c_err->Print(Form("cUF_err_%s.eps",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.eps",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.eps",name.Data()));
    c_dsigma->Print(Form("cUF_dsigma_%s.eps",name.Data()));
    c_Normdsigma->Print(Form("cUF_Normdsigma_%s.eps",name.Data()));
    c_d->Print(Form("cUF_d_%s.eps",name.Data()));
    if(toy)c_toy->Print(Form("cUF_toy_%s.eps",name.Data()));

    c_response->Print(Form("cUF_response_%s.png",name.Data()));
    c->Print(Form("cUF_unfold_%s.png",name.Data()));
    c_err->Print(Form("cUF_err_%s.png",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.png",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.png",name.Data()));
    c_dsigma->Print(Form("cUF_dsigma_%s.png",name.Data()));
    c_Normdsigma->Print(Form("cUF_Normdsigma_%s.png",name.Data()));
    c_d->Print(Form("cUF_d_%s.png",name.Data()));
    if(toy)c_toy->Print(Form("cUF_toy_%s.png",name.Data()));

  }
}

TGraphAsymmErrors* printFinal( int nbins, TH1F* hgen, TH1F* accept, double lumi, bool truth, bool norm=false ){

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;

  double totalN = 0;
  double totalS = 0;
  double integralS = 0;

  for(int i=1; i <=  nbins; i++){
    double x;
    double y;

    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i); 
    double unfolded = hgen->GetBinContent(i);
    double sigma = 0;
    if(y != 0) sigma = unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    double width = hgen->GetBinWidth(i);

    totalN += unfolded;
    totalS += sigma*width;
    integralS += sigma*width;
  }

  for(int i=1; i <=  nbins; i++){
    double x;
    double y;
    //accept->GetPoint(i-1,x,y);
      
    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i); 
 
    double unfolded = hgen->GetBinContent(i);
    double err = hgen->GetBinError(i); 
    double sigma = 0;
    if( y != 0) sigma = unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    double sigmaErr = 0;
    if(unfolded != 0) sigmaErr = sigma*err/unfolded;
    else sigmaErr = 0;

    double width = hgen->GetBinWidth(i);

    dsigma->SetPointEXhigh(i-1, width/2);
    dsigma->SetPointEXlow(i-1, width/2);
    if(norm){
      dsigma->SetPointEYhigh(i-1, sigmaErr/totalS);
      dsigma->SetPointEYlow(i-1, sigmaErr/totalS);
      dsigma->SetPoint(i-1, x, sigma/totalS );
      cout << "$" << hgen->GetBinCenter(i)-hgen->GetBinWidth(i)/2 << "-" << hgen->GetBinCenter(i)+hgen->GetBinWidth(i)/2 << "$   ~&~ "
         << setprecision (4) << hgen->GetBinContent(i) << " $\\pm$ " << err << " ~&~ "
         << sigma/totalS << " $\\pm$ " << sigmaErr/totalS
         << " \\\\" <<  endl;
    }else{
      dsigma->SetPointEYhigh(i-1, sigmaErr);
      dsigma->SetPointEYlow(i-1, sigmaErr);
      dsigma->SetPoint(i-1, x, sigma );
      cout << "$" << hgen->GetBinCenter(i)-hgen->GetBinWidth(i)/2 << "-" << hgen->GetBinCenter(i)+hgen->GetBinWidth(i)/2 << "$   ~&~ "
         << setprecision (4) << hgen->GetBinContent(i) << " $\\pm$ " << err << " ~&~ "
         << sigma << " $\\pm$ " << sigmaErr
         << " \\\\" <<  endl;
    }
  }
  cout << "total unfolded= " << totalN << " integrated sigma= " << totalS << endl;
  
  return dsigma;
}

TH1* getSigmaTruth(TH1F* hgen, TH1F* accept, double lumi, bool norm=false ){

  int nbins = hgen->GetNbinsX(); 

  TH1* dsigma = new TH1F("dsigma","dsigma", nbins, binsMass);

  double totalS = 0;
  for(int i=1; i <=  nbins; i++){
    double x;
    double y;
    //accept->GetPoint(i-1,x,y);
    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i);

    double unfolded = hgen->GetBinContent(i);
    double sigma = 0;
    if(y != 0) sigma = unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    double width = hgen->GetBinWidth(i);
    totalS += sigma*width;
  }


  for(int i=1; i <=  nbins; i++){
    double x;
    double y;
    //accept->GetPoint(i-1,x,y);
    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i);

    double unfolded = hgen->GetBinContent(i);
    double sigma = 0;
    if( y != 0) sigma = unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    if(norm){
      dsigma->SetBinContent(i, sigma/totalS);
    }else{
      dsigma->SetBinContent(i, sigma);
    }
  }

  return dsigma;
}

TH1* getTruthDist(TH1F* hgen){

  int nbins = hgen->GetNbinsX();

  TH1* truth = new TH1F("truth","truth", nbins, binsMass);

  for(int i=1; i <=  nbins; i++){
    double unfolded = hgen->GetBinContent(i);
    truth->SetBinContent(i, unfolded);
  }

  return truth;
}


