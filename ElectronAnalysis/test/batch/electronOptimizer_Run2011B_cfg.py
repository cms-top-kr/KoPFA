import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("ELEOPT")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_Run2011B.root')
)

from KoPFA.TopAnalyzer.Sources.ELE.RD.patTuple_Run2011B_cff import readFiles
process.load("KoPFA.CommonTools.JetEnergyScale_cfi")
process.load("KoPFA.ElectronAnalysis.electronIdMVA_cfi")
process.JetEnergyScale.globalTag = cms.untracked.string('GR_R_42_V23')
process.JetEnergyScale.doResJec = cms.untracked.bool(True)

process.source = cms.Source("PoolSource",
    fileNames = readFiles 
)

process.eleOpt = cms.EDAnalyzer("ElectronOptimizer",
    electronLabel = cms.InputTag("mvaElectrons"),
    metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
    ),
)

process.patElectronFilter = cms.EDFilter("PATCandViewCountFilter",
  src = cms.InputTag('mvaElectrons'),
  minNumber = cms.uint32(2),
  maxNumber = cms.uint32(999)
)

process.p = cms.Path(
    process.JetEnergyScale+
    process.mvaElectrons+
    process.patElectronFilter+
    process.eleOpt
)

