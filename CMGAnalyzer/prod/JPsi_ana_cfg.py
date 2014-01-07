import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options  = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'START53_V18PR::All'

process.load("KoPFA.CMGAnalyzer.topAnalysis_cff")
process.load("KoPFA.CommonTools.eventFilter_cfi")
process.load("KoPFA.CMGAnalyzer.finalLeptonProducer_cfi")
process.load("KoPFA.CMGAnalyzer.cmgElectronAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.cmgMuonAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.ZFilter_cfi")
process.load("KoPFA.CMGAnalyzer.ttbar2bFilter_cfi")
process.load("KoPFA.CMGAnalyzer.ttbarJPsiFilter_cfi") #jkim
process.load("KoPFA.CMGAnalyzer.JPsiFilter_cfi")    #jkim
process.load("KoPFA.CMGAnalyzer.topHLTfilter_cff")  
from KoPFA.CommonTools.PileUpWeight_cff import *

runOnMC = True 
runOn2012 = True

#Data
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012CElEl_cff")
#MC
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.patTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.patTuple_TTbarFullLepMGDecays_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTH_HToBB_M125_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZJets_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.LYON.patTuple_TTbarFullLepSemiLeptPYTHIA6_cff")


process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #pickRelValInputFiles() # <-- picks automatically RelVal input files for the current release
    #'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYmm20to50/patTuple_skim_1_1_ogh.root',
    #'/store/caf/user/tjkim/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/CMG/cmgTuple.root'
#    '/store/user/geonmo/JpsiMM_8TeV/JpsiMM_8TeV/ed48ad56ccaef4fbaeb1c9bf839c0fe8/JpsiMM_8TeV_RECO_100_1_QLg.root',
#    '/store/user/geonmo/JpsiMM_8TeV/JpsiMM_8TeV/ed48ad56ccaef4fbaeb1c9bf839c0fe8/JpsiMM_8TeV_RECO_10_1_rLK.root',
#    '/store/user/geonmo/JpsiMM_8TeV/JpsiMM_8TeV/ed48ad56ccaef4fbaeb1c9bf839c0fe8/JpsiMM_8TeV_RECO_271_1_aXr.root',
    'file:///pnfs/user/top/patTuple.root'
        
  )
)

from CMGTools.Common.Tools.applyJSON_cff import applyJSON
json = 'Cert_8TeV_Run2012ABCD_Golden_JSON.txt'
if not runOnMC:
    applyJSON(process, json )

if runOn2012 == True:
  #############2012 analysis######################################
  process.PUweight.PileUpRD   = PileUpRD2012
  process.PUweight.PileUpRDup = PileUpRD2012UP
  process.PUweight.PileUpRDdn = PileUpRD2012DN
  process.PUweight.PileUpMC   = Summer12

process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.load("KoPFA.CMGAnalyzer.TtFullLepKinSolutionProducer_cfi")
process.load("KoPFA.CMGAnalyzer.TtFullLepMaosSolutionProducer_cfi")

#process.BaseSequence = cms.Sequence(
 #   process.ttbar2bFilter*
 #   process.EventFilter*
 #   process.nEventsFilter*
 #   process.topDecayGenFilter*
 #   process.GenZmassFilter*
 #   process.PUweight
 #   process.JetEnergyScale*
 #   process.Electrons*
 #   process.Muons
#)

#############This is only for CMG patTuple########################
process.topDecayGenFilter.genParticlesLabel = cms.InputTag("genParticlesPruned")
process.GenZmassFilter.genParticlesLabel = cms.InputTag("genParticlesPruned")
###################################################################

from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet
#process.BaseSequenceMuMu = cloneProcessingSnippet(process, process.BaseSequence, 'MuMu')
#process.BaseSequenceMuEl = cloneProcessingSnippet(process, process.BaseSequence, 'MuEl')
#process.BaseSequenceElEl = cloneProcessingSnippet(process, process.BaseSequence, 'ElEl')

process.EventFilterMuMu = process.EventFilter.clone()
process.EventFilterMuEl = process.EventFilter.clone()
process.EventFilterElEl = process.EventFilter.clone()
process.nEventsFilterMuMu = process.nEventsFilter.clone()
process.nEventsFilterMuEl = process.nEventsFilter.clone()
process.nEventsFilterElEl = process.nEventsFilter.clone()
process.PUweightMuMu = process.PUweight.clone()
process.PUweightMuEl = process.PUweight.clone()
process.PUweightElEl = process.PUweight.clone()

