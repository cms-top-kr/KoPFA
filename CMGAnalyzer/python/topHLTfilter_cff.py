import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

## to apply the same trigger path for data and MC
##for MuEG
hltHighLevelMuEl = hltHighLevel.clone()
hltHighLevelMuEl.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuEl.HLTPaths = cms.vstring(
    'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
    'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*'
)
hltHighLevelMuEl.throw = cms.bool(False)

##for DoubleElectron
hltHighLevelElEl = hltHighLevel.clone()
hltHighLevelElEl.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElEl.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*'
)
hltHighLevelElEl.throw = cms.bool(False)

##for DoubleMuon
hltHighLevelMuMu = hltHighLevel.clone()
hltHighLevelMuMu.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMu.HLTPaths = cms.vstring('HLT_Mu17_Mu8_v*','HLT_Mu17_TkMu8_v*')
hltHighLevelMuMu.throw = cms.bool(False)

## to separate for data and MC
#for MuEG dataset
#MC
hltHighLevelMuElMC = hltHighLevel.clone()
hltHighLevelMuElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuElMC.HLTPaths = cms.vstring(
    'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7',
    'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7'
)
hltHighLevelMuElMC.throw = cms.bool(False)
#RD
hltHighLevelMuElRD = hltHighLevel.clone()
hltHighLevelMuElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuElRD.HLTPaths = cms.vstring(
    'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
    'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*'
)
hltHighLevelMuElRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelElElMC = hltHighLevel.clone()
hltHighLevelElElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElMC.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17'
)
hltHighLevelElElMC.throw = cms.bool(False)
#RD
hltHighLevelElElRD = hltHighLevel.clone()
hltHighLevelElElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElRD.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*'
)
hltHighLevelElElRD.throw = cms.bool(False)

#for DoubleMuon dataset
#MC
hltHighLevelMuMuMC = hltHighLevel.clone()
hltHighLevelMuMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuMC.HLTPaths = cms.vstring('HLT_Mu17_Mu8_v17','HLT_Mu17_TkMu8_v10')
hltHighLevelMuMuMC.throw = cms.bool(False)
#RD
hltHighLevelMuMuRD = hltHighLevel.clone()
hltHighLevelMuMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuRD.HLTPaths = cms.vstring('HLT_Mu17_Mu8_v*','HLT_Mu17_TkMu8_v*')
hltHighLevelMuMuRD.throw = cms.bool(False)


