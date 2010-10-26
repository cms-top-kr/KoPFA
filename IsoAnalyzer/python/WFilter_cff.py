import FWCore.ParameterSet.Config as cms

WenuMtCut = cms.EDFilter("WenuFilter",
  eleLabel =  cms.InputTag("Electrons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(70),
  mindphi = cms.double(-1.0), #anlge between lepton and neutrino should be smaller than maxdphi and larger than mindphi
  maxdphi = cms.double(999.0),
)

WmunuMtCut = cms.EDFilter("WmunuFilter",
  muonLabel =  cms.InputTag("Muons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  minMt = cms.double(70),
  mindphi = cms.double(-1.0),
  maxdphi = cms.double(999.0),
)

