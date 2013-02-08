import FWCore.ParameterSet.Config as cms

ttbar2bFilter = cms.EDFilter('CMGTTbar2bGenFilter',
        genParticlesLabel = cms.InputTag('genParticlesPruned'),
        genJetsLabel = cms.InputTag('genJetSel'),
)

