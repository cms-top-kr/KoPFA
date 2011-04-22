import FWCore.ParameterSet.Config as cms

process = cms.Process("RERECOPF")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-RECO/MC_42_V9-v1/0055/087B1717-C25E-E011-B225-00248C0BE018.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-RECO/MC_42_V9-v1/0055/C4D5AA13-AD5E-E011-89A6-001A92810AB8.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-RECO/MC_42_V9-v1/0055/E0005583-AB5E-E011-8E39-003048678BB8.root',
    ),
    secondaryFileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/02F697F7-AA5E-E011-858F-002618943854.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/2817AD81-AB5E-E011-AA06-003048678F0C.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/2A3C63C9-B35E-E011-B094-002618FDA237.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/56668601-AD5E-E011-BD2D-0026189437FE.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/5AA45C81-AB5E-E011-BDB1-003048678B38.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/6E194E0E-C25E-E011-A302-00261894389F.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/B877CE0D-AE5E-E011-8806-003048678B06.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/D630698A-AB5E-E011-901E-00261894387C.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/E05C9A81-AC5E-E011-AF94-003048678BEA.root',
        '/store/relval/CMSSW_4_2_0/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V9-v1/0055/EEBE4886-AC5E-E011-8252-001A9281172E.root',
    )
)
print process.source.fileNames

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'mc' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")

## Set output
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('rerecoPF.root'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    outputCommands = cms.untracked.vstring('drop *')
)

process.outpath = cms.EndPath(process.out)

## User defined modules and sequences
process.load("RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi")
process.eidSequence = cms.Sequence(
    process.eidLooseMC
)

process.electronsCiCLoose = cms.EDFilter("EleIdCutBasedRef",
    src = cms.InputTag("gsfElectrons"),
    algorithm = cms.string("eIDCB"),
    threshold = cms.double(1),
    electronIDType = process.eidLooseMC.electronIDType,
    electronQuality = process.eidLooseMC.electronQuality,
    electronVersion = process.eidLooseMC.electronVersion,
    additionalCategories = process.eidLooseMC.additionalCategories,
    classbasedlooseEleIDCutsV06 = process.eidLooseMC.classbasedlooseEleIDCutsV06,
    etBinning = cms.bool(False),
    version = cms.string(""),
    verticesCollection = cms.InputTag('offlinePrimaryVertices'),
    reducedBarrelRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
    reducedEndcapRecHitCollection = cms.InputTag("recucedEcalRecHitsEE"),
)

process.load("RecoParticleFlow.PFProducer.particleFlow_cfi")
process.particleFlow.useEGammaElectrons = True
process.particleFlow.egammaElectrons = cms.InputTag('electronsCiCLoose')

## Paths

process.p = cms.Path(
    process.eidSequence
  * process.electronsCiCLoose
#  * process.particleFlow
)

