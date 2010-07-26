import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
muonSelector = muonSelectorPSet.clone()


acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuons"),
    cut =cms.string("pt > 15 && abs(eta) < 2.4")
)

Muons = cms.EDProducer(
    "MuonSelector",
    muonLabel  = cms.InputTag("acceptedMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1)
)

acceptedMuonsPFlow = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 15 && abs(eta) < 2.4")
)

PFMuons = cms.EDProducer(
    "MuonSelector",
    muonLabel  = cms.InputTag("acceptedMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

patPFMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('PFMuons'),
  minNumber = cms.uint32(1)
)

