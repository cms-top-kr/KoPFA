from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

#process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010B_SingleMU_cff")
process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010B_SingleMU_cff")
#process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010B_SingleMU_DisableNoPileUp_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_2.root')
    #fileName = cms.string('tagprob_2_DisableNoPileUp.root')
)


