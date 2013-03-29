import FWCore.ParameterSet.Config as cms
import os

def loadDataset(dataset):
    files = []
    for line in open("/afs/cern.ch/user/j/jhgoh/public/sources/CMG/V5_13_0/%s.txt" % dataset).readlines():
        line = line.strip()
        if '.root' not in line: continue
        if line[0] == '#': continue

        files.append(line)
    return files

section = int(os.environ['SECTION'])
begin = int(os.environ['BEGIN'])
end = int(os.environ['END'])
dataset = os.environ['DATASET']
triggerMode = os.environ['TRIGGERMODE']

process = cms.Process("TagProbe")

## Include ##
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## Input and output ##
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),)
process.source.fileNames = loadDataset(dataset)[begin:end]
print dataset, section
print process.source.fileNames[0]
print process.source.fileNames[-1]

if 'Run' in dataset:
    from CMGTools.Common.Tools.applyJSON_cff import *
    json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
    applyJSON(process, json)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("ntuple/unmerged/ntuple_%s_%03d.root" % (dataset, section))
    #fileName = cms.string("tnpTree-TTJets-dR05s.root"),
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.load("KoPFA.CommonTools.EventWeightProducer_cfi")

process.hltHighLevel.throw = False

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
    ),
    vertexLabel = cms.untracked.InputTag("goodOfflinePrimaryVertices"),
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
    vertexLabel = cms.untracked.InputTag("goodOfflinePrimaryVertices"),
    coneSize = cms.double(0.3),
    minNumber = cms.uint32(0),
    maxNumber = cms.uint32(999),
)

process.goodMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithRelIso"),
    cut = cms.string(''),#userIsolation("User2Iso") < 0.15'),
    filter = cms.bool(False),
)

process.goodElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        ' pt > 20 && abs(eta) < 2.5'
        #&& gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0' 
        #' && electronID("mvaTrigV0") > 0.5'
        #' && userIsolation("User3Iso") < 0.15'
        #' && isPF'
    ),
    filter = cms.bool(False),
)

process.tag = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        'pt > 30 && abs(eta) < 0.8 '
        ' && electronID("mvaTrigV0") > 0.9 '
        ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && userIsolation("User3Iso") < 0.10'
        ' && isPF'
    ),
    filter = cms.bool(True),
)

process.tagHL = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("tag"),
    cut = cms.string(
        '!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoFilter").empty()'
    ),
    filter = cms.bool(False),
)

process.tagSL = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("tag"),
    cut = cms.string(
        '!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDoubleFilter").empty()'
    ),
    filter = cms.bool(False),
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

process.probeNh0Mva09Riso15Pf = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("patElectronsWithRelIso"),
    cut = cms.string(
        'gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
        ' && electronID("mvaTrigV0") > 0.9'
        ' && userIsolation("User3Iso") < 0.15'
        ' && isPF'
    ),
    filter = cms.bool(False),
)

process.probeNh0Mva05Riso15PfHLSL = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("probeNh0Mva05Riso15Pf"),
    cut = cms.string(
        '    !triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDoubleFilter").empty()'
        ' && !triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoFilter").empty()'
    ),
    filter = cms.bool(False),
)

process.probeNh0Mva00Riso15PfHLSL = process.probeNh0Mva05Riso15PfHLSL.clone(
    src = cms.InputTag("probeNh0Mva00Riso15Pf")
)

process.probeNh0Mva09Riso15PfHLSL = process.probeNh0Mva05Riso15PfHLSL.clone(
    src = cms.InputTag("probeNh0Mva09Riso15Pf")
)

process.z = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tag@+ probe@-"),
    checkCharge = cms.bool(False),
    cut = cms.string("50 < mass < 130"),
)

