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
    fileName = cms.string('vallot_TTbarTuneZ2.root')
)

process.load("KoPFA.TopAnalyzer.Sources.EMU.MC.Spring11.patTuple_TTbar_TuneZ2_cff")
process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.muonTriggerFilterForMC.triggerResults = "TriggerResults::HLT"
process.muonTriggerFilterForMC.matchTriggerPath = cms.untracked.string('HLT_Mu9')

process.topWLeptonGenFilter.applyFilter = True

process.p = cms.Path(
    process.topMuElAnalysisMCSequence
)

