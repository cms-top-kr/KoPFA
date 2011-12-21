import FWCore.ParameterSet.Config as cms

process = cms.Process("GenSkim")

### standard includes
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Services_cff")

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_0.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_1.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_2.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_3.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_4.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_5.root'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    fileMode = cms.untracked.string('FULLMERGE')
)

process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring(
        'drop *',
        "keep *_generator_*_*",
    ),
    fileName = cms.untracked.string('edmHepMC_skim.root')
)

process.outPath = cms.EndPath(process.out)

