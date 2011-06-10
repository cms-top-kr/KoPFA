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

from KoPFA.TopAnalyzer.Sources.ELE.MC.Spring11.patTuple_TTbarTuneZ2_cff import readFiles
process.source.fileNames = readFiles

process.eleAna = cms.EDAnalyzer("KoPatElectronAnalyzer",
    electronLabel = cms.untracked.InputTag("selectedPatElectronsLoosePFlow"),
    idNames = cms.untracked.vstring(
        "eidVeryLooseMC", 
        "eidLooseMC", 
        "eidMediumMC", 
        "eidTightMC", 
        "eidSuperTightMC", 
        "eidHyperTight1MC"
    ),
    idMask = cms.untracked.int32(5),
)

process.p = cms.Path(
    process.eleAna
)

