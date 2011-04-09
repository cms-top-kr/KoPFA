import FWCore.ParameterSet.Config as cms

ttbarGenAna = cms.EDAnalyzer('TTbarGenLevelAnalyzer',
    genParticle = cms.InputTag('genParticles'),
    electronMaxEta = cms.double(2.5),
    electronMinPt = cms.double(10),
    muonMaxEta = cms.double(2.4),
    muonMinPt = cms.double(10),
    jetMaxEta = cms.double(2.5),
    jetMinPt = cms.double(30),
    metMinPt = cms.double(30),
)
