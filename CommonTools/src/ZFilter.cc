#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CommonTools/interface/ZFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

typedef ZFilter<pat::Muon,pat::Muon> ZmmFilter;
typedef ZFilter<pat::Muon,pat::Electron> ZmeFilter;
typedef ZFilter<pat::Electron,pat::Electron> ZeeFilter;

DEFINE_FWK_MODULE(ZmmFilter);
DEFINE_FWK_MODULE(ZmeFilter);
DEFINE_FWK_MODULE(ZeeFilter);

