import FWCore.ParameterSet.Config as cms

WenuMtCut = cms.EDFilter("WenuFilter",
  eleLabel =  cms.InputTag("selectedPatElectronsPFlowIso"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(60),
  mindphi = cms.double(-999),
  maxdphi = cms.double(2.0),
)


WmunuMtCut = cms.EDFilter("WmunuFilter",
  muonLabel =  cms.InputTag("selectedPatMuonsPFlowIso"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(60),
  mindphi = cms.double(-999),
  maxdphi = cms.double(2.0),
)

