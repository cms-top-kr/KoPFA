import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_Wm.root')
)

process.load("PFAnalyses.TTbarDIL.Sources.ELE.MC.Fall10.patTuple_Wmu_cff")
process.source.fileNames = [
    #'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/Wm.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/Wm.root',
]
process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.electronTriggerFilterForMC.triggerResults = "TriggerResults::REDIGI38X"
process.electronTriggerFilterForMC.triggerEvent = "hltTriggerSummaryAOD::REDIGI38X"
process.electronTriggerFilterForMC.matchTriggerPath = cms.untracked.string('HLT_Ele10_LW_L1R')
process.electronTriggerFilterForMC.matchTriggerObject = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt10PixelMatchFilter")

process.p = cms.Path(
    process.topElElAnalysisMCSequence
)

