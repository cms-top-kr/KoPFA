import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

#for MuEG dataset
#MC
hltHighLevelMuEGMC = hltHighLevel.clone()
hltHighLevelMuEGMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuEGMC.HLTPaths = cms.vstring('HLT_Mu8_Ele8_v1','HLT_Mu11_Ele8_v1')
hltHighLevelMuEGMC.throw = cms.bool(False)
#RD
hltHighLevelMuEGRD = hltHighLevel.clone()
hltHighLevelMuEGRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuEGRD.HLTPaths = cms.vstring('HLT_Mu10_Ele10_CaloIdL_v1')
hltHighLevelMuEGRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelElElMC = hltHighLevel.clone()
hltHighLevelElElMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelElElMC.HLTPaths = cms.vstring('HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2')
hltHighLevelElElMC.throw = cms.bool(False)
#RD
hltHighLevelElElRD = hltHighLevel.clone()
hltHighLevelElElRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelElElRD.HLTPaths = cms.vstring('HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v2')
hltHighLevelElElRD.throw = cms.bool(False)

#for DoubleElectron dataset
#MC
hltHighLevelMuMuMC = hltHighLevel.clone()
hltHighLevelMuMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI311X")
hltHighLevelMuMuMC.HLTPaths = cms.vstring('HLT_DoubleMu5_v1')
hltHighLevelMuMuMC.throw = cms.bool(False)
#RD
hltHighLevelMuMuRD = hltHighLevel.clone()
hltHighLevelMuMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelMuMuRD.HLTPaths = cms.vstring('HLT_DoubleMu6_v1')
hltHighLevelMuMuRD.throw = cms.bool(False)

