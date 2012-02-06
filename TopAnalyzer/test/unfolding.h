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

TH1F* unfoldingPlot(int algo, TH2* m, TH1* h_mea, TH1* h_genTTbar, TString name, double lumi, int k, RooUnfold::ErrorTreatment & err, bool print, bool pseudo, bool toy){

  const TH1* h_gen = m->ProjectionY();
  const TH1* h_rec = m->ProjectionX();

  int nbins = h_gen->GetNbinsX();

  RooUnfoldResponse *response = new RooUnfoldResponse(h_rec, h_gen, m);

  TH1F *hgen = (TH1F*)h_genTTbar->Clone("hgen");
  TH1F *hmea = (TH1F*)h_mea->Clone("hmea");
  TH1F *hrec = (TH1F*)h_rec->Clone("hrec");
  hgen->SetLineColor(2);
  hmea->SetLineColor(4);


  //response matrix plot ====================================================================================
  if(print){
    TCanvas *c_response = new TCanvas(Form("c_response_%s",name.Data()),Form("c_response_%s",name.Data()),1);
    TMatrixD * Mres = (TMatrixD *) response->Mresponse();
    TH2D* hResponse = new TH2D(*Mres);
    hResponse->GetXaxis()->SetTitle("Generated M_{t#bar{t}} bin number");
    hResponse->GetYaxis()->SetTitle("Reconstructed M_{t#bar{t}} bin number");
    hResponse->Draw("box");
  //==========================================================================================================

  //response plot ====================================================================================
    TCanvas *c_responseH = new TCanvas(Form("c_responseH_%s",name.Data()),Form("c_responseH_%s",name.Data()),1);
    TH2D * Hres = (TH2D *) response->Hresponse();

    Hres->GetYaxis()->SetTitle("Generated M_{t#bar{t}} (GeV/c^{2})");
    Hres->GetXaxis()->SetTitle("Reconstructed M_{t#bar{t}} (GeV/c^{2})");
    Hres->Draw("colTextbox");
    double total = Hres->Integral();
  }
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
  if(algo == 0) unfold = new RooUnfoldBinByBin(response, h_mea);
  if(algo == 1) unfold = new RooUnfoldInvert(response, h_mea);
  if(algo == 2) unfold = new RooUnfoldSvd(response, h_mea, k);
  if(algo == 3) unfold = new RooUnfoldBayes(response, h_mea, 4);    
  TH1F* h_unfold = (TH1F*) unfold->Hreco(err);
  //h_unfold->Scale(2.0); 
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
  //h_unfold->Scale(2.0);
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
  label->DrawLatex(0.50,0.88,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));

  //////////////////////////////////////////
  unfold->PrintTable(cout, truthDist, err);
  //////////////////////////////////////////

  //===============================================================================================

  //Toy Test =======================================================================================
  if(toy){
    unfold->RooUnfoldSvd::SetNtoysSVD(1000);
    cout << "n. of toys= " << unfold->RooUnfoldSvd::GetNtoysSVD() << endl;

    bool skip = h_unfold->GetBinContent(1) == 0;

    TH1 *h1[9];
    TH1 *h2[9];
    TF1 *g1[9];
    TF1 *g2[9];

    for(int i=0; i <nbins; i++){
       double center = hgen->GetBinContent(i+1);
       //h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 200, (center+10)-100,(center+10)+100);
       //h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 1000,-10,10);
       h1[i] = new TH1F(Form("bin %1.0f ",i+1), Form("bin %1.0f",i+1), 650,-5,8);
       h2[i] = new TH1F(Form("bin %1.0f ",i+1), Form("bin %1.0f",i+1), 100,-1,1);
    } 

    for(int i=0 ; i < 10000 ; i++){
      double *chi2_ = 0;
      //TH1* unfoldedToy =  unfold->Runtoy(RooUnfold::kCovariance,chi2_,hGen);
      TH1* unfoldedToy =  unfold->Runtoy();
      double total_unfolded = unfoldedToy->Integral();
      double total_gen = hgen->Integral();
o     if ( i == 9999) cout << total_unfolded << " " << total_gen << endl;
      for(int j=0; j <nbins; j++){
        double rec_ = RooUnfoldResponse::GetBinContent(unfoldedToy,j+1,true);
        double toyerror_ = RooUnfoldResponse::GetBinError(unfoldedToy,j+1,true);
        double error_ = h_unfold->GetBinError(j+1);
        if( i == 9999) cout << "toy unfolded= " << rec_ << " error= " << toyerror_ << " error = " << error_ << endl; 
        double gen_ = hgen->GetBinContent(j+1);
        double pullNtrue_ = (gen_ - rec_)/gen_;
        //double pullNtrue_ = ( (gen_/total_gen) - (rec_/total_unfolded) ) / (gen_/total_gen);
        double pullerror_ = (gen_ - rec_)/error_;
        h1[j]->Fill(pullerror_);
        h2[j]->Fill(pullNtrue_);
      }
    }

    TCanvas *c_toy_sigma =  new TCanvas(Form("c_toy_sigma_%s",name.Data()),Form("c_toy_sigma_%s",name.Data()),800,800);

    if( skip ){
      cout << "2x4" << endl;
      c_toy_sigma->Divide(2,4);
    }else{
      cout << "3x3" << endl;
      c_toy_sigma->Divide(3,3);
    }
  
    int k = 0;
    if(skip) k = 1;

    for(int i=k; i<nbins; i++){
      c_toy_sigma->cd(i-k+1);
      h1[i]->Fit("gaus");
      g1[i]  = h1[i]->GetFunction("gaus");
      h1[i]->Draw();
      gStyle->SetStatH(0.2);
      gStyle->SetStatW(0.15);
      gStyle->SetStatFontSize(0.05);
      gStyle->SetStatBorderSize(1);
      double bin = i-k+1;
      h1[i]->SetTitle(Form("bin %1.0f",bin));
      h1[i]->GetXaxis()->SetTitle("(N_{true}-N_{unfolded})/#sigma");
      h1[i]->GetYaxis()->SetTitle("Number of toy MC");
    }

    TCanvas *c_toy_Ntrue =  new TCanvas(Form("c_toy_Ntrue_%s",name.Data()),Form("c_toy_Ntrue_%s",name.Data()),800,800);

    if( skip ){
      cout << "2x4" << endl;
      c_toy_Ntrue->Divide(2,4);
    }else{
      cout << "3x3" << endl;
      c_toy_Ntrue->Divide(3,3);
    }

    int k = 0;
    if(skip) k = 1;

    for(int i=k; i<nbins; i++){
      c_toy_Ntrue->cd(i-k+1);
      h2[i]->Fit("gaus");
      g2[i]  = h2[i]->GetFunction("gaus");
      h2[i]->Draw();
      gStyle->SetStatH(0.2);
      gStyle->SetStatW(0.15);
      gStyle->SetStatFontSize(0.05);
      gStyle->SetStatBorderSize(1);
      double bin = i-k+1;
      h2[i]->SetTitle(Form("bin %1.0f",bin));
      h2[i]->GetXaxis()->SetTitle("N_{true}-N_{unfolded}/N_{true}");
      h2[i]->GetYaxis()->SetTitle("Number of toy MC");
    }


    for(int i=k; i<nbins; i++){
      double Mean = h1[i]->GetMean();
      double rms = h1[i]->GetRMS();
      double mean = g1[i]->GetParameter(1);
      double sigma = g1[i]->GetParameter(2);
      double meanerr = g1[i]->GetParError(1);
      double sigmaerr = g1[i]->GetParError(2);
      cout << "$" << hgen->GetBinCenter(i+1)-hgen->GetBinWidth(i+1)/2 << "-" << hgen->GetBinCenter(i+1)+hgen->GetBinWidth(i+1)/2 << "$   ~&~ "
           << setprecision (4) << mean << " $\\pm$ " << sigma 
           << " \\\\" <<  endl;
    }
  }
  //==================================================================================================

  //covariance matrix =============================================================================
  if(print){
    TCanvas *c_errmat = new TCanvas(Form("c_errmat_%s",name.Data()),Form("c_errmat_%s",name.Data()),1);
    //m_unfoldE.Draw("colz");
    TH2D* hErrMat = new TH2D(m_unfoldE);
    hErrMat->GetXaxis()->SetTitle("Generated M_{t#bar{t}} bin number");
    hErrMat->GetYaxis()->SetTitle("Reconstructed M_{t#bar{t}} bin number");
    hErrMat->Draw("Textcolz");

    errorPlots(lumi, h_unfold, name);
  }

  //cout << "covariance matrix= " << endl; 
  //double num = 0;
  //for(i=1; i <= 9; i++){
  //  cout << sqrt(hErrMat->GetBinContent(i,i)) << endl;
  //  num = sqrt(hErrMat->GetBinContent(3,3)) ;
  //}
  //cout << "off covariance= " << endl;
  //double den=0;
  //for(i=1; i <= 9; i++){
  //  cout << sqrt(hErrMat->GetBinContent(3,i)) << endl;
  //  if( sqrt(hErrMat->GetBinContent(3,i))  > 0){
  //    den += sqrt(hErrMat->GetBinContent(3,i));
  //  }
  //}

  //cout << "ratio= " << num/den << endl;

  //================================================================================================== 

  //Printing chi2
  chi2.push_back(unfold->Chi2(hgen, err)); 
  cout << "chi2 : " << unfold->Chi2(hgen, err) << endl;

  //Saving canvas 
  if(print){
    c_response->Print(Form("Unfold_plot/cUF_response_%s.eps",name.Data()));
    c_responseH->Print(Form("Unfold_plot/cUF_responseH_%s.eps",name.Data()));
    c->Print(Form("Unfold_plot/cUF_unfold_%s.eps",name.Data()));
    c_errmat->Print(Form("Unfold_plot/cUF_errmat_%s.eps",name.Data()));

    //c_response->Print(Form("Unfold_plot/cUF_response_%s.png",name.Data()));
    //c_responseH->Print(Form("Unfold_plot/cUF_responseH_%s.png",name.Data()));
    //c->Print(Form("Unfold_plot/cUF_unfold_%s.png",name.Data()));
    //c_errmat->Print(Form("Unfold_plot/cUF_errmat_%s.png",name.Data()));
  }

  if(toy){
      c_toy_sigma->Print(Form("Unfold_plot/cUF_toy_sigma_%s.eps",name.Data()));
      c_toy_Ntrue->Print(Form("Unfold_plot/cUF_toy_Ntrue_%s.eps",name.Data()));

      //c_toy_sigma->Print(Form("Unfold_plot/cUF_toy_sigma_%s.png",name.Data()));
      //c_toy_Ntrue->Print(Form("Unfold_plot/cUF_toy_Ntrue_%s.png",name.Data()));
  }

 
  return h_unfold;
}


