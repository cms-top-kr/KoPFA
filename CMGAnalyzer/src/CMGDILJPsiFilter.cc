#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CMGAnalyzer/interface/CMGDILJPsiFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

typedef CMGDILJPsiFilter<cmg::Muon,cmg::Muon,cmg::Muon,cmg::Muon> CMGmmJPsimmFilter;
typedef CMGDILJPsiFilter<cmg::Muon,cmg::Muon,cmg::Electron,cmg::Electron> CMGmmJPsieeFilter;
typedef CMGDILJPsiFilter<cmg::Muon,cmg::Electron,cmg::Muon,cmg::Muon> CMGmeJPsimmFilter;
typedef CMGDILJPsiFilter<cmg::Muon,cmg::Electron,cmg::Electron,cmg::Electron> CMGmeJPsieeFilter;
typedef CMGDILJPsiFilter<cmg::Electron,cmg::Electron,cmg::Muon,cmg::Muon> CMGeeJPsimmFilter;
typedef CMGDILJPsiFilter<cmg::Electron,cmg::Electron,cmg::Electron,cmg::Electron> CMGeeJPsieeFilter;

DEFINE_FWK_MODULE(CMGmmJPsimmFilter);
DEFINE_FWK_MODULE(CMGmmJPsieeFilter);
DEFINE_FWK_MODULE(CMGmeJPsimmFilter);
DEFINE_FWK_MODULE(CMGmeJPsieeFilter);
DEFINE_FWK_MODULE(CMGeeJPsimmFilter);
DEFINE_FWK_MODULE(CMGeeJPsieeFilter);

