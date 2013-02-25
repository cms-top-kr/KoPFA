import FWCore.ParameterSet.Config as cms

process = cms.Process("Histo")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("KoPFA.CMGAnalyzer.topAnalysis_cff")
process.load("KoPFA.CommonTools.eventFilter_cfi")
process.load("KoPFA.IsoAnalyzer.cmgMuonIsoAnalyzer_cfi")
#process.load("KoPFA.IsoAnalyzer.cmgEMuonIsoAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.ZFilter_cfi")

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

runOnMC = True
runOn2012 = True

from CMGTools.Common.Tools.applyJSON_cff import applyJSON
json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON_v2.txt'
if not runOnMC:
    applyJSON(process, json )

process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.load("KoPFA.CMGAnalyzer.TtFullLepKinSolutionProducer_cfi")
process.load("KoPFA.CMGAnalyzer.TtFullLepMaosSolutionProducer_cfi")

from KoPFA.CMGAnalyzer.JetEnergyScale_cfi import *
JetEnergyScale.electronLabel = cms.InputTag("cmgElectronSel")
JetEnergyScale.muonLabel = cms.InputTag("cmgMuonSel")

nEventsPatHLT = cms.EDProducer("EventCountProducer")
process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.p5 = cms.Path(
    process.hltHighLevelMuMu*
    #process.hltHighLevelMuEl*
    process.nEventsPatHLT*
    process.EventFilter*
    process.nEventsFilter*
    JetEnergyScale*
    process.MuonAnalysis
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)




##################################################################

