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
void btagefficiency(bool type, bool type2, bool type3)
{
    gROOT->ProcessLine(".L tdrstyle.C");
    defaultStyle();
    TFile* f1 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v3/vallot_TTbarTuneZ2_btag.root");
    TFile* f2 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v3/vallot_TTbarTuneZ2_btag.root");
    TFile* f3 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v3/vallot_TTbarTuneZ2_btag.root");
	
    TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
    TTree* treeElEl = (TTree*)f2->Get("ElEl/tree");
    TTree* treeMuEl = (TTree*)f3->Get("MuEl/tree");
	
    float binspt[] = {20,30,40,50,60,70,80,100,120,160,210,260,320, 450};
    int nBinpt = sizeof(binspt)/sizeof(float) - 1;
    float binseta[] = {0.,0.4,0.8,1.2,1.6,2.0,2.4};
    int nBineta = sizeof(binseta)/sizeof(float) - 1;

    TCut tag0 = "nGenbJet20 == 0";
    TCut tag1 = "nGenbJet20 == 1";
    TCut tag2 = "nGenbJet20 == 2";
    TCut tag3 = "nGenbJet20 == 3";
    TCut tag4 = "nGenbJet20 >= 4";

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

//    bool type=true, type2=false;
//////////
   bool type4=false;
if(type==false && type2 ==false && type3==false)
{

    TH1F* eff_b_pt_CSVM_fromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, fromTop, "b_pt_CSVM_fromTop","CSVM",4,"p_{T}(GeV/c)",3395);
    TH1F* eff_b_pt_CSVM_notfromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, notfromTop, "b_pt_CSVM_notfromTop","CSVM",6,"p_{T}(GeV/c)",3010); 

    TH1F* eff_b_pt_CSVT_fromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, fromTop, "b_pt_CSVT_fromTop","CSVT",4,"p_{T}(GeV/c)",3395);
    TH1F* eff_b_pt_CSVT_notfromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, notfromTop, "b_pt_CSVT_notfromTop","CSVT",6,"p_{T}(GeV/c)",3010); 
 
    TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
    eff_b_pt_CSVM_fromTop->Draw("e3");
    eff_b_pt_CSVM_notfromTop->Draw("e3 same");

    TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVM_fromTop,"b from t","F");
    l->AddEntry(eff_b_pt_CSVM_notfromTop,"b not from t","F");

    SetLegend(l);
    c_b_pt_CSVM->Print("compare_b_pt_CSVM_Top.png");
    c_b_pt_CSVM->Print("compare_b_pt_CSVM_Top.eps");

    TCanvas * c_b_pt_CSVT = new TCanvas("c_b_pt_CSVT","c_b_pt_CSVT",500,500);
    eff_b_pt_CSVT_fromTop->Draw("e3");
    eff_b_pt_CSVT_notfromTop->Draw("e3 same");

    TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
    l->AddEntry(eff_b_pt_CSVT_fromTop,"b from t","F");
    l->AddEntry(eff_b_pt_CSVT_notfromTop,"b not from t","F");

    SetLegend(l);
    c_b_pt_CSVT->Print("compare_b_pt_CSVT_Top.png");
    c_b_pt_CSVT->Print("compare_b_pt_CSVT_Top.eps");
}
else{
////////
TH1F* eff_b_eta_CSVM_fromTop= eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, csvm, fromTop, "b_eta_CSVM_fromTop","CSVM",4,"#eta",3395);
TH1F* eff_b_eta_CSVM_notfromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, csvm, notfromTop, "b_eta_CSVM_notfromTop","CSVM",6,"#eta",3010); 

