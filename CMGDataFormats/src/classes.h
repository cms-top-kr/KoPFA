#include "DataFormats/Common/interface/Wrapper.h"
#include "KoPFA/CMGDataFormats/interface/CMGTTbarCandidate.h"

#include <vector>

namespace {
  struct KoPFA_CMGAnalyzer {

    Ko::CMGTTbarCandidate dummyCMGTTbarCandidate;
    edm::Wrapper<Ko::CMGTTbarCandidate> dummyCMGTTbarCandidateWrapper;
    std::vector<Ko::CMGTTbarCandidate> dummyCMGTTbarCandidateCollection;
    edm::Wrapper<std::vector<Ko::CMGTTbarCandidate> > dummyCMGTTbarCandidateCollectionWrapper;
    edm::Ptr<Ko::CMGTTbarCandidate> dummyCMGTTbarCandidatePtr;

  };

}
