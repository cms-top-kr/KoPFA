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


process.demo = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('selectedPatMuons'),
  outputFile = cms.string('ntuple.root')
)


process.p = cms.Path(process.demo)