TH1F* eff_b_eta_CSVT_fromTop= eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, csvt, fromTop, "b_eta_CSVT_fromTop","CSVT",4,"#eta",3395);
TH1F* eff_b_eta_CSVT_notfromTop = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.eta()", nBineta, binseta, precut, precut_em, bcut, csvt, notfromTop, "b_eta_CSVT_notfromTop","CSVT",6,"#eta",3010); 
 
    TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
    eff_b_eta_CSVM_fromTop->Draw("e3");
    eff_b_eta_CSVM_notfromTop->Draw("e3 same");

    TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVM_fromTop,"b from t","F");
    l->AddEntry(eff_b_eta_CSVM_notfromTop,"b not from t","F");

    SetLegend(l);
    c_b_eta_CSVM->Print("compare_b_eta_CSVM_Top.png");
    c_b_eta_CSVM->Print("compare_b_eta_CSVM_Top.eps");

    TCanvas * c_b_eta_CSVT = new TCanvas("c_b_eta_CSVT","c_b_eta_CSVT",500,500);
    eff_b_eta_CSVT_fromTop->Draw("e3");
    eff_b_eta_CSVT_notfromTop->Draw("e3 same");

    TLegend *l = new TLegend(0.62,0.75,0.89,0.87);
    l->AddEntry(eff_b_eta_CSVT_fromTop,"b from t","F");
    l->AddEntry(eff_b_eta_CSVT_notfromTop,"b not from t","F");

    SetLegend(l);
    c_b_eta_CSVT->Print("compare_b_eta_CSVT_Top.png");
    c_b_eta_CSVT->Print("compare_b_eta_CSVT_Top.eps");

}

//if(type4)
if(type)
{
if(type2)
{
if(type3)
{
 //   TH1F* eff_b_pt_CSVM_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, tag0, "b_pt_CSVM_tag0","CSVM",2, "p_{T}(GeV/c)",3005); 
//    TH1F* eff_b_pt_CSVM_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, tag1, "b_pt_CSVM_tag1","CSVM",3, "p_{T}(GeV/c)",3004); 
    TH1F* eff_b_pt_CSVM_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, tag2, "b_pt_CSVM_tag2","CSVM",4,"p_{T}(GeV/c)",3395); 
    TH1F* eff_b_pt_CSVM_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, tag3, "b_pt_CSVM_tag3","CSVM",6,"p_{T}(GeV/c)",3010); 
    TH1F* eff_b_pt_CSVM_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, tag4, "b_pt_CSVM_tag4","CSVM",12,"p_{T}(GeV/c)",3012); 

//    TH1F* eff_b_pt_CSVT_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, tag0, "b_pt_CSVT_tag0","CSVT",2, "p_{T}(GeV/c)",3005); 
//    TH1F* eff_b_pt_CSVT_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, tag1, "b_pt_CSVT_tag1","CSVT",3, "p_{T}(GeV/c)",3004); 
    TH1F* eff_b_pt_CSVT_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, tag2, "b_pt_CSVT_tag2","CSVT",4,"p_{T}(GeV/c)",3395); 
    TH1F* eff_b_pt_CSVT_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, tag3, "b_pt_CSVT_tag3","CSVT",6,"p_{T}(GeV/c)",3010); 
    TH1F* eff_b_pt_CSVT_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, tag4, "b_pt_CSVT_tag4","CSVT",12,"p_{T}(GeV/c)",3012); 

    TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
 //   eff_b_pt_CSVM_tag0->Draw("e3");
//    eff_b_pt_CSVM_tag1->Draw("e3 same");
    eff_b_pt_CSVM_tag2->Draw("e3");
    eff_b_pt_CSVM_tag3->Draw("e3 same");
    eff_b_pt_CSVM_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
 //   l->AddEntry(eff_b_pt_CSVM_tag0,"tt + 0jet","F");
 //   l->AddEntry(eff_b_pt_CSVM_tag1,"tt + 1jet","F");
    l->AddEntry(eff_b_pt_CSVM_tag2,"2bjets","F");
    l->AddEntry(eff_b_pt_CSVM_tag3,"3bjets","F");
    l->AddEntry(eff_b_pt_CSVM_tag4,"4bjets","F");

    SetLegend(l);
    c_b_pt_CSVM->Print("Ncompare_b_pt_CSVM_tag.png");
    c_b_pt_CSVM->Print("Ncompare_b_pt_CSVM_tag.eps");

    TCanvas * c_b_pt_CSVT = new TCanvas("c_b_pt_CSVT","c_b_pt_CSVT",500,500);