process.MuonsMuMu = process.Muons.clone()
process.MuonsMuEl = process.Muons.clone()
process.MuonsElEl = process.Muons.clone() #jkim
process.ElectronsMuMu = process.Electrons.clone() #jkim
process.ElectronsMuEl = process.Electrons.clone()
process.ElectronsElEl = process.Electrons.clone()

process.nEventsPatHLTMuMu = process.nEventsPatHLT.clone()
process.nEventsPatHLTMuEl = process.nEventsPatHLT.clone()
process.nEventsPatHLTElEl = process.nEventsPatHLT.clone()

process.kinSolutionTtFullLepEventMuMu = process.kinSolutionTtFullLepEvent.clone()
process.kinSolutionTtFullLepEventMuEl = process.kinSolutionTtFullLepEvent.clone()
process.kinSolutionTtFullLepEventElEl = process.kinSolutionTtFullLepEvent.clone()

process.maosSolutionTtFullLepEventMuMu = process.maosSolutionTtFullLepEvent.clone()
process.maosSolutionTtFullLepEventMuEl = process.maosSolutionTtFullLepEvent.clone()
process.maosSolutionTtFullLepEventElEl = process.maosSolutionTtFullLepEvent.clone()

process.CMGFinalLeptonsMuMu = process.CMGFinalLeptons.clone()
process.CMGFinalLeptonsMuEl = process.CMGFinalLeptons.clone()
process.CMGFinalLeptonsElEl = process.CMGFinalLeptons.clone()

process.CMGFinalLeptonsMuMuJPsiMuMu = process.CMGFinalLeptons.clone() #jkim
process.CMGFinalLeptonsMuMuJPsiElEl = process.CMGFinalLeptons.clone() #jkim
process.CMGFinalLeptonsMuElJPsiMuMu = process.CMGFinalLeptons.clone() #jkim
process.CMGFinalLeptonsMuElJPsiElEl = process.CMGFinalLeptons.clone() #jkim
process.CMGFinalLeptonsElElJPsiMuMu = process.CMGFinalLeptons.clone() #jkim
process.CMGFinalLeptonsElElJPsiElEl = process.CMGFinalLeptons.clone() #jkim

process.JetEnergyScaleMuMu = process.JetEnergyScale.clone()
process.JetEnergyScaleMuEl = process.JetEnergyScale.clone()
process.JetEnergyScaleElEl = process.JetEnergyScale.clone()

process.JetEnergyScaleMuMuJPsiMuMu = process.JetEnergyScale.clone() #jkim
process.JetEnergyScaleMuMuJPsiElEl = process.JetEnergyScale.clone() #jkim
process.JetEnergyScaleMuElJPsiMuMu = process.JetEnergyScale.clone() #jkim
process.JetEnergyScaleMuElJPsiElEl = process.JetEnergyScale.clone() #jkim
process.JetEnergyScaleElElJPsiMuMu = process.JetEnergyScale.clone() #jkim
process.JetEnergyScaleElElJPsiElEl = process.JetEnergyScale.clone() #jkim

### Ntuple producer for dilepton ###

process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)
process.goodOfflinePrimaryVerticesMuMu = process.goodOfflinePrimaryVertices.clone()
process.goodOfflinePrimaryVerticesMuEl = process.goodOfflinePrimaryVertices.clone()
process.goodOfflinePrimaryVerticesElEl = process.goodOfflinePrimaryVertices.clone()

#process.p = cms.Path(
##    process.BaseSequenceMuMu*
#    process.hltHighLevelMuMu*
#    process.nEventsPatHLTMuMu*
#    process.EventFilterMuMu*
##    process.goodOfflinePrimaryVerticesMuMu*
#    process.nEventsFilterMuMu*
#    process.MuonsMuMu*
#    process.ZMuMu*
#    process.CMGFinalLeptonsMuMu*
#    process.JetEnergyScaleMuMu*
##    process.kinSolutionTtFullLepEventMuMu*
##    process.maosSolutionTtFullLepEventMuMu*
#    process.PUweightMuMu*
#    process.MuMu
#)

