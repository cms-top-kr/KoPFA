import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.countingSequences_cfi import *
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from KoPFA.TopAnalyzer.topLeptonSelector_cfi import *
from KoPFA.TopAnalyzer.triggerFilterByRun_cfi import *
from KoPFA.TopAnalyzer.topHLTfilter_cff import *
from KoPFA.TopAnalyzer.PileUpWeight_cff import *
from KoPFA.CommonTools.JetEnergyScale_cfi import *

PUweight = cms.EDProducer("EventWeightProducer",
  PileUpRD = PileUpRD2011, 
  #PileUpMC = PoissonIntDist #probdistFlat10, PoissonOneXDist 
  PileUpMC = PoissonIntDist
)

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
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
    PileUpRD = PileUpRD2011,
    PileUpMC = PoissonOneXDist,
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
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
    PileUpRD = PileUpRD2011,
    PileUpMC = PoissonOneXDist,
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
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
    PileUpRD = PileUpRD2011,
    PileUpMC = PoissonOneXDist,
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

