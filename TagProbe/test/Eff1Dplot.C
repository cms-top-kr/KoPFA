#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include <map>
#include <fstream.h>
#include "styleTnP.h"

void Eff1Dplot(){

  gROOT->LoadMacro("tdrStyle.C");
  setTDRStyle();

//  using namespace std;
//  ofstream fout; 
//  fout.open("Efficiency_Table.txt"); 
  cout << "Output of data" <<endl;

//////////////////////////////////////////////////////////////////////////

  TString RelIsoCut="020";
  TString ytitleIso = "Isolation Efficiency";
  TString ytitleId = "Identification Efficiency";
//  //tdrStyle->SetOptTitle(1);

//////////////////////////////////////////////////////////////////////////
  //TString var ="abseta";
  //TString xtitle = "Probe #eta";
  //TString htitle = "A RooPlot of Probe #eta";
  //double Xmin = 0.0;
  //double Xmax = 2.4;

  TString var = "pt";
  TString xtitle = "Probe P_{t} (GeV/c)";
  TString htitle = "A RooPlot of Probe P_{t}";
  double Xmin = 20;
  double Xmax = 150;
//////////////////////////////////////////////////////////////////////////

  TString FileIso="./data4/Efficiency_Iso_data.root";
  TString FileIso_mc="./mc4/Efficiency_Iso_mc.root";
  TString DirIso="tnpTreeIso/"+var+"/fit_eff_plots";

  TString FileID="./data4/Efficiency_ID_data.root";
  TString FileID_mc="./mc4/Efficiency_ID_mc.root";
  TString DirID="tnpTree/ID_"+var+"/fit_eff_plots";

//////////////////////////////////////////////////////////////////////////
  cout << "///////////////////// Isolation (Data) ///////////////////////////" << endl;
  TFile * f_Iso = new TFile(Form("%s",FileIso.Data()));
  f_Iso->cd(Form("%s",DirIso.Data()));
    
  TGraphAsymmErrors * gr_Iso = new TGraphAsymmErrors();
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(var+"_PLOT")->ReadObj();
  TString obj1="";
  obj1 = "hxy_fit_eff";
  RooHist* h1 = (RooHist*) c1->FindObject(obj1);
  int nbin = h1->GetMaxSize();
  for(int j=0 ; j < nbin ; j++){
      double x;
      double y;
      double xerrhi = h1->GetErrorXhigh(j);
      double xerrlo = h1->GetErrorXlow(j);
      double yerrhi = h1->GetErrorYhigh(j);
      double yerrlo = h1->GetErrorYlow(j);
      int eff =  h1->GetPoint(j,x,y);
      cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(eff)" << eff << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
      gr_Iso->SetPoint(j,x,y);
      gr_Iso->SetPointError(j,xerrlo,xerrhi,yerrlo,yerrhi);          
      }
//////////////////////////////////////////////////////////////////////////
  cout << "///////////////////// Isolation (MC) ///////////////////////////" << endl;
  TFile * f_Iso_mc = new TFile(Form("%s",FileIso_mc.Data()));
  f_Iso_mc->cd(Form("%s",DirIso.Data()));
    
  TGraphAsymmErrors * gr_Isomc = new TGraphAsymmErrors();
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(var+"_PLOT")->ReadObj();
  TString obj1="";
  obj1 = "hxy_fit_eff";
  RooHist* h1 = (RooHist*) c1->FindObject(obj1);
  int nbin = h1->GetMaxSize();
  for(int j=0 ; j < nbin ; j++){
      double x;
      double y;
      double xerrhi = h1->GetErrorXhigh(j);
      double xerrlo = h1->GetErrorXlow(j);
      double yerrhi = h1->GetErrorYhigh(j);
      double yerrlo = h1->GetErrorYlow(j);
      int eff =  h1->GetPoint(j,x,y);
      cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(eff)" << eff << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
      gr_Isomc->SetPoint(j,x,y);
      gr_Isomc->SetPointError(j,xerrlo,xerrhi,yerrlo,yerrhi);          
      }

/////////////////////////////////////////////////////////
  cIso=new TCanvas("cIso","cIso",500,400);

  gr_Iso->GetXaxis()->SetLimits(Xmin,Xmax);
  gr_Iso->SetMaximum(1.1);  
  gr_Iso->SetMinimum(0.5);
  gr_Iso->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
  gr_Iso->GetYaxis()->SetTitle(Form("%s",ytitleIso.Data()));

  gr_Iso->SetLineColor(4);
  gr_Iso->SetMarkerColor(4);
  gr_Iso->SetLineWidth(2);
  //gr_Iso->SetMarkerSize(1.1);
  gr_Iso->SetMarkerStyle(21);

  gr_Isomc->SetLineColor(2);
  gr_Isomc->SetMarkerColor(2);
  gr_Isomc->SetLineWidth(2);
  //gr_Isomc->SetMarkerSize(1.1);
  gr_Isomc->SetMarkerStyle(21);

  gr_Iso->Draw("AP"); 
  gr_Isomc->Draw("Psame"); 
  TLegend *lIso= new TLegend(0.6,0.2,0.8,0.4);
  lIso->AddEntry(gr_Isomc,"  MC","PL");
  lIso->AddEntry(gr_Iso,"  Data","PL");
  lIso->SetTextSize(0.04);
  lIso->SetFillColor(0);
  lIso->SetLineColor(0);
  lIso->Draw();
  cIso->Print("Eff_of_Iso_"+var+".gif");
  cIso->Print("Eff_of_Iso_"+var+".png");
  cIso->Print("Eff_of_Iso_"+var+".eps");


//////////////////////////////////////////////////////////////////////////
  cout << "///////////////////// Identification (Data) ///////////////////////////" << endl;
  TFile * f_ID = new TFile(Form("%s",FileID.Data()));
  f_ID->cd(Form("%s",DirID.Data()));
    
  TGraphAsymmErrors * gr_ID = new TGraphAsymmErrors();
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(var+"_PLOT")->ReadObj();
  TString obj1="";
  obj1 = "hxy_fit_eff";
  RooHist* h1 = (RooHist*) c1->FindObject(obj1);
  int nbin = h1->GetMaxSize();
  for(int j=0 ; j < nbin ; j++){
      double x;
      double y;
      double xerrhi = h1->GetErrorXhigh(j);
      double xerrlo = h1->GetErrorXlow(j);
      double yerrhi = h1->GetErrorYhigh(j);
      double yerrlo = h1->GetErrorYlow(j);
      int eff =  h1->GetPoint(j,x,y);
      cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(eff)" << eff << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
      gr_ID->SetPoint(j,x,y);
      gr_ID->SetPointError(j,xerrlo,xerrhi,yerrlo,yerrhi);          
      }
//////////////////////////////////////////////////////////////////////////
  cout << "///////////////////// Identification (MC) ///////////////////////////" << endl;
  TFile * f_ID_mc = new TFile(Form("%s",FileID_mc.Data()));
  f_ID_mc->cd(Form("%s",DirID.Data()));
    
  TGraphAsymmErrors * gr_IDmc = new TGraphAsymmErrors();
  TCanvas* c1 = (TCanvas*) gDirectory->FindKey(var+"_PLOT")->ReadObj();
  TString obj1="";
  obj1 = "hxy_fit_eff";
  RooHist* h1 = (RooHist*) c1->FindObject(obj1);
  int nbin = h1->GetMaxSize();
  for(int j=0 ; j < nbin ; j++){
      double x;
      double y;
      double xerrhi = h1->GetErrorXhigh(j);
      double xerrlo = h1->GetErrorXlow(j);
      double yerrhi = h1->GetErrorYhigh(j);
      double yerrlo = h1->GetErrorYlow(j);
      int eff =  h1->GetPoint(j,x,y);
      cout << "[" << x-xerrlo  << "," << x+xerrhi << "] "  << " eff= " << y << "(eff)" << eff << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
      gr_IDmc->SetPoint(j,x,y);
      gr_IDmc->SetPointError(j,xerrlo,xerrhi,yerrlo,yerrhi);          
      }

/////////////////////////////////////////////////////////
  cId=new TCanvas("cId","cId",500,400);

  gr_ID->GetXaxis()->SetLimits(Xmin,Xmax);
  gr_ID->SetMaximum(1.1);  
  gr_ID->SetMinimum(0.5);
  gr_ID->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
  gr_ID->GetYaxis()->SetTitle(Form("%s",ytitleId.Data()));

  gr_ID->SetLineColor(4);
  gr_ID->SetMarkerColor(4);
  gr_ID->SetLineWidth(2);
  //gr_ID->SetMarkerSize(1.1);
  gr_ID->SetMarkerStyle(21);

  gr_IDmc->SetLineColor(2);
  gr_IDmc->SetMarkerColor(2);
  gr_IDmc->SetLineWidth(2);
  //gr_IDmc->SetMarkerSize(1.1);
  gr_IDmc->SetMarkerStyle(21);

  gr_ID->Draw("AP"); 
  gr_IDmc->Draw("Psame"); 
  TLegend *lId= new TLegend(0.6,0.2,0.8,0.4);
  lId->AddEntry(gr_IDmc,"  MC","PL");
  lId->AddEntry(gr_Iso,"  Data","PL");
  lId->SetTextSize(0.04);
  lId->SetFillColor(0);
  lId->SetLineColor(0);
  lId->Draw();
  cId->Print("Eff_of_Id_"+var+".gif");
  cId->Print("Eff_of_Id_"+var+".png");
  cId->Print("Eff_of_Id_"+var+".eps");

/////////////////////////////////////////////////////////

}
