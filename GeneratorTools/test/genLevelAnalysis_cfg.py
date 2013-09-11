import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:E87AF0D3-4C4D-E211-95FA-003048D37694.root',
    )
)

process.load("Configuration.StandardSequences.Services_cff")
process.load("KoPFA.GeneratorTools.genJetsWithGhostBHadrons_cff")

process.genAnalysis = cms.EDAnalyzer("TTbarGenLevelAnalyzer",
    genParticles = cms.InputTag("genParticles"),
    genJets = cms.InputTag("genJetsWithGhost"),
    leptonMinPt = cms.untracked.double(20),
    leptonMaxEta = cms.untracked.double(2.5),
    neutrinoMaxEta = cms.untracked.double(5),
    jetMinPt = cms.untracked.double(30),
    jetMaxEta = cms.untracked.double(2.5),
)

process.TFileService = cms.Serivce("TFileService",
    fileName = cms.untracked.fileName("genLevel.root"),
)

process.p = cms.Path(
)
