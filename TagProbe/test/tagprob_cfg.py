import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
   'file:/afs/cern.ch/user/t/tjkim/public/forColin/pf2pat_iso.root',
    )
)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

process.tagMuons = cms.EDFilter("PATMuonRefSelector",
  src = cms.InputTag("patMuons"),
  cut = cms.string("isGlobalMuon && muonID('GlobalMuonPromptTight') && !triggerObjectMatchesByFilter('hltSingleMu3L3Filtered3').empty()"),   ## Global Mu P.T. matched to HLT_Mu3

)

process.probeMuons = cms.EDFilter("PATMuonRefSelector",
  src = cms.InputTag("patMuons"),
  cut = cms.string("isGlobalMuon && pt > 3 && abs(eta) < 2.4"),   ## Global Mu, pt > 3, eta < 2.4
)

process.tagProbes = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tagMuons@+ probeMuons@-"), # charge coniugate states are implied; 'tagMuons' and 'trkProbes' should be collections of Candidates
    cut   = cms.string("70 < mass < 110"),
)

process.tnpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tagProbes"),
    arbitration   = cms.string("OneProbe"), ## that is, use only tags associated to a single probe.
    # probe variables
    variables = cms.PSet(
        pt     = cms.string("pt"),
        abseta = cms.string("abs(eta)"),
    ),
    # choice of what defines a 'passing' probe
    flags = cms.PSet(
        isGlobalMuon = cms.string("isGlobalMuon"),
        isHLTMu3     = cms.string("!triggerObjectMatchesByFilter('hltSingleMu3L3Filtered3').empty()"),  
    ),
    ## DATA-related info
    addRunLumiInfo = cms.bool(True),
    ## MC-related info
    isMC = cms.bool(False), ## on MC you can set this to true, add some parameters and get extra info in the tree.
)

process.p = cms.Path(
                      process.tagMuons
                     *process.probeMuons
                     *process.tagProbes
                     *process.tnpTree
)