void dPlot(TH1F* h_unfold, bool print){
  //log d plot =====================================================================================
  TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  c_d->SetLogy();
  TH1D* h_d = unfold->RooUnfoldSvd::Impl()->GetD();
  h_d->SetTitle(0);
  h_d->Draw("PC");
  h_d->GetYaxis()->SetTitle("log|d_{i}|");
  h_d->GetXaxis()->SetTitle("i");
  if(print){
    c_d->Print(Form("Unfold_plot/cUF_d_%s.eps",name.Data()));
    //c_d->Print(Form("Unfold_plot/cUF_d_%s.png",name.Data()));
  }
}
//err after unfolding =============================================================================
void errorPlotsToCompareWithDESY(double lumi, TH1F* h_unfold, int k, TString name=""){
  TCanvas *c_err = new TCanvas("c_err","c_err",1);

  int nbins = h_unfold->GetNbinsX();

  TGraph *gerr = new TGraph(nbins-1);
  TGraph *gerr_DESY = new TGraph(nbins-1);
  double er[6] = { 0, 0.048, 0.046, 0.058, 0.062, 0.084 }; 
  for(int i=2; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-2, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
      gerr_DESY->SetPoint(i-2, h_unfold->GetBinCenter(i), 100*er[i-1]);
    } else{
      gerr->SetPoint(i-2, h_unfold->GetBinCenter(i), 0);
      gerr_DESY->SetPoint(i-2, h_unfold->GetBinCenter(i), 0);
    }
  }

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.30,0.88,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));

  TCanvas *c_err_all = new TCanvas("c_err_all","c_err_all",1);
  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->SetMaximum(30);
  gerr->SetMinimum(0);
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass (GeV/c^{2})");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  gerr_DESY->SetLineColor(2);
  gerr_DESY->SetMarkerColor(2);
  gerr_DESY->SetMarkerStyle(21);
  gerr_DESY->Draw("LPsame");
  SetLegend(gerr, gerr_DESY, Form("RooUnfold SVD, k=%1.0f",(double) k),"Bin By Bin","LP","LP", 0.2,0.72,0.4,0.94);

  if(true){
    c_err->Print(Form("Unfold_plot/cUF_err_%s.eps",name.Data()));
    //c_err->Print(Form("Unfold_plot/cUF_err_%s.png",name.Data()));
    c_err_all->Print(Form("Unfold_plot/cUF_err_all_%s.eps",name.Data()));
    //c_err_all->Print(Form("Unfold_plot/cUF_err_all_%s.png",name.Data()));
  }

}

