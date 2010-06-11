import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.load("KoPFA.DiMuonAnalyzer.RD.SDMUON_MuonFilter_Run_135176_135802_cff")

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
#    )
#)

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.DiMuon = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('selectedPatMuons'),
)


process.p = cms.Path(process.DiMuon)
