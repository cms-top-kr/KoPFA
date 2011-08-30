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

TH1F* unfoldingPlot(TH2* m, TH1* h_mea, TH1* h_genTTbar, TString name, double lumi, int k, RooUnfold::ErrorTreatment & err, bool print, bool pseudo, bool toy){

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

  //cout << "total= " << total << endl;
  //double diagonal = 0;
  //for(int i=0; i < nbins; i++){
  //  diagonal += Hres->GetBinContent(i+1,i+1);
  //  cout << "diagonal= " << diagonal << endl;
  //}
  //double offdiagonal = (total-diagonal)/total*100;
  //cout << "off diagonal= " << offdiagonal << endl;
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
  label->DrawLatex(0.50,0.88,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));
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
      for(int j=0; j <nbins; j++){
        double rec_ = RooUnfoldResponse::GetBinContent(unfoldedToy,j+1,true);
        double toyerror_ = RooUnfoldResponse::GetBinError(unfoldedToy,j+1,true);
        double error_ = h_unfold->GetBinError(j+1);
        if( i == 9999) cout << "toy error= " << toyerror_ << " error = " << error_ << endl; 
        double gen_ = hgen->GetBinContent(j+1);
        double pullNtrue_ = (gen_ - rec_)/gen_;
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

  //err after unfolding =============================================================================

  TCanvas *c_err = new TCanvas(Form("c_err_%s",name.Data()),Form("c_err_%s",name.Data()),1); 

  TGraph *gerr = new TGraph(nbins);  
  TGraph *gerrbefore = new TGraph(nbins);  

  for(int i=1; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
    } else{
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 0);
    }

    if( hmea->GetBinContent(i) != 0){
      gerrbefore->SetPoint(i-1, hmea->GetBinCenter(i), 100*hmea->GetBinError(i)/hmea->GetBinContent(i));
    } else {
      gerrbefore->SetPoint(i-1, hmea->GetBinCenter(i), 0);
    }
  }

  gerr->SetTitle(0);
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  label->DrawLatex(0.30,0.88,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));

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

  //log d plot =====================================================================================
  TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  c_d->SetLogy();
  TH1D* h_d = unfold->RooUnfoldSvd::Impl()->GetD();
  h_d->SetTitle(0);
  h_d->Draw("PC");
  h_d->GetYaxis()->SetTitle("log|d_{i}|");
  h_d->GetXaxis()->SetTitle("i");
  //================================================================================================

  //Printing chi2
  chi2.push_back(unfold->Chi2(hgen, err)); 
  cout << "chi2 : " << unfold->Chi2(hgen, err) << endl;

  //Saving canvas 
  if(print){
    c_response->Print(Form("cUF_response_%s.eps",name.Data()));
    c_responseH->Print(Form("cUF_responseH_%s.eps",name.Data()));
    c->Print(Form("cUF_unfold_%s.eps",name.Data()));
    c_err->Print(Form("cUF_err_%s.eps",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.eps",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.eps",name.Data()));
    //c_dsigma->Print(Form("cUF_dsigma_%s.eps",name.Data()));
    //c_Normdsigma->Print(Form("cUF_Normdsigma_%s.eps",name.Data()));
    c_d->Print(Form("cUF_d_%s.eps",name.Data()));
    if(toy){
      c_toy_sigma->Print(Form("cUF_toy_sigma_%s.eps",name.Data()));
      c_toy_Ntrue->Print(Form("cUF_toy_Ntrue_%s.eps",name.Data()));
    }

    c_response->Print(Form("cUF_response_%s.png",name.Data()));
    c_responseH->Print(Form("cUF_responseH_%s.png",name.Data()));
    c->Print(Form("cUF_unfold_%s.png",name.Data()));
    c_err->Print(Form("cUF_err_%s.png",name.Data()));
    c_meaerr->Print(Form("cUF_meaerr_%s.png",name.Data()));
    c_errmat->Print(Form("cUF_errmat_%s.png",name.Data()));
    //c_dsigma->Print(Form("cUF_dsigma_%s.png",name.Data()));
    //c_Normdsigma->Print(Form("cUF_Normdsigma_%s.png",name.Data()));
    c_d->Print(Form("cUF_d_%s.png",name.Data()));
    if(toy){
      c_toy_sigma->Print(Form("cUF_toy_sigma_%s.png",name.Data()));
      c_toy_Ntrue->Print(Form("cUF_toy_Ntrue_%s.png",name.Data()));
    }

  }
 
  return h_unfold;
}

