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
void bjet_pt(bool type, int i)
{
    gROOT->ProcessLine(".L tdrstyle.C");
    defaultStyle();
    TFile* f1 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v3/vallot_TTbarTuneZ2_btag.root");
    TFile* f2 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v3/vallot_TTbarTuneZ2_btag.root");
    TFile* f3 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v3/vallot_TTbarTuneZ2_btag.root");
	
    TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
    TTree* treeElEl = (TTree*)f2->Get("ElEl/tree");
    TTree* treeMuEl = (TTree*)f3->Get("MuEl/tree");
	
    float binspt[] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};//,260,270,280,290,300};//,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450};
    int nBinpt = sizeof(binspt)/sizeof(float) - 1;
    float binseta[] = {0.,0.4,0.8,1.2,1.6,2.0,2.4};
    int nBineta = sizeof(binseta)/sizeof(float) - 1;

    TCut ttjj = "nGenbJet20 >= 2 ";//&& nGenJet20 >= 4";
    TCut ttbb = "nGenbJet20 >= 4" + ttjj;
    TCut ttll = "nGenbJet20 < 4" + ttjj;

    TCut fromTop = "jetspt30fromtop ==1 ";
    TCut notfromTop = "jetspt30fromtop ==0";
	
    TCut precut_em =    "ZMass > 12 && isIso > 0 && PairSign < 0 && nJet30 >= 4";
    TCut precut = precut_em + "abs(ZMass - 91.2) > 15 && MET > 30"; 
    TCut bcut =  "abs(jetspt30flavor) == 5";
    TCut ccut =  "abs(jetspt30flavor) == 4";
    TCut csvm =  "jetspt30bDiscriminator > 0.679";
    TCut csvt =  "jetspt30bDiscriminator > 0.898";

    TCut tag[5];
     tag[0] = "abs(jetspt30.eta()) < 0.5";
     tag[1] = "abs(jetspt30.eta()) >= 0.5 && abs(jetspt30.eta()) < 1.0";
     tag[2] = "abs(jetspt30.eta()) >= 1.0 && abs(jetspt30.eta()) < 1.5";
     tag[3] = "abs(jetspt30.eta()) >= 1.5 && abs(jetspt30.eta()) < 2.0";
     tag[4] = "abs(jetspt30.eta()) >= 2.0 && abs(jetspt30.eta()) < 2.5";

