import FWCore.ParameterSet.Config as cms

topWLeptonGenFilter = cms.EDFilter("GenParticleDecayFilter",
    applyFilter = cms.untracked.bool( False ),
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(11, 13), #remove tau decay from signal
    minCount = cms.untracked.uint32(2),
)