void FinalPlot(TH1F* h_unfold, TH1F* gen, TH1F* accept, double lumi, TString hName, TString cName, double min, double max, bool norm=true, bool log=true, bool curve=false, bool print){

  int nbins = h_unfold->GetNbinsX();

  cout << "Unfolded: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaData = printFinal(nbins, h_unfold, accept, lumi, false, norm);
  cout << "Truth: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaTruth = printFinal(nbins, hgen, accept, lumi, true, norm);
  TH1* hSigmaTruth = getSigmaTruth(hgen, accept, lumi, norm);

  TCanvas *c_dsigma = new TCanvas(Form("c_%s_dsigma_%s",hName.Data(), cName.Data()),Form("c_%s_dsigma_%s",hName.Data(), cName.Data()));
  TGaxis::SetMaxDigits(4);

  if(log) c_dsigma->SetLogy();

  //SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"Unfolded t#bar{t} invariant mass (GeV/c^{2})","");

  if(norm){
    hSigmaTruth->GetYaxis()->SetTitle("1/#sigma_{t#bar{t}} d#sigma/dM_{t#bar{t}} (1/GeV/c^{2})");
  }else{
    hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}} (pb/GeV/c^{2})");
  }

  if(curve){
    hSigmaTruth->Draw("c");
  }else{
    hSigmaTruth->Draw();
  }

  //MC band
  //dsigmaTruth->SetFillColor(30);
  //dsigmaTruth->SetFillStyle(3001);
  //dsigmaTruth->SetLineColor(0);
  //dsigmaTruth->Draw("2same");

  dsigmaData->Draw("Psame");

  SetLabel(0.47,0.88, lumi);
  //Default Style
  SetLegend(hSigmaTruth, dsigmaData, "MadGraph", "Unfolded data", "L", "P", 0.58,0.64,0.80,0.8);
  //print
  Print(c_dsigma, "final", hName.Data(), cName.Data(), print);
}

void FinalPlot(TH1F* h_unfold, TH1F* gen, TH1F* accept, TH1D* hTr1, TH1D* hTr2, TH1D* hTr3, double lumi, TString hName, TString cName, double min, double max, bool norm=true, bool log=true, bool curve=false, bool print){

  int nbins = h_unfold->GetNbinsX();
  
  cout << "Unfolded: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaData = printFinal(nbins, h_unfold, accept, lumi, false, norm);
  cout << "Truth: evt number / sigma (pb)" << endl;
  TGraphAsymmErrors* dsigmaTruth = printFinal(nbins, hgen, accept, lumi, true, norm);

  TH1* hSigmaTruth = getSigmaTruth(hgen, hTr1, lumi, norm);
  TH1* hSigmaTruth2 = getSigmaTruth(hgen, hTr2, lumi, norm);
  TH1* hSigmaTruth3 = getSigmaTruth(hgen, hTr3, lumi, norm);
 
  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth2, 2,4,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth3, 2,3,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");

  TCanvas *c_dsigma = new TCanvas(Form("c_%s_dsigma_%s",hName.Data(), cName.Data()),Form("c_%s_dsigma_%s",hName.Data(), cName.Data()));
  TGaxis::SetMaxDigits(4);
  
  if(log) c_dsigma->SetLogy();
  
  //SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"M_{t#bar{t}} (GeV/c^{2})","");
  SetHistoStyle(hSigmaTruth, 2,2,1,0,0,0,min,max,"Unfolded t#bar{t} invariant mass (GeV/c^{2})","");
  
  if(norm){
    hSigmaTruth->GetYaxis()->SetTitle("1/#sigma_{t#bar{t}} d#sigma/dM_{t#bar{t}} (1/GeV/c^{2})"); 
  }else{
    hSigmaTruth->GetYaxis()->SetTitle("d#sigma/dM_{t#bar{t}} (pb/GeV/c^{2})");
  }

  if(curve){
    hSigmaTruth->Draw("c");
    hSigmaTruth2->Draw("csame");
    hSigmaTruth3->Draw("csame");
  }else{
    hSigmaTruth->Draw();
    hSigmaTruth2->Draw("same");
    hSigmaTruth3->Draw("same");
  }

  //MC band
  //dsigmaTruth->SetFillColor(30);
  //dsigmaTruth->SetFillStyle(3001);
  //dsigmaTruth->SetLineColor(0);
  //dsigmaTruth->Draw("2same");

  dsigmaData->Draw("Psame");

  SetLabel(0.47,0.88, lumi);
  //Default Style
  SetLegend(hSigmaTruth, hSigmaTruth2, hSigmaTruth3, dsigmaData, "MadGraph", "MC@NLO", "POWHEG", "Unfolded data", "L","L","L", "P", 0.58,0.64,0.80,0.8);
  //print
  Print(c_dsigma, "final", hName.Data(), cName.Data(), print);
}



TGraphAsymmErrors* printFinal( int nbins, TH1F* hgen, TH1F* accept, double lumi, bool truth, bool norm){

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

TH1* getSigmaTruth(TH1F* hgen, TH1F* accept, double lumi, bool norm){

  int nbins = hgen->GetNbinsX(); 

  TH1* dsigma = (TH1F*)hgen->Clone("disgma"); 
  dsigma->Reset();

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

TH1* getSigmaTruth(TH1F* hgen, TH1D* htruth, double lumi, bool norm){

  int nbins = hgen->GetNbinsX();

  TH1* dsigma = (TH1F*)hgen->Clone("disgma");
  dsigma->Reset();

  double total = htruth->Integral();

  for(int i=1; i <=  nbins; i++){
    double width = hgen->GetBinWidth(i);
    int start = hgen->GetBinCenter(i)-width/2 + 1;
    int end = hgen->GetBinCenter(i)+width/2;
    //cout << "start= " << start << " end=" << end;
    double unfolded = htruth->Integral(start, end);
    double normsigma = unfolded/( total * width );
    double sigma = unfolded/( lumi * width );

    if(norm){
      dsigma->SetBinContent(i, normsigma);
    }else{
      dsigma->SetBinContent(i, sigma);
    }
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


