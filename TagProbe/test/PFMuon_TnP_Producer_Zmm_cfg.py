import FWCore.ParameterSet.Config as cms
import os

def loadDataset(process, dataset, cmgVersion="V5_10_0"):
    if 'Run2012' in dataset:
        process.load("KoPFA.CommonTools.Sources.CMG.%s.Run2012.cmgTuple_%sMuMu_cff" % (cmgVersion, dataset))
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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
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

idLoose = "isPFMuon && ( isGlobalMuon || isTrackerMuon )"
idTight = "isPFMuon && isGlobalMuon && globalTrack.normalizedChi2 < 10.0 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0 && innerTrack.hitPattern.numberOfValidTrackerHits > 10 && numberOfMatchedStations() > 1"

process.probe = cms.EDFilter("PatRelIsoMuonSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(
        'pt > 20 && abs(eta) < 2.4'
        #' && (!triggerObjectMatchesByPath("HLT_IsoMu30*_v*",1,0).empty())'
        ' && (!triggerObjectMatchesByPath("HLT_IsoMu24*_v*",1,0).empty())'
    ),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)

process.tag = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("probe"),
    cut = cms.string(
        'pt > 35 && abs(eta) < 2.4'
        '&&' +idLoose+
        ' && userIsolation("User2Iso") < 0.10'
    ),
    filter = cms.bool(True),
)

process.probelooseId = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("probe"),
    cut = cms.string( idLoose ),
)

process.probetightId = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("probe"),
    cut = cms.string( idTight ),
)

process.probelooseIdiso15 = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("probelooseId"),
    cut = cms.string('userIsolation("User2Iso") < 0.15'),
)

process.probetightIdiso10 = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("probetightId"),
    cut = cms.string('userIsolation("User2Iso") < 0.10'),
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zlooseId = process.z.clone(decay = cms.string("tag@+ probelooseId@-"),)
process.ztightId = process.z.clone(decay = cms.string("tag@+ probetightId@-"),)
process.zlooseIdiso15 = process.z.clone(decay = cms.string("tag@+ probelooseIdiso15@-"),)
process.ztightIdiso10 = process.z.clone(decay = cms.string("tag@+ probetightIdiso10@-"),)

process.tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("z"),
    arbitration = cms.string("OneProbe"),
	variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
	    looseId = cms.string( idLoose ),
	    tightId = cms.string( idTight ),
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
) 

process.tnplooseIdIso = process.tnpId.clone(
    tagProbePairs = cms.InputTag("zlooseId"),
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

process.tnptightIdIso = process.tnpId.clone(
    tagProbePairs = cms.InputTag("ztightId"),
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

process.tnplooseIdiso15Trg = process.tnpId.clone(
    tagProbePairs = cms.InputTag("zlooseIdiso15"),
    flags = cms.PSet(
        trg = cms.string('!triggerObjectMatchesByPath("HLT_Mu17_*Mu8_v*",1,0).empty()'),
    ),
)

process.tnptightIdiso10Trg = process.tnpId.clone(
    tagProbePairs = cms.InputTag("ztightIdiso10"),
    flags = cms.PSet(
        trg = cms.string('!triggerObjectMatchesByPath("HLT_Mu17_*Mu8_v*",1,0).empty()'),
    ),
)

process.p = cms.Path(
#    process.hltHighLevel
    process.goodOfflinePrimaryVertices
  * process.PUweight
  * process.probe * process.tag * process.z * process.tnpId
  * process.probelooseId * process.probetightId * process.zlooseId * process.ztightId * process.tnplooseIdIso * process.tnptightIdIso
  * process.probelooseIdiso15 * process.probetightIdiso10 * process.zlooseIdiso15 * process.ztightIdiso10
  * process.tnplooseIdiso15Trg * process.tnptightIdiso10Trg
)

