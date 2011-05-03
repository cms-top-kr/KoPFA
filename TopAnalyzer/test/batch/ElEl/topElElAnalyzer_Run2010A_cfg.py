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
    fileName = cms.string('vallot_Run2010A.root')
)

#process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010A_Nov4ReReco_cff")
process.source.fileNames = [
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/RD/20101209/EG_Run2010A-Nov4ReReco_v1.root',
]

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")
process.ElEl.doResJec = cms.untracked.bool(True)
process.ee.doResJec = True

process.p = cms.Path(
    process.topElElAnalysisRealDataSequence
)