//    eff_b_pt_CSVT_tag0->Draw("e3");
//    eff_b_pt_CSVT_tag1->Draw("e3 same");
    eff_b_pt_CSVT_tag2->Draw("e3");
    eff_b_pt_CSVT_tag3->Draw("e3 same");
    eff_b_pt_CSVT_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
//    l->AddEntry(eff_b_pt_CSVT_tag0,"0bjets","F");
//    l->AddEntry(eff_b_pt_CSVT_tag1,"1bjets","F");
    l->AddEntry(eff_b_pt_CSVT_tag2,"2bjets","F");
    l->AddEntry(eff_b_pt_CSVT_tag3,"3bjets","F");
    l->AddEntry(eff_b_pt_CSVT_tag4,"4bjets","F");

    SetLegend(l);
    c_b_pt_CSVT->Print("Ncompare_b_pt_CSVT_tag.png");
    c_b_pt_CSVT->Print("Ncompare_b_pt_CSVT_tag.eps");

}
else
{
/////////////////

    //TH1F* eff_c_pt_CSVM_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, tag0, "c_pt_CSVM_tag0","CSVM",2, "p_{T}(GeV/c)",3005); 
    TH1F* eff_c_pt_CSVM_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, tag1, "c_pt_CSVM_tag1","CSVM",3, "p_{T}(GeV/c)",3004); 
    TH1F* eff_c_pt_CSVM_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, tag2, "c_pt_CSVM_tag2","CSVM",4,"p_{T}(GeV/c)",3395); 
//    TH1F* eff_c_pt_CSVM_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, tag3, "c_pt_CSVM_tag3","CSVM",6,"p_{T}(GeV/c)",3010); 
//    TH1F* eff_c_pt_CSVM_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, tag4, "c_pt_CSVM_tag4","CSVM",12,"p_{T}(GeV/c)",3012); 

    //TH1F* eff_c_pt_CSVT_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, tag0, "c_pt_CSVT_tag0","CSVT",2, "p_{T}(GeV/c)",3005); 
    TH1F* eff_c_pt_CSVT_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, tag1, "c_pt_CSVT_tag1","CSVT",3, "p_{T}(GeV/c)",3004); 
    TH1F* eff_c_pt_CSVT_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, tag2, "c_pt_CSVT_tag2","CSVT",4,"p_{T}(GeV/c)",3395); 
//    TH1F* eff_c_pt_CSVT_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, tag3, "c_pt_CSVT_tag3","CSVT",6,"p_{T}(GeV/c)",3010); 
//    TH1F* eff_c_pt_CSVT_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, tag4, "c_pt_CSVT_tag4","CSVT",12,"p_{T}(GeV/c)",3012); 

    TCanvas * c_c_pt_CSVM = new TCanvas("c_c_pt_CSVM","c_c_pt_CSVM",500,500);
 //   eff_c_pt_CSVM_tag0->Draw("e3");
    eff_c_pt_CSVM_tag1->Draw("e3");// same");
    eff_c_pt_CSVM_tag2->Draw("e3 same");
//    eff_c_pt_CSVM_tag3->Draw("e3 same");
//    eff_c_pt_CSVM_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
//    l->AddEntry(eff_c_pt_CSVM_tag0,"0bjets","F");
    l->AddEntry(eff_c_pt_CSVM_tag1,"1bjets","F");
    l->AddEntry(eff_c_pt_CSVM_tag2,"2bjets","F");
  //  l->AddEntry(eff_c_pt_CSVM_tag3,"3bjets","F");
  //  l->AddEntry(eff_c_pt_CSVM_tag4,"4bjets","F");

    SetLegend(l);
    c_c_pt_CSVM->Print("Ncompare_c_pt_CSVM_tag.png");
    c_c_pt_CSVM->Print("Ncompare_c_pt_CSVM_tag.eps");

    TCanvas * c_c_pt_CSVT = new TCanvas("c_c_pt_CSVT","c_c_pt_CSVT",500,500);
//    eff_c_pt_CSVT_tag0->Draw("e3");
    eff_c_pt_CSVT_tag1->Draw("e3");// same");
    eff_c_pt_CSVT_tag2->Draw("e3 same");
