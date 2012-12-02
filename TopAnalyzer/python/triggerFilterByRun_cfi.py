import FWCore.ParameterSet.Config as cms

mmTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(160404),
            runEnd = cms.untracked.int32(163260),
            triggerNames = cms.untracked.vstring("HLT_DoubleMu6_*")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(163261),
            runEnd = cms.untracked.int32(163869),
            triggerNames = cms.untracked.vstring("HLT_DoubleMu7_*")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(165364),
            runEnd = cms.untracked.int32(178380),
            triggerNames = cms.untracked.vstring("HLT_Mu13_Mu8_*")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(178380),
            runEnd = cms.untracked.int32(180252),
            triggerNames = cms.untracked.vstring("HLT_Mu17_Mu8_*")
        ),
    )
)

eeTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(160404),
            runEnd = cms.untracked.int32(167913),
            triggerNames = cms.untracked.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_*"),
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(167913),
            runEnd = cms.untracked.int32(180252),
            triggerNames = cms.untracked.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_*"),
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(161222),
            runEnd = cms.untracked.int32(166346),
            triggerNames = cms.untracked.vstring("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_*"),
        ),
    )
)

emTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(160404),
            runEnd = cms.untracked.int32(163869),
            triggerNames = cms.untracked.vstring("HLT_Mu10_Ele10_CaloIdL_*"),
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(160404),
            runEnd = cms.untracked.int32(167913),
            triggerNames = cms.untracked.vstring("HLT_Mu8_Ele17_CaloIdL_*"),
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(160404),
            runEnd = cms.untracked.int32(173198),
            triggerNames = cms.untracked.vstring("HLT_Mu17_Ele8_CaloIdL_*"),
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(167039),
            runEnd = cms.untracked.int32(180252),
            triggerNames = cms.untracked.vstring("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_*",
                                                 "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_*"),
        ),
    )
)
