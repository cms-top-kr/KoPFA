import FWCore.ParameterSet.Config as cms


topDecayGenFilter = cms.EDFilter('TopDecayGenFilter',
  applyFilter =  cms.untracked.bool(True),
  allHadronic = cms.bool(False),
  semiLeptonic = cms.bool(False),
  semiLeptonicMuon = cms.bool(False),
  semiLeptonicElectron = cms.bool(False),
  semiLeptonicTau = cms.bool(False),
  diLeptonic = cms.bool(True),
  diLeptonicMuoMuo = cms.bool(True),
  diLeptonicEleEle = cms.bool(True),
  diLeptonicMuoEle = cms.bool(True),
  diLeptonicTauMuo = cms.bool(False),
  diLeptonicTauEle = cms.bool(False),
  diLeptonicTauTau = cms.bool(False),
)   

