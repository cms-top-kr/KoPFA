#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/TopAnalyzer/interface/TopLJAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

typedef TopLJAnalyzer<pat::Muon> TopMuJetAnalyzer;
typedef TopLJAnalyzer<pat::Electron> TopElJetAnalyzer;

DEFINE_FWK_MODULE(TopMuJetAnalyzer);
DEFINE_FWK_MODULE(TopElJetAnalyzer);

