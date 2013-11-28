#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CMGAnalyzer/interface/CMGTopDILJPsiAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

typedef CMGTopDILJPsiAnalyzer<cmg::Muon,cmg::Muon,cmg::Muon,cmg::Muon> CMGTopMuMu2MuAnalyzer;
typedef CMGTopDILJPsiAnalyzer<cmg::Muon,cmg::Muon,cmg::Electron,cmg::Electron> CMGTopMuMu2ElAnalyzer;
typedef CMGTopDILJPsiAnalyzer<cmg::Muon,cmg::Electron,cmg::Muon,cmg::Muon> CMGTopMuEl2MuAnalyzer;
typedef CMGTopDILJPsiAnalyzer<cmg::Muon,cmg::Electron,cmg::Electron,cmg::Electron> CMGTopMuEl2ElAnalyzer;
typedef CMGTopDILJPsiAnalyzer<cmg::Electron,cmg::Electron,cmg::Muon,cmg::Muon> CMGTopElEl2MuAnalyzer;
typedef CMGTopDILJPsiAnalyzer<cmg::Electron,cmg::Electron,cmg::Electron,cmg::Electron> CMGTopElEl2ElAnalyzer;

DEFINE_FWK_MODULE(CMGTopMuMu2MuAnalyzer);
DEFINE_FWK_MODULE(CMGTopMuMu2ElAnalyzer);
DEFINE_FWK_MODULE(CMGTopMuEl2MuAnalyzer);
DEFINE_FWK_MODULE(CMGTopMuEl2ElAnalyzer);
DEFINE_FWK_MODULE(CMGTopElEl2MuAnalyzer);
DEFINE_FWK_MODULE(CMGTopElEl2ElAnalyzer);

