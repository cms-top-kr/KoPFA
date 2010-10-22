#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
//#include "TStyle.h"


void printEff(RooHist* h){
   for(int i=0 ; i < h->GetMaxSize() ; i++){
    double x;
    double y;
    double xerrhi = h->GetErrorXhigh(i);
    double xerrlo = h->GetErrorXlow(i);
    double yerrhi = h->GetErrorYhigh(i);
    double yerrlo = h->GetErrorYlow(i);
    double eff =  h->GetPoint(i,x,y);
    cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
  }
}

void setRangeY(TCanvas *c, double min=0, double max=1.1){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("TH1")) ((TH1*)o)->GetYaxis()->SetRangeUser(min,max);
  }
}

void plot2Eff(TFile *f1, TFile* f2, const TString & leg1, const TString & leg2, const TString& dir1, const TString &dir2, const TString& plot1, const TString & plot2, const TString& printName, const TString& hName){
  gStyle->SetPadTickX(1);

  f1->cd(dir1);
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(plot1)->ReadObj();
  //getObjects(c1);
  TString obj1="";
  if(dir1.Contains("cnt")) obj1 = "hxy_cnt_eff";
  else obj1 = "hxy_fit_eff";
  RooHist* h1 = (RooHist*) c1->FindObject(obj1);

  setRangeY(c1,0.5,1.1);
  h1->SetLineWidth(2);
  h1->SetLineColor(4);
  h1->SetMarkerColor(4);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.7);
  cout << "data-----" << plot1 << "---" << hName << "----" << endl;
  printEff(h1);

  f2->cd(dir2);
  TCanvas* c2 = (TCanvas*) gDirectory->FindKey(plot2)->ReadObj();
  TString obj2="";
  if(dir2.Contains("cnt")) obj2 = "hxy_cnt_eff";
  else obj2 = "hxy_fit_eff";
  RooHist* h2 = (RooHist*) c2->FindObject(obj2);
  
  setRangeY(c2,0.5,1.1); 
  h2->SetLineWidth(2);
  h2->SetLineColor(2);
  h2->SetMarkerColor(2);
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(0.7);

  cout << "MC-----" << plot2 << "---"<< hName << "---" << endl;
  printEff(h2);

  c1->Draw();
  h2->Draw("P Same");

  doLegend(h1, h2, leg1, leg2);
  c1->Print("c_"+printName+"_"+hName+".png");
  c1->Print("c_"+printName+"_"+hName+".eps");

}


void plotEff(TFile* f, const TString& dir, const TString& hName){
  TCanvas * c = (TCanvas *) f->Get(Form("%s",dir.Data()));
  getObjects(c);
  RooHist* h = (RooHist*) c->FindObject(Form("%s",hName.Data()));
  h->SetLineWidth(2);
  h->SetLineColor(4);
  h->SetMarkerColor(4);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.0);

  cout << "---" << plot << "---" << hName << "---" << endl;
  printEff(h);

  c->Draw();
}

void plot2DEff(TFile* f, TFile* f_MC, const TString& dir, const TString& plot, const TString& hName){
  gStyle->SetPalette(1);
  f->cd(dir);
  TCanvas* c = (TCanvas*) gDirectory->FindKey(plot)->ReadObj();
  TH2* h = (TH2F*) c->FindObject(plot);
  cout << "---" << plot << "---" << hName << "---" << endl;
  h->SetMarkerSize(2.5);

  c->Draw();
  c->Print("c_"+plot+"_"+hName+".png");
  c->Print("c_"+plot+"_"+hName+".eps");

  f_MC->cd(dir);
  TCanvas* c2 = (TCanvas*) gDirectory->FindKey(plot)->ReadObj();
  TH2* h2 = (TH2F*) c2->FindObject(plot);
  cout << "---" << plot << "---" << hName << "---" << endl;
  h2->SetMarkerSize(2.5);
  c2->Draw();  
  c2->Print("c_"+plot+"_"+hName+"_mc.png");
  c2->Print("c_"+plot+"_"+hName+"_mc.eps");


  int nbinx = h->GetNbinsX();
  int nbiny = h->GetNbinsY();
  for(int i=1; i <=nbinx ; i++){
    for(int j=1; j <=nbiny ; j++){  
      cout << "data  = " << "[" << i << "," << j << "] " << "eff= " << h->GetBinContent(i,j) << "( +- " << h->GetBinError(i,j) << " )" << endl;
      cout << "mc    = " << "[" << i << "," << j << "] " << "eff= " << h2->GetBinContent(i,j) << "( +- " << h2->GetBinError(i,j) << " )" << endl;
      double scale = h->GetBinContent(i,j)/h2->GetBinContent(i,j);
      double scale_err = h->GetBinError(i,j)/h2->GetBinContent(i,j);
      cout << "SCALE : " << scale << "( +- " << scale_err << " )" << endl;
    }
  }

}

