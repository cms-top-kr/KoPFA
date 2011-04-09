import FWCore.ParameterSet.Config as cms

from KoPFA.TopAnalyzer.pf2pat_template_cfg import *

postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(999)
process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(999)

## Source
# MC sample will be taken automatically from template file
process.source.fileNames = [ ## 
'/store/relval/CMSSW_4_1_3/RelValZMM/GEN-SIM-RECO/START311_V2-v1/0037/EEB7C520-C751-E011-94C9-0030486790BE.root' ]

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHighLevel.HLTPaths = cms.vstring()
process.hltHighLevel.throw = cms.bool(False)
process.load("KoPFA.TopAnalyzer.triggerFilterByRun_cfi")

process.acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 20 && abs(eta) < 2.4")
)

process.patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(2)
)

#process.p += process.muonTriggerFilterByRun 
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.acceptedMuons
process.p += process.patMuonFilter
process.out.outputCommands += cms.untracked.vstring(*patExtraAodEventContent)

# top projections in PF2PAT:
getattr(process,"pfNoPileUp"+postfix).enable = True
getattr(process,"pfNoMuon"+postfix).enable = True
getattr(process,"pfNoElectron"+postfix).enable = True
getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
getattr(process,"pfNoJet"+postfix).enable = True

process.MessageLogger.cerr.FwkReport.reportEvery = 100
