import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

## Include ##
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
process.load("PFAnalyses.TTbarDIL.Sources.ELE.MC.Fall10.patTuple_ZJets50_cff")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )    

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_ZJets50.root")
)

process.load("KoPFA.TagProbe.Electron_TnP_Producer_cff")

process.p = cms.Path(
    process.eleTnPSequence
)