//    eff_c_pt_CSVT_tag3->Draw("e3 same");
//    eff_c_pt_CSVT_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
 //   l->AddEntry(eff_c_pt_CSVT_tag0,"0bjets","F");
    l->AddEntry(eff_c_pt_CSVT_tag1,"1bjets","F");
    l->AddEntry(eff_c_pt_CSVT_tag2,"2bjets","F");
 //   l->AddEntry(eff_c_pt_CSVT_tag3,"3bjets","F");
 //   l->AddEntry(eff_c_pt_CSVT_tag4,"tt + 4jets","F");

    SetLegend(l);
    c_c_pt_CSVT->Print("Ncompare_c_pt_CSVT_tag.png");
    c_c_pt_CSVT->Print("Ncompare_c_pt_CSVT_tag.eps");
}
}
else
{
if(type3)
{
//////////////////////////////////////////////////////////////////////////////////////
// TH1F* eff_b_eta_CSVM_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, tag0, "b_eta_CSVM_tag0","CSVM",2, "#eta",3005);
// TH1F* eff_b_eta_CSVM_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, tag1, "b_eta_CSVM_tag1","CSVM",3, "#eta",3004);
   TH1F* eff_b_eta_CSVM_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, tag2, "b_eta_CSVM_tag2","CSVM",4, "#eta",3395);
   TH1F* eff_b_eta_CSVM_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, tag3, "b_eta_CSVM_tag3","CSVM",6, "#eta",3010);
   TH1F* eff_b_eta_CSVM_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, tag4, "b_eta_CSVM_tag4","CSVM",12,"#eta",3012); 
// TH1F* eff_b_eta_CSVT_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, tag0, "b_eta_CSVT_tag0","CSVT",2, "#eta",3005);
// TH1F* eff_b_eta_CSVT_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, tag1, "b_eta_CSVT_tag1","CSVT",3, "#eta",3004);
   TH1F* eff_b_eta_CSVT_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, tag2, "b_eta_CSVT_tag2","CSVT",4, "#eta",3395);
   TH1F* eff_b_eta_CSVT_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, tag3, "b_eta_CSVT_tag3","CSVT",6, "#eta",3010);
   TH1F* eff_b_eta_CSVT_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, tag4, "b_eta_CSVT_tag4","CSVT",12,"#eta",3012);

    TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
  //  eff_b_eta_CSVM_tag0->Draw("e3");
  //  eff_b_eta_CSVM_tag1->Draw("e3 same");
    eff_b_eta_CSVM_tag2->Draw("e3");
    eff_b_eta_CSVM_tag3->Draw("e3 same");
    eff_b_eta_CSVM_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
   // l->AddEntry(eff_b_eta_CSVM_tag0,"tt + 0jet","F");
   // l->AddEntry(eff_b_eta_CSVM_tag1,"tt + 1jet","F");
    l->AddEntry(eff_b_eta_CSVM_tag2,"2bjets","F");
    l->AddEntry(eff_b_eta_CSVM_tag3,"3bjets","F");
    l->AddEntry(eff_b_eta_CSVM_tag4,"4bjets","F");

    SetLegend(l);
    c_b_eta_CSVM->Print("Ncompare_b_eta_CSVM_tag.png");
    c_b_eta_CSVM->Print("Ncompare_b_eta_CSVM_tag.eps");

    TCanvas * c_b_eta_CSVT = new TCanvas("c_b_eta_CSVT","c_b_eta_CSVT",500,500);
    //eff_b_eta_CSVT_tag0->Draw("e3");
    //eff_b_eta_CSVT_tag1->Draw("e3 same");
    eff_b_eta_CSVT_tag2->Draw("e3");
    eff_b_eta_CSVT_tag3->Draw("e3 same");
    eff_b_eta_CSVT_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
   // l->AddEntry(eff_b_eta_CSVT_tag0,"tt + 0jet","F");
   // l->AddEntry(eff_b_eta_CSVT_tag1,"tt + 1jet","F");
    l->AddEntry(eff_b_eta_CSVT_tag2,"2bjets","F");
    l->AddEntry(eff_b_eta_CSVT_tag3,"3bjets","F");
    l->AddEntry(eff_b_eta_CSVT_tag4,"4bjets","F");

    SetLegend(l);
    c_b_eta_CSVT->Print("Ncompare_b_eta_CSVT_tag.png");
    c_b_eta_CSVT->Print("Ncompare_b_eta_CSVT_tag.eps");
}
else
{
/////////////////
 //TH1F* eff_c_eta_CSVM_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, tag0, "c_eta_CSVM_tag0","CSVM",2, "#eta",3005);
   TH1F* eff_c_eta_CSVM_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, tag1, "c_eta_CSVM_tag1","CSVM",3, "#eta",3004);
   TH1F* eff_c_eta_CSVM_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, tag2, "c_eta_CSVM_tag2","CSVM",4, "#eta",3395);
