#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CommonTools/interface/WFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

typedef WFilter<pat::Muon> WmnuFilter;
typedef WFilter<pat::Electron> WenuFilter;

DEFINE_FWK_MODULE(WmnuFilter);
DEFINE_FWK_MODULE(WenuFilter);

