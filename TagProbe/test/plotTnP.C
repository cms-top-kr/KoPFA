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
  TFile * f = new TFile("result/result_PFId_Data.root");
  TFile * f_MC = new TFile("result/result_PFId_MC.root");

  // Data vs MC
  string dir = "tnpPFId";
  string flag = "PFId_abseta";
  string var = "abseta_PLOT";
  string method = "fit_eff_plots";
  string canvas = dir+"/"+flag+"/"+method;
  
  plot2Eff(f,f_MC,"Data","MC", canvas, canvas, var, var, var,"PFId");

  // 2D
  //plot2DEff(f, f_MC, "tnpTree/isIDMuon_pt_abseta/fit_eff_plots","pt_abseta_PLOT","isIDMuon");
  
}

