import FWCore.ParameterSet.Config as cms

WenuMtCut = cms.EDFilter("WenuFilter",
  eleLabel =  cms.InputTag("Muons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(70),
  mindphi = cms.double(0.0), #anlge between lepton and neutrino should be larger than maxdphi or smaller than mindphi
  maxdphi = cms.double(0.0),
)


WmunuMtCut = cms.EDFilter("WmunuFilter",
  muonLabel =  cms.InputTag("Muons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(70),
  mindphi = cms.double(0.0),
  maxdphi = cms.double(0.0),
)

