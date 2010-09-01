import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/data/Run2010A/Mu/RECO/v4/000/140/379/E6F46854-8592-DF11-AACD-001617C3B6CE.root',
#'/store/data/Run2010A/Mu/RECO/v4/000/140/379/DADA85C0-8692-DF11-B916-0030486733D8.root',
#'/store/data/Run2010A/Mu/RECO/v4/000/140/379/D659EFB7-AF92-DF11-96BD-00304879FC6C.root',
#'/store/data/Run2010A/Mu/RECO/v4/000/140/379/44E5E31D-8492-DF11-AA30-001D09F253C0.root'
  )

)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START36_V4::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

## Output Module Configuration (expects a path 'p')
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple_muon.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('drop *')
                               )

## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load("PhysicsTools.PFCandProducer.PF2PAT_cff")

#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
postfix = "PFlow"
usePF2PAT(process,runPF2PAT=True, jetAlgo='AK5', runOnMC=False, postfix=postfix)
removeMCMatching(process, ['All'] )

process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.noscraping = cms.EDFilter("FilterOutScraping",
   applyfilter = cms.untracked.bool(True),
   debugOn = cms.untracked.bool(False),
   numtrack = cms.untracked.uint32(10),
   thresh = cms.untracked.double(0.25)
)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(9999.)

#PATMUON Selector
#Here we define the muon selectors
from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
muonSelector = muonSelectorPSet.clone()
  
process.Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 1 ),#PF
    muonLabel  = cms.InputTag("selectedPatMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(0)
)

process.PFMuons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 1 ),#PF
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonSelectorPSet,
)

process.patPFMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('PFMuons'),
  minNumber = cms.uint32(0)
)

 
##################################################################
process.load("PFAnalyses.CommonTools.countingSequences_cfi")
process.load("KoPFA.DiMuonAnalyzer.triggerMatch_cfi" )

#process.outpath = cms.EndPath(process.saveHistosInRunInfo*process.out)

from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning

process.out.outputCommands.extend(cms.untracked.vstring(
                                                    'keep *_MEtoEDMConverter_*_PAT',
                                                    'keep *_particleFlow_*_*',
                                                    'keep *_triggeredPatMuons_*_*',
                                                ))

process.p = cms.Path(
                 process.primaryVertexFilter*
                 process.noscraping*
                 process.startupSequence*
                 process.patDefaultSequence*
                 getattr(process,"patPF2PATSequence"+postfix)*
                 process.triggerMatch*
                 process.patMuonFilter*
                 process.finalSequence
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.load("KoPFA.CommonTools.MuonSelector_cfi")
from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False


process.DiMuonPFlow = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('PFMuons'),
  metLabel =  cms.InputTag('patMETsPFlow'),
  jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),
  looseJetId = myJetId,
)

process.DiMuon = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('Muons'),
  metLabel =  cms.InputTag('patMETsPFlow'),
  jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),
  looseJetId = myJetId,
)

process.DiMuonAnalPFlow = cms.Path(
                              process.primaryVertexFilter
                             +process.noscraping
                             +process.startupSequence
                             +process.patDefaultSequence
                             +getattr(process,"patPF2PATSequence"+postfix)
                             +process.PFMuons
                             +process.patPFMuonFilter
                             +process.finalSequence
                             +process.loadHistosFromRunInfo
                             +process.DiMuonPFlow
                             )

process.DiMuonAnal = cms.Path(
                              process.primaryVertexFilter
                             +process.noscraping
                             +process.startupSequence
                             +process.patDefaultSequence
                             +getattr(process,"patPF2PATSequence"+postfix)
                             +process.Muons
                             +process.patMuonFilter
                             +process.finalSequence
                             +process.loadHistosFromRunInfo
                             +process.DiMuon
                             )

process.schedule = cms.Schedule(
                                process.DiMuonAnal,
                                process.DiMuonAnalPFlow,
#                                process.outpath
                               )

process.MessageLogger.cerr.FwkReport.reportEvery = 100
