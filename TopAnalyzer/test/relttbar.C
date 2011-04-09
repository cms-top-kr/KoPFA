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

#include <iostream>
#include "TUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/TSVDUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldResponse.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBayes.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldSvd.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBinByBin.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldInvert.h"

void resolutionPlot(TTree* t, TString var, TCut cut, TString name, bool print){
  TH1 *h_rel = new TH1F(Form("h_rel_%s",name.Data()),Form("h_rel_%s",name.Data()),100,-500,500);
  TH1 *h_frac_rel = new TH1F(Form("h_frac_rel_%s",name.Data()),Form("h_frac_rel_%s",name.Data()),60,-3,3);
  TH2 *h2_relgenM = new TH2F(Form("h2_relgenM_%s",name.Data()),Form("h2_relgenM_%s",name.Data()),30,320,920,500,-500,500);
  TH2 *h2_relMt2 = new TH2F(Form("h2_relMt2_%s",name.Data()),Form("h2_relMt2_%s",name.Data()),30,100,400,500,-500,500);

  TCanvas *c_rel = new TCanvas(Form("c_rel_%s",name.Data()),Form("c_rel_%s",name.Data()),1);
  t->Project(Form("h_rel_%s",name.Data()),Form("%s",var.Data()),cut);
  h_rel->Draw();
  h_rel->GetXaxis()->SetTitle("gen M(t#bar{t}) - reco M(t#bar{t})");
  h_rel->SetStats(true);

  TCanvas *c_frac_rel = new TCanvas(Form("c_frac_rel_%s",name.Data()),Form("c_frac_rel_%s",name.Data()),1);
  t->Project(Form("h_frac_rel_%s",name.Data()),Form("%s/genttbarM",var.Data()), cut);
  h_frac_rel->Draw();
  h_frac_rel->GetXaxis()->SetTitle("(gen M(t#bar{t}) - reco M(t#bar{t}))/gen M(t#bar{t})");
  h_frac_rel->SetStats(true);

  TCanvas *c_relgenM = new TCanvas(Form("c_relgenM_%s",name.Data()),Form("c_relgenM_%s",name.Data()),1);
  t->Project(Form("h2_relgenM_%s",name.Data()),Form("%s:genttbarM",var.Data()), cut);
  h2_relgenM->Draw();
  h2_relgenM->GetYaxis()->SetTitle("gen M(t#bar{t}) - reco M(t#bar{t})");
  h2_relgenM->GetXaxis()->SetTitle("gen M(t#bar{t})");
  h2_relgenM->SetStats(0);

  TCanvas *c_prof_relgenM =  new TCanvas(Form("c_prof_relgenM_%s",name.Data()),Form("c_prof_relgenM_%s",name.Data()),1);
  TProfile *prof_relgenM;
  prof_relgenM = h2_relgenM->ProfileX("prof_relgenM");
  prof_relgenM->Draw();
  //for(int i=1; i < 31; i++){ 
  //  cout << h2_relgenM->ProjectionY("",i)->GetMean() << " : " << h2_relgenM->ProjectionY("",i)->GetRMS() << endl;
  //}
  prof_relgenM->SetStats(0);
  prof_relgenM->GetYaxis()->SetTitle("mean of #Deltam(t#bar{t})");
  prof_relgenM->GetXaxis()->SetTitle("gen M(t#bar{t})");

  TCanvas *c_relMt2 = new TCanvas(Form("c_relMt2_%s",name.Data()),Form("c_relMt2_%s",name.Data()),1);
  t->Project(Form("h2_relMt2_%s",name.Data()),Form("%s:maosMt2",var.Data()), cut);
  h2_relMt2->Draw();
  h2_relMt2->GetYaxis()->SetTitle("gen M(t#bar{t}) - reco M(t#bar{t})");
  h2_relMt2->GetXaxis()->SetTitle("Mt2");
  h2_relMt2->SetStats(0);

  TCanvas *c_prof_relMt2 =  new TCanvas(Form("c_prof_relMt2_%s",name.Data()),Form("c_prof_relMt2_%s",name.Data()),1);
  TProfile *prof_relMt2;
  prof_relMt2 = h2_relMt2->ProfileX("prof_relMt2");
  prof_relMt2->Draw();
  //for(int i=1; i < 31; i++){
  //  cout << h2_relMt2->ProjectionY("",i)->GetMean() << " : " << h2_relMt2->ProjectionY("",i)->GetRMS() << endl;
  //}
  prof_relMt2->SetStats(0);
  prof_relMt2->GetYaxis()->SetTitle("mean of #Deltam(t#bar{t})");
  prof_relMt2->GetXaxis()->SetTitle("Mt2");

  if(print){
    c_rel->Print(Form("c_rel_%s.eps",name.Data()));
    c_frac_rel->Print(Form("c_frac_rel_%s.eps",name.Data()));
    c_relgenM->Print(Form("c_relgenM_%s.eps",name.Data()));
    c_prof_relgenM->Print(Form("c_prof_relgenM_%s.eps",name.Data()));
    c_relMt2->Print(Form("c_relMt2_%s.eps",name.Data()));
    c_prof_relMt2->Print(Form("c_prof_relMt2_%s.eps",name.Data()));
  }
}

