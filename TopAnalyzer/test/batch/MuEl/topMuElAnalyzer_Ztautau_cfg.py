from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.EMU.MC.Fall10.patTuple_Ztautau_cff")
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.min = 0
process.GenZmassFilter.max = 50


