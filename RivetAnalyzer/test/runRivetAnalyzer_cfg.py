import FWCore.ParameterSet.Config as cms

process = cms.Process("RIVET")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(),
)

cmgBaseDir = '/store/cmst3/user/cmgtools/CMG'
sampleName = '/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/AODSIM'
cmgFullVer = 'V5_B/PAT_CMG_V5_13_0'
for i in range(1,1184):
    process.source.fileNames.append("%s%s/%s/patTuple_%d.root" % (cmgBaseDir, sampleName, cmgFullVer, i))

### Add ghost B hadron
process.load('KoPFA.CommonTools.genJetsWithGhostBHadrons_cff')
process.genParticlesWithGhostB.userPdgId = 7

### Rebuild HepMC
#process.load('Configuration.GenProduction.EightTeV.Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_tauola_cff')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')
process.generator.genParticles = 'genParticlesWithGhostB'

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

process.p = cms.Path(process.rivetAnalyzer)
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection = cms.double(13.43)
process.rivetAnalyzer.OutputFile = 'rivet.aida'

process.p = cms.Path(process.genParticlesWithGhostB * process.generator * process.rivetAnalyzer)
#process.p = cms.Path(process.generator * process.rivetAnalyzer)

