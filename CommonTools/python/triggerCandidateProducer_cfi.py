import FWCore.ParameterSet.Config as cms

# just a template.
# this module should be cloned, and the HLTPath changed for the clone

triggerCandidate = cms.EDProducer(
    "TriggerTool",
    processName = cms.string("HLT"),
    TriggerEvent = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
    TriggerResults = cms.InputTag("TriggerResults","","HLT"),
    verbose_ = cms.untracked.bool( True ),
    HLTPath = cms.string("HLT_Jet50U")
    )