// TH1F* eff_c_eta_CSVM_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, tag3, "c_eta_CSVM_tag3","CSVM",6, "#eta",3010);
// TH1F* eff_c_eta_CSVM_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, tag4, "c_eta_CSVM_tag4","CSVM",12,"#eta",3012);

//TH1F* eff_c_eta_CSVT_tag0 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, tag0, "c_eta_CSVT_tag0","CSVT",2, "#eta",3005); 
  TH1F* eff_c_eta_CSVT_tag1 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, tag1, "c_eta_CSVT_tag1","CSVT",3, "#eta",3004); 
  TH1F* eff_c_eta_CSVT_tag2 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, tag2, "c_eta_CSVT_tag2","CSVT",4, "#eta",3395); 
// TH1F* eff_c_eta_CSVT_tag3 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, tag3, "c_eta_CSVT_tag3","CSVT",6, "#eta",3010);
// TH1F* eff_c_eta_CSVT_tag4 = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, tag4, "c_eta_CSVT_tag4","CSVT",12,"#eta",3012); 
    TCanvas * c_c_eta_CSVM = new TCanvas("c_c_eta_CSVM","c_c_eta_CSVM",500,500);
    //eff_c_eta_CSVM_tag0->Draw("e3");
    eff_c_eta_CSVM_tag1->Draw("e3");// same");
    eff_c_eta_CSVM_tag2->Draw("e3 same");
//    eff_c_eta_CSVM_tag3->Draw("e3 same");
//    eff_c_eta_CSVM_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //l->AddEntry(eff_c_eta_CSVM_tag0,"0bjets","F");
    l->AddEntry(eff_c_eta_CSVM_tag1,"1bjets","F");
    l->AddEntry(eff_c_eta_CSVM_tag2,"2bjets","F");
//    l->AddEntry(eff_c_eta_CSVM_tag3,"3bjet","F");
//    l->AddEntry(eff_c_eta_CSVM_tag4,"4bjets","F");

    SetLegend(l);
    c_c_eta_CSVM->Print("Ncompare_c_eta_CSVM_tag.png");
    c_c_eta_CSVM->Print("Ncompare_c_eta_CSVM_tag.eps");

    TCanvas * c_c_eta_CSVT = new TCanvas("c_c_eta_CSVT","c_c_eta_CSVT",500,500);
    //eff_c_eta_CSVT_tag0->Draw("e3");
    eff_c_eta_CSVT_tag1->Draw("e3");// same");
    eff_c_eta_CSVT_tag2->Draw("e3 same");
