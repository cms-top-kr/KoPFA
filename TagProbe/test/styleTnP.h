#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include "TGraph.h"

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

void printEff(RooHist* h1, RooHist* h2, vector<double>& data, vector<double>& mc, TGraphAsymmErrors *&h_s){
  vector<double> tmpdata;
  vector<double> tmpmc;
  TGraphAsymmErrors *tmps = new TGraphAsymmErrors();
  for(int i=0 ; i < h1->GetMaxSize() ; i++){
    double x1;
    double y1;
    double xerrhi1 = h1->GetErrorXhigh(i);
    double xerrlo1 = h1->GetErrorXlow(i);
    double yerrhi1 = h1->GetErrorYhigh(i);
    double yerrlo1 = h1->GetErrorYlow(i);
    double eff1 =  h1->GetPoint(i,x1,y1);
    double x2;
    double y2;
    double xerrhi2 = h2->GetErrorXhigh(i);
    double xerrlo2 = h2->GetErrorXlow(i);
    double yerrhi2 = h2->GetErrorYhigh(i);
    double yerrlo2 = h2->GetErrorYlow(i);
    double eff2 =  h2->GetPoint(i,x2,y2);
    tmpdata.push_back(y1);
    tmpmc.push_back(y2);
    double scalefactor = y1/y2;
    cout << "data-[" << x1-xerrlo1  << "," << x1+xerrhi1 << "] "  << " eff= " << y1 << "(+" << yerrhi1 << " -" << yerrlo1 << ")" << endl;
    cout << "MC---[" << x2-xerrlo2  << "," << x2+xerrhi2 << "] "  << " eff= " << y2 << "(+" << yerrhi2 << " -" << yerrlo2 << ")" << endl;
    cout << "scale= " << scalefactor << endl;
    tmps->SetPoint(i,x1,scalefactor);
    tmps->SetPointEXhigh(i, xerrhi1);
    tmps->SetPointEXlow(i, xerrlo1);
    double errh = yerrhi1/y2;
    double errl = yerrlo1/y2;
    tmps->SetPointEYhigh(i, errh);
    tmps->SetPointEYlow(i, errl);

  }
  data = tmpdata;
  mc = tmpmc;
  h_s = tmps;
}

//vector<string> printEff(RooHist* h, map<int,vector<double> > seff){
//   for(int i=0 ; i < h->GetMaxSize() ; i++){
//    double x;
//    double y;
//    double xerrhi = h->GetErrorXhigh(i);
//    double xerrlo = h->GetErrorXlow(i);
//    double yerrhi = h->GetErrorYhigh(i);
//    double yerrlo = h->GetErrorYlow(i);
//    double eff =  h->GetPoint(i,x,y);
//    seff[i].push_back(y);
//    cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
//  }
//  return seff;
//}

void setRangeY(TCanvas *c, double min=0, double max=1.1){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("TH1")) ((TH1*)o)->GetYaxis()->SetRangeUser(min,max);
  }
}

void setRangeY(TPad *c, double min=0, double max=1.1){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("TH1")) ((TH1*)o)->GetYaxis()->SetRangeUser(min,max);
  }
}

void setTitleY(TCanvas *c, TString title){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("TH1")) ((TH1*)o)->GetYaxis()->SetTitle(Form("%s",title.Data()));
  }
}

void setTitleY(TPad *c, TString title){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("TH1")) ((TH1*)o)->GetYaxis()->SetTitle(Form("%s",title.Data()));
  }
}

void setMarker(TCanvas *c, int s){
  for(size_t i=0, n = c->GetListOfPrimitives()->GetSize(); i <n; ++i){
    TObject *o = c->GetListOfPrimitives()->At(i);
    if(o->InheritsFrom("RooHist")) ((RooHist*)o)->SetMarkerSize(s);
  }
}

RooHist* getHist(TFile *f, const TString &dir, const TString &plot, int color, int style){
  cout << "getHist" << endl;
  cout << dir.Data() << endl;
  f->cd(dir.Data());
  TCanvas* c = (TCanvas*) gDirectory->FindKey(plot)->ReadObj();
  TString obj="";
  if(dir.Contains("cnt")) obj = "hxy_cnt_eff";
  else obj = "hxy_fit_eff";
  RooHist* h = (RooHist*) c->FindObject(obj);
  TH1D* hf= (TH1D*) c->FindObject("frame_202425112");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(style);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(color+19);
  h->SetMarkerSize(0.7);
  h->GetYaxis()->SetTitleSize(0.0);
  delete c;

  return h;
}

