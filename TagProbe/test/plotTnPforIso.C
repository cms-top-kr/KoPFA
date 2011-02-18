#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "styleTnP.h"
#include <map>

void plotTnPforIso(){

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  using namespace std;
  //TFile * f = new TFile("result2/plot_voigtian/Efficiency_ID.root");
  //TFile * f_MC = new TFile("result/plot/Efficiency_ID.root");
  //TFile * f_MC = new TFile("result2/plot_voigtian/Efficiency_ID_mc.root");
  //TFile * f_MCUnbias = new TFile("result/plot/Efficiency_ID_mcUnbias.root");

  TFile * f_Iso = new TFile("result_MUiso/plot/Efficiency_Iso.root");
  //TFile * f_Iso_MC = new TFile("result/plot/Efficiency_Iso.root");
  TFile * f_Iso_MC = new TFile("result_MUiso/plot/Efficiency_Iso_mc.root");
  //TFile * f_Iso_MCUnbias = new TFile("result/plot/Efficiency_Iso_mcUnbias.root");

  // Data vs MC
  cout << "Data vs MC" << endl;
  TString l1 = "Data";
  TString l2 = "MC";

  bool datavsmc = true;

  if( datavsmc ){
    vector<TString> lname;
    lname.push_back("0.06");
    lname.push_back("0.07");
    lname.push_back("0.08");
    lname.push_back("0.09");
    lname.push_back("0.10");
    lname.push_back("0.11");
    lname.push_back("0.12");
    lname.push_back("0.13");
    lname.push_back("0.14");
    lname.push_back("0.15");
    lname.push_back("0.16");
    lname.push_back("0.17");
    lname.push_back("0.18");
    lname.push_back("0.19");
    lname.push_back("0.20");
    lname.push_back("0.21");
    lname.push_back("0.22");
    lname.push_back("0.23");
    lname.push_back("0.24");
    lname.push_back("0.25");
    lname.push_back("0.26");
    lname.push_back("0.27");
    lname.push_back("0.28");

    vector<TString> dir_abseta;
    vector<TString> plot_abseta;
    dir_abseta.push_back("tnpTreeIso/isIso20_abseta/fit_eff_plots");
    dir_abseta.push_back("tnpTreeIso/isIso16_abseta/fit_eff_plots");
//  dir_abseta.push_back("tnpTreeIso/isIso14_abseta/fit_eff_plots");
    dir_abseta.push_back("tnpTreeIso/isIso12_abseta/fit_eff_plots");
//    dir_abseta.push_back("tnpTreeIso/isIso08_abseta/fit_eff_plots");
    for(int i=0; i < dir_abseta.size();i++){
      plot_abseta.push_back("abseta_PLOT");
    }

    vector<TString> dir_pt;    
    vector<TString> plot_pt;
    dir_pt.push_back("tnpTreeIso/isIso06_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso07_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso08_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso09_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso10_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso11_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso12_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso13_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso14_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso15_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso16_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso17_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso18_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso19_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso20_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso21_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso22_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso23_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso24_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso25_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso26_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso27_pt/fit_eff_plots");
    dir_pt.push_back("tnpTreeIso/isIso28_pt/fit_eff_plots");

    for(int i=0; i < dir_pt.size(); i++){
      plot_pt.push_back("pt_PLOT");
    }

    cout << "DEBUG: dir size= " << dir_pt.size() << " = " << " plot size= " << plot_pt.size() << endl;

    bool print = true; 
    //plotMultiEff(f_Iso,f_Iso_MC,l1,l2,dir_pt, plot_pt, "pt","isIso", lname, print);
    plotNewEff(f_Iso,f_Iso_MC,l1,l2,dir_pt, plot_pt, "pt","isIso", lname, print);
    //plotMultiEff(f_Iso,f_Iso_MC,l1,l2,dir_abseta,plot_abseta, "abseta","isIso", lname, print);

    cout << "ERROR" << endl; 

  }

}

