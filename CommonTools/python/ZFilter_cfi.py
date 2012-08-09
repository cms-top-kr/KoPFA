import FWCore.ParameterSet.Config as cms

ZMuMu = cms.EDFilter("ZmmFilter",
  applyFilter = cms.untracked.bool(True),
  filterIso = cms.untracked.bool(False),
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Muons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.2),
  relIso2 = cms.untracked.double(0.2),
)

ZElEl = cms.EDFilter("ZeeFilter",
  applyFilter = cms.untracked.bool(True),
  filterIso = cms.untracked.bool(False),
  muonLabel1 =  cms.InputTag('Electrons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.17),
  relIso2 = cms.untracked.double(0.17),
)

ZMuEl = cms.EDFilter("ZmeFilter",
  applyFilter = cms.untracked.bool(True),
  filterIso = cms.untracked.bool(False),
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.2),
  relIso2 = cms.untracked.double(0.17),
)
