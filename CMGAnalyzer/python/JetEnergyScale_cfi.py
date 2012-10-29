import FWCore.ParameterSet.Config as cms

from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

JetEnergyScale = cms.EDFilter('CMGJetFilter',
    applyFilter = cms.untracked.bool(False),
    bJetFirst = cms.untracked.bool(False),
    bTagAlgo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
    bTagValue = cms.untracked.double(0.244),
    rhoLabel =  cms.InputTag('kt6PFJets','rho'),
    jetLabel =  cms.InputTag('cmgPFJetSelCHS'),
    metLabel =  cms.InputTag('cmgPFMET'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.uint32(0),
    ptcut = cms.untracked.double(30.),
    absetacut = cms.untracked.double(2.5),
    looseJetId = myJetId,
    doJecFly = cms.untracked.bool(False),
    doResJec = cms.untracked.bool(False),
    doJecUnc = cms.untracked.bool(False),
    up = cms.untracked.bool(True),
    doJERUnc = cms.untracked.bool(False),
    resolutionFactor = cms.untracked.double(1.0),
    globalTag = cms.untracked.string("GR_R_42_V23"),
)
