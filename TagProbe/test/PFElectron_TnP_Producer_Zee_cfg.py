import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

## Include ##
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring('patElectronTrigger')
process.MessageLogger.suppressInfo = cms.untracked.vstring('patElectronTrigger')


from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
#from KoPFA.TagProbe.Sources.ELE.RD.patTuple_Run2011B_cff import readFiles
#process.source.fileNames = readFiles

process.load("KoPFA.TagProbe.Sources.ELE.RD.patTuple_Run2011B_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

mode = "Data"

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_%s.root" % mode)
)

#process.load("KoPFA.TagProbe.Electron_TnP_Producer_cff")

relIso05 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.05"
relIso10 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.10"
relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.15"
relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.17"
relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.20"
relIso05dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - puChargedHadronIso) )/pt < 0.05"
relIso10dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - puChargedHadronIso) )/pt < 0.10"
relIso15dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - puChargedHadronIso) )/pt < 0.15"
relIso17dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - puChargedHadronIso) )/pt < 0.17"
relIso20dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - puChargedHadronIso) )/pt < 0.20"
# FIXME:was not able to call pfCandidateRef for gsf electron
#relIso10 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.10"
#relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.15"
#relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.17"
#relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.20"

eidLooseMC = "(electronID('eidLooseMC') == 5 || electronID('eidLooseMC') == 7 || electronID('eidLooseMC') == 15)"
eidMediumMC = "(electronID('eidMediumMC') == 5 || electronID('eidMediumMC') == 7 || electronID('eidMediumMC') == 15)"
eidTightMC = "(electronID('eidTightMC') == 5 || electronID('eidTightMC')  == 7 || electronID('eidTightMC') == 15)" 
eidSuperTightMC = "(electronID('eidSuperTightMC') == 5 || electronID('eidSuperTightMC') == 7 || electronID('eidSuperTightMC') == 15)" 
eidHyperTight1MC = "(electronID('eidHyperTight1MC') == 5 || electronID('eidHyperTight1MC') == 7 || electronID('eidHyperTight1MC') == 15)"
simpleEleId95relIso = "(electronID('simpleEleId95relIso') == 5 || electronID('simpleEleId95relIso') == 7 || electronID('simpleEleId95relIso') == 15)" 
simpleEleId90relIso = "(electronID('simpleEleId90relIso') == 5 || electronID('simpleEleId90relIso') == 7 || electronID('simpleEleId90relIso') == 15)" 
simpleEleId85relIso = "(electronID('simpleEleId85relIso') == 5 || electronID('simpleEleId85relIso') == 7 || electronID('simpleEleId85relIso') == 15)" 
simpleEleId80relIso = "(electronID('simpleEleId80relIso') == 5 || electronID('simpleEleId80relIso') == 7 || electronID('simpleEleId80relIso') == 15)" 
simpleEleId70relIso = "(electronID('simpleEleId70relIso') == 5 || electronID('simpleEleId70relIso') == 7 || electronID('simpleEleId70relIso') == 15)" 

###Trigger Matching###

process.patElectronTrigger = cms.EDProducer("PATTriggerProducer",
    processName = cms.string('HLT'),
    triggerResults = cms.InputTag( "TriggerResults" ),
    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
    onlyStandAlone = cms.bool( False ),
    addPathModuleLabels = cms.bool( False )
)

process.patElectronTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'acceptedGsfElectrons'),
    matched = cms.InputTag( "patElectronTrigger" ),
    andOr = cms.bool( False ),
    filterIdsEnum = cms.vstring( '*' ),
    filterIds = cms.vint32( 0 ),
    filterLabels = cms.vstring( '*' ),
    matchedCuts = cms.string( ""),
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.2 ),
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( False )
)

process.triggeredPatElectrons = cms.EDProducer("PATTriggerMatchElectronEmbedder",
    src = cms.InputTag('acceptedGsfElectrons'),
    matches = cms.VInputTag( "patElectronTriggerMatch")
)

