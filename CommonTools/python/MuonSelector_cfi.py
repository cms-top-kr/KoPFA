import FWCore.ParameterSet.Config as cms

acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuons"),
    cut =cms.string("pt > 15 && abs(eta) < 2.4")
)

Muons = cms.EDProducer(
    "MuonSelector",
    muonLabel  = cms.InputTag("acceptedMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),

    chi2 = cms.untracked.double("999999"),
    nHits = cms.untracked.double("-1"),
    d0 = cms.untracked.double("0.2"),
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

    chi2 = cms.untracked.double("999999"),
    nHits = cms.untracked.double("-1"),
    d0 = cms.untracked.double("0.2"),
)

patPFMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('PFMuons'),
  minNumber = cms.uint32(1)
)

