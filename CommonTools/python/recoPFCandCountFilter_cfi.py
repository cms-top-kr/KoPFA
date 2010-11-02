import FWCore.ParameterSet.Config as cms

recoPFElElCountFilter = cms.EDFilter("PFCandCountFilter",
    pdgId = cms.untracked.int32(11),
    minPt = cms.untracked.double(20),
    maxEta = cms.untracked.double(2.5),
    minCount = cms.untracked.int32(2)
)

recoPFMuMuCountFilter = cms.EDFilter("PFCandCountFilter",
    pdgId = cms.untracked.int32(13),
    minPt = cms.untracked.double(20),
    maxEta = cms.untracked.double(2.5),
    minCount = cms.untracked.int32(2)
)

