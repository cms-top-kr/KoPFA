import FWCore.ParameterSet.Config as cms


process = cms.Process("PAT")

# Starting with a skeleton process which gets imported with the following line
#from PhysicsTools.PatAlgos.patTemplate_cfg import *


## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load("PhysicsTools.PFCandProducer.PF2PAT_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))


# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1000)
        )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/WmunuSpring10/24BF0D12-DF46-DF11-BA71-001D0968F2F6.root')
'/store/data/Run2010A/Mu/RECO/Jul6thReReco_v1/0054/FCC806C9-7D89-DF11-8666-0022649F01AA.root')
#'/store/relval/CMSSW_3_6_1_patch1/RelValTTbar/GEN-SIM-RECO/START36_V8-v1/0000/DA3B2785-F462-DF11-B39C-0030487C5CE2.root'    )
)                            
#pat event CONTENT
from Configuration.EventContent.EventContent_cff import AODEventContent

process.out = cms.OutputModule("PoolOutputModule",
    AODEventContent,    
     fileName = cms.untracked.string('PF2PAT_SDMUON_GOODCOLL_PFMuonFilter.root'),
     )


process.outMuonFilter = cms.OutputModule("PoolOutputModule",
    AODEventContent,    
     fileName = cms.untracked.string('PF2PAT_SDMUON_GOODCOLL_MuonFilter.root'),
     )

#run36xOn35xInput =False 
#runOnData = True 
#if run36xOn35xInput:
#    from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *  
#    run36xOn35xInput(process)

#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
postfix = "PFlow"
usePF2PAT(process,runPF2PAT=True, jetAlgo='AK5', runOnMC=False, postfix=postfix)
removeMCMatching(process, ['All'] )

#DATA SPECIFIC
process.GlobalTag.globaltag = cms.string('GR09_R_35X_V4::All')

#from PhysicsTools.PatAlgos.tools.jetTools import *
#switchJECSet(process,"Spring10")
#switchJECSet(process,"Summer09_7TeV")
process.patJets.addTagInfos = False



#REMOVE ISOLATION FROM PF2PAT!!!
process.pfIsolatedMuons.isolationCuts        = cms.vdouble(9999.,9999.,9999.)
process.pfIsolatedMuons.combinedIsolationCut = cms.double(9999.)

#Lower the jet min pT to 5 GeV
process.pfJets.ptMin = 5

#Lower the muon pT to 0 GeV
process.pfMuonsPtGt5.ptMin = 0.0

#Embed PFCandidates in the patMuons and patElectrons
process.patMuonsPFlow.embedPFCandidate = cms.bool(True)


#Removing the taus from the PF2PAT list
process.pfTaus.discriminators = cms.VPSet( 
    cms.PSet( discriminator=cms.InputTag("pfTausBaseDiscriminationByLeadingPionPtCut"),
    selectionCut=cms.double(10.) ),
    )
        
##################################################################

#LOAD THE HLT
#process.load("PFAnalyses.W.hltSelection_cfi")

#LOAD THE W creation(Combines mu+MET applies basic cuts on the trigger acceptance, it includes also the statupSequence)
#process.ipMuons.src =  cms.InputTag("selectedPatMuonsPFlow")


##################################################################
#Skim on GOODCOLLISION EVENTS
import HLTrigger.HLTfilters.hltHighLevelDev_cfi

process.Mu_1e28 = HLTrigger.HLTfilters.hltHighLevelDev_cfi.hltHighLevelDev.clone(andOr = True)
process.Mu_1e28.HLTPaths = cms.vstring(
'HLT_L2Mu9',
'HLT_Mu9'
)

process.Mu_1e28.HLTPathsPrescales  = cms.vuint32(1,1)
process.Mu_1e28.HLTOverallPrescale = cms.uint32(1)
process.Mu_1e28.throw = False
process.Mu_1e28.andOr = True

process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)


process.noscraping = cms.EDFilter("FilterOutScraping",
applyfilter = cms.untracked.bool(True),
debugOn = cms.untracked.bool(False),
numtrack = cms.untracked.uint32(10),
thresh = cms.untracked.double(0.25)
)

process.goodvertex=cms.Path(process.primaryVertexFilter+process.noscraping)

#PATMUON Selector
#Here we define the muon selectors
process.load("KoPFA.CommonTools.MuonSelector_cfi")
   
process.pfmuonFilter = cms.Path(
                             process.primaryVertexFilter
                             +process.noscraping
#                            process.Mu_1e28
                             +process.acceptedMuonsPFlow
                             +process.PFMuons
                             +process.patPFMuonFilter)

