import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    pickRelValInputFiles( cmsswVersion  = 'CMSSW_4_1_2'
                        , relVal        = 'RelValTTbar'
                        , globalTag     = 'START311_V2'
                        , numberOfFiles = 1
                        )
    )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string('START38_V13::All')
from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")

## Output Module Configuration (expects a path 'p')
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('patTuple_skim.root'),
    # save only events passing the full path
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    # save PAT Layer 1 output; you need a '*' to
    # unpack the list of commands 'patEventContent'
    outputCommands = cms.untracked.vstring('drop *')
)

#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *

#postfix = "PFlow"
#jetAlgo="AK5"
#runOnMC=False
#usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix)
#removeMCMatching(process, ['All'] )

process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.noscraping = cms.EDFilter("FilterOutScraping",
   applyfilter = cms.untracked.bool(True),
   debugOn = cms.untracked.bool(False),
   numtrack = cms.untracked.uint32(10),
   thresh = cms.untracked.double(0.25)
)

process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')

#Electron ID
process.load('RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi')
process.patElectrons.electronIDSources = cms.PSet(
    eidVeryLoose = cms.InputTag("eidVeryLoose"),
    eidLoose = cms.InputTag("eidLoose"),
    eidMedium = cms.InputTag("eidMedium"),
    eidTight = cms.InputTag("eidTight"),
    eidSuperTight = cms.InputTag("eidSuperTight"),
    eidHyperTight1 = cms.InputTag("eidHyperTight")
)

#REMOVE ISOLATION FROM PF2PAT!!!
#process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(999)
#process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(999)

##################################################################
process.load("PFAnalyses.CommonTools.countingSequences_cfi")

process.outpath = cms.EndPath(process.saveHistosInRunInfo*process.out)
#process.load("KoPFA.CommonTools.recoPFCandCountFilter_cfi")

process.p = cms.Path(
#    process.startupSequence*
    process.noscraping*
    process.primaryVertexFilter
#    process.HBHENoiseFilter *
  * process.eidVeryLoose * process.eidLoose * process.eidMedium
  * process.eidTight * process.eidSuperTight * process.eidHyperTight1
)

# top projections in PF2PAT:
#getattr(process,"pfNoPileUp"+postfix).enable = True
#getattr(process,"pfNoMuon"+postfix).enable = True
#getattr(process,"pfNoElectron"+postfix).enable = True
#getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
#getattr(process,"pfNoJet"+postfix).enable = True

from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning

process.out.outputCommands.extend(cms.untracked.vstring(
    'keep *_MEtoEDMConverter_*_PAT',
    'keep *_particleFlow_*_*',
    'keep *_acceptedMuons_*_*',
    'keep *_acceptedElectrons_*_*',
))
