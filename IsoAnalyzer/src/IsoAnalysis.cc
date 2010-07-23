#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/IsoAnalyzer/interface/IsoAnalysis.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef IsoAnalysis<pat::Muon> MuonIsoAnalysis;
typedef IsoAnalysis<pat::Electron> ElecIsoAnalysis;

DEFINE_FWK_MODULE(MuonIsoAnalysis);
DEFINE_FWK_MODULE(ElecIsoAnalysis);

