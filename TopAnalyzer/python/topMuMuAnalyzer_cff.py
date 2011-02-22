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
#process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
#process.printTree = cms.EDAnalyzer("ParticleListDrawer",
#                                    src = cms.InputTag("genParticles"),
#                                    maxEventsToPrint  = cms.untracked.int32(20)
#                                    )

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

process.load("PFAnalyses.CommonTools.countingSequences_cfi")
process.load("KoPFA.TopAnalyzer.topLeptonSelector_cfi")

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('Muons'),
  minNumber = cms.uint32(2)
)

from PFAnalyses.CommonTools.Selectors.looseJetIdPSet_cff import looseJetIdPSet
myJetId = looseJetIdPSet.clone()
myJetId.verbose = False 
#from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

process.MuMu = cms.EDAnalyzer('TopMuMuAnalyzer',
  muonLabel1 =  cms.InputTag('Muons'),
  muonLabel2 =  cms.InputTag('Muons'),
  metLabel =  cms.InputTag('patMETsPFlow'),
  jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
  genParticlesLabel = cms.InputTag('genParticles'),
  doResJec = cms.untracked.bool( True),
  useEventCounter = cms.bool( True ),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),
  looseJetId = myJetId, 
  #looseJetId = pfJetIDSelector, 
  #for jet cleaning overlapping with isolated epton within 0.4
  relIso1 = cms.untracked.double(0.21),
  relIso2 = cms.untracked.double(0.21),
  bTagAlgo = cms.untracked.string("trackCountingHighEffBJetTags"),
  minBTagValue = cms.untracked.double(1.7),
)

process.load("KoPFA.TopAnalyzer.ttbarNtupleProducer_cfi")
#process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9')
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")
process.load("KoPFA.CommonTools.genParticleDecayFilter_cfi")

process.p = cms.Path(
#                     process.printTree*
                     	process.loadHistosFromRunInfo*
#                     process.hltHighLevel*
                     	process.muonTriggerFilterForMC*
                        process.topWLeptonGenFilter*
                     	process.GenZmassFilter*
                     	process.Muons*
                     	process.patMuonFilter*
                     	process.VertexFilter*
                     	process.MuMu*
						process.mumu
                    )