RooHist* getHist(TCanvas* ctmp, const TString &dir, int color, int style){
  cout << "getHist" << endl;
  TString obj="";
  if(dir.Contains("cnt")) obj = "hxy_cnt_eff";
  else obj = "hxy_fit_eff";
  RooHist* h = (RooHist*) ctmp->FindObject(obj);

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(style);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.2);
  h->GetYaxis()->SetTitleSize(0.0);

  return h;
}

void plotNewEff(TFile *f1, TFile *f2, const TString & leg1, const TString & leg2, const vector<TString>& dir, const vector<TString>& plot, const TString& printName, const TString& hName, const vector<TString>& lname, bool print=true){
  vector<double> dataPT20_50;
  vector<double> dataPT20_50Errh;
  vector<double> dataPT20_50Errl;
  vector<double> mcPT20_50;
  vector<double> mcPT20_50Errh;
  vector<double> mcPT20_50Errl;
  f2->cd(dir[0]);
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(plot[0])->ReadObj();
  setTitleY(c1,"Isolation Efficiency"); 
  setMarker(c1,0); 
  if(plot[0].Contains("eta")){
    setRangeY(c1,0.7,1.1);
  }else{
    setRangeY(c1,0.5,1.1);

  }
  c1->Draw();

  TLegend *isolabel = new TLegend(.55,.20 ,.65,.45 );
  TLegend *sflabel = new TLegend(.55,.20 ,.65,.45 );
  if(plot[0].Contains("eta")) {
    sflabel = new TLegend(.20,.20 ,.30,.45 );
  }
  isolabel->SetHeader("Rel. Iso.");
  sflabel->SetHeader("Rel. Iso.");
   
  TCanvas * c = new TCanvas("c","c",800,300);

  int k = 0;

  for(int i=0; i < dir.size() ; i++){
    RooHist* h1 = getHist(f1, dir[i], plot[i], i+2, 2);
    RooHist* h2 = getHist(f2, dir[i], plot[i], i+2, 1);

    TGraphAsymmErrors* htemp = new TGraphAsymmErrors();
    vector<double> & data( h1->GetMaxSize() );
    vector<double> & mc( h2->GetMaxSize() );
    printEff(h1,h2,data,mc,htemp);
    dataPT20_50.push_back(data[k]);
    mcPT20_50.push_back(mc[k]);
    h1->Draw("PSame");
    h2->Draw("PSame");
    isolabel->AddEntry(h1, Form("%s",lname[i].Data()), "LP");
    sflabel->AddEntry(h1, Form("%s",lname[i].Data()), "LP");
    if(i==0) doLegend(h1, h2, leg1, leg2);
    //htemp->Draw("PSame");
    //scale factor
    for(int j=0; j < h1->GetMaxSize(); j++){
      double x;
      double y;
      htemp->GetPoint(j,x,y);
      cout << "x= " << x << " y= " << y << endl;
      double eff1;
      double x1;
      double yerrhi1 = h1->GetErrorYhigh(j);
      double yerrlo1 = h1->GetErrorYlow(j);
      double test1 =  h1->GetPoint(j,x1,eff1);
      double eff2;
      double x2;
      double yerrhi2 = h2->GetErrorYhigh(j);
      double yerrlo2 = h2->GetErrorYlow(j);
      double test2 =  h2->GetPoint(j,x2,eff2);
      if(j== k){
        dataPT20_50Errh.push_back(yerrhi1);
        dataPT20_50Errl.push_back(yerrlo1);
        mcPT20_50Errh.push_back(yerrhi2);
        mcPT20_50Errl.push_back(yerrlo2);
      }
    }
    c->cd();
    c->Draw();
    htemp->SetLineColor(i+2);
    htemp->SetMarkerColor(i+2);
    htemp->SetMarkerStyle(i+2+19);
    htemp->SetLineWidth(1.5);
    if(i == 0) {
      htemp->GetYaxis()->SetTitle("Scale Factor");
      if(plot[0].Contains("eta")) {
        htemp->GetXaxis()->SetTitle("#eta");
      }
      else htemp->GetXaxis()->SetTitle("p_{T} (GeV)");
      htemp->Draw("ALP");
    }
    else htemp->Draw("LPSame"); 
    sflabel->Draw();
  }
  c1->cd(); 

  cout << "void Eff" <<  hName.Data() << "Data(TGraphAsymmErrors* grae){" << endl;
  for(int i=0; i < dataPT20_50.size() ;i++){
    cout << "  grae->SetPoint(" << i << "," << lname[i] << "," << dataPT20_50[i] << "); " << endl;
    cout << "  grae->SetPointError(" << i << ",0,0," << dataPT20_50Errl[i] << "," << dataPT20_50Errh[i] << "); " << endl;
  }
  cout << "}" << endl;

  cout << "void Eff" << hName.Data() << "MC(TGraphAsymmErrors* grae){" << endl;
  for(int i=0; i < mcPT20_50.size() ;i++){
    cout << "  grae->SetPoint(" << i << "," << lname[i] << "," << mcPT20_50[i] << "); " << endl;
    cout << "  grae->SetPointError(" << i << ",0,0," << mcPT20_50Errl[i] << "," << mcPT20_50Errh[i] << "); " << endl;
  }
  cout << "}" << endl;

  cout << "double eff_sig_data[] = {" << " " ;
  for(int i=0; i < dataPT20_50.size() ;i++) cout << dataPT20_50[i] << ", " ;
  cout << " };" << endl;
  cout << "double data_errY_high[] = {" << " " ;
  for(int i=0; i < dataPT20_50Errh.size() ;i++) cout << dataPT20_50Errh[i] << ", " ;
  cout << " };" << endl;
  cout << "double data_errY_low[] = {" << " " ;
  for(int i=0; i < dataPT20_50Errl.size() ;i++) cout << dataPT20_50Errl[i] << ", " ;
  cout << " };" <<endl;

  cout << "double eff_sig_mc[] = {" << " " ;
  for(int i=0; i < mcPT20_50.size() ;i++) cout << mcPT20_50[i] << ", " ;
  cout << " };" << endl;
  cout << "double mc_errY_high[] ={" << " " ;
  for(int i=0; i < mcPT20_50Errh.size() ;i++) cout << mcPT20_50Errh[i] << ", " ;
  cout << " };" << endl;
  cout << "double mc_errY_low[] ={" << " " ;
  for(int i=0; i < mcPT20_50Errl.size() ;i++) cout << mcPT20_50Errl[i] << ", " ;
  cout << " };" << endl;



  isolabel->SetFillColor(0);
  isolabel->SetTextSize(0.04);
  isolabel->SetLineColor(0);
  sflabel->SetFillColor(0);
  sflabel->SetTextSize(0.04);
  sflabel->SetLineColor(0);

  isolabel->Draw();
  
  SetLatex(0.60,0.60);

  c1->Print(Form("c_eff_%s_%s.eps",printName.Data(),hName.Data()));
  c1->Print(Form("c_eff_%s_%s.C",printName.Data(),hName.Data()));
  c1->Print(Form("c_eff_%s_%s.png",printName.Data(),hName.Data()));
  c->Print(Form("c_sf_%s_%s.eps",printName.Data(),hName.Data()));
  
}

