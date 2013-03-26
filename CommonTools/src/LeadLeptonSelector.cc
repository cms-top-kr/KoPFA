#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoPFA/CommonTools/interface/LeadLeptonSelector.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef LeadLeptonSelector<pat::Muon> LeadMuonSelector;
typedef LeadLeptonSelector<pat::Electron> LeadElectronSelector;

DEFINE_FWK_MODULE(LeadMuonSelector);
DEFINE_FWK_MODULE(LeadElectronSelector);

