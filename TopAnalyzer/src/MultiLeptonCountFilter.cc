#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include <memory>

using namespace edm;
using namespace std;

class MultiLeptonCountFilter : public edm::EDFilter
{
public:
  MultiLeptonCountFilter(const edm::ParameterSet& pset);
  ~MultiLeptonCountFilter() {};

private:
  void beginJob() {};
  void endJob() {};
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);

  bool applyFilter_;
  std::vector<edm::InputTag> leptonLabels_;
  unsigned int minCount_, maxCount_;
};

MultiLeptonCountFilter::MultiLeptonCountFilter(const edm::ParameterSet& pset)
{
  applyFilter_ = pset.getUntrackedParameter<bool>("applyFilter", true);

  leptonLabels_ = pset.getUntrackedParameter<std::vector<edm::InputTag> >("leptons");
  minCount_ = pset.getUntrackedParameter<unsigned int>("minCount", 1);
  maxCount_ = pset.getUntrackedParameter<unsigned int>("maxCount", 999);
  
}

bool MultiLeptonCountFilter::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  if ( !applyFilter_ ) return true;

  unsigned int nCount = 0;

  for ( std::vector<edm::InputTag>::const_iterator leptonLabel = leptonLabels_.begin();
        leptonLabel != leptonLabels_.end(); ++leptonLabel )
  {
    edm::Handle<edm::View<reco::Candidate> > leptonHandle;
    event.getByLabel(*leptonLabel, leptonHandle);

    if ( !leptonHandle.isValid() ) continue;

    nCount += leptonHandle->size();
  }
  
  return nCount >= minCount_ && nCount <= maxCount_;
}

DEFINE_FWK_MODULE(MultiLeptonCountFilter);

