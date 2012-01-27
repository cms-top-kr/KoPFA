#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/SourceFactory.h"
#include "CondCore/PluginSystem/interface/registration_macros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionService.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionServiceChain.h"
#include "JetMETCorrections/Modules/interface/JetCorrectionProducer.h"
#include "JetMETCorrections/Algorithms/interface/LXXXCorrector.h"
#include "JetMETCorrections/Algorithms/interface/L1OffsetCorrector.h"
#include "JetMETCorrections/Algorithms/interface/L1FastjetCorrector.h"
#include "JetMETCorrections/Algorithms/interface/L6SLBCorrector.h"
/*
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/JPTJet.h"
#include "DataFormats/JetReco/interface/TrackJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
*/
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

using namespace cms;
using namespace reco;

typedef JetCorrectionProducer<pat::Jet> KoCorrectJetProducer;
DEFINE_FWK_MODULE(KoCorrectJetProducer);

