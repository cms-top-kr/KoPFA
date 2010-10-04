from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010A_Jul16thReReco_cff")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele15_LW_L1R")
