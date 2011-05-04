#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TVectorD.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TTree.h"
#include "TCut.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TMatrixD.h"
#include <iomanip>
#include <iostream>

TH1F* getMeasuredHistoPseudo( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var,  vector<TString> decayMode , double frac){

  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1F *hData = new TH1F("hData","hData",nDet,detBins);

  for(size_t i = 0; i< mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TH1F* hDataTemp = new TH1F(Form("hDataTemp_%s_%s",var.Data(),decayMode[i].Data()),"hDataTemp",nDet,detBins);
    tree->Project(Form("hDataTemp_%s_%s",var.Data(),decayMode[i].Data()),Form("%sttbarM",var.Data()), cut,"",entries*frac, 0);

    hData->Add(hDataTemp);
  }

  return hData;
}

TH1F* getMeasuredHisto( vector<std::string> rdPath, string cutStep){

  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH1F *hData = new TH1F("hData","hData",nDet,detBins);

  for(size_t i = 0; i < rdPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TH1F *hTemp = (TH1F*) f_data->Get(Form("%s/hDataSub_%s_vsumMAlt", cutStep.c_str(), cutStep.c_str()));
    hData->Add(hTemp);
  }

  return hData;
}

TH2F* getResponseM( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var,  vector<TString> decayMode ){

  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};
  float detBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nGen = sizeof(genBins)/sizeof(float) - 1;
  int nDet = sizeof(detBins)/sizeof(float) - 1;

  TH2F *h2_response_m = new TH2F("h2_response_m","h2_response_m",nDet,detBins,nGen,genBins);

  for(size_t i = 0; i < mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TH2F *h2Temp = new TH2F(Form("h2_response_m_%s_%s",var.Data(),decayMode[i].Data()),Form("h2_response_m_%s",var.Data()),nDet,detBins,nGen,genBins);
    tree->Project(Form("h2_response_m_%s_%s",var.Data(),decayMode[i].Data()),Form("genttbarM:%sttbarM",var.Data()),cut, "", entries/2, 0);
    h2_response_m->Add(h2Temp);
  }

  return h2_response_m;
}

TH1F* getGenDistHisto( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var, vector<TString> decayMode ){

  float genBins[] = {0, 350, 400, 450, 500,  550, 600, 700, 800, 1400};

  int nGen = sizeof(genBins)/sizeof(float) - 1;

  TH1F *hGen = new TH1F("hGen","hGen",nGen,genBins);

  for(size_t i = 0; i< mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TH1F *hGenDistTemp = new TH1F(Form("hGenDisTemp_%s_%s",var.Data(),decayMode[i].Data()),"h_genTTbar",nGen,genBins);
    tree->Project(Form("hGenDisTemp_%s_%s",var.Data(),decayMode[i].Data()),"genttbarM", cut,"",entries/2, entries/2);  

    hGen->Add(hGenDistTemp);
  }

  return hGen;

}

TGraphAsymmErrors* getAcceptance(vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var, vector<TString> decayMode ){

  TFile * fDen = new TFile("/home/tjkim/ntuple/top/genTTbar/ttbarGen.root");
  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  TH1F* hDen = new TH1F("hDen", "Denominator", nBinsMass, binsMass);
  TH1F* hNum = new TH1F("hNum", "Numerator", nBinsMass, binsMass);

  genTreeDen->Project("hDen", "tt.M()");

  for(size_t i = 0; i < mcPath.size() ; i++){

    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    TH1F* hNumTemp = new TH1F(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "Numerator", nBinsMass, binsMass);
    tree->Project(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "genttbarM", cut);
    hNum->Add(hNumTemp);
    cout << hNum->GetBinContent(1) << endl;
  }
  cout << hDen->GetBinContent(1) << endl;

  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors();

  for(int i=0; i < nBinsMass; i++){
    int bin = i+1;
    double acc = hNum->GetBinContent(bin)/hDen->GetBinContent(bin);
    double center = hNum->GetBinCenter(bin);
    double width = hNum->GetBinWidth(bin);
    double err = sqrt(hNum->GetBinContent(bin))/hDen->GetBinContent(bin);
    grpAccept->SetPoint(i, center, acc );
    grpAccept->SetPointEXhigh(i, width/2);
    grpAccept->SetPointEXlow(i, width/2);
    grpAccept->SetPointEYhigh(i, err);
    grpAccept->SetPointEYlow(i, err);
    cout << "accept= " << setprecision(4) << acc*100 << " +- " << err*100 << endl;
  }
  cout << "all bins= " << setprecision(4) << 100*hNum->GetEntries()/hDen->GetEntries() << " +- " << 100*sqrt(hNum->GetEntries())/hDen->GetEntries() << endl;
  return grpAccept;

}

