import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from KoPFA.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose = False 
muonId.dxy = 0.02
muonId.eta = 2.4
muonId.pt = 20

Muons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( -1 ),# dxy, pt, eta
    cut = cms.vstring("pt","eta","dxy","TOPDIL"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("acceptedMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,

)

Electrons = cms.EDProducer(
    "KoElectronSelector",
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    etacut = cms.untracked.double( 2.4 ),
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    mvacut = cms.untracked.double(-0.1),
    usemva = cms.untracked.bool(False),
    eidName = cms.untracked.string("eidTightMC"),
    eidBitMask = cms.untracked.int32(5), # = 101, ID and cms.Conversion
)

IsolatedMuons = cms.EDProducer(
    "KoMuonSelector",
    version = cms.untracked.int32( -1 ),# dxy, pt, eta
    cut = cms.vstring("pt","eta","dxy","TOPDIL"),
    isocut = cms.vstring(),
    relIso = cms.untracked.double(0.20),
    muonLabel  = cms.InputTag("acceptedMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,

)

IsolatedElectrons = cms.EDProducer(
    "KoElectronSelector",
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    etacut = cms.untracked.double( 2.4 ),
    relIso = cms.untracked.double(0.17),
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    mvacut = cms.untracked.double(-0.1),
    usemva = cms.untracked.bool(False),
    eidName = cms.untracked.string("eidTightMC"),
    eidBitMask = cms.untracked.int32(5), # = 101, ID and cms.Conversion
)


