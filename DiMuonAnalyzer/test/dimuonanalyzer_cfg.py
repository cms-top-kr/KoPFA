import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:../prod/RD/patTuple_muon.root'
    )
)

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.load("KoPFA.CommonTools.countingSequences_cfi")

process.DiMuon = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('selectedPatMuons'),
  filters = cms.untracked.vstring(
                              'initialEvents',
                              'finalEvents'
                              ),

)

process.p = cms.Path(process.loadHistosFromRunInfo*process.DiMuon)
