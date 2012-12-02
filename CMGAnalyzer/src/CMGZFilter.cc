#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CMGAnalyzer/interface/CMGZFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

typedef CMGZFilter<cmg::Muon,cmg::Muon> CMGZmmFilter;
typedef CMGZFilter<cmg::Muon,cmg::Electron> CMGZmeFilter;
typedef CMGZFilter<cmg::Electron,cmg::Electron> CMGZeeFilter;

DEFINE_FWK_MODULE(CMGZmmFilter);
DEFINE_FWK_MODULE(CMGZmeFilter);
DEFINE_FWK_MODULE(CMGZeeFilter);

