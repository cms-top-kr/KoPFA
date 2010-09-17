from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010A_Jul16thReReco_cff")
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_Ele10_LW_L1R',"HLT_Ele15_LW_L1R","HLT_Ele15_SW_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele20_SW_L1R","HLT_DoubleEle10_SW_L1R")