process.patPFElectronTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'acceptedElectrons'),
    matched = cms.InputTag( "patElectronTrigger" ),
    andOr = cms.bool( False ),
    filterIdsEnum = cms.vstring( '*' ),
    filterIds = cms.vint32( 0 ),
    filterLabels = cms.vstring( '*' ),
    matchedCuts = cms.string( ""),
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.2 ),
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( False )
)

process.triggeredPatPFElectrons = cms.EDProducer("PATTriggerMatchElectronEmbedder",
    src = cms.InputTag('acceptedElectrons'),
    matches = cms.VInputTag( "patPFElectronTriggerMatch")
)

###Tags###

process.eleTag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("triggeredPatPFElectrons"),
    cut = cms.string(
        relIso10 + "&&" + eidTightMC
        + "&&" + "(" + "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',1,0).empty()"
        + "||" + "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',1,0).empty()"
        + "||" + "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',1,0).empty()"
        + ")"
    ),
    filter = cms.bool(True),
)

###Probes###

process.eleIdMedium = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("acceptedGsfElectrons"),
    cut = cms.string(
        eidMediumMC
    ),  
    filter = cms.bool(False),
)

process.eleIdTight = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("acceptedGsfElectrons"),
    cut = cms.string(
        eidTightMC 
    ),  
    filter = cms.bool(False),
)

process.elePFIdTight = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("triggeredPatPFElectrons"),
    cut = cms.string(
        eidTightMC 
    ),
    filter = cms.bool(False),
)


###Z Pairs###

process.zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ triggeredPatPFElectrons@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zIdMedium = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ eleIdMedium@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zIdTight = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ eleIdTight@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zPFIdTight = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ elePFIdTight@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

###Fill Trees###

process.tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zBase"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        IdLoose = cms.string(eidLooseMC),
        IdMedium = cms.string(eidMediumMC),
        IdTight = cms.string(eidTightMC),
        IdSuperTight = cms.string(eidSuperTightMC),
        IdHyperTight1 = cms.string(eidHyperTight1MC),
        IdsimpleEleId95relIso = cms.string(simpleEleId95relIso),
        IdsimpleEleId90relIso = cms.string(simpleEleId90relIso),
        IdsimpleEleId85relIso = cms.string(simpleEleId85relIso),
        IdsimpleEleId80relIso = cms.string(simpleEleId80relIso),
        IdsimpleEleId70relIso = cms.string(simpleEleId70relIso),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.tnpPFId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zIdTight"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        PFId = cms.string("mva > -0.1"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.tnpMediumIdIso = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zIdMedium"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        Iso15 = cms.string(relIso15),
        Iso17 = cms.string(relIso17),
        Iso20 = cms.string(relIso20),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.tnpTightIdIso = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zPFIdTight"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        Iso05 = cms.string(relIso05),
        Iso10 = cms.string(relIso10),
        Iso15 = cms.string(relIso15),
        Iso17 = cms.string(relIso17),
        Iso20 = cms.string(relIso20),
        Iso05dbeta = cms.string(relIso05dbeta),
        Iso10dbeta = cms.string(relIso10dbeta),
        Iso15dbeta = cms.string(relIso15dbeta),
        Iso17dbeta = cms.string(relIso17dbeta),
        Iso20dbeta = cms.string(relIso20dbeta),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.tnpTrigger = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zPFIdTight"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        Trigger = cms.string(
          "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',1,0).empty()"
          + "||" + "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',1,0).empty()"
          + "||" + "!triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',1,0).empty()"
        ),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)   

process.p = cms.Path(
    process.patElectronTrigger 
#  + process.patElectronTriggerMatch + process.triggeredPatElectrons 
  + process.patPFElectronTriggerMatch + process.triggeredPatPFElectrons 
  + process.eleTag #produce tag electron 
  + process.eleIdTight + process.elePFIdTight #produce probe electron
  + process.zBase + process.zIdTight + process.zPFIdTight #produce Z pair
  + process.tnpId + process.tnpPFId + process.tnpTightIdIso #produce trees for Id, isolation
  + process.tnpTrigger #trigger study
  #FIXME: if you want to get isolation efficiency with respect to Medium electron.
  #+ process.eleIdMedium
  #+ process.zIdMedium
  #+ process.tnpMediumIdIso
)

