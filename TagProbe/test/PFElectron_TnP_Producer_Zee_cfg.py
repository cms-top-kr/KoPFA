import FWCore.ParameterSet.Config as cms
import os

def loadDataset(process, dataset, cmgVersion="V5_10_0"):
    prod, dataset = dataset.split("-")
    process.load("KoPFA.CommonTools.Sources.CMG.%s.%s.cmgTuple_%s_cff" % (cmgVersion, prod, dataset))

def getEnv(varName, default):
    import os
    if varName in os.environ:
        return os.environ[varName]
    else:
        return default

section = int(getEnv('SECTION', 1))
begin = int(getEnv('BEGIN', 0))
end = int(getEnv('END', -1))
dataset = getEnv('DATASET', 'Summer12-ZJets')
cmgVersion = getEnv('CMGVERSION', 'V5_10_0')

process = cms.Process("TagProbe")

## Include ##
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## Input and output ##
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),)
loadDataset(process, dataset, cmgVersion)
process.source.fileNames = process.source.fileNames[begin:end]

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("ntuple/unmerged/tnpTree_%s_%03d.root" % (dataset, section))
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.load("KoPFA.CommonTools.EventWeightProducer_cfi")

process.hltHighLevel.throw = False
#process.hltHighLevel.HLTPaths = ["HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v*",]
process.hltHighLevel.HLTPaths = ["HLT_Ele27_WP80_v*",]

process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
    src = cms.InputTag('offlinePrimaryVertices'),
    filterParams =  cms.PSet(
        minNdof = cms.double(4.),
        maxZ    = cms.double(24.),
        maxRho  = cms.double(2.)
    ),
    filter = cms.bool(True),
)

process.patElectronsWithRelIso = cms.EDFilter("PatRelIsoElectronSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patElectronsWithTrigger"),
    cut = cms.string(
        'abs(eta) < 2.5 && dB < 0.04 && passConversionVeto'
        #' && (!triggerObjectMatchesByPath("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v*",1,0).empty())'
        #' && (!triggerObjectMatchesByPath("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v*",1,0).empty())'
    ),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)

process.patMuonsWithRelIso = cms.EDFilter("PatRelIsoMuonSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(
        'abs(eta) < 2.5 && dB < 0.04 && pt > 20'
        ' && isPFMuon && (isGlobalMuon || isTrackerMuon)'
    ),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(0),
    maxNumber = cms.uint32(999),
)

process.goodMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithRelIso"),
    cut = cms.string('userIsolation("User2Iso") < 0.15'),
    filter = cms.bool(False),
)

process.goodElectrons00 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        ' pt > 20 && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0' 
        ' && electronID("mvaTrigV0") > 0.0'
        ' && userIsolation("User3Iso") < 0.15'
        ' && isPF'
    ),
    filter = cms.bool(False),
)
process.goodElectrons05 = process.goodElectrons00.clone(
    cut = cms.string(
        ' pt > 20 && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0' 
        ' && electronID("mvaTrigV0") > 0.5'
        ' && userIsolation("User3Iso") < 0.15'
        ' && isPF'
    ),
)

process.tag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        'pt > 30 '
        ' && electronID("mvaTrigV0") > 0.5 '
        ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && userIsolation("User3Iso") < 0.10'
        # Require tag to matched to hard leg of HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v* path
        #' && !triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsoFilter").empty()'
        ' && !triggerObjectMatchesByPath("HLT_Ele27_WP80_v*", 1, 0).empty()'
    ),
    filter = cms.bool(True),
)

process.probe = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string('pt > 20'),
    filter = cms.bool(False),
)

process.probeNh0 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probe"),
    cut = cms.string('gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'),
)

process.probeNh0Mva05 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0"),
    cut = cms.string('electronID("mvaTrigV0") > 0.5'),
)

process.probeNh0Mva00 = process.probeNh0Mva05.clone(cut = cms.string('electronID("mvaTrigV0") > 0.0'))

process.probeNh0Mva05Riso15 = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05"),
    cut = cms.string('userIsolation("User3Iso") < 0.15'),
)

process.probeNh0Mva00Riso15 = process.probeNh0Mva05Riso15.clone(src = cms.InputTag("probeNh0Mva00"))

process.probeNh0Mva05Riso15Pf = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        'gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && electronID("mvaTrigV0") > 0.5'
        ' && userIsolation("User3Iso") < 0.15'
        ' && isPF'
    ),
    filter = cms.bool(False),
)

