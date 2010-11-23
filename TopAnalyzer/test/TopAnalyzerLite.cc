#include "TROOT.h"
#include "TSystem.h"

#include "TCut.h"
#include "TFile.h"
#include "TChain.h"
#include "TTreePlayer.h"

#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TH1F.h"
#include "THStack.h"

#include "TMath.h"

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

class TopAnalyzerLite
{
public:
  TopAnalyzerLite(const string subDirName = "", const string imageOutDir = "");
  ~TopAnalyzerLite();

  void addMC(const string mcSampleName, const string mcSampleLabel,
             const string fileName, const double xsec, const double nEvents,
             const Color_t color);
  void addRealData(const string fileName, const double lumi);
  void addCutStep(const TCut cut, const TString monitorPlotNamesStr, const double plotScale = 1.0);
  void addMonitorPlot(const string name, const string varexp, const string title,
                      const int nBins, const double xmin, const double xmax,
                      const double ymin = 0, const double ymax = 0, const bool doLogy = true);

  void applyCutSteps();
  void applySingleCut(const TCut cut, const TString monitirPlotNamesStr);
  void saveHistograms(TString fileName = "");

private:
  TObjArray getHistograms();

  struct MCSample
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

  struct Stat
  {
    string name, label;
    double nEvents, nEventsErr2;
  };

  double lumi_;
  string subDirName_;
  vector<MCSample> mcSamples_;
  TChain* realDataChain_;

  map<const string, MonitorPlot> monitorPlots_;
  vector<CutStep> cuts_;

  string imageOutDir_;

  void plot(const string name, TCut cut, MonitorPlot& monitorPlot, const double plotScale = 1.0);
  void printStat(const string& name, TCut cut);

  TObjArray histograms_;
  ofstream fout_;
  bool writeSummary_;

  TDirectory* baseRootDir_;
};

TopAnalyzerLite::TopAnalyzerLite(const string subDirName, const string imageOutDir)
{
  subDirName_ = subDirName;
  lumi_ = 0;
  realDataChain_ = 0;
  imageOutDir_ = imageOutDir;

  baseRootDir_ = gROOT->mkdir(subDirName_.c_str());

  if ( imageOutDir != "" )
  {
    gSystem->mkdir(imageOutDir.c_str(), true);
    fout_.open((imageOutDir+"/summary.txt").c_str());
    writeSummary_ = true;
  }
  else writeSummary_ = false;
}

TopAnalyzerLite::~TopAnalyzerLite()
{
  if ( writeSummary_ ) fout_.close();
}

void TopAnalyzerLite::addMC(const string mcSampleName, const string mcSampleLabel,
                            const string fileName, const double xsec, const double nEvents,
                            const Color_t color)
{
  int mcSampleIndex = -1;
  for ( unsigned int i = 0; i < mcSamples_.size(); ++i )
  {
    if ( mcSamples_[i].name == mcSampleName )
    {
      mcSampleIndex = i;
      break;
    }
  }

  if ( mcSampleIndex == -1 )
  {
    MCSample mcSample = {mcSampleName, 0, xsec, 0, mcSampleLabel, color};
    baseRootDir_->cd();
    mcSample.chain = new TChain((subDirName_+"/tree").c_str(), (subDirName_+"/tree").c_str());
    mcSamples_.push_back(mcSample);
    mcSampleIndex = mcSamples_.size()-1;
  }

  MCSample& mcSample = mcSamples_[mcSampleIndex];

  mcSample.nEvents += nEvents;
  mcSample.chain->Add(fileName.c_str());
}

void TopAnalyzerLite::addRealData(const string fileName, const double lumi)
{
  lumi_ += lumi;
  if ( !realDataChain_ )
  {
    const string chainName = subDirName_+"/tree";
    baseRootDir_->cd();
    realDataChain_ = new TChain(chainName.c_str(), chainName.c_str());
  }

  realDataChain_->Add(fileName.c_str());
}

