import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
                                    src = cms.InputTag("genParticles"),
                                    maxEventsToPrint  = cms.untracked.int32(20)
)

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.MuMu.doResJec = cms.untracked.bool(False)

process.p = cms.Path(
    process.printTree+
    process.topMuMuAnalysisMCSequence
) 

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_TTbarTuneZ2.root')
)

process.load("KoPFA.TopAnalyzer.Sources.MU.MC.Summer11.patTuple_TTbarTuneZ2_cff")

process.topWLeptonGenFilter.applyFilter = True
