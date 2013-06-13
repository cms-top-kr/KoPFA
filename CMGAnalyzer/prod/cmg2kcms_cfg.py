import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load("KoPFA.CMGAnalyzer.topAnalysis_cff")
process.load("KoPFA.CommonTools.eventFilter_cfi")
process.load("KoPFA.CMGAnalyzer.finalLeptonProducer_cfi")
process.load("KoPFA.CMGAnalyzer.cmgElectronAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.cmgMuonAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.ZFilter_cfi")
process.load("KoPFA.CMGAnalyzer.ttbar2bFilter_cfi")
process.load("KoPFA.CMGAnalyzer.topHLTfilter_cff")
from KoPFA.CommonTools.PileUpWeight_cff import *

runOnMC = True 
runOn2012 = True

#Data
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Run2012.cmgTuple_Run2012CElEl_cff")
#MC
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.patTuple_TTbarTuneZ2_cff")
process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.patTuple_TTbarFullLepMGDecays_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTH_HToBB_M125_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_ZJets_cff")


#process.source = cms.Source("PoolSource",
#  fileNames = cms.untracked.vstring(
    #pickRelValInputFiles() # <-- picks automatically RelVal input files for the current release
    #'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYmm20to50/patTuple_skim_1_1_ogh.root',
#    '/store/caf/user/tjkim/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/CMG/cmgTuple.root'
#  )
#)

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

process.JetEnergyScaleMuMu = process.JetEnergyScale.clone()
process.JetEnergyScaleMuEl = process.JetEnergyScale.clone()
process.JetEnergyScaleElEl = process.JetEnergyScale.clone()
### Ntuple producer for dilepton ###

process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)
process.goodOfflinePrimaryVerticesMuMu = process.goodOfflinePrimaryVertices.clone()
process.goodOfflinePrimaryVerticesMuEl = process.goodOfflinePrimaryVertices.clone()
process.goodOfflinePrimaryVerticesElEl = process.goodOfflinePrimaryVertices.clone()

process.p = cms.Path(
#    process.BaseSequenceMuMu*
#    process.ttbar2bFilter*
    process.hltHighLevelMuMu*
    process.nEventsPatHLTMuMu*
    process.EventFilterMuMu*
#    process.goodOfflinePrimaryVerticesMuMu*
    process.nEventsFilterMuMu*
    process.MuonsMuMu*
    process.ZMuMu*
    process.CMGFinalLeptonsMuMu*
    process.JetEnergyScaleMuMu*
#    process.kinSolutionTtFullLepEventMuMu*
#    process.maosSolutionTtFullLepEventMuMu*
    process.PUweightMuMu*
    process.MuMu
)

process.p2 = cms.Path(
#    process.BaseSequenceMuEl*
    process.hltHighLevelMuEl*
    process.nEventsPatHLTMuEl*
    process.EventFilterMuEl*
#    process.goodOfflinePrimaryVerticesMuEl*
    process.nEventsFilterMuEl*
    process.MuonsMuEl*
    process.ElectronsMuEl*
    process.ZMuEl*
    process.CMGFinalLeptonsMuEl*
    process.JetEnergyScaleMuEl*
#    process.kinSolutionTtFullLepEventMuEl*
#    process.maosSolutionTtFullLepEventMuEl*
    process.PUweightMuEl*
    process.MuEl
)

process.p3 = cms.Path(
#    process.BaseSequenceElEl*
    process.hltHighLevelElEl*
    process.nEventsPatHLTElEl*
    process.EventFilterElEl*
#    process.goodOfflinePrimaryVerticesElEl*
    process.nEventsFilterElEl*
    process.ElectronsElEl*
    process.ZElEl*
    process.CMGFinalLeptonsElEl*
    process.JetEnergyScaleElEl*
#    process.kinSolutionTtFullLepEventElEl*
#    process.maosSolutionTtFullLepEventElEl*
    process.PUweightElEl*
    process.ElEl
)

### Electron Analyzer ###

#process.p4 = cms.Path(
#    process.ElectronAnalysis
#)

#process.p5 = cms.Path(
#    process.MuonAnalysis
#)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

#############This is only for combining three channels#######################

