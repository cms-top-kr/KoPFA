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

void unfoldingPlot(TH1* h_gen, TH1* h_rec, TH2* m, TH1* h_mea, TH1* h_genTTbar, TH1F* accept, double scale_ttbar, TString name, double lumi, int k, RooUnfold::ErrorTreatment & err, bool print, bool pseudo){

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
  hgen->Scale(scale_ttbar);
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
  unfold->RooUnfoldSvd::SetNtoysSVD(1000);
  cout << "n. of toys= " << unfold->RooUnfoldSvd::GetNtoysSVD() << endl;
  TH1F* h_unfold = (TH1F*) unfold->Hreco(err);
  //TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kCovToy);
 
  int nbins = h_unfold->GetNbinsX();
 
  TMatrixD m_unfoldE = unfold->Ereco();
  //TVectorD v_unfoldE = unfold->ErecoV(RooUnfold::kCovariance);

  hgen->Draw();
  hgen->SetFillColor(6);
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
  l_unfold->AddEntry(hgen,"MC Truth t#bar{t}","F");
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
  TCanvas *c_toy =  new TCanvas(Form("c_toy_%s",name.Data()),Form("c_toy_%s",name.Data()),1);
  c_toy->Divide(3,3);
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1 *h[9];
  TF1 *g[9];
  for(int i=0; i <9; i++){
     double center = hgen->GetBinContent(i+1);
     h[i] = new TH1F(Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), Form("h%1.0f_%1.0f_%s",detBins[i],detBins[i+1],name.Data()), 200, (center+10)-100,(center+10)+100);
  } 

  for(int i=0 ; i <10000 ; i++){
    TH1* unfoldedToy =  unfold->Runtoy();
    for(int j=0; j <9; j++){
      double rec_ = RooUnfoldResponse::GetBinContent(unfoldedToy,j+1,true);
      h[j]->Fill(rec_);
    }
  }
  
  for(int i=0; i<9; i++){
    c_toy->cd(i+1);
    h[i]->Fit("gaus");
    g[i]  = h[i]->GetFunction("gaus");
    h[i]->Draw();
    gStyle->SetStatH(0.4);
    gStyle->SetStatW(0.2);
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatBorderSize(1);
    h[i]->SetTitle(Form("%1.0f-%1.0f GeV",detBins[i],detBins[i+1]));
    h[i]->GetXaxis()->SetTitle("Unfolded number of events");
    h[i]->GetYaxis()->SetTitle("Number of toy MC");
  }

  for(int i=0; i<9; i++){
    double Mean = h[i]->GetMean();
    double rms = h[i]->GetRMS();
    double mean = g[i]->GetParameter(1);
    double sigma = g[i]->GetParameter(2);
    double mass = (detBins[i+1] + detBins[i])/2;
    double meanerr = g[i]->GetParError(1);
    double sigmaerr = g[i]->GetParError(2);
    cout <<  "point= " << mass <<  " MEAN= " <<  mean << " RMS= " << rms << " mean= " << mean << "(error= " << meanerr << ")" << " sigma= " << sigma << "(error= " << sigmaerr << ") " <<"\n";
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

  cout << "Unfolded: evt number / sigma (fb)" << endl;  
  TGraphAsymmErrors* dsigmaData = printFinal(nbins, h_unfold, accept, lumi, 1, false);
  cout << "Truth: evt number / sigma (fb)" << endl;
  TGraphAsymmErrors* dsigmaTruth = printFinal(nbins, hgen, accept, lumi, scale_ttbar, true);
  TH1* hSigmaTruth = getSigmaTruth(hgen, accept, lumi);
 
  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  label->DrawLatex(0.30,0.88,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));

  //====================================================================================================

  //err before unfolding ===============================================================================
  TCanvas *c_meaerr = new TCanvas(Form("c_meaerr_%s",name.Data()),Form("c_meaerr_%s",name.Data()),1);
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
  TCanvas *c_dsigma = new TCanvas(Form("c_dsigma_%s",name.Data()),Form("c_dsigma_%s",name.Data()));
  c_dsigma->SetLogy();
  hSigmaTruth->SetLineWidth(1);
  hSigmaTruth->SetLineStyle(1);
  hSigmaTruth->SetTitle(0);
  hSigmaTruth->Draw();
  hSigmaTruth->SetMaximum(3000);
  hSigmaTruth->GetXaxis()->SetTitle("Unfolded t#bar{t} invariant mass (GeV/c^{2})");
  hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}}");
  dsigmaData->Draw("Psame");
  dsigmaTruth->SetFillColor(30);
  dsigmaTruth->SetFillStyle(3001);
  dsigmaTruth->SetLineColor(0);
  dsigmaTruth->Draw("2same");

  TLegend *l_dsigma= new TLegend(0.58,0.68,0.80,0.8);
  l_dsigma->AddEntry(hSigmaTruth, "SM Expectation","L");
  l_dsigma->AddEntry(dsigmaTruth, "SM Uncertainties","F");
  l_dsigma->AddEntry(dsigmaData, "Unfolded Data","P");
  l_dsigma->SetTextSize(0.04);
  l_dsigma->SetFillColor(0);
  l_dsigma->SetLineColor(0);
  l_dsigma->Draw();

  label->DrawLatex(0.47,0.88,Form("%1.0f pb^{-1} at #sqrt{s} = 7 TeV",lumi));
  //======================================================================================================================  

  cout << "chi2(kErrors) : " << unfold->Chi2(hgen, RooUnfold::kErrors) << endl;
  cout << "chi2(kCovariance) : " << unfold->Chi2(hgen, RooUnfold::kCovariance) << endl;

  if(print){
    c_response->Print(Form("cUF_response_%s.eps",name.Data()));
    c->Print(Form("cUF_unfold_%s.eps",name.Data()));
    c_err->Print(Form("cUF_err_%s.eps",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.eps",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.eps",name.Data()));
    c_dsigma->Print(Form("cUF_dsigma_%s.eps",name.Data()));
    c_d->Print(Form("cUF_d_%s.eps",name.Data()));
    c_toy->Print(Form("cUF_toy_%s.eps",name.Data()));

    c_response->Print(Form("cUF_response_%s.png",name.Data()));
    c->Print(Form("cUF_unfold_%s.png",name.Data()));
    c_err->Print(Form("cUF_err_%s.png",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.png",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.png",name.Data()));
    c_dsigma->Print(Form("cUF_dsigma_%s.png",name.Data()));
    c_d->Print(Form("cUF_d_%s.png",name.Data()));
    c_toy->Print(Form("cUF_toy_%s.png",name.Data()));

  }
}