void errorPlots(double lumi, TH1F* h_unfold, TString name=""){

  TCanvas *c_err = new TCanvas("c_err","c_err",1);
  int nbins = h_unfold->GetNbinsX();
  TGraph *gerr = new TGraph(nbins-1);

  for(int i=1; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
    } else{
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 0);
    }
  }

  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass (GeV/c^{2})");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.30,0.88,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));

  c_err->Print(Form("Unfold_plot/cUF_err_%s.eps",name.Data()));
  //c_err->Print(Form("Unfold_plot/cUF_err_%s.png",name.Data()));

}

void errorPlots(double lumi, TH1F* h_unfold, int k, TH1F* h_unfoldBinByBin, TString name=""){

  int nbins = h_unfold->GetNbinsX();

  TGraph *gerr = new TGraph(nbins-1);
  TGraph *gerr_perfect = new TGraph(nbins-1);
  TGraph *gerr_binbybin = new TGraph(nbins-1);

  for(int i=2; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-2, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
      gerr_binbybin->SetPoint(i-2, h_unfoldBinByBin->GetBinCenter(i), 100*h_unfoldBinByBin->GetBinError(i)/h_unfoldBinByBin->GetBinContent(i));
      gerr_perfect->SetPoint(i-2, h_unfold->GetBinCenter(i), 100*sqrt(h_unfold->GetBinContent(i))/h_unfold->GetBinContent(i));
    } else{      
      gerr->SetPoint(i-2, h_unfold->GetBinCenter(i), 0);
      gerr_binbybin->SetPoint(i-2, h_unfoldBinByBin->GetBinCenter(i), 0);
      gerr_perfect->SetPoint(i-2, h_unfold->GetBinCenter(i), 0);
    }
  }

  //put together errors ============
  //TCanvas *c_err_all = new TCanvas(Form("c_err_all_%s",name.Data()),Form("c_err_all_%s",name.Data()),1);
  TCanvas *c_err_all = new TCanvas("c_err_all","c_err_all",1);
  gerr->SetMaximum(30);
  gerr->SetMinimum(0);
  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass (GeV/c^{2})");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  gerr->Draw("ALP");
  gerr_perfect->SetLineColor(2);
  gerr_perfect->SetMarkerColor(2);
  gerr_perfect->SetMarkerStyle(24);
  //gerr_perfect->Draw("LPsame");
  gerr_binbybin->SetLineColor(2);
  gerr_binbybin->SetMarkerColor(2);
  gerr_binbybin->SetMarkerStyle(21);
  gerr_binbybin->Draw("LPsame");
  //SetLegend(gerr, gerr_binbybin, gerr_perfect, Form("RooUnfold SVD, k=%1.0f",(double) k),"RooUnfold Bin By Bin", "perfect,  #sqrt{N_{unfolded}}", "LP","LP","LP", 0.2,0.72,0.4,0.94);
  SetLegend(gerr, gerr_binbybin, Form("RooUnfold SVD, k=%1.0f",(double) k),"Bin By Bin","LP","LP", 0.2,0.72,0.4,0.94);

  if(true){
    c_err_all->Print(Form("Unfold_plot/cUF_err_all_%s.eps",name.Data()));
    //c_err_all->Print(Form("Unfold_plot/cUF_err_all_%s.png",name.Data()));
  }

}


