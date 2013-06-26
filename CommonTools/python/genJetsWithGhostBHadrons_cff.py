import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Generator_cff import *

genParticlesWithGhostB = cms.EDProducer("GhostBHadronProducer",
    src = cms.InputTag("genParticles"),
    userPdgId = cms.untracked.int32(0),
)

genParticlesForJets.src = cms.InputTag("genParticlesWithGhostB")
genParticlesForJetsNoNu.src = cms.InputTag("genParticlesWithGhostB")
#genParticlesForJets.partonicFinalState = cms.bool(True)
#ak5GenJets.inputEtMin = cms.double(-1.0)
#ak5GenJets.inputEMin = cms.double(-1.0)


