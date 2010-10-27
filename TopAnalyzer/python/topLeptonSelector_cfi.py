import FWCore.ParameterSet.Config as cms

from PFAnalyses.CommonTools.Selectors.muonSelectorPSet_cff import muonSelectorPSet
from PFAnalyses.CommonTools.Selectors.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose = False 
muonId.dxy = 0.02
muonId.eta = 2.5
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

from PFAnalyses.CommonTools.Selectors.electronSelectorPSet_cff import electronSelectorPSet
from PFAnalyses.CommonTools.Selectors.newElectronIsoSelectorPSet_cff import electronIsoSelectorPSet

Electrons = cms.EDProducer(
    "KoElectronSelector",
    version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    electronIdSelector = electronSelectorPSet,
    electronIsoSelector = electronIsoSelectorPSet,
)

