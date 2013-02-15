#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
//using namespace std;
void btagefficiency(int ii, int jj)
{
    gROOT->ProcessLine(".L tdrstyle.C");
    defaultStyle();
    TFile* f1 = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20130208_V00-00-06/vallot_TTbarFullLepMGDecays.root");
	
    TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
    TTree* treeElEl = (TTree*)f1->Get("ElEl/tree");
    TTree* treeMuEl = (TTree*)f1->Get("MuEl/tree");
	
    float binspt[] = {20,30,40,50,60,70,80,100,120,160,210,260,320,400,450};
    int nBinpt = sizeof(binspt)/sizeof(float) - 1;
    float binseta[] = {0.,0.4,0.8,1.2,1.6,2.0,2.4};
    int nBineta = sizeof(binseta)/sizeof(float) - 1;

    TCut precut_em = "ZMass > 12 && lep1_relIso03 < 0.15 && lep2_relIso03 < 0.15 && PairSign < 0 && nJet30 >= 4";
    TCut precut = precut_em + "abs(ZMass - 91.2) > 15 && MET > 30"; 
    TCut bcut =  "abs(jets_flavor) == 5";
    TCut ccut =  "abs(jets_flavor) == 4";
    TCut lcut =  "abs(jets_flavor) < 4";

    TCut etacut1 = "abs(jets_eta) <= 0.8";
    TCut etacut2 = "abs(jets_eta) > 0.8 && abs(jets_eta) <=1.6";
    TCut etacut3 = "abs(jets_eta) > 1.6";

    TCut etacutl1 = "abs(jets_eta) <= 0.5";
    TCut etacutl2 = "abs(jets_eta) > 0.5 && abs(jets_eta) <=1.0";
    TCut etacutl3 = "abs(jets_eta) > 1.0 && abs(jets_eta) <=1.5";
    TCut etacutl4 = "abs(jets_eta) > 1.5";


    TCut csvl =  "jets_bDiscriminatorCSV > 0.244";
    TCut csvm =  "jets_bDiscriminatorCSV > 0.679";
    TCut csvt =  "jets_bDiscriminatorCSV > 0.898";


    float binsDR[] = {0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.2,3.5,4};
    int nBinDR = sizeof(binsDR)/sizeof(float) - 1;
    TString DR_ = "TMath::Sqrt( abs(jets_eta[csvd_jetid[2]]-jets_eta[csvd_jetid[3]])*abs(jets_eta[csvd_jetid[2]]-jets_eta[csvd_jetid[3]])+abs(TVector2::Phi_mpi_pi(jets_phi[csvd_jetid[2]]-jets_phi[csvd_jetid[3]]))*abs(TVector2::Phi_mpi_pi(jets_phi[csvd_jetid[2]]-jets_phi[csvd_jetid[3]])) )";  

    float binsCSV[] = {0.0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};
    int nBinCSV = sizeof(binsCSV)/sizeof(float) - 1;
    

 if(ii ==4)
 {
    TH1F* dist_b_csvd = dist(treeElEl, treeMuMu, treeMuEl, "jets_bDiscriminatorCSV", nBinCSV, binsCSV, precut, precut_em, bcut, "B flavor","b_csvd",2,"discriminator (CSV)"); 
    TH1F* dist_c_csvd = dist(treeElEl, treeMuMu, treeMuEl, "jets_bDiscriminatorCSV", nBinCSV, binsCSV, precut, precut_em, ccut, "C flavor","c_csvd",4,"discriminator (CSV)");
    TH1F* dist_l_csvd = dist(treeElEl, treeMuMu, treeMuEl, "jets_bDiscriminatorCSV", nBinCSV, binsCSV, precut, precut_em, lcut, "LF flavor","l_csvd",3,"discriminator (CSV)");

    TCanvas * c_b_csvd = new TCanvas("c_b_csvd","c_b_csvd",500,500);
    double ymax = dist_l_csvd->GetMaximum(); 
    if(ymax< dist_c_csvd->GetMaximum()) ymax=dist_c_csvd->GetMaximum();
    if(ymax< dist_b_csvd->GetMaximum()) ymax=dist_b_csvd->GetMaximum();   

    ymax=ymax*1.5;
    dist_l_csvd->SetMaximum(ymax);   
 
    dist_l_csvd->Draw("");
    dist_c_csvd->Draw("same");
    dist_b_csvd->Draw("same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(dist_b_csvd,"b-flavor","L");
    l->AddEntry(dist_c_csvd,"c-flavor","L");
    l->AddEntry(dist_l_csvd,"l-flavor","L");
    SetLegend(l);
    c_b_csvd->Print("compare_b_csvd.png");
    c_b_csvd->Print("compare_b_csvd.eps");
 }
 else if(ii ==3)
 {
    TH1F* eff_b_dr_CSVL = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, bcut, csvl, "b_dr_CSVL","CSVL",2,"#Delta R"); 
    TH1F* eff_c_dr_CSVL = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, ccut, csvl, "c_dr_CSVL","CSVL",4,"#Delta R");
    TH1F* eff_l_dr_CSVL = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, lcut, csvl, "l_dr_CSVL","CSVL",5,"#Delta R");

    TH1F* eff_b_dr_CSVM = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, bcut, csvm, "b_dr_CSVM","CSVM",2,"#Delta R"); 
    TH1F* eff_b_dr_CSVT = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, bcut, csvt, "b_dr_CSVT","CSVT",2,"#Delta R"); 

    TH1F* eff_c_dr_CSVM = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, ccut, csvm, "c_dr_CSVM","CSVM",4,"#Delta R");
    TH1F* eff_c_dr_CSVT = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, ccut, csvt, "c_dr_CSVT","CSVT",4,"#Delta R");

    TH1F* eff_l_dr_CSVM = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, lcut, csvm, "l_dr_CSVM","CSVM",5,"#Delta R");
    TH1F* eff_l_dr_CSVT = eff(treeElEl, treeMuMu, treeMuEl, DR_.Data(), nBinDR, binsDR, precut, precut_em, lcut, csvt, "l_dr_CSVT","CSVT",5,"#Delta R");

    TCanvas * c_b_dr_CSVL = new TCanvas("c_b_dr_CSVL","c_b_dr_CSVL",500,500);
    eff_b_dr_CSVL->Draw("e3");
    eff_c_dr_CSVL->Draw("e3 same");
    eff_l_dr_CSVL->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_dr_CSVL,"b-flavor","F");
    l->AddEntry(eff_c_dr_CSVL,"c-flavor","F");
    l->AddEntry(eff_l_dr_CSVL,"l-flavor","F");
    SetLegend(l);
    c_b_dr_CSVL->Print("compare_b_dr_CSVL.png");
    c_b_dr_CSVL->Print("compare_b_dr_CSVL.eps");


    TCanvas * c_b_dr_CSVM = new TCanvas("c_b_dr_CSVM","c_b_dr_CSVM",500,500);
    eff_b_dr_CSVM->Draw("e3");
    eff_c_dr_CSVM->Draw("e3 same");
    eff_l_dr_CSVM->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_dr_CSVM,"b-flavor","F");
    l->AddEntry(eff_c_dr_CSVM,"c-flavor","F");
    l->AddEntry(eff_l_dr_CSVM,"l-flavor","F");
    SetLegend(l);
    c_b_dr_CSVM->Print("compare_b_dr_CSVM.png");
    c_b_dr_CSVM->Print("compare_b_dr_CSVM.eps");

    TCanvas * c_b_dr_CSVT = new TCanvas("c_b_dr_CSVT","c_b_dr_CSVT",500,500);
    eff_b_dr_CSVT->Draw("e3");
    eff_c_dr_CSVT->Draw("e3 same");
    eff_l_dr_CSVT->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_dr_CSVT,"b-flavor","F");
    l->AddEntry(eff_c_dr_CSVT,"c-flavor","F");
    l->AddEntry(eff_l_dr_CSVT,"l-flavor","F");
    SetLegend(l);
    c_b_dr_CSVT->Print("compare_b_dr_CSVT.png");
    c_b_dr_CSVT->Print("compare_b_dr_CSVT.eps");

 }
 else if(ii ==0)
 {

    TH1F* eff_b_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, bcut, csvl, "b_pt_CSVL","CSVL",2,"p_{T}(GeV/c)"); 
    TH1F* eff_c_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, ccut, csvl, "c_pt_CSVL","CSVL",4,"p_{T}(GeV/c)");
    TH1F* eff_l_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut, csvl, "l_pt_CSVL","CSVL",5,"p_{T}(GeV/c)");

    TH1F* eff_b_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, bcut, csvm, "b_pt_CSVM","CSVM",2,"p_{T}(GeV/c)"); 
    TH1F* eff_b_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, bcut, csvt, "b_pt_CSVT","CSVT",2,"p_{T}(GeV/c)"); 

    TH1F* eff_c_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, ccut, csvm, "c_pt_CSVM","CSVM",4,"p_{T}(GeV/c)");
    TH1F* eff_c_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, ccut, csvt, "c_pt_CSVT","CSVT",4,"p_{T}(GeV/c)");

    TH1F* eff_l_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut, csvm, "l_pt_CSVM","CSVM",5,"p_{T}(GeV/c)");
    TH1F* eff_l_pt_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut, csvt, "l_pt_CSVT","CSVT",5,"p_{T}(GeV/c)");

    TCanvas * c_b_pt_CSVL = new TCanvas("c_b_pt_CSVL","c_b_pt_CSVL",500,500);
    eff_b_pt_CSVL->Draw("e3");
    eff_c_pt_CSVL->Draw("e3 same");
    eff_l_pt_CSVL->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVL,"b-flavor","F");
    l->AddEntry(eff_c_pt_CSVL,"c-flavor","F");
    l->AddEntry(eff_l_pt_CSVL,"l-flavor","F");
    SetLegend(l);
    c_b_pt_CSVL->Print("compare_b_pt_CSVL.png");
    c_b_pt_CSVL->Print("compare_b_pt_CSVL.eps");


    TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
    eff_b_pt_CSVM->Draw("e3");
    eff_c_pt_CSVM->Draw("e3 same");
    eff_l_pt_CSVM->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVM,"b-flavor","F");
    l->AddEntry(eff_c_pt_CSVM,"c-flavor","F");
    l->AddEntry(eff_l_pt_CSVM,"l-flavor","F");
    SetLegend(l);
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.png");
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.eps");

    TCanvas * c_b_pt_CSVT = new TCanvas("c_b_pt_CSVT","c_b_pt_CSVT",500,500);
    eff_b_pt_CSVT->Draw("e3");
    eff_c_pt_CSVT->Draw("e3 same");
    eff_l_pt_CSVT->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVT,"b-flavor","F");
    l->AddEntry(eff_c_pt_CSVT,"c-flavor","F");
    l->AddEntry(eff_l_pt_CSVT,"l-flavor","F");
    SetLegend(l);
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.png");
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.eps");


 }
 else if(ii==2)
 {
    if(jj==0)
    {
        TH1F* eff_l1_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacutl1, csvl, "l1_pt_CSVL","CSVL",2,"p_{T}(GeV/c)"); 
        TH1F* eff_l2_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacutl2, csvl, "l2_pt_CSVL","CSVL",3,"p_{T}(GeV/c)");
        TH1F* eff_l3_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacutl3, csvl, "l3_pt_CSVL","CSVL",4,"p_{T}(GeV/c)");
        TH1F* eff_l4_pt_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacutl4, csvl, "l4_pt_CSVL","CSVL",5,"p_{T}(GeV/c)");
        
        TCanvas * c_l3_pt_CSVL = new TCanvas("c_b_pt_CSVL","c_b_pt_CSVL",500,500);
        eff_l1_pt_CSVL->SetMaximum(0.4);
        eff_l1_pt_CSVL->Draw("e3");
        eff_l2_pt_CSVL->Draw("e3 same");
        eff_l3_pt_CSVL->Draw("e3 same");
        eff_l4_pt_CSVL->Draw("e3 same");
        
        TLegend *l = new TLegend(0.42,0.76,0.89,0.87);
        l->AddEntry(eff_l1_pt_CSVL,"l-flavor  #eta #leq 0.5","F");
        l->AddEntry(eff_l2_pt_CSVL,"l-flavor 0.5 < #eta #leq 1.0","F");
        l->AddEntry(eff_l3_pt_CSVL,"l-flavor 1.0 < #eta #leq 1.5","F");
        l->AddEntry(eff_l4_pt_CSVL,"l-flavor 1.5 < #eta","F");
        SetLegend(l);
        c_l3_pt_CSVL->Print("compare_l4_pt_CSVL.png");
        c_l3_pt_CSVL->Print("compare_l4_pt_CSVL.eps");
    }
    else if(jj==1)
    {
        TH1F* eff_l1_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacut1, csvm, "l1_pt_CSVM","CSVM",2,"p_{T}(GeV/c)"); 
        TH1F* eff_l2_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacut2, csvm, "l2_pt_CSVM","CSVM",4,"p_{T}(GeV/c)");
        TH1F* eff_l3_pt_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_pt", nBinpt, binspt, precut, precut_em, lcut+etacut3, csvm, "l3_pt_CSVM","CSVM",5,"p_{T}(GeV/c)");
        
        TCanvas * c_l3_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
        eff_l1_pt_CSVM->SetMaximum(0.1);
        eff_l1_pt_CSVM->Draw("e3");
        eff_l2_pt_CSVM->Draw("e3 same");
        eff_l3_pt_CSVM->Draw("e3 same");
        
        TLegend *l = new TLegend(0.42,0.76,0.89,0.87);
        l->AddEntry(eff_l1_pt_CSVM,"l-flavor #eta #leq 0.8","F");
        l->AddEntry(eff_l2_pt_CSVM,"l-flavor 0.8 < #eta #leq 1.6","F");
        l->AddEntry(eff_l3_pt_CSVM,"l-flavor 1.6 < #eta","F");
        SetLegend(l);
        c_l3_pt_CSVM->Print("compare_l3_pt_CSVM.png");
        c_l3_pt_CSVM->Print("compare_l3_pt_CSVM.eps");
    }
 }
 else if(ii==1)
 {
    TH1F* eff_b_eta_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, bcut, csvl, "b_eta_CSVL","CSVL",2, "#eta"); 
    TH1F* eff_c_eta_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, ccut, csvl, "c_eta_CSVL","CSVL",4, "#eta");
    TH1F* eff_l_eta_CSVL = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, lcut, csvl, "l_eta_CSVL","CSVL",5, "#eta");

    TH1F* eff_b_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, bcut, csvm, "b_eta_CSVM","CSVM",2, "#eta"); 
    TH1F* eff_b_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, bcut, csvt, "b_eta_CSVT","CSVT",2, "#eta"); 

    TH1F* eff_c_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, ccut, csvm, "c_eta_CSVM","CSVM",4, "#eta");
    TH1F* eff_c_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, ccut, csvt, "c_eta_CSVT","CSVT",4, "#eta");

    TH1F* eff_l_eta_CSVM = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, lcut, csvm, "l_eta_CSVM","CSVM",5, "#eta");
    TH1F* eff_l_eta_CSVT = eff(treeElEl, treeMuMu, treeMuEl, "jets_eta", nBineta, binseta, precut, precut_em, lcut, csvt, "l_eta_CSVT","CSVT",5, "#eta");

    TCanvas * c_b_eta_CSVL = new TCanvas("c_b_eta_CSVL","c_b_eta_CSVL",500,500);
    eff_b_eta_CSVL->Draw("e3");
    eff_c_eta_CSVL->Draw("e3 same");
    eff_l_eta_CSVL->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVL,"b-flavor","F");
    l->AddEntry(eff_c_eta_CSVL,"c-flavor","F");
    l->AddEntry(eff_l_eta_CSVL,"l-flavor","F");
    SetLegend(l);
    c_b_eta_CSVL->Print("compare_b_eta_CSVL.png");
    c_b_eta_CSVL->Print("compare_b_eta_CSVL.eps");


    TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
    eff_b_eta_CSVM->Draw("e3");
    eff_c_eta_CSVM->Draw("e3 same");
    eff_l_eta_CSVM->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVM,"b-flavor","F");
    l->AddEntry(eff_c_eta_CSVM,"c-flavor","F");
    l->AddEntry(eff_l_eta_CSVM,"l-flavor","F");
    SetLegend(l);
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.png");
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.eps");

    TCanvas * c_b_eta_CSVT = new TCanvas("c_b_eta_CSVT","c_b_eta_CSVT",500,500);
    eff_b_eta_CSVT->Draw("e3");
    eff_c_eta_CSVT->Draw("e3 same");
    eff_l_eta_CSVT->Draw("e3 same");

    TLegend *l = new TLegend(0.68,0.76,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVT,"b-flavor","F");
    l->AddEntry(eff_c_eta_CSVT,"c-flavor","F");
    l->AddEntry(eff_l_eta_CSVT,"l-flavor","F");
    SetLegend(l);
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.png");
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.eps");
  }

}