#process.p2 = cms.Path(
##    process.BaseSequenceMuEl*
#    process.hltHighLevelMuEl*
#    process.nEventsPatHLTMuEl*
#    process.EventFilterMuEl*
##    process.goodOfflinePrimaryVerticesMuEl*
#    process.nEventsFilterMuEl*
#    process.MuonsMuEl*
#    process.ElectronsMuEl*
#    process.ZMuEl*
#    process.CMGFinalLeptonsMuEl*
#    process.JetEnergyScaleMuEl*
##    process.kinSolutionTtFullLepEventMuEl*
##    process.maosSolutionTtFullLepEventMuEl*
#    process.PUweightMuEl*
#    process.MuEl
#)

#process.p3 = cms.Path(
##    process.BaseSequenceElEl*
#    process.hltHighLevelElEl*
#    process.nEventsPatHLTElEl*
#    process.EventFilterElEl*
##    process.goodOfflinePrimaryVerticesElEl*
#    process.nEventsFilterElEl*
#    process.ElectronsElEl*
#    process.ZElEl*
#    process.CMGFinalLeptonsElEl*
#    process.JetEnergyScaleElEl*
##    process.kinSolutionTtFullLepEventElEl*
##    process.maosSolutionTtFullLepEventElEl*
#    process.PUweightElEl*
#    process.ElEl
#)

#MuMu+JPsi->MuMu
process.p4 = cms.Path(
#    process.BaseSequenceMuMu*
    #process.ttbarJPsiFilter*
    process.hltHighLevelMuMu*
    process.nEventsPatHLTMuMu*
    process.EventFilterMuMu*
#    process.goodOfflinePrimaryVerticesMuMu*
    process.nEventsFilterMuMu*
    process.MuonsMuMu*
    process.MuMuJPsiMuMu*
    process.CMGFinalLeptonsMuMuJPsiMuMu*
    process.JetEnergyScaleMuMuJPsiMuMu*
#    process.kinSolutionTtFullLepEventMuMu*
#    process.maosSolutionTtFullLepEventMuMu*
    process.PUweightMuMu*
    process.MuMu2Mu
)

#process.p5 = cms.Path(
##    process.BaseSequenceMuMu*
#    process.hltHighLevelMuMu*
#    process.nEventsPatHLTMuMu*
#    process.EventFilterMuMu*
##    process.goodOfflinePrimaryVerticesMuMu*
#    process.nEventsFilterMuMu*
#    process.MuonsMuMu*
#    process.ElectronsMuMu*
#    process.MuMuJPsiElEl*
#    process.CMGFinalLeptonsMuMuJPsiElEl*
#    process.JetEnergyScaleMuMuJPsiElEl*
##    process.kinSolutionTtFullLepEventMuMu*
##    process.maosSolutionTtFullLepEventMuMu*
#    process.PUweightMuMu*
#    process.MuMu2El
#)

#MuEl+JPsi->MuMu
process.p6 = cms.Path(
#    process.BaseSequenceMuEl*
    #process.ttbarJPsiFilter*
    process.hltHighLevelMuEl*
    process.nEventsPatHLTMuEl*
    process.EventFilterMuEl*
#    process.goodOfflinePrimaryVerticesMuEl*
    process.nEventsFilterMuEl*
    process.MuonsMuEl*
    process.ElectronsMuEl*
    process.MuElJPsiMuMu*
    process.CMGFinalLeptonsMuElJPsiMuMu*
    process.JetEnergyScaleMuElJPsiMuMu*
#    process.kinSolutionTtFullLepEventMuEl*
#    process.maosSolutionTtFullLepEventMuEl*
    process.PUweightMuEl*
    process.MuEl2Mu
)

#process.p7 = cms.Path(
##    process.BaseSequenceMuEl*
#    process.hltHighLevelMuEl*
#    process.nEventsPatHLTMuEl*
#    process.EventFilterMuEl*
##    process.goodOfflinePrimaryVerticesMuEl*
#    process.nEventsFilterMuEl*
#    process.MuonsMuEl*
#    process.ElectronsMuEl*
#    process.MuElJPsiElEl*
#    process.CMGFinalLeptonsMuElJPsiElEl*
#    process.JetEnergyScaleMuElJPsiElEl*
##    process.kinSolutionTtFullLepEventMuEl*
##    process.maosSolutionTtFullLepEventMuEl*
#    process.PUweightMuEl*
#    process.MuEl2El
#)

