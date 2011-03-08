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

#include <iostream>
#include "TUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/TSVDUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldResponse.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBayes.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldSvd.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBinByBin.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldInvert.h"

void unfoldingPlot(TH1* h_gen, TH1* h_rec, TH2* m, TH1* h_mea, TH1* h_genTTbar, double scale_ttbar, TString name, bool print, bool pseudo){

  RooUnfoldResponse *response = new RooUnfoldResponse(h_rec, h_gen, m);

  TH1F *hgen = (TH1F*)h_genTTbar->Clone("hgen");
  TH1F *hmea = (TH1F*)h_mea->Clone("hmea");
  TH1F *hrec = (TH1F*)h_rec->Clone("hrec");
  hgen->SetLineColor(2);
  hmea->SetLineColor(4);

  TCanvas *c_response = new TCanvas(Form("c_response_%s",name.Data()),Form("c_response_%s",name.Data()),1);
  m->Draw("colz");
  m->SetStats(0);
  m->SetTitle("");

  TCanvas *c = new TCanvas(Form("c_unfold_%s",name.Data()),Form("c_unfold_%s",name.Data()), 1);
  c->SetLogy();
  //unfolding
  hgen->Scale(scale_ttbar);
  hgen->SetLineWidth(2);
  hgen->SetStats(0);
  hgen->SetTitle(""); 
  hgen->GetYaxis()->SetTitle("Events");

  RooUnfold* unfold = 0;
  //unfold = new RooUnfoldBayes(response, h_mea, 4);    // OR
  unfold = new RooUnfoldSvd(response, h_mea, 2);   // OR
  //unfold = new RooUnfoldBinByBin(response, h_mea);
  //unfold = new RooUnfoldInvert(response, h_mea);

  TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kCovToy);
  //TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kCovariance);
  //TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kErrors);
  
  //TMatrixD m_unfoldE = unfold->Ereco();
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
  l_unfold->AddEntry(hgen,"True t#bar{t}","F");
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
  label->DrawLatex(0.50,0.88,"36.1 pb^{-1} at #sqrt{s} = 7 TeV");

  int nbins = h_unfold->GetNbinsX();

  TCanvas *c_err = new TCanvas(Form("c_err_%s",name.Data()),Form("c_err_%s",name.Data()),1); 

  TGraph *gerr = new TGraph(nbins);  
  TGraph *gerrbefore = new TGraph(nbins);  

  cout << "[bin range] / unfolded number / truth number " << endl;
  for(int i=1; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-1, h_unfold->GetBinCenter(i), 100*h_unfold->GetBinError(i)/h_unfold->GetBinContent(i));
      cout << "[" << h_unfold->GetBinCenter(i)-h_unfold->GetBinWidth(i)/2 << "," << h_unfold->GetBinCenter(i)+h_unfold->GetBinWidth(i)/2 << "]" ;
      cout << h_unfold->GetBinContent(i) << " $/\pm$ " << h_unfold->GetBinError(i) << " " ; 
      cout << hgen->GetBinContent(i) << " $/\pm$ " << sqrt(hgen->GetBinContent(i))*sqrt(scale_ttbar) << endl;
//    cout << " : " << v_unfoldE(i-1) << " : " << m_unfoldE(i-1,i-1) << endl;
    }

    if( hmea->GetBinContent(i) != 0){
      gerrbefore->SetPoint(i-1, hmea->GetBinCenter(i), 100*hmea->GetBinError(i)/hmea->GetBinContent(i));
    }
  }

  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  label->DrawLatex(0.30,0.88,"36.1 pb^{-1} at #sqrt{s} = 7 TeV");

  //TCanvas *c_meaerr = new TCanvas(Form("c_meaerr_%s",name.Data()),Form("c_meaerr_%s",name.Data()),1);
  //gerrbefore->Draw("ALP");
  //gerrbefore->SetLineStyle(2);
  //gerrbefore->SetMarkerStyle(20);
  

  //TCanvas *c_errmat = new TCanvas(Form("c_errmat_%s",name.Data()),Form("c_errmat_%s",name.Data()),1);
  //m_unfoldE.Draw("colz");

 
  TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  TH1D* h_d = unfold->RooUnfoldSvd::Impl()->GetD();
  h_d->Draw();

  cout << "chi2 : " << unfold->Chi2(hgen, RooUnfold::kErrors) << endl;
  //cout << "2 " << unfold->Chi2(hgen, RooUnfold::kCovariance) << endl;

  if(print){
    c_response->Print(Form("c_response_%s.eps",name.Data()));
    c->Print(Form("c_unfold_%s.eps",name.Data()));
    c_err->Print(Form("c_err_%s.eps",name.Data()));
    //c_errmat->Print(Form("c_errmat_%s.eps",name.Data()));
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

