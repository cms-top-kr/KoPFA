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
                const Color_t color);
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
  void setScanVariables(const string scanVariables);

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
  MCSample mcSig_;
  vector<MCSample> mcBkgs_;
  TChain* realDataChain_;

  map<const string, MonitorPlot> monitorPlots_;
  vector<CutStep> cuts_;

  string imageOutDir_;

  void plot(const string name, TCut cut, MonitorPlot& monitorPlot, const double plotScale = 1.0);
  void printStat(const string& name, TCut cut);

  TObjArray histograms_;
  ofstream fout_;
  bool writeSummary_;
  string scanVariables_;

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

  mcSig_.nEvents = 0;
  mcSig_.chain = 0;
}

TopAnalyzerLite::~TopAnalyzerLite()
{
  if ( writeSummary_ ) fout_.close();
}

void TopAnalyzerLite::addMCSig(const string mcSampleName, const string mcSampleLabel,
                               const string fileName, const double xsec, const double nEvents,
                               const Color_t color)
{
  mcSig_.name = mcSampleName;
  mcSig_.label = mcSampleLabel;
  mcSig_.nEvents += nEvents;
  mcSig_.xsec = xsec;
  mcSig_.color = color;

  if ( !mcSig_.chain )
  {
    mcSig_.chain = new TChain((subDirName_+"/tree").c_str(), (subDirName_+"/tree").c_str());
  }
  mcSig_.chain->Add(fileName.c_str());
}

void TopAnalyzerLite::addMCBkg(const string mcSampleName, const string mcSampleLabel,
                               const string fileName, const double xsec, const double nEvents,
                               const Color_t color)
{
  int mcSampleIndex = -1;
  for ( unsigned int i = 0; i < mcBkgs_.size(); ++i )
  {
    if ( mcBkgs_[i].name == mcSampleName )
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
    mcBkgs_.push_back(mcSample);
    mcSampleIndex = mcBkgs_.size()-1;
  }

  MCSample& mcSample = mcBkgs_[mcSampleIndex];

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
  cout << " * " << mcSig_.name << "\t" << mcSig_.xsec << " /pb (" << mcSig_.nEvents << ")\n";
  if ( writeSummary_ ) fout_ << " * " << mcSig_.name << "\t" << mcSig_.xsec << " /pb (" << mcSig_.nEvents << ")\n";
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

  THStack* hStack = new THStack("hStack", title.c_str());
  typedef vector<pair<string, TH1F*> > LabeledPlots;
  LabeledPlots stackedPlots;
  TString mcSigHistName = Form("hMCSig_%s_%s", mcSig_.name.c_str(), name.c_str());
  TH1F* hMCSig = new TH1F(mcSigHistName, title.c_str(), nBins, xBins);

  mcSig_.chain->Project(mcSigHistName, varexp.c_str(), cut);
  hMCSig->AddBinContent(nBins, hMCSig->GetBinContent(nBins+1));
  hMCSig->Scale(lumi_*mcSig_.xsec/mcSig_.nEvents);
  hMCSig->SetFillColor(mcSig_.color);

  stackedPlots.push_back(make_pair(mcSig_.label, hMCSig));
  hStack->Add(hMCSig);
  histograms_.Add(hMCSig);

  for ( unsigned int i=0; i<mcBkgs_.size(); ++i )
  {
    MCSample& mcSample = mcBkgs_[i];
    //TString mcHistName = Form("hMC_%s_%s_%s", subDirName_.c_str(), mcSample.name.c_str(), name.c_str());
    TString mcHistName = Form("hMC_%s_%s", mcSample.name.c_str(), name.c_str());
    TH1F* hMC = new TH1F(mcHistName, title.c_str(), nBins, xBins);

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
  const double normSig = lumi_*mcSig_.xsec/mcSig_.nEvents;
  const double nEventsSig = mcSig_.chain->GetEntries(cut)*normSig;
  const double nEventsErr2Sig = nEventsSig*normSig;
  Stat statSig = {mcSig_.name, mcSig_.label, nEventsSig, nEventsErr2Sig};
  stats.push_back(statSig);

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

    if ( stat.name == mcSig_.name )
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

  TParameter<double> lumi("lumi", lumi_);
  lumi.Write();

  TH1F* hScale = new TH1F("hScale", "Scale factors for each samples", mcBkgs_.size()+1, 0, mcBkgs_.size()+1);
  hScale->Fill(mcSig_.name.c_str(), lumi_*mcSig_.xsec/mcSig_.nEvents);
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
