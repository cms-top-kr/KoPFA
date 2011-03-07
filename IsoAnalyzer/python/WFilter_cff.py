import FWCore.ParameterSet.Config as cms

WenuMtCut = cms.EDFilter("WenuFilter",
  eleLabel =  cms.InputTag("Electrons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  metMin = cms.double(-999),
  minMt = cms.double(0),
  mindphi = cms.double(-1.0), #anlge between lepton and neutrino should be smaller than maxdphi and larger than mindphi
  maxdphi = cms.double(999.0),
)

WmunuMtCut = cms.EDFilter("WmunuFilter",
  muonLabel =  cms.InputTag("Muons"),
  metLabel =  cms.InputTag('patMETsPFlow'),
  pfCandidateLabel = cms.InputTag('particleFlow'),
  metMin =cms.untracked.double(-999.0),
  minMt = cms.double(0),
  maxMt = cms.double(9999),
  mindphi = cms.double(-1.0),
  maxdphi = cms.double(999.0),
)