process.zNh0                    = process.z.clone(decay = cms.string("tag@+ probeNh0@-"),)
process.zNh0Mva05               = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05@-"),)
process.zNh0Mva00               = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00@-"),)
process.zNh0Mva05Riso15         = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Riso15@-"),)
process.zNh0Mva00Riso15         = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00Riso15@-"),)
process.zNh0Mva05Riso15Pf       = process.z.clone(decay = cms.string("tag@+ probeNh0Mva05Riso15Pf@-"),)
process.zNh0Mva00Riso15Pf       = process.z.clone(decay = cms.string("tag@+ probeNh0Mva00Riso15Pf@-"),)
process.zNh0Mva09Riso15Pf       = process.z.clone(decay = cms.string("tag@+ probeNh0Mva09Riso15Pf@-"),)
process.zHLNh0Mva05Riso15Pf     = process.z.clone(decay = cms.string("tagHL@+ probeNh0Mva05Riso15Pf@-"),)
process.zHLNh0Mva00Riso15Pf     = process.z.clone(decay = cms.string("tagHL@+ probeNh0Mva00Riso15Pf@-"),)
process.zHLNh0Mva09Riso15Pf     = process.z.clone(decay = cms.string("tagHL@+ probeNh0Mva09Riso15Pf@-"),)
process.zSLNh0Mva05Riso15PfHLSL = process.z.clone(decay = cms.string("tagSL@+ probeNh0Mva05Riso15PfHLSL@-"),)
process.zSLNh0Mva00Riso15PfHLSL = process.z.clone(decay = cms.string("tagSL@+ probeNh0Mva00Riso15PfHLSL@-"),)
process.zSLNh0Mva09Riso15PfHLSL = process.z.clone(decay = cms.string("tagSL@+ probeNh0Mva09Riso15PfHLSL@-"),)

process.tnpNh = cms.EDAnalyzer("TagProbeFitTreeProducer",
    tagProbePairs = cms.InputTag("z"),
    arbitration = cms.string("OneProbe"),
    variables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("superCluster.eta"),
        abseta = cms.string("abs(superCluster.eta)"),
#        chargeConsistency = cms.string("isGsfCtfScPixChargeConsistent()"),
    ),
    flags = cms.PSet(
        nh0 = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0"),
        nh1 = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1"),
        allIdIso09 = cms.string(
            'gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
            ' && electronID("mvaTrigV0") > 0.9'
            ' && userIsolation("User3Iso") < 0.15'
            ' && isPF'
        ),
        allIdIso05 = cms.string(
            'gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0'
            ' && electronID("mvaTrigV0") > 0.5'
            ' && userIsolation("User3Iso") < 0.15'
            ' && isPF'
        ),
        allIdIso00 = cms.string(
            "gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0"
            ' && electronID("mvaTrigV0") > 0.0'
            ' && userIsolation("User3Iso") < 0.15'
            ' && isPF'
        )
    ),
    addRunLumiInfo = cms.bool(True),
    isMC = cms.bool(False),
    eventWeight = cms.InputTag("PUweight","weight")
)

process.tnpNh0Mva = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0"),
    flags = cms.PSet(
          mvam01 = cms.string('electronID("mvaTrigV0") > -0.1'),
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

process.tnpNh0Mva05Riso15Pf = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Riso15"),
    flags = cms.PSet(
        pf = cms.string("isPF"),
    ),
)

process.tnpNh0Mva05Riso15PfCharge = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Riso15Pf"),
    flags = cms.PSet(
        chargeConsistency = cms.string("isGsfCtfScPixChargeConsistent()")
    ),
)

process.tnpNh0Mva05Riso15PfHL = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zNh0Mva05Riso15Pf"),
    flags = cms.PSet(
        #trgPath = cms.string('!triggerObjectMatchesByPath("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",1,0).empty()'),
        L1 = cms.string('!triggerObjectMatchesByFilter("hltL1sL1DoubleEG137").empty()'),
        HL = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoFilter").empty()'),
        SL = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDoubleFilter").empty()'),
        DZ = cms.string('!triggerObjectMatchesByFilter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsoDZ").empty()'),

        ZM = cms.string('!triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8PMMassFilter").empty()'),
        TH = cms.string('!triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsoFilter").empty()'),
        TS = cms.string('!triggerObjectMatchesByPath("HLT_Ele27_WP80_v*", 1, 0).empty()'),
    ),
    pairFlags = cms.PSet(),
    pairVariables = cms.PSet(
        dz = cms.string('abs(daughter(0).vz - daughter(1).vz)'),
        dR = cms.string('deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)'),
    ),
)