void acceptPlot(TH1* h1, TH1* h2, int nbin_mt, TString name, bool print){

  TCanvas *c_eff_vsum_m = new TCanvas(Form("c_eff_%s_m",name.Data()),Form("c_eff_%s_m",name.Data()), 1);
  TH1D *h_tmp = new TH1D(Form("h_temp_%s",name.Data()),Form("h_temp_%s",name.Data()),nbin_mt, 200, 1200);
  h_tmp->SetMinimum(0);
  h_tmp->SetMaximum(1.05);
  h_tmp->SetTitle("");
  h_tmp->SetStats(0);
  h_tmp->GetXaxis()->SetTitle("mt2");
  h_tmp->GetYaxis()->SetTitle("Efficiency");
  h_tmp->Draw();

  TGraphAsymmErrors *eff_vsum = new TGraphAsymmErrors();

  //for(int i=1 ; i <= nbin_mt ;i++ ){
  //  double de = h1->GetBinContent(i);
  //  double no = h2->GetBinContent(i);
  //  double ac = 0;
  //  if(de != 0){
  //    ac = no/de;
  //  }
  //  eff_vsum->SetPoint(i-1, h1->GetBinCenter(i), ac);
  //}

  eff_vsum->BayesDivide(h2,h1);
  clearXErrorBar(eff_vsum);
  eff_vsum->SetMarkerStyle(20);
  eff_vsum->SetMarkerSize(1.0);
  eff_vsum->SetMarkerColor(1);
  eff_vsum->Draw("P");
 
  if(print){
    c_eff_vsum_m->Print(Form("c_eff_%s.eps",name.Data()));
  }

} 

void unfoldingPlot(TH1* h_gen, TH1* h_rec, TH2* m, TH1* h_mea, double scale_ttbar, TString name, bool print){

  TH1F *hgen = (TH1F*)h_gen->Clone("hgen");
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

  RooUnfoldResponse *response = new RooUnfoldResponse(h_rec, h_gen, m);

  RooUnfold* unfold = 0;
  //unfold = new RooUnfoldBayes(response, h_mea, 4);    // OR
  unfold = new RooUnfoldSvd(response, h_mea, 2);   // OR
  //unfold = new RooUnfoldBinByBin(response, h_mea);
  //unfold = new RooUnfoldInvert(response, h_mea);


  //TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kCovariance);
  TH1F* h_unfold = (TH1F*) unfold->Hreco(RooUnfold::kErrors);
  TMatrixD m_unfoldE = unfold->Ereco();
  TVectorD v_unfoldE = unfold->ErecoV(RooUnfold::kCovariance);

  hgen->Draw();
  hmea->Draw("same");  
  hmea->SetLineStyle(2);
  hmea->SetLineWidth(2);
  hmea->SetStats(0);

  h_unfold->Draw("Psame");
  h_unfold->SetLineColor(1);
  h_unfold->SetLineWidth(2);
  h_unfold->SetMarkerStyle(20);
  h_unfold->SetMarkerSize(1.0);
  h_unfold->SetStats(0);  
  

  TLegend *l_unfold= new TLegend(0.65,0.60,0.80,0.8);
  l_unfold->AddEntry(hgen,"true t#bar{t}","l");
  l_unfold->AddEntry(hmea,"data t#bar{t}","l");
  l_unfold->AddEntry(h_unfold,"Unfolded t#bar{t}","p");
  l_unfold->SetTextSize(0.04);
  l_unfold->SetFillColor(0);
  l_unfold->SetLineColor(0);
  l_unfold->Draw();

  TCanvas *c_err = new TCanvas(Form("c_err_%s",name.Data()),Form("c_err_%s",name.Data()),1); 
  int nbins = h_unfold->GetNbinsX();
  int offset = 0;
  int size = nbins - offset;
  TGraph *gerr = new TGraph(size);  
  for(int i=1+offset; i <=  nbins; i++){
    if( h_unfold->GetBinContent(i) != 0 ){
      gerr->SetPoint(i-1-offset, h_unfold->GetBinCenter(i), 100*v_unfoldE(i-1)/h_unfold->GetBinContent(i));
//      cout << "[" << h_unfold->GetBinCenter(i)-h_unfold->GetBinWidth(i)/2 << "," << h_unfold->GetBinCenter(i)+h_unfold->GetBinWidth(i)/2 << "]" ;
//      cout << " : " << h_unfold->GetBinError(i) << "/" <<h_unfold->GetBinContent(i);
//      cout << " : " << v_unfoldE(i-1) << " : " << m_unfoldE(i-1,i-1) << endl;
    }
  }
  gerr->SetMarkerStyle(20);
  gerr->Draw("ALP");
  gerr->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  gerr->GetYaxis()->SetTitle("Statistical Uncertainty (%)");

  TCanvas *c_errmat = new TCanvas(Form("c_errmat_%s",name.Data()),Form("c_errmat_%s",name.Data()),1);
  m_unfoldE.Draw("colz");

  //TCanvas *c_d = new TCanvas(Form("c_d_%s",name.Data()),Form("c_d_%s",name.Data()));
  //RooUnfoldSvd* unfoldsvd = new RooUnfoldSvd(response, h_mea, 5);
  //TSVDUnfold* tsvdunfold = unfold->Impl();
  //TH1D* test = tsvdunfold->GetD();
  //cout << tsvdunfold->GetKReg() << endl;
  //cout << unfoldsvd->GetKterm() << endl;
  //h_d->Draw();

  cout << "chi2 : " << unfold->Chi2(hgen, RooUnfold::kErrors) << endl;
  //cout << "2 " << unfold->Chi2(hgen, RooUnfold::kCovariance) << endl;

  if(print){
    c_response->Print(Form("c_response_%s.eps",name.Data()));
    c->Print(Form("c_unfold_%s.eps",name.Data()));
    c_err->Print(Form("c_err_%s.eps",name.Data()));
    c_errmat->Print(Form("c_errmat_%s.eps",name.Data()));
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
  h3->Draw("PEsame");
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);

  int nbins = h3->GetNbinsX();
  for(int i=1; i <=  nbins; i++){
    std::cout << "[" << h3->GetBinCenter(i)-h3->GetBinWidth(i)/2 << "," << h3->GetBinCenter(i)+h3->GetBinWidth(i)/2 << "]" ;
    std::cout << " : " << h3->GetBinError(i) << "/" <<h3->GetBinContent(i) << std::endl;
  }


  TLegend *l= new TLegend(0.55,0.55,0.8,0.8);
  l->AddEntry(h1,"gen mass","l");
  l->AddEntry(h2,"reco mass","l");
  l->AddEntry(h3,"data mass","p");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
 
  c->Print("c_massPlot.eps");

}

