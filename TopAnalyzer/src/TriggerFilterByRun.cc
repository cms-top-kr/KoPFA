#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include <vector>

using namespace std;

class TriggerFilterByRun : public edm::EDFilter
{
public:
  TriggerFilterByRun(const edm::ParameterSet& pset);
  ~TriggerFilterByRun() {};

  bool beginRun(edm::Run& run, const edm::EventSetup& eventSetup);
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);

  typedef vector<edm::ParameterSet> VPSet;

private:
  struct TriggerSet
  {
    TriggerSet() {};
    TriggerSet(const int runBegin, const int runEnd, const vector<string> triggerNames)
    {
      runBegin_ = runBegin;
      runEnd_ = runEnd;
      triggerNames_ = triggerNames;
    };

    int runBegin_, runEnd_;
    vector<string> triggerNames_;
  };

  bool doFilter_, filterOutUndefined_;
  edm::InputTag triggerResultsLabel_;
  vector<TriggerSet> triggerSets_;
  vector<string> currentTriggerNames_;
};

TriggerFilterByRun::TriggerFilterByRun(const edm::ParameterSet& pset)
{
  triggerResultsLabel_ = pset.getUntrackedParameter<edm::InputTag>("triggerResults", edm::InputTag("TriggerResults", "", "HLT"));
  doFilter_ = pset.getUntrackedParameter<bool>("filter", true);
  filterOutUndefined_ = pset.getUntrackedParameter<bool>("filterOutUndefined", true);
  VPSet triggerPSets = pset.getUntrackedParameter<VPSet>("triggerPSets");

  for ( VPSet::const_iterator triggerPSet = triggerPSets.begin();
        triggerPSet != triggerPSets.end(); ++triggerPSet )
  {
    const int runBegin = triggerPSet->getUntrackedParameter<int>("runBegin");
    const int runEnd = triggerPSet->getUntrackedParameter<int>("runEnd");

    const vector<string> triggerNames = triggerPSet->getUntrackedParameter<vector<string> >("triggerNames");

    triggerSets_.push_back(TriggerSet(runBegin, runEnd, triggerNames));
  }
}

bool TriggerFilterByRun::beginRun(edm::Run& run, const edm::EventSetup& eventSetup)
{
  const int runNumber = run.run();
  // Find trigger sets corresponding to this run
  currentTriggerNames_.clear();
  for ( vector<TriggerSet>::const_iterator triggerSet = triggerSets_.begin();
        triggerSet != triggerSets_.end(); ++triggerSet )
  {
    const int runBegin = triggerSet->runBegin_;
    const int runEnd = triggerSet->runEnd_;

    // If the run number is sit in the run range of this trigger name,
    // put into the list of trigger names to be considered.
    if ( runNumber < runBegin or runNumber > runEnd ) continue;

    const vector<string>& input = triggerSet->triggerNames_;
    currentTriggerNames_.insert(currentTriggerNames_.end(), input.begin(), input.end());
  }

  return true;
}

bool TriggerFilterByRun::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  if ( !doFilter_ ) return true;

  // If we don't know which triggers to be required, no need to check trigger bits.
  if ( currentTriggerNames_.empty() )
  {
    // More simpler form is possible, but keep this for readability
    if ( filterOutUndefined_ ) return false;
    else return true;
  }

  edm::Handle<edm::TriggerResults> triggerResultsHandle;
  if ( !event.getByLabel(triggerResultsLabel_, triggerResultsHandle) )
  {
    edm::LogError("TriggerFilterByRun") << "Cannot find TriggerResults\n";
    return false;
  }
  const edm::TriggerResults* triggerResults = triggerResultsHandle.product();

  if ( !triggerResults->wasrun() or !triggerResults->accept() ) return false;

  const edm::TriggerNames& triggerNames = event.triggerNames(*triggerResults);

  for ( vector<string>::const_iterator triggerNameToFilter = currentTriggerNames_.begin();
      triggerNameToFilter != currentTriggerNames_.end(); ++triggerNameToFilter )
  {
    const unsigned int triggerIndex = triggerNames.triggerIndex(*triggerNameToFilter);
    if ( triggerIndex == triggerNames.size() ) continue;
    if ( triggerResults->accept(triggerIndex) ) return true;
  }

  return false;
}

DEFINE_FWK_MODULE(TriggerFilterByRun);