process.tnpNh0Mva05Riso15PfSL = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zHLNh0Mva05Riso15Pf"))
process.tnpNh0Mva05Riso15PfDZ = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zSLNh0Mva05Riso15PfHLSL"))

## Set variables
#process.tnpNh.variables.nh = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits")
process.tnpNh0Mva.variables.mva = cms.string('electronID("mvaTrigV0")')
process.tnpNh0Mva05Iso.variables.iso = cms.string('userIsolation("User1Iso")')
process.tnpNh0Mva05Iso.variables.diso = cms.string('userIsolation("User2Iso")')
process.tnpNh0Mva05Iso.variables.riso = cms.string('userIsolation("User3Iso")')
process.tnpNh0Mva05Riso15PfDZ.variables.dz = cms.string("userFloat('dz')")

process.tnpNh0Mva00Iso = process.tnpNh0Mva05Iso.clone(tagProbePairs = cms.InputTag("zNh0Mva00"))
process.tnpNh0Mva00Riso15Pf = process.tnpNh0Mva05Riso15Pf.clone(tagProbePairs = cms.InputTag("zNh0Mva00Riso15"))
process.tnpNh0Mva00Riso15PfHL = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zNh0Mva00Riso15Pf"))
process.tnpNh0Mva00Riso15PfSL = process.tnpNh0Mva05Riso15PfSL.clone(tagProbePairs = cms.InputTag("zHLNh0Mva00Riso15Pf"))
process.tnpNh0Mva00Riso15PfDZ = process.tnpNh0Mva05Riso15PfDZ.clone(tagProbePairs = cms.InputTag("zSLNh0Mva00Riso15PfHLSL"))
process.tnpNh0Mva00Riso15PfCharge = process.tnpNh0Mva05Riso15PfCharge.clone(
    tagProbePairs = cms.InputTag("zNh0Mva00Riso15Pf"),
)

process.tnpNh0Mva09Riso15PfHL = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zNh0Mva09Riso15Pf"))
process.tnpNh0Mva09Riso15PfSL = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zHLNh0Mva09Riso15Pf"))
process.tnpNh0Mva09Riso15PfDZ = process.tnpNh0Mva05Riso15PfHL.clone(tagProbePairs = cms.InputTag("zSLNh0Mva09Riso15PfHLSL"))

process.goodJets = cms.EDFilter("CMGCleanJetSelector",
    debug = cms.untracked.bool(False),
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
        cms.InputTag("goodElectrons"),
    ),
    overlapDeltaR = cms.double(0.5),
    #cleanMethod = cms.untracked.string("subtract"),
    cleanMethod = cms.untracked.string("subtractAndRestore"),
    #cleanMethod = cms.untracked.string(""),
    minPt = cms.untracked.double(30),
    maxEta = cms.untracked.double(2.5),
    minNumber = cms.uint32(2),
    maxNumber = cms.uint32(999),
)

if triggerMode == 'DoubleElectron':
    process.hltHighLevel.HLTPaths = ["HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v*",]
    # Require tag to matched to hard leg of HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v* path
    process.tag.cut = process.tag.cut.value() + ' && !triggerObjectMatchesByFilter("hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsoFilter").empty()'
else:
    process.hltHighLevel.HLTPaths = ["HLT_Ele27_WP80_v*",]
    process.tag.cut = process.tag.cut.value() + ' && !triggerObjectMatchesByPath("HLT_Ele27_WP80_v*", 1, 0).empty()'

