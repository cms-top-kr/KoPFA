
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring()
)
source.fileNames.extend([
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_0.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_1.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_10.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_11.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_12.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_13.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_14.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_15.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_16.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_17.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_18.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_19.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_2.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_20.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_21.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_22.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_3.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_4.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_5.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_6.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_7.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_8.root',
    '/store/cmst3/user/cmgtools/CMG/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM/V5/PAT_CMG_V5_4_1/cmgTuple_9.root',
])