void getObjects( TCanvas *c){

  TObject *obj;
  TIter next(c->GetListOfPrimitives());
  while ((obj=next())) {
    cout << "Reading: " << obj->GetName() << endl;
    if (obj->InheritsFrom("TH1")) {
      cout << "histo: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("RooHist")) {
      cout << "RooHisto: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("RooPlot")) {
      cout << "RooPlot: " << obj->GetName() << endl;
    }

  }
}


void doLegend(TGraphAsymmErrors *g1, TGraphAsymmErrors *g2, TString lab1, TString lab2) {
    TLegend *leg = new TLegend(.55,.15 ,.85,.45 );
    leg->AddEntry(g1, lab1, "LP");
    leg->AddEntry(g2, lab2, "LP");
    leg->SetFillColor(0);
    leg->SetTextSize(0.04);
    leg->SetLineColor(0);
    leg->Draw();
}

//void SetStyle(){
//  compStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
//  compStyle->SetPadTickY(1);
//  compStyle->cd();
//}

void plotTnP(){
  
  using namespace std;
  TFile * f = new TFile("result3/plot/Efficiency_ID.root");
  //TFile * f_MC = new TFile("result/plot/Efficiency_ID.root");
  TFile * f_MC = new TFile("result3/plot/Efficiency_ID_mc.root");
  TFile * f_MCUnbias = new TFile("result3/plot/Efficiency_ID_mcUnbias.root");

  TFile * f_Iso = new TFile("result3/plot/Efficiency_Iso.root");
  //TFile * f_Iso_MC = new TFile("result/plot/Efficiency_Iso.root");
  TFile * f_Iso_MC = new TFile("result3/plot/Efficiency_Iso_mc.root");
  TFile * f_Iso_MCUnbias = new TFile("result3/plot/Efficiency_Iso_mcUnbias.root");

  // Data vs MC
  cout << "Data vs MC" << endl;
  TString l1 = "Data";
  TString l2 = "MC";

  bool datavsmc = false;
  bool datavstruth = false;
  bool datavsunbiased = false;
  bool h2d = true;

  if( datavsmc ){
    plot2Eff(f,f_MC,l1,l2,"tnpTree/PF_abseta/fit_eff_plots","tnpTree/PF_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","PF");
    plot2Eff(f,f_MC,l1,l2,"tnpTree/PF_pt/fit_eff_plots","tnpTree/PF_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","PF");

    plot2Eff(f,f_MC,l1,l2,"tnpTree/ID_abseta/fit_eff_plots","tnpTree/ID_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","ID");
    plot2Eff(f,f_MC,l1,l2,"tnpTree/ID_pt/fit_eff_plots","tnpTree/ID_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","ID");

    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/abseta/fit_eff_plots","tnpTreeIso/abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","Iso");
    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/pt/fit_eff_plots","tnpTreeIso/pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","Iso");
  }
  // Data vs MC truth
  if( datavstruth ){ 
    cout << "Data vs MC truth" << endl;
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/PF_abseta/fit_eff_plots","tnpTree/PF_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","PF");
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/PF_pt/fit_eff_plots","tnpTree/PF_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","PF");

    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/ID_abseta/fit_eff_plots","tnpTree/ID_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","ID");
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/ID_pt/fit_eff_plots","tnpTree/ID_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","ID");

    plot2Eff(f_Iso,f_Iso_MC,"Data","MC truth","tnpTreeIso/abseta/fit_eff_plots","tnpTreeIso/abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","Iso");
    plot2Eff(f_Iso,f_Iso_MC,"Data","MC truth","tnpTreeIso/pt/fit_eff_plots","tnpTreeIso/pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","Iso");
  }
  // Data vs MC unbiased truth
  if( datavsunbiased =){
    cout << "Data vs MC unbiased truth" << endl;
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth ","tnpTree/PF_abseta/fit_eff_plots","tnpTree/PF_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","PF");
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/PF_pt/fit_eff_plots","tnpTree/PF_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","PF");

    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/ID_abseta/fit_eff_plots","tnpTree/ID_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","ID");
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/ID_pt/fit_eff_plots","tnpTree/ID_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","ID");

    plot2Eff(f_Iso,f_Iso_MCUnbias,"Data","MC(unbiased) truth","tnpTreeIso/abseta/fit_eff_plots","tnpTreeIso/abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","Iso");
    plot2Eff(f_Iso,f_Iso_MCUnbias,"Data","MC(unbiased) truth","tnpTreeIso/pt/fit_eff_plots","tnpTreeIso/pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","Iso");

  }

  if( h2d == true){
    //2D histograms
    plot2DEff(f, f_MC, "tnpTree/PF_pt_abseta/fit_eff_plots","pt_abseta_PLOT","PF");
    plot2DEff(f, f_MC, "tnpTree/ID_pt_abseta/fit_eff_plots","pt_abseta_PLOT","ID");
    plot2DEff(f_Iso, f_Iso_MC, "tnpTreeIso/pt_abseta/fit_eff_plots","pt_abseta_PLOT","Iso");
  }

}