TGraphAsymmErrors* FinalPlot(TH1F* h_unfold, TH1F* hgen, TH1F* accept, TH1D* hTr1, double lumi, TString hName, TString cName, double min, double max, bool norm=true, bool log=true, bool curve=false, bool print){

  int nbins = h_unfold->GetNbinsX();

  TCanvas *c_dsigma = new TCanvas(Form("c_%s_dsigma_%s",hName.Data(), cName.Data()),Form("c_%s_dsigma_%s",hName.Data(), cName.Data()));
  TGaxis::SetMaxDigits(4);

  if(log) c_dsigma->SetLogy();

  TH1F* hSigmaData = getMeasuredCrossSection(h_unfold,accept,lumi,norm, true, "unfolded");
  TH1F* hSigmaTruth = getMeasuredCrossSection(hgen,accept,lumi,norm, true, "truth");
  //TH1F* hSigmaTruth = getTruthCrossSection(hgen, hTr1, lumi, norm, false, 1, true);
  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"Unfolded t#bar{t} invariant mass (GeV/c^{2})","");

  if(norm){
    hSigmaTruth->GetYaxis()->SetTitle("1/#sigma_{t#bar{t}} d#sigma/dM_{t#bar{t}} (1/GeV/c^{2})");
  }else{
    hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}} (pb/GeV/c^{2})");
  }

  hSigmaTruth->Draw("HIST");

  //MC band
  TGraphAsymmErrors* dsigmaTruth = getGraphAsymmErrors(hSigmaTruth);
  dsigmaTruth->SetFillColor(30);
  dsigmaTruth->SetFillStyle(3001);
  dsigmaTruth->SetLineColor(0);
  dsigmaTruth->Draw("2same");
  hSigmaData->Draw("Psame");

  SetLabel(0.47,0.88, lumi);
  SetLegend(hSigmaTruth, hSigmaData, "MadGraph", "Unfolded data", "L", "P", 0.58,0.64,0.80,0.8);
  Print(c_dsigma, "Unfold_plot", hName.Data(), cName.Data(), print);

  TGraphAsymmErrors* dsigmaData = getGraphAsymmErrors(hSigmaData);
  return dsigmaData;
}

void FinalPlot(TH1F* h_unfold, TH1F* hgen, TH1F* accept, TH1D* hTr1, TH1D* hTr2, TH1D* hTr3, double lumi, TString hName, TString cName, double min, double max, bool norm=true, bool log=true, bool curve=false, bool print = false, bool printX = false, bool HBBstyle = false, bool band = false, TH1D* hTr2_up ="", TH1D* hTr2_dw= ""){

  int nbins = h_unfold->GetNbinsX();
 
  TH1F* dsigmaDataHisto = getMeasuredCrossSection(h_unfold,accept,lumi,norm, printX, "unfolded");
  TH1F* dsigmaDataHistoOnlyWithStat = getMeasuredCrossSection(h_unfold,accept,lumi,norm, printX, "unfolded", false); //set false for systematic uncert.

  TGraphAsymmErrors* dsigmaTruth = new TGraphAsymmErrors();
  TGraphAsymmErrors* dsigmaData = getGraphAsymmErrors(dsigmaDataHisto);
  TGraphAsymmErrors* dsigmaDataOnlyWithStat = getGraphAsymmErrors(dsigmaDataHistoOnlyWithStat);

  //TGraphAsymmErrors* DESY = DESYPlot(accept); 
  TH1F* hSigmaTruth = getTruthCrossSection(hgen, hTr1, lumi, norm, curve,50);
  TH1F* hSigmaTruth2 = getTruthCrossSection(hgen, hTr2, lumi, norm, curve,50);
  TH1F* hSigmaTruth3 = getTruthCrossSection(hgen, hTr3, lumi, norm, curve,50);
  //getUncertainty(dsigmaData, hSigmaTruth2);
  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth2, 2,4,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth3, 2,3,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");

  TCanvas *c_dsigma = new TCanvas(Form("c_%s_dsigma_%s",hName.Data(), cName.Data()),Form("c_%s_dsigma_%s",hName.Data(), cName.Data()));
  TGaxis::SetMaxDigits(4);
  if(log) c_dsigma->SetLogy();

  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"Unfolded t#bar{t} invariant mass (GeV/c^{2})","");
  if(norm){
    hSigmaTruth->GetYaxis()->SetTitle("1/#sigma d#sigma/dM_{t#bar{t}} (1/GeV/c^{2})");
  }else{
    hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}} (pb/GeV/c^{2})");
  }

  hSigmaTruth->Draw();
  hSigmaTruth2->Draw("same");
  hSigmaTruth3->Draw("same");
  dsigmaDataHisto->Draw("Psame");

  SetLabel(0.47,0.88, lumi);
  SetLegend(dsigmaData, hSigmaTruth, hSigmaTruth2, hSigmaTruth3, "Unfolded data", "MadGraph", "MC@NLO", "POWHEG", "P","L","L", "L", 0.58,0.64,0.80,0.8);

  //print
  Print(c_dsigma, "Unfold_plot", hName.Data(), cName.Data(), print);
}

