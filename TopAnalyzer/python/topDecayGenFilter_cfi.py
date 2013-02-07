import FWCore.ParameterSet.Config as cms


topDecayGenFilter = cms.EDFilter('TopDecayGenFilter',
  applyFilter =  cms.untracked.bool(True),
  genParticlesLabel = cms.InputTag('genParticlesPruned'),
  allHadronic = cms.bool(False),
  semiLeptonic = cms.bool(False),
  semiLeptonicMuon = cms.bool(False),
  semiLeptonicElectron = cms.bool(False),
  semiLeptonicTau = cms.bool(False),
  diLeptonic = cms.bool(True),
  diLeptonicMuoMuo = cms.bool(True),
  diLeptonicEleEle = cms.bool(True),
  diLeptonicMuoEle = cms.bool(True),
  diLeptonicTauMuo = cms.bool(True),
  diLeptonicTauEle = cms.bool(True),
  diLeptonicTauTau = cms.bool(True),
)   

