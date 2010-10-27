from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_data_cff")
process.hltHighLevel.HLTPaths = cms.vstring()
