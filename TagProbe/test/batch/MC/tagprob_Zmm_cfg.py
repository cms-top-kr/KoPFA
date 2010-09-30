from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Spring10.patTuple_Zmumu_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) )
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_mc.root')
)


