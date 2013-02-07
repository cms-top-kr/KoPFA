import FWCore.ParameterSet.Config as cms

MuonAnalysis = cms.EDProducer("cmgMuonAnalyzer",
  muonLabel = cms.InputTag('cmgMuonSel'),
  beamSpotLabel = cms.InputTag('offlineBeamSpot'),
  metLabel = cms.InputTag('cmgPFMET'),
  jetLabel = cms.InputTag('cmgPFJetSelCHS'),
  genParticlesLabel = cms.InputTag('genParticlesPruned'),
  vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
  useZMassWindow = cms.untracked.bool(False),
  applyPFId = cms.untracked.bool(True),
  numberOfLeptons    = cms.untracked.uint32(1),
  numberOfJets    = cms.untracked.uint32(2),
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
      'prePathCounter',
      'postPathCounter'
  )
)

