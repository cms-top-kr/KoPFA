import FWCore.ParameterSet.Config as cms

Electrons = cms.EDFilter('CMGElectronFilter',
    applyFilter = cms.untracked.bool(False),
    electronLabel  = cms.InputTag("cmgElectronSel"),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    ptcut = cms.untracked.double(20),
    etacut = cms.untracked.double(2.4),
    mvacut = cms.untracked.double(0.5),
    relIso = cms.untracked.double(999),
    numberOfHits = cms.untracked.uint32(0),
)