void TopAnalyzerLite::addCutStep(const TCut cut, TString monitorPlotNamesStr, const double plotScale)
{
  TObjArray* monitorPlotNames = monitorPlotNamesStr.Tokenize(",");
  const int nPlots = monitorPlotNames->GetSize();

  vector<string> plotNames;
  for ( int i=0; i<nPlots; ++i )
  {
    TObject* obj = monitorPlotNames->At(i);
    if ( !obj ) continue;

    const string plotName = obj->GetName();
  
    plotNames.push_back(plotName);
  }

  CutStep cutStep = {cut, plotNames, plotScale};
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
  if ( writeSummary_ )
  {
    fout_ << "--------------------------------------\n";
    fout_ << " Cross sections and sample statistics \n";
  }
  for ( unsigned int i=0; i<mcSamples_.size(); ++i )
  {
    MCSample& mcSample = mcSamples_[i];
    cout << " * " << mcSample.name << "\t" << mcSample.xsec << " /pb (" << mcSample.nEvents << ")\n";
    if ( writeSummary_ ) fout_ << " * " << mcSample.name << "\t" << mcSample.xsec << " /pb (" << mcSample.nEvents << ")\n";
  }
  cout << "--------------------------------------\n";
  if ( writeSummary_ ) fout_ << "--------------------------------------\n";

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
  if ( writeSummary_ ) fout_ << "Final" << endl;
  TCut finalCut = "";
  for ( unsigned int i=0; i<cuts_.size(); ++i )
  {
    finalCut = finalCut && cuts_[i].cut;
  }
  if ( realDataChain_ )
  {
    realDataChain_->Scan("RUN:LUMI:EVENT:Z.mass():@jetspt30.size():MET",finalCut);
    cout << "Number of entries after final selection = " << realDataChain_->GetEntries(finalCut) << endl;
  }

  if ( writeSummary_ && realDataChain_ )
  {
    const string tmpFileName = imageOutDir_+"/tmp.txt";

    ((TTreePlayer*)(realDataChain_->GetPlayer()))->SetScanRedirect(true);
    ((TTreePlayer*)(realDataChain_->GetPlayer()))->SetScanFileName(tmpFileName.c_str());
    realDataChain_->Scan("RUN:LUMI:EVENT:Z.mass():@jetspt30.size():MET",finalCut);
    ((TTreePlayer*)(realDataChain_->GetPlayer()))->SetScanRedirect(false);

    ifstream tmpFile(tmpFileName.c_str());
    copy(istreambuf_iterator<char>(tmpFile), istreambuf_iterator<char>(), ostreambuf_iterator<char>(fout_));
    fout_ << "Number of entries after final selection = " << realDataChain_->GetEntries(finalCut) << endl;

    gSystem->Exec(("rm -f "+tmpFileName).c_str());
  }
}

void TopAnalyzerLite::plot(const string name, const TCut cut, MonitorPlot& monitorPlot, const double plotScale)
{
  const string& varexp = monitorPlot.varexp;
  const string& title = monitorPlot.title;
  const int nBins = monitorPlot.nBins;
  const double xmin = monitorPlot.xmin;
  const double xmax = monitorPlot.xmax;
  double ymin = monitorPlot.ymin;
  double ymax = monitorPlot.ymax*plotScale;

  baseRootDir_->cd();
  TLegend* legend = new TLegend(0.73,0.57,0.88,0.88);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);

  //TString dataHistName = Form("hData_%s_%s", subDirName_.c_str(), name.c_str());
  TString dataHistName = Form("hData_%s", name.c_str());
  TH1F* hData = new TH1F(dataHistName, title.c_str(), nBins, xmin, xmax);
  histograms_.Add(hData);

  if ( realDataChain_ ) realDataChain_->Project(dataHistName, varexp.c_str(), cut);
  hData->AddBinContent(nBins, hData->GetBinContent(nBins+1));
  hData->Sumw2();
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(1);
  hData->SetTitle(title.c_str());
  hData->SetStats(0);

  legend->AddEntry(hData, "Data", "p");

  THStack* hStack = new THStack("hStack", title.c_str());
  typedef vector<pair<string, TH1F*> > LabeledPlots;
  LabeledPlots stackedPlots;
  for ( unsigned int i=0; i<mcSamples_.size(); ++i )
  {
    MCSample& mcSample = mcSamples_[i];
    //TString mcHistName = Form("hMC_%s_%s_%s", subDirName_.c_str(), mcSample.name.c_str(), name.c_str());
    TString mcHistName = Form("hMC_%s_%s", mcSample.name.c_str(), name.c_str());
    TH1F* hMC = new TH1F(mcHistName, title.c_str(), nBins, xmin, xmax);

    mcSample.chain->Project(mcHistName, varexp.c_str(), cut);
    hMC->AddBinContent(nBins, hMC->GetBinContent(nBins+1));
    hMC->Scale(lumi_*mcSample.xsec/mcSample.nEvents);
    hMC->SetFillColor(mcSample.color);

    // Add to the HStack if there's no duplicated label
    // If duplicated label exists, call TH1::Add
    // First, find if plot with same label already in the THStack
    LabeledPlots::const_iterator matchedPlot = stackedPlots.end();
    for ( LabeledPlots::const_iterator plotIter = stackedPlots.begin();
          plotIter != stackedPlots.end(); ++plotIter )
    {
      if ( plotIter->first == mcSample.label )
      {
        matchedPlot = plotIter;
        break;
      }
    }
    // If the label was not in the stack, insert it
    if ( matchedPlot == stackedPlots.end() )
    {
      stackedPlots.push_back(make_pair(mcSample.label, hMC));
      hStack->Add(hMC);
      histograms_.Add(hMC);
    }
    // If tehre's plot with same label, sum entries
    else
    {
      TH1F* h = matchedPlot->second;
      if ( h ) h->Add(hMC);
      // In this case, temporary histogram is not needed anymore.
      delete hMC;
    }
  }

  // Build legend, legend should be added in reversed order of THStack
  for ( int i=stackedPlots.size()-1; i>=0; --i )
  {
    const char* label = stackedPlots[i].first.c_str();
    TH1F* h = stackedPlots[i].second;
    legend->AddEntry(h, label, "f");
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
    c->Print((imageOutDir_+"/"+c->GetName()+".pdf").c_str());
  }
}

