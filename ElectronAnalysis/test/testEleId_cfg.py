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
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-RECO/MC_42_V10-v1/0027/F0807B18-4D67-E011-8AAB-00304867BFA8.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-RECO/MC_42_V10-v1/0026/641CFA1D-D366-E011-832B-002618943980.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-RECO/MC_42_V10-v1/0026/44C50AD1-CC66-E011-8694-001A9281174A.root',
    ),
    secondaryFileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0029/7E2F3EC6-6D67-E011-9A96-0018F3D0965C.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/F20E47C0-CC66-E011-ACDB-0018F3D0962E.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/C67D109D-D466-E011-B662-003048678D6C.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/96405E32-CD66-E011-9EF0-003048678C9A.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/76F9F7B1-CA66-E011-BAD1-002618943927.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/6C02719A-D366-E011-9205-00261894385D.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/5E38332E-CE66-E011-A07A-0018F3D09636.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/562BC414-DA66-E011-AF4C-003048679168.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/2E8965BE-CC66-E011-963B-001A92971B36.root',
        '/store/relval/CMSSW_4_2_1/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_42_V10-v1/0026/14E770B1-CB66-E011-82DC-001A92810AE0.root',
    )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'mc' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")

## Set output
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('rerecoPF.root'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    outputCommands = cms.untracked.vstring(
        'drop *',
    )
)
from RecoParticleFlow.Configuration.RecoParticleFlow_EventContent_cff import *
process.out.outputCommands.extend(RecoParticleFlowRECO.outputCommands)

process.outpath = cms.EndPath(process.out)

## User defined modules and sequences
process.load("RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi")
process.eidSequence = cms.Sequence(
    process.eidLooseMC
)

process.electronsCiCLoose = cms.EDFilter("EleIdCutBased",
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

#process.load("RecoParticleFlow.PFProducer.particleFlow_cfi")
process.particleFlow.useEGammaElectrons = True
process.particleFlow.egammaElectrons = cms.InputTag('electronsCiCLoose')

## Paths

process.p = cms.Path(
    process.RawToDigi
  * process.eidSequence
  * process.electronsCiCLoose
  * process.reconstruction
)

