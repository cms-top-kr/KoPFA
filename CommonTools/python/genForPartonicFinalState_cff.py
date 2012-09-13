import FWCore.ParameterSet.Config as cms

# To reconstruct genjets without the neutrinos
from RecoJets.Configuration.GenJetParticles_cff import *
from RecoJets.Configuration.RecoGenJets_cff import *

genParticlesForPartonicFinalState = genParticlesForJets.clone()
genParticlesForPartonicFinalState.partonicFinalStates = cms.bool(True)

ak5GenJetsPartonicFinalState = ak5GenJets.clone( src = cms.InputTag("genParticlesForPartonicFinalState") )

genForPartonicFinalState = cms.Sequence(
    genParticlesForPartonicFinalState +
    ak5GenJetsPartonicFinalState
    )

