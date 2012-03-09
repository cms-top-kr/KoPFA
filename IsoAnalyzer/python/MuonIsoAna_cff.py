import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        'file:../prod/RD/patTuple_muon.root'
#         'rfio:///castor/cern.ch/user/t/tjkim/SDMUONFILTER/July19th_v4/Run2010A-PromptReco-v4/patTuple_muon_22_0_Qie.root'
#    )
#)

#process.load("PFAnalyses.TTbarDIL.Sources.MU.RD.patTuple_Run2010B_PromptReco_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Spring10.patTuple_WJets_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Spring10.patTuple_Zmumu_cff")
#process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Spring10.patTuple_InclusiveMu15_cff")
#process.load("KoPFA.DiMuonAnalyzer.MC.Fall10_Single_MUSKIM.patTuple_Zmm_cff")
#process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_Run2010A_SingleMU_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.VertexFilter = cms.EDFilter('VertexFilter',
    vertexLabel =  cms.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.int32(1),
    max = cms.untracked.int32(999),
)

process.Muons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuons"),
    cut =cms.string("isGlobalMuon && pt > 20 && abs(eta) < 2.4 && globalTrack.normalizedChi2 < 10.0 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0 && innerTrack.hitPattern.numberOfValidTrackerHits > 10 && numberOfMatchedStations() >1")
)

process.patMuonFilter = cms.EDFilter("PATCandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1),
  maxNumber = cms.uint32(1)
)

from KoPFA.CommonTools.JetEnergyScale_cfi import *

##################################################

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI38X")
process.hltHighLevel.throw = False

process.MuonAna = cms.EDAnalyzer('MuonIsolationAnalyzer',
    collectionLabel =  cms.InputTag('Muons'),
    jetLabel = cms.InputTag("selectedPatJetsPFlow"),
    metLabel =  cms.InputTag('patMETsPFlow'),
    pfCandidateLabel = cms.InputTag('particleFlow'),
    looseJetId = myJetId,
)

process.load("KoPFA.IsoAnalyzer.WFilter_cff")
process.WmunuMtCut.muonLabel = "Muons"
process.WmunuMtCut.minMt = 0 #70 
process.WmunuMtCut.maxMt = 20 #70 
process.WmunuMtCut.maxdphi =  1.5 #999 #1.5

process.p = cms.Path(
#                     process.loadHistosFromRunInfo*
                     process.hltHighLevel*
#                     process.JetFilter*
                     process.Muons*
                     process.patMuonFilter*
#                     process.WmunuMtCut*
#                     process.VertexFilter*
                     process.MuonAna
                    )

