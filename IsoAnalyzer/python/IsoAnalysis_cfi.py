import FWCore.ParameterSet.Config as cms

MuonIsoAnal = cms.EDAnalyzer('MuonIsoAnalysis',
    collectionLabel =  cms.InputTag('selectedPatMuonsPFlowIso'),
    pfCandidateLabel = cms.InputTag('particleFlow'),
    genParticlesLabel = cms.InputTag('genParticles'),
    matchId = cms.int32(13),
)

ElecIsoAnal = cms.EDAnalyzer('ElecIsoAnalysis',
    collectionLabel =  cms.InputTag('selectedPatElectronsPFlowIso'),
    pfCandidateLabel = cms.InputTag('particleFlow'),
    genParticlesLabel = cms.InputTag('genParticles'),
    matchId = cms.int32(11),
)