void plot2Eff(TFile *f1, TFile* f2, const TString & leg1, const TString & leg2, const TString& dir1, const TString &dir2, const TString& plot1, const TString & plot2, const TString& printName, const TString& hName){

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
    if (obj->InheritsFrom("TH1F")) {
      cout << "TH1F: " << obj->GetName() << endl;
    }else if (obj->InheritsFrom("TH1D")) {
      cout << "TH1D: " << obj->GetName() << endl;
    }else if (obj->InheritsFrom("RooHist")) {
      cout << "RooHisto: " << obj->GetName() << endl;
    }else if (obj->InheritsFrom("RooPlot")) {
      cout << "RooPlot: " << obj->GetName() << endl;
    }else{
      cout << "Ohter: " << obj->GetName() << endl;
    }

  }
}


void doLegend(TGraphAsymmErrors *g1, TGraphAsymmErrors *g2, const TString& lab1, const TString& lab2) {
    TLegend *leg = new TLegend(.68,.25 ,.88,.40 );
    leg->AddEntry(g1, Form("%s",lab1.Data()), "LP");
    leg->AddEntry(g2, Form("%s",lab2.Data()), "LP");
    leg->SetFillColor(0);
    leg->SetTextSize(0.04);
    leg->SetLineColor(0);
    leg->Draw();
}

