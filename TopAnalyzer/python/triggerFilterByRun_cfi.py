import FWCore.ParameterSet.Config as cms

muonTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),
    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(145000),
            triggerNames = cms.untracked.vstring("HLT_Mu9")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(145000),
            runEnd = cms.untracked.int32(147120),
            triggerNames = cms.untracked.vstring("HLT_Mu11")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Mu15_v1")
        )
    )
)

electronTriggerFilterByRun = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(138000),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_SW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(138000),
            triggerNames = cms.untracked.vstring("HLT_Ele10_LW_L1R")
       ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(138000),
            runEnd = cms.untracked.int32(141900),
            triggerNames = cms.untracked.vstring("HLT_Ele15_LW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(141900),
            runEnd = cms.untracked.int32(144000),
            triggerNames = cms.untracked.vstring("HLT_Ele15_SW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(144000),
            runEnd = cms.untracked.int32(144114),
            triggerNames = cms.untracked.vstring("HLT_Ele15_SW_CaloEleId_L1R",
                                                 "HLT_Ele20_SW_L1R",
                                                 "HLT_DoubleEle10_SW_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(146000),
            runEnd = cms.untracked.int32(147120),
            triggerNames = cms.untracked.vstring("HLT_DoubleEle10_SW_L1R",
                                                 "HLT_Ele17_SW_CaloEleId_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(147120),
            runEnd = cms.untracked.int32(148100),
            triggerNames = cms.untracked.vstring("HLT_DoubleEle15_SW_L1R_v1",
                                                 "HLT_Ele17_SW_TightCaloEleId_SC8HE_L1R_v1",
                                                 "HLT_Ele17_SW_TightEleId_L1R")
        ),
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(148100),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_DoubleEle17_SW_L1R_v1",
                                                 "HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2",
                                                 "HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v1",
                                                 "HLT_Ele22_SW_TighterEleId_L1R_v3",
                                                 "HLT_Ele22_SW_TighterEleId_L1R_v2",
                                                 "HLT_Ele17_SW_TighterEleIdIsol_L1R_v3",
                                                 "HLT_Ele17_SW_TighterEleIdIsol_L1R_v2")
        ),
    )
)

muonTriggerFilterForMC = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    doMatch = cms.untracked.bool(False),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Mu9")
        )
    )
)

muonTriggerFilterForMCREDIGI38X = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38X"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    doMatch = cms.untracked.bool(False),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Mu9")
        )
    )
)

muonTriggerFilterForMCREDIGI38XPU = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38XPU"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    doMatch = cms.untracked.bool(False),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Mu9")
        )
    )
)

electronTriggerFilterForMC = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_SW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_SW_L1R")
        )
    )
)

electronTriggerFilterForMCREDIGI38X = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38X"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "REDIGI38X"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_SW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_SW_L1R")
        )
    )
)

electronTriggerFilterForMCREDIGI38XPU = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38XPU"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "REDIGI38XPU"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_SW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_SW_L1R")
        )
    )
)

emuTriggerFilterForMC = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "HLT"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_SW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_SW_L1R","HLT_Mu9")
        )
    )
)

emuTriggerFilterForMCREDIGI38X = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38X"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "REDIGI38X"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_LW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_LW_L1R","HLT_Mu9")
        )
    )
)

emuTriggerFilterForMCREDIGI38XPU = cms.EDFilter("TriggerFilterByRun",
    triggerResults = cms.untracked.InputTag("TriggerResults", "", "REDIGI38XPU"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "REDIGI38XPU"),
    filter = cms.untracked.bool(True),
    filterOutUndefined = cms.untracked.bool(True),

    ## Special treatment for early runs, to do trigger object matching
    doMatch = cms.untracked.bool(True),
    matchRunBegin = cms.untracked.int32(0),
    matchRunEnd = cms.untracked.int32(999999),
    matchMinPt = cms.untracked.double(15),
    matchTriggerPath = cms.untracked.string("HLT_Ele10_LW_L1R"),
    matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter"),

    triggerPSets = cms.untracked.VPSet(
        cms.untracked.PSet(
            runBegin = cms.untracked.int32(0),
            runEnd = cms.untracked.int32(999999),
            triggerNames = cms.untracked.vstring("HLT_Ele10_LW_L1R","HLT_Mu9")
        )
    )
)

