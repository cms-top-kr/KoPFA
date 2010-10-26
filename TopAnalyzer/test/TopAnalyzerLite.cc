#include "THStack.h"
#include "TLatex.h"
//#include "TGraphAsymmErrors.h"
#include "TChain.h"
#include "TH1.h"
#include "TCut.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TROOT.h"

#include <iostream>
#include <sstream>
#include <set>
//#include <fstream>
//#include <algorithm>

using namespace std;

class TopAnalyzerLite
{
public:
  TopAnalyzerLite(const string subDirName = "", const string imageOutDir = "image");
  ~TopAnalyzerLite() {};

  void addMC(const string channelName, const string channelLabel, 
             const string fileName, const double xsec, const double nEvents, 
             const Color_t color);
  void addRealData(const string fileName, const double lumi);
  void addCutStep(const TCut cut, const string monitorPlotNames, const double plotScale = 1.0);
  void addMonitorPlot(const string name, const string varexp, const string title,
                      const int nBins, const double xmin, const double xmax, 
                      const double ymin = 0, const double ymax = 0, const bool doLogy = true);

  void applyCutSteps();

private:
  struct Channel
  {
    string name;
    double nEvents;
    double xsec;
    TChain* chain;
    string label;
    Color_t color;
  };

  struct MonitorPlot
  {
    string varexp;
    string title;
    int nBins;
    double xmin, xmax;
    bool doLogy;
    double ymin, ymax;
  };

  struct CutStep
  {
    TCut cut;
    vector<string> monitorPlotNames;
    double plotScale;
  };

  double lumi_;
  string subDirName_;
  vector<Channel> channels_;
  TChain* realDataChain_;

  map<const string, MonitorPlot> monitorPlots_;
  vector<CutStep> cuts_;

  string imageOutDir_;

  void plot(const string name, TCut cut, MonitorPlot& monitorPlot, const double plotScale = 1.0);
  void printStat(const string& name, TCut cut);
};

TopAnalyzerLite::TopAnalyzerLite(const string subDirName, const string imageOutDir)
{
  subDirName_ = subDirName;
  lumi_ = 0;
  realDataChain_ = 0;
  imageOutDir_ = imageOutDir;
}

void TopAnalyzerLite::addMC(const string channelName, const string channelLabel, 
                            const string fileName, const double xsec, const double nEvents, 
                            const Color_t color)
{
  int channelIndex = -1;
  for ( unsigned int i = 0; i < channels_.size(); ++i )
  {
    if ( channels_[i].name == channelName )
    {
      channelIndex = i;
      break;
    }
  }

  if ( channelIndex == -1 )
  {
    Channel channel = {channelName, 0, xsec, 0, channelLabel, color};
    channel.chain = new TChain((subDirName_+"/tree").c_str(), (subDirName_+"/tree").c_str());
    channels_.push_back(channel);
    channelIndex = channels_.size()-1;
  }

  Channel& channel = channels_[channelIndex];

  channel.nEvents += nEvents;
  channel.chain->Add(fileName.c_str());
}

void TopAnalyzerLite::addRealData(const string fileName, const double lumi)
{
  lumi_ += lumi;
  if ( !realDataChain_ )
  {
    gROOT->cd();
    const string chainName = subDirName_+"/tree";
    realDataChain_ = new TChain(chainName.c_str(), chainName.c_str());
  }

  realDataChain_->Add(fileName.c_str());
}

void TopAnalyzerLite::addCutStep(const TCut cut, string monitorPlotNamesStr, const double plotScale)
{
  replace(monitorPlotNamesStr.begin(), monitorPlotNamesStr.end(), ',', ' ');

  vector<string> tokens;
  istringstream iss(monitorPlotNamesStr, istringstream::in);
  string tmpStr;
  while ( iss >> tmpStr ) tokens.push_back(tmpStr);
  CutStep cutStep = {cut, tokens, plotScale};
  cuts_.push_back(cutStep);
}

void TopAnalyzerLite::addMonitorPlot(const string name, const string varexp, const string title,
                                     const int nBins, const double xmin, const double xmax,
                                     const double ymin, const double ymax, const bool doLogy)
{
  MonitorPlot monitorPlot = {varexp, title, nBins, xmin, xmax, doLogy, ymin, ymax};
  monitorPlots_[name] = monitorPlot;
}

void TopAnalyzerLite::applyCutSteps()
{
  cout << "--------------------------------------\n";
  cout << " Cross sections and sample statistics \n";
  for ( unsigned int i=0; i<channels_.size(); ++i )
  {
    Channel& channel = channels_[i];
    cout << " * " << channel.name << "\t" << channel.xsec << " /pb (" << channel.nEvents << ")\n";
  }
  cout << "--------------------------------------\n";

  TCut cut = "";
  for ( unsigned int i=0; i<cuts_.size(); ++i )
  {
    cut = cut && cuts_[i].cut;
    const vector<string>& monitorPlotNames = cuts_[i].monitorPlotNames;
    const double plotScale = cuts_[i].plotScale;

    printStat(Form("Step_%d", i+1), cut);
    for ( unsigned int j = 0; j < monitorPlotNames.size(); ++ j)
    {
      const string& plotName = monitorPlotNames[j];

      if ( monitorPlots_.find(plotName) == monitorPlots_.end() ) continue;
      MonitorPlot& monitorPlot = monitorPlots_[plotName];
      plot(Form("Step_%d_%s", i+1, plotName.c_str()), cut, monitorPlot, lumi_*plotScale);
    }
  }

  cout << "Final" << endl;
  TCut finalCut = "";
  for ( unsigned int i=0; i<cuts_.size(); ++i )
  {
    finalCut = finalCut && cuts_[i].cut;
  }
  realDataChain_->Scan("RUN:LUMI:EVENT:Z.mass():@jetspt30.size():MET",finalCut); 
  cout << "Number of entries after final selection = " << realDataChain_->GetEntries(finalCut) << endl;
}

