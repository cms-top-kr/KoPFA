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
  h->SetMarkerSize(2.1);
  h->GetXaxis()->SetMoreLogLabels(true); 
  h->SetLabelOffset(0.0005);
  h->SetTitleOffset(1.08);
  c->SetLogx();
  c->Draw();
  c->Print("c_"+plot+"_"+hName+".png");
  c->Print("c_"+plot+"_"+hName+".eps");

  f_MC->cd(dir);
  TCanvas* c2 = (TCanvas*) gDirectory->FindKey(plot)->ReadObj();
  TH2* h2 = (TH2F*) c2->FindObject(plot);
  cout << "---" << plot << "---" << hName << "---" << endl;
  h2->SetMarkerSize(2.1);
  h2->GetXaxis()->SetMoreLogLabels(true);
  h2->SetLabelOffset(0.0005);
  h2->SetTitleOffset(1.08);
  c2->SetLogx();
  c2->Draw();  
  c2->Print("c_"+plot+"_"+hName+"_mc.png");
  c2->Print("c_"+plot+"_"+hName+"_mc.eps");


  int nbinx = h->GetNbinsX();
  int nbiny = h->GetNbinsY();
  for(int i=1; i <=nbinx ; i++){
    for(int j=1; j <=nbiny ; j++){  
      cout << "data  = " << "[ pt bin= " << i << ", eta bin= " << j << "] " << "eff= " << h->GetBinContent(i,j) << "( +- " << h->GetBinError(i,j) << " )" << endl;
      cout << "mc    = " << "[ pt bin= " << i << ", eta bin= " << j << "] " << "eff= " << h2->GetBinContent(i,j) << "( +- " << h2->GetBinError(i,j) << " )" << endl;
      double scale = h->GetBinContent(i,j)/h2->GetBinContent(i,j);
      double scale_err = h->GetBinError(i,j)/h2->GetBinContent(i,j);
      cout << "[ pt bin= " << i << ", eta bin= " << j << "] " << "SCALE: " << scale << "( +- " << scale_err << " )" << endl;
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

