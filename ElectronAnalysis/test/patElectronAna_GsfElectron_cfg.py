import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("ANA")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('eleAna.root')
)

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    pickRelValInputFiles( cmsswVersion  = os.environ['CMSSW_VERSION']
                        , relVal        = 'RelValTTbar'
                        , globalTag     = process.GlobalTag.globaltag.value().split(':')[0]
                        , numberOfFiles = 1
                        )
    )
)

from KoPFA.ElectronAnalysis.Sources.patTuple_GsfElectron_cff import readFiles
process.source.fileNames = readFiles

process.eleAna = cms.EDAnalyzer("PatElectronIDAnalyzer",
    electronLabel = cms.untracked.InputTag("acceptedElectrons"),
    metLabel = cms.untracked.InputTag("patMETsPFlow"),
    idNames = cms.untracked.vstring(
        "eidVeryLooseMC", 
        "eidLooseMC", 
        "eidMediumMC", 
        "eidTightMC", 
        "eidSuperTightMC", 
        "eidHyperTight1MC",
        "simpleEleId95relIso",
        "simpleEleId90relIso",
        "simpleEleId85relIso",
        "simpleEleId80relIso",
        "simpleEleId70relIso",
        "simpleEleId60relIso",
    ),
    idMask = cms.untracked.int32(5),
)

process.p = cms.Path(
    process.eleAna
)