TH1F* eff(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int nBin, float * bins, TCut precut, TCut precut_em, TCut fcut, TCut wcut, const TString & name, const TString & tagName, int color, const TString & xtitle){

  TCut dencut_em =  precut_em + fcut;
  TCut dencut    =  precut    + fcut;
  TCut numcut_em =  dencut_em + wcut;
  TCut numcut    =  dencut    + wcut;

  TH1F* h_eff = new TH1F(Form("h_eff_%s",name.Data()),"h_eff",nBin,bins);

  TH1F* hden = new TH1F(Form("hden_%s",name.Data()),"hden",nBin,bins);
  TH1F* hnum = new TH1F(Form("hnum_%s",name.Data()),"hnum",nBin,bins);

  TH1F* hden_ee = new TH1F(Form("hden_%s_ee",name.Data()),"hden_ee",nBin,bins);
  TH1F* hnum_ee = new TH1F(Form("hnum_%s_ee",name.Data()),"hnum_ee",nBin,bins);

  TH1F* hden_mm = new TH1F(Form("hden_%s_mm",name.Data()),"hden_mm",nBin,bins);
  TH1F* hnum_mm = new TH1F(Form("hnum_%s_mm",name.Data()),"hnum_mm",nBin,bins);

  TH1F* hden_em = new TH1F(Form("hden_%s_em",name.Data()),"hden_em",nBin,bins);
  TH1F* hnum_em = new TH1F(Form("hnum_%s_em",name.Data()),"hnum_em",nBin,bins);

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeElEl->Project(Form("hnum_%s_ee",name.Data()),Form("%s",variable.Data()),numcut,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeMuMu->Project(Form("hnum_%s_mm",name.Data()),Form("%s",variable.Data()),numcut,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em,"");
  treeMuEl->Project(Form("hnum_%s_em",name.Data()),Form("%s",variable.Data()),numcut_em,"");

  hnum->Add(hnum_ee,1);
  hnum->Add(hnum_mm,1);
  hnum->Add(hnum_em,1);
  hden->Add(hden_ee,1);
  hden->Add(hden_mm,1);
  hden->Add(hden_em,1);

  TCanvas*  tag_eff = new TCanvas(Form("eff_%s",name.Data()),Form("eff_%s",name.Data()),500,500);
  h_eff->Sumw2();
  h_eff->SetStats(0);
  h_eff->SetTitle(Form("b-tagging efficiency (%s)",tagName.Data()));
  h_eff->Divide(hnum,hden,1,1,"B");
  TF1* function = new TF1("function","pol4");
  function->SetLineColor(color);
  h_eff->Fit(function);
  h_eff->SetMinimum(0.0);
  h_eff->SetMaximum(1.0);
  h_eff->GetXaxis()->SetTitle(xtitle);
  h_eff->GetYaxis()->SetTitle("Efficiency");
  h_eff->SetStats(0);
  //h_eff->Draw("AXIS");
  TH1F* h_effint = h_eff->Clone(); 
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_effint,0.68);
  h_effint->SetFillColor(color);
  h_effint->SetFillStyle(3005);
  h_effint->SetStats(0);
  h_effint->Draw("e3 same");

  tag_eff->Print(Form("eff_%s.png",name.Data()));
  return h_effint;

}