#ElEl+JPsi->MuMu
process.p8 = cms.Path(
#    process.BaseSequenceElEl*
    #process.ttbarJPsiFilter*
    process.hltHighLevelElEl*
    process.nEventsPatHLTElEl*
    process.EventFilterElEl*
#    process.goodOfflinePrimaryVerticesElEl*
    process.nEventsFilterElEl*
    process.ElectronsElEl*
    process.ElElJPsiMuMu*
    process.CMGFinalLeptonsElElJPsiMuMu*
    process.JetEnergyScaleElElJPsiMuMu*
#    process.kinSolutionTtFullLepEventElEl*
#    process.maosSolutionTtFullLepEventElEl*
    process.PUweightElEl*
    process.ElEl2Mu
)

#process.p9 = cms.Path(
##    process.BaseSequenceElEl*
#    process.hltHighLevelElEl*
#    process.nEventsPatHLTElEl*
#    process.EventFilterElEl*
##    process.goodOfflinePrimaryVerticesElEl*
#    process.nEventsFilterElEl*
#    process.ElectronsElEl*
#    process.ElElJPsiElEl*
#    process.CMGFinalLeptonsElElJPsiElEl*
#    process.JetEnergyScaleElElJPsiElEl*
##    process.kinSolutionTtFullLepEventElEl*
##    process.maosSolutionTtFullLepEventElEl*
#    process.PUweightElEl*
#    process.ElEl2El
#)

### Gen Analyzer ###
process.p10 = cms.Path(
    process.ttbarJPsiFilter
)

### Electron Analyzer ###

#process.p4 = cms.Path(
#    process.ElectronAnalysis
#)

#process.p5 = cms.Path(
#    process.MuonAnalysis
#)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_FullttbarPythia6.root')
)


process.JetEnergyScaleMuMu.electronLabel = cms.InputTag("CMGFinalLeptonsMuMu","Electrons")
process.JetEnergyScaleMuMu.muonLabel = cms.InputTag("CMGFinalLeptonsMuMu","Muons")

process.JetEnergyScaleMuEl.electronLabel = cms.InputTag("CMGFinalLeptonsMuEl","Electrons")
process.JetEnergyScaleMuEl.muonLabel = cms.InputTag("CMGFinalLeptonsMuEl","Muons")

process.JetEnergyScaleElEl.electronLabel = cms.InputTag("CMGFinalLeptonsElEl","Electrons")
process.JetEnergyScaleElEl.muonLabel = cms.InputTag("CMGFinalLeptonsElEl","Muons")

process.JetEnergyScaleMuMuJPsiMuMu.electronLabel = cms.InputTag("CMGFinalLeptonsMuMuJPsiMuMu","Electrons") #jkim
process.JetEnergyScaleMuMuJPsiMuMu.muonLabel = cms.InputTag("CMGFinalLeptonsMuMuJPsiMuMu","Muons") #jkim
process.JetEnergyScaleMuMuJPsiElEl.electronLabel = cms.InputTag("CMGFinalLeptonsMuMuJPsiElEl","Electrons") #jkim
process.JetEnergyScaleMuMuJPsiElEl.muonLabel = cms.InputTag("CMGFinalLeptonsMuMuJPsiElEl","Muons") #jkim

process.JetEnergyScaleMuElJPsiMuMu.electronLabel = cms.InputTag("CMGFinalLeptonsMuElJPsiMuMu","Electrons") #jkim
process.JetEnergyScaleMuElJPsiMuMu.muonLabel = cms.InputTag("CMGFinalLeptonsMuElJPsiMuMu","Muons") #jkim
process.JetEnergyScaleMuElJPsiElEl.electronLabel = cms.InputTag("CMGFinalLeptonsMuElJPsiElEl","Electrons") #jkim
process.JetEnergyScaleMuElJPsiElEl.muonLabel = cms.InputTag("CMGFinalLeptonsMuElJPsiElEl","Muons") #jkim

