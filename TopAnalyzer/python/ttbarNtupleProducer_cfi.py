import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
jetIdForTTbar = looseJetIdPSet.clone()
jetIdForTTbar.verbose = False

mm = cms.EDAnalyzer("TTbarMuMuEventNtupleProducer",
    genParticle = cms.InputTag("genParticles"),

    lepton1 = cms.InputTag("Muons"),
    lepton2 = cms.InputTag("Muons"),
    met = cms.InputTag("patMETsPFlow"),
    jet = cms.InputTag("selectedPatJetsPFlow"),

    jetId = jetIdForTTbar,
    doResJec = cms.untracked.bool(False),

    minJetIso1 = cms.double(0.21),
    minJetIso2 = cms.double(0.21),
)

ee = cms.EDAnalyzer("TTbarElElEventNtupleProducer",
    genParticle = cms.InputTag("genParticles"),

    lepton1 = cms.InputTag("Electrons"),
    lepton2 = cms.InputTag("Electrons"),
    met = cms.InputTag("patMETsPFlow"),
    jet = cms.InputTag("selectedPatJetsPFlow"),

    jetId = jetIdForTTbar,
    doResJec = cms.untracked.bool(False),

    minJetIso1 = cms.double(0.26),
    minJetIso2 = cms.double(0.26),
)

em = cms.EDAnalyzer("TTbarElMuEventNtupleProducer",
    genParticle = cms.InputTag("genParticles"),

    lepton1 = cms.InputTag("Electrons"),
    lepton2 = cms.InputTag("Muons"),
    met = cms.InputTag("patMETsPFlow"),
    jet = cms.InputTag("selectedPatJetsPFlow"),

    jetId = jetIdForTTbar,
    doResJec = cms.untracked.bool(False),

    minJetIso1 = cms.double(0.26),
    minJetIso2 = cms.double(0.21),
)

