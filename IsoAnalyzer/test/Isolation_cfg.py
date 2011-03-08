import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCDMu20/patTuple_skim_140_1_kGw.root'
#    )
#)

#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10_jetfixed.patTuple_Wmu_SingleMuSkim_cff")
process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10_jetfixed.patTuple_QCDMu20_SingleMuSkim_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10_jetfixed.patTuple_ZJets_SingleMuSkim_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10_jetfixed.patTuple_TTbarD6T_SingleMuSkim_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010A_SingleMU_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010B_SingleMU_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.VertexFilter = cms.EDFilter('VertexFilter',
    vertexLabel =  cms.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.int32(1),
    max = cms.untracked.int32(999),
)

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False 

##################################################
process.JetFilter = cms.EDFilter('JetFilter',
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    min = cms.untracked.uint32(1),
    ptcut = cms.untracked.double(30.),
    looseJetId = myJetId,
)
##################################################

process.load("PFAnalyses.CommonTools.countingSequences_cfi")

from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.dxy = 0.02
muonId.eta = 2.4
muonId.pt = 20 

process.Muons = cms.EDProducer(
    "KoMuonSelector",
    cut = cms.vstring("dxy","eta","pt"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,
)

process.patMuonFilter = cms.EDFilter("PATCandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1),
  maxNumber = cms.uint32(999)
)

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False 

process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")

process.MuonAna = cms.EDAnalyzer('IsolationAnalyzer',
    collectionLabel =  cms.InputTag('Muons'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    looseJetId = myJetId,

    metLabel =  cms.InputTag('patMETsPFlow'),
    pfCandidateLabel = cms.InputTag('particleFlow'),
)

process.load("KoPFA.IsoAnalyzer.WFilter_cff")
process.WmunuMtCut.muonLabel = "Muons"
process.WmunuMtCut.metMin = -999 
process.WmunuMtCut.minMt = 20 #70 
process.WmunuMtCut.maxdphi = 1.5 # 1.5 #999 #1.5

process.GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(11,13,15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

process.topWLeptonGenFilter = cms.EDFilter("GenParticleDecayFilter",
    #applyFilter = cms.untracked.bool( False ),
    applyFilter = cms.untracked.bool( True ),
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(13),
    minCount = cms.untracked.uint32(2),
)

process.GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(13),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

process.p = cms.Path(
                     process.loadHistosFromRunInfo*
                     #process.muonTriggerFilterForMC*
                     process.muonTriggerFilterForMCREDIGI38X*
                     #process.muonTriggerFilterByRun*
                     process.VertexFilter*
                     process.Muons*
                     process.patMuonFilter*
                     #process.GenZmassFilter*
                     #process.topWLeptonGenFilter*
                     #process.WmunuMtCut*
                     #process.JetFilter*
                     process.MuonAna
                    )

