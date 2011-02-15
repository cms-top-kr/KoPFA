from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_Nov4ReReco_SingleMU_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_1.root')
)