void TOP11013Plot(TH1F* h_unfold, TH1F* hgen, TH1F* accept, TH1D* hTr1, TH1D* hTr2, TH1D* hTr3, double lumi, TString hName, TString cName, double min, double max, bool norm=true, bool log=true, bool curve=false, bool print = false, bool printX = false, bool HBBstyle = false, bool band = false, TH1D* hTr2_up ="", TH1D* hTr2_dw= ""){

  int nbins = h_unfold->GetNbinsX();

  TH1F* dsigmaDataHisto = getMeasuredCrossSection(h_unfold,accept,lumi,norm, printX, "unfolded");
  TH1F* dsigmaDataHistoOnlyWithStat = getMeasuredCrossSection(h_unfold,accept,lumi,norm, printX, "unfolded", false); //set false for systematic uncert.

  TGraphAsymmErrors* dsigmaTruth = new TGraphAsymmErrors();
  TGraphAsymmErrors* dsigmaData = getGraphAsymmErrors(dsigmaDataHisto);
  TGraphAsymmErrors* dsigmaDataOnlyWithStat = getGraphAsymmErrors(dsigmaDataHistoOnlyWithStat);

  TH1F* hSigmaTruth = getTruthCrossSection(hgen, hTr1, lumi, norm, curve,50);
  TH1F* hSigmaTruthHisto = getTruthCrossSection(hgen, hTr1, lumi, norm, false, 1, printX);

  TCanvas *c_dsigma = new TCanvas(Form("c_%s_dsigma_%s",hName.Data(), cName.Data()),Form("c_%s_dsigma_%s",hName.Data(), cName.Data()));
  TGaxis::SetMaxDigits(4);
  if(log) c_dsigma->SetLogy();

  TH1F* fSigmaTruth = getFitHistogram(hTr1, "madgraph");
  TH1F* fSigmaTruth2 = getFitHistogram(hTr2, "mcatnlo");
  TH1F* fSigmaTruth3 = getFitHistogram(hTr3, "powheg");

  SetHistoStyle(fSigmaTruth, 2,kRed+1,1,0,0,0,min,max,"","");
  SetHistoStyle(fSigmaTruth2, 2,kAzure,1,0,0,0,min,max,"","");
  SetHistoStyle(fSigmaTruth3, 2,kGreen+1,1,0,0,0,min,max,"","");

  TH1F* fSigmaTruth2_up = getFitHistogram(hTr2_up, "mcatnlo");
  TH1F* fSigmaTruth2_dw = getFitHistogram(hTr2_dw, "mcatnlo");
  dsigmaTruth = getGraphAsymmErrors( fSigmaTruth2, true, fSigmaTruth2_up, fSigmaTruth2_dw);

  SetHistoStyle_TOP11013(hSigmaTruthHisto, 2,kRed+1,1,1.2,0,20,min,max,"m_{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]","#frac{1}{#sigma} #frac{d#sigma}{dm_{t#bar{t}}} #left[#left(#frac{GeV}{c^{2}}#right)^{-1}#right]");

  hSigmaTruthHisto->Draw();
  dsigmaTruth->SetLineWidth(2);
  dsigmaTruth->SetLineStyle(1);
  dsigmaTruth->SetLineColor(kAzure);
  dsigmaTruth->SetFillColor(kGray);
  dsigmaTruth->Draw("e3");

  hSigmaTruthHisto->Draw("same");
  fSigmaTruth->Draw("hist c same");
  fSigmaTruth2->Draw("hist c same");
  fSigmaTruth3->Draw("hist c same");

  TGraphAsymmErrors* dsigmaDataCentered = BinCenterCorrection(dsigmaData, hSigmaTruthHisto, hSigmaTruth);
  TGraphAsymmErrors* dsigmaDataCenteredOnlyWithStats = BinCenterCorrection(dsigmaDataOnlyWithStat, hSigmaTruthHisto, hSigmaTruth);
  dsigmaDataCentered->Draw("ZPsame");
  dsigmaDataCenteredOnlyWithStats->Draw("||");

  bool isPreliminary = true;
  DrawCMSLabels(isPreliminary, 1143);
  DrawDecayChLabel("Dilepton Combined");

  TLegend *l= new TLegend();
  l->AddEntry(dsigmaData, "Data" ,"P");
  l->AddEntry(fSigmaTruth, "MadGraph" ,"L");
  l->AddEntry(dsigmaTruth, "MC@NLO" ,"FL");
  l->AddEntry(fSigmaTruth3, "POWHEG" ,"L");
  SetLegendStyle(l,true);
  l->Draw("same");

  //print
  Print(c_dsigma, "Unfold_plot", hName.Data(), cName.Data(), print);
}


TH1* getMeasuredCrossSection( TH1F* h_unfold, TH1F* accept, double lumi, bool norm=false, bool print = false, TString name="", bool sysuncert = true){

  double syst[] = { 0, 9.35, 15.08, 17.96, 23.04, 19.02, 17.14, 17.23, 31.38};

  int nbins = h_unfold->GetNbinsX();
  TH1* dsigma = (TH1F*)h_unfold->Clone("disgma");
  dsigma->Reset();
 
  double totalN = 0;
  double totalS = 0;
  for(int i=1; i <=  nbins; i++){
    double acceptance = accept->GetBinContent(i);
    double unfolded = h_unfold->GetBinContent(i);
    double width = hgen->GetBinWidth(i);
    double sigma = 0;
    if( acceptance != 0) sigma = unfolded/( acceptance * lumi * width ) ;
    totalN += unfolded;
    totalS += sigma*width;
  } 

  if(print) cout << "========= Measured Cross section: sigma (fb) for  " << name.Data() << " ====================== " << endl;
  for(int i=1; i <=  nbins; i++){
    double bincenter = accept->GetBinCenter(i);
    double acceptance = accept->GetBinContent(i);
    double unfolded = h_unfold->GetBinContent(i);
    double abserr = h_unfold->GetBinError(i);
    double width = hgen->GetBinWidth(i);

    double sigma = 0;
    double sigmaErr = 0;
    double sigmaSystErr = 0;

    if( acceptance != 0) {
      if(norm) { 
        sigma = unfolded/( acceptance * lumi * width )/totalS ;
      }else{
        sigma = unfolded/( acceptance * lumi * width ) ;
      }
    }

    if( unfolded != 0) {
      sigmaErr = sigma*(abserr/unfolded);
      if( sysuncert ) sigmaSystErr = sigma*syst[i-1]/100.0;
    }

    double totalE = sqrt(sigmaErr*sigmaErr + sigmaSystErr*sigmaSystErr);
    dsigma->SetBinContent(i,sigma);
    dsigma->SetBinError(i,totalE);
    if(print){
      if(name == "truth"){
        cout << "$" << bincenter-width/2 << "-" << bincenter+width/2 << "$   ~&~ "
           << setprecision (4) << unfolded << " $\\pm$ " << abserr << " ~&~ "
           << sigma*1000 << " $\\pm$ " << sigmaErr*1000  
           << " \\\\" <<  endl;
      }else{
        cout << "$" << bincenter-width/2 << "-" << bincenter+width/2 << "$   ~&~ "
           << setprecision (4) << unfolded << " $\\pm$ " << abserr << " ~&~ "
           << sigma*1000 << " $\\pm$ " << sigmaErr*1000 << "(stat.) $\\pm$ " << sigmaSystErr*1000 << "(syst.) $\\pm$ " << totalE*1000 << "(total)"
           << " \\\\" <<  endl;
      }
    }
  }
 
  if(print) cout << "========  SUMMARY : total " << name.Data() << " events= " << totalN << " /  total cross section= " << totalS << " (pb) =========" << endl; 
  return dsigma;

}