process.JetEnergyScaleElElJPsiMuMu.electronLabel = cms.InputTag("CMGFinalLeptonsElElJPsiMuMu","Electrons") #jkim
process.JetEnergyScaleElElJPsiMuMu.muonLabel = cms.InputTag("CMGFinalLeptonsElElJPsiMuMu","Muons") #jkim
process.JetEnergyScaleElElJPsiElEl.electronLabel = cms.InputTag("CMGFinalLeptonsElElJPsiElEl","Electrons") #jkim
process.JetEnergyScaleElElJPsiElEl.muonLabel = cms.InputTag("CMGFinalLeptonsElElJPsiElEl","Muons") #jkim

process.ZMuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.ZMuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.ZMuEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.ZMuEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.ZElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ZElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')

process.MuMuJPsiMuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMuJPsiMuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMuJPsiMuMu.muonLabel3 =  cms.InputTag('cmgMuonSel')
#process.MuMuJPsiMuMu.muonLabel3 =  cms.InputTag('MuonsMuMu')
process.MuMuJPsiMuMu.muonLabel4 =  cms.InputTag('cmgMuonSel')
#process.MuMuJPsiMuMu.muonLabel4 =  cms.InputTag('MuonsMuMu')

process.MuMuJPsiElEl.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMuJPsiElEl.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMuJPsiElEl.muonLabel3 =  cms.InputTag('cmgElectronSel')
#process.MuMuJPsiElEl.muonLabel3 =  cms.InputTag('ElectronsMuMu')
process.MuMuJPsiElEl.muonLabel4 =  cms.InputTag('cmgElectronSel')
#process.MuMuJPsiElEl.muonLabel4 =  cms.InputTag('ElectronsMuMu')

process.MuElJPsiMuMu.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuElJPsiMuMu.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuElJPsiMuMu.muonLabel3 =  cms.InputTag('cmgMuonSel')
#process.MuElJPsiMuMu.muonLabel3 =  cms.InputTag('MuonsMuEl')
process.MuElJPsiMuMu.muonLabel4 =  cms.InputTag('cmgMuonSel')
#process.MuElJPsiMuMu.muonLabel4 =  cms.InputTag('MuonsMuEl')

process.MuElJPsiElEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuElJPsiElEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuElJPsiElEl.muonLabel3 =  cms.InputTag('cmgElectronSel')
#process.MuElJPsiElEl.muonLabel3 =  cms.InputTag('ElectronsMuEl')
process.MuElJPsiElEl.muonLabel4 =  cms.InputTag('cmgElectronSel')
#process.MuElJPsiElEl.muonLabel4 =  cms.InputTag('ElectronsMuEl')

process.ElElJPsiMuMu.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElElJPsiMuMu.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElElJPsiMuMu.muonLabel3 =  cms.InputTag('cmgMuonSel')
#process.ElElJPsiMuMu.muonLabel3 =  cms.InputTag('MuonsElEl')
process.ElElJPsiMuMu.muonLabel4 =  cms.InputTag('cmgMuonSel')
#process.ElElJPsiMuMu.muonLabel4 =  cms.InputTag('MuonsElEl')

process.ElElJPsiElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElElJPsiElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElElJPsiElEl.muonLabel3 =  cms.InputTag('cmgElectronSel')
#process.ElElJPsiElEl.muonLabel3 =  cms.InputTag('ElectronElEl')
process.ElElJPsiElEl.muonLabel4 =  cms.InputTag('cmgElectronSel')
#process.ElElJPsiElEl.muonLabel4 =  cms.InputTag('ElectronElEl')

process.MuMu.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuMu.genJetsLabel = cms.InputTag('genJetSel')
process.MuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMu.metLabel =  cms.InputTag('JetEnergyScaleMuMu','MET')
process.MuMu.jetLabel =  cms.InputTag('JetEnergyScaleMuMu','Jets')
process.MuMu.puWeightLabel = cms.InputTag('PUweightMuMu','weight')
process.MuMu.puUpWeightLabel = cms.InputTag('PUweightMuMu','weightplus')
process.MuMu.puDwWeightLabel = cms.InputTag('PUweightMuMu','weightminus')
process.MuMu.puNVertexLabel = cms.InputTag('PUweightMuMu','npileup')
process.MuMu.filters  =  cms.untracked.vstring( 
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuMu',
                                             'nEventsFilterMuMu',
                                              )

