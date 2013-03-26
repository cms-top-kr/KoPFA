#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
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
  HLTConfigProvider hltConfig_;

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
  
  bool doMatch_;
  double matchRunBegin_, matchRunEnd_;
  double matchMinPt_;
  std::string matchTriggerPath_;
  edm::InputTag matchTriggerObjectLabel_;

  edm::InputTag triggerResultsLabel_;
  edm::InputTag triggerEventLabel_;
  vector<TriggerSet> triggerSets_;
  vector<string> currentTriggerNames_;
};

TriggerFilterByRun::TriggerFilterByRun(const edm::ParameterSet& pset)
{
  triggerResultsLabel_ = pset.getUntrackedParameter<edm::InputTag>("triggerResults", edm::InputTag("TriggerResults", "", "REDIGI"));
  triggerEventLabel_ = pset.getUntrackedParameter<edm::InputTag>("triggerEvent", edm::InputTag("hltTriggerSummaryAOD", "", "REDIGI"));
  
  doFilter_ = pset.getUntrackedParameter<bool>("filter", true);
  filterOutUndefined_ = pset.getUntrackedParameter<bool>("filterOutUndefined", true);
  VPSet triggerPSets = pset.getUntrackedParameter<VPSet>("triggerPSets");

  // Special treatment for early runs, to do trigger object matching
  doMatch_ = pset.getUntrackedParameter<bool>("doMatch", false);
  if ( doMatch_ )
  {
    matchRunBegin_ = pset.getUntrackedParameter<int>("matchRunBegin");
    matchRunEnd_ = pset.getUntrackedParameter<int>("matchRunEnd");
    matchMinPt_ = pset.getUntrackedParameter<double>("matchMinPt");
    matchTriggerPath_ = pset.getUntrackedParameter<std::string>("matchTriggerPath");
    matchTriggerObjectLabel_ = pset.getUntrackedParameter<edm::InputTag>("matchTriggerObject");
  }

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
  using namespace std;
  using namespace edm;

  const string& processName = triggerResultsLabel_.process();
  bool isChanged = true;
  hltConfig_.init(run, eventSetup, processName, isChanged);

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
    for ( vector<string>::const_iterator triggerName = input.begin();
          triggerName != input.end(); ++triggerName )
    {
      const vector<string> matchedPaths = hltConfig_.matched(hltConfig_.triggerNames(), *triggerName);
      if ( matchedPaths.empty() ) continue;

      currentTriggerNames_.insert(currentTriggerNames_.end(), matchedPaths.begin(), matchedPaths.end());
    }
    //currentTriggerNames_.insert(currentTriggerNames_.end(), input.begin(), input.end());
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

  edm::Handle<trigger::TriggerEvent> triggerEventHandle;
  if ( doMatch_ )
  {
    if ( !event.getByLabel(triggerEventLabel_,triggerEventHandle) ) {
      edm::LogError("TriggerFilterByRun") << "Cannot find TriggerEvent\n";
      return false;
    }
  }

  const int runNumber = event.id().run();
  const edm::TriggerNames& triggerNames = event.triggerNames(*triggerResults);

  bool accept = false;

  for ( vector<string>::const_iterator triggerNameToFilter = currentTriggerNames_.begin();
      triggerNameToFilter != currentTriggerNames_.end(); ++triggerNameToFilter )
  {
    const unsigned int triggerIndex = triggerNames.triggerIndex(*triggerNameToFilter);
    if ( triggerIndex == triggerNames.size() ) continue;
    if ( triggerResults->accept(triggerIndex) ) accept = true;

    // If matching is turn on and the run number is in the run range, try trigger object matching
    if ( doMatch_ and matchRunBegin_ >= runNumber and matchRunEnd_ <= runNumber and
         matchTriggerPath_ == *triggerNameToFilter )
    {
      const unsigned int filterIndex = triggerEventHandle->filterIndex(matchTriggerObjectLabel_);

      // Check filterIndex for safety : invalid values in case of wrong input like typo
      // Skip if the label is not found
      if ( filterIndex >= triggerEventHandle->sizeFilters() )
      {
        edm::LogError("TriggerFilterByRun") << "Filter name is not in the trigger object\n";
        continue;
      }

      int nMatch = 0;
      const trigger::Keys& keys = triggerEventHandle->filterKeys(filterIndex);
      const size_t nKey = keys.size();
      for ( size_t i=0; i<nKey; ++i )
      {
        const trigger::TriggerObject& triggerObject = triggerEventHandle->getObjects().at(keys[i]);
        if ( triggerObject.pt() >= matchMinPt_ ) ++nMatch;
      }

      if ( nMatch == 0 ) accept = false;
    }

    if ( accept ) return true;
  }

  return accept;
}

DEFINE_FWK_MODULE(TriggerFilterByRun);