TH1* getTruthCrossSection(TH1F* hgen, TH1D* htruth, double lumi, bool norm, bool curve=false, int w=1, bool print = false){

  TH1* dsigma = (TH1F*)hgen->Clone("disgma");
  dsigma->Reset();
  int nbins = hgen->GetNbinsX();
  double totalN = 0;
  double totalS = 0;
  for(int i=1; i <=  nbins; i++){
    double width = hgen->GetBinWidth(i);
    double start = hgen->GetBinCenter(i)-width/2 + 1;
    double end = hgen->GetBinCenter(i)+width/2;
    double unfolded = hgen->GetBinContent(i);
    double truth = htruth->Integral(start, end);
    double sigma = truth/( lumi * width );

    totalN += unfolded;
    totalS += sigma*width;
  }

  if(curve){
    double bins = 1400/(double) w;
    TH1* truthRe = (TH1F*)htruth->Clone("truthRe");
    truthRe->Rebin(w);

    TH1* hdSigma = (TH1F*)truthRe->Clone("hdSigma");
    hdSigma->Reset();

    for(int i=1; i <= bins ; i++){
      double num = truthRe->GetBinContent(i);
      if(norm){
        hdSigma->SetBinContent(i, num/(lumi*w)/totalS);
      }else{
        hdSigma->SetBinContent(i, num/(lumi*w));
      }
    }

    return hdSigma;
  }

  if(print) cout << "========= Truth Cross section: sigma (fb)====================== " << endl;
  for(int i=1; i <=  nbins; i++){
    double width = hgen->GetBinWidth(i);
    double bincenter = hgen->GetBinCenter(i);
    double start = bincenter-width/2 + 1;
    double end = bincenter+width/2;
    double unfolded = hgen->GetBinContent(i);
    double abserr = hgen->GetBinError(i);
    double truth = htruth->Integral(start, end);
    double sigma = 0;
    double sigmaErr = 0;
    if(norm) {
      sigma = truth/( lumi * width )/totalS;
    }else{
      sigma = truth/( lumi * width );
    }
    if(unfolded) sigmaErr = sigma*(abserr/unfolded);
    dsigma->SetBinContent(i, sigma); 

    if(print){
      cout << "$" << bincenter-width/2 << "-" << bincenter+width/2 << "$   ~&~ "
         << setprecision (4) << unfolded << " $\\pm$ " << abserr << " ~&~ "
         << sigma*1000 << " $\\pm$ " << sigmaErr*1000 << " "
         << " \\\\" <<  endl;
    }
  } 
 
  if(print) cout << "========  SUMMARY : total truth events= " << totalN << " /  total cross section= " << totalS << " (pb) =========" << endl;
  return dsigma;
}


TGraphAsymmErrors* printFinal( int nbins, TH1F* hgen, TH1F* accept, double lumi, bool truth, bool norm){

  double syst[] = { 0, 9.35, 15.08, 17.96, 23.04, 19.02, 17.14, 17.23, 31.38};

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;
  double totalN = 0;
  TH1F* sigmaHistogram = getMeasuredCrossSection(hgen,accept,lumi,norm);

  for(int i=1; i <=  nbins; i++){
    double unfolded = hgen->GetBinContent(i);
    totalN += unfolded;
    double err = hgen->GetBinError(i);
    double rel_err = 0;
    if(unfolded != 0) rel_err = err/unfolded;
    double width = sigmaHistogram->GetBinWidth(i);
    double x = sigmaHistogram->GetBinCenter(i);
    double sigma = sigmaHistogram->GetBinContent(i);
    double sigmaErr = sigma*rel_err;
    double sigmaSystErr = 0;
    if(!truth) sigmaSystErr = sigma*syst[i-1]/100.0;
    double totalE = sqrt(sigmaErr*sigmaErr + sigmaSystErr*sigmaSystErr);

    cout << "$" << hgen->GetBinCenter(i)-hgen->GetBinWidth(i)/2 << "-" << hgen->GetBinCenter(i)+hgen->GetBinWidth(i)/2 << "$   ~&~ "
       << setprecision (4) << hgen->GetBinContent(i) << " $\\pm$ " << err << " ~&~ "
       << sigma*1000 << " $\\pm$ " << sigmaErr*1000 << "(stat.) $\\pm$ " << sigmaSystErr*1000 << "(syst.) $\\pm$ " << totalE*1000 << "(total)"
       << " \\\\" <<  endl;
  }
  cout << "total unfolded= " << totalN << endl;

  return dsigma;
}

