#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/TopAnalyzer/interface/TopDILAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

typedef TopDILAnalyzer<pat::Muon,pat::Muon,pat::MET> TopMuMuAnalyzer;
typedef TopDILAnalyzer<pat::Muon,pat::Electron,pat::MET> TopMuElAnalyzer;
typedef TopDILAnalyzer<pat::Electron,pat::Electron,pat::MET> TopElElAnalyzer;

DEFINE_FWK_MODULE(TopMuMuAnalyzer);
DEFINE_FWK_MODULE(TopMuElAnalyzer);
DEFINE_FWK_MODULE(TopElElAnalyzer);

