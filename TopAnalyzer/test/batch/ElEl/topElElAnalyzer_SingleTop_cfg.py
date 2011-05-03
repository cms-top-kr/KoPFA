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
    fileName = cms.string('vallot_SingleTop.root')
)

process.load("PFAnalyses.TTbarDIL.Sources.ELE.MC.Fall10.patTuple_SingleTop_cff")
process.source.fileNames = [
#    'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_s.root',
#    'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_t.root',
#    'file:/data/export/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_tW.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_s.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_t.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110425/SingleTop_tW.root',
]
process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.p = cms.Path(
    process.topElElAnalysisMCSequence
)