process.MuEl.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuEl.genJetsLabel = cms.InputTag('genJetSel')
process.MuEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuEl.metLabel =  cms.InputTag('JetEnergyScaleMuEl','MET')
process.MuEl.jetLabel =  cms.InputTag('JetEnergyScaleMuEl','Jets')
process.MuEl.puWeightLabel = cms.InputTag('PUweightMuEl','weight')
process.MuEl.puUpWeightLabel = cms.InputTag('PUweightMuEl','weightplus')
process.MuEl.puDwWeightLabel = cms.InputTag('PUweightMuEl','weightminus')
process.MuEl.puNVertexLabel = cms.InputTag('PUweightMuEl','npileup')
process.MuEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuEl',
                                             'nEventsFilterMuEl',
                                              )

process.ElEl.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.ElEl.genJetsLabel = cms.InputTag('genJetSel')
process.ElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElEl.metLabel =  cms.InputTag('JetEnergyScaleElEl','MET')
process.ElEl.jetLabel =  cms.InputTag('JetEnergyScaleElEl','Jets')
process.ElEl.puWeightLabel = cms.InputTag('PUweightElEl','weight')
process.ElEl.puUpWeightLabel = cms.InputTag('PUweightElEl','weightplus')
process.ElEl.puDwWeightLabel = cms.InputTag('PUweightElEl','weightminus')
process.ElEl.puNVertexLabel = cms.InputTag('PUweightElEl','npileup')
process.ElEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTElEl',
                                             'nEventsFilterElEl',
                                              )
################################################################################

process.MuMu2Mu.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuMu2Mu.genJetsLabel = cms.InputTag('genJetSel')
process.MuMu2Mu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMu2Mu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMu2Mu.muonLabel3 =  cms.InputTag('MuMuJPsiMuMu','Lepton3')
process.MuMu2Mu.muonLabel4 =  cms.InputTag('MuMuJPsiMuMu','Lepton4')
process.MuMu2Mu.metLabel =  cms.InputTag('JetEnergyScaleMuMuJPsiMuMu','MET')
process.MuMu2Mu.jetLabel =  cms.InputTag('JetEnergyScaleMuMuJPsiMuMu','Jets')
process.MuMu2Mu.puWeightLabel = cms.InputTag('PUweightMuMu','weight')
process.MuMu2Mu.puUpWeightLabel = cms.InputTag('PUweightMuMu','weightplus')
process.MuMu2Mu.puDwWeightLabel = cms.InputTag('PUweightMuMu','weightminus')
process.MuMu2Mu.puNVertexLabel = cms.InputTag('PUweightMuMu','npileup')
process.MuMu2Mu.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuMu',
                                             'nEventsFilterMuMu',
                                              )

process.MuMu2El.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuMu2El.genJetsLabel = cms.InputTag('genJetSel')
process.MuMu2El.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMu2El.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMu2El.muonLabel3 =  cms.InputTag('MuMuJPsiElEl','Lepton3')
process.MuMu2El.muonLabel4 =  cms.InputTag('MuMuJPsiElEl','Lepton4')
process.MuMu2El.metLabel =  cms.InputTag('JetEnergyScaleMuMuJPsiElEl','MET')
process.MuMu2El.jetLabel =  cms.InputTag('JetEnergyScaleMuMuJPsiElEl','Jets')
process.MuMu2El.puWeightLabel = cms.InputTag('PUweightMuMu','weight')
process.MuMu2El.puUpWeightLabel = cms.InputTag('PUweightMuMu','weightplus')
process.MuMu2El.puDwWeightLabel = cms.InputTag('PUweightMuMu','weightminus')
process.MuMu2El.puNVertexLabel = cms.InputTag('PUweightMuMu','npileup')
process.MuMu2El.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuMu',
                                             'nEventsFilterMuMu',
                                              )