TH1F* getAcceptanceHisto(vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var, vector<TString> decayMode ){

  TFile * fDen = new TFile("/home/tjkim/ntuple/top/genTTbar/ttbarGen.root");
  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");

  double binsMass[] = {0, 350, 400, 450, 500, 550, 600, 700, 800, 1400};
  const int nBinsMass = sizeof(binsMass)/sizeof(binsMass[0]) - 1;

  TH1F* hDen = new TH1F("hDen", "Denominator", nBinsMass, binsMass);
  TH1F* hNum = new TH1F("hNum", "Numerator", nBinsMass, binsMass);

  genTreeDen->Project("hDen", "tt.M()");

  for(size_t i = 0; i < mcPath.size() ; i++){

    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    TH1F* hNumTemp = new TH1F(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "Numerator", nBinsMass, binsMass);
    tree->Project(Form("hNumTemp_%s_%s",var.Data(), decayMode[i].Data()), "genttbarM", cut);
    hNum->Add(hNumTemp);
    cout << hNum->GetBinContent(1) << endl;
  }
  cout << hDen->GetBinContent(1) << endl;

  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors();
  TH1F *hAccept = new TH1F("hAccept","hAccept",nBinsMass, binsMass);

  for(int i=0; i < nBinsMass; i++){
    int bin = i+1;
    double acc = hNum->GetBinContent(bin)/hDen->GetBinContent(bin);
    double center = hNum->GetBinCenter(bin);
    double width = hNum->GetBinWidth(bin);
    double err = sqrt(hNum->GetBinContent(bin))/hDen->GetBinContent(bin);

    hAccept->SetBinContent(bin, acc);
    hAccept->SetBinError(bin, err);

    grpAccept->SetPoint(i, center, acc );
    grpAccept->SetPointEXhigh(i, width/2);
    grpAccept->SetPointEXlow(i, width/2);
    grpAccept->SetPointEYhigh(i, err);
    grpAccept->SetPointEYlow(i, err);

    cout << "accept= " << setprecision(4) << acc*100 << " +- " << err*100 << endl;
  }

  TCanvas *c_acc = new TCanvas(Form("c_acc_%s",var.Data()),"acceptance",1);
  grpAccept->Draw("2AP");
  grpAccept->SetFillColor(4);
  grpAccept->SetFillStyle(3001);
  grpAccept->SetTitle("Acceptance ;Generator level M(t#bar{t});Acceptance ");
  grpAccept->SetMinimum(0);

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);

  if( decayMode.size() == 1){
    if( decayMode[0].Contains("MuEl") )
      label->DrawLatex(0.70,0.68,"e#mu");
    if( decayMode[0].Contains("MuMu") )
      label->DrawLatex(0.70,0.68,"#mu#mu");
    if( decayMode[0].Contains("ElEl") )
      label->DrawLatex(0.70,0.68,"ee");
    c_acc->Print(Form("c_accept_%s_%s.eps",decayMode[0].Data(),var.Data()));
  } else {
    label->DrawLatex(0.70,0.68,"ee/#mu#mu/e#mu");
    c_acc->Print(Form("c_accept_all_%s.eps",var.Data()));
  }

  cout << "all bins= " << setprecision(4) << 100*hNum->GetEntries()/hDen->GetEntries() << " +- " << 100*sqrt(hNum->GetEntries())/hDen->GetEntries() << endl;
  return hAccept;

}

