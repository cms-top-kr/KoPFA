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

process.nEventsFilter = cms.EDProducer("EventCountProducer")

process.JetEnergyScale.globalTag = cms.untracked.string('GR_R_42_V23')
process.JetEnergyScale.doResJec = cms.untracked.bool(True)

process.p = cms.Path(
    process.EventFilter*
    process.nEventsFilter*
    process.nEventsPatHLT*
    process.topWLeptonGenFilter*
    process.GenZmassFilter*
    process.PUweight*
    process.JetEnergyScale*
    process.Electrons*
    process.Muons*
    process.ZMuMu*
    process.MuMu
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_Run2011.root')
)

#Data
process.load("KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012ADoubleMu_cff")
#MC
#process.load("KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_TTbarTuneZ2_cff")

runOnMC = True 
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
process.Muons.muonLabel  = cms.InputTag("patMuonsWithTrigger")
process.Electrons.usepflow = cms.untracked.bool( False )
process.Electrons.mvacut = cms.untracked.double( 0.0 )
process.Electrons.usemva = cms.untracked.bool( True )
process.Electrons.electronLabel  = cms.InputTag("patElectronsWithTrigger")
process.Electrons.eidName = cms.untracked.string("eidTight")
process.JetEnergyScale.rhoLabel = cms.InputTag('kt6PFJets','rho')
process.JetEnergyScale.jetLabel = cms.InputTag('selectedPatJetsCHS')
process.JetEnergyScale.metLabel = cms.InputTag('patMETs')

process.MuMu.metLabel =  cms.InputTag('JetEnergyScale','patMETs')
process.MuMu.jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS')
process.MuMu.filters  =  cms.untracked.vstring( 
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilter',
                                             'nEventsPatHLT'
                                              )

process.MuEl.metLabel =  cms.InputTag('JetEnergyScale','patMETs')
process.MuEl.jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS')
process.MuEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilter',
                                             'nEventsPatHLT'
                                              )

process.ElEl.metLabel =  cms.InputTag('JetEnergyScale','patMETs')
process.ElEl.jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsCHS')
process.ElEl.filters  =  cms.untracked.vstring(  
                                             'prePathCounter',
                                             'postPathCounter',
                                             'nEventsFilter',
                                             'nEventsPatHLT'
                                              )
##################################################################

