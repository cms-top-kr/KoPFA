#include "DataFormats/Common/interface/Wrapper.h"

#include "KoPFA/DataFormats/interface/ZCandidate.h"

#include <vector>

namespace {
  struct KoPFA_DataFormats {

    Ko::ZCandidate dummyZCandidate;
    edm::Wrapper<Ko::ZCandidate> dummyZCandidateWrapper;
    std::vector<Ko::ZCandidate> dummyZCandidateCollection;
    edm::Wrapper<std::vector<Ko::ZCandidate> > dummyZCandidateCollectionWrapper;
    edm::Ptr<Ko::ZCandidate> dummyZCandidatePtr;

  };
}
