import FWCore.ParameterSet.Config as cms

topWENuGenFilter = cms.EDFilter("GenParticleDecayFilter",
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(11, 12),
    minCount = cms.untracked.uint32(2),
)

topWMuNuGenFilter = cms.EDFilter("GenParticleDecayFilter",
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(13, 14),
    minCount = cms.untracked.uint32(2),
)

