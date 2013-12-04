import FWCore.ParameterSet.Config as cms

ttbarJPsiFilter = cms.EDFilter('CMGTTbarJPsiGenFilter',
        genParticlesLabel = cms.InputTag('genParticlesPruned'),
        genJetsLabel = cms.InputTag('genJetSel'),
)

