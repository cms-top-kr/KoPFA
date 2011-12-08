from KoPFA.TagProbe.tagprob_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.TagProbe.Sources.MU.RD.patTuple_Run2011B_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_Run2011B.root')
)


