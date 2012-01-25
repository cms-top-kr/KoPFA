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
  //TFile * f_Iso = new TFile("result/result_TightIdIso_Data.root"); 
  //TFile * f_Iso_MC = new TFile("result/result_TightIdIso_MC.root"); 

  // Data vs MC
  TString l1 = "Data";
  TString l2 = "MC";

  // Data vs MC
  plot2Eff(f_PFId,f_PFId_MC,l1,l2, "tnpPFId/PFId_pt/fit_eff_plots", "tnpPFId/PFId_pt/fit_eff_plots", "pt_PLOT", "pt_PLOT", "pt_PLOT","PFId");
  plot2Eff(f_PFId,f_PFId_MC,l1,l2, "tnpPFId/PFId_abseta/fit_eff_plots", "tnpPFId/PFId_abseta/fit_eff_plots", "abseta_PLOT", "abseta_PLOT", "abseta_PLOT","PFId");

  //plot2Eff(f_Id,f_Id_MC,l1,l2, "tnpId/IdTight_pt/fit_eff_plots", "tnpId/IdTight_pt/fit_eff_plots", "pt_PLOT", "pt_PLOT", "pt_PLOT","IdTight");
  //plot2Eff(f_Id,f_Id_MC,l1,l2, "tnpId/IdTight_abseta/fit_eff_plots", "tnpId/IdTight_abseta/fit_eff_plots", "abseta_PLOT", "abseta_PLOT", "abseta_PLOT","IdTight");

  //Isolation
  //plot2Eff(f_Iso,f_Iso_MC,l1,l2, "tnpTightIdIso/Iso17_pt/cnt_eff_plots", "tnpTightIdIso/Iso17_pt/cnt_eff_plots", "pt_PLOT", "pt_PLOT", "pt_PLOT","Iso17");
  //plot2Eff(f_Iso,f_Iso_MC,l1,l2, "tnpTightIdIso/Iso17_abseta/cnt_eff_plots", "tnpTightIdIso/Iso17_abseta/cnt_eff_plots", "abseta_PLOT", "abseta_PLOT", "abseta_PLOT","Iso17");
  //dbeta correction
  //plot2Eff(f_Iso,f_Iso_MC,l1,l2, "tnpTightIdIso/Iso17dbeta_pt/cnt_eff_plots", "tnpTightIdIso/Iso17dbeta_pt/cnt_eff_plots", "pt_PLOT", "pt_PLOT", "pt_PLOT","Iso17dbeta");
  //plot2Eff(f_Iso,f_Iso_MC,l1,l2, "tnpTightIdIso/Iso17dbeta_abseta/cnt_eff_plots", "tnpTightIdIso/Iso17dbeta_abseta/cnt_eff_plots", "abseta_PLOT", "abseta_PLOT", "abseta_PLOT","Iso17dbeta");
  //plot2Eff(f_Iso,f_Iso,"No dbeta Corr.","dbeta Corr.", "tnpTightIdIso/Iso17_event_nPV/cnt_eff_plots", "tnpTightIdIso/Iso17dbeta_event_nPV/cnt_eff_plots", "event_nPV_PLOT", "event_nPV_PLOT", "event_nPV_PLOT","Iso17vsIso17dbeta", 0.8);

  // 2D
  //plot2DEff(f, f_MC, "tnpTree/isIDMuon_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIDMuon");
 
  // multiple comparisons:
  //plotMulti(f_Id, f_Id_MC, "pt");
  //plotMulti(f_Id, f_Id_MC, "abseta");
 
}

plotMulti(TFile* f, TFile* f_MC, const TString& variable){
  
  vector<TString> lname;
  lname.push_back("CiC Loose");
  lname.push_back("CiC Medium");
  lname.push_back("CiC Tight");
  lname.push_back("CiC SuperTight");
  lname.push_back("CiC HyperTight1");

  //lname.push_back("WP95");
  //lname.push_back("WP90");
  //lname.push_back("WP85");
  //lname.push_back("WP80");
  //lname.push_back("WP70");

  vector<TString> vdir;
  vector<TString> vplot;
  vdir.push_back("tnpId/IdLoose_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdMedium_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdTight_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdSuperTight_"+variable+"/fit_eff_plots");
  vdir.push_back("tnpId/IdHyperTight1_"+variable+"/fit_eff_plots");

  //vdir.push_back("tnpId/IdsimpleEleId95relIso_"+variable+"/fit_eff_plots");
  //vdir.push_back("tnpId/IdsimpleEleId90relIso_"+variable+"/fit_eff_plots");
  //vdir.push_back("tnpId/IdsimpleEleId85relIso_"+variable+"/fit_eff_plots");
  //vdir.push_back("tnpId/IdsimpleEleId80relIso_"+variable+"/fit_eff_plots");
  //vdir.push_back("tnpId/IdsimpleEleId70relIso_"+variable+"/fit_eff_plots");

  for(int i=0; i < vdir.size(); i++){
    vplot.push_back(variable+"_PLOT");
  }

  bool print = true;
  //plotMultiEff(f,f_MC,vdir, vplot, variable,"WPIdData", lname);
  plotMultiEff(f,f_MC,vdir, vplot, variable,"CiCIdData", lname);

}

