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

void unfoldingPlot(TH1* h_gen, TH1* h_rec, TH2* m, TH1* h_mea, TH1* h_genTTbar, TGraphAsymmErrors* accept, double scale_ttbar, TString name, bool print, bool pseudo){

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
  label->DrawLatex(0.50,0.88,"35.9 pb^{-1} at #sqrt{s} = 7 TeV");

  int nbins = h_unfold->GetNbinsX();

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
  TGraphAsymmErrors* dsigmaData = printFinal(nbins, h_unfold, accept, 1, false);
  cout << "Truth: evt number / sigma (fb)" << endl;
  TGraphAsymmErrors* dsigmaTruth = printFinal(nbins, hgen, accept, scale_ttbar, true);
  TH1* hSigmaTruth = getSigmaTruth(hgen, accept);

  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");
  label->DrawLatex(0.30,0.88,"35.9 pb^{-1} at #sqrt{s} = 7 TeV");

  TCanvas *c_meaerr = new TCanvas(Form("c_meaerr_%s",name.Data()),Form("c_meaerr_%s",name.Data()),1);
  gerrbefore->Draw("ALP");
  gerrbefore->SetMarkerStyle(20);
  gerrbefore->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerrbefore->GetYaxis()->SetTitle("Statistical Uncertainty (%)");

  TCanvas *c_errmat = new TCanvas(Form("c_errmat_%s",name.Data()),Form("c_errmat_%s",name.Data()),1);
  m_unfoldE.Draw("colz");

  TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  TH1D* h_d = unfold->RooUnfoldSvd::Impl()->GetD();
  h_d->Draw();

  TCanvas *c_dsigma = new TCanvas(Form("c_dsigma_%s",name.Data()),Form("c_dsigma_%s",name.Data()));
  c_dsigma->SetLogy();
  hSigmaTruth->SetLineWidth(1);
  hSigmaTruth->SetLineStyle(1);
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

  label->DrawLatex(0.47,0.88,"35.9 pb^{-1} at #sqrt{s} = 7 TeV");
  
  cout << "chi2 : " << unfold->Chi2(hgen, RooUnfold::kErrors) << endl;
  //cout << "2 " << unfold->Chi2(hgen, RooUnfold::kCovariance) << endl;

  if(print){
    c_response->Print(Form("c_response_%s.eps",name.Data()));
    c->Print(Form("c_unfold_%s.eps",name.Data()));
    c_err->Print(Form("c_err_%s.eps",name.Data()));
    c_meaerr->Print(Form("c_meaerr_%s.eps",name.Data()));
    c_errmat->Print(Form("c_errmat_%s.eps",name.Data()));
    c_dsigma->Print(Form("c_dsigma_%s.eps",name.Data()));
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

TH1F* getMeasuredHisto( vector<std::string> rdPath, string cutStep){

  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1F *hData = new TH1F("hData","hData",nDet,detBins);

  for(int i = 0; i < rdPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TH1F *hTemp = (TH1F*) f_data->Get(Form("%s/hDataSub_%s_vsumMAlt", cutStep.c_str(), cutStep.c_str()));
    hData->Add(hTemp);
  }

  return hData;
}

TH2F* getResponseM( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var,  vector<TString> decayMode ){

  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nGen = sizeof(genBins)/sizeof(float) - 1;
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH2F *h2_response_m = new TH2F(Form("h2_response_m_%s_%s",var.Data(),decayMode[0].Data()),Form("h2_response_m_%s",var.Data()),nDet,detBins,nGen,genBins);

  for(int i = 0; i < mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TH2F *h2Temp = new TH2F(Form("h2_response_m_%s_%s",var.Data(),decayMode[i].Data()),Form("h2_response_m_%s",var.Data()),nDet,detBins,nGen,genBins);
    tree->Project(Form("h2_response_m_%s_%s",var.Data(),decayMode[i].Data()),Form("genttbarM:%sttbarM",var.Data()),cut, "", entries/2, 0);
    h2_response_m->Add(h2Temp);
  }

  return h2_response_m;
}

TH1F* getGenDistHisto( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var, vector<TString> decayMode ){

  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nGen = sizeof(genBins)/sizeof(float) - 1;

  TH1F *h_genTTbar = new TH1F(Form("h_genTTbar%s_%s",var.Data(),decayMode[0].Data()),"h_genTTbar",nGen,genBins);

  for(int i = 0; i< mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    hGenDistTemp = new TH1F(Form("hGenDisTemp_%s_%s",var.Data(),decayMode[i].Data()),"h_genTTbar",nGen,genBins);
    tree->Project(Form("hGenDisTemp_%s_%s",var.Data(),decayMode[i].Data()),"genttbarM", cut,"",entries/2, entries/2);  

    h_genTTbar->Add(hGenDistTemp);
  }

  return h_genTTbar;

}

TGraphAsymmErrors* getAcceptance(vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var, vector<TString> decayMode ){

  TFile * fDen = new TFile("/home/tjkim/ntuple/top/genTTbar/ttbarGen.root");
  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  TH1F* hDen = new TH1F("hDen", "Denominator", nBinsMass, binsMass);
  TH1F* hNum = new TH1F("hNum", "Numerator", nBinsMass, binsMass);

  genTreeDen->Project("hDen", "tt.M()");

  for(int i = 0; i < mcPath.size() ; i++){

    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    TH1F* hNumTemp = new TH1F(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "Numerator", nBinsMass, binsMass);
    tree->Project(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "genttbarM", cut);
    hNum->Add(hNumTemp);

  }

  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors;

  for(int i=0; i < nBinsMass; i++){
    int bin = i+1;
    double acc = hNum->GetBinContent(bin)/hDen->GetBinContent(bin);
    double center = hNum->GetBinCenter(bin);
    double width = hNum->GetBinWidth(bin);
    double err = sqrt(hNum->GetBinContent(bin))/hDen->GetBinContent(bin);
    grpAccept->SetPoint(i, center, acc );
    grpAccept->SetPointEXhigh(i, width/2);
    grpAccept->SetPointEXlow(i, width/2);
    grpAccept->SetPointEYhigh(i, err);
    grpAccept->SetPointEYlow(i, err);
    cout << "accept= " << acc << endl;
  }

  return grpAccept;

}

TGraphAsymmErrors* printFinal( int nbins, TH1F* hgen, TGraphAsymmErrors* accept, double scale, bool truth ){

  TGraphAsymmErrors* dsigma = new TGraphAsymmErrors;

  for(int i=1; i <=  nbins; i++){
    double x;
    double y;
    accept->GetPoint(i-1,x,y);
   
    double unfolded = hgen->GetBinContent(i);
    double err = 0;
    if(truth) err = sqrt(hgen->GetBinContent(i))*sqrt(scale) ;
    else err = hgen->GetBinError(i);

    double sigma = 1000*unfolded/( y * 35.9 * hgen->GetBinWidth(i) ) ;
    double sigmaErr = sigma*err/unfolded;

    cout << "$" << hgen->GetBinCenter(i)-hgen->GetBinWidth(i)/2 << "-" << hgen->GetBinCenter(i)+hgen->GetBinWidth(i)/2 << "$   ~&~ "
         << hgen->GetBinContent(i) << " $\\pm$ " << err << " ~&~ "
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

TH1* getSigmaTruth(TH1F* hgen, TGraphAsymmErrors* accept ){

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  TH1* dsigma = new TH1F("dsigma","dsigma", nBinsMass, binsMass);

  for(int i=1; i <=  nBinsMass; i++){
    double x;
    double y;
    accept->GetPoint(i-1,x,y);
    double unfolded = hgen->GetBinContent(i);
    double sigma = 1000*unfolded/( y * 35.9 * hgen->GetBinWidth(i) ) ;
    dsigma->SetBinContent(i, sigma);
  }

  return dsigma;

}
