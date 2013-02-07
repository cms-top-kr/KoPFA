import FWCore.ParameterSet.Config as cms

ZMuMu = cms.EDFilter("CMGZmmFilter",
  applyFilter = cms.untracked.bool(True),
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Muons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
  rhoIsoLabel =  cms.untracked.InputTag('kt6PFJets','rho'),
)

ZElEl = cms.EDFilter("CMGZeeFilter",
  applyFilter = cms.untracked.bool(True),
  muonLabel1 =  cms.InputTag('Electrons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
  rhoIsoLabel =  cms.untracked.InputTag('kt6PFJets','rho'),
)

ZMuEl = cms.EDFilter("CMGZmeFilter",
  applyFilter = cms.untracked.bool(True),
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  min = cms.double(12),
  max = cms.double(99999),
  relIso1 = cms.untracked.double(0.15),
  relIso2 = cms.untracked.double(0.15),
  rhoIsoLabel =  cms.untracked.InputTag('kt6PFJets','rho'),
)
