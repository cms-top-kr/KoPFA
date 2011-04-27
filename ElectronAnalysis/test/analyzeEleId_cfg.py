import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeEleId.root')
)

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:rerecoPF.root',
    )
)

## User defined modules and sequences
process.e = cms.EDAnalyzer("ElectronAnalyzer",
    electron = cms.InputTag("electronsCiCLoose"),
    pfCandidate = cms.InputTag("particleFlow", "", "RERECOPF"),
)

process.p = cms.Path(
    process.e
)

