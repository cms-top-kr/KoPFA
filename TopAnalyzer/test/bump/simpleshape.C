#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include <iostream>
#include <fstream>

using namespace std;

void file(const std::string fname, TString name, const std::string decay, double xsection){
  TFile *f = new TFile(Form("../%s_Oct2/%s.root",decay.c_str(), decay.c_str() ));
  TFile *fsig = new TFile(fname.c_str());
  TTree * tree = (TTree *) fsig->Get(Form("%s/tree",decay.c_str())); 
  TH1F * hnum = (TH1F*) fsig->Get(Form("%s/EventSummary", decay.c_str()));
  double lumi = 1143.22;
  double xsec = xsection;
  double num = hnum->GetBinContent(1);
  double lumi_eff = num/xsec;
  double norm = lumi/lumi_eff;

  TH1F* ttbar = (TH1F*)f->Get("Step_7/hMCSig_TTbar_Step_7_vsumMhigh");
  TH1F* signal = new TH1F("signal","signal",100,0,5000);
  TH1F* data = (TH1F*)f->Get("Step_7/hData_Step_7_vsumMhigh");
  TH1F* datasub = (TH1F*)f->Get("Step_7/hDataSub_Step_7_vsumMhigh");
  TH1F* background = (TH1F*)data->Clone("background");
  background->Add(datasub, -1);
  background->Add(ttbar, 1);

  const std::string cutStep = "Step_7";
  TCut cut((f->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());
  tree->Project("signal","ttbar.M()",cut);  

  signal->Scale(norm);
  signal->SetName("signal");
  background->SetName("background");
  data->SetName("data_obs");

  TFile* out = TFile::Open(Form("limit/%s/ZPrime_%s.root", decay.c_str(), name.Data()), "recreate");
  signal->Write();
  background->Write();
  data->Write();  
  cout << "signal= " << signal->Integral() << " data= " << data->Integral() << " background= " << background->Integral() << endl;
  out->Delete();

   
  ofstream fout; 
  fout.open(Form("limit/%s/ZPrime_%s.txt",decay.c_str(), name.Data()));

  fout << "imax 1" << endl;
  fout << "jmax 1" << endl;
  fout << "kmax *" << endl;
  fout << "---------------" << endl;
  fout << "#shapes * * ZPrime_1000.root $PROCESS $PROCESS_$SYSTEMATIC" << endl;
  fout << Form("shapes * * ZPrime_%s.root $PROCESS",name.Data()) << endl;
  fout << "---------------" << endl;
  fout << "bin 1" << endl;
  fout << Form("observation %f",data->Integral()) << endl;
  fout << "------------------------------" << endl;
  fout << "bin             1          1  " << endl;
  fout << "process         signal     background " << endl;
  fout << "process         0          1 " << endl;
  fout << Form("rate       %f         %f ",signal->Integral(), background->Integral()) << endl;
  fout << "--------------------------------" << endl;
  fout << "lumi     lnN    1.04       1.04 " << endl;
  fout << "bgnorm   lnN    1.10       1.10 " << endl;
  fout << "#alpha  shape    -           1   uncertainty on background shape and normalization " << endl;
  fout << "#sigma  shape    0.5         -   uncertainty on signal resolution. Assume the histogram is a 2 sigma shift," << endl; 
  fout << "#                                so divide the unit gaussian by 2 before doing the interpolation" << endl;

  fout.close();
}

void simpleshape(const std::string decay="MuMu"){
  
  const std::string fname500 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM500W1.root";
  const std::string fname750 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM750W1.root";
  const std::string fname1000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1000W1.root";
  const std::string fname1250 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1250W1.root";
  const std::string fname1500 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM1500W1.root";
  const std::string fname2000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM2000W1.root";
  const std::string fname3000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM3000W1.root";
  const std::string fname4000 = "/home/tjkim/ntuple/top/"+decay+"/MC/Summer11_new/vallot_ZPrimeM4000W1.root";

  file(fname500, "500", decay.c_str(), 16.2208794979645);
  file(fname750, "750", decay.c_str(), 3.16951400706147);
  file(fname1000, "1000", decay.c_str(), 0.820761719054490);
  file(fname1250, "1250", decay.c_str(), 0.249122386537253);
  file(fname1500, "1500", decay.c_str(), 8.526785886254366E-002);
  file(fname2000, "2000", decay.c_str(), 1.184858819322720E-002);
  file(fname3000, "3000", decay.c_str(), 3.626054308973676E-004);
  file(fname4000, "4000", decay.c_str(), 4.164114248995513E-005);

}
