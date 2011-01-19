#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <iostream>
//#include "TStyle.h"
using namespace std;

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

string float2string(float f,int n){
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(n) << f;
  string s= ss.str();
  return s;
}

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

RooHist* getHist(TFile *f, const TString &dir, const TString &plot, int color, int style){
  f->cd(dir);
  TCanvas* c = (TCanvas*) gDirectory->FindKey(plot)->ReadObj();
  TString obj="";
  if(dir.Contains("cnt")) obj = "hxy_cnt_eff";
  else obj = "hxy_fit_eff";
  RooHist* h = (RooHist*) c->FindObject(obj);

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(style);
  h->SetMarkerSize(0.7);

  return h;
}

void plotMultiEff(TFile *f1, TFile *f2, const TString & leg1, const TString & leg2, vector<TString> dir, vector<TString> plot, const TString& printName, const TString& hName){
  gStyle->SetPadTickX(1);
  f1->cd(dir[0]);
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(plot[0])->ReadObj();
  setRangeY(c1,0.5,1.1);
  c1->Draw();

  RooHist* h_1[1];
  RooHist* h_2[1];

  for(int i=0; i < dir.size() ;i++){
    RooHist* h1 = getHist(f1, dir[i], plot[i], 4, 20);
    cout << "data-----" << plot[i] << "---" << hName << "----" << endl;
    printEff(h1);

    RooHist* h2 = getHist(f2, dir[i], plot[i], 2, 20);
    cout << "MC-----" << plot[i] << "---"<< hName << "---" << endl;
    printEff(h2);

    h_1[i] = h1;
    h_2[i] = h2;
  }

  c1->Draw();
  for( int i=0; i < dir.size() ; i++){
    h_1[i]->Draw("P Same");
    h_2[i]->Draw("P Same");
  }

  doLegend(h_1[0], h_2[0], leg1, leg2);
  c1->Print("c_"+printName+"_"+hName+".png");
  c1->Print("c_"+printName+"_"+hName+".eps");
}

void plot2Eff(TFile *f1, TFile* f2, const TString & leg1, const TString & leg2, const TString& dir1, const TString &dir2, const TString& plot1, const TString & plot2, const TString& printName, const TString& hName){

  gStyle->SetPadTickX(1);
  f1->cd(dir1);
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(plot1)->ReadObj();
  setRangeY(c1,0.5,1.1);
  //getObjects(c1);

  RooHist* h1 = getHist(f1, dir1, plot1, 4, 20);
  cout << "data-----" << plot1 << "---" << hName << "----" << endl;
  printEff(h1);

  RooHist* h2 = getHist(f2, dir2, plot2, 2, 20);
  cout << "MC-----" << plot2 << "---"<< hName << "---" << endl;
  printEff(h2);

  c1->Draw();
  h1->Draw("P Same");
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
  string tablefordata;
  string tableformc;
  string tableforscale;
  string columnfortable;
  for(int i=1; i <=nbinx ; i++){
    string si = int2string(i);
    string slowedge = int2string(h->GetBinLowEdge(i));
    int highedge = h->GetBinLowEdge(i) + h->GetBinWidth(i);
    string shighedge = int2string(highedge);
    string temp = "$"+slowedge + " \\GeV < p_{T} < " + shighedge+ " \\GeV$";
    tablefordata += temp; 
    tableformc += temp; 
    tableforscale += temp; 
    for(int j=1; j <=nbiny ; j++){  
      string sj = int2string(j);
      if(i==1) { 
        string slowedgey = float2string(h->ProfileY()->GetBinLowEdge(j),1);
        float highedgey = h->ProfileY()->GetBinLowEdge(j) + h->ProfileY()->GetBinWidth(j);
        string shighedgey = float2string(highedgey,1);

        if(j==1) { 
          columnfortable += "Selection";
          columnfortable = columnfortable + " ~&~ " + " $|\\eta|<"+ shighedgey +"$";
        }else if( j == nbiny ){
          columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
          columnfortable += "\\\\ \\hline"; 
        }else columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
      }

      float effdata = h->GetBinContent(i,j);
      float errdata = h->GetBinError(i,j);
      float effmc = h2->GetBinContent(i,j);
      float errmc = h2->GetBinError(i,j);

      string seffdata = float2string(effdata,4);
      string serrdata = float2string(errdata,4);
      string seffmc = float2string(effmc,4);
      string serrmc = float2string(errmc,4);
  
      tablefordata = tablefordata+" ~&~ "+seffdata + "$\\pm$" + serrdata;
      tableformc = tableformc+" ~&~ "+seffmc + "$\\pm$" + serrmc;

      float scale = h->GetBinContent(i,j)/h2->GetBinContent(i,j);
      float scale_err = h->GetBinError(i,j)/h2->GetBinContent(i,j);
 
      string sscale = float2string(scale,4);
      string sscale_err = float2string(scale_err,4);

      tableforscale = tableforscale+" ~&~ "+ sscale+ "$\\pm$"+ sscale_err;
    }
   
    tablefordata = tablefordata + "\\\\ \n";
    tableformc = tableformc + "\\\\ \n";
    tableforscale = tableforscale + "\\\\ \n";
  }

  cout.precision(5);
  cout << "efficiency for data" << endl;
  cout << columnfortable << endl;
  cout << tablefordata << endl;
  cout << "efficiency for mc" << endl;
  cout << columnfortable << endl;
  cout << tableformc << endl;
  cout << "scale factor" << endl;
  cout << columnfortable << endl;
  cout << tableforscale << endl;

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