process.probeNh0Mva00Riso15Pf = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        'gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && electronID("mvaTrigV0") > 0.0'
        ' && userIsolation("User3Iso") < 0.15'
        ' && isPF'
    ),
    filter = cms.bool(False),
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zNh0 = process.z.clone(decay = cms.string("tag@+ probeNh0@-"),)
process.zNh0Mva05 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05@-"),)
process.zNh0Mva00 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00@-"),)
process.zNh0Mva05Riso15 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Riso15@-"),)
process.zNh0Mva00Riso15 = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00Riso15@-"),)
process.zNh0Mva05Riso15Pf = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Riso15Pf@-"),)
process.zNh0Mva00Riso15Pf = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00Riso15Pf@-"),)

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

process.tnpNh0Mva00Iso = process.tnpNh0Mva05Iso.clone(tagProbePairs = cms.InputTag("zNh0Mva00"))

process.tnpNh0Mva05Riso15Pf = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Riso15"),
    flags = cms.PSet(
        pf = cms.string("isPF"),
    ),
)

process.tnpNh0Mva00Riso15Pf = process.tnpNh0Mva05Riso15Pf.clone(tagProbePairs = cms.InputTag("zNh0Mva00Riso15"))

process.tnpNh0Mva05Riso15PfTrg = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Riso15Pf"),
    flags = cms.PSet(
        #trgPath = cms.string('!triggerObjectMatchesByPath("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",1,0).empty()'),
        trgHL = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoFilter").empty()'),
        trgDZ = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDZ").empty()'),
        trgSL = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDoubleFilter").empty()'),

        trgZM = cms.string('!triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8PMMassFilter").empty()'),
        trgTH = cms.string('!triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsoFilter").empty()'),
    ),
)

process.tnpNh0Mva00Riso15PfTrg = process.tnpNh0Mva05Riso15PfTrg.clone(tagProbePairs = cms.InputTag("zNh0Mva00Riso15Pf"))

process.jetFilter00 = cms.EDFilter("CMGCleanJetSelector",
    doFilter = cms.bool(True),
    src = cms.InputTag("cmgPFJetSelCHS"),
    cut = cms.string(
        " abs(eta) < 2.5 && pt > 30 && nConstituents > 1"
        " && component(5).fraction < 0.99 && component(4).fraction < 0.99"
        " && (abs(eta) >= 2.4 || component(2).fraction < 0.99 )"
        " && (abs(eta) >= 2.4 || component(1).fraction > 0 )"
        " && (abs(eta) >= 2.4 || component(1).number > 0 ) "
    ),
    overlapCands = cms.VInputTag(
        cms.InputTag("goodMuons"),
        cms.InputTag("goodElectrons00"),
    ),
    overlapDeltaR = cms.double(0.5),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)
process.jetFilter05 = process.jetFilter00.clone(
    doFilter = cms.bool(True),
    overlapCandLabels = cms.VInputTag(
        cms.InputTag("goodMuons"),
        cms.InputTag("goodElectrons05"),
    ),
)

process.p00 = cms.Path(
    process.hltHighLevel * process.goodOfflinePrimaryVertices * process.PUweight
  * process.patMuonsWithRelIso * process.goodMuons
  * process.patElectronsWithRelIso * process.goodElectrons00
  * process.jetFilter00

  * process.tag 
  * process.probe 
  * process.probeNh0 
  * process.probeNh0Mva00 
  * process.probeNh0Mva00Riso15 
  * process.probeNh0Mva00Riso15Pf 

  * process.zNh0Mva00 * process.tnpNh0Mva00Iso
  * process.zNh0Mva00Riso15 * process.tnpNh0Mva00Riso15Pf
  * process.zNh0Mva00Riso15Pf * process.tnpNh0Mva00Riso15PfTrg
)

process.p05 = cms.Path(
    process.hltHighLevel * process.goodOfflinePrimaryVertices * process.PUweight
  * process.patMuonsWithRelIso * process.goodMuons
  * process.patElectronsWithRelIso * process.goodElectrons05
  * process.jetFilter05

  * process.tag 
  * process.probe 
  * process.probeNh0 
  * process.probeNh0Mva05 
  * process.probeNh0Mva05Riso15 
  * process.probeNh0Mva05Riso15Pf 

  * process.z * process.tnpNh
  * process.zNh0 * process.tnpNh0Mva
  * process.zNh0Mva05 * process.tnpNh0Mva05Iso
  * process.zNh0Mva05Riso15 * process.tnpNh0Mva05Riso15Pf
  * process.zNh0Mva05Riso15Pf * process.tnpNh0Mva05Riso15PfTrg
)

