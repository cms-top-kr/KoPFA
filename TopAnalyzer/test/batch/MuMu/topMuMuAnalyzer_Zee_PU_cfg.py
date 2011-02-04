from KoPFA.TopAnalyzer.topMuMuAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10.patTuple_Zee_PU_cff")
process.muonTriggerFilterForMC = process.muonTriggerFilterForMCREDIGI38XPU
process.topWLeptonGenFilter.applyFilter = False
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.min = 0
process.GenZmassFilter.max = 50


