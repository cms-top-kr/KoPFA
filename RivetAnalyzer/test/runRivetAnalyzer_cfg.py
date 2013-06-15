import FWCore.ParameterSet.Config as cms

process = cms.Process("RIVET")

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V7C::All', '')

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

### Setup pythia for the hadronization
#process.load('Configuration.GenProduction.EightTeV.Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_tauola_cff')
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

process.p = cms.Path(process.rivetAnalyzer)
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection= cms.double('157.5')
process.rivetAnalyzer.OutputFile = 'rivet.aida'

process.p = cms.Path(process.generator * process.rivetAnalyzer)

