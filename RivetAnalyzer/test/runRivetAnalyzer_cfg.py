import FWCore.ParameterSet.Config as cms
import sys, os

process = cms.Process("RIVET")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(),
)

### Rebuild HepMC
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

process.p = cms.Path(process.rivetAnalyzer)
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection = cms.double(13.43)
#process.rivetAnalyzer.CrossSection = cms.double(165)
process.rivetAnalyzer.OutputFile = 'rivet.aida'

process.p = cms.Path(process.generator * process.rivetAnalyzer)

