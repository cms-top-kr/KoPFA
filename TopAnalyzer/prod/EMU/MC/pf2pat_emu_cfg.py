import FWCore.ParameterSet.Config as cms

from KoPFA.TopAnalyzer.pf2pat_template_cfg import *

#Electron ID
process.load('RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi')
process.patElectrons.electronIDSources = cms.PSet(
    eidVeryLooseMC = cms.InputTag("eidVeryLooseMC"),
    eidLooseMC = cms.InputTag("eidLooseMC"),
    eidMediumMC = cms.InputTag("eidMediumMC"),
    eidTightMC = cms.InputTag("eidTightMC"),
    eidSuperTightMC = cms.InputTag("eidSuperTightMC"),
    eidHyperTight1MC = cms.InputTag("eidHyperTight1MC")
)

process.eidCiCSequence = cms.Sequence(
    process.eidVeryLooseMC * process.eidLooseMC * process.eidMediumMC
  * process.eidTightMC * process.eidSuperTightMC * process.eidHyperTight1MC
)

process.p += process.eidCiCSequence

#Apply PF2PAT
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)

updateEventContent(process)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(999)
process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(999)

## Source
#process.source = cms.Source("PoolSource",
#                                fileNames = cms.untracked.vstring(
#  '/store/data/Run2011A/MuEG/RECO/PromptReco-v1/000/161/312/C69F1A78-0958-E011-AC6B-003048F118C4.root'
#  )
#)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring()
process.hltHighLevel.throw = cms.bool(False)
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")

#process.p += process.muonTriggerFilterByRun 
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.acceptedElectrons
process.p += process.acceptedMuons
process.p += process.patElectronFilter
process.p += process.patMuonFilter

# top projections in PF2PAT:
getattr(process,"pfNoPileUp"+postfix).enable = True
getattr(process,"pfNoMuon"+postfix).enable = True
getattr(process,"pfNoElectron"+postfix).enable = True
getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
getattr(process,"pfNoJet"+postfix).enable = True

process.MessageLogger.cerr.FwkReport.reportEvery = 100
