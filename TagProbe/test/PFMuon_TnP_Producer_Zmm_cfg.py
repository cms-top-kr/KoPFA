import FWCore.ParameterSet.Config as cms
import os

from CMGTools.Common.Tools.applyJSON_cff import applyJSON
def loadDataset(process, dataset, cmgVersion="V5_10_0"):
	if 'Run2012' in dataset:
		process.load("KoPFA.CommonTools.Sources.CMG.%s.Run2012.cmgTuple_%s_cff" % (cmgVersion, dataset))
		json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON_v2.txt'
	else:
#		production, dataset = dataset.split("-")
		process.load("KoPFA.CommonTools.Sources.CMG.%s.Summer12.cmgTuple_%s_cff" % (cmgVersion, dataset))

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
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(),
)
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

process.probe = cms.EDFilter("PatRelIsoMuonSelector",
    rho = cms.InputTag("kt6PFJets", "rho"),
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(
				'pt > 5 && abs(eta) < 2.4'
    ),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)

process.tag = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("probe"),
	cut = cms.string(
		'isPFMuon && isGlobalMuon'
		'&& globalTrack.normalizedChi2 < 10.0'
		'&& track.hitPattern.trackerLayersWithMeasurement > 5'
  		'&& globalTrack.hitPattern.numberOfValidMuonHits > 0'
		'&& abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0'
		'&& numberOfMatchedStations() > 1'
		'&& userIsolation("User2Iso") < 0.15'
		'&& (!triggerObjectMatchesByPath("HLT_IsoMu24*_v*",1,0).empty())'
    ),
	filter = cms.bool(True),
)

process.tagDebug = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("patMuonsWithTrigger"),
	cut = cms.string(
		'(!triggerObjectMatchesByFilter("hltL3pfL1DoubleMu10MuOpenL1f0L2pf0L3PreFiltered8").empty())'
	),
	filter = cms.bool(True),
)

process.probelooseId = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("probe"),
	cut = cms.string('isPFMuon && (isGlobalMuon || isTrackerMuon)'),
)
process.probelooseIddBIso15 = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("probelooseId"),
	cut = cms.string('userIsolation("User2Iso") < 0.15'),
)
process.probetightIddBIso15 = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("probetightId"),
	cut = cms.string('userIsolation("User2Iso") < 0.15'),
)
process.probelooseIddBIso15sl = cms.EDFilter("PATMuonSelector",
	src = cms.InputTag("probelooseIddBIso15"),
	cut = cms.string(
		'(!triggerObjectMatchesByFilter("hltL3pfL1DoubleMu10MuOpenL1f0L2pf0L3PreFiltered8").empty())'
        '|| (!triggerObjectMatchesByFilter("hltL3pfL1DoubleMu10MuOpenOR3p5L1f0L2pf0L3PreFiltered8").empty())'
	),
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)
process.zlooseId = process.z.clone(decay = cms.string("tag@+ probelooseId@-"),)
process.zlooseIddBIso15 = process.z.clone(decay = cms.string("tag@+ probelooseIddBIso15@-"),)
process.zlooseIddBIso15sl = process.z.clone(decay = cms.string("tag@+ probelooseIddBIso15sl"),)

process.tnpId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("z"),
    arbitration = cms.string("OneProbe"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
    ),
    flags = cms.PSet(
        looseId = cms.string("isPFMuon && (isGlobalMuon || isTrackerMuon)"),
        tightId = cms.string(
			'isPFMuon && isGlobalMuon'
			'&& globalTrack.normalizedChi2 < 10.0'
			'&& track.hitPattern.trackerLayersWithMeasurement > 5'
			'&& globalTrack.hitPattern.numberOfValidMuonHits > 0'
			'&& abs(dB) < 0.2 && innerTrack.hitPattern.numberOfValidPixelHits > 0'
			'&& numberOfMatchedStations() > 1'
		),
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
		riso10 = cms.string('userIsolation("User3Iso") < 0.10'),
		riso15 = cms.string('userIsolation("User3Iso") < 0.15'),
		riso17 = cms.string('userIsolation("User3Iso") < 0.17'),
		riso20 = cms.string('userIsolation("User3Iso") < 0.20'),
		diso10 = cms.string('userIsolation("User2Iso") < 0.10'),
		diso15 = cms.string('userIsolation("User2Iso") < 0.15'),
		diso17 = cms.string('userIsolation("User2Iso") < 0.17'),
		diso20 = cms.string('userIsolation("User2Iso") < 0.20'),
	)
)
process.tnplooseIddBIso15TrgMu17Mu8 = process.tnpId.clone(
    tagProbePairs = cms.InputTag("zlooseIddBIso15"),
    flags = cms.PSet(
        softLeg = cms.string(
			'(!triggerObjectMatchesByFilter("hltL3pfL1DoubleMu10MuOpenL1f0L2pf0L3PreFiltered8").empty())'
			'|| (!triggerObjectMatchesByFilter("hltL3pfL1DoubleMu10MuOpenOR3p5L1f0L2pf0L3PreFiltered8").empty())'
		),
		hardLeg = cms.string(
			'(!triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenL1f0L2f10L3Filtered17").empty())'
			'|| (!triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenOR3p5L1f0L2f10L3Filtered17").empty())'
		),
    ),
)
process.tnplooseIddBIso15TrgMu17Mu8sl = process.tnpId.clone(
    tagProbePairs = cms.InputTag("zlooseIddBIso15sl"),
    flags = cms.PSet(
        p = cms.string(
			'(!triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenL1f0L2f10L3Filtered17").empty())'
			'|| (!triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenOR3p5L1f0L2f10L3Filtered17").empty())'
		),
		f = cms.string(
			'(triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenL1f0L2f10L3Filtered17").empty())'
			'&& (triggerObjectMatchesByFilter("hltL3fL1DoubleMu10MuOpenOR3p5L1f0L2f10L3Filtered17").empty())'
		),
    ),
)

process.p = cms.Path(
#    process.hltHighLevel
	  process.goodOfflinePrimaryVertices
	* process.PUweight
	* process.probe * process.tag
	* process.z * process.tnpId
	* process.probelooseId * process.zlooseId * process.tnplooseIdIso
	* process.probelooseIddBIso15 * process.zlooseIddBIso15	* process.tnplooseIddBIso15TrgMu17Mu8
	* process.probelooseIddBIso15sl * process.zlooseIddBIso15sl	* process.tnplooseIddBIso15TrgMu17Mu8sl
#	* process.tagDebug
)

