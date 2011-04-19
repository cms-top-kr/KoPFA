#include "TROOT.h"
#include "TSystem.h"

#include "TCut.h"
#include "TObjString.h"
#include "TParameter.h"
#include "TFile.h"
#include "TChain.h"
#include "TTreePlayer.h"

#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TH1F.h"
#include "THStack.h"
#include "TGraph.h"

#include "TMath.h"

#include "TPRegexp.h"

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

class TopAnalyzerLite
{
public:
  TopAnalyzerLite(const string subDirName = "", const string imageOutDir = "");
  ~TopAnalyzerLite();

  void addMCSig(const string mcSampleName, const string mcSampleLabel,
                const string fileName, const double xsec, const double nEvents,
                const Color_t color, const bool doStackSignal = true);
  void addMCBkg(const string mcSampleName, const string mcSampleLabel,
                const string fileName, const double xsec, const double nEvents,
                const Color_t color);
  void addRealData(const string fileName, const double lumi);

  void addCutStep(const TCut cut, const TString monitorPlotNamesStr, const double plotScale = 1.0);
  void addMonitorPlot(const string name, const string varexp, const string title,
                      const int nBins, const double xmin, const double xmax,
                      const double ymin = 0, const double ymax = 0, const bool doLogy = true);
  void addMonitorPlot(const string name, const string varexp, const string title,
                      const string xBinsStr,
                      const double ymin = 0, const double ymax = 0, const bool doLogy = true);
  void setEventWeightVar(const string eventWeightVar = "weight");
  void setScanVariables(const string scanVariables);

  void applyCutSteps();
  void applySingleCut(const TCut cut, const TString monitirPlotNamesStr);

  void drawEffCurve(const TCut cut, const string varexp, const string scanPoints);
  void drawEffCurve(const TCut cut, const string varexp, std::vector<double>& scanPoints);

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
    std::vector<double> xBins;
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
  bool doStackSignal_;
  vector<MCSample> mcSigs_;
  vector<MCSample> mcBkgs_;
  TChain* realDataChain_;

  map<const string, MonitorPlot> monitorPlots_;
  vector<CutStep> cuts_;

  string imageOutDir_;

  void plot(const string name, TCut cut, MonitorPlot& monitorPlot, const double plotScale = 1.0);
  void printStat(const string& name, TCut cut);
  void addMC(vector<MCSample>& mcSetup,
             const string name, const string label,
             const string fileName, const double xsec, const double nEvents,
             const Color_t color);

  TObjArray histograms_;
  ofstream fout_;
  bool writeSummary_;
  string scanVariables_;
  string eventWeightVar_;

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

  scanVariables_ = "RUN:LUMI:EVENT:Z.mass():@jetspt30.size():MET";
  eventWeightVar_ = "";

  doStackSignal_ = true;
}

TopAnalyzerLite::~TopAnalyzerLite()
{
  if ( writeSummary_ ) fout_.close();
}

void TopAnalyzerLite::addMC(vector<MCSample>& mcSetup,
                            const string name, const string label,
                            const string fileName, const double xsec, const double nEvents,
                            const Color_t color)
{
  int index = -1;
  for ( unsigned int i=0; i<mcSetup.size(); ++i )
  {
    if ( mcSetup[i].name == name )
    {
      index = i;
      break;
    }
  }

  if ( index == -1 )
  {
    MCSample mc = {name, 0, xsec, 0, label, color};
    baseRootDir_->cd();
    mc.chain = new TChain((subDirName_+"/tree").c_str(), (subDirName_+"/tree").c_str());
    mcSetup.push_back(mc);
    index = mcSetup.size()-1;
  }

  MCSample& mc = mcSetup[index];
  mc.nEvents += nEvents;
  mc.chain->Add(fileName.c_str());
}