void SetLatex(double x, double y){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  //label->DrawLatex(x,y,"CMS Preliminary 2010");
  //label->DrawLatex(x,y-0.05,"36 pb^{-1} at #sqrt{s} = 7 TeV");
  label->DrawLatex(x,y-0.1,"#DeltaR=0.4");
}

void plotEff1D(TFile* fMC, TFile* fRD, TString dirName, TString varName, TString varTitleOpt)
{
  TObjArray* varTitleOpts = varTitleOpt.Tokenize(";");
  const int nField = varTitleOpts->GetEntries();
  TString varTitle = nField <= 0 ? "" : varTitleOpts->At(0)->GetName();
  TString varUnit  = nField <= 1 ? "" : varTitleOpts->At(1)->GetName();
  TString varOpt   = nField <= 2 ? "" : varTitleOpts->At(2)->GetName();

  TString srcCanvasName = dirName+"_"+varName+"/fit_eff_plots/"+varName+"_PLOT";
  TCanvas* cMC = (TCanvas*)fMC->Get(srcCanvasName);
  TCanvas* cRD = (TCanvas*)fRD->Get(srcCanvasName);

  RooHist* hMC = (RooHist*)cMC->FindObject("hxy_fit_eff");
  RooHist* hRD = (RooHist*)cRD->FindObject("hxy_fit_eff");

  if ( !hMC || !hRD ) return;

  TString grpTitle = Form("Efficiency of %s", varTitle.Data());
  TGraphAsymmErrors* grpMC = getGraph(hMC, grpTitle);
  TGraphAsymmErrors* grpRD = getGraph(hRD, grpTitle);

  grpMC->GetXaxis()->SetTitle(varTitle+" "+varUnit);
  grpRD->GetXaxis()->SetTitle(varTitle+" "+varUnit);
  grpMC->GetYaxis()->SetTitle("Efficiency");
  grpRD->GetYaxis()->SetTitle("Efficiency");

  decorateGraph(grpMC, kBlue, 20);
  decorateGraph(grpRD, kRed , 21);

  TString canvasName = (dirName+"_"+varName).ReplaceAll("/", "_");
  TCanvas* can = new TCanvas("c_"+canvasName, canvasName, 600, 500);
  if ( varOpt.Contains("log") || varOpt.Contains("LOG") ) can->SetLogx();

  grpMC->Draw("AP");
  grpRD->Draw("P");
  TLegend* leg = new TLegend(0.65, 0.20, 0.85, 0.35);
  leg->AddEntry(grpRD, "Data");
  leg->AddEntry(grpMC, "MC");
  leg->Draw();

  can->Print(TString(can->GetName())+".png");
  can->Print(TString(can->GetName())+".eps");
}

