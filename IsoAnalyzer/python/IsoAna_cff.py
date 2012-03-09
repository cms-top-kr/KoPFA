import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        'file:../prod/RD/patTuple_muon.root'
#         'rfio:///castor/cern.ch/user/t/tjkim/SDMUONFILTER/July19th_v4/Run2010A-PromptReco-v4/patTuple_muon_22_0_Qie.root'
#    )
#)

#process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_muon_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.VertexFilter = cms.EDFilter('VertexFilter',
    vertexLabel =  cms.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.int32(1),
    max = cms.untracked.int32(999),
)

from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from KoPFA.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose = False
muonId.dxy = 0.02
muonId.eta = 2.4
muonId.pt = 20

process.Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( 1 ),#TOP
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonSelector = muonId,
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1)
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9')
process.load("KoPFA.IsoAnalyzer.Isolation_cfi")
process.MuonIso.collectionLabel = "Muons"
process.MuonAna = cms.EDAnalyzer('MuonIsoAna',
    collectionLabel =  cms.InputTag('Muons'),
)

process.load("KoPFA.IsoAnalyzer.WFilter_cff")
process.WmunuMtCut.muonLabel = "Muons"

process.p = cms.Path(
                     process.hltHighLevel*
                     process.Muons*
                     process.patMuonFilter*
                     process.WmunuMtCut*
                     process.VertexFilter*
                     process.MuonIso*
                     process.MuonAna
                    )

