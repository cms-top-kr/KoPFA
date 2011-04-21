from KoPFA.TagProbe.tagprob_mc_cff import process

import FWCore.ParameterSet.Config as cms

process.load("KoPFA.TopAnalyzer.Sources.MU.MC.Spring11.patTuple_DYJetsToLL_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) )
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_mc.root')
)

process.tnpTree.isMC = True 
process.tnpTreeIso.isMC = True

