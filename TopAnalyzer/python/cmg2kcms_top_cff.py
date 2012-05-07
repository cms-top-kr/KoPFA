import FWCore.ParameterSet.Config as cms

from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from KoPFA.TopAnalyzer.topHLTfilter_cff import *
from KoPFA.CommonTools.EventWeightProducer_cfi import *
from KoPFA.CommonTools.JetEnergyScale_cfi import *

JetEnergyScale.rhoLabel = cms.InputTag('kt6PFJets','rho')
JetEnergyScale.jetLabel = cms.InputTag('selectedPatJetsCHS')
JetEnergyScale.metLabel = cms.InputTag('patMETs')

from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from KoPFA.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose = False
muonId.dxy = 0.02
muonId.eta = 2.4
muonId.pt = 20

Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( -1 ),# dxy, pt, eta
    cut = cms.vstring("pt","eta","dxy","TOPDIL"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("patMuonsWithTrigger"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,
)

Electrons = cms.EDProducer(
    "KoElectronSelector",
    usepflow = cms.untracked.bool( False ),
    ptcut = cms.untracked.double( 20 ),
    etacut = cms.untracked.double( 2.4 ),
    mvacut = cms.untracked.double( -0.1 ),
    usemva = cms.untracked.bool( True ),
    electronLabel  = cms.InputTag("patElectronsWithTrigger"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    eidName = cms.untracked.string("eidTight"),
    eidBitMask = cms.untracked.int32(5), # = 101, ID and cms.Conversion
)

GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(11, 13, 15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

topWLeptonGenFilter = cms.EDFilter("GenParticleDecayFilter",
    applyFilter = cms.untracked.bool( False ),
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(11, 13), #remove tau decay from signal
    minCount = cms.untracked.uint32(2),
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Muons'),
    minNumber = cms.uint32(2)
)

patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Electrons'),
    minNumber = cms.uint32(2)
)

patMuonFilterForMuEl = patMuonFilter.clone()
patElectronFilterForMuEl = patElectronFilter.clone()
patMuonFilterForMuEl.minNumber = 1
patElectronFilterForMuEl.minNumber = 1

bTagSets = cms.untracked.VPSet(
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVL"),
        cutValue = cms.untracked.double(0.244),
        isCutMin = cms.untracked.bool(True),
    ),
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVM"),
        cutValue = cms.untracked.double(0.679),
        isCutMin = cms.untracked.bool(True),
    ),
    cms.untracked.PSet(
        algo = cms.untracked.string("combinedSecondaryVertexBJetTags"),
        name = cms.untracked.string("CSVT"),
        cutValue = cms.untracked.double(0.898),
        isCutMin = cms.untracked.bool(True),
    ),
)

ElEl = cms.EDFilter('TopElElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    genJetsLabel = cms.InputTag('ak5GenJets'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETs'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'prePathCounter',
        'postPathCounter',
        'nEventsPatHLT'
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.17),
    relIso2 = cms.untracked.double(0.17),
    bTagSets = bTagSets,
)

MuMu = cms.EDFilter('TopMuMuAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    genJetsLabel = cms.InputTag('ak5GenJets'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETs'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'prePathCounter',
        'postPathCounter',
        'nEventsPatHLT'
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    bTagSets = bTagSets,
)

MuEl = cms.EDFilter('TopMuElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    genJetsLabel = cms.InputTag('ak5GenJets'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETs'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'prePathCounter',
        'postPathCounter',
        'nEventsPatHLT'
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.17),
    bTagSets = bTagSets,
)

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

nEventsPatHLT = cms.EDProducer("EventCountProducer")

topElElAnalysisMCSequence = cms.Sequence(
    hltHighLevelElElMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
    PUweight*
    Electrons*
    patElectronFilter*
    JetEnergyScale*
    ElEl
)

topElElAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelElElRD*
    nEventsPatHLT*
    removeDuplicate*
    Electrons*
    patElectronFilter*
    JetEnergyScale*
    ElEl
)

topMuMuAnalysisMCSequence = cms.Sequence(
    hltHighLevelMuMuMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
    PUweight*
    Muons*
    patMuonFilter*
    JetEnergyScale*
    MuMu
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelMuMuRD*
    nEventsPatHLT*
    removeDuplicate*
    Muons*
    patMuonFilter*
    JetEnergyScale*
    MuMu
)

topMuElAnalysisMCSequence = cms.Sequence(
    hltHighLevelMuElMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
    PUweight*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    JetEnergyScale*
    MuEl
)

topMuElAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelMuElRD*
    nEventsPatHLT*
    removeDuplicate*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    JetEnergyScale*
    MuEl
)