process.MuEl2Mu.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuEl2Mu.genJetsLabel = cms.InputTag('genJetSel')
process.MuEl2Mu.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuEl2Mu.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuEl2Mu.muonLabel3 =  cms.InputTag('MuElJPsiMuMu','Lepton3')
process.MuEl2Mu.muonLabel4 =  cms.InputTag('MuElJPsiMuMu','Lepton4')
process.MuEl2Mu.metLabel =  cms.InputTag('JetEnergyScaleMuElJPsiMuMu','MET')
process.MuEl2Mu.jetLabel =  cms.InputTag('JetEnergyScaleMuElJPsiMuMu','Jets')
process.MuEl2Mu.puWeightLabel = cms.InputTag('PUweightMuEl','weight')
process.MuEl2Mu.puUpWeightLabel = cms.InputTag('PUweightMuEl','weightplus')
process.MuEl2Mu.puDwWeightLabel = cms.InputTag('PUweightMuEl','weightminus')
process.MuEl2Mu.puNVertexLabel = cms.InputTag('PUweightMuEl','npileup')
process.MuEl2Mu.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuEl',
                                             'nEventsFilterMuEl',
                                              )

process.MuEl2El.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.MuEl2El.genJetsLabel = cms.InputTag('genJetSel')
process.MuEl2El.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuEl2El.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuEl2El.muonLabel3 =  cms.InputTag('MuElJPsiElEl','Lepton3')
process.MuEl2El.muonLabel4 =  cms.InputTag('MuElJPsiElEl','Lepton4')
process.MuEl2El.metLabel =  cms.InputTag('JetEnergyScaleMuElJPsiElEl','MET')
process.MuEl2El.jetLabel =  cms.InputTag('JetEnergyScaleMuElJPsiElEl','Jets')
process.MuEl2El.puWeightLabel = cms.InputTag('PUweightMuEl','weight')
process.MuEl2El.puUpWeightLabel = cms.InputTag('PUweightMuEl','weightplus')
process.MuEl2El.puDwWeightLabel = cms.InputTag('PUweightMuEl','weightminus')
process.MuEl2El.puNVertexLabel = cms.InputTag('PUweightMuEl','npileup')
process.MuEl2El.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTMuEl',
                                             'nEventsFilterMuEl',
                                              )

process.ElEl2Mu.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.ElEl2Mu.genJetsLabel = cms.InputTag('genJetSel')
process.ElEl2Mu.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElEl2Mu.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElEl2Mu.muonLabel3 =  cms.InputTag('ElElJPsiMuMu','Lepton3')
process.ElEl2Mu.muonLabel4 =  cms.InputTag('ElElJPsiMuMu','Lepton4')
process.ElEl2Mu.metLabel =  cms.InputTag('JetEnergyScaleElElJPsiMuMu','MET')
process.ElEl2Mu.jetLabel =  cms.InputTag('JetEnergyScaleElElJPsiMuMu','Jets')
process.ElEl2Mu.puWeightLabel = cms.InputTag('PUweightElEl','weight')
process.ElEl2Mu.puUpWeightLabel = cms.InputTag('PUweightElEl','weightplus')
process.ElEl2Mu.puDwWeightLabel = cms.InputTag('PUweightElEl','weightminus')
process.ElEl2Mu.puNVertexLabel = cms.InputTag('PUweightElEl','npileup')
process.ElEl2Mu.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTElEl',
                                             'nEventsFilterElEl',
                                              )

process.ElEl2El.genParticlesLabel = cms.InputTag('genParticlesPruned')
process.ElEl2El.genJetsLabel = cms.InputTag('genJetSel')
process.ElEl2El.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElEl2El.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElEl2El.muonLabel3 =  cms.InputTag('ElElJPsiElEl','Lepton3')
process.ElEl2El.muonLabel4 =  cms.InputTag('ElElJPsiElEl','Lepton3')
process.ElEl2El.metLabel =  cms.InputTag('JetEnergyScaleElElJPsiElEl','MET')
process.ElEl2El.jetLabel =  cms.InputTag('JetEnergyScaleElElJPsiElEl','Jets')
process.ElEl2El.puWeightLabel = cms.InputTag('PUweightElEl','weight')
process.ElEl2El.puUpWeightLabel = cms.InputTag('PUweightElEl','weightplus')
process.ElEl2El.puDwWeightLabel = cms.InputTag('PUweightElEl','weightminus')
process.ElEl2El.puNVertexLabel = cms.InputTag('PUweightElEl','npileup')
process.ElEl2El.filters  =  cms.untracked.vstring(
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsPatHLTElEl',
                                             'nEventsFilterElEl',
                                              )

##################################################################

