import FWCore.ParameterSet.Config as cms

process = cms.Process("Histo")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load("KoPFA.CMGAnalyzer.topAnalysis_cff")
process.load("KoPFA.CommonTools.eventFilter_cfi")
process.load("KoPFA.IsoAnalyzer.cmgMuonIsoAnalyzer_cfi")

#Data
process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Run2012.cmgTuple_Run2012AMuMu_cff")
#MC
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.patTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.patTuple_TTbarFullLepMGDecays_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTH_HToBB_M125_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTbarFullLepMGDecays_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_ZJets_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.patTuple_QCD_cff")

nEventsPatHLT = cms.EDProducer("EventCountProducer")
process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.p = cms.Path(
    process.hltHighLevelMuMu*
    process.nEventsPatHLT*
    process.EventFilter*
    process.nEventsFilter*
    process.MuonIsoAnalysis
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)