TH1F* dist(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int nBin, float * bins, TCut precut, TCut precut_em, TCut fcut, const TString & name, const TString & tagName, int color, const TString & xtitle){

  TCut dencut_em =  precut_em + fcut;
  TCut dencut    =  precut    + fcut;

  TH1F* h_eff = new TH1F(Form("h_eff_%s",name.Data()),"h_eff",nBin,bins);

  TH1F* hden = new TH1F(Form("hden_%s",name.Data()),"hden",nBin,bins);
  TH1F* hden_ee = new TH1F(Form("hden_%s_ee",name.Data()),"hden_ee",nBin,bins);
  TH1F* hden_mm = new TH1F(Form("hden_%s_mm",name.Data()),"hden_mm",nBin,bins);
  TH1F* hden_em = new TH1F(Form("hden_%s_em",name.Data()),"hden_em",nBin,bins);

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s",variable.Data()),dencut,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em,"");

  hden->Add(hden_ee,1);
  hden->Add(hden_mm,1);
  hden->Add(hden_em,1);

  //TCanvas*  tag_eff = new TCanvas(Form("eff_%s",name.Data()),Form("eff_%s",name.Data()),500,500);
  TH1F* h_effint = hden->Clone();
  h_effint->Scale(1/h_effint->Integral()); 
  h_effint->SetTitle(xtitle);

  h_effint->SetLineColor(color);
  h_effint->GetXaxis()->SetTitle(xtitle);
  h_effint->GetYaxis()->SetTitle("Normalized Entries");

  return h_effint;

}



void SetLegend(TLegend* l){
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}
