import FWCore.ParameterSet.Config as cms

ZMuMu = cms.EDFilter("CMGZmmFilter",
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Muons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
)

ZElEl = cms.EDFilter("CMGZeeFilter",
  muonLabel1 =  cms.InputTag('Electrons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
)

ZMuEl = cms.EDFilter("CMGZmeFilter",
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
)
