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

process.GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

process.load("PFAnalyses.CommonTools.countingSequences_cfi")
process.load("KoPFA.TopAnalyzer.topLeptonSelector_cfi")

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(1)
)

process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Electrons'),
  minNumber = cms.uint32(1)
)


from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False 

process.MuEl = cms.EDAnalyzer('TopMuElAnalyzer',
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Electrons'),
  metLabel =  cms.InputTag('patMETsPFlow'),
  jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),
  looseJetId = myJetId, 
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9')
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9','HLT_Ele10_LW_L1R')

process.p = cms.Path(
                     process.loadHistosFromRunInfo*
                     process.hltHighLevel*
                     process.GenZmassFilter*
                     process.Muons*
                     process.patMuonFilter*
                     process.Electrons*
                     process.patElectronFilter*
                     process.VertexFilter*
                     process.MuEl
                    )

