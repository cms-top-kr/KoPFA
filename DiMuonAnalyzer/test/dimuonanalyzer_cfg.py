import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        'file:../prod/RD/patTuple_muon.root'
#         'rfio:///castor/cern.ch/user/t/tjkim/SDMUONFILTER/July19th_v4/Run2010A-PromptReco-v4/patTuple_muon_22_0_Qie.root'
#    )
#)

process.load("KoPFA.DiMuonAnalyzer.RD.patTuple_data_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.load("KoPFA.CommonTools.countingSequences_cfi")
process.load("KoPFA.CommonTools.MuonSelector_cfi")

process.DiMuon = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('selectedPatMuons'),
  metLabel =  cms.InputTag('patMETsPFlow'),
  useEventCounter = cms.bool( False ),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),
)

process.acceptedMuons.src = "selectedPatMuons"
process.Muons.version = 2 #VBTF

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Mu9')

process.p = cms.Path(
                     process.loadHistosFromRunInfo*
#                     process.hltHighLevel*
                     process.acceptedMuons*
                     process.Muons*
                     process.DiMuon
                    )
