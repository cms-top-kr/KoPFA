#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/IsoAnalyzer/interface/LeptonIsoAna.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef LeptonIsoAna<pat::Muon> MuonIsoAna;
typedef LeptonIsoAna<pat::Electron> ElecIsoAna;

DEFINE_FWK_MODULE(MuonIsoAna);
DEFINE_FWK_MODULE(ElecIsoAna);