void TopAnalyzerLite::addMCSig(const string name, const string label,
                               const string fileName, const double xsec, const double nEvents,
                               const Color_t color, const bool doStackSignal)
{
  doStackSignal_ = doStackSignal;
  addMC(mcSigs_, name, label, fileName, xsec, nEvents, color);
}

void TopAnalyzerLite::addMCBkg(const string name, const string label,
                               const string fileName, const double xsec, const double nEvents,
                               const Color_t color)
{
  addMC(mcBkgs_, name, label, fileName, xsec, nEvents, color);
}

void TopAnalyzerLite::addRealData(const string fileName, const double lumi)
{
  lumi_ += lumi;
  if ( fileName == "" ) return;

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
  std::vector<double> xBins;
  const double dX = (xmax-xmin)/nBins;
  for ( int i=0; i<=nBins; ++i )
  {
    xBins.push_back(xmin+dX*i);
  }

  MonitorPlot monitorPlot = {varexp, title, xBins, doLogy, ymin, ymax};
  monitorPlots_[name] = monitorPlot;
}

void TopAnalyzerLite::addMonitorPlot(const string name, const string varexp, const string title,
                                     const string xBinsStr,
                                     const double ymin, const double ymax, const bool doLogy)
{
  stringstream ss(xBinsStr);
  std::vector<double> xBins;
  double x;
  while(ss >> x ) xBins.push_back(x);

  MonitorPlot monitorPlot = {varexp, title, xBins, doLogy, ymin, ymax};
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
  for ( unsigned int i=0; i<mcSigs_.size(); ++i )
  {
    MCSample& mcSample = mcSigs_[i];
    cout << " * " << mcSample.name << "\t" << mcSample.xsec << " /pb (" << mcSample.nEvents << ")\n";
    if ( writeSummary_ ) fout_ << " * " << mcSample.name << "\t" << mcSample.xsec << " /pb (" << mcSample.nEvents << ")\n";
  }
  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    MCSample& mcSample = mcBkgs_[i];
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
    realDataChain_->Scan(scanVariables_.c_str(), finalCut);
    cout << "Number of entries after final selection = " << realDataChain_->GetEntries(finalCut) << endl;
  }

  if ( writeSummary_ && realDataChain_ )
  {
    const string tmpFileName = imageOutDir_+"/tmp.txt";

    ((TTreePlayer*)(realDataChain_->GetPlayer()))->SetScanRedirect(true);
    ((TTreePlayer*)(realDataChain_->GetPlayer()))->SetScanFileName(tmpFileName.c_str());
    realDataChain_->Scan(scanVariables_.c_str(), finalCut);
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
  const int nBins = monitorPlot.xBins.size()-1;
  const double* xBins = &(monitorPlot.xBins[0]);
  double ymin = monitorPlot.ymin;
  double ymax = monitorPlot.ymax*plotScale;

  baseRootDir_->cd();
  TLegend* legend = new TLegend(0.73,0.57,0.88,0.88);
  legend->SetTextSize(0.04);
  legend->SetFillColor(0);
  legend->SetLineColor(0);

  //TString dataHistName = Form("hData_%s_%s", subDirName_.c_str(), name.c_str());
  TString dataHistName = Form("hData_%s", name.c_str());
  TH1F* hData = new TH1F(dataHistName, title.c_str(), nBins, xBins);
  histograms_.Add(hData);

  if ( realDataChain_ ) realDataChain_->Project(dataHistName, varexp.c_str(), cut);
  hData->AddBinContent(nBins, hData->GetBinContent(nBins+1));
  hData->Sumw2();
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(1);
  hData->SetTitle(title.c_str());
  hData->SetStats(0);

  legend->AddEntry(hData, "Data", "p");

  TString dataSubHistName = Form("hDataSub_%s", name.c_str());
  TH1F* hDataSub = (TH1F*)hData->Clone(dataSubHistName);
  hDataSub->SetTitle(hData->GetTitle()+TString(" background subtracted"));
  histograms_.Add(hDataSub);

  THStack* hStack = new THStack("hStack", title.c_str());
  typedef vector<pair<string, TH1F*> > LabeledPlots;
  LabeledPlots stackedPlots;
  LabeledPlots sigPlots; // Keep list of signal plots if doStackSignal == false

  TCut mcCutStr = "";
  if ( eventWeightVar_.empty() ) mcCutStr = cut;
  else mcCutStr = Form("%s*(%s)", eventWeightVar_.c_str(), (const char*)(cut));

  for ( unsigned int i=0; i<mcSigs_.size(); ++i )
  {
    MCSample& mcSample = mcSigs_[i];
    TString mcSigHistName = Form("hMCSig_%s_%s", mcSample.name.c_str(), name.c_str());
    TH1F* hMCSig = new TH1F(mcSigHistName, title.c_str(), nBins, xBins);

    mcSample.chain->Project(mcSigHistName, varexp.c_str(), mcCutStr);
    hMCSig->AddBinContent(nBins, hMCSig->GetBinContent(nBins+1));
    hMCSig->Scale(lumi_*mcSample.xsec/mcSample.nEvents);

    if ( doStackSignal_ )
    {
      hMCSig->SetFillColor(mcSample.color);

      stackedPlots.push_back(make_pair(mcSample.label, hMCSig));
      hStack->Add(hMCSig);

      histograms_.Add(hMCSig);
    }
    else
    {
      LabeledPlots::const_iterator matchedPlot = sigPlots.end();
      for ( LabeledPlots::const_iterator plotIter = sigPlots.begin();
            plotIter != sigPlots.end(); ++plotIter )
      {
        if ( plotIter->first == mcSample.label )
        {
          matchedPlot = plotIter;
          break;
        }
      }

      if ( matchedPlot == sigPlots.end() )
      {
        sigPlots.push_back(make_pair(mcSample.label, hMCSig));

        hMCSig->SetLineWidth(2);
        hMCSig->SetLineColor(mcSample.color);

        histograms_.Add(hMCSig);
      }
      else
      {
        TH1F* h = matchedPlot->second;
        if ( h ) h->Add(hMCSig);
        delete hMCSig;
      }

    }
  }

  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    MCSample& mcSample = mcBkgs_[i];
    //TString mcHistName = Form("hMC_%s_%s_%s", subDirName_.c_str(), mcSample.name.c_str(), name.c_str());
    TString mcHistName = Form("hMC_%s_%s", mcSample.name.c_str(), name.c_str());
    TH1F* hMC = new TH1F(mcHistName, title.c_str(), nBins, xBins);

    mcSample.chain->Project(mcHistName, varexp.c_str(), mcCutStr);
    hMC->AddBinContent(nBins, hMC->GetBinContent(nBins+1));
    hMC->Scale(lumi_*mcSample.xsec/mcSample.nEvents);
    hMC->SetFillColor(mcSample.color);

    // Subtract background from the hDataSub histogram
    hDataSub->Add(hMC, -1);

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
    // If there's plot with same label, sum entries
    else
    {
      TH1F* h = matchedPlot->second;
      if ( h ) h->Add(hMC);
      // In this case, temporary histogram is not needed anymore.
      delete hMC;
    }
  }

  // Do automatic bin labels
  if ( xBins[0] == 0 and xBins[nBins] == nBins and nBins < 20 )
  {
    const int xmin = xBins[0];

    TList* hList = hStack->GetHists();
    for ( int bin=1; bin<nBins; ++bin )
    {
      hData->GetXaxis()->SetBinLabel(bin, Form("%d", int(xmin+bin-1)));
    }
    hData->GetXaxis()->SetBinLabel(nBins, Form("#geq%d", int(xmin+nBins-1)));

    for ( int i=0; i<hList->GetSize(); ++i )
    {
      TH1* h = (TH1*)hList->At(i);

      for ( int bin=1; bin<nBins; ++bin )
      {
        h->GetXaxis()->SetBinLabel(bin, Form("%d", int(xmin+bin-1)));
      }
      h->GetXaxis()->SetBinLabel(nBins, Form("#geq%d", int(xmin+nBins-1)));
    }

  }

  // Build legend, legend should be added in reversed order of THStack
  for ( int i=stackedPlots.size()-1; i>=0; --i )
  {
    const char* label = stackedPlots[i].first.c_str();
    TH1F* h = stackedPlots[i].second;
    legend->AddEntry(h, label, "f");
  }

  if ( !doStackSignal_ )
  {
    for ( unsigned int i=0; i<sigPlots.size(); ++i )
    {
      const char* label = sigPlots[i].first.c_str();
      TH1F* h = sigPlots[i].second;
      legend->AddEntry(h, label, "f");
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
  if ( !doStackSignal_ )
  {
    for ( unsigned int i=0; i<sigPlots.size(); ++i )
    {
      sigPlots[i].second->Draw("same");
    }
  }
  legend->Draw();

  if ( imageOutDir_ != "" )
  {
    c->Print((imageOutDir_+"/"+c->GetName()+".png").c_str());
    c->Print((imageOutDir_+"/"+c->GetName()+".eps").c_str());
    //c->Print((imageOutDir_+"/"+c->GetName()+".pdf").c_str());
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
  for ( unsigned int i=0; i<mcSigs_.size(); ++i )
  {
    MCSample& mcSample = mcSigs_[i];

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
  }

  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    MCSample& mcSample = mcBkgs_[i];

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

    bool isSignal = false;
    for ( unsigned int j=0; j<mcSigs_.size(); ++j )
    {
      if ( stat.name == mcSigs_[j].name )
      {
        isSignal = true;
        break;
      }
    }
    if ( isSignal ) nSignal = stat.nEvents;

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

  TParameter<double> lumi("lumi", lumi_);
  lumi.Write();

  TH1F* hScale = new TH1F("hScale", "Scale factors for each samples", mcBkgs_.size()+1, 0, mcBkgs_.size()+1);
  for ( unsigned int i=0; i<mcSigs_.size(); ++i )
  {
    hScale->Fill(mcSigs_[i].name.c_str(), lumi_*mcSigs_[i].xsec/mcSigs_[i].nEvents);
  }
  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    hScale->Fill(mcBkgs_[i].name.c_str(), lumi_*mcBkgs_[i].xsec/mcBkgs_[i].nEvents);
  }

  TCut cut;
  for ( unsigned int i=0; i<cuts_.size(); ++i )
  {
    TDirectory* dir = f->mkdir(Form("Step_%d", i+1));
    dir->cd();

    cut += cuts_[i].cut;
    TNamed cutStr("cut", cut);
    cutStr.Write();
  }

  TPRegexp stepPattern("Step_[0-9]+");
  TObjArray histograms = getHistograms();
  for ( int i=0; i<histograms.GetSize(); ++i )
  {
    TH1F* h = (TH1F*)histograms.At(i);
    if ( !h ) continue;
    TString hName = h->GetName();
    TString dirName = hName(stepPattern);

    if ( dirName == "" )
    {
      f->cd();
    }
    else
    {
      TDirectory* dir = f->GetDirectory(dirName);
      if ( !dir ) dir = f->mkdir(dirName);
      dir->cd();
    }

    h->Write();
  }
  f->Write();
  f->Close();
}

void TopAnalyzerLite::setScanVariables(const string scanVariables)
{
  scanVariables_ = scanVariables;
}

void TopAnalyzerLite::setEventWeightVar(const string eventWeightVar)
{
  eventWeightVar_ = eventWeightVar;
}

void TopAnalyzerLite::drawEffCurve(const TCut cut, const string varexp, const string scanPoints)
{
  stringstream ss(scanPoints);

  double x;
  std::vector<double> xarr;
  while ( ss >> x ) xarr.push_back(x);

  drawEffCurve(cut, varexp, xarr);
}

void TopAnalyzerLite::drawEffCurve(const TCut cut, const string varexp, std::vector<double>& scanPoints)
{
  // Check scan points are monotonically ordered
  const int nPoint = scanPoints.size();
  const bool isIncreasing = scanPoints[0] < scanPoints[nPoint-1];
  for ( int i=1; i<nPoint; ++i )
  {
    // if ( x[0] > x[N] and x[i] < x[i+1] ) or ( x[0] < x[N] and x[i] > x[i+1] )
    // this sequence is not well-ordered : do not consider the input
    if ( isIncreasing xor (scanPoints[i-1] < scanPoints[i]) )
    {
      cout << "Error : Scan point should be monotonically increasing/decreasing\n";
      return;
    }
  }

  TGraph* grpSigEff = new TGraph();
  TGraph* grpBkgEff = new TGraph();
  TGraph* grpSignif = new TGraph();
  TGraph* grpResponse = new TGraph();

  // Get the total # of signal entries and background entries
  double nTotalSig = 0, nTotalBkg = 0;
  for ( unsigned int i=0; i<mcSigs_.size(); ++i )
  {
    nTotalSig += mcSigs_[i].nEvents*mcSigs_[i].xsec*lumi_;
  }

  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    nTotalBkg += mcBkgs_[i].nEvents*mcBkgs_[i].xsec*lumi_;
  }

  for ( int i=0; i<nPoint; ++i )
  {
    TCut iCut = cut;
    if ( isIncreasing ) iCut += Form("%s > %f", varexp.c_str(), scanPoints[i]);
    else iCut += Form("%s < %f", varexp.c_str(), scanPoints[i]);

    double nSig = 0, nBkg = 0;
    for ( unsigned int j=0; j<mcSigs_.size(); ++j )
    {
      nSig += mcSigs_[j].chain->GetEntries(iCut)*mcSigs_[j].xsec*lumi_;
    }

    for ( unsigned int j=0; j<mcBkgs_.size(); ++j )
    {
      nBkg += mcBkgs_[j].chain->GetEntries(iCut)*mcBkgs_[j].xsec*lumi_;
    }

    const double sigEff = nSig/nTotalSig;
    const double bkgEff = nBkg/nTotalBkg;

    grpSigEff->SetPoint(i, scanPoints[i], 100*sigEff);
    grpBkgEff->SetPoint(i, scanPoints[i], 100*bkgEff);
    grpSignif->SetPoint(i, scanPoints[i], nSig/sqrt(nSig+nBkg));
    grpResponse->SetPoint(i, 100*bkgEff, 100*sigEff);
  }

  TCanvas* cEff = new TCanvas;
  cEff->cd();
  grpSigEff->SetTitle(("Efficiency curve for "+varexp+";"+varexp+";Efficiency #epsilon [\%]").c_str());
  grpBkgEff->SetTitle(("Efficiency curve for "+varexp+";"+varexp+";Efficiency #epsilon [\%]").c_str());
  grpSigEff->SetLineColor(kBlue);
  grpBkgEff->SetLineColor(kRed);
  grpSigEff->SetMinimum(0);
  grpSigEff->Draw("AL*");
  grpBkgEff->Draw("sameL*");

  TCanvas* cSignif = new TCanvas;
  cSignif->cd();
  grpSignif->SetTitle(("S/#sqrt{S+B} curve for "+varexp+";"+varexp+";S/#sqrt{S+B}").c_str());
  grpSignif->SetMinimum(0);
  grpSignif->Draw("AL*");

  TCanvas* cEffVsEff = new TCanvas;
  cEffVsEff->cd();
  grpResponse->SetTitle(("Response curve for "+varexp+";Background #epsilon [\%];Signal #epsilon [\%]").c_str());
  grpResponse->Draw("AL*");
}

