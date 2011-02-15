import FWCore.ParameterSet.Config as cms

from KoPFA.DiMuonAnalyzer.pf2pat_muon_cff import process

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/data/Run2010A/Mu/RECO/v4/000/140/379/E6F46854-8592-DF11-AACD-001617C3B6CE.root', #golden event from top
#'/store/data/Run2010A/Mu/RECO/v4/000/142/136/1A788144-289E-DF11-AC2A-001D09F2960F.root', #golden event from PF
'castor:/castor/cern.ch/cms/store/data/Run2010B/Mu/RECO/PromptReco-v2/000/149/182/00A4394A-44E4-DF11-9DD6-001617E30CD4.root'
  )
)
process.GlobalTag.globaltag = cms.string('GR_R_38X_V14::All')
process.acceptedMuons.cut = cms.string("pt > 5 && abs(eta) < 2.4")
process.patMuonFilter.minNumber = 1


