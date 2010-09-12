from KoPFA.TopAnalyzer.topMuMuAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_PromptReco_cff")
#process.load("KoPFA.DiMuonAnalyzer.MC.Spring10.patTuple_Zmumu_cff")
#process.load("KoPFA.DiMuonAnalyzer.MC.Spring10.patTuple_ZJets_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.VertexFilter.min = 1
process.VertexFilter.max = 9999
