import FWCore.ParameterSet.Config as cms

MuonAnalysis = cms.EDProducer("cmgEMuonIsoAnalyzer",
  muonLabel = cms.InputTag('cmgMuonSel'),
  electronLabel = cms.InputTag('cmgElectronSel'),
  beamSpotLabel = cms.InputTag('offlineBeamSpot'),
  #metLabel = cms.InputTag('cmgPFMET'),
  #jetLabel = cms.InputTag('cmgPFJetSelCHS'),
  metLabel =  cms.InputTag('JetEnergyScale','MET'),
  jetLabel =  cms.InputTag('JetEnergyScale','Jets'),
  genParticlesLabel = cms.InputTag('genParticlesPruned'),
  vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
  useZMassWindow = cms.untracked.bool(False),
  applyPreTrigSel = cms.untracked.bool(True),
  applyPFId = cms.untracked.bool(False),
  numberOfHits    = cms.untracked.uint32(0),
  numberOfLeptons    = cms.untracked.uint32(2), 
  numberOfJets    = cms.untracked.uint32(2),
  qcdMC = cms.untracked.bool(False), 
  #qcdMC = cms.untracked.bool(True),  #for QCD MC
  useEventCounter = cms.bool( True ),
  bTagSets = cms.untracked.VPSet(
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVL"),
        cutValue = cms.untracked.double(0.244),
        isCutMin = cms.untracked.bool(True),
    ),
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVM"),
        cutValue = cms.untracked.double(0.679),
        isCutMin = cms.untracked.bool(True),
    ),
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVT"),
        cutValue = cms.untracked.double(0.898),
        isCutMin = cms.untracked.bool(True),
    ),
  ),
  filters = cms.untracked.vstring(
      'prePathCounter',
      'postPathCounter',
      'nEventsPatHLT',
      'nEventsFilter'
  )
)

