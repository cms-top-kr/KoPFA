import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

#for MuEG dataset
#MC
hltHighLevelMuElMC = hltHighLevel.clone()
hltHighLevelMuElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuElMC.HLTPaths = cms.vstring('HLT_Mu10_Ele10_CaloIdL_v*','HLT_Mu17_Ele8_CaloIdL_v*','HLT_Mu8_Ele17_CaloIdL_v*','HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v*','HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v*')
hltHighLevelMuElMC.throw = cms.bool(False)
#RD
hltHighLevelMuElRD = hltHighLevel.clone()
hltHighLevelMuElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuElRD.HLTPaths = cms.vstring('HLT_Mu10_Ele10_CaloIdL_v*','HLT_Mu17_Ele8_CaloIdL_v*','HLT_Mu8_Ele17_CaloIdL_v*','HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v*','HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v*')
hltHighLevelMuElRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelElElMC = hltHighLevel.clone()
hltHighLevelElElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElMC.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',
    'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',
    'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
)
hltHighLevelElElMC.throw = cms.bool(False)
#RD
hltHighLevelElElRD = hltHighLevel.clone()
hltHighLevelElElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElRD.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',
    'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',
    'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
)
hltHighLevelElElRD.throw = cms.bool(False)

#for DoubleMuon dataset
#MC
hltHighLevelMuMuMC = hltHighLevel.clone()
hltHighLevelMuMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuMC.HLTPaths = cms.vstring('HLT_DoubleMu7_v*')
hltHighLevelMuMuMC.throw = cms.bool(False)
#RD
hltHighLevelMuMuRD = hltHighLevel.clone()
hltHighLevelMuMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuRD.HLTPaths = cms.vstring('HLT_DoubleMu7_*','HLT_Mu17_Mu8_v*','HLT_Mu13_Mu8_v*')
hltHighLevelMuMuRD.throw = cms.bool(False)


