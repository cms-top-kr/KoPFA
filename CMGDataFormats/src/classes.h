#include "DataFormats/Common/interface/Wrapper.h"
#include "KoPFA/CMGDataFormats/interface/CMGTTbarCandidate.h"

#include <vector>

namespace {
  struct KoPFA_CMGAnalyzer {

    vallot::CMGTTbarCandidate dummyCMGTTbarCandidate;
    edm::Wrapper<vallot::CMGTTbarCandidate> dummyCMGTTbarCandidateWrapper;
    std::vector<vallot::CMGTTbarCandidate> dummyCMGTTbarCandidateCollection;
    edm::Wrapper<std::vector<vallot::CMGTTbarCandidate> > dummyCMGTTbarCandidateCollectionWrapper;
    edm::Ptr<vallot::CMGTTbarCandidate> dummyCMGTTbarCandidatePtr;

  };

}
