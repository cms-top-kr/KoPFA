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
#'/store/data/Run2010A/Mu/RECO/v4/000/142/136/1A788144-289E-DF11-AC2A-001D09F2960F.root', #golden event from PF
#'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_8_0_pre8/RelValTTbar/GEN-SIM-RECO/START38_V6-v1/0004/847D00B0-608E-DF11-A37D-003048678FA0.root'
#'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/WmunuSpring10/24BF0D12-DF46-DF11-BA71-001D0968F2F6.root'
)


)

process.load("KoPFA.TopAnalyzer.Sources.Fall10_ZJets_reco_cff")
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
#process.load("PhysicsTools.PFCandProducer.PF2PAT_cff") # for CMSSW_3_8_X
process.load("CommonTools.ParticleFlow.PF2PAT_cff") # for CMSSW_4_2_X

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

process.patJets.addTagInfos = False
process.patJetsPFlow.addTagInfos = False

#ElectronID
process.patElectronsPFlow.electronIDSources = cms.PSet(
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
)
#
process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")
process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
process.makePatElectronsPFlow = cms.Sequence(
      process.patElectronIDs*
      process.patElectronIsolation*
      process.patElectronsPFlow
)

process.patElectrons.electronIDSources = cms.PSet(
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
)
#
process.makePatElectrons = cms.Sequence(
      process.patElectronIDs*
      process.patElectronIsolation*
      process.patElectrons
)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(9999.)
process.pfIsolatedElectronsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(9999.)

process.pfSelectedElectronsPFlow.cut = cms.string("pt>20 && gsfTrackRef.isNonnull && gsfTrackRef.trackerExpectedHitsInner.numberOfHits<2") 
#Removing the taus from the PF2PAT list
#process.pfTausPFlow.discriminators = cms.VPSet( 
#    cms.PSet( discriminator=cms.InputTag("pfTausBaseDiscriminationByLeadingPionPtCutPFlow"),
#    selectionCut=cms.double(10.) ),
#    )

process.pfElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('pfSelectedElectronsPFlow'),
  #src = cms.InputTag('particleFlowElectronsPtGt20'),
  minNumber = cms.uint32(0)
)

process.pfElectronSequencePFlow = cms.Sequence(
    process.pfAllElectronsPFlow +
    # electron selection:
    #pfElectronsPtGt5 +
    process.pfElectronsFromVertexPFlow +
    process.pfSelectedElectronsPFlow +
    process.pfElectronFilter+
    # computing isolation variables:
    process.pfElectronIsolationSequencePFlow +
    # selecting isolated electrons:
    process.pfIsolatedElectronsPFlow
    )


process.particleFlowElectrons = cms.EDFilter("PdgIdPFCandidateSelector",
    src = cms.InputTag("particleFlow"),
    pdgId = cms.vint32(11,-11)
)

process.particleFlowElectronsPtGt20 = cms.EDFilter("PtMinPFCandidateSelector",
    src = cms.InputTag("particleFlowElectrons"),
    ptMin = cms.double(20.0)
)

#PATMUON Selector
#Here we define the muon selectors
process.acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut =cms.string("pfCandidateRef.p4.pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
)

process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedElectrons'),
  minNumber = cms.uint32(0)
)

process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5")
)

##################################################################
process.load("PFAnalyses.CommonTools.countingSequences_cfi")

process.outpath = cms.EndPath(process.saveHistosInRunInfo*process.out)
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring()
process.hltHighLevel.throw = cms.bool(False)
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")

process.p = cms.Path(
#                 process.startupSequence*
                 process.noscraping*
                 process.primaryVertexFilter*
#                 process.hltHighLevel*
#                 process.electronTriggerFilterByRun*
                 process.patDefaultSequence*
                 getattr(process,"patPF2PATSequence"+postfix)*
                 process.acceptedMuons*
                 process.acceptedElectrons
#                 process.patElectronFilter*
#                 process.finalSequence
    )

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTriggerStandAlone( process )

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

process.MessageLogger.cerr.FwkReport.reportEvery = 100
