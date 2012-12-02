import FWCore.ParameterSet.Config as cms

ttbarGenAna = cms.EDAnalyzer('TTbarGenLevelAnalyzer',
    genParticle = cms.InputTag('genParticles'),
    genJet = cms.InputTag("ak5GenJets"),
    genMET = cms.InputTag("genMetTrue"),
)
