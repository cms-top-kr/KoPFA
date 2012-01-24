import FWCore.ParameterSet.Config as cms

process = cms.Process("runRivetAnalysis")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000000)
)

#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(

#       'file:./data/ZMM/8AC9EB63-CAF5-E011-A329-002354EF3BDB.root',
#       'file:./data/ZMM/D2CC4B63-CAF5-E011-B6F1-003048D3FC94.root',
#       'file:./data/ZEE/9EA4642C-3BF5-E011-91D6-002354EF3BDA.root',
#       'file:./data/ZEE/F8CEB664-CCF5-E011-88BC-00261894394F.root',

#       'file:./data/Susy/808EF414-5BF5-E011-8B14-0018F3D096C2.root',
#       'file:./data/Susy/A48F72AA-77F5-E011-878E-002618943916.root',

#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_100_1_9TB.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_101_1_K2q.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_102_1_4QO.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_103_1_ehQ.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_104_1_xMq.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/SKIM/Gen/HepMC3/edmHepMC_skim_10_1_Nmz.root',

#       'file:output.SAMPLE_0.root'

#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/cms441/RelValZEE/9EA4642C-3BF5-E011-91D6-002354EF3BDA.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/cms441/RelValZMM/8AC9EB63-CAF5-E011-A329-002354EF3BDB.root',

#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_0.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_1.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_2.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_3.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_4.root',
#       'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test/Summer11_TTJets_TuneZ2_7TeV-madgraph-tauola_5.root'

#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_0.root',
#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_1.root',
#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_2.root',
#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_3.root',
#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_4.root',
#      'rfio:///castor/cern.ch/user/t/taeyeon/MC/Summer11/test3/Summer11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_5.root'
#    )
#)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
process.load("KoPFA.RivetAnalyzer.HepMC_TTbar_cff")

#process.TFileService = cms.Service("TFileService",
#    fileName = cms.string('vallot_TTbar.root')
#)

process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

#process.rivetAnalyzer.AnalysisNames = cms.vstring('OPAL_test_190112')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_LES_HOUCHES_SYSTEMATICS_CMS')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_GENERIC')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_11_013')
process.rivetAnalyzer.AnalysisNames = cms.vstring('SKK_MM_11_013')
process.rivetAnalyzer.CrossSection= cms.double('157.5')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_SUSY')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('MC_WWJETS')
#process.rivetAnalyzer.CrossSection= cms.double('31314')

process.p = cms.Path(process.rivetAnalyzer)



