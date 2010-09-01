import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
muonSelector = muonSelectorPSet.clone()


acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuons"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5")
)

Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 3 ),#TOP
    muonLabel  = cms.InputTag("selectedPatMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1)
)

acceptedMuonsPFlow = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5")
)

PFMuons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 3 ),#TOP
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

patPFMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('PFMuons'),
  minNumber = cms.uint32(1)
)