void TopAnalyzerLite::plot(const string name, const TCut cut, MonitorPlot& monitorPlot, const double plotScale)
{
  const string& varexp = monitorPlot.varexp;
  const string& title = monitorPlot.title;
  const int nBins = monitorPlot.nBins;
  const double xmin = monitorPlot.xmin;
  const double xmax = monitorPlot.xmax;
  double ymin = monitorPlot.ymin;
  double ymax = monitorPlot.ymax;

  TLegend* legend = new TLegend(0.73,0.57,0.88,0.88);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);

  TString dataHistName = Form("hData_%s", name.c_str());
  TH1F* hData = new TH1F(dataHistName, title.c_str(), nBins, xmin, xmax);

  realDataChain_->Project(dataHistName, varexp.c_str(), cut);
  hData->AddBinContent(nBins, hData->GetBinContent(nBins+1));
  hData->Sumw2();
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(1);
  hData->SetTitle(title.c_str());
  hData->SetStats(0);

  legend->AddEntry(hData, "Data", "p");

  THStack* hStack = new THStack("hStack", title.c_str());
  map<string, int> drawnLabels;
  for ( unsigned int i=0; i<channels_.size(); ++i )
  {
    Channel& channel = channels_[i];
    TString mcHistName = Form("hMC_%s_%s", channel.name.c_str(), name.c_str());
    TH1F* hMC = new TH1F(mcHistName, title.c_str(), nBins, xmin, xmax);

    channel.chain->Project(mcHistName, varexp.c_str(), cut);
    hMC->AddBinContent(nBins, hMC->GetBinContent(nBins+1));
    hMC->Scale(lumi_*channel.xsec/channel.nEvents);
    hMC->SetFillColor(channel.color);

    // Add to the HStack if there's no duplicated label
    // If duplicated label exists, call TH1::Add
    map<string, int>::const_iterator drawnLabel = drawnLabels.find(channel.label);
    if ( drawnLabel == drawnLabels.end() ) 
    {
      legend->AddEntry(hMC, channel.label.c_str(), "f");
      drawnLabels.insert(make_pair(channel.label, i));
      hStack->Add(hMC);
    }
    else
    {
      // Find previously added histogram in the HStack
      const unsigned int index = drawnLabel->second;
      const char* prevChannel = channels_[index].name.c_str();
      const TString prevHistName = Form("hMC_%s_%s", prevChannel, name.c_str());

      TH1F* h = (TH1F*)(hStack->GetStack()->FindObject(prevHistName));
      if ( h ) h->Add(hMC);
    }
  }

  TCanvas* c = new TCanvas(Form("c_%s", name.c_str()), name.c_str(), 1);
  if ( ymax == 0 )
  {
    const int dataMaxBin = hData->GetMaximumBin();
    const double dataYmax = hData->GetBinContent(dataMaxBin) + hData->GetBinError(dataMaxBin);
    const double mcYmax = hStack->GetMaximum();

    ymax = TMath::Max(dataYmax, mcYmax);
  }

  if ( monitorPlot.doLogy ) 
  {
    if ( ymin <= 0 ) ymin = 1e-2;
    c->SetLogy();
  }

  hStack->SetMinimum(ymin);
  hStack->SetMaximum(ymax);

  hStack->Draw();
  hData->Draw("same");
  legend->Draw();

  if ( imageOutDir_ != "" )
  {
    c->Print((imageOutDir_+"/"+c->GetName()+".png").c_str());
    c->Print((imageOutDir_+"/"+c->GetName()+".eps").c_str());
  }
}

void TopAnalyzerLite::printStat(const string& name, TCut cut)
{
  cout << "------------------------\n";
  cout << "   " << name << endl;

  const double nData = realDataChain_->GetEntries(cut);

  double nTotal = 0, nSignal = 0;
  double nTotalErr2 = 0, nSignalErr = 0;
  for ( unsigned int i=0; i<channels_.size(); ++i )
  {
    Channel& channel = channels_[i];

    const double norm = lumi_*channel.xsec/channel.nEvents;
    const double nEvents = channel.chain->GetEntries(cut)*norm;
    const double nEventsErr2 = nEvents*norm;
    const double nEventsErr = sqrt(nEventsErr2);
    
    cout << channel.name << ' ' << nEvents << " +- " << nEventsErr << endl;
    if ( channel.name == "TTbar" )
    {
      nSignal = nEvents;
      nSignalErr = nEventsErr;
    }
    nTotal += nEvents;
    nTotalErr2 += nEventsErr2;
  }

  const double nBkg = nTotal - nSignal;
  const double signif = nSignal/sqrt(nTotal);
  const double nTotalErr = sqrt(nTotalErr2);

  cout << "Total       = " << nTotal << " +- " << nTotalErr << endl;
  cout << "------------------------------" << endl;
  cout << "Data        = " << nData << endl;
  cout << "S/sqrt(S+B) = " << signif << endl;
  cout << "------------------------------" << endl;
}

