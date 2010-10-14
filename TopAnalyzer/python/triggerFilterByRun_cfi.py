import FWCore.ParameterSet.Config as cms

muonTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(145000),
            triggerName = cms.untracked.string("HLT_Mu9")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(145000),
            runEnd = cms.untracked.int32(147120),
            triggerName = cms.untracked.string("HLT_Mu11")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(999999),
            triggerName = cms.untracked.string("HLT_Mu15_v1")
        )
    )
)

electronTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(138000),
            triggerName = cms.untracked.string("HLT_Ele10_LW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(138000),
            runEnd = cms.untracked.int32(141900),
            triggerName = cms.untracked.string("HLT_Ele15_LW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(141900),
            runEnd = cms.untracked.int32(144000),
            triggerName = cms.untracked.string("HLT_Ele15_SW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(144000),
            runEnd = cms.untracked.int32(144114),
            triggerName = cms.untracked.string("HLT_Ele15_SW_CaloEleId_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(144000),
            runEnd = cms.untracked.int32(144114),
            triggerName = cms.untracked.string("HLT_DoubleEle10_SW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(146000),
            runEnd = cms.untracked.int32(147120),
            triggerName = cms.untracked.string("HLT_Ele17_SW_CaloEleId_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(999999),
            triggerName = cms.untracked.string("HLT_DoubleEle15_SW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(999999),
            triggerName = cms.untracked.string("HLT_Ele17_SW_TightCaloEleId_SC8HE_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(999999),
            triggerName = cms.untracked.string("HLT_Ele17_SW_TightEleId_L1R")
        ),
    )
)

