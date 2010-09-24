import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()

muonId.dxy = 0.02
muonId.eta = 2.5
muonId.pt = 20

Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 1 ),#TOP
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,

)

Electrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5 && abs(gsfTrack.dxy) < 0.04 && mva > 0.4 && gsfTrack.trackerExpectedHitsInner.numberOfHits<=1 ")
    #cut =cms.string("pt > 20 && abs(eta) < 2.5")
)


