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

TH1F* getMeasuredHistoPseudo( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var,  vector<TString> decayMode , double frac, TString name, string weight=""){

  TH1F *hData = new TH1F(Form("hPseudoData_%s",name.Data()),Form("hPseudoData_%s",name.Data()),nDet,detBins);

  for(size_t i = 0; i< mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TCut cutStr = "";
    if( weight != ""){
      cutStr = Form("(%s)*(%s)", weight.c_str(), (const char*)cut );
    }else{
      cutStr = Form("%s", (const char*)cut );
    }

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();
    TH1F* hDataTemp = new TH1F(Form("hDataTemp_%s_%s",name.Data(),decayMode[i].Data()),"hDataTemp",nDet,detBins);
    tree->Project(Form("hDataTemp_%s_%s",name.Data(),decayMode[i].Data()),Form("%s",var.Data()), cutStr, "",entries*frac, 0);
    hData->Add(hDataTemp);
  }

  return hData;
}

TH1F* getMeasuredHisto( vector<std::string> rdPath, string cutStep, TString var = "vsumMAlt" , TString name = ""){

  TH1F *hData = new TH1F(Form("hData_%s",name.Data()),Form("hData_%s",name.Data()),nDet,detBins);

  for(size_t i = 0; i < rdPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TH1F *hTemp = (TH1F*) f_data->Get(Form("%s/hDataSub_%s_%s", cutStep.c_str(), cutStep.c_str(), var.Data()));
    hData->Add(hTemp);
  }

  return hData;
}

TH1F* getMeasuredHistoNew( vector<std::string> rdPath, string cutStep, TString var = "vsumMAlt" , TString name = ""){

  TH1F *hData = new TH1F(Form("hData_%s",name.Data()),Form("hData_%s",name.Data()),nDet,detBins);

  for(size_t i = 0; i < rdPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TList* keys = f_data->GetDirectory(cutStep.c_str())->GetListOfKeys();

    for ( int j=0; j<keys->GetSize(); ++j )
    {
      TString key = keys->At(j)->GetName();
      if ( !key.EndsWith( Form("_%s", var.Data()) )) continue;

      TString histPath = Form("%s/%s", cutStep.c_str(), key.Data());
      TH1F* hTemp = (TH1F*)f_data->Get(histPath);

      if ( !hTemp ) { cout << "No hist" << endl; continue; }

      if ( key.BeginsWith("hMC_") )
      {
        hData->Add(hTemp, -1);
      }
      else if ( key.BeginsWith("hData_") )
      {
        hData->Add(hTemp);
      }
    }
  }

  return hData;
}

TH2F* getResponseM( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, TString var,  vector<TString> decayMode , bool split, TString name){

  TH2F *h2_response_m = new TH2F("h2_response_m","h2_response_m",nDet,detBins,nGen,genBins);

  for(size_t i = 0; i < mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TCut mcCutStr = "";
    mcCutStr = Form("%s*(%s)", "weightin", (const char*)(cut));

    TH2F *h2Temp = new TH2F(Form("h2_response_m_%s_%s",name.Data(),decayMode[i].Data()),Form("h2_response_m_%s",var.Data()),nDet,detBins,nGen,genBins);
    if(split)
      tree->Project(Form("h2_response_m_%s_%s",name.Data(),decayMode[i].Data()),Form("genttbarM:%s",var.Data()),mcCutStr, "", entries/2, 0);
    else 
      tree->Project(Form("h2_response_m_%s_%s",name.Data(),decayMode[i].Data()),Form("genttbarM:%s",var.Data()),mcCutStr);
    h2_response_m->Add(h2Temp);
  }

  return h2_response_m;
}


TH1F* getGenDistHisto( vector<std::string> rdPath, string cutStep, TString var = "genttbarM2" , TString name = ""){

  TH1F *hGen = new TH1F(Form("hTruth_%s",name.Data()), "truth distribution after reconstructed level selection",nGen,genBins);

  for(size_t i = 0; i < rdPath.size() ; i++){
    TFile * f = new TFile(rdPath[i].c_str());
    TH1F *hTemp = (TH1F*) f->Get(Form("%s/hMCSig_TTbar_%s_%s", cutStep.c_str(), cutStep.c_str(), var.Data()));
    hGen->Add(hTemp);
  }

  return hGen;
}


