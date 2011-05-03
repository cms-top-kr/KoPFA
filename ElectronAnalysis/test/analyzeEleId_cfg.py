import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeEleId_default.root')
)

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:recoPF.root',
    )
)

## User defined modules and sequences
process.genElectrons = cms.EDFilter("GenParticleSelector",
    src = cms.InputTag("genParticles"),
    cut = cms.string("abs(pdgId) == 11 && abs(eta) < 2.4"),
)

process.e = cms.EDAnalyzer("ElectronAnalyzer",
    genParticles = cms.InputTag("genElectrons"),
    electron = cms.InputTag("electronsHZZVeryLoose"),
    pfCandidate = cms.InputTag("pfElectronsID", "", "RERECOPF"),
)

process.p = cms.Path(
    process.genElectrons
  * process.e
)

