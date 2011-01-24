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

#include <iostream>
#include "TUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfold.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldResponse.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBayes.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldSvd.h"
#include "unfold/RooUnfold-1.0.3/src/RooUnfoldBinByBin.h"

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
  t->Project(Form("h2_relMt2_%s",name.Data()),Form("%s:maos2Mt2",var.Data()), cut);
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
void unfoldingPlot(TH1* h_gen, TH1* h2, TH2* m, TH1* h_rec, double norm, TString name, bool scale, bool print){

  TCanvas *c_mat = new TCanvas(Form("c_mat_%s",name.Data()),Form("c_mat_%s",name.Data()),1);
  m->Draw("colz");

  TCanvas *c = new TCanvas(Form("c_unfold_%s",name.Data()),Form("c_unfold_%s",name.Data()), 1);
  h_gen->Draw();
  h_rec->Draw("same");
  cout << "test" << endl;
  //unfolding
  RooUnfoldResponse *response = new RooUnfoldResponse(h2,h_gen,m);

  RooUnfold* unfold = 0;
  unfold = new RooUnfoldBayes(response, h_rec, 4);    // OR
//RooUnfoldSvd      unfold (&response, hMeas, 20);   // OR
//RooUnfoldBinByBin unfold (&response, hMeas);
  TH1F* h_unfold = (TH1F*) unfold->Hreco();
  if(scale){
    h_unfold->Scale(norm);
  }
  h_unfold->Draw("Psame");
  h_unfold->SetLineColor(1);
  h_unfold->SetMarkerSize(3);

  TLegend *l_unfold= new TLegend(0.60,0.60,0.8,0.8);
  l_unfold->AddEntry(h_gen,"gen","l");
  l_unfold->AddEntry(h2,Form("meas. %s",name.Data()),"l");
  l_unfold->AddEntry(h_unfold,"unfolded","p");
  l_unfold->SetTextSize(0.04);
  l_unfold->SetFillColor(0);
  l_unfold->SetLineColor(0);
  l_unfold->Draw();
  
  if(print){
    c_mat->Print(Form("c_mat_%s.eps",name.Data()));
    c->Print(Form("c_unfold_%s.eps",name.Data()));
  }
}

void massPlot(TH1* h1, TH1* h2, TH1* h3){

  TCanvas *c = new TCanvas("c","c", 1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  //h_data_m->SetMarkerSize(2);
  double L_data = 36.1;
  double L_ttbar = 1000000.0/157.5;
  double norm = L_data/L_ttbar;
  double nh1 = h1->GetEntries();
  double nh2 = h2->GetEntries();
  double nh3 = h3->GetEntries();
  //double nh_data = h_data_m->GetEntries();
  double A2 = nh2/nh1;
  double A3 = nh3/nh1;
  cout << "Acceptance= " << A2 << "(vsum)" << " " << A3  << "(maos)" << endl;
  h2->Scale(1/A2);
  h3->Scale(1/A3);
  //h_data_m->Scale(nh3/nh_data);

  //h1->SetMaximum(1000);
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  //h_data_m->Draw("same");
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  //h_data_m->SetStats(0);
  //h_data_m->SetMarkerStyle(20);
  //h_data_m->SetMarkerSize(0.5);
  //h_data_m->Sumw2();

  TLegend *l= new TLegend(0.55,0.55,0.8,0.8);
  l->AddEntry(h1,"gen ttbar","l");
  l->AddEntry(h2,"4-vec. sum","l");
  l->AddEntry(h3,"maos mass","l");
  //l->AddEntry(h_data_m,"data M","l");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
 
  c->Print("c_massPlot.eps");

}

void relttbar(){

  bool print = true;

  TFile * f_data = new TFile("vallot_data.root");
  TFile * f = new TFile("vallot_TTbar.root");
  TTree * t_data = (TTree *) f_data->Get("MuMu/tree");
  TTree * t = (TTree *) f->Get("MuMu/tree");

  int nbin_mt = 20;
  double max_mt = 1200;
  double low_mt = 200;

  TH1 *h1 = new TH1F("h1","h1",nbin_mt,low_mt,max_mt);
  TH1 *h2 = new TH1F("h2","h2",nbin_mt,low_mt,max_mt);
  TH1 *h3 = new TH1F("h3","h3",nbin_mt,low_mt,max_mt);
  TH2 *h2_gen_reco_maos = new TH2F("h2_gen_reco_maos","h2_gen_reco_maos",nbin_mt,low_mt,max_mt,nbin_mt,low_mt,max_mt);
  TH2 *h2_gen_reco_vsum = new TH2F("h2_gen_reco_vsum","h2_gen_reco_vsum",nbin_mt,low_mt,max_mt,nbin_mt,low_mt,max_mt);

  TCut precut = "Z.mass() > 12 && relIso04lep1 < 0.21 && relIso04lep2 < 0.21 && Z.sign() < 0 && abs(Z.mass() - 91.2) > 15 && @jetspt30.size() >= 2 && MET >30";
  TCut mt2 = "maos2Mt2 > 140";
  TCut cut = precut; 

  t->Project("h1","genttbarM","genttbarM > 0");
  t->Project("h2","vsumttbarM",cut);
  t->Project("h3","maosttbarM",cut);

  t_data->Project("h_data_m","vsumttbarM",cut);

  acceptPlot(h1, h2, nbin_mt, "vsum", print);
  acceptPlot(h1, h3, nbin_mt, "maos", print);

  massPlot(h1, h2, h3);

  double nh1 = h1->GetEntries();
  double nh2 = h2->GetEntries();
  double nh3 = h3->GetEntries();

  resolutionPlot(t,"relmaosM", cut, "maos", print);
  resolutionPlot(t,"relvsumM", cut, "vsum", print);

  t->Project("h2_gen_reco_maos","genttbarM:maosttbarM",cut);
  t->Project("h2_gen_reco_vsum","genttbarM:vsumttbarM",cut);

  unfoldingPlot(h1, h3, h2_gen_reco_maos, h2, nh2/nh1, "maos", true, print);
  unfoldingPlot(h1, h2, h2_gen_reco_vsum, h3, nh3/nh1, "vsum", true, print);

}
