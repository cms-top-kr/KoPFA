import FWCore.ParameterSet.Config as cms

ElectronAnalysis = cms.EDProducer("cmgElectronAnalyzer",
  electronLabel = cms.InputTag('cmgElectronSel'),
  beamSpotLabel = cms.InputTag('offlineBeamSpot'),
  metLabel = cms.InputTag('cmgPFMET'),
  jetLabel = cms.InputTag('cmgPFJetSelCHS'),
  vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
  rhoIsoLabel =  cms.untracked.InputTag('kt6PFJets','rho')
)

#ElectronAnalysis = cms.EDAnalyzer("pfElectronAnalyzer",