//    eff_c_eta_CSVT_tag3->Draw("e3 same");
//    eff_c_eta_CSVT_tag4->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
   // l->AddEntry(eff_c_eta_CSVT_tag0,"0bjets","F");
    l->AddEntry(eff_c_eta_CSVT_tag1,"1bjets","F");
    l->AddEntry(eff_c_eta_CSVT_tag2,"2bjets","F");
   // l->AddEntry(eff_c_eta_CSVT_tag3,"3bjets","F");
   // l->AddEntry(eff_c_eta_CSVT_tag4,"4bjets","F");

    SetLegend(l);
    c_c_eta_CSVT->Print("Ncompare_c_eta_CSVT_tag.png");
    c_c_eta_CSVT->Print("Ncompare_c_eta_CSVT_tag.eps");

}
}
}
else
{
if(type3=true) if(type2)
{
///////////////////////////////////////
   
    TH1F* eff_b_pt_CSVM_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, ttbb, "b_pt_CSVM_ttbb","CSVM",2, "p_{T}(GeV/c)",3005); 
    TH1F* eff_b_pt_CSVM_ttll = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, ttll, "b_pt_CSVM_ttll","CSVM",4, "p_{T}(GeV/c)",3004); 
    TH1F* eff_b_pt_CSVM_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvm, ttjj, "b_pt_CSVM_ttjj","CSVM",12,"p_{T}(GeV/c)",3395); 
                                                                                                                                                                                     
    TH1F* eff_b_pt_CSVT_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, ttbb, "b_pt_CSVT_ttbb","CSVT",2, "p_{T}(GeV/c)",3005); 
    TH1F* eff_b_pt_CSVT_ttll = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, ttll, "b_pt_CSVT_ttll","CSVT",4, "p_{T}(GeV/c)",3004); 
    TH1F* eff_b_pt_CSVT_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, bcut, csvt, ttjj, "b_pt_CSVT_ttjj","CSVT",12,"p_{T}(GeV/c)",3995); 

   TH1F* eff_b_eta_CSVM_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, ttbb, "b_eta_CSVM_ttbb","CSVM",2,"#eta",3005); 
   TH1F* eff_b_eta_CSVM_ttll = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, ttll, "b_eta_CSVM_ttll","CSVM",4,"#eta",3004); 
   TH1F* eff_b_eta_CSVM_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvm, ttjj, "b_eta_CSVM_ttjj","CSVM",12,"#eta",3395); 
   TH1F* eff_b_eta_CSVT_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, ttbb, "b_eta_CSVT_ttbb","CSVT",2,"#eta",3005);
   TH1F* eff_b_eta_CSVT_ttll = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, ttll, "b_eta_CSVT_ttll","CSVT",4,"#eta",3004);
   TH1F* eff_b_eta_CSVT_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, bcut, csvt, ttjj, "b_eta_CSVT_ttjj","CSVT",12,"#eta",3995);

    TCanvas * c_b_pt_CSVM = new TCanvas("c_b_pt_CSVM","c_b_pt_CSVM",500,500);
    eff_b_pt_CSVM_ttbb->Draw("e3");
    eff_b_pt_CSVM_ttll->Draw("e3 same");
    eff_b_pt_CSVM_ttjj->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    l->AddEntry(eff_b_pt_CSVM_ttbb,"tt + bb","F");
    l->AddEntry(eff_b_pt_CSVM_ttll,"tt + LF","F");
    l->AddEntry(eff_b_pt_CSVM_ttjj,"tt + jj","F");
    SetLegend(l);
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.png");
    c_b_pt_CSVM->Print("compare_b_pt_CSVM.eps");

    TCanvas * c_b_pt_CSVT = new TCanvas("c_b_pt_CSVT","c_b_pt_CSVT",500,500);
    eff_b_pt_CSVT_ttbb->Draw("e3");
    eff_b_pt_CSVT_ttll->Draw("e3 same");
    eff_b_pt_CSVT_ttjj->Draw("e3 same");

    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    l->AddEntry(eff_b_pt_CSVT_ttbb,"tt + bb","F");
    l->AddEntry(eff_b_pt_CSVT_ttll,"tt + LF","F");
    l->AddEntry(eff_b_pt_CSVT_ttjj,"tt + jj","F");
    SetLegend(l);
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.png");
    c_b_pt_CSVT->Print("compare_b_pt_CSVT.eps");
