import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/data/Run2010A/Mu/RECO/v4/000/140/379/E6F46854-8592-DF11-AACD-001617C3B6CE.root', #golden event from top
        '/store/data/Run2010A/Mu/RECO/v4/000/142/136/1A788144-289E-DF11-AC2A-001D09F2960F.root', #golden event from PF
        #'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/WmunuSpring10/24BF0D12-DF46-DF11-BA71-001D0968F2F6.root'
    )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V13::All')
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

## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load("CommonTools.ParticleFlow.PF2PAT_cff")

process.pfPileUp.Enable = True #enable for test, Aug 30

#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
postfix = "PFlow"
usePF2PAT(process,runPF2PAT=True, jetAlgo='AK5', runOnMC=False, postfix=postfix)
removeMCMatching(process, ['All'] )

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

#ElectronID
#process.patElectronsPFlow.electronIDSources = cms.PSet(
#    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
#    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
#)
#
#process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")
#process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
#process.makePatElectronsPFlow = cms.Sequence(
#      process.patElectronIDs*
#      process.patElectronIsolation*
#      process.patElectronsPFlow
#)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(9999.)
#process.pfIsolatedElectronsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
#process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(9999.)

process.acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
)

#PATMUON Selector
#Here we define the muon selectors
process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.4")
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(1)
)

##################################################################
process.load("PFAnalyses.CommonTools.countingSequences_cfi")

process.outpath = cms.EndPath(process.saveHistosInRunInfo*process.out)
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring()
process.hltHighLevel.throw = cms.bool(False)
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")
#process.load("KoPFA.CommonTools.recoPFCandCountFilter_cfi")

process.p = cms.Path(
#    process.startupSequence*
    process.noscraping*
    process.primaryVertexFilter*
#    process.HBHENoiseFilter *
#    process.hltHighLevel*
    process.muonTriggerFilterByRun*
#    process.patDefaultSequence*
    getattr(process,"patPF2PATSequence"+postfix)*
#    process.acceptedElectrons*
    process.acceptedMuons*
    process.patMuonFilter
#    process.finalSequence
)

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTriggerStandAlone( process )

from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning

process.out.outputCommands.extend(cms.untracked.vstring(
#    'keep *_MEtoEDMConverter_*_PAT',
    'keep *_particleFlow_*_*',
    'keep *_acceptedMuons_*_*',
#    'keep *_acceptedElectrons_*_*',
    'drop *_selectedPatPhotons*_*_*',
    'drop *_selectedPatElectrons*_*_*',
    'keep *_selectedPatMuons*_*_*',
    'keep *_selectedPatTaus*_*_*',
    'keep *_selectedPatJets*_*_*',
    'keep *_patMETs*_*_*',
    'drop *_selectedPatPFParticles*_*_*',
    'drop *_selectedPatTrackCands*_*_*'

))

process.MessageLogger.cerr.FwkReport.reportEvery = 100