if(type)
{
        TH2F* eff_b_pt_fromTop;  
        TH2F* eff_b_pt_notfromTop; 

        eff_b_pt_eta_fromTop =   distribution(treeElEl, treeMuMu, treeMuEl,  "abs(jetspt30.eta()):jetspt30.pt()", nBinpt, binspt,nBineta,binseta, precut, precut_em, bcut,  fromTop, Form("eff_b_pt_eta_fromTop"),"","p_{T}(GeV/c)", "#eta", " from top");
        eff_b_pt_eta_notfromTop = distribution(treeElEl, treeMuMu, treeMuEl, "abs(jetspt30.eta()):jetspt30.pt()", nBinpt, binspt,nBineta,binseta, precut, precut_em, bcut, notfromTop, Form("eff_b_pt_eta_notfromTop"),"","p_{T}(GeV/c)", "#eta", " not form top"); 

        gStyle->SetPalette(1);
        gStyle->SetPadRightMargin(0.18);

        double s1 = eff_b_pt_eta_fromTop->Integral();
        double s2 = eff_b_pt_eta_notfromTop->Integral();
 
        eff_b_pt_eta_fromTop->Scale(1/s1);
        eff_b_pt_eta_notfromTop->Scale(1/s2);

       // eff_b_pt_eta_fromTop->SetMaximum(0.085);
       // eff_b_pt_eta_notfromTop->SetMaximum(0.085);  
       
        TCanvas * c_b_pt = new TCanvas("c_b_pt","c_b_pt_eta_from_top",500,500);
        eff_b_pt_eta_fromTop->Draw("colz");
        c_b_pt->Print(Form("compare_b_pt_eta_from_Top.png"));
        c_b_pt->Print(Form("compare_b_pt_eta_from_Top.eps"));

        TCanvas * c_b_pt_not = new TCanvas("c_b_pt_not","c_b_pt_eta_not_from_top",500,500);
        eff_b_pt_eta_notfromTop->Draw("colz");
        c_b_pt_not->Print(Form("compare_b_pt_eta_not_from_Top.png"));
        c_b_pt_not->Print(Form("compare_b_pt_eta_not_from_Top.eps"));

}
//////////////////
else if(type && i>-1 )
{
    
    //for(int i=0;i<5;i++)
        TH1F* eff_b_pt_fromTop;  
        TH1F* eff_b_pt_notfromTop; 

        if(i==0)
        { 
           eff_b_pt_fromTop =   distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut+tag[i], precut_em, bcut,  fromTop, Form("eff_b_pt_fromTop_%d",i),"p_{T}","p_{T}(GeV/c)", Form("with |#eta| < %.1f",(i*5.+5.)/10.));
           eff_b_pt_notfromTop = distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut+tag[i], precut_em, bcut, notfromTop, Form("eff_b_pt_notfromTop_%d",i),"p_{T}","p_{T}(GeV/c)", Form("with |#eta| < %.1f",(i*5.+5.)/10.)); 
        }
        else {
           eff_b_pt_fromTop =   distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut+tag[i], precut_em, bcut,  fromTop, Form("eff_b_pt_fromTop_%d",i),"p_{T}","p_{T}(GeV/c)", Form("with %.1f #leq |#eta| < %.1f",(i*5./10.), (i*5.+5.)/10.));
           eff_b_pt_notfromTop = distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut+tag[i], precut_em, bcut, notfromTop, Form("eff_b_pt_notfromTop_%d",i),"p_{T}","p_{T}(GeV/c)", Form("with %.1f #leq |#eta| < %.1f",(i*5./10.), (i*5.+5.)/10.)); 
        }

       
        TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
       
        //eff_b_pt_fromTop->Sumw2();
        eff_b_pt_notfromTop->Sumw2();
       
        double s1 = eff_b_pt_fromTop->Integral();
        double s2 = eff_b_pt_notfromTop->Integral();
       
         eff_b_pt_fromTop->Scale(1/s1);
         eff_b_pt_notfromTop->Scale(1/s2);
       
        eff_b_pt_fromTop->SetLineColor(kRed);
        eff_b_pt_fromTop->SetFillColor(kRed);
       
        eff_b_pt_notfromTop->SetLineColor(kBlue);
        eff_b_pt_notfromTop->SetMarkerStyle(20);
        eff_b_pt_notfromTop->SetMarkerSize(1);
       
         eff_b_pt_fromTop->SetMaximum(0.4);
         eff_b_pt_fromTop->Draw();
         eff_b_pt_notfromTop->Draw("same");
       
        TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
        l->AddEntry(eff_b_pt_fromTop,"b from t","f");
        l->AddEntry(eff_b_pt_notfromTop,"b not from t","p");
       
        SetLegend(l);
        c_b_pt_CSVM->Print(Form("compare_b_pt_from_and_notfrom_Top_tag%d.png",i*5+5));
        c_b_pt_CSVM->Print(Form("compare_b_pt_from_and_notfrom_Top_tag%d.eps",i*5+5));
}
///////////////////////////////
else
{
        TH1F* eff_b_eta_fromTop= distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, fromTop, "eff_b_eta_fromTop","#eta","#eta","");
        TH1F* eff_b_eta_notfromTop = distribution(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, notfromTop, "eff_b_eta_notfromTop","#eta","#eta",""); 

        TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
       
        eff_b_eta_notfromTop->Sumw2();
       
        double s1 = eff_b_eta_fromTop->Integral();
        double s2 = eff_b_eta_notfromTop->Integral();
       
         eff_b_eta_fromTop->Scale(1/s1);
         eff_b_eta_notfromTop->Scale(1/s2);
       
        eff_b_eta_fromTop->SetLineColor(kRed);
        eff_b_eta_fromTop->SetFillColor(kRed);
       
        eff_b_eta_notfromTop->SetLineColor(kBlue);
        eff_b_eta_notfromTop->SetMarkerStyle(20);
        eff_b_eta_notfromTop->SetMarkerSize(1);
       
         eff_b_eta_fromTop->SetMaximum(0.4);
         eff_b_eta_fromTop->Draw();
         eff_b_eta_notfromTop->Draw("same");
       
        TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
        l->AddEntry(eff_b_eta_fromTop,"b from t","f");
        l->AddEntry(eff_b_eta_notfromTop,"b not from t","p");
       
        SetLegend(l);
        c_b_eta_CSVM->Print("compare_b_eta_from_and_notfrom_Top.png");
        c_b_eta_CSVM->Print("compare_b_eta_from_and_notfrom_Top.eps");

}
////////////////////////    

}



