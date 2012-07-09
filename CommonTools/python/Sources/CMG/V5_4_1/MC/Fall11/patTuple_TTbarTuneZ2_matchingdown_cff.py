
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring()
)
source.fileNames.extend([
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_0.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_1.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_10.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_11.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_12.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_13.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_14.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_15.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_16.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_17.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_18.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_19.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_2.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_20.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_21.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_22.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_3.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_4.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_5.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_6.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_7.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_8.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/patTuple_9.root',
])
