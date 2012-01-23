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
  TFile * f_PFId = new TFile("result/result_PFId_Data.root");
  TFile * f_PFId_MC = new TFile("result/result_PFId_MC.root");
  //TFile * f_Id = new TFile("result/result_Id_Data.root"); //Example for multipl flags of ID for Data
  //TFile * f_Id_MC = new TFile("result/result_Id_MC.root"); //Example for multiple flags of ID for MC

  // Data vs MC
  TString l1 = "Data";
  TString l2 = "MC";

  // Data vs MC
  plot2Eff(f_PFId,f_PFId_MC,l1,l2, "tnpPFId/PFId_pt/fit_eff_plots", "tnpPFId/PFId_pt/fit_eff_plots", "pt_PLOT", "pt_PLOT", "pt_PLOT","PFId");
  plot2Eff(f_PFId,f_PFId_MC,l1,l2, "tnpPFId/PFId_abseta/fit_eff_plots", "tnpPFId/PFId_abseta/fit_eff_plots", "abseta_PLOT", "abseta_PLOT", "abseta_PLOT","PFId");

  // 2D
  //plot2DEff(f, f_MC, "tnpTree/isIDMuon_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIDMuon");
 
  // multiple comparisons:
  //plotMulti(f, f_MC, "pt");
  //plotMulti(f, f_MC, "abseta");
 
}

plotMulti(TFile* f, TFile* f_MC, const TString& variable){
  
  vector<TString> lname;
  lname.push_back("CiC Loose");
  lname.push_back("CiC Medium");
  lname.push_back("CiC Tight");
  lname.push_back("CiC SuperTight");
  lname.push_back("CiC HyperTight1");

  vector<TString> vdir;
  vector<TString> vplot;
  vdir.push_back("tnpId/IdLoose_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdMedium_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdTight_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdSuperTight_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdHyperTight1_"+variable+"/fit_eff_plots");

  for(int i=0; i < vdir.size(); i++){
    vplot.push_back(variable+"_PLOT");
  }

  bool print = true;
  plotMultiEff(f,f_MC,vdir, vplot, variable,"CiCID", lname);

}

