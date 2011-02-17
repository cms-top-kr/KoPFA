from KoPFA.DiMuonAnalyzer.dimuonanalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010A_SingleMU_cff")

process.VertexFilter.min = 1
process.VertexFilter.max = 9999