TH1F* distribution(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int nBin, float * bins, TCut precut, TCut precut_em, TCut fcut, TCut process,const TString & name, const TString &title, const TString &xtitle, const TString &with){

  TCut dencut_em =  precut_em + fcut;
  TCut dencut    =  precut    + fcut;


  TH1F* hden = new TH1F(Form("hden_%s",name.Data()),Form("%s distribution %s", title.Data(), with.Data()),nBin,bins);

  TH1F* hden_ee = new TH1F(Form("hden_%s_ee",name.Data()),"hden_ee",nBin,bins);
  TH1F* hden_mm = new TH1F(Form("hden_%s_mm",name.Data()),"hden_mm",nBin,bins);
  TH1F* hden_em = new TH1F(Form("hden_%s_em",name.Data()),"hden_em",nBin,bins);

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut+process,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s",variable.Data()),dencut+process,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em+process,"");

  hden->Add(hden_ee,1);
  hden->Add(hden_mm,1);
  hden->Add(hden_em,1);

  hden->GetXaxis()->SetTitle(xtitle);//"p_{T}(GeV/c)");
  hden->GetYaxis()->SetTitle("Normalized");

//  hden->Sumw2();
//  hden->SetLineColor(color);

 return hden;

}

TH2F* distribution(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int xnBin, float * xbins, int ynBin, float * ybins, TCut precut, TCut precut_em, TCut fcut, TCut process,const TString & name, const TString &title, const TString &xtitle, const TString &ytitle, const TString &with){

  TCut dencut_em =  precut_em + fcut;
  TCut dencut    =  precut    + fcut;


  TH2F* hden = new TH2F(Form("hden_%s",name.Data()),Form("b %s", with.Data()),xnBin,xbins, ynBin,ybins);

  TH2F* hden_ee = new TH2F(Form("hden_%s_ee",name.Data()),"hden_ee",xnBin,xbins, ynBin,ybins);
  TH2F* hden_mm = new TH2F(Form("hden_%s_mm",name.Data()),"hden_mm",xnBin,xbins, ynBin,ybins);
  TH2F* hden_em = new TH2F(Form("hden_%s_em",name.Data()),"hden_em",xnBin,xbins, ynBin,ybins);

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut+process,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s ",variable.Data()),dencut+process,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em+process,"");

  hden->Add(hden_ee,1);
  hden->Add(hden_mm,1);
  hden->Add(hden_em,1);

  hden->GetXaxis()->SetTitle(xtitle);//"p_{T}(GeV/c)");
  hden->GetYaxis()->SetTitle(ytitle);

//  hden->Sumw2();
//  hden->SetLineColor(color);

 return hden;

}



void SetLegend(TLegend* l){
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}
