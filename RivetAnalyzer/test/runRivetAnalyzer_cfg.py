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
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:E87AF0D3-4C4D-E211-95FA-003048D37694.root',
        #'file:out.root',
        'file:/data/local/data01/common/CMS/AODSIM/Summer12/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/PU_S7_START52_V9-v2/A6323CBD-A0B8-E111-97B4-002618943958.root',
    ),
)

### Setup pythia for the hadronization
process.load('Configuration.GenProduction.EightTeV.Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_tauola_cff')
process.generator = cms.EDProducer("GenParticles2HepMCConverter",
    genParticles = cms.InputTag("genParticles"),
    genRunInfo = cms.InputTag("generator"),
    genEventInfo = cms.InputTag("generator"),
)

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection= cms.double('157.5')

#process.p = cms.Path(process.generator * process.rivetAnalyzer)
#Pprocess.p = cms.Path(process.rivetAnalyzer)
process.p = cms.Path(process.generator * process.rivetAnalyzer)

