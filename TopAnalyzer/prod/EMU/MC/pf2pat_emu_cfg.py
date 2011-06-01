import FWCore.ParameterSet.Config as cms

from KoPFA.TopAnalyzer.pf2pat_template_cfg import *
from KoPFA.TopAnalyzer.eventContent_cff import *
from KoPFA.TopAnalyzer.tools import *

postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=True, postfix=postfix)

#change cone size
changeConeSize(process)

#FastJet!
applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

# output
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.patMuonFilter.minNumber = 1 
process.patElectronFilter.minNumber = 1

## Source
#process.source = cms.Source("PoolSource",
#                                fileNames = cms.untracked.vstring(
#  '/store/data/Run2011A/DoubleMu/RECO/PromptReco-v1/000/161/312/9CD2FBA7-E557-E011-B433-001D09F29849.root',
#  '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/0E8D9A70-E857-E011-B3DC-001D09F29321.root',
#  '/store/data/Run2011A/MuEG/AOD/PromptReco-v1/000/161/312/04850A2C-F757-E011-9A74-003048F024DC.root'
#  )
#)

#process.p += process.hltHighLevelMuElMC
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.looseLeptonSequence
process.p += process.acceptedElectrons
process.p += process.acceptedMuons
process.p += process.patElectronFilter
process.p += process.patMuonFilter
process.p += process.nEventsFiltered

