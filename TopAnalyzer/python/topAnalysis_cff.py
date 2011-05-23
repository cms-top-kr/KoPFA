import FWCore.ParameterSet.Config as cms

#from PFAnalyses.CommonTools.countingSequences_cfi import *
#from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
#myJetId = looseJetIdPSet.clone()
#myJetId.verbose = False

from KoPFA.CommonTools.countingSequences_cfi import *
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from KoPFA.TopAnalyzer.topLeptonSelector_cfi import *
from KoPFA.TopAnalyzer.triggerFilterByRun_cfi import *
from KoPFA.TopAnalyzer.topHLTfilter_cff import *

PUweight = cms.EDProducer("EventWeightProducer",
   # PUweight = cms.vdouble(0.24698,0.878399,1.62972,1.74644,1.48563,0.999695,0.740525,0.457214,0.268234,0.184943,0.127889,0.0274048,0.0959167,0.383667),
    PUweight = cms.vdouble(0.302925,0.965597,1.65007,1.8125,1.42073,0.999606,0.65037,0.358266,0.258592,0.130467,0.0776312,0.0805065),#EMU 153pb-1
    PUdefault = cms.double(0.0),
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

ElEl = cms.EDFilter('TopElElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    metStudy = cms.untracked.bool( False),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
    ),
    looseJetId = myJetId,
    relIso1 = cms.untracked.double(0.26),
    relIso2 = cms.untracked.double(0.26),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

MuMu = cms.EDFilter('TopMuMuAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    metStudy = cms.untracked.bool( True ),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.21),
    relIso2 = cms.untracked.double(0.21),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

MuEl = cms.EDFilter('TopMuElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

from KoPFA.TopAnalyzer.ttbarNtupleProducer_cfi import *

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

topElElAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelElElMC*
    topWLeptonGenFilter*
    GenZmassFilter*
#    VertexFilter*
    PUweight*
    Electrons*
    patElectronFilter*
    ElEl
#    ee
)

topElElAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelElElRD*
#    electronTriggerFilterByRun*
    removeDuplicate*
#    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl
#    ee
)

topMuMuAnalysisMCSequence = cms.Sequence(
    hltHighLevelMuMuMC*
    topWLeptonGenFilter*
    GenZmassFilter*
#    VertexFilter*
    PUweight*
    DYmmFilter*
    Muons*
    patMuonFilter*
    MuMu
#    mm
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelMuMuRD*
#    muonTriggerFilterByRun*
    removeDuplicate*
#    VertexFilter*
    DYmmFilter*
    Muons*
    patMuonFilter*
    MuMu
#    mm
)

topMuElAnalysisMCSequence = cms.Sequence(
#    hltHighLevelMuElMC*
    topWLeptonGenFilter*
    GenZmassFilter*
#    VertexFilter*
    PUweight*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    MuEl
#    em
)

topMuElAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelMuElRD*
#    muonTriggerFilterByRun*
    removeDuplicate*
#    VertexFilter*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    MuEl
#    em
)