TH1F* getGenDistHisto( vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, vector<TString> decayMode, double scale, bool split , TString name, string weight="" ){

  TH1F *hGen = new TH1F(Form("hTruth_%s",name.Data()), "truth distribution after reconstructed level selection",nGen,genBins);

  for(size_t i = 0; i< mcPath.size() ; i++){
    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());

    TCut cutStr = "";
    if( weight != ""){
      cutStr = Form("(%s)*(%s)", weight.c_str(), (const char*)cut );
    }else{
      cutStr = Form("%s", (const char*)cut );
    }

    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");

    int entries = tree->GetEntries();

    TH1F *hGenDistTemp = new TH1F(Form("hGenDisTemp_%s_%s",name.Data(),decayMode[i].Data()),"hGenDisTemp",nGen,genBins);
    if(split){
      tree->Project(Form("hGenDisTemp_%s_%s",name.Data(),decayMode[i].Data()),"genttbarM", cutStr,"",entries/2, entries/2);  
      hGenDistTemp->Scale(scale*2);
    } else{
      tree->Project(Form("hGenDisTemp_%s_%s",name.Data(),decayMode[i].Data()),"genttbarM", cutStr);  
      hGenDistTemp->Scale(scale);
    }
    hGen->Add(hGenDistTemp);

  }

  //put statistical error
  for(int i=0; i < nGen ; i++){
    double err = sqrt(hGen->GetBinContent(i+1))*sqrt(scale*2) ;
    hGen->SetBinError(i+1,err);
  }

  return hGen;

}

TH1D* getTruthHisto(TFile * fDen, TString name, double scale, TCut visible ="" ){

  TTree* genTree = (TTree*)fDen->Get("ttbarGenAna/tree");
  TH1D* h_Gen = new TH1D(Form("hTruthFinal%s",name.Data()), Form("hGen%s",name.Data()), 1400, 0, 1400);
  genTree->Project(Form("hTruthFinal%s",name.Data()), "ttbarGen.m()",visible);
  h_Gen->Scale(scale);

  return h_Gen;
}

