from KoPFA.TopAnalyzer.topMuMuAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010B_Nov4ReReco_cff")
process.muonTriggerFilterForMC.filter = False
process.topWLeptonGenFilter.applyFilter = False
