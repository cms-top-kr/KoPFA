import FWCore.ParameterSet.Config as cms

## Building Tag and probe electrons
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
hltHighLevel.throw = False
hltHighLevel.HLTPaths = ["HLT_Ele10_SW_L1R"]

patElectronTrigger = cms.EDProducer("PATTriggerProducer",
    processName = cms.string('HLT'),
    triggerResults = cms.InputTag( "TriggerResults" ),
    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
    onlyStandAlone = cms.bool( False ),
    addPathModuleLabels = cms.bool( False )
)

patElectronTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'selectedPatElectronsPFlow'),
    matched = cms.InputTag( "patElectronTrigger" ),
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

triggeredPatElectrons = cms.EDProducer("PATTriggerMatchElectronEmbedder",
    src = cms.InputTag('selectedPatElectronsPFlow'),
    matches = cms.VInputTag( "patElectronTriggerMatch")
)

eleTag = cms.EDProducer("KoElectronRefSelector",
    src = cms.InputTag("triggeredPatElectrons"),
    maxRelIso = cms.untracked.double(0.20),
    idValues = cms.untracked.vint32(5,7),
)

eleProbeId = cms.EDProducer("KoElectronRefSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    minPt = cms.untracked.double(20.0),
    maxRelIso = cms.untracked.double(999.0),
    idValues = cms.untracked.vint32(5,7),
)

gsfEleMva = cms.EDFilter("GsfElectronRefSelector",
    src = cms.InputTag("gsfElectrons"),
    cut = cms.string("mva > -0.1")
)

## Make pair of tag and probe
zMva = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("gsfEleMva@+ gsfElectrons@-"),
    cut = cms.string("70 < mass < 110")
)

countZMva = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("zMva"),
    minNumber = cms.uint32(1)
)

zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ selectedPatElectronsPFlow@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110")
)

zId = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ eleProbeId@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110")
)

## Tag and Probe producer
tnpMva = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zMva"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        mva = cms.string("mva"),
    ),
    flags = cms.PSet(
        Id = cms.string("mva > -0.1"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zBase"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        eleId = cms.string("electronID('simpleEleId90relIso')"),
        mva = cms.string("mva"),
        relIso = cms.string("(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt"),
    ),
    flags = cms.PSet(
        Id = cms.string("electronID('simpleEleId90relIso') == 5 || electronID('simpleEleId90relIso') == 7"),
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
        eleId = cms.string("electronID('simpleEleId90relIso')"),
        mva = cms.string("mva"),
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

eleTnPSequence = cms.Sequence(
    hltHighLevel * patElectronTrigger * patElectronTriggerMatch * triggeredPatElectrons *
    gsfEleMva * eleTag * eleProbeId *
    zMva * zBase * zId *
    countZMva *
    tnpMva * tnpId * tnpIdIso
)