TH1F* getAcceptanceHisto(vector<std::string> mcPath, vector<std::string> rdPath, string cutStep, vector<TString> decayMode, TString name, TCut visible =""){

  TFile * fDen = new TFile("/data/export/common/Top/ntuple/ttbarGen.root");
  TTree* genTreeDen = (TTree*)fDen->Get("ttbarGenAna/tree");

  TH1F* hDen = new TH1F("hDen", "Denominator", nGen, genBins);
  TH1F* hNum = new TH1F("hNum", "Numerator", nGen, genBins);

  genTreeDen->Project("hDen", "ttbarGen.m()",visible);

  for(size_t i = 0; i < mcPath.size() ; i++){

    TFile * f_data = new TFile(rdPath[i].c_str());
    TCut cut((f_data->Get(Form("%s/cut", cutStep.c_str())))->GetTitle());
    TFile * file = new TFile(mcPath[i].c_str());
    TTree * tree = (TTree *) file->Get(decayMode[i]+"/tree");
    TH1F* hNumTemp = new TH1F(Form("hNumTemp_%s_%s",name.Data(), decayMode[i].Data()), "Numerator", nGen, genBins);
    tree->Project(Form("hNumTemp_%s_%s",name.Data(), decayMode[i].Data()), "genttbarM", cut);
    hNum->Add(hNumTemp);
    cout << hNumTemp->GetEntries() << endl;

    TGraphAsymmErrors* grpAcceptTmp = new TGraphAsymmErrors();

    cout << "decay: " << decayMode[i].Data() << endl;

    for(int j=0; j < nGen; j++){
      int bin = j+1;

      double acc = 0;
      double den = hDen->GetBinContent(bin);
      double num = hNumTemp->GetBinContent(bin); 
      if( den != 0) acc = num/den;
      else acc = 0.0;

      double center = hNumTemp->GetBinCenter(bin);
      double width = hNumTemp->GetBinWidth(bin);
      double err = sqrt(num)/den;

      grpAcceptTmp->SetPoint(j, center, acc );
      grpAcceptTmp->SetPointEXhigh(j, width/2);
      grpAcceptTmp->SetPointEXlow(j, width/2);
      grpAcceptTmp->SetPointEYhigh(j, err);
      grpAcceptTmp->SetPointEYlow(j, err);

      cout << "accept= " << setprecision(4) << acc*100 << " $\\pm$ " << err*100 << endl;
    }
    cout << "all bins= " << setprecision(4) << 100*hNumTemp->GetEntries()/hDen->GetEntries() << " $\\pm$ " << 100*sqrt(hNumTemp->GetEntries())/hDen->GetEntries() << endl;

    TCanvas *c_accTmp = new TCanvas(Form("c_acc_%s_%s",decayMode[i].Data(), name.Data()),"acceptance",1);
    grpAcceptTmp->Draw("2AP");
    grpAcceptTmp->SetFillColor(4);
    grpAcceptTmp->SetFillStyle(3001);
    grpAcceptTmp->SetTitle("Aceeptance ;Generator level M(t#bar{t});Acceptance ");
    grpAcceptTmp->SetMinimum(0);

    TLatex *labelTmp= new TLatex;
    labelTmp->SetNDC();
    labelTmp->SetTextSize(0.05);

    if( decayMode[i].Contains("MuEl") ) labelTmp->DrawLatex(0.70,0.68,"e#mu");
    if( decayMode[i].Contains("MuMu") ) labelTmp->DrawLatex(0.70,0.68,"#mu#mu");
    if( decayMode[i].Contains("ElEl") ) labelTmp->DrawLatex(0.70,0.68,"ee");

    c_accTmp->Print(Form("c_accept_%s_%s.eps",decayMode[i].Data(),name.Data()));

  }
  cout << hDen->GetEntries() << endl;
  
  TGraphAsymmErrors* grpAccept = new TGraphAsymmErrors();
  TH1F *hAccept = new TH1F(Form("hAccept_%s",name.Data()),Form("hAccept_%s",name.Data()),nGen, genBins);

  for(int i=0; i < nGen; i++){
    int bin = i+1;

    double acc = 0;
    double den = hDen->GetBinContent(bin);
    double num = hNum->GetBinContent(bin);
    if( den != 0) acc = num/den;
    else acc = 0.0;

    double center = hNum->GetBinCenter(bin);
    double width = hNum->GetBinWidth(bin);
    double err = sqrt(num)/den;

    hAccept->SetBinContent(bin, acc);
    hAccept->SetBinError(bin, err);

    grpAccept->SetPoint(i, center, acc );
    grpAccept->SetPointEXhigh(i, width/2);
    grpAccept->SetPointEXlow(i, width/2);
    grpAccept->SetPointEYhigh(i, err);
    grpAccept->SetPointEYlow(i, err);

    cout << "accept= " << setprecision(4) << acc*100 << " $\\pm$ " << err*100 << endl;
  }
  cout << "all bins= " << setprecision(4) << 100*hNum->GetEntries()/hDen->GetEntries() << " $\\pm$ " << 100*sqrt(hNum->GetEntries())/hDen->GetEntries() << endl;

  TCanvas *c_acc = new TCanvas(Form("c_acc_%s",name.Data()),"acceptance",1);
  grpAccept->Draw("2AP");
  grpAccept->SetFillColor(4);
  grpAccept->SetFillStyle(3001);
  grpAccept->SetTitle("Aceeptance ;Generator level M(t#bar{t});Acceptance ");
  grpAccept->SetMinimum(0);

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);

  label->DrawLatex(0.70,0.68,"ee/#mu#mu/e#mu");
  c_acc->Print(Form("c_accept_all_%s.eps",name.Data()));

  return hAccept;

}

