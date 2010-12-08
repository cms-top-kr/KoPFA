#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "styleTnP.h"

void plotTnP(){
  
  using namespace std;
  TFile * f = new TFile("result2/plot_bgauss/Efficiency_ID.root");
  //TFile * f_MC = new TFile("result/plot/Efficiency_ID.root");
  TFile * f_MC = new TFile("result2/plot_bgauss/Efficiency_ID_mc.root");
  //TFile * f_MCUnbias = new TFile("result/plot/Efficiency_ID_mcUnbias.root");

  TFile * f_Iso = new TFile("result2/plot_bgauss/Efficiency_Iso.root");
  //TFile * f_Iso_MC = new TFile("result/plot/Efficiency_Iso.root");
  TFile * f_Iso_MC = new TFile("result2/plot_bgauss/Efficiency_Iso_mc.root");
  //TFile * f_Iso_MCUnbias = new TFile("result/plot/Efficiency_Iso_mcUnbias.root");

  // Data vs MC
  cout << "Data vs MC" << endl;
  TString l1 = "Data";
  TString l2 = "MC";

  bool datavsmc = true;
  bool datavstruth = false;
  bool datavsunbiased = false;
  bool h2d = true;
  bool chargedependency = false;


  if( chargedependency ){
    plot2Eff(f,f_MC,l1,l2,"tnpTree/isIDMuon_charge/fit_eff_plots","tnpTree/isIDMuon_charge/fit_eff_plots","charge_PLOT","charge_PLOT","charge","isIDMuon");
    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/isIso12_charge/fit_eff_plots","tnpTreeIso/isIso12_charge/fit_eff_plots","charge_PLOT","charge_PLOT","charge","isIso12");
  }

  if( datavsmc ){
    //plot2Eff(f,f_MC,l1,l2,"tnpTree/isPFMuon_abseta/fit_eff_plots","tnpTree/isPFMuon_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","isPFMuon");
    //plot2Eff(f,f_MC,l1,l2,"tnpTree/isPFMuon_pt/fit_eff_plots","tnpTree/isPFMuon_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","isPFMuon");

    plot2Eff(f,f_MC,l1,l2,"tnpTree/isIDMuon_abseta/fit_eff_plots","tnpTree/isIDMuon_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","isIDMuon");
    plot2Eff(f,f_MC,l1,l2,"tnpTree/isIDMuon_pt/fit_eff_plots","tnpTree/isIDMuon_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","isIDMuon");

    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/isIso_abseta/fit_eff_plots","tnpTreeIso/isIso_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","isIso");
    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/isIso_pt/fit_eff_plots","tnpTreeIso/isIso_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","isIso");

    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/isIso12_abseta/fit_eff_plots","tnpTreeIso/isIso12_abseta/fit_eff_plots","abseta_PLOT","abseta_PLOT","abseta","isIso12");
    plot2Eff(f_Iso,f_Iso_MC,l1,l2,"tnpTreeIso/isIso12_pt/fit_eff_plots","tnpTreeIso/isIso12_pt/fit_eff_plots","pt_PLOT","pt_PLOT","pt","isIso12");

  }
  // Data vs MC truth
  if( datavstruth ){ 
    cout << "Data vs MC truth" << endl;
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/isPFMuon_abseta/fit_eff_plots","tnpTree/isPFMuon_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","isPFMuon");
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/isPFMuon_pt/fit_eff_plots","tnpTree/isPFMuon_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","isPFMuon");

    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/isIDMuon_abseta/fit_eff_plots","tnpTree/isIDMuon_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","isIDMuon");
    plot2Eff(f,f_MC,"Data","MC truth","tnpTree/isIDMuon_pt/fit_eff_plots","tnpTree/isIDMuon_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","isIDMuon");

    plot2Eff(f_Iso,f_Iso_MC,"Data","MC truth","tnpTreeIso/isIso_abseta/fit_eff_plots","tnpTreeIso/isIso_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue","Iso");
    plot2Eff(f_Iso,f_Iso_MC,"Data","MC truth","tnpTreeIso/isIso_pt/fit_eff_plots","tnpTreeIso/isIso_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue","Iso");
  }
  // Data vs MC unbiased truth
  if( datavsunbiased =){
    cout << "Data vs MC unbiased truth" << endl;
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth ","tnpTree/isPFMuon_abseta/fit_eff_plots","tnpTree/isPFMuon_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","isPFMuon");
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/isPFMuon_pt/fit_eff_plots","tnpTree/isPFMuon_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","isPFMuon");

    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/isIDMuon_abseta/fit_eff_plots","tnpTree/isIDMuon_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","isIDMuon");
    plot2Eff(f,f_MCUnbias,"Data","MC(unbiased) truth","tnpTree/isIDMuon_pt/fit_eff_plots","tnpTree/isIDMuon_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","isIDMuon");

    plot2Eff(f_Iso,f_Iso_MCUnbias,"Data","MC(unbiased) truth","tnpTreeIso/isIso_abseta/fit_eff_plots","tnpTreeIso/isIso_abseta_mcTrue/cnt_eff_plots","abseta_PLOT","abseta_PLOT_mcTrue_true","abseta_mcTrue_Unbiased","Iso");
    plot2Eff(f_Iso,f_Iso_MCUnbias,"Data","MC(unbiased) truth","tnpTreeIso/isIso_pt/fit_eff_plots","tnpTreeIso/isIso_pt_mcTrue/cnt_eff_plots","pt_PLOT","pt_PLOT_mcTrue_true","pt_mcTrue_Unbiased","Iso");

  }

  if( h2d == true){
    //2D histograms
    //plot2DEff(f, f_MC, "tnpTree/isPFMuon_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isPFMuon");
    plot2DEff(f, f_MC, "tnpTree/isIDMuon_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIDMuon");
    plot2DEff(f_Iso, f_Iso_MC, "tnpTreeIso/isIso_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIso");
    plot2DEff(f_Iso, f_Iso_MC, "tnpTreeIso/isIso12_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIso12");
    
  }

  
}

