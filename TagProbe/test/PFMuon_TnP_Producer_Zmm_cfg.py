import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

## Include ##
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring('patMuonTrigger')
process.MessageLogger.suppressInfo = cms.untracked.vstring('patMuonTrigger')
#process.MessageLogger.suppressError = cms.untracked.vstring('patMuonTrigger')

process.load("KoPFA.CommonTools.EventWeightProducer_cfi") 

from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)

#from KoPFA.TagProbe.Sources.MU.RD.patTuple_Run2011B_cff import readFiles
#process.source.fileNames = readFiles
#process.load("KoPFA.TagProbe.Sources.MU.RD.patTuple_Run2011B_cff")
process.load("KoPFA.TagProbe.Sources.MU.MC.patTuple_ZJets_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

mode = "MC"

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_%s.root" % mode)
)

#process.load("KoPFA.TagProbe.Muon_TnP_Producer_cff")

relIso05 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.05"
relIso10 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.10"
relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.15"
relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.17"
relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.20"
relIso05dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt < 0.05"
relIso10dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt < 0.10"
relIso15dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt < 0.15"
relIso17dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt < 0.17"
relIso20dbeta = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt < 0.20"
# FIXME:was not able to call pfCandidateRef for gsf electron
#relIso10 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.10"
#relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.15"
#relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.17"
#relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.20"

midLooseMC = "isPFMuon && ( isGlobalMuon || isTrackerMuon )"
midTightMC = "isPFMuon && isGlobalMuon && globalTrack.normalizedChi2 < 10.0 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0 && innerTrack.hitPattern.numberOfValidTrackerHits > 10 && numberOfMatchedStations() > 1" 
midHighPtMC = "isPFMuon && isGlobalMuon && innerTrack.hitPattern.trackLayersWithMeasurement > 8 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0 && innerTrack.hitPattern.numberOfValidTrackerHits > 10 && numberOfMatchedStations() > 1" 

###Trigger Matching###

process.patMuonTrigger = cms.EDProducer("PATTriggerProducer",
    processName = cms.string('HLT'),
    triggerResults = cms.InputTag( "TriggerResults" ),
    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
    onlyStandAlone = cms.bool( False ),
    addPathModuleLabels = cms.bool( False )
)

process.patMuonTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'acceptedMuons'),
    matched = cms.InputTag( "patMuonTrigger" ),
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

process.triggeredPatMuons = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag('acceptedMuons'),
    matches = cms.VInputTag( "patMuonTriggerMatch")
)

process.patPFMuonTriggerMatch = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src = cms.InputTag( 'acceptedMuons'),
    matched = cms.InputTag( "patMuonTrigger" ),
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

process.triggeredPatPFMuons = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag('acceptedMuons'),
    matches = cms.VInputTag( "patPFMuonTriggerMatch")
)

###Tags###

process.muTag = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("triggeredPatPFMuons"),
    cut = cms.string(
        relIso10 + "&&" + midLooseMC
        + "&&" + "(" + "!triggerObjectMatchesByPath('HLT_Mu17_Mu8_v*',1,0).empty()"
        + "||" + "!triggerObjectMatchesByPath('HLT_Mu17_TkMu8_v*',1,0).empty()"
        + ")"
    ),
    filter = cms.bool(True),
)

###Probes###

process.muIdLoose = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("acceptedMuons"),
    cut = cms.string(
        midLooseMC 
    ),  
    filter = cms.bool(False),
)

process.muIdHighPt = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("acceptedMuons"),
    cut = cms.string(
        midHighPtMC
    ),  
    filter = cms.bool(False),
)

process.muIdTight = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("acceptedMuons"),
    cut = cms.string(
        midTightMC 
    ),  
    filter = cms.bool(False),
)

process.muPFIdLoose = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("triggeredPatPFMuons"),
    cut = cms.string(
        midLooseMC 
    ),
    filter = cms.bool(False),
)

process.muPFIdTight = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("triggeredPatPFMuons"),
    cut = cms.string(
        midTightMC 
    ),
    filter = cms.bool(False),
)


###Z Pairs###

process.zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ triggeredPatPFMuons@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zIdHighPt = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muIdHighPt@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zIdLoose = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muIdLoose@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zIdTight = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muIdTight@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zPFIdLoose = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muPFIdLoose@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zPFIdTight = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("muTag@+ muPFIdTight@-"),
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
        IdLoose = cms.string(midLooseMC),
        IdHighPt = cms.string(midHighPtMC),
        IdTight = cms.string(midTightMC),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
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
        PFId = cms.string("isPFMuon"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
)

process.tnpHighPtIdIso = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zIdHighPt"),
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
    eventWeight = cms.InputTag("PUweight","weight")
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
    eventWeight = cms.InputTag("PUweight","weight")
)

process.tnpTrigger = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zPFIdLoose"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        Trigger = cms.string(
          "!triggerObjectMatchesByPath('HLT_Mu17_Mu8_v*',1,0).empty()"
          + "||" + "!triggerObjectMatchesByPath('HLT_Mu17_TkMu8_v*',1,0).empty()"
        ),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
)   

process.p = cms.Path(
    process.PUweight
  + process.patMuonTrigger 
#  + process.patMuonTriggerMatch + process.triggeredPatMuons 
  + process.patPFMuonTriggerMatch + process.triggeredPatPFMuons 
  + process.muTag #produce tag muon 
  + process.muIdLoose + process.muPFIdLoose #produce probe muon
  + process.zBase + process.zIdLoose + process.zPFIdLoose #produce Z pair
  #+ process.muIdTight + process.muPFIdTight #produce probe muon
  #+ process.zBase + process.zIdTight + process.zPFIdTight #produce Z pair
  + process.tnpId + process.tnpPFId + process.tnpTightIdIso #produce trees for Id, isolation
  + process.tnpTrigger #trigger study
  #FIXME: if you want to get isolation efficiency with respect to HighPt muon.
  #+ process.muIdHighPt
  #+ process.zIdHighPt
  #+ process.tnpHighPtIdIso
)

