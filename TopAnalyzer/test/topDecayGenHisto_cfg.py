import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_topdecay.root')
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
                                    src = cms.InputTag("genParticles"),
                                    maxEventsToPrint  = cms.untracked.int32(95)
)

#process.load("KoPFA.TopAnalyzer.Sources.MU.MC.Summer11.patTuple_TTbarTuneZ2_cff")
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #pickRelValInputFiles() # <-- picks automatically RelVal input files for the current release
    'rfio:/castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Fall11/TTJets/patTuple_skim_95_0_860.root'
  )
)

process.topDecayGenHisto = cms.EDFilter('TopDecayGenHisto',
  applyFilter =  cms.untracked.bool(True),
  semiLeptonic = cms.bool(False),
  semiLeptonicMuon = cms.bool(False),
  semiLeptonicElectron = cms.bool(False),
  diLeptonic = cms.bool(True),
  diLeptonicMuoMuo = cms.bool(False),
  diLeptonicEleEle = cms.bool(False),
  diLeptonicMuoEle = cms.bool(False),
  diLeptonicTauMuo = cms.bool(False),
  diLeptonicTauEle = cms.bool(False),
  diLeptonicTauTau = cms.bool(False),
)

process.p = cms.Path(
#    process.printTree+
    process.topDecayGenHisto
) 


