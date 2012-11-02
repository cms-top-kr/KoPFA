import FWCore.ParameterSet.Config as cms

muonsWithRelIso = cms.EDFilter("PatRelIsoMuonSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    minNumber = cms.uint32(0),
    maxNumber = cms.uint32(999),
    coneSize = cms.double(0.3),
)

electronsWithRelIso = cms.EDFilter("PatRelIsoElectronSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patElectronsWithTrigger"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    minNumber = cms.uint32(0),
    maxNumber = cms.uint32(999),
    coneSize = cms.double(0.3),
)
