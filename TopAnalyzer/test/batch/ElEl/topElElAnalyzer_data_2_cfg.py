from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010B_PromptReco_cff")
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )
#process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele15_LW_L1R","HLT_Ele15_SW_L1R","HLT_Ele15_SW_CaloEleId_L1R")
#process.hltHighLevel.throw = cms.bool(False)
