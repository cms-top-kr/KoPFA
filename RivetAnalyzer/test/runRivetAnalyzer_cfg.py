import FWCore.ParameterSet.Config as cms

process = cms.Process("runRivetAnalysis")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_0.root',
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_1.root',
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_2.root',
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_3.root',
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_4.root',
       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_5.root'

#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_0.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_1.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_2.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_3.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_4.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_5.root'
    )
)

process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

#process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_EWK_10_012')
process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_TTBAR')
process.rivetAnalyzer.CrossSection= cms.double('157.5')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_SUSY')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_WJETS')
#process.rivetAnalyzer.CrossSection= cms.double('31314')

process.p = cms.Path(process.rivetAnalyzer)



