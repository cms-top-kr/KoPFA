#include "DataFormats/Common/interface/Wrapper.h"

#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarEvent.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/H2WWMass.h"

#include <vector>

namespace {
  struct KoPFA_DataFormats {

    Ko::ZCandidate dummyZCandidate;
    edm::Wrapper<Ko::ZCandidate> dummyZCandidateWrapper;
    std::vector<Ko::ZCandidate> dummyZCandidateCollection;
    edm::Wrapper<std::vector<Ko::ZCandidate> > dummyZCandidateCollectionWrapper;
    edm::Ptr<Ko::ZCandidate> dummyZCandidatePtr;

    Ko::Lepton dummyLepton;
    edm::Wrapper<Ko::Lepton> dummyLeptonWrapper;
    std::vector<Ko::Lepton> dummyLeptonCollection;
    edm::Wrapper<std::vector<Ko::Lepton> > dummyLeptonCollectionWrapper;
    edm::Ptr<Ko::Lepton> dummyLeptonPtr;

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

    Ko::TTbarMass dummyTTbarMass;
    edm::Wrapper<Ko::TTbarMass> dummyTTbarMassWrapper;
    std::vector<Ko::TTbarMass> dummyTTbarMassCollection;
    edm::Wrapper<std::vector<Ko::TTbarMass> > dummyTTbarMassCollectionWrapper;
    edm::Ptr<Ko::TTbarMass> dummyTTbarMassPtr;

    Ko::H2WWMass dummyH2WWMass;
    edm::Wrapper<Ko::H2WWMass> dummyH2WWMassWrapper;
    std::vector<Ko::H2WWMass> dummyH2WWMassCollection;
    edm::Wrapper<std::vector<Ko::H2WWMass> > dummyH2WWMassCollectionWrapper;
    edm::Ptr<Ko::H2WWMass> dummyH2WWMassPtr;
  };

}
