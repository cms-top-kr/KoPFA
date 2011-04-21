from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.TopAnalyzer.Sources.MU.RD.patTuple_Run2011A_PromptReco_DoubleMu_official_muphy_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_run2011a_official.root')
)


