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


Eff2Dplot(){

  ofstream fout; 
  ofstream fout2; 
  fout.open("Efficiency_Table_Iso.txt"); 
  fout2.open("Efficiency_Table_ID.txt"); 

  gStyle->SetPalette(1);
  gStyle->SetPaintTextFormat("5.3f");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

  TString hName = "isIso";
  TString plot = "pt_abseta_PLOT";
  TString var = "pt_abseta";

  TString FileIso=   "./data4/Efficiency_Iso_data.root";
  TString FileIso_mc="./mc4/Efficiency_Iso_mc.root";
  TString FileID=    "./data4/Efficiency_ID_data.root";
  TString FileID_mc= "./mc4/Efficiency_ID_mc.root";

  TString DirID="tnpTree/ID_pt_abseta/fit_eff_plots";
  TString DirIso="tnpTreeIso/pt_abseta/fit_eff_plots";

//////////////////////////
  TFile * f_Iso = new TFile(Form("%s",FileIso.Data()));
  f_Iso->cd("tnpTreeIso/pt_abseta/fit_eff_plots");
  TCanvas* cc1 = (TCanvas*) gDirectory->FindKey("pt_abseta_PLOT")->ReadObj();
  TH2* hh1 = (TH2F*) cc1->FindObject("pt_abseta_PLOT");
  cout << "---" << "pt_abseta_PLOT" << "---" << hName << "---" << endl;
  hh1->SetMarkerSize(1.9);
  hh1->GetXaxis()->SetMoreLogLabels(true);
  hh1->SetLabelOffset(0.0005);
  hh1->SetTitleOffset(1.08);
  cc1->SetLogx();
  cc1->Draw();
  cc1->Print("Eff_Iso_data_"+var+".gif");
  cc1->Print("Eff_Iso_data_"+var+".png");
  cc1->Print("Eff_Iso_data_"+var+".eps");

//////////////////////////
  TFile * f_Isomc = new TFile(Form("%s",FileIso_mc.Data()));
  f_Isomc->cd("tnpTreeIso/pt_abseta/fit_eff_plots");
  TCanvas* cc2 = (TCanvas*) gDirectory->FindKey("pt_abseta_PLOT")->ReadObj();
  TH2* hh2 = (TH2F*) cc2->FindObject("pt_abseta_PLOT");
  cout << "---" << "pt_abseta_PLOT" << "---" << hName << "---" << endl;
  hh2->SetMarkerSize(1.9);
  hh2->GetXaxis()->SetMoreLogLabels(true);
  hh2->SetLabelOffset(0.0005);
  hh2->SetTitleOffset(1.08);
  cc2->SetLogx();
  cc2->Draw();
  cc2->Print("Eff_Iso_mc_"+var+".gif");
  cc2->Print("Eff_Iso_mc_"+var+".png");
  cc2->Print("Eff_Iso_mc_"+var+".eps");

///////////////////////////////////////////////////////////////////
//  For print out the efficiency into a file
///////////////////////////////////////////////////////////////////
/*  int nbinx = hh1->GetNbinsX();
  int nbiny = hh1->GetNbinsY();
    cout << "//////////////////////////////" << endl;
  string tablefordata;
  string tableformc;
  string tableforscale;
  string columnfortable;
    cout << "//////////////////////////////" << endl;
  for(int i=1; i <=nbinx ; i++){
    string si = int2string(i);
    string slowedge = int2string(hh1->GetBinLowEdge(i));
    int highedge = hh1->GetBinLowEdge(i) + hh1->GetBinWidth(i);
    string shighedge = int2string(highedge);
    string temp = "$"+slowedge + " \\GeV < p_{T} < " + shighedge+ " \\GeV$";
    tablefordata += temp;
    tableformc += temp;
    tableforscale += temp;
    for(int j=1; j <=nbiny ; j++){
      string sj = int2string(j);
      if(i==1) {
        string slowedgey = float2string(hh1->ProfileY()->GetBinLowEdge(j),1);
        float highedgey = hh1->ProfileY()->GetBinLowEdge(j) + hh1->ProfileY()->GetBinWidth(j);
        string shighedgey = float2string(highedgey,1);

        if(j==1) {
          columnfortable += "Selection";
          columnfortable = columnfortable + " ~&~ " + " $|\\eta|<"+ shighedgey +"$";
        }else if( j == nbiny ){
          columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
          columnfortable += "\\\\ \\hline";
        }else columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
      }

      float effdata = hh1->GetBinContent(i,j);
      float errdata = hh1->GetBinError(i,j);
      float effmc = hh2->GetBinContent(i,j);
      float errmc = hh2->GetBinError(i,j);

      string seffdata = float2string(effdata,4);
      string serrdata = float2string(errdata,4);
      string seffmc = float2string(effmc,4);
      string serrmc = float2string(errmc,4);

      tablefordata = tablefordata+" ~&~ "+seffdata + "$\\pm$" + serrdata;
      tableformc = tableformc+" ~&~ "+seffmc + "$\\pm$" + serrmc;

      float scale = hh1->GetBinContent(i,j)/hh2->GetBinContent(i,j);
      float scale_err = hh1->GetBinError(i,j)/hh2->GetBinContent(i,j);

      string sscale = float2string(scale,4);
      string sscale_err = float2string(scale_err,4);

      tableforscale = tableforscale+" ~&~ "+ sscale+ "$\\pm$"+ sscale_err;
    }

    tablefordata = tablefordata + "\\\\ \n";
    tableformc = tableformc + "\\\\ \n";
    tableforscale = tableforscale + "\\\\ \n";
  }

  fout.precision(5);
  fout << "efficiency for data" << endl;
  fout << columnfortable << endl;
  fout << tablefordata << endl;
  fout << "efficiency for mc" << endl;
  fout << columnfortable << endl;
  fout << tableformc << endl;
  fout << "scale factor" << endl;
  fout << columnfortable << endl;
  fout << tableforscale << endl;
*/
////////////////////////////////////////////////////////////////////////////
  TFile * f_ID = new TFile(Form("%s",FileID.Data()));
  f_ID->cd("tnpTree/ID_pt_abseta/fit_eff_plots");
  TCanvas* cc3 = (TCanvas*) gDirectory->FindKey("pt_abseta_PLOT")->ReadObj();
  TH2* hh3 = (TH2F*) cc3->FindObject("pt_abseta_PLOT");
  cout << "---" << "pt_abseta_PLOT" << "---" << hName << "---" << endl;
  hh3->SetMarkerSize(1.9);
  hh3->GetXaxis()->SetMoreLogLabels(true);
  hh3->SetLabelOffset(0.0005);
  hh3->SetTitleOffset(1.08);
  cc3->SetLogx();
  cc3->Draw();
  cc3->Print("Eff_ID_data_"+var+".gif");
  cc3->Print("Eff_ID_data_"+var+".png");
  cc3->Print("Eff_ID_data_"+var+".eps");

//////////////////////////
  TFile * f_IDmc = new TFile(Form("%s",FileID_mc.Data()));
  f_IDmc->cd("tnpTree/ID_pt_abseta/fit_eff_plots");
  TCanvas* cc4 = (TCanvas*) gDirectory->FindKey("pt_abseta_PLOT")->ReadObj();
  TH2* hh4 = (TH2F*) cc4->FindObject("pt_abseta_PLOT");
  cout << "---" << "pt_abseta_PLOT" << "---" << hName << "---" << endl;
  hh4->SetMarkerSize(1.9);
  hh4->GetXaxis()->SetMoreLogLabels(true);
  hh4->SetLabelOffset(0.0005);
  hh4->SetTitleOffset(1.08);
  cc4->SetLogx();
//  cc4->Draw();
//  cc4->Print("Eff_ID_mc_"+var+".gif");
//  cc4->Print("Eff_ID_mc_"+var+".png");
//  cc4->Print("Eff_ID_mc_"+var+".eps");
////////////////////////////////////////////////////////////////////
//  For print out the efficiency into a file
////////////////////////////////////////////////////////////////////
/*  int nbinx = hh3->GetNbinsX();
  int nbiny = hh3->GetNbinsY();
    cout << "//////////////////////////////" << endl;
  string tablefordata;
  string tableformc;
  string tableforscale;
  string columnfortable;
    cout << "//////////////////////////////" << endl;
  for(int i=1; i <=nbinx ; i++){
    string si = int2string(i);
    string slowedge = int2string(hh3->GetBinLowEdge(i));
    int highedge = hh3->GetBinLowEdge(i) + hh3->GetBinWidth(i);
    string shighedge = int2string(highedge);
    string temp = "$"+slowedge + " \\GeV < p_{T} < " + shighedge+ " \\GeV$";
    tablefordata += temp;
    tableformc += temp;
    tableforscale += temp;
    for(int j=1; j <=nbiny ; j++){
      string sj = int2string(j);
      if(i==1) {
        string slowedgey = float2string(hh3->ProfileY()->GetBinLowEdge(j),1);
        float highedgey = hh3->ProfileY()->GetBinLowEdge(j) + hh3->ProfileY()->GetBinWidth(j);
        string shighedgey = float2string(highedgey,1);

        if(j==1) {
          columnfortable += "Selection";
          columnfortable = columnfortable + " ~&~ " + " $|\\eta|<"+ shighedgey +"$";
        }else if( j == nbiny ){
          columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
          columnfortable += "\\\\ \\hline";
        }else columnfortable = columnfortable + " ~&~ " + "$"+slowedgey + "<|\\eta|<"+ shighedgey +"$";
      }

      float effdata = hh3->GetBinContent(i,j);
      float errdata = hh3->GetBinError(i,j);
      float effmc = hh4->GetBinContent(i,j);
      float errmc = hh4->GetBinError(i,j);

      string seffdata = float2string(effdata,4);
      string serrdata = float2string(errdata,4);
      string seffmc = float2string(effmc,4);
      string serrmc = float2string(errmc,4);

      tablefordata = tablefordata+" ~&~ "+seffdata + "$\\pm$" + serrdata;
      tableformc = tableformc+" ~&~ "+seffmc + "$\\pm$" + serrmc;

      float scale = hh3->GetBinContent(i,j)/hh4->GetBinContent(i,j);
      float scale_err = hh3->GetBinError(i,j)/hh4->GetBinContent(i,j);

      string sscale = float2string(scale,4);
      string sscale_err = float2string(scale_err,4);

      tableforscale = tableforscale+" ~&~ "+ sscale+ "$\\pm$"+ sscale_err;
    }

    tablefordata = tablefordata + "\\\\ \n";
    tableformc = tableformc + "\\\\ \n";
    tableforscale = tableforscale + "\\\\ \n";
  }

  fout2.precision(5);
  fout2 << "efficiency for data" << endl;
  fout2 << columnfortable << endl;
  fout2 << tablefordata << endl;
  fout2 << "efficiency for mc" << endl;
  fout2 << columnfortable << endl;
  fout2 << tableformc << endl;
  fout2 << "scale factor" << endl;
  fout2 << columnfortable << endl;
  fout2 << tableforscale << endl;
*/
//////////////////////////
  fout.close();
  fout2.close();

}
