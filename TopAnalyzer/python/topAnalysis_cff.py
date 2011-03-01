import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.countingSequences_cfi import *

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False

from KoPFA.TopAnalyzer.topLeptonSelector_cfi import *
from KoPFA.TopAnalyzer.triggerFilterByRun_cfi import *

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

patMuonFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Muons'),
    minNumber = cms.uint32(2)
)

patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Electrons'),
    minNumber = cms.uint32(2)
)

patMuonFilterForElMu = patMuonFilter.clone()
patElectronFilterForElMu = patElectronFilter.clone()
patMuonFilterForElMu.minNumber = 1
patElectronFilterForElMu.minNumber = 1

ElEl = cms.EDAnalyzer('TopElElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'initialEvents',
        'finalEvents'
    ),
    looseJetId = myJetId,
    relIso1 = cms.untracked.double(0.26),
    relIso2 = cms.untracked.double(0.26),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

MuMu = cms.EDAnalyzer('TopMuMuAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'initialEvents',
        'finalEvents'
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.21),
    relIso2 = cms.untracked.double(0.21),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

ElMu = cms.EDAnalyzer('TopElMuAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( False ),
    filters = cms.untracked.vstring(
        'initialEvents',
        'finalEvents'
    ),
    looseJetId = myJetId, 
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.26),
    relIso2 = cms.untracked.double(0.21),
    bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
    minBTagValue = cms.untracked.double(1.7),
)

from KoPFA.TopAnalyzer.ttbarNtupleProducer_cfi import *

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

topElElAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    GenZmassFilter*
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl*
    ee
)

topElElAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    electronTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl*
    ee
)

topMuMuAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    GenZmassFilter*
    VertexFilter*
    Muons*
    patMuonFilter*
    MuMu*
    mm
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    muonTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Muons*
    patMuonFilter*
    MuMu*
    mm
)

topElMuAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    GenZmassFilter*
    VertexFilter*
    Muons * Electrons *
    patMuonFilterForElMu * patElectronFilterForElMu *
    ElMu*
    em
)

topElMuAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    muonTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Muons * Electrons *
    patMuonFilterForElMu * patElectronFilterForElMu *
    ElMu*
    em
)

