import FWCore.ParameterSet.Config as cms
import sys, os

process = cms.Process("USER")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:E87AF0D3-4C4D-E211-95FA-003048D37694.root',
    )
)

### Rebuild HepMC
process.load("Configuration.StandardSequences.Services_cff")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')
process.generatorConverter = process.generator.clone()
process.load("Configuration.Generator.Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_tauola_cff")
process.load("Configuration.StandardSequences.Generator_cff")

process.hepmc2hepmcValidator = cms.EDFilter("HepMC2HepMCValidator",
    verbose = cms.untracked.bool(False),
    asciiFilePrefix = cms.untracked.string('hepmc'),
    genEvent1 = cms.InputTag("generator"),
    genEvent2 = cms.InputTag("generatorConverter"),
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("badEvents.root"),
    outputCommands = cms.untracked.vstring(
        "keep *",
        "drop *_*_*_USER",
        "keep *_generator_*_*",
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p'),
    ),
)

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
    #src = cms.InputTag("genParticlesPruned"),
    src = cms.InputTag("genParticles"),
    maxEventsToPrint  = cms.untracked.int32(1)
)

process.genParticlesFromConverter = process.genParticles.clone(
    src = cms.InputTag("generatorConverter")
)
process.printTreeFromConverter = process.printTree.clone(
    src = cms.InputTag("genParticlesFromConverter"),
)

process.p = cms.Path(
    process.generator * process.genParticles
  * process.generatorConverter
  * process.genParticlesFromConverter
  * process.hepmc2hepmcValidator
  * process.printTree + process.printTreeFromConverter
)

process.outPath = cms.EndPath(process.out)
