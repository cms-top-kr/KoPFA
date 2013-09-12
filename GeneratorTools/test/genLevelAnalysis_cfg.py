import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/cmst3/user/cmgtools/CMG//TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/AODSIM/V5_B/PAT_CMG_V5_13_0/patTuple_2.root', 
    )
)

process.load("Configuration.StandardSequences.Services_cff")
process.load("KoPFA.GeneratorTools.genJetsWithGhostBHadrons_cff")

process.genAnalysis = cms.EDAnalyzer("TTbarGenLevelAnalyzer",
    genParticles = cms.untracked.InputTag("genParticles"),
    genJets = cms.untracked.InputTag("ak5GenJets::USER"),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("genLevel.root"),
)

process.p = cms.Path(
    process.genParticlesWithGhostB * process.genParticlesForJets * process.ak5GenJets
  * process.genAnalysis
)