void massPlot(TH1* hgen, TH1* hrec, TH1* hmea, const double scale_ttbar){

  TH1F *h1 = (TH1F*)hgen->Clone("h1");
  TH1F *h2 = (TH1F*)hrec->Clone("h2");
  TH1F *h3 = (TH1F*)hmea->Clone("h3");

  TCanvas *c = new TCanvas("c","c", 1);
  c->SetLogy();
  h1->SetTitle("");
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetMarkerSize(1.0);
  h3->SetMarkerStyle(20);

  h1->Scale(scale_ttbar);
  h2->Scale(scale_ttbar);

  //h1->SetMaximum(1000);
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);

  int nbins = h3->GetNbinsX();
  for(int i=1; i <=  nbins; i++){
    std::cout << "[" << h3->GetBinCenter(i)-h3->GetBinWidth(i)/2 << "," << h3->GetBinCenter(i)+h3->GetBinWidth(i)/2 << "]" ;
    std::cout << " : " << h3->GetBinError(i) << "/" <<h3->GetBinContent(i) << std::endl;
  }


  TLegend *l= new TLegend(0.60,0.60,0.8,0.8);
  l->AddEntry(h1,"gen mass","l");
  l->AddEntry(h2,"reco mass","l");
  l->AddEntry(h3,"data mass","p");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
 
  c->Print("c_massPlot.eps");

}

TGraphAsymmErrors* printFinal( int nbins, TH1F* hgen, TH1F* accept, double lumi, double scale, bool truth ){

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;

  for(int i=1; i <=  nbins; i++){
    double x;
    double y;
    //accept->GetPoint(i-1,x,y);
      
    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i); 
 
    double unfolded = hgen->GetBinContent(i);
    double err = 0;
    if(truth) err = sqrt(hgen->GetBinContent(i))*sqrt(scale) ;
    else err = hgen->GetBinError(i);

    double sigma = 1000*unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    double sigmaErr = sigma*err/unfolded;

    cout << "$" << hgen->GetBinCenter(i)-hgen->GetBinWidth(i)/2 << "-" << hgen->GetBinCenter(i)+hgen->GetBinWidth(i)/2 << "$   ~&~ "
         << setprecision (4) << hgen->GetBinContent(i) << " $\\pm$ " << err << " ~&~ "
         << sigma << " $\\pm$ " << sigmaErr  
         << " \\\\" <<  endl;

    double width = hgen->GetBinWidth(i);

    dsigma->SetPoint(i-1, x, sigma );
    dsigma->SetPointEXhigh(i-1, width/2);
    dsigma->SetPointEXlow(i-1, width/2);
    dsigma->SetPointEYhigh(i-1, sigmaErr);
    dsigma->SetPointEYlow(i-1, sigmaErr);

  }

  return dsigma;
}

TH1* getSigmaTruth(TH1F* hgen, TH1F* accept, double lumi ){

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  TH1* dsigma = new TH1F("dsigma","dsigma", nBinsMass, binsMass);

  for(int i=1; i <=  nBinsMass; i++){
    double x;
    double y;
    //accept->GetPoint(i-1,x,y);
    x = accept->GetBinCenter(i);
    y = accept->GetBinContent(i);

    double unfolded = hgen->GetBinContent(i);
    double sigma = 1000*unfolded/( y * lumi * hgen->GetBinWidth(i) ) ;
    dsigma->SetBinContent(i, sigma);
  }

  return dsigma;
}


