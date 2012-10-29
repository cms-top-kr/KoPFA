import FWCore.ParameterSet.Config as cms

CMGFinalLeptons = cms.EDProducer("CMGFinalLeptonProducer",
  MuMuLep1Label =  cms.untracked.InputTag('ZMuMu','Lepton1'),
  MuMuLep2Label =  cms.untracked.InputTag('ZMuMu','Lepton2'),
  MuElLep1Label =  cms.untracked.InputTag('ZMuEl','Lepton1'),
  MuElLep2Label =  cms.untracked.InputTag('ZMuEl','Lepton2'),
  ElElLep1Label =  cms.untracked.InputTag('ZElEl','Lepton1'),
  ElElLep2Label =  cms.untracked.InputTag('ZElEl','Lepton2'),
)
