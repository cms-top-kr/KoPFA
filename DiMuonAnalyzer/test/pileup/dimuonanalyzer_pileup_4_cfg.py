from KoPFA.DiMuonAnalyzer.dimuonanalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_PromptReco_cff")

process.VertexFilter.min = 2
process.VertexFilter.max = 9999

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
process.TFileService.fileName = "vallot_PVs.root"
