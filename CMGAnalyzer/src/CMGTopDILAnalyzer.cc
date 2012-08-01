#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CMGAnalyzer/interface/CMGTopDILAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"


typedef CMGTopDILAnalyzer<cmg::Muon,cmg::Muon> CMGTopMuMuAnalyzer;
typedef CMGTopDILAnalyzer<cmg::Muon,cmg::Electron> CMGTopMuElAnalyzer;
typedef CMGTopDILAnalyzer<cmg::Electron,cmg::Electron> CMGTopElElAnalyzer;

DEFINE_FWK_MODULE(CMGTopMuMuAnalyzer);
DEFINE_FWK_MODULE(CMGTopMuElAnalyzer);
DEFINE_FWK_MODULE(CMGTopElElAnalyzer);