//////////////
    TCanvas * c_b_eta_CSVM = new TCanvas("c_b_eta_CSVM","c_b_eta_CSVM",500,500);
    eff_b_eta_CSVM_ttbb->Draw("e3");
    eff_b_eta_CSVM_ttll->Draw("e3 same");
    eff_b_eta_CSVM_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    l->AddEntry(eff_b_eta_CSVM_ttbb,"tt + bb","F");
    l->AddEntry(eff_b_eta_CSVM_ttll,"tt + LF","F");
    l->AddEntry(eff_b_eta_CSVM_ttjj,"tt + jj","F");
    SetLegend(l);
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.png");
    c_b_eta_CSVM->Print("compare_b_eta_CSVM.eps");

    TCanvas * c_b_eta_CSVT = new TCanvas("c_b_eta_CSVT","c_b_eta_CSVT",500,500);
    eff_b_eta_CSVT_ttbb->Draw("e3");
    eff_b_eta_CSVT_ttll->Draw("e3 same");
    eff_b_eta_CSVT_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    l->AddEntry(eff_b_eta_CSVT_ttbb,"tt + bb","F");
    l->AddEntry(eff_b_eta_CSVT_ttll,"tt + LF","F");
    l->AddEntry(eff_b_eta_CSVT_ttjj,"tt + jj","F");
    SetLegend(l);
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.png");
    c_b_eta_CSVT->Print("compare_b_eta_CSVT.eps");
}
else
{
    //we can not use ttbb for mis-tag rate.
    //TH1F* eff_c_pt_CSVM_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, ttbb, "c_pt_CSVM_ttbb","CSVM",2);
    TH1F* eff_c_pt_CSVM_ttll = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, ttll, "c_pt_CSVM_ttll","CSVM",4, "p_{T}(GeV/c)",3004);
    TH1F* eff_c_pt_CSVM_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvm, ttjj, "c_pt_CSVM_ttjj","CSVM",12,"p_{T}(GeV/c)",3395);

    //TH1F* eff_c_pt_CSVT_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, ttbb, "c_pt_CSVT_ttbb","CSVT",2);
    TH1F* eff_c_pt_CSVT_ttll = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, ttll, "c_pt_CSVT_ttll","CSVT",4, "p_{T}(GeV/c)",3004);
    TH1F* eff_c_pt_CSVT_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "jetspt30.pt()", nBinpt, binspt, precut, precut_em, ccut, csvt, ttjj, "c_pt_CSVT_ttjj","CSVT",12,"p_{T}(GeV/c)",3395);

  //TH1F* eff_c_eta_CSVM_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, ttbb, "c_eta_CSVM_ttbb","CSVM",2,"#eta",3005);
   TH1F* eff_c_eta_CSVM_ttll = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, ttll, "c_eta_CSVM_ttll","CSVM",4,"#eta",3004); 
   TH1F* eff_c_eta_CSVM_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvm, ttjj, "c_eta_CSVM_ttjj","CSVM",12,"#eta",3395); 
  //TH1F* eff_c_eta_CSVT_ttbb = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, ttbb, "c_eta_CSVT_ttbb","CSVT",2,"#eta",3005);
   TH1F* eff_c_eta_CSVT_ttll = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, ttll, "c_eta_CSVT_ttll","CSVT",4,"#eta",3004);
   TH1F* eff_c_eta_CSVT_ttjj = eff(treeElEl, treeMuMu, treeMuEl, "TMath::Abs(jetspt30.eta())", nBineta, binseta, precut, precut_em, ccut, csvt, ttjj, "c_eta_CSVT_ttjj","CSVT",12,"#eta",3995);


/////////////////////////////////////
    TCanvas * c_c_pt_CSVM = new TCanvas("c_c_pt_CSVM","c_c_pt_CSVM",500,500);
    //eff_c_pt_CSVM_ttbb->Draw("e3");
    eff_c_pt_CSVM_ttll->Draw("e3");
    eff_c_pt_CSVM_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    //l->AddEntry(eff_c_pt_CSVM_ttbb,"tt + bb","F");
    l->AddEntry(eff_c_pt_CSVM_ttll,"tt + LF","F");
    l->AddEntry(eff_c_pt_CSVM_ttjj,"tt + jj","F");
    SetLegend(l);
    c_c_pt_CSVM->Print("compare_c_pt_CSVM.png");
    c_c_pt_CSVM->Print("compare_c_pt_CSVM.eps");

    TCanvas * c_c_pt_CSVT = new TCanvas("c_c_pt_CSVT","c_c_pt_CSVT",500,500);
    //eff_c_pt_CSVT_ttbb->Draw("e3");
    eff_c_pt_CSVT_ttll->Draw("e3");
    eff_c_pt_CSVT_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    //l->AddEntry(eff_c_pt_CSVT_ttbb,"tt + bb","F");
    l->AddEntry(eff_c_pt_CSVT_ttll,"tt + LF","F");
    l->AddEntry(eff_c_pt_CSVT_ttjj,"tt + jj","F");
    SetLegend(l);
    c_c_pt_CSVT->Print("compare_c_pt_CSVT.png"); 
    c_c_pt_CSVT->Print("compare_c_pt_CSVT.eps"); 

