import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("ELEOPT")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_TTbarTuneZ2.root')
)

#from KoPFA.TopAnalyzer.Sources.ELE.MC.Fall11.patTuple_TTbarTuneZ2_cff import readFiles
from KoPFA.CommonTools.Sources.MC.Fall11.SingleElectron.patTuple_TTbarTuneZ2_cff import readFiles
process.load("KoPFA.CommonTools.JetEnergyScale_cfi")
process.load("KoPFA.ElectronAnalysis.electronIdMVA_cfi")
process.JetEnergyScale.globalTag = cms.untracked.string('START42_V17')

process.source = cms.Source("PoolSource",
    fileNames = readFiles 
)

process.matchedElectrons = cms.EDFilter("GenMatchedElectronSelector",
    genParticles = cms.InputTag("genParticles"),
    electrons = cms.InputTag("mvaElectrons"),
    minNumber = cms.untracked.uint32(2),
)

process.eleOpt = cms.EDAnalyzer("ElectronOptimizer",
    electronLabel = cms.InputTag("mvaElectrons"),
    metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    useEventCounter = cms.bool( True ),
    vertexLabel = cms.untracked.InputTag("goodOfflinePrimaryVertices"),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
    ),
)
process.matchedEleOpt = process.eleOpt.clone(electronLabel = cms.InputTag("matchedElectrons"))

process.patElectronFilter = cms.EDFilter("PATCandViewCountFilter",
  src = cms.InputTag('mvaElectrons'),
  minNumber = cms.uint32(2),
  maxNumber = cms.uint32(999)
)

process.p = cms.Path(
    process.JetEnergyScale+
    process.mvaElectrons+
    process.patElectronFilter+
    process.eleOpt+
    process.matchedElectrons * process.matchedEleOpt
)

