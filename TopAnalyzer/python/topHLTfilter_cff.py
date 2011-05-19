import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

#for MuEG dataset
#MC
hltHighLevelMuElMC = hltHighLevel.clone()
hltHighLevelMuElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuElMC.HLTPaths = cms.vstring('HLT_Mu8_Ele8_v1','HLT_Mu11_Ele8_v1')
hltHighLevelMuElMC.throw = cms.bool(False)
#RD
hltHighLevelMuElRD = hltHighLevel.clone()
hltHighLevelMuElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuElRD.HLTPaths = cms.vstring('HLT_Mu10_Ele10_CaloIdL_*')
hltHighLevelMuElRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelElElMC = hltHighLevel.clone()
hltHighLevelElElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelElElMC.HLTPaths = cms.vstring('HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2')
hltHighLevelElElMC.throw = cms.bool(False)
#RD
hltHighLevelElElRD = hltHighLevel.clone()
hltHighLevelElElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElRD.HLTPaths = cms.vstring(
    'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_*',
    'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_*',
)
hltHighLevelElElRD.throw = cms.bool(False)

#for DoubleMuon dataset
#MC
hltHighLevelMuMuMC = hltHighLevel.clone()
hltHighLevelMuMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuMuMC.HLTPaths = cms.vstring('HLT_DoubleMu5_v1')
hltHighLevelMuMuMC.throw = cms.bool(False)
#RD
hltHighLevelMuMuRD = hltHighLevel.clone()
hltHighLevelMuMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuRD.HLTPaths = cms.vstring('HLT_DoubleMu7_*')
hltHighLevelMuMuRD.throw = cms.bool(False)

