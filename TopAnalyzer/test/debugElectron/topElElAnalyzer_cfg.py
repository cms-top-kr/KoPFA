import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:patTuple_skim.root'
#         'rfio:///castor/cern.ch/user/t/tjkim/SDMUONFILTER/July19th_v4/Run2010A-PromptReco-v4/patTuple_muon_22_0_Qie.root'
    )
)

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
    decayMode = cms.untracked.vint32(11,13,15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

from PFAnalyses.CommonTools.Selectors.electronSelectorPSet_cff import electronSelectorPSet
from PFAnalyses.CommonTools.Selectors.newElectronIsoSelectorPSet_cff import electronIsoSelectorPSet

process.pfElectrons = cms.EDProducer(
    "KoElectronSelector",
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    electronLabel  = cms.InputTag("acceptedElectrons"),
    #electronLabel  = cms.InputTag("selectedPatElectronsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    electronIdSelector = electronSelectorPSet,
    electronIsoSelector = electronIsoSelectorPSet,
)

process.Electrons = cms.EDProducer(
    "KoElectronSelector", 
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    usepflow = cms.untracked.bool(False),
    electronLabel  = cms.InputTag("selectedPatElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    electronIdSelector = electronSelectorPSet,
    electronIsoSelector = electronIsoSelectorPSet,
)

process.patpfElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('pfElectrons'),
  minNumber = cms.uint32(2)
)

process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Electrons'),
  minNumber = cms.uint32(2)
)


from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False 

process.ElEl = cms.EDAnalyzer('TopElElAnalyzer',
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
  #for jet cleaning overlapping with isolated epton within 0.4
  relIso1 = cms.untracked.double(0.20),
  relIso2 = cms.untracked.double(0.20),
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_Ele10_LW_L1R')

process.p_pflow = cms.Path(
                     process.pfElectrons*
                     process.patpfElectronFilter
                    )

process.p = cms.Path(
#                    process.loadHistosFromRunInfo*
#                     process.hltHighLevel*
#                     process.GenZmassFilter*
                     process.Electrons*
                     process.patElectronFilter
#                     process.VertexFilter*
#                     process.ElEl
                    )

