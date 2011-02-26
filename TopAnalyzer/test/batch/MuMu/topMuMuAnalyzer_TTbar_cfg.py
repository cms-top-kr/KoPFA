import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_TTbar.root')
)

process.load("PFAnalyses.TTbarDIL.Sources.MU.MC.Fall10.patTuple_TTbar_cff")
process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.muonTriggerFilterForMC.triggerResults = "TriggerResults::HLT"
process.muonTriggerFilterForMC.matchTriggerPath = cms.untracked.string('HLT_Mu9')

process.p = cms.Path(
    process.topMuMuAnalysisMCSequence
)

