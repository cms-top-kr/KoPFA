import FWCore.ParameterSet.Config as cms

from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

JetEnergyScale = cms.EDFilter('JetFilter',
    applyFilter = cms.untracked.bool(False),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    min = cms.untracked.uint32(0),
    ptcut = cms.untracked.double(30.),
    absetacut = cms.untracked.double(2.4),
    looseJetId = myJetId,
    doJecFly = cms.untracked.bool(True),
    doResJec = cms.untracked.bool(False),
    doJecUnc = cms.untracked.bool(False),
    up = cms.untracked.bool(True),
    doJERUnc = cms.untracked.bool(False),
    resolutionFactor = cms.untracked.double(1.0),
    globalTag = cms.untracked.string("GR_R_42_V23"),
)
