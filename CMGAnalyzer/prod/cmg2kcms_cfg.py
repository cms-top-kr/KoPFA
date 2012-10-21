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
process.load("KoPFA.CMGAnalyzer.cmgElectronAnalyzer_cfi")
process.load("KoPFA.CMGAnalyzer.ZFilter_cfi")
from KoPFA.CommonTools.PileUpWeight_cff import *

runOnMC = True
runOn2012 = True

#Data
#process.load("KoPFA.CommonTools.Sources.CMG.V5_7_0.Run2012.cmgTuple_Run2012AElEl_cff")
#MC
process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.patTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTH_HToBB_M125_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_TTbarTuneZ2_cff")
#process.load("KoPFA.CommonTools.Sources.CMG.V5_10_0.Summer12.cmgTuple_ZJets_cff")

from CMGTools.Common.Tools.applyJSON_cff import applyJSON
json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON_v2.txt'
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

process.BaseSequence = cms.Sequence(
    process.nEventsPatHLT*
    process.EventFilter*
    process.nEventsFilter*
 #   process.topDecayGenFilter*
 #   process.GenZmassFilter*
    process.PUweight*
    process.JetEnergyScale*
    process.Electrons*
    process.Muons
)


#############This is only for CMG patTuple########################
process.topDecayGenFilter.genParticlesLabel = cms.InputTag("genParticlesPruned")
process.GenZmassFilter.genParticlesLabel = cms.InputTag("genParticlesPruned")
###################################################################

from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet
process.BaseSequenceMuMu = cloneProcessingSnippet(process, process.BaseSequence, 'MuMu')
process.BaseSequenceMuEl = cloneProcessingSnippet(process, process.BaseSequence, 'MuEl')
process.BaseSequenceElEl = cloneProcessingSnippet(process, process.BaseSequence, 'ElEl')
process.kinSolutionTtFullLepEventMuMu = process.kinSolutionTtFullLepEvent.clone()
process.kinSolutionTtFullLepEventMuEl = process.kinSolutionTtFullLepEvent.clone()
process.kinSolutionTtFullLepEventElEl = process.kinSolutionTtFullLepEvent.clone()

### Ntuple producer for dilepton ###

process.p = cms.Path(
    process.BaseSequenceMuMu*
    process.ZMuMu*
    process.kinSolutionTtFullLepEventMuMu*
    process.MuMu
)

process.p2 = cms.Path(
    process.BaseSequenceMuEl*
    process.ZMuEl*
    process.kinSolutionTtFullLepEventMuEl*
    process.MuEl
)

process.p3 = cms.Path(
    process.BaseSequenceElEl*
    process.ZElEl*
    process.kinSolutionTtFullLepEventElEl*
    process.ElEl
)

### Electron Analyzer ###

process.p4 = cms.Path(
    process.ElectronAnalysis
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

#############This is only for combining three channels#######################

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
                                             'nEventsFilterMuMu',
                                             'nEventsPatHLTMuMu'
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
                                             'nEventsFilterMuEl',
                                             'nEventsPatHLTMuEl'
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
                                             'nEventsFilterElEl',
                                             'nEventsPatHLTElEl'
                                              )
##################################################################

