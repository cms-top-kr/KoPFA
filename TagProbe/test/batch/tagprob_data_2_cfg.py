from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010A_Jun14thReReco_cff")
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_2.root')
)


