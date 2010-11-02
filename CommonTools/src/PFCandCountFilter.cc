#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <memory>
#include <vector>

class PFCandCountFilter : public edm::EDFilter
{
public:
  PFCandCountFilter(const edm::ParameterSet& pset);
  ~PFCandCountFilter() {};

  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  int pdgId_, minCount_;
  double minPt_, maxEta_;
};

PFCandCountFilter::PFCandCountFilter(const edm::ParameterSet& pset)
{
  pdgId_ = pset.getUntrackedParameter<int>("pdgId");
  minPt_ = pset.getUntrackedParameter<double>("minPt");
  maxEta_ = pset.getUntrackedParameter<double>("maxEta");

  minCount_ = pset.getUntrackedParameter<int>("minCount");
}

bool PFCandCountFilter::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::PFCandidateCollection> pfCandHandle;
  event.getByLabel("particleFlow", pfCandHandle);

  int nCand = 0;
  for ( reco::PFCandidateCollection::const_iterator pfCand = pfCandHandle->begin();
        pfCand != pfCandHandle->end(); ++pfCand )
  {
    if ( pdgId_ != std::abs(pfCand->pdgId()) ) continue;
    if ( minPt_ > pfCand->pt() ) continue;
    if ( maxEta_ < std::fabs(pfCand->eta()) ) continue;

    ++nCand;

    if ( nCand >= minCount_ ) return true;
  }

  return false;
}

DEFINE_FWK_MODULE(PFCandCountFilter);

