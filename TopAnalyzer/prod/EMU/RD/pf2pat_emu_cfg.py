import FWCore.ParameterSet.Config as cms

from KoPFA.TopAnalyzer.pf2pat_template_cfg import *

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
  '/store/data/Run2011A/MuEG/RECO/PromptReco-v1/000/161/312/C69F1A78-0958-E011-AC6B-003048F118C4.root'
  )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring()
process.hltHighLevel.throw = cms.bool(False)
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")

process.acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
)

process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('acceptedElectrons'),
    minNumber = cms.uint32(1)
)

process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.5")
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(1)
)

#process.p += process.muonTriggerFilterByRun 
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.acceptedElectrons
process.p += process.acceptedMuons
process.p += process.patElectronFilter
process.p += process.patMuonFilter

process.MessageLogger.cerr.FwkReport.reportEvery = 100
