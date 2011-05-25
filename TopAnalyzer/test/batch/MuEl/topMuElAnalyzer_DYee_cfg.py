from KoPFA.TopAnalyzer.topMuElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.EMU.MC.Fall10.patTuple_DYee_cff")
process.emuTriggerFilterForMC = process.emuTriggerFilterForMCREDIGI38X

