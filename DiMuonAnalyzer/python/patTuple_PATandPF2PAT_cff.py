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

# load the PAT config
process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.patJets.addTagInfos     = cms.bool(False)

# Configure PAT to use PF2PAT instead of AOD sources
# this function will modify the PAT sequences. It is currently 
# not possible to run PF2PAT+PAT and standart PAT at the same time
from PhysicsTools.PatAlgos.tools.pfTools import *

process.pfPileUp.Enable = True #enable

# An empty postfix means that only PF2PAT is run,
# otherwise both standard PAT and PF2PAT are run. In the latter case PF2PAT
# collections have standard names + postfix (e.g. patElectronPFlow)  
postfix = "PFlow"
usePF2PAT(process,runPF2PAT=True, jetAlgo='AK5', runOnMC=False, postfix=postfix) 
removeMCMatching(process, ['All'] )
# turn to false when running on data
#getattr(process, "patElectrons"+postfix).embedGenMatch = False
#getattr(process, "patMuons"+postfix).embedGenMatch = False

#to include particle-based isolation to reco muon
from CommonTools.ParticleFlow.Isolation.tools_cfi import *  # for 4_2_x version
#from PhysicsTools.PFCandProducer.Isolation.tools_cfi import * # for 3_8_x version

process.isoDepMuonWithCharged   = isoDepositReplace( 'muons', 'pfAllChargedHadronsPFlow' )
process.isoDepMuonWithNeutral   = isoDepositReplace( 'muons', 'pfAllNeutralHadronsPFlow' )
process.isoDepMuonWithPhotons   = isoDepositReplace( 'muons', 'pfAllPhotonsPFlow' )

process.isoValMuonWithCharged = cms.EDProducer("CandIsolatorFromDeposits",
    deposits = cms.VPSet(cms.PSet(
        src = cms.InputTag("isoDepMuonWithCharged"),
        deltaR = cms.double(0.4),
        weight = cms.string('1'),
        vetos = cms.vstring(),
        skipDefaultVeto = cms.bool(True),
        mode = cms.string('sum')
    ))
)

process.isoValMuonWithNeutral = cms.EDProducer("CandIsolatorFromDeposits",
    deposits = cms.VPSet(cms.PSet(
        src = cms.InputTag("isoDepMuonWithNeutral"),
        deltaR = cms.double(0.4),
        weight = cms.string('1'),
        vetos = cms.vstring('Threshold(0.5)'),
        skipDefaultVeto = cms.bool(True),
        mode = cms.string('sum')
    ))
)

process.isoValMuonWithPhotons = cms.EDProducer("CandIsolatorFromDeposits",
    deposits = cms.VPSet(cms.PSet(
        src = cms.InputTag("isoDepMuonWithPhotons"),
        deltaR = cms.double(0.4),
        weight = cms.string('1'),
        vetos = cms.vstring('Threshold(0.5)'),
        skipDefaultVeto = cms.bool(True),
        mode = cms.string('sum')
    ))
)

process.patMuons.isoDeposits = cms.PSet(
       pfNeutralHadrons = cms.InputTag("isoDepMuonWithNeutral"),
       pfChargedHadrons = cms.InputTag("isoDepMuonWithCharged"),
       pfPhotons = cms.InputTag("isoDepMuonWithPhotons")
)

process.patMuons.isolationValues = cms.PSet(
       pfNeutralHadrons = cms.InputTag("isoValMuonWithNeutral"),
       pfChargedHadrons = cms.InputTag("isoValMuonWithCharged"),
       pfPhotons = cms.InputTag("isoValMuonWithPhotons")
)

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

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(9999.)
process.pfIsolatedElectronsPFlow.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(9999.)

#PATMUON Selector
#Here we define the muon selectors
process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuons"),
    cut =cms.string("isGlobalMuon && pt > 20 && abs(eta) < 2.4 && globalTrack.normalizedChi2 < 10.0 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0 && innerTrack.hitPattern.numberOfValidTrackerHits > 10 && numberOfMatchedStations() > 1")
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(1)
)

# Let it run
process.p = cms.Path(
    process.noscraping*
    process.primaryVertexFilter*
    getattr(process,"patPF2PATSequence"+postfix)*
    process.isoDepMuonWithCharged*
    process.isoDepMuonWithNeutral*
    process.isoDepMuonWithPhotons*   
    process.isoValMuonWithNeutral*
    process.isoValMuonWithCharged*
    process.isoValMuonWithPhotons*
    process.patDefaultSequence*
    process.acceptedMuons*
    process.patMuonFilter
)

process.outpath = cms.EndPath(process.out)

# Add PF2PAT output to the created file
from PhysicsTools.PatAlgos.patEventContent_cff import * 
#process.load("PhysicsTools.PFCandProducer.PF2PAT_EventContent_cff")
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands.extend(cms.untracked.vstring(
    'keep *_acceptedMuons_*_*',
    'keep *_particleFlow_*_*',
))


process.MessageLogger.cerr.FwkReport.reportEvery = 100