TGraphAsymmErrors* getGraphAsymmErrors( TH1F* hgen, bool band = false, TH1F* hgen_up = "", TH1F* hgen_dw = "" ){

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;
  int nbins = hgen->GetNbinsX();
  for(int i=1; i <=  nbins; i++){
    double x = hgen->GetBinCenter(i);
    double sigma = hgen->GetBinContent(i);
    double sigma_up = 0; 
    double sigma_dw = 0; 
    
    if(band){
      sigma_up = hgen_up->GetBinContent(i) - sigma;
      sigma_dw = sigma - hgen_dw->GetBinContent(i);
    }else{
      sigma_up = hgen->GetBinError(i);
      sigma_dw = sigma_up;
    }

    dsigma->SetPointEYhigh(i-1, sigma_up);
    dsigma->SetPointEYlow(i-1, sigma_dw);
    dsigma->SetPoint(i-1, x, sigma );
  }

  return dsigma;
}

TH1* getTruthDist(TH1F* hgen){

  int nbins = hgen->GetNbinsX();

  TH1* truth = (TH1F*)hgen->Clone("disgma");
  truth->Reset();

  for(int i=1; i <=  nbins; i++){
    double unfolded = hgen->GetBinContent(i);
    truth->SetBinContent(i, unfolded);
  }

  return truth;
}

TGraphAsymmErrors* BinCenterCorrection( TGraphAsymmErrors* data, TH1* gen_histo, TH1* gen_curve = ""){

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;
  int nbins = gen_histo->GetNbinsX();

  double centerpoints[] = { 172.5, 363, 427, 472, 522, 575, 646, 741, 975};

  for(int i=1; i <=  nbins; i++){
    double x;
    double sigma;
    data->GetPoint(i-1,x,sigma);
    double ave = gen_histo->GetBinContent(i);
    double width = gen_histo->GetBinWidth(i);
    double bincenter = x;
    double curvesigma = gen_curve->GetBinContent(i);

    if( ave != 0 || ave != curvesigma ){
      double proximity = 999999;
      double lowedge = x-width/2;
      double highedge = x+width/2;
      int start = (int) lowedge/gen_curve->GetBinWidth(i) + 1;
      int end = (int) highedge/gen_curve->GetBinWidth(i);
      
      bincenter = centerpoints[i-1];
      //for(int k=start ; k<= end; k++){
      //  double center = gen_curve->GetBinCenter(k);
      //  double ypoint = gen_curve->GetBinContent(k);

      //  if( fabs( ypoint - ave) < proximity){
      //    bincenter = center;
      //    proximity = fabs(ypoint - ave);
      //  }
      //}
    }

    double ErrYhigh = data->GetErrorYhigh(i-1);
    double ErrYlow = data->GetErrorYlow(i-1);
    dsigma->SetPoint(i-1, bincenter, sigma );
    dsigma->SetPointEYhigh(i-1, ErrYhigh);
    dsigma->SetPointEYlow(i-1, ErrYlow);
    //dsigma->SetPointEXhigh(i-1, width/2 - (bincenter-x));
    //dsigma->SetPointEXlow(i-1, width/2 + (bincenter-x));
    cout << "$" << gen_histo->GetBinCenter(i)-width/2 << "-" << gen_histo->GetBinCenter(i)+width/2 << "$   ~&~ "
       << bincenter << " ~&~ " << sigma << " $\\pm$ " << ErrYhigh << "(" << ErrYlow << ")" << " \\\\" <<  endl;
  }

  return dsigma;
}

void getUncertainty(TGraphAsymmErrors* de, TGraphAsymmErrors* up, TGraphAsymmErrors* dw){

  for(int i=0; i <9; i++){
    double de_x;
    double de_y;
    double up_x;
    double up_y;
    double dw_x;
    double dw_y;
    de->GetPoint(i, de_x, de_y);
    up->GetPoint(i, up_x, up_y);
    dw->GetPoint(i, dw_x, dw_y);
    if( de_y != 0){
      cout << "Bin " << i+1 << " : " << " + " << fabs(up_y - de_y)/ de_y << " - " << fabs(dw_y - de_y)/ de_y << endl; 
    }
  }

}

void getUncertainty(TGraphAsymmErrors* de, TH1* up){

  for(int i=0; i <9; i++){
    double de_x;
    double de_y;
    double up_y = up->GetBinContent(i+1);
    de->GetPoint(i, de_x, de_y);
    if( de_y != 0){
      cout << "Bin " << i+1 << " : " << fabs(up_y - de_y)/ de_y << endl;
    }
  }

}

TF1 * getFitFunction(TH1D* h, int color, int style, int width){
  TH1F *tmp = (TH1F*)h->Clone("tmp");
  TF1* function=new TF1("function","TMath::LogNormal(x,[0],[1],[2])",0, 2000);
  double scale = tmp->Integral();
  tmp->Scale(1.0/scale);
  function->SetParLimits(0,0.65,69);
  function->SetParLimits(1,250,320);
  function->SetParLimits(2,90,300);
  tmp->Fit(function, "LR","same",0, 2000);
  function->SetLineColor(color);
  function->SetLineStyle(style);
  function->SetLineWidth(width);

  return function;
}

