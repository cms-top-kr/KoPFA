from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010A_Jun14thReReco_cff")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele10_LW_L1R")

