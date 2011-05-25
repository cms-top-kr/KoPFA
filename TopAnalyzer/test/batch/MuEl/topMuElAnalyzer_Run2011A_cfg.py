import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_run2011a.root')
)

process.load("KoPFA.TopAnalyzer.Sources.EMU.RD.patTuple_Run2011A_PromptReco_EMu_cff")

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.p = cms.Path(
    process.topMuElAnalysisRealDataSequence
)

