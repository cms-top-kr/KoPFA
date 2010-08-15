from KoPFA.DiMuonAnalyzer.dimuonanalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Commissioning10_cff")

process.VertexFilter.min = 1
process.VertexFilter.max = 1
