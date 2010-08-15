from KoPFA.DiMuonAnalyzer.dimuonanalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Commissioning10_cff")

process.VertexFilter.min = 2
process.VertexFilter.max = 9999