process.p00 = cms.Path(
    process.hltHighLevel * process.goodOfflinePrimaryVertices * process.PUweight
  * process.patMuonsWithRelIso * process.goodMuons
  * process.patElectronsWithRelIso * process.goodElectrons
  * process.goodJets

  * process.tag 
  * process.tagHL * process.tagSL
  * process.probe 
  * process.probeNh0 
  * process.probeNh0Mva00 
  * process.probeNh0Mva00Riso15 
  * process.probeNh0Mva00Riso15Pf 
  * process.probeNh0Mva00Riso15PfHLSL

  * process.zNh0Mva00 * process.tnpNh0Mva00Iso
  * process.zNh0Mva00Riso15 * process.tnpNh0Mva00Riso15Pf 

  ## HL eff
  * process.zNh0Mva00Riso15Pf       * process.tnpNh0Mva00Riso15PfHL
  * process.zHLNh0Mva00Riso15Pf     * process.tnpNh0Mva00Riso15PfSL
  * process.zSLNh0Mva00Riso15PfHLSL * process.tnpNh0Mva00Riso15PfDZ

  * process.tnpNh0Mva00Riso15PfCharge
)

process.p05 = cms.Path(
    process.hltHighLevel * process.goodOfflinePrimaryVertices * process.PUweight
  * process.patMuonsWithRelIso * process.goodMuons
  * process.patElectronsWithRelIso * process.goodElectrons
  * process.goodJets

  * process.tag 
  * process.tagHL * process.tagSL
  * process.probe 
  * process.probeNh0 
  * process.probeNh0Mva05 
  * process.probeNh0Mva05Riso15 
  * process.probeNh0Mva05Riso15Pf 
  * process.probeNh0Mva05Riso15PfHLSL

  * process.z * process.tnpNh
  * process.zNh0 * process.tnpNh0Mva
  * process.zNh0Mva05 * process.tnpNh0Mva05Iso
  * process.zNh0Mva05Riso15 * process.tnpNh0Mva05Riso15Pf 

  * process.zNh0Mva05Riso15Pf       * process.tnpNh0Mva05Riso15PfHL
  * process.zHLNh0Mva05Riso15Pf     * process.tnpNh0Mva05Riso15PfSL
  * process.zSLNh0Mva05Riso15PfHLSL * process.tnpNh0Mva05Riso15PfDZ

  * process.tnpNh0Mva05Riso15PfCharge
)

## Special path for B2G reference
process.tagS = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("tag"),
    cut = cms.string('dB < 0.02 && electronID("mvaTrigV0") > 0.9'),
)

process.probeS = process.probe.clone(
    cut = cms.string('pt > 20 && dB < 0.02')
)
process.probeSIdIso = process.probe.clone(
    cut = cms.string(
        ' dB < 0.02 && electronID("mvaTrigV0") > 0.9 '
        ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0 '
        ' && userIsolation("User3Iso") < 0.10 '
        ' && isPF'
    ),
)

process.zS    = process.z.clone(decay = cms.string("tagS@+ probeS@-"   ))
process.zSTrg = process.z.clone(decay = cms.string("tagS@+ probeSIdIso@-"))
process.tnpS = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zS"),
    flags = cms.PSet(
        idIso = cms.string(
            'electronID("mvaTrigV0") > 0.9 '
            ' && gsfTrack.trackerExpectedHitsInner.numberOfHits <= 0 '
            ' && userIsolation("User3Iso") < 0.10 '
            ' && isPF'
        ),
    )
)
process.tnpSTrg = process.tnpNh.clone(
    tagProbePairs = cms.InputTag("zSTrg"),
    flags = cms.PSet(
        TS = cms.string('!triggerObjectMatchesByPath("HLT_Ele27_WP80_v*", 1, 0).empty()'),
    ),
    pairFlags = cms.PSet(),
    pairVariables = cms.PSet(
        dz = cms.string('abs(daughter(0).vz - daughter(1).vz)'),
        dR = cms.string('deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)'),
    ),
)

process.pB2G = cms.Path(
    process.hltHighLevel * process.goodOfflinePrimaryVertices * process.PUweight
  * process.patMuonsWithRelIso * process.goodMuons
  * process.patElectronsWithRelIso * process.goodElectrons
  * process.goodJets

  * process.tag
  * process.tagS
  * process.probeS
  * process.probeSIdIso

  * process.zS * process.tnpS
  * process.zSTrg * process.tnpSTrg
)
