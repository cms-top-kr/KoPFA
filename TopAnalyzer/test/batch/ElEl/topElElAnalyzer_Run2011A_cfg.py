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
    fileName = cms.string('vallot_Run2011A.root')
)

process.source.fileNames = [
#    'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/RD/20110425/DoubleElectron_Run2011A-PromptReco-v1.root',
#    'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/RD/20110425/DoubleElectron_Run2011A-PromptReco-v2.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/RD/20110425/DoubleElectron_Run2011A-PromptReco-v1.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/RD/20110425/DoubleElectron_Run2011A-PromptReco-v2.root',
]

#process.out = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('test.root'),
#    outputCommands = cms.untracked.vstring(
#        'drop *',
#        'keep *_*_*_Ntuple'
#    )
#)
#process.outPath = cms.EndPath(process.out)

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")
process.ElEl.doResJec = cms.untracked.bool(False)
#process.ee.doResJec = True

process.p = cms.Path(
    process.topElElAnalysisRealDataSequence
)