void TopAnalyzerLite::printStat(const string& name, TCut cut)
{
  cout << "-------------------------\n";
  cout << "   " << name << endl;

  if ( writeSummary_ )
  {
    fout_ << "-------------------------\n";
    fout_ << "   " << name << endl;
  }

  const double nData = realDataChain_ ? realDataChain_->GetEntries(cut) : 0;

  double nTotal = 0, nSignal = 0;
  double nTotalErr2 = 0;

  vector<Stat> stats;
  for ( unsigned int i=0; i<mcSamples_.size(); ++i )
  {
    MCSample& mcSample = mcSamples_[i];

    const double norm = lumi_*mcSample.xsec/mcSample.nEvents;
    const double nEvents = mcSample.chain->GetEntries(cut)*norm;
    const double nEventsErr2 = nEvents*norm;

    // Merge statistics with same labels
    vector<Stat>::iterator matchedStatObj = stats.end();
    for ( vector<Stat>::iterator statObj = stats.begin();
          statObj != stats.end(); ++statObj )
    {
      if ( statObj->label == mcSample.label )
      {
        matchedStatObj = statObj;
        break;
      }
    }
    if ( matchedStatObj == stats.end() )
    {
      Stat stat = {mcSample.name, mcSample.label, nEvents, nEventsErr2};
      stats.push_back(stat);
    }
    else
    {
      matchedStatObj->nEvents += nEvents;
      matchedStatObj->nEventsErr2 += nEventsErr2;
    }
  }

  // Get the field width for printing
  int maxFWidth = 0;
  for ( int i=stats.size()-1; i>=0; --i )
  {
    const int fWidth = stats[i].label.size();
    if ( fWidth > maxFWidth ) maxFWidth = fWidth;
  }
  TString form = TString("%-") + Form("%d", maxFWidth) + "s";

  // Print out statistics
  for ( int i=stats.size()-1; i>=0; --i )
  {
    Stat& stat = stats[i];
    const string label = Form(form.Data(), stat.label.c_str());

    cout << label << " = " << stat.nEvents << " +- " << sqrt(stat.nEventsErr2) << endl;
    if ( writeSummary_ ) fout_ << label << " = " << stat.nEvents << " +- " << sqrt(stat.nEventsErr2) << endl;

    if ( stat.name == "TTbar" )
    {
      nSignal = stat.nEvents;
    }

    nTotal += stat.nEvents;
    nTotalErr2 += stat.nEventsErr2;
  }

  //const double nBkg = nTotal - nSignal;
  const double signif = nSignal/sqrt(nTotal);
  const double nTotalErr = sqrt(nTotalErr2);

  cout << Form(form.Data(), "Total") << " = " << nTotal << " +- " << nTotalErr << endl;
  cout << "-----------------------------------------------" << endl;
  cout << Form(form.Data(), "Data") << " = " << nData << endl;
  cout << Form(form.Data(), "S/sqrt(S+B)") << " = " << signif << endl;
  cout << "-----------------------------------------------" << endl;

  if ( writeSummary_ )
  {
    fout_ << Form(form.Data(), "Total") << " = " << nTotal << " +- " << nTotalErr << endl;
    fout_ << "-----------------------------------------------" << endl;
    fout_ << Form(form.Data(), "Data") << " = " << nData << endl;
    fout_ << Form(form.Data(), "S/sqrt(S+B)") << " = " << signif << endl;
    fout_ << "-----------------------------------------------" << endl;
  }
}

void TopAnalyzerLite::applySingleCut(const TCut cut, const TString monitorPlotNamesStr)
{
  static int singleCutUniqueId = 0;

  TObjArray* monitorPlotNames = monitorPlotNamesStr.Tokenize(",");
  const int nPlots = monitorPlotNames->GetSize();

  cout << "----------------------------\n";
  cout << "Result of single cut" << endl;
  cout << "Cut = " << cut << endl;
  printStat(Form("SingleCut_%d", singleCutUniqueId), cut);
  for ( int i=0; i<nPlots; ++i )
  {
    TObject* obj = monitorPlotNames->At(i);
    if ( !obj ) continue;

    const string plotName = obj->GetName();
    if ( monitorPlots_.find(plotName) == monitorPlots_.end() ) continue;
    MonitorPlot& monitorPlot = monitorPlots_[plotName];
    plot(Form("SingleCut_%d_%s", singleCutUniqueId, plotName.c_str()), cut, monitorPlot);
  }

  monitorPlotNames->Delete();

  ++singleCutUniqueId;
}

TObjArray TopAnalyzerLite::getHistograms()
{
  return histograms_;
}

void TopAnalyzerLite::saveHistograms(TString fileName)
{
  if ( fileName == "" )
  {
    fileName = subDirName_+".root";
  }

  TFile* f = TFile::Open(fileName, "recreate");
  TObjArray histograms = getHistograms();
  histograms.Write();
  f->Write();
  f->Close();
}