///////////////////////////////////////////
    TCanvas * c_c_eta_CSVM = new TCanvas("c_c_eta_CSVM","c_c_eta_CSVM",500,500);
    //eff_c_eta_CSVM_ttbb->Draw("e3");
    eff_c_eta_CSVM_ttll->Draw("e3");
    eff_c_eta_CSVM_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    //l->AddEntry(eff_c_eta_CSVM_ttbb,"tt + bb","F");
    l->AddEntry(eff_c_eta_CSVM_ttll,"tt + LF","F");
    l->AddEntry(eff_c_eta_CSVM_ttjj,"tt + jj","F");
    SetLegend(l);
    c_c_eta_CSVM->Print("compare_c_eta_CSVM.png");
    c_c_eta_CSVM->Print("compare_c_eta_CSVM.eps");

    TCanvas * c_c_eta_CSVT = new TCanvas("c_c_eta_CSVT","c_c_eta_CSVT",500,500);
    //eff_c_eta_CSVT_ttbb->Draw("e3");
    eff_c_eta_CSVT_ttll->Draw("e3");
    eff_c_eta_CSVT_ttjj->Draw("e3 same");


    TLegend *l = new TLegend(0.78,0.70,0.89,0.87);
    //TLegend *l = new TLegend(0.58,0.78,0.69,0.87);
    //l->AddEntry(eff_c_eta_CSVT_ttbb,"tt + bb","F");
    l->AddEntry(eff_c_eta_CSVT_ttll,"tt + LF","F");
    l->AddEntry(eff_c_eta_CSVT_ttjj,"tt + jj","F");
    SetLegend(l);
    c_c_eta_CSVT->Print("compare_c_eta_CSVT.png"); 
    c_c_eta_CSVT->Print("compare_c_eta_CSVT.eps"); 

}
}
}

TH1F* eff(TTree* treeElEl, TTree* treeMuMu, TTree* treeMuEl, const TString &variable, int nBin, float * bins, TCut precut, TCut precut_em, TCut fcut, TCut wcut, TCut process, const TString & name, const TString & tagName, int color, const TString &xtitle, const int style){

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

  treeElEl->Project(Form("hden_%s_ee",name.Data()),Form("%s",variable.Data()),dencut+process,"");
  treeElEl->Project(Form("hnum_%s_ee",name.Data()),Form("%s",variable.Data()),numcut+process,"");
  treeMuMu->Project(Form("hden_%s_mm",name.Data()),Form("%s",variable.Data()),dencut+process,"");
  treeMuMu->Project(Form("hnum_%s_mm",name.Data()),Form("%s",variable.Data()),numcut+process,"");
  treeMuEl->Project(Form("hden_%s_em",name.Data()),Form("%s",variable.Data()),dencut_em+process,"");
  treeMuEl->Project(Form("hnum_%s_em",name.Data()),Form("%s",variable.Data()),numcut_em+process,"");

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
  h_eff->GetXaxis()->SetTitle(xtitle);//"p_{T}(GeV/c)");
  h_eff->GetYaxis()->SetTitle("Efficiency");
  h_eff->SetStats(0);
  //h_eff->Draw("AXIS");
  TH1F* h_effint = h_eff->Clone(); 
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_effint,0.68);
  h_effint->SetFillColor(color);
  h_effint->SetFillStyle(style);
  h_effint->SetStats(0);
  h_effint->Draw("e3 same");

//  h_effint->GetXaxis()->SetRange(h_effint->GetBinLowEdge(0), h_effint->GetBinCenter(nBin));

//  tag_eff->Print(Form("eff_%s.png",name.Data()));
  return h_effint;

}

void SetLegend(TLegend* l){
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}
