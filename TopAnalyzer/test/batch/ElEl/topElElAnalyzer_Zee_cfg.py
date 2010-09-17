from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.MC.Spring10.patTuple_Zee_cff")
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.min = 0
process.GenZmassFilter.max = 50


