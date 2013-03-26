#include "DataFormats/Common/interface/Wrapper.h"

#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/TTbarDILEvent.h"
#include "KoPFA/DataFormats/interface/TTbarCandidate.h"
#include "KoPFA/DataFormats/interface/H2WWMass.h"
#include "KoPFA/DataFormats/interface/Jet.h"

#include <vector>

namespace {
  struct KoPFA_DataFormats {

    vallot::ZCandidate dummyZCandidate;
    edm::Wrapper<vallot::ZCandidate> dummyZCandidateWrapper;
    std::vector<vallot::ZCandidate> dummyZCandidateCollection;
    edm::Wrapper<std::vector<vallot::ZCandidate> > dummyZCandidateCollectionWrapper;
    edm::Ptr<vallot::ZCandidate> dummyZCandidatePtr;

    vallot::Lepton dummyLepton;
    edm::Wrapper<vallot::Lepton> dummyLeptonWrapper;
    std::vector<vallot::Lepton> dummyLeptonCollection;
    edm::Wrapper<std::vector<vallot::Lepton> > dummyLeptonCollectionWrapper;
    edm::Ptr<vallot::Lepton> dummyLeptonPtr;

    vallot::Jet dummyJet;
    edm::Wrapper<vallot::Jet> dummyJetWrapper;
    std::vector<vallot::Jet> dummyJetCollection;
    edm::Wrapper<std::vector<vallot::Jet> > dummyJetCollectionWrapper;
    edm::Ptr<vallot::Jet> dummyJetPtr;

    vallot::METCandidate dummyMETCandidate;
    edm::Wrapper<vallot::METCandidate> dummyMETCandidateWrapper;
    std::vector<vallot::METCandidate> dummyMETCandidateCollection;
    edm::Wrapper<std::vector<vallot::METCandidate> > dummyMETCandidateCollectionWrapper;
    edm::Ptr<vallot::METCandidate> dummyMETCandidatePtr;

    vallot::TTbarGenEvent dummyTTbarGenEvent;
    edm::Wrapper<vallot::TTbarGenEvent> dummyTTbarGenEventWrapper;
    std::vector<vallot::TTbarGenEvent> dummyTTbarGenEventCollection;
    edm::Wrapper<std::vector<vallot::TTbarGenEvent> > dummyTTbarGenEventCollectionWrapper;
    edm::Ptr<vallot::TTbarGenEvent> dummyTTbarGenEventPtr;

    vallot::TTbarMass dummyTTbarMass;
    edm::Wrapper<vallot::TTbarMass> dummyTTbarMassWrapper;
    std::vector<vallot::TTbarMass> dummyTTbarMassCollection;
    edm::Wrapper<std::vector<vallot::TTbarMass> > dummyTTbarMassCollectionWrapper;
    edm::Ptr<vallot::TTbarMass> dummyTTbarMassPtr;

    vallot::TTbarDILEvent dummyTTbarDILEvent;
    edm::Wrapper<vallot::TTbarDILEvent> dummyTTbarDILEventWrapper;
    std::vector<vallot::TTbarDILEvent> dummyTTbarDILEventCollection;
    edm::Wrapper<std::vector<vallot::TTbarDILEvent> > dummyTTbarDILEventCollectionWrapper;
    edm::Ptr<vallot::TTbarDILEvent> dummyTTbarDILEventPtr;

    vallot::TTbarCandidate dummyTTbarCandidate;
    edm::Wrapper<vallot::TTbarCandidate> dummyTTbarCandidateWrapper;
    std::vector<vallot::TTbarCandidate> dummyTTbarCandidateCollection;
    edm::Wrapper<std::vector<vallot::TTbarCandidate> > dummyTTbarCandidateCollectionWrapper;
    edm::Ptr<vallot::TTbarCandidate> dummyTTbarCandidatePtr;

    vallot::H2WWMass dummyH2WWMass;
    edm::Wrapper<vallot::H2WWMass> dummyH2WWMassWrapper;
    std::vector<vallot::H2WWMass> dummyH2WWMassCollection;
    edm::Wrapper<std::vector<vallot::H2WWMass> > dummyH2WWMassCollectionWrapper;
    edm::Ptr<vallot::H2WWMass> dummyH2WWMassPtr;
  };

}
