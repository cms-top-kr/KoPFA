import FWCore.ParameterSet.Config as cms

genMassLLBBMet = cms.EDAnalyzer("TTbarMassAnalyzer",
    lepton1 = cms.InputTag("genLeptons"),
    lepton2 = cms.InputTag("genLeptons"),
    jet = cms.InputTag("genBJets"),
    met = cms.InputTag("genMetTrue"),
    genTTbar = cms.untracked.string("genTTbar"),
)

genMassLLJJMet = cms.EDAnalyzer("TTbarMassAnalyzer",
    lepton1 = cms.InputTag("genLeptons"),
    lepton2 = cms.InputTag("genLeptons"),
    jet = cms.InputTag("ak5GenJets"),
    met = cms.InputTag("genMetTrue"),
    genTTbar = cms.untracked.string("genTTbar"),
)
