from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Commissioning10_cff")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele10_LW_L1R")
