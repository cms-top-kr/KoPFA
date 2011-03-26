from KoPFA.TagProbe.tagprob_tightmu_cff import process

import FWCore.ParameterSet.Config as cms

#process.load("KoPFA.DiMuonAnalyzer.MC.Fall10_Single_MUSKIM.patTuple_Zmm_cff")
#process.load("KoPFA.DiMuonAnalyzer.MC.Fall10_Single_MUSKIM.patTuple_ZmmPU_cff")
process.load("KoPFA.DiMuonAnalyzer.MC.Fall10_Single_MUSKIM.patTuple_ZmmPU_TightMU_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(35000) )
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob_mcPU.root')
)


