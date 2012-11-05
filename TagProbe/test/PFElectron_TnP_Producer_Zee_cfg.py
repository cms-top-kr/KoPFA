import FWCore.ParameterSet.Config as cms
import os

mode = "MC"
if 'MODE' in os.environ:
    mode = os.environ['MODE']

process = cms.Process("TagProbe")

## Include ##
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load("KoPFA.CommonTools.EventWeightProducer_cfi") 

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)

if mode == 'MC':
    for i in range(0, 2575):
        process.source.fileNames.append("/store/cmst3/user/cmgtools/CMG/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/V5_B/PAT_CMG_V5_10_0/cmgTuple_%d.root" % i)
else:
    for i in range(0, 1588):
        process.source.fileNames.append("/store/cmst3/user/cmgtools/CMG/DoubleElectron/Run2012B-13Jul2012-v1/AOD/V5/PAT_CMG_V5_10_0/cmgTuple_%d.root" % i)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_%s.root" % mode)
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
    cut = cms.string('userIsolation("User1Iso") > 0.15'),
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
    process.PUweight
  * process.probe * process.tag * process.z * process.tnpNh
  * process.probeNh0 * process.zNh0 * process.tnpNh0Mva
  * process.probeNh0Mva05 * process.zNh0Mva05 * process.tnpNh0Mva05Iso
  * process.probeNh0Mva05Diso15 * process.zNh0Mva05Diso15 * process.tnpNh0Mva05Diso15Pf
  * process.probeNh0Mva05Diso15Pf * process.zNh0Mva05Diso15Pf * process.tnpNh0Mva05Diso15PfTrg
)

