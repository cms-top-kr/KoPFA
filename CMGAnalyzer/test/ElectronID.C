#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include <TLegend.h>
#include <TLatex.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
//#include "norm.h"
#include "Samples.h"
#include "tdrstyle.h"

//TString dir_ = "";

void ElectronID()
{

 // gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();
  

  lumi_=10000.;
  dir_="ElectronAnalysis";
  TString location = "/afs/cern.ch/work/t/tjkim/public/store/electron/electrons2/nhits0";

  Samples *sample = new Samples();
  sample->Add(Sample( new TFile(Form("%s/vallot_Run2012ElEl.root",location.Data())) , "Run2012ElEl", "Data",     1 ));
  sample->Add(Sample( new TFile(Form("%s/vallot_TTbarTuneZ2.root",location.Data())) , "TTbarTuneZ2", "t#bar{t}", 2 , 225    ));
  sample->Add(Sample( new TFile(Form("%s/vallot_WJetsToLNu.root", location.Data())) , "WJetsToLNu",  "W+jets",   3 , 36257  ));
  sample->Add(Sample( new TFile(Form("%s/vallot_ZJets10To50.root",location.Data())) , "ZJets10To50", "Z+jets",   4 , 860, 4 ));
  sample->Add(Sample( new TFile(Form("%s/vallot_ZJets.root",      location.Data())) , "ZJets",       "Z+jets",   4 , 3503.71));

  TString name_ ="h_pt";//mvaTrigV0";
  const int ch=7;
  TString Ids[ch] = {"Preselection","IDPF","IDMVA","IDVeto","IDLoose","IDMedium","IDTight"};//,"IDMediumIso","IDTightIso","IDMediumIsoPF","IDTightIsoPF","IDPF"};
 /* std::vector<TH1F*> hSamples;
  std::vector<TString> hLabels;

  for(int i=0;i<ch;i++)
  {
     TH1F *h_barrel = (TH1F *) sample->plotSample(Form("Signal/%s/Barrel/%s", Ids[i].Data(), name_.Data()),"TTbarTuneZ2"); 
     TH1F *h_endcap = (TH1F *) sample->plotSample(Form("Signal/%s/Endcap/%s", Ids[i].Data(), name_.Data()),"TTbarTuneZ2");
     TH1F *hID = h_barrel;
     hID->Add(h_endcap);
     hSamples.push_back(hID);
     hLabels.push_back(Ids[i].Data());
  }

  sample->plotMulti("pt","p_{T} (GeV/c)","Entries", hSamples, hLabels);
*/

  TString name2_ ="h_mvaTrigV0";
  TH1F *h2_barrel = (TH1F *) sample->plotSample(Form("Signal/%s/Barrel/%s", Ids[0].Data(), name2_.Data()),"TTbarTuneZ2"); 
  TH1F *h2_endcap = (TH1F *) sample->plotSample(Form("Signal/%s/Endcap/%s", Ids[0].Data(), name2_.Data()),"TTbarTuneZ2");
  TH1F *hID2 = h2_barrel;
  hID2->Add(h2_endcap);

  TH1F *h2q_barrel = (TH1F *) sample->plotSub(Form("QCD/%s/Barrel/%s", Ids[0].Data(), name2_.Data())); 
  TH1F *h2q_endcap = (TH1F *) sample->plotSub(Form("QCD/%s/Endcap/%s", Ids[0].Data(), name2_.Data()));
  TH1F *hID2q = h2q_barrel;
  hID2q->Add(h2q_endcap);


/*  TCanvas * c_roc1 = new TCanvas(Form("c_roc1"),Form("c_roc1"),500,500);
  hID2->Draw();

  TCanvas * c_roc2 = new TCanvas(Form("c_roc2"),Form("c_roc2"),500,500);
  hID2q->Draw();
*/

  TCanvas * c_roc = new TCanvas(Form("c_roc"),Form("c_roc"),500,500);
  TGraphAsymmErrors * hroc = sample->ROC(hID2,hID2q);
  sample->Style( hroc, 1, 1);
  //hroc->SetMinimum(0.001);
  hroc->Draw("APL");

  double preSig = hID2->Integral();
  double preQCD = hID2q->Integral();
  double eff_S[4], eff_B[4];  

  for(int i=3;i<7;i++)
  {
     TH1F *h_barrel = (TH1F *) sample->plotSample(Form("Signal/%s/Barrel/%s", Ids[i].Data(), name2_.Data()),"TTbarTuneZ2");
     TH1F *h_endcap = (TH1F *) sample->plotSample(Form("Signal/%s/Endcap/%s", Ids[i].Data(), name2_.Data()),"TTbarTuneZ2");
     TH1F *hID = h_barrel;
     hID->Add(h_endcap);
     eff_S[i-3]= hID->Integral()/preSig;

     TH1F *hq_barrel = (TH1F *) sample->plotSub(Form("QCD/%s/Barrel/%s", Ids[i].Data(), name2_.Data()));
     TH1F *hq_endcap = (TH1F *) sample->plotSub(Form("QCD/%s/Endcap/%s", Ids[i].Data(), name2_.Data()));
     TH1F *hIDq = hq_barrel;
     hIDq->Add(hq_endcap);
     eff_B[i-3]= hIDq->Integral()/preQCD;
  }

  TGraph *hroc2 = new TGraph(4,eff_B,eff_S);
  sample->Style( hroc2,2, 2);
  hroc2->SetMarkerSize(1.5);
  hroc2->Draw("sameLP");

  double eff_Sv[4], eff_Bv[4];

  eff_Sv[0] = hID2->Integral(101,200)/preSig;
  eff_Bv[0] = hID2q->Integral(101,200)/preQCD;
  eff_Sv[1] = hID2->Integral(151,200)/preSig;
  eff_Bv[1] = hID2q->Integral(151,200)/preQCD;

  eff_Sv[2] = hID2->Integral(191,200)/preSig;
  eff_Bv[2] = hID2q->Integral(191,200)/preQCD;

  eff_Sv[3] = hID2->Integral(199,200)/preSig;
  eff_Bv[3] = hID2q->Integral(199,200)/preQCD;
 
 
  TGraph *hroc3 = new TGraph(4,eff_Bv,eff_Sv);
  sample->Style( hroc3,3, 3);
  hroc3->SetMarkerSize(1.5);
  hroc3->Draw("sameP");

  TLegend *l= new TLegend(0.6,0.5,0.87,0.67);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->AddEntry( hroc, "MVA ID", "LP" );
  l->AddEntry( hroc2, "Cutbased ID", "P" );
  
  l->Draw();

  
  c_roc->Print("c_roc_ID.eps");

  //sample->plotStack("Signal/IDPF/h_pt" , "pt", " pt; pt (GeV);Entries", 0.1, 10e7, true);

}

