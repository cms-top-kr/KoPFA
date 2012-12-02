import FWCore.ParameterSet.Config as cms

MuonIsoAnalysis = cms.EDProducer("cmgMuonIsoAnalyzer",
  muonLabel = cms.InputTag('cmgMuonSel'),
  beamSpotLabel = cms.InputTag('offlineBeamSpot'),
  metLabel = cms.InputTag('cmgPFMET'),
  jetLabel = cms.InputTag('cmgPFJetSelCHS'),
  genParticlesLabel = cms.InputTag('genParticlesPruned'),
  vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
  useZMassWindow = cms.untracked.bool(False),
  applyPFId = cms.untracked.bool(False),
  numberOfLeptons    = cms.untracked.uint32(2), 
  qcdMC = cms.untracked.bool(False), 
#  qcdMC = cms.untracked.bool(True),  #for QCD MC
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
      'prePathCounter',
      'postPathCounter',
      'nEventsPatHLT',
      'nEventsFilter'
  )
)

