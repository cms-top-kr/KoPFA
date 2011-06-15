import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

## Include ##
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
#from KoPFA.TopAnalyzer.Sources.ELE.RD.patTuple_Run2011A_cff import readFiles
#from KoPFA.TopAnalyzer.Sources.ELE.MC.Spring11.patTuple_ZJets_TnP_cff import readFiles
from KoPFA.TopAnalyzer.Sources.ELE.MC.Spring11.patTuple_ZJets_cff import readFiles
process.source.fileNames = readFiles

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_MC.root")
)

#process.load("KoPFA.TagProbe.Electron_TnP_Producer_cff")

relIso10 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.10"
relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.15"
relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.17"
relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pfCandidateRef.p4.pt < 0.20"
eidMediumMC = "(electronID('eidMediumMC') == 5 || electronID('eidMediumMC') == 7 || electronID('eidMediumMC') == 15)"
eidTightMC = "(electronID('eidTightMC') == 5 || electronID('eidTightMC') == 7 || electronID('eidTightMC') == 15)"

process.eleTag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("acceptedElectrons"),
    cut = cms.string(
        relIso10 + "&&" + eidTightMC
    ),
    filter = cms.bool(True),
)

process.eleIdMedium = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsLoosePFlow"),
    cut = cms.string(
        eidMediumMC
    ),  
    filter = cms.bool(False),
)

process.eleIdTight = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsLoosePFlow"),
    cut = cms.string(
        eidTightMC
    ),  
    filter = cms.bool(False),
)

process.zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ selectedPatElectronsLoosePFlow@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110"),
)

process.zIdMedium = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ eleIdMedium@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110"),
)

process.zIdTight = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ eleIdTight@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("70 < mass < 110"),
)

process.tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("zBase"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        charge = cms.string("charge"),
    ),
    flags = cms.PSet(
        IdMedium = cms.string(eidMediumMC),
        IdTight = cms.string(eidTightMC),
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
        charge = cms.string("charge"),
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
    tagProbePairs = cms.InputTag("zIdTight"),
    arbitration = cms.string("OneProbe"),
    #arbitration = cms.string("BestMass"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        charge = cms.string("charge"),
    ),
    flags = cms.PSet(
        Iso15 = cms.string(relIso15),
        Iso17 = cms.string(relIso17),
        Iso20 = cms.string(relIso20),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.p = cms.Path(
    process.eleTag * process.eleIdMedium + process.eleIdTight
  + process.zBase + process.zIdMedium + process.zIdTight
  + process.tnpId + process.tnpMediumIdIso + process.tnpTightIdIso
)

