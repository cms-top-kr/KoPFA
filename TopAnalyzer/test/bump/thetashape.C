#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include <iostream>
#include <fstream>

using namespace std;

TH1F* file(const std::string fname, TString name, const std::string decay, double xsection, double luminosity, TCut cut){
  TFile *fsig = new TFile(fname.c_str());
  TTree * tree = (TTree *) fsig->Get(Form("%s/tree",decay.c_str()));
  TH1F * hnum = (TH1F*) fsig->Get(Form("%s/EventSummary", decay.c_str()));
  double lumi = luminosity;
  double xsec = xsection;
  double num = hnum->GetBinContent(1);
  double lumi_eff = num/xsec;
  double norm = lumi/lumi_eff;

  TH1F* signal = new TH1F(Form("signal_%s",name.Data()),"signal",50,0,2500);
  tree->Project(Form("signal_%s",name.Data()),"ttbar.M()",cut);

  signal->Scale(norm);
  signal->SetName(Form("%s_mtt__zp%s",decay.c_str(), name.Data()));

  return signal;
}

void thetashape(const std::string decay="MuMu"){

  const std::string fname500 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM500W1.root";
  const std::string fname750 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM750W1.root";
  const std::string fname1000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1000W1.root";
  const std::string fname1250 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1250W1.root";
  const std::string fname1500 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1500W1.root";
  const std::string fname2000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM2000W1.root";
  const std::string fname3000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM3000W1.root";
  const std::string fname4000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM4000W1.root";

  TFile *f = new TFile(Form("../%s_Nov10/%s.root",decay.c_str(), decay.c_str() ));
  TH1F* ttbar = (TH1F*)f->Get("Step_7/hMCSig_TTbar_Step_7_vsumMhigh");
  TH1F* data = (TH1F*)f->Get("Step_7/hData_Step_7_vsumMhigh");
  TH1F* datasub = (TH1F*)f->Get("Step_7/hDataSub_Step_7_vsumMhigh");
  TH1F* background = (TH1F*)data->Clone("background");
  background->Add(datasub, -1);
  background->Add(ttbar, 1);
  background->SetName(Form("%s_mtt__background",decay.c_str()));
  data->SetName(Form("%s_mtt__DATA",decay.c_str()));

  double lumi = 4684;
  const std::string cutStep = "Step_7";
  TCut cut((f->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

  TH1F* signal_500 = file(fname500, "500", decay.c_str(), 16.2208794979645, lumi, cut);
  TH1F* signal_750 = file(fname750, "750", decay.c_str(), 3.16951400706147, lumi, cut);
  TH1F* signal_1000 = file(fname1000, "1000", decay.c_str(), 0.820761719054490, lumi, cut);
  TH1F* signal_1250 = file(fname1250, "1250", decay.c_str(), 0.249122386537253, lumi, cut);
  TH1F* signal_1500 = file(fname1500, "1500", decay.c_str(), 8.526785886254366E-002, lumi, cut);
  TH1F* signal_2000 = file(fname2000, "2000", decay.c_str(), 1.184858819322720E-002, lumi, cut);
  TH1F* signal_3000 = file(fname3000, "3000", decay.c_str(), 3.626054308973676E-004, lumi, cut);
  TH1F* signal_4000 = file(fname4000, "4000", decay.c_str(), 4.164114248995513E-005, lumi, cut);

  TFile* out = TFile::Open(Form("Zprime_histograms_%s.root",decay.c_str()), "recreate");
  signal_500->Write();
  signal_750->Write();
  signal_1000->Write();
  signal_1250->Write();
  signal_1500->Write();
  signal_2000->Write();
  signal_3000->Write();
  signal_4000->Write();
  background->Write();
  data->Write();  
  out->Delete();
}