void plot(TTree *t, TTree *t_data, const TString &var, const double &scale_ttbar, TCut cut, bool print){
  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 650, 700, 750, 800, 900, 1000, 1400};
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 650, 700, 750, 800, 900, 1000, 1400};
  int nGen = sizeof(genBins)/sizeof(float) - 1;
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1 *h_genMC = new TH1F(Form("h_genMC%s",var.Data()),"h_genMC",nGen,genBins);
  TH1 *h_recMC = new TH1F(Form("h_recMC%s",var.Data()),"h_recMC",nDet,detBins);
  TH1 *h_meaData = new TH1F(Form("h_meaData%s",var.Data()),"h_meaData",nDet,detBins);
  TH2 *h2_gen_reco_vsum = new TH2F(Form("h2_gen_reco_%s",var.Data()),Form("h2_gen_reco_%s",var.Data()),nDet,detBins,nGen,genBins);
 
  t->Project(Form("h_genMC%s",var.Data()),"genttbarM",cut);
  t->Project(Form("h_recMC%s",var.Data()),Form("%sttbarM",var.Data()),cut);
  t->Project(Form("h2_gen_reco_%s",var.Data()),Form("genttbarM:%sttbarM",var.Data()),cut);
  t_data->Project(Form("h_meaData%s",var.Data()),Form("%sttbarM",var.Data()),cut);

  //acceptPlot(h_gen, h2, nbin_mt, "vsum", print);

  massPlot(h_genMC, h_recMC, h_meaData, scale_ttbar);

  //resolutionPlot(t,Form("rel%sM",var.Data()), cut, Form("%s",var.Data()), print);

  unfoldingPlot(h_genMC, h_recMC, h2_gen_reco_vsum, h_meaData, scale_ttbar, Form("%s",var.Data()), print);

}

void relttbar(const TString& decayMode = "ElEl"){
  
  bool print = true;
  
  TFile * f_data = new TFile("vallot_TTbar1fb_MuEl.root");
  //TFile * f_data = new TFile("vallot_data_MuEl.root");
  TFile * f = new TFile("vallot_TTbar_MuEl.root");
  TTree * t_data = (TTree *) f_data->Get(decayMode+"/tree");
  TTree * t = (TTree *) f->Get(decayMode+"/tree");
 
  TCut precut = "Z.mass() > 12 && relIso04lep1 < 0.26 && relIso04lep2 < 0.26 && Z.sign() < 0 && @jetspt30.size() >= 2 && abs(Z.mass() - 91 ) > 15 && MET > 30";
  TCut mt2 = "maosMt2 > 140";
  TCut cut = precut;
  //double lumi = 36.1; //pb-1
  double lumi = 1000; //pb-1
  double lumi_ttbar = 1000000.0/157.5; //pb-1
  //double lumi_ttbar = 853741/157.5; //pb-1
  double scale_ttbar = lumi/lumi_ttbar;

  plot(t,t_data,"vsum",scale_ttbar, cut, true);
  //plot(t,t_data,"maos",scale_ttbar, cut, true);
 
}

