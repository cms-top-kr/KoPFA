import FWCore.ParameterSet.Config as cms

Muons = cms.EDFilter('CMGMuonFilter',
    applyFilter = cms.untracked.bool(False),
    muonLabel  = cms.InputTag("cmgMuonSel"),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    ptcut = cms.untracked.double(20),
    etacut = cms.untracked.double(2.5),
    relIso = cms.untracked.double(999),
)