process.kinSolutionTtFullLepEventMuMu.mumuChannel = True
process.kinSolutionTtFullLepEventMuMu.jets = cms.InputTag("JetEnergyScaleMuMu","Jets")
process.kinSolutionTtFullLepEventMuMu.electrons = cms.InputTag("CMGFinalLeptonsMuMu","Electrons")
process.kinSolutionTtFullLepEventMuMu.muons = cms.InputTag("CMGFinalLeptonsMuMu","Muons")
process.kinSolutionTtFullLepEventMuMu.mets = cms.InputTag("JetEnergyScaleMuMu","MET")
process.kinSolutionTtFullLepEventMuEl.emuChannel  = True
process.kinSolutionTtFullLepEventMuEl.jets = cms.InputTag("JetEnergyScaleMuEl","Jets")
process.kinSolutionTtFullLepEventMuEl.electrons = cms.InputTag("CMGFinalLeptonsMuEl","Electrons")
process.kinSolutionTtFullLepEventMuEl.muons = cms.InputTag("CMGFinalLeptonsMuEl","Muons")
process.kinSolutionTtFullLepEventMuEl.mets = cms.InputTag("JetEnergyScaleMuEl","MET")
process.kinSolutionTtFullLepEventElEl.eeChannel  = True
process.kinSolutionTtFullLepEventElEl.jets = cms.InputTag("JetEnergyScaleElEl","Jets")
process.kinSolutionTtFullLepEventElEl.electrons = cms.InputTag("CMGFinalLeptonsElEl","Electrons")
process.kinSolutionTtFullLepEventElEl.muons = cms.InputTag("CMGFinalLeptonsElEl","Muons")
process.kinSolutionTtFullLepEventElEl.mets = cms.InputTag("JetEnergyScaleElEl","MET")

process.maosSolutionTtFullLepEventMuMu.mumuChannel = True
process.maosSolutionTtFullLepEventMuMu.jets = cms.InputTag("JetEnergyScaleMuMu","Jets")
process.maosSolutionTtFullLepEventMuMu.electrons = cms.InputTag("CMGFinalLeptonsMuMu","Electrons")
process.maosSolutionTtFullLepEventMuMu.muons = cms.InputTag("CMGFinalLeptonsMuMu","Muons")
process.maosSolutionTtFullLepEventMuMu.mets = cms.InputTag("JetEnergyScaleMuMu","MET")
process.maosSolutionTtFullLepEventMuEl.emuChannel  = True
process.maosSolutionTtFullLepEventMuEl.jets = cms.InputTag("JetEnergyScaleMuEl","Jets")
process.maosSolutionTtFullLepEventMuEl.electrons = cms.InputTag("CMGFinalLeptonsMuEl","Electrons")
process.maosSolutionTtFullLepEventMuEl.muons = cms.InputTag("CMGFinalLeptonsMuEl","Muons")
process.maosSolutionTtFullLepEventMuEl.mets = cms.InputTag("JetEnergyScaleMuEl","MET")
process.maosSolutionTtFullLepEventElEl.eeChannel  = True
process.maosSolutionTtFullLepEventElEl.jets = cms.InputTag("JetEnergyScaleElEl","Jets")
process.maosSolutionTtFullLepEventElEl.electrons = cms.InputTag("CMGFinalLeptonsElEl","Electrons")
process.maosSolutionTtFullLepEventElEl.muons = cms.InputTag("CMGFinalLeptonsElEl","Muons")
process.maosSolutionTtFullLepEventElEl.mets = cms.InputTag("JetEnergyScaleElEl","MET")

process.JetEnergyScaleMuMu.electronLabel = cms.InputTag("CMGFinalLeptonsMuMu","Electrons")
process.JetEnergyScaleMuMu.muonLabel = cms.InputTag("CMGFinalLeptonsMuMu","Muons")

process.JetEnergyScaleMuEl.electronLabel = cms.InputTag("CMGFinalLeptonsMuEl","Electrons")
process.JetEnergyScaleMuEl.muonLabel = cms.InputTag("CMGFinalLeptonsMuEl","Muons")

process.JetEnergyScaleElEl.electronLabel = cms.InputTag("CMGFinalLeptonsElEl","Electrons")
process.JetEnergyScaleElEl.muonLabel = cms.InputTag("CMGFinalLeptonsElEl","Muons")

process.ZMuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.ZMuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.ZMuEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.ZMuEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.ZElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ZElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')

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
##################################################################

