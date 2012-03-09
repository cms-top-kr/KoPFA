import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.countingSequences_cfi import *
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from KoPFA.TopAnalyzer.topLeptonSelector_cfi import *
from KoPFA.TopAnalyzer.triggerFilterByRun_cfi import *
from KoPFA.TopAnalyzer.topHLTfilter_cff import *
from KoPFA.CommonTools.PileUpWeight_cff import *
from KoPFA.CommonTools.JetEnergyScale_cfi import *

VertexFilter = cms.EDFilter('VertexFilter',
    vertexLabel =  cms.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.int32(1),
    max = cms.untracked.int32(999),
)

GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(11, 13, 15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

GenWtransversemassFilter = cms.EDFilter('GenWtransversemassFilter',
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
    daughterPdgIds = cms.untracked.vuint32(11, 13, 15),
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

patMuonFilterForMuJet = patMuonFilter.clone()
patMuonFilterForMuJet.minNumber = 1
patElectronFilterForElJet = patElectronFilter.clone()
patElectronFilterForElJet.minNumber = 1

topWLeptonGenFilterForLJ = topWLeptonGenFilter.clone()
topWLeptonGenFilterForLJ.daughterPdgIds = 11,13
topWLeptonGenFilterForLJ.minCount = 1

DYmmFilter = cms.EDFilter("ZmmFilter",
  muonLabel1 =  cms.InputTag('acceptedMuons'),
  muonLabel2 =  cms.InputTag('acceptedMuons'),
  min = cms.double(12),
  max = cms.double(99999),
)

#correctedPatJetsPFlow = cms.EDProducer('KoCorrectJetProducer',
#    src = cms.InputTag('selectedPatJetsPFlow'),
#    correctors = cms.vstring('ak5PFL2L3')
#)

bTagSets = cms.untracked.VPSet(
    cms.untracked.PSet(
        algo = cms.untracked.string("trackCountingHighEffBJetTags"),
        name = cms.untracked.string("TCHEL"),
        cutValue = cms.untracked.double(1.7),
        isCutMin = cms.untracked.bool(True),
    ),
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
    cms.untracked.PSet(
        algo = cms.untracked.string("simpleSecondaryVertexHighEffBJetTags"),
        name = cms.untracked.string("SSVHEM"),
        cutValue = cms.untracked.double(1.74),
        isCutMin = cms.untracked.bool(True),
    ),
)

ElEl = cms.EDFilter('TopElElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    relIso1 = cms.untracked.double(0.17),
    relIso2 = cms.untracked.double(0.17),
    bTagSets = bTagSets,
    PileUpRD = PileUpRD2011,
    PileUpMC = Fall11,
)

MuMu = cms.EDFilter('TopMuMuAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    bTagSets = bTagSets,
    PileUpRD = PileUpRD2011,
    PileUpMC = Fall11,
)

MuEl = cms.EDFilter('TopMuElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.17),
    bTagSets = bTagSets,
    PileUpRD = PileUpRD2011,
    PileUpMC = Fall11,
)

MuJet = cms.EDFilter('TopMuJetAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso = cms.untracked.double(0.20),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
    PileUpRD = PileUpRD2011,
    PileUpMC = PoissonOneXDist,#Summer11 PU_S4 in-time
    #PileUpMC = Fall2011_InTime,#Fall11 PU_S6 in-time
)

ElJet = cms.EDFilter('TopElJetAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso = cms.untracked.double(0.17),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
    PileUpRD = PileUpRD2011,
    PileUpMC = PoissonOneXDist,#Summer11 PU_S4 in-time
    #PileUpMC = Fall2011_InTime,#Fall11 PU_S6 in-time
)

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

ElectronAna = cms.EDAnalyzer(
    "pfElectronAnalyzer",
    ptcut = cms.untracked.double(20),
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
)

nEventsPatHLT = cms.EDProducer("EventCountProducer")

topElElAnalysisMCSequence = cms.Sequence(
    hltHighLevelElElMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    ElectronAna*
    Electrons*
    patElectronFilter*
    JetEnergyScale*
    ElEl
#    ee
)

topElElAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelElElRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    selectedPatJetsPFlow*
#    ElectronAna*
    Electrons*
    patElectronFilter*
    JetEnergyScale*
    ElEl
#    ee
)

topMuMuAnalysisMCSequence = cms.Sequence(
    hltHighLevelMuMuMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    patMuonFilter*
    JetEnergyScale*
    MuMu
#    mm
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelMuMuRD*
#    muonTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    DYmmFilter*
#    selectedPatJetsPFlow*
    Muons*
    patMuonFilter*
    JetEnergyScale*
    MuMu
#    mm
)

topMuElAnalysisMCSequence = cms.Sequence(
    hltHighLevelMuElMC*
    nEventsPatHLT*
    topWLeptonGenFilter*
    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    JetEnergyScale*
    MuEl
#    em
)

topMuElAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelMuElRD*
#    muonTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    JetEnergyScale*
    MuEl
#    em
)

topMuJetAnalysisMCSequence = cms.Sequence(
#    hltHighLevelMuJetMC*
    nEventsPatHLT*
    topWLeptonGenFilterForLJ*
#    GenZmassFilter*
#    PUweight*
    Muons *
    patMuonFilterForMuJet *
    MuJet
#    mj
)

topMuJetAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelMuJetRD*
#    muonTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
    Muons *
    patMuonFilterForMuJet *
    MuJet
#    mj
)

topElJetAnalysisMCSequence = cms.Sequence(
#    hltHighLevelElJetMC*
    nEventsPatHLT*
    topWLeptonGenFilterForLJ*
#    GenZmassFilter*
#    PUweight*
    Electrons *
    patElectronFilterForElJet *
    ElJet
#    ej
)

topElJetAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelElJetRD*
#    elctronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
    Electrons *
    patElectronFilterForElJet *
    ElJet
#    ej
)
