import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

## Source
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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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

process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
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

process.acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsLoosePFlow"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
    filter = cms.bool(False),
)

process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('acceptedElectrons'),
    minNumber = cms.uint32(2)
)

process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsLoosePFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5"),
    filter = cms.bool(False),
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(2)
)

#Electron ID
process.load('RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi')
process.patElectrons.electronIDSources = cms.PSet(
    eidVeryLooseMC = cms.InputTag("eidVeryLooseMC"),
    eidLooseMC = cms.InputTag("eidLooseMC"),
    eidMediumMC = cms.InputTag("eidMediumMC"),
    eidTightMC = cms.InputTag("eidTightMC"),
    eidSuperTightMC = cms.InputTag("eidSuperTightMC"),
    eidHyperTight1MC = cms.InputTag("eidHyperTight1MC")
)

process.eidCiCSequence = cms.Sequence(
    process.eidVeryLooseMC * process.eidLooseMC * process.eidMediumMC
  * process.eidTightMC * process.eidSuperTightMC * process.eidHyperTight1MC
)

process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')
process.HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(9999)
process.HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(9999)
process.HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(9999)


##################################################################
process.load("KoPFA.TopAnalyzer.topHLTfilter_cff")

process.nEventsTotal = cms.EDProducer("EventCountProducer")
process.nEventsClean = cms.EDProducer("EventCountProducer")
process.nEventsHLT = cms.EDProducer("EventCountProducer")
process.nEventsFiltered = cms.EDProducer("EventCountProducer")

process.outpath = cms.EndPath(process.out)
#process.load("KoPFA.CommonTools.recoPFCandCountFilter_cfi")

process.p = cms.Path(
    process.nEventsTotal*
    process.noscraping*
    process.goodOfflinePrimaryVertices*
    process.HBHENoiseFilter *
    process.nEventsClean* 
    process.eidCiCSequence
)

