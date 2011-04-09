from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.EMU.MC.Fall10.patTuple_Zee_cff")
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = cms.untracked.vint32(11,13)
process.GenZmassFilter.min = 20
process.GenZmassFilter.max = 50


