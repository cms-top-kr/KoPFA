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
#process.load("PFAnalyses.TTbarDIL.Sources.ELE.MC.Fall10.patTuple_ZJets50_cff")
from KoPFA.TopAnalyzer.Sources.ELE.RD.patTuple_Run2011A_cff import readFiles
process.source.fileNames = readFiles

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("/tmp/jhgoh/tnpTree_RD.root")
)

#process.load("KoPFA.TagProbe.Electron_TnP_Producer_cff")

relIso15 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.15"
relIso17 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.17"
relIso20 = "(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.20"
eidMediumMC = "(electronID('eidMediumMC') == 5 || electronID('eidMediumMC') == 7 || electronID('eidMediumMC') == 15)"
eidTightMC = "(electronID('eidTightMC') == 5 || electronID('eidTightMC') == 7 || electronID('eidTightMC') == 15)"

process.eleTag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("acceptedElectrons"),
    cut = cms.string(
        relIso20 + "&&" + eidTightMC
    ),
    filter = cms.bool(True),
)

process.zBase = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("eleTag@+ selectedPatElectronsLoosePFlow@-"),
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
        Iso15 = cms.string(relIso15),
        Iso17 = cms.string(relIso17),
        Iso20 = cms.string(relIso20),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
)

process.p = cms.Path(
    process.eleTag
  + process.zBase
  + process.tnpId
)

