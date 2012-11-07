import FWCore.ParameterSet.Config as cms
import os

def loadDataset(process, dataset, cmgVersion="V5_10_0"):
    if 'Run2012' in dataset:
        process.load("KoPFA.CommonTools.Sources.CMG.%s.Run2012.cmgTuple_%sElEl_cff" % (cmgVersion, dataset))
    else:
        production, dataset = dataset.split("-")
        process.load("KoPFA.CommonTools.Sources.CMG.%s.%s.cmgTuple_%s_cff" % (cmgVersion, production, dataset))

section = int(os.environ['SECTION'])
begin = int(os.environ['BEGIN'])
end = int(os.environ['END'])
dataset = os.environ['DATASET']

process = cms.Process("TagProbe")

## Include ##
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load("KoPFA.CommonTools.EventWeightProducer_cfi")

## Input and output ##
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),)
loadDataset(process, dataset)
process.source.fileNames = process.source.fileNames[begin:end]

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("result/tnpTree_%s_%03d.root" % (dataset, section))
)


process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
    src = cms.InputTag('offlinePrimaryVertices'),
    filterParams =  cms.PSet(
        minNdof = cms.double(4.),
        maxZ    = cms.double(24.),
        maxRho  = cms.double(2.)
    ),
    filter = cms.bool(True),
)

process.probe = cms.EDFilter("PatRelIsoElectronSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patElectronsWithTrigger"),
    cut = cms.string(
        'pt > 20 && abs(eta) < 2.5 && dB < 0.04 && passConversionVeto'
        #' && (!triggerObjectMatchesByPath("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v*",1,0).empty())'
        ' && (!triggerObjectMatchesByPath("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v*",1,0).empty())'
    ),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)

process.tag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probe"),
    cut = cms.string(
        'pt > 20 && abs(eta) < 2.5'
        ' && electronID("mvaTrigV0") > 0.5 '
        ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && userIsolation("User2Iso") < 0.10'
    ),
    filter = cms.bool(True),
)

process.probeNh0 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probe"),
    cut = cms.string('gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'),
)

process.probeNh0Mva05 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0"),
    cut = cms.string('electronID("mvaTrigV0") > 0.5'),
)

process.probeNh0Mva05Diso15 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05"),
    cut = cms.string('userIsolation("User2Iso") < 0.15'),
)

process.probeNh0Mva05Diso15Pf = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05Diso15"),
    cut = cms.string("isPF"),
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zNh0 = process.z.clone(decay = cms.string("tag@+ probeNh0@-"),)
process.zNh0Mva05 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05@-"),)
process.zNh0Mva05Diso15 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Diso15@-"),)
process.zNh0Mva05Diso15Pf = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Diso15Pf@-"),)

process.tnpNh = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("z"),
    arbitration = cms.string("OneProbe"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("superCluster.eta"),
        abseta = cms.string("abs(superCluster.eta)"),
    ),
    flags = cms.PSet(
        nh0 = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0"),
        nh1 = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1"),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
)

process.tnpNh0Mva = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0"),
    flags = cms.PSet(
          mva00 = cms.string('electronID("mvaTrigV0") > 0.0'),
          mva03 = cms.string('electronID("mvaTrigV0") > 0.3'),
          mva05 = cms.string('electronID("mvaTrigV0") > 0.5'),
          mva07 = cms.string('electronID("mvaTrigV0") > 0.7'),
          mva09 = cms.string('electronID("mvaTrigV0") > 0.9'),
    ),
)

process.tnpNh0Mva05Iso = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05"),
    flags = cms.PSet(
        iso10 = cms.string('userIsolation("User1Iso") < 0.10'),
        iso15 = cms.string('userIsolation("User1Iso") < 0.15'),
        iso17 = cms.string('userIsolation("User1Iso") < 0.17'),
        iso20 = cms.string('userIsolation("User1Iso") < 0.20'),

        diso10 = cms.string('userIsolation("User2Iso") < 0.10'),
        diso15 = cms.string('userIsolation("User2Iso") < 0.15'),
        diso17 = cms.string('userIsolation("User2Iso") < 0.17'),
        diso20 = cms.string('userIsolation("User2Iso") < 0.20'),

        riso10 = cms.string('userIsolation("User3Iso") < 0.10'),
        riso15 = cms.string('userIsolation("User3Iso") < 0.15'),
        riso17 = cms.string('userIsolation("User3Iso") < 0.17'),
        riso20 = cms.string('userIsolation("User3Iso") < 0.20'),
    ),
)

process.tnpNh0Mva05Diso15Pf = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Diso15"),
    flags = cms.PSet(
        pf = cms.string("isPF"),
    ),
)

process.tnpNh0Mva05Diso15PfTrg = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Diso15Pf"),
    flags = cms.PSet(
        trg = cms.string('!triggerObjectMatchesByPath("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",1,0).empty()'),
    ),
)

process.p = cms.Path(
#    process.hltHighLevel
    process.goodOfflinePrimaryVertices
  * process.PUweight
  * process.probe * process.tag * process.z * process.tnpNh
  * process.probeNh0 * process.zNh0 * process.tnpNh0Mva
  * process.probeNh0Mva05 * process.zNh0Mva05 * process.tnpNh0Mva05Iso
  * process.probeNh0Mva05Diso15 * process.zNh0Mva05Diso15 * process.tnpNh0Mva05Diso15Pf
  * process.probeNh0Mva05Diso15Pf * process.zNh0Mva05Diso15Pf * process.tnpNh0Mva05Diso15PfTrg
)

