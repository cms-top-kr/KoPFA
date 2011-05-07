import FWCore.ParameterSet.Config as cms

from KoPFA.TopAnalyzer.pf2pat_template_cfg import *

#Apply PF2PAT
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)

updateEventContent(process)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(999)
process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(999)

## Source
# MC sample will be taken automatically from template file

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.p += process.hltHighLevelElElMC
process.p += process.eidCiCSequence
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.acceptedElectrons
process.p += process.patElectronFilter

# top projections in PF2PAT:
getattr(process,"pfNoPileUp"+postfix).enable = True
getattr(process,"pfNoMuon"+postfix).enable = True
getattr(process,"pfNoElectron"+postfix).enable = True
getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
getattr(process,"pfNoJet"+postfix).enable = True

process.MessageLogger.cerr.FwkReport.reportEvery = 100
