import FWCore.ParameterSet.Config as cms

mode = "MC"

process = cms.Process("TagProbe")

## Include ##
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("KoPFA.CommonTools.EventWeightProducer_cfi") 

## Input and output ##
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
for i in range(0, 2575):
    process.source.fileNames.append("/store/cmst3/user/cmgtools/CMG/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/V5_B/PAT_CMG_V5_10_0/cmgTuple_%d.root" % i)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("tnpTree_%s.root" % mode)
)

varexpIso = '(chargedHadronIso+neutralHadronIso+photonIso)/pt'
varexpDiso = "(chargedHadronIso+ max(0.0 , neutralHadronIso+photonIso - 0.5*puChargedHadronIso) )/pt"

process.probe = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithTrigger"),
    cut = cms.string(
        'pt > 20 && abs(eta) < 2.5 && dB < 0.04 && passConversionVeto'
        ' && (!triggerObjectMatchesByPath("HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v*",1,0).empty())'
    ),
    filter = cms.bool(True),
)

process.tag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probe"),
    cut = cms.string(
        'pt > 35 && abs(eta) < 2.5'
        ' && electronID("mvaTrigV0") > 0.5 '
        ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && %s < 0.10' % varexpDiso
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

process.probeNh0Mva05Diso20 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05"),
    cut = cms.string("%s > 0.20" % varexpDiso),
)

process.probeNh0Mva05Diso20Pf = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05Diso20"),
    cut = cms.string("isPF"),
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zNh0 = process.z.clone(decay = cms.string("tag@+ probeNh0@-"),)
process.zNh0Mva05 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05@-"),)
process.zNh0Mva05Diso20 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Diso20@-"),)
process.zNh0Mva05Diso20Pf = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Diso20Pf@-"),)

process.tnpNh = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("z"),
    arbitration = cms.string("OneProbe"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
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
        iso10 = cms.string("%s < 0.10" % varexpIso),
        iso15 = cms.string("%s < 0.15" % varexpIso),
        iso17 = cms.string("%s < 0.17" % varexpIso),
        iso20 = cms.string("%s < 0.20" % varexpIso),
        iso25 = cms.string("%s < 0.25" % varexpIso),
        diso10 = cms.string("%s < 0.10" % varexpDiso),
        diso15 = cms.string("%s < 0.15" % varexpDiso),
        diso17 = cms.string("%s < 0.17" % varexpDiso),
        diso20 = cms.string("%s < 0.20" % varexpDiso),
        diso25 = cms.string("%s < 0.25" % varexpDiso),
    ),
) 

process.tnpNh0Mva05Diso20Pf = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Diso20"),
    flags = cms.PSet(
        pf = cms.string("isPF"),
    ),
)

process.tnpNh0Mva05Diso20PfTrg = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Diso20Pf"),
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
  * process.probeNh0Mva05Diso20 * process.zNh0Mva05Diso20 * process.tnpNh0Mva05Diso20Pf
  * process.probeNh0Mva05Diso20Pf * process.zNh0Mva05Diso20Pf * process.tnpNh0Mva05Diso20PfTrg
)

