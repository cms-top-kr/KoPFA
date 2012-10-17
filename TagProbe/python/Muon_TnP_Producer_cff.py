import FWCore.ParameterSet.Config as cms

## Building Tag and probe muctrons
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
hltHighLevel.throw = False
hltHighLevel.HLTPaths = ["HLT_IsoMu24"]

patMuonTrigger = cms.EDProducer("PATTriggerProducer",
    processName = cms.string('HLT'),
    triggerResults = cms.InputTag( "TriggerResults" ),
    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
    onlyStandAlone = cms.bool( False ),
    addPathModuleLabels = cms.bool( False )
)

patMuonTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'selectedPatMuonsPFlow'),
    matched = cms.InputTag( "patMuonTrigger" ),
    andOr = cms.bool( False ),
    filterIdsEnum = cms.vstring( '*' ),
    filterIds = cms.vint32( 0 ),
    filterLabels = cms.vstring( '*' ),
    pathNames = hltHighLevel.HLTPaths,
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.2 ),
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( False )
)

triggeredPatMuons = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag('selectedPatMuonsPFlow'),
    matches = cms.VInputTag( "patMuonTriggerMatch")
)

muTag = cms.EDProducer("KoMuonRefSelector",
    src = cms.InputTag("triggeredPatMuons"),
    maxRelIso = cms.untracked.double(0.20),
	muId = cms.string("isPFMuon && ( isGlobalMuon || isTrackerMuon )"),
)

muProbeId = cms.EDProducer("KoMuonRefSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    minPt = cms.untracked.double(20.0),
    maxRelIso = cms.untracked.double(999.0),
	muId = cms.string("isPFMuon && ( isGlobalMuon || isTrackerMuon )"),
)

## Make pair of tag and probe
zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ selectedPatMuonsPFlow@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110")
)

zId = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muProbeId@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110")
)

## Tag and Probe producer
tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zBase"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        muId = cms.string("isPFMuon && isGlobalMuon"),
        relIso = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt"),
    ),
    flags = cms.PSet(
        Id = cms.string("isPFMuon && isGlobalMuon"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

tnpIdIso = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zId"),
    arbitration = cms.string("OneProbe"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        muId = cms.string("isPFMuon && isGlobalMuon"),
        relIso = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt"),
    ),
    flags = cms.PSet(
        IdIso20 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.20"),
        IdIso22 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.22"),
        IdIso24 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.24"),
        IdIso26 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.26"),
        IdIso30 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.30"),
        IdIso50 = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.50"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

muTnPSequence = cms.Sequence(
    hltHighLevel * patMuonTrigger * patMuonTriggerMatch * triggeredPatMuons *
    muTag * muProbeId *
    zBase * zId *
    tnpId * tnpIdIso
)

