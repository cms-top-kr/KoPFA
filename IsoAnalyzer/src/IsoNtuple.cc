#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/IsoAnalyzer/interface/IsoNtuple.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
//#include "AnalysisDataFormats/PFAnalyses/interface/RandomCone.h"

typedef IsoNtuple<pat::Muon> MuonIsoNtuple;
typedef IsoNtuple<pat::Electron> ElecIsoNtuple;
//typedef IsoNtuple<RandomCone> RandomIsoNtuple;

DEFINE_FWK_MODULE(MuonIsoNtuple);
DEFINE_FWK_MODULE(ElecIsoNtuple);
//DEFINE_FWK_MODULE(RandomIsoNtuple);

