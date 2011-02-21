import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.countingSequences_cfi import *
from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.dxy = 0.02
muonId.eta = 2.5
muonId.pt = 20
from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonIso = muonIsoSelectorPSet.clone()

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

ElEl = cms.EDAnalyzer('TopElElAnalyzer',
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'initialEvents',
        'finalEvents'
    ),
    looseJetId = myJetId,
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
		bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
		minBTagValue = cms.untracked.double(1.7),
)

MuMu = cms.EDAnalyzer('TopMuMuAnalyzer',
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( True ),
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

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

topElElAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    GenZmassFilter*
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl
)

topElElAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    electronTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl
)

topMuMuAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    GenZmassFilter*
    VertexFilter*
    Muons*
    patMuonFilter*
    MuMu
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    muonTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Muons*
    patMuonFilter*
    MuMu
)

