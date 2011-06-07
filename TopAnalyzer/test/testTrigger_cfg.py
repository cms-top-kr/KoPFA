import FWCore.ParameterSet.Config as cms
process = cms.Process( "HLTPROV" )
# Conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
# Source
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #pickRelValInputFiles() # <-- picks automatically RelVal input files for the current release
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYmm20to50/patTuple_skim_1_1_ogh.root',
  )
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1 ) )
# Trigger analyzers
process.load( "HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi" )
process.hltEventAnalyzerAOD.processName = cms.string( "REDIGI311X" ) # <-- wild-card for all HLT paths
process.hltEventAnalyzerAOD.triggerName = cms.string( '@' ) # <-- wild-card for all HLT paths
process.hltEventAnalyzerAOD.triggerResults = cms.InputTag("TriggerResults", "REDIGI311X" ) # <-- wild-card for all HLT paths
process.hltEventAnalyzerAOD.triggerEvent = cms.InputTag("hltTriggerSummaryAOD", "REDIGI311X" ) # <-- wild-card for all HLT paths

# Schedule
process.p = cms.Path( process.hltEventAnalyzerAOD )
