#include "DataFormats/Common/interface/Wrapper.h"

#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarEvent.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"

#include <vector>

namespace {
  struct KoPFA_DataFormats {

    Ko::ZCandidate dummyZCandidate;
    edm::Wrapper<Ko::ZCandidate> dummyZCandidateWrapper;
    std::vector<Ko::ZCandidate> dummyZCandidateCollection;
    edm::Wrapper<std::vector<Ko::ZCandidate> > dummyZCandidateCollectionWrapper;
    edm::Ptr<Ko::ZCandidate> dummyZCandidatePtr;

    Ko::METCandidate dummyMETCandidate;
    edm::Wrapper<Ko::METCandidate> dummyMETCandidateWrapper;
    std::vector<Ko::METCandidate> dummyMETCandidateCollection;
    edm::Wrapper<std::vector<Ko::METCandidate> > dummyMETCandidateCollectionWrapper;
    edm::Ptr<Ko::METCandidate> dummyMETCandidatePtr;

    Ko::TTbarEvent dummyTTbarEvent;
    edm::Wrapper<Ko::TTbarEvent> dummyTTbarEventWrapper;
    std::vector<Ko::TTbarEvent> dummyTTbarEventCollection;
    edm::Wrapper<std::vector<Ko::TTbarEvent> > dummyTTbarEventCollectionWrapper;
    edm::Ptr<Ko::TTbarEvent> dummyTTbarEventPtr;

    Ko::TTbarGenEvent dummyTTbarGenEvent;
    edm::Wrapper<Ko::TTbarGenEvent> dummyTTbarGenEventWrapper;
    std::vector<Ko::TTbarGenEvent> dummyTTbarGenEventCollection;
    edm::Wrapper<std::vector<Ko::TTbarGenEvent> > dummyTTbarGenEventCollectionWrapper;
    edm::Ptr<Ko::TTbarGenEvent> dummyTTbarGenEventPtr;

  };

}
