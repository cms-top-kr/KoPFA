from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Spring10.patTuple_ZJets_cff")
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = cms.untracked.vint32(15)
process.GenZmassFilter.min = 50
process.GenZmassFilter.max = 999


