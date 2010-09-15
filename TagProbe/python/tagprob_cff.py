import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tagprob.root')
)

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
   #'file:/afs/cern.ch/user/t/tjkim/public/forColin/pf2pat_iso.root',
#   '/store/data/Run2010A/Mu/RECO/v4/000/142/136/1A788144-289E-DF11-AC2A-001D09F2960F.root'
#    )
#)
process.load("KoPFA.DiMuonAnalyzer.MC.Spring10.patTuple_Zmumu_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose =False 
muonId.dxy = 0.02
muonId.eta = 2.5
muonId.pt = 20
from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonIso = muonIsoSelectorPSet.clone()

process.tagMuons = cms.EDProducer(
    "KoMuonRefSelector",
    version = cms.untracked.int32( 4 ),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIso,
)

process.probeMuons = cms.EDProducer(
    "KoMuonRefSelector",
    version = cms.untracked.int32( 0 ),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIso,
)


process.IdMuons = cms.EDProducer(
    "KoMuonRefSelector",
    version = cms.untracked.int32( 1 ),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIso,
)

process.IsoMuons = cms.EDProducer(
    "KoMuonRefSelector",
    version = cms.untracked.int32( 4 ),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIso,
)

process.tagProbesId = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tagMuons@+ probeMuons@-"), # charge coniugate states are implied; 'tagMuons' and 'trkProbes' should be collections of Candidates
    cut   = cms.string("70 < mass < 110"),
)

process.tagProbesIso = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tagMuons@+ IdMuons@-"), # charge coniugate states are implied; 'tagMuons' and 'trkProbes' should be collections of Candidates
    cut   = cms.string("70 < mass < 110"),
)

process.tnpTreeId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tagProbesId"),
    arbitration   = cms.string("OneProbe"), ## that is, use only tags associated to a single probe.
    # probe variables
    variables = cms.PSet(
        pt     = cms.string("pt"),
        abseta = cms.string("abs(eta)"),
    ),
    # choice of what defines a 'passing' probe
    flags = cms.PSet(
        isMuon = cms.InputTag("IdMuons"),
    ),
    ## DATA-related info
    addRunLumiInfo = cms.bool(True),
    ## MC-related info
    isMC = cms.bool(False),
)

process.tnpTreeIso = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tagProbesIso"),
    arbitration   = cms.string("OneProbe"), ## that is, use only tags associated to a single probe.
    # probe variables
    variables = cms.PSet(
        pt     = cms.string("pt"),
        abseta = cms.string("abs(eta)"),
    ),
    # choice of what defines a 'passing' probe
    flags = cms.PSet(
        isIso = cms.InputTag("IsoMuons"),
    ),
    ## DATA-related info
    addRunLumiInfo = cms.bool(True),
    ## MC-related info
    isMC = cms.bool(False),
)

process.p = cms.Path(
                      process.tagMuons
                     *process.probeMuons
                     *process.IdMuons
                     *process.IsoMuons
                     *process.tagProbesId
                     *process.tagProbesIso
                     *process.tnpTreeId
                     *process.tnpTreeIso
)