void plotEff2D(TFile* fMC, TFile* fRD, TString dirName, TString varName1, TString varName2, TString varTitleOpt1, TString varTitleOpt2)
{
  TObjArray* varTitleOpts1 = varTitleOpt1.Tokenize(";");
  const int nField1 = varTitleOpts1->GetEntries();
  TString varTitle1 = nField1 <= 0 ? "" : varTitleOpts1->At(0)->GetName();
  TString varUnit1  = nField1 <= 1 ? "" : varTitleOpts1->At(1)->GetName();
  TString varOpt1   = nField1 <= 2 ? "" : varTitleOpts1->At(2)->GetName();

  TObjArray* varTitleOpts2 = varTitleOpt2.Tokenize(";");
  const int nField2 = varTitleOpts2->GetEntries();
  TString varTitle2 = nField2 <= 0 ? "" : varTitleOpts2->At(0)->GetName();
  TString varUnit2  = nField2 <= 1 ? "" : varTitleOpts2->At(1)->GetName();
  TString varOpt2   = nField2 <= 2 ? "" : varTitleOpts2->At(2)->GetName();

  const bool doLogX = varOpt1.Contains("log") || varOpt1.Contains("LOG");
  const bool doLogY = varOpt2.Contains("log") || varOpt2.Contains("LOG");

  TString srcCanvasName = dirName+"_"+varName1+"_"+varName2+"/fit_eff_plots/"+varName1+"_"+varName2+"_PLOT";
  TCanvas* cMC = (TCanvas*)fMC->Get(srcCanvasName);
  TCanvas* cRD = (TCanvas*)fRD->Get(srcCanvasName);

  //RooHist* hMC = (RooHist*)cMC->FindObject(varName1+"_"+varName2+"_PLOT");
  //RooHist* hRD = (RooHist*)cRD->FindObject(varName1+"_"+varName2+"_PLOT");

  TH2* hMC = (TH2*)cMC->FindObject(varName1+"_"+varName2+"_PLOT");
  TH2* hRD = (TH2*)cRD->FindObject(varName1+"_"+varName2+"_PLOT");

  hMC->GetXaxis()->SetTitle(varTitle1+" "+varUnit1);
  hRD->GetXaxis()->SetTitle(varTitle1+" "+varUnit1);
  hMC->GetYaxis()->SetTitle(varTitle2+" "+varUnit2);
  hRD->GetYaxis()->SetTitle(varTitle2+" "+varUnit2);

  decorateTH2(hMC);
  decorateTH2(hRD);

  TPaveText* ttMC = new TPaveText(0.1, 0.93, 0.4, 0.98, "NDC");
  TPaveText* ttRD = new TPaveText(0.1, 0.93, 0.4, 0.98, "NDC");
  ttMC->AddText("MC");
  ttRD->AddText("Data");

  TString canvasName = (dirName+"_"+varName1+"_"+varName2).ReplaceAll("/", "_");
  TCanvas* can = new TCanvas("c_"+canvasName, canvasName, 1200, 500);
  can->Divide(2);
  TPad* pad1 = can->cd(1);
  if ( doLogX ) pad1->SetLogx();
  if ( doLogY ) pad1->SetLogy();
  hMC->Draw("colz,texte");
  ttMC->Draw();
  TPad* pad2 = can->cd(2);
  if ( doLogX ) pad2->SetLogx();
  if ( doLogY ) pad2->SetLogy();
  hRD->Draw("colz,texte");
  ttRD->Draw();

  can->Print(TString(can->GetName())+".png");
  can->Print(TString(can->GetName())+".eps");
}

void decorateGraph(TGraph* grp, int color, int marker)
{
  grp->SetLineColor(color);
  grp->SetMarkerColor(color);
  grp->SetFillColor(kWhite);
  grp->SetLineWidth(2);
  grp->SetMarkerStyle(marker);
  grp->SetMarkerSize(1.2);
  grp->GetXaxis()->SetMoreLogLabels(true); 
  grp->GetHistogram()->SetTitleOffset(1.22);

  grp->SetMinimum(0.5);
  grp->SetMaximum(1.1);

  const int n = grp->GetN();
  const double xmin = grp->GetX()[0]-grp->GetEXlow()[0];
  const double xmax = grp->GetX()[n-1]+grp->GetEXhigh()[n-1];
  grp->GetXaxis()->SetRangeUser(xmin, xmax);
}

void decorateTH2(TH2* h)
{
  h->SetMarkerSize(1.5);
  h->GetXaxis()->SetMoreLogLabels(true);
  h->GetYaxis()->SetMoreLogLabels(true);
  h->SetLabelOffset(0.0005);
  h->SetTitleOffset(1.22);
}

TGraphAsymmErrors* getGraph(RooHist* h, TString title)
{
  const int n = h->GetN();
  const double* x = h->GetX();
  const double* y = h->GetY();
  const double* exl = h->GetEXlow();
  const double* exh = h->GetEXhigh();
  const double* eyl = h->GetEYlow();
  const double* eyh = h->GetEYhigh();

  TGraphAsymmErrors* grp = new TGraphAsymmErrors(n, x, y, exl, exh, eyl, eyh);
  grp->SetTitle(title);
  return grp;
}