TH1F * getFitHistogram(TH1D* h, string model){

  TH1F* tmp=(TH1F*) h->Clone();
  double scale = tmp->Integral();
  tmp->Scale(1.0/scale);

  TH1F* result=(TH1F*) h->Clone();
  result->Reset();

  double fitLowEdge=0;
  double fitHighEdge=0;
  TString def="";
  double a=0.;
  double b=0.;
  double c=0.;
  // define fit function B
  double fitLowEdgeB=0;
  double fitHighEdgeB=0;
  TString defB="";
  double aB=0.;
  double bB=0.;
  double cB=0.;
  TString addOptB="";
  // define fit function C
  double fitLowEdgeC=0;
  double fitHighEdgeC=0;
  TString defC="";
  double aC=0.;
  double bC=0.;
  double cC=0.;

  if(model=="mcatnlo"){
    //tail:
    fitLowEdge=440.;
    fitHighEdge=1400.;
    def="[0]*exp([1]*x)+[2]";
    a=0.11;
    b=-0.0074;
    c=0.00001;
    // start:
    fitLowEdgeB=345.;
    fitHighEdgeB=440.;
    defB="TMath::GammaDist(x,[0],[1],[2])";
    aB=1.53;
    bB=345.;
    cB=96.2;
    // very early start:
    fitLowEdgeC=300.;
    fitHighEdgeC=345.;
    defC="[0]*exp([1]*x)+[2]";
    aC=0.00000373757;
    bC=0.0125775;
    cC=-0.000194989;
  }
  else if(model=="madgraph"){
    //tail:
    fitLowEdge=440.;
    fitHighEdge=1400.;
    def="[0]*exp([1]*x)+[2]";
    a=28165.;
    b=-0.00756;
    c=2.77;
    // start:
    fitLowEdgeB=340.;
    fitHighEdgeB=440.;
    defB="[3]*TMath::GammaDist(x,[0],[1],[2])";
    aB=1.56;
    bB=344.8;
    cB=80.8;
  }
  else if(model=="powheg"){
    fitLowEdge=440.;
    fitHighEdge=1400.;
    def="[0]*exp([1]*x)+[2]";
    a=40556.;
    b=-0.007;
    c=3.1;
    // start:
    fitLowEdgeB=345.;
    fitHighEdgeB=440.;
    defB="[3]*TMath::GammaDist(x,[0],[1],[2])";
    aB=1.58;
    bB=344.;
    cB=86.6;
    addOptB="LL";
    // very early start:
    fitLowEdgeC=295.;
    fitHighEdgeC=345.;
    defC="[0]*exp([1]*x)+[2]";
    aC=0.000000000530501;
    bC=0.075;
    cC=3.81;
  }

  TF1* function=new TF1("function",def,fitLowEdge,fitHighEdge);
  function->SetParLimits(0, 0.0, 0.1442);
  function->SetParLimits(1, -0.01, 0.00);
  function->SetParLimits(2, 0.0, 0.0000036);

  //FIXME: it does not work
  //function->SetParameter(0,a);
  //function->SetParLimits(1,0.85*b,1.15*b);
  //function->SetParameter(2,c);

  TF1* functionB=new TF1("functionB",defB,fitLowEdgeB, fitHighEdgeB);
  functionB->SetParameter(0,aB);
  functionB->SetParameter(1,bB);
  if(bB<0.) functionB->SetParLimits(1,1.15*bB,0.85*bB);
  if(bB>0.) functionB->SetParLimits(1,0.85*bB,1.15*bB);
  functionB->SetParameter(2,cB);

  TF1* functionC=new TF1("functionC",defC, fitLowEdgeC, fitHighEdgeC);
  functionC->SetParameter(0,aC);
  functionC->SetParameter(1,bC);
  functionC->SetParLimits(1,0.85*bC,1.15*bC);
  functionC->SetParameter(2,cC);

  tmp->Fit(function,"R","same", fitLowEdge, fitHighEdge);
  result->Add(function);
  tmp->Fit(functionB,"R+","same", fitLowEdgeB, fitHighEdgeB);
  result->Add(functionB);

  if( model != "madgraph" ){
    tmp->Fit(functionC,"R+","same", fitLowEdgeC, fitHighEdgeC);
    result->Add(functionC);
  }

  return result;
}


TGraphAsymmErrors* DESYPlot(TH1F* accept){

  TGraphAsymmErrors* DESY = new TGraphAsymmErrors();
  DESY->SetPoint(0,accept->GetBinCenter(1),0);
  DESY->SetPoint(1,accept->GetBinCenter(2),0.00528);
  DESY->SetPoint(2,accept->GetBinCenter(3),0.00416);
  DESY->SetPoint(3,accept->GetBinCenter(4),0.00255);
  DESY->SetPoint(4,accept->GetBinCenter(5),0.00098);
  DESY->SetPoint(5,accept->GetBinCenter(6),0.00020);
  DESY->SetPointEYhigh(0,0);
  DESY->SetPointEYhigh(1,0.00528*0.048);
  DESY->SetPointEYhigh(2,0.00416*0.046);
  DESY->SetPointEYhigh(3,0.00255*0.058);
  DESY->SetPointEYhigh(4,0.00098*0.062);
  DESY->SetPointEYhigh(5,0.00020*0.084);
  DESY->SetPointEYlow(0,0);
  DESY->SetPointEYlow(1,0.00528*0.048);
  DESY->SetPointEYlow(2,0.00416*0.046);
  DESY->SetPointEYlow(3,0.00255*0.058);
  DESY->SetPointEYlow(4,0.00098*0.062);
  DESY->SetPointEYlow(5,0.00020*0.084);
  DESY->SetMarkerColor(4);

  return DESY;

}
