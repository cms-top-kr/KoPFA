import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
muontagId = muonSelectorPSet.clone()
muontagId.dxy = 0.02
muontagId.eta = 2.4
muontagId.pt = 20

muonprobId = muonSelectorPSet.clone()
muonprobId.dxy = 0.02
muonprobId.eta = 2.4
muonprobId.pt = 5


from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonIso = muonIsoSelectorPSet.clone()

taggedMuons = cms.EDProducer(
    "KoMuonSelector",
    cut = cms.vstring("TOPDIL"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muontagId,
    muonIsoSelector = muonIso,
)

PFMuons = cms.EDProducer(
    "KoMuonRefSelector",
    cut = cms.vstring("pt","eta"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonprobId,
    muonIsoSelector = muonIso,
)

IDMuons = cms.EDProducer(
    "KoMuonRefSelector",
    cut = cms.vstring("pt","eta","dxy"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonprobId,
    muonIsoSelector = muonIso,
)

IsoMuons = cms.EDProducer(
    "KoMuonRefSelector",
    cut = cms.vstring("pt","eta","dxy"),
    isocut = cms.vstring("pfOptimizedRel"),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonprobId,
    muonIsoSelector = muonIso,
)

from PFAnalyses.CommonTools.Selectors.electronSelectorPSet_cff import electronSelectorPSet
from PFAnalyses.CommonTools.Selectors.newElectronIsoSelectorPSet_cff import electronIsoSelectorPSet

Electrons = cms.EDProducer(
    "KoElectronSelector",
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    electronIdSelector = electronSelectorPSet,
    electronIsoSelector = electronIsoSelectorPSet,
)

