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
    TriggerSet(const int runBegin, const int runEnd, const string triggerName)
    {
      runBegin_ = runBegin;
      runEnd_ = runEnd;
      triggerName_ = triggerName;
    };

    int runBegin_, runEnd_;
    string triggerName_;
  };

  edm::InputTag triggerResultsLabel_;
  vector<TriggerSet> triggerSets_;
  vector<string> currentTriggerNames_;
  bool isTriggerSetUpdated_;
};

TriggerFilterByRun::TriggerFilterByRun(const edm::ParameterSet& pset)
{
  triggerResultsLabel_ = pset.getUntrackedParameter<edm::InputTag>("triggerResults", edm::InputTag("TriggerResults", "", "HLT"));
  VPSet triggerPSets = pset.getUntrackedParameter<VPSet>("triggerSets");

  for ( VPSet::const_iterator triggerPSet = triggerPSets.begin();
        triggerPSet != triggerPSets.end(); ++triggerPSet )
  {
    const int runBegin = triggerPSet->getUntrackedParameter<int>("runBegin");
    const int runEnd = triggerPSet->getUntrackedParameter<int>("runEnd");

    const string triggerName = triggerPSet->getUntrackedParameter<string>("triggerName");

    triggerSets_.push_back(TriggerSet(runBegin, runEnd, triggerName));
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
    if ( runNumber < runBegin ) continue;
    if ( runBegin <= runEnd and runNumber >= runEnd ) continue;

    currentTriggerNames_.push_back(triggerSet->triggerName_);
  }

  return true;
}

bool TriggerFilterByRun::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  // We accept event if we don't know which triggers to be required
  if ( currentTriggerNames_.empty() ) return true;

  edm::Handle<edm::TriggerResults> triggerResultsHandle;
  if ( !event.getByLabel(triggerResultsLabel_, triggerResultsHandle) )
  {
    edm::LogError("TriggerFilterByRun") << "Cannot find TriggerResults\n";
    return false;
  }
  const edm::TriggerResults* triggerResults = triggerResultsHandle.product();

  if ( !triggerResults->wasrun() or !triggerResults->accept() ) return false;

  const int nTriggerResult = triggerResults->size();
  const edm::TriggerNames& triggerNames = event.triggerNames(*triggerResults);

  for ( int triggerIndex = 0; triggerIndex < nTriggerResult; ++triggerIndex )
  {
    if ( !triggerResults->accept(triggerIndex) ) continue;
    const string triggerName = triggerNames.triggerName(triggerIndex);

    for ( vector<string>::const_iterator triggerNameToFilter = currentTriggerNames_.begin();
          triggerNameToFilter != currentTriggerNames_.end(); ++triggerNameToFilter )
    {
      if ( triggerName == *triggerNameToFilter ) return true;
    }
  }

  return false;
}

DEFINE_FWK_MODULE(TriggerFilterByRun);

