from KoPFA.IsoAnalyzer.MuonIsoAna_cff import process

import FWCore.ParameterSet.Config as cms

#process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010A_SingleMU_cff")
#process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_SingleMU_cff")
process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_TightMU_cff")

process.hltHighLevel.HLTPaths = cms.vstring("HLT_Mu9","HLT_Mu11","HLT_Mu15_v1")
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")

process.TFileService.fileName = cms.string('vallot_data_1.root')



