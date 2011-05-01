import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.countingSequences_cfi import *

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False

from KoPFA.TopAnalyzer.topLeptonSelector_cfi import *
from KoPFA.TopAnalyzer.triggerFilterByRun_cfi import *

PUweight = cms.EDProducer("EventWeightProducer",
    PUweight = cms.vdouble(0.24698,0.878399,1.62972,1.74644,1.48563,0.999695,0.740525,0.457214,0.268234,0.184943,0.127889,0.0274048,0.0959167,0.383667),
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

from HLTrigger.HLTfilters.hltHighLevel_cfi import *
#for MuEG dataset
#MC
hltHighLevelMuEGMC = hltHighLevel.clone()
hltHighLevelMuEGMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuEGMC.HLTPaths = cms.vstring('HLT_Mu8_Ele8_v1','HLT_Mu11_Ele8_v1')
hltHighLevelMuEGMC.throw = cms.bool(False)
#RD
hltHighLevelMuEGRD = hltHighLevel.clone()
hltHighLevelMuEGRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuEGRD.HLTPaths = cms.vstring('HLT_Mu10_Ele10_CaloIdL_v1')
hltHighLevelMuEGRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelElElMC = hltHighLevel.clone()
hltHighLevelElElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelElElMC.HLTPaths = cms.vstring('HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2')
hltHighLevelElElMC.throw = cms.bool(False)
#RD
hltHighLevelElElRD = hltHighLevel.clone()
hltHighLevelElElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElRD.HLTPaths = cms.vstring('HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v2')
hltHighLevelElElRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelMuMuMC = hltHighLevel.clone()
hltHighLevelMuMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuMuMC.HLTPaths = cms.vstring('HLT_DoubleMu5_v1')
hltHighLevelMuMuMC.throw = cms.bool(False)
#RD
hltHighLevelMuMuRD = hltHighLevel.clone()
hltHighLevelMuMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuRD.HLTPaths = cms.vstring('HLT_DoubleMu6_v1')
hltHighLevelMuMuRD.throw = cms.bool(False)

ElEl = cms.EDAnalyzer('TopElElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Electrons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    metStudy = cms.bool( False),
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
    metStudy = cms.bool( True ),
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

MuEl = cms.EDAnalyzer('TopMuElAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    muonLabel1 =  cms.InputTag('Muons'),
    muonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'initialEvents',
    #    'finalEvents'
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
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl*
    ee
)

topElElAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelElElMC*
#    electronTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Electrons*
    patElectronFilter*
    ElEl*
    ee
)

topMuMuAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelMuMuMC*
    topWLeptonGenFilter*
    GenZmassFilter*
    VertexFilter*
    PUweight*
    Muons*
    patMuonFilter*
    MuMu*
    mm
)

topMuMuAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelMuMuRD*
#    muonTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Muons*
    patMuonFilter*
    MuMu*
    mm
)

topMuElAnalysisMCSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelMuEGMC*
    topWLeptonGenFilter*
    GenZmassFilter*
    VertexFilter*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    MuEl
#    em
)

topMuElAnalysisRealDataSequence = cms.Sequence(
    loadHistosFromRunInfo*
    hltHighLevelMuEGRD*
#    muonTriggerFilterByRun*
    removeDuplicate*
    VertexFilter*
    Muons * Electrons *
    patMuonFilterForMuEl * patElectronFilterForMuEl *
    MuEl
#    em
)

