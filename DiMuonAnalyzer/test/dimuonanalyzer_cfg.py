from KoPFA.DiMuonAnalyzer.dimuonanalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.VertexFilter.min = 1
process.VertexFilter.max = 9999
