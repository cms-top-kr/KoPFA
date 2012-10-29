import FWCore.ParameterSet.Config as cms

Electrons = cms.EDFilter('CMGElectronFilter',
    applyFilter = cms.untracked.bool(False),
    electronLabel  = cms.InputTag("cmgElectronSel"),
    ptcut = cms.untracked.double(20),
    etacut = cms.untracked.double(2.5),
    mvacut = cms.untracked.double(0.0),
    relIso = cms.untracked.double(999),
)