process.muonFilter = cms.Path(
                             process.primaryVertexFilter
                             +process.noscraping
#                             process.Mu_1e28
                             +process.acceptedMuons
                             +process.Muons
                             +process.patMuonFilter)

##################################################################


#ADDING THE TRIGGER INFORMATION IN THE PF2PAT+PAT OUTPUT FILE
#from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.load("Configuration.EventContent.EventContent_cff") 
process.ModifiedPF2PATEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
    # Gen information
    'keep *_generalTracks_*_*',    
    'keep *_electronGsfTracks_*_*',    
    'keep *_genParticles_*_*',
    'keep *_generator_*_*',
    'keep *_genMetTrue_*_*',
    'keep recoGenJets_*_*_*',
    'keep recoGsfElectronCores_gsfElectronCores_*_*', 
    # isolated electrons and muons
    'keep patMuons_*_*_*',
    'keep patElectrons_*_*_*',
    'keep patJets_*_*_*',
    'keep patTaus_*_*_*',
    'keep patMETs_*_*_*',
    'keep *_patMuonsWithMesonVeto*_*_*',    
    'keep *_MEtoEDMConverter_*_*',
   'keep *_randomCones_*_*',
    # Trigger
    'keep *_TriggerResults_*_*',
    'keep *_hltTriggerSummaryAOD_*_*',
    'keep *_pfElectronTranslator_*_*',
    'keep patTriggerObjects_patTrigger_*_*', 
    'keep patTriggerFilters_patTrigger_*_*', 
    'keep patTriggerPaths_patTrigger_*_*', 
    'keep patTriggerEvent_patTriggerEvent_*_*', 
    'keep patTriggerObjectsedmAssociation_patTriggerEvent_*_*', 
    
          )
)

process.out.outputCommands.extend(process.AODEventContent.outputCommands)
process.out.outputCommands.extend(process.ModifiedPF2PATEventContent.outputCommands)
process.outMuonFilter.outputCommands.extend(process.AODEventContent.outputCommands)
process.outMuonFilter.outputCommands.extend(process.ModifiedPF2PATEventContent.outputCommands)

#Select events
process.out.SelectEvents = cms.untracked.PSet(
#SelectEvents = cms.vstring('goodvertex','l1tcollpath')
SelectEvents = cms.vstring('pfmuonFilter') #When running on SD no need to have a further L1 requirement
)

#Select events
process.outMuonFilter.SelectEvents = cms.untracked.PSet(
SelectEvents = cms.vstring('muonFilter') #When running on SD no need to have a further L1 requirement
)

#Adding random cones
#process.load("PFAnalyses.CommonTools.RandomCone_cfi")
#process.randomCones.muonLabel = cms.InputTag("selectedPatMuonsPFlow")
#process.load("PFAnalyses.W.countingSequences_cfi")
process.load("KoPFA/CommonTools/EventInfo_cfi")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

process.TotalEventInfo = cms.Path(process.EventInfo)

process.DiMuonPFlow = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('PFMuons'),
)

process.DiMuon = cms.EDAnalyzer('DiMuonAnalyzer',
  muonLabel =  cms.InputTag('Muons'),
)

process.DiMuonAnalPFlow = cms.Path(
                              process.acceptedMuonsPFlow
                             +process.PFMuons
                             +process.patPFMuonFilter
                             +process.DiMuonPFlow
                             )

process.DiMuonAnal = cms.Path(
                              process.acceptedMuons
                             +process.Muons
                             +process.patMuonFilter
                             +process.DiMuon
                             )

process.p = cms.Path(
#         process.startupSequence*
process.patDefaultSequence*
getattr(process,"patPF2PATSequence"+postfix)
#         process.postPF2PAT*
#         process.randomCones*
#        process.patRecoMuonSequence*
#         process.selectWtoMuNu
    )

process.e = cms.EndPath(
#    process.saveHistosInRunInfo* #SAVE THE counters
    process.out*
    process.outMuonFilter
)


process.schedule = cms.Schedule(#process.l1tcollpath,
                                process.TotalEventInfo,
                                process.goodvertex,                            
                                process.p,
                                process.muonFilter,
                                process.pfmuonFilter,
                                process.DiMuonAnal,
                                process.DiMuonAnalPFlow,
#                                process.e
                               )

process.MessageLogger.cerr.FwkReport.reportEvery = 100
