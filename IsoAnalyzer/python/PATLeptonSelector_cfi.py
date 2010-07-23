import FWCore.ParameterSet.Config as cms

PatMuonsPFlowIso = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    #src = cms.InputTag("muonsForIsolation"),
    cut =cms.string("pt > 20 && abs(eta) < 2.1")
    )

selectedPatMuonsPFlowIso = cms.EDProducer(
    "LeadMuonSelector",
    src  = cms.InputTag("PatMuonsPFlowIso"),
    chi2 = cms.untracked.double("999"),
    nHits = cms.untracked.double("0"),
    d0 = cms.untracked.double("999"),
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('selectedPatMuonsPFlowIso'),
  minNumber = cms.uint32(1)
)

PatElectronsPFlowIso = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.1 && mva > 0.4 && gsfTrack.trackerExpectedHitsInner.numberOfHits<=1")
    )

selectedPatElectronsPFlowIso = cms.EDProducer(
    "LeadElectronSelector",
    src  = cms.InputTag("PatElectronsPFlowIso"),
)

patElectronFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('selectedPatElectronsPFlowIso'),
  minNumber = cms.uint32(1)
)

