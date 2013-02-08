import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       'file:patTuple.root'
    )
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("KoPFA.TopAnalyzer.cmg2kcms_top_cff")

#FIXME: the gloabl tag does not really matter - this is just indication whether it is MC or Data. 
process.JetEnergyScale.globalTag = cms.untracked.string('START42_V17')

# remove trigger path filter
process.topElElAnalysisMCSequence.remove( process.hltHighLevelElElMC )

process.p = cms.Path(
    #ElEl sequence
    process.topElElAnalysisMCSequence
) 

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)
