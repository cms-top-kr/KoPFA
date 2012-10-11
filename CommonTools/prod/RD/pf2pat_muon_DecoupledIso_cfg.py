import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.patTemplate_cfg import *
from KoPFA.CommonTools.pf2pat_template_cfg import *
from KoPFA.CommonTools.eventContent_cff import *
from KoPFA.CommonTools.tools import *

postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=False, postfix=postfix)

#change cone size
changeConeSize(process,postfix)

#FastJet!
applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

# output
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.patMuonFilter.minNumber = 0 
process.patMuonFilter.src = cms.InputTag('acceptedMuons') 
process.patMuonFilter.minNumber = 2 

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
  '/store/data/Run2011B/SingleMu/AOD/PromptReco-v1/000/175/990/DC97D958-07DE-E011-857A-001D09F232B9.root',
  '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/180/252/08D65FBF-0B05-E111-83AA-003048D2C0F0.root',
  '/store/data/Run2011A/DoubleMu/AOD/PromptReco-v1/000/161/312/0E8D9A70-E857-E011-B3DC-001D09F29321.root',
  '/store/data/Run2011A/MuEG/AOD/PromptReco-v1/000/161/312/04850A2C-F757-E011-9A74-003048F024DC.root'
  )
)

# remove MC matching from the default sequence
removeMCMatching(process, ['All'])

process.patMuonTrigger = cms.EDProducer("PATTriggerProducer",
    processName = cms.string('HLT'),
    triggerResults = cms.InputTag( "TriggerResults" ),
    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
    onlyStandAlone = cms.bool( False ),
    addPathModuleLabels = cms.bool( False )
)

process.patMuonTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'acceptedMuons'),
    matched = cms.InputTag( "patMuonTrigger" ),
    andOr = cms.bool( False ),
    filterIdsEnum = cms.vstring( '*' ),
    filterIds = cms.vint32( 0 ),
    filterLabels = cms.vstring( '*' ),
    matchedCuts = cms.string( ""),
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.2 ),
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( False )
)

process.triggeredMuons = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag('acceptedMuons'),
    matches = cms.VInputTag( "patMuonTriggerMatch")
)

process.p += process.hltHighLevelElHadRD
process.p += process.nEventsHLT
process.p += process.patDefaultSequence
#process.p += process.acceptedGsfElectrons
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
process.p += process.acceptedElectrons
process.p += process.acceptedMuons
process.p += process.patMuonFilter
process.p += process.patMuonFilter
process.p += process.nEventsFiltered
#trigger embedded 
process.p += process.patMuonTrigger
process.p += process.patMuonTriggerMatch
process.p += process.triggeredMuons

process.out.outputCommands +=[
        'keep *_acceptedMuons_*_*',
        'keep *_triggeredMuons_*_*',
]
