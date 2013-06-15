import FWCore.ParameterSet.Config as cms

## EventContents
from PhysicsTools.PatAlgos.patEventContent_cff import *
pf2patEventContent = cms.untracked.vstring('drop *')
pf2patEventContent += patTriggerEventContent
pf2patEventContent += patExtraAodEventContent
#pf2patEventContent += patEventContentNoCleaning
pf2patEventContent +=[
        'keep edmMergeableCounter_*_*_*',
        'keep *_goodOfflinePrimaryVertices*_*_*',
        'drop *_offlinePrimaryVertices*_*_*',
        'drop *_towerMaker_*_*',
#        'keep *_particleFlow_*_*',
        'keep *_acceptedMuons_*_*',
        'keep *_acceptedElectrons_*_*',
        'keep patJets_selectedPatJetsPFlow_*_*',
        'keep *_patMETsPFlow_*_*',
        'keep double_kt6PFJets*_rho_*',
#        'keep *_pfJets*_*_*',
        'keep *_addPileupInfo_*_*',
        'keep *_ak5GenJets*_*_*',
        'keep *_genMet*_*_*',
        'drop recoGenJets_selectedPatJets*_genJets_PAT',
        'drop recoPFCandidates_selectedPatJetsPFlow_pfCandidates_PAT',
]

