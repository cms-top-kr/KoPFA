#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"

namespace Ko {

  std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
  bool hasBottom(const reco::Candidate &c);
  bool decayFromBHadron(const reco::Candidate &c);
  const reco::Candidate* lastBHadron(const reco::Candidate &c);
  double dR( const reco::Candidate &pasObj, const reco::GenJet &proObj );
 
}
