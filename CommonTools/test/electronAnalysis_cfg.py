import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")
process.load("KoPFA.CommonTools.eventFilter_cfi")
process.load("KoPFA.CommonTools.ZFilter_cfi")
process.load("KoPFA.CommonTools.patElectronAnalyzer_cfi")

process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.JetEnergyScale.globalTag = cms.untracked.string('GR_R_42_V23')
process.JetEnergyScale.doResJec = cms.untracked.bool(True)

process.BaseSequence = cms.Sequence(
    process.nEventsPatHLT*
    process.EventFilter*
    process.nEventsFilter*
    process.topWLeptonGenFilter*
    process.GenZmassFilter*
    process.PUweight*
    process.JetEnergyScale*
    process.Electrons*
    process.Muons
)


#############This is only for CMG patTuple########################
process.Muons.muonLabel  = cms.InputTag("patMuonsWithTrigger")
process.Electrons.usepflow = cms.untracked.bool( False )
process.Electrons.mvacut = cms.untracked.double( 0.0 )
process.Electrons.usemva = cms.untracked.bool( True )
process.Electrons.electronLabel  = cms.InputTag("patElectronsWithTrigger")
process.Electrons.eidName = cms.untracked.string("mvaTrigV0")
process.JetEnergyScale.rhoLabel = cms.InputTag('kt6PFJets','rho')
process.JetEnergyScale.jetLabel = cms.InputTag('selectedPatJetsCHS')
process.JetEnergyScale.metLabel = cms.InputTag('patMETs')
###################################################################

from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet
process.BaseSequenceMuMu = cloneProcessingSnippet(process, process.BaseSequence, 'MuMu')
process.BaseSequenceMuEl = cloneProcessingSnippet(process, process.BaseSequence, 'MuEl')
process.BaseSequenceElEl = cloneProcessingSnippet(process, process.BaseSequence, 'ElEl')

process.p3 = cms.Path(
    process.BaseSequenceElEl*
    process.ElectronAnalysis
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)

#Data
#process.load("KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012ADoubleMu_cff")
process.load("KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012ADoubleElectron_cff")
#MC
#process.load("KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_TTbarTuneZ2_cff")

runOnMC = False
TTbar = True
TTbarOthers = False
ZJets = False
ZtauDecay = False

from CMGTools.Common.Tools.applyJSON_cff import applyJSON
json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-194479_8TeV_PromptReco_Collisions12_JSON.txt'
if not runOnMC:
    applyJSON(process, json )

##### This is only for MC ##################
if runOnMC == True:
  process.JetEnergyScale.globalTag = cms.untracked.string('START42_V17')
  process.JetEnergyScale.doResJec = cms.untracked.bool(False)

  if ZJets == True: 
    process.GenZmassFilter.applyFilter = True
    process.GenZmassFilter.decayMode = [11, 13]
  if ZtauDecay == True:
    process.GenZmassFilter.applyFilter = True
    process.GenZmassFilter.decayMode = [15]
  if TTbar == True:
    process.topWLeptonGenFilter.applyFilter = True
  if TTbarOthers == True:
    process.topWLeptonGenFilter.applyFilter = True
    process.p.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)

#############################################

#############This is only for CMG patTuple#######################

process.ZMuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.ZMuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.ZMuEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.ZMuEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.ZElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ZElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')

process.MuMu.muonLabel1 =  cms.InputTag('MuonsMuMu')
process.MuMu.muonLabel2 =  cms.InputTag('MuonsMuMu')
process.MuMu.metLabel =  cms.InputTag('JetEnergyScaleMuMu','patMETs')
process.MuMu.jetLabel =  cms.InputTag('JetEnergyScaleMuMu','selectedPatJetsCHS')
process.MuMu.filters  =  cms.untracked.vstring( 
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilterMuMu',
                                             'nEventsPatHLTMuMu'
                                              )

process.MuEl.muonLabel1 =  cms.InputTag('MuonsMuEl')
process.MuEl.muonLabel2 =  cms.InputTag('ElectronsMuEl')
process.MuEl.metLabel =  cms.InputTag('JetEnergyScaleMuEl','patMETs')
process.MuEl.jetLabel =  cms.InputTag('JetEnergyScaleMuEl','selectedPatJetsCHS')
process.MuEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilterMuEl',
                                             'nEventsPatHLTMuEl'
                                              )

process.ElEl.muonLabel1 =  cms.InputTag('ElectronsElEl')
process.ElEl.muonLabel2 =  cms.InputTag('ElectronsElEl')
process.ElEl.metLabel =  cms.InputTag('JetEnergyScaleElEl','patMETs')
process.ElEl.jetLabel =  cms.InputTag('JetEnergyScaleElEl','selectedPatJetsCHS')
process.ElEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilterElEl',
                                             'nEventsPatHLTElEl'
                                              )
##################################################################

