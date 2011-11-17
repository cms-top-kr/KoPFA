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
        'keep *_selectedPatJetsPFlow_*_*',
        'keep *_patMETsPFlow_*_*',
        'keep double_*PFlow*_rho_PAT',
#        'keep *_pfJets*_*_*',
        'keep *_addPileupInfo_*_*',
]

