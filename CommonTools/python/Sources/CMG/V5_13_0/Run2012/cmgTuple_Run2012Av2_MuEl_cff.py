
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring()
)
source.fileNames.extend([
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_1.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_10.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_11.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_12.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_13.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_14.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_15.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_16.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_17.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_18.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_19.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_2.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_20.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_21.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_22.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_23.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_3.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_4.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_5.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_6.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_7.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_8.root',
		'/store/cmst3/user/cmgtools/CMG/MuEG/Run2012A-recover-06Aug2012-v1/AOD/PAT_CMG_V5_13_0/cmgTuple_9.root',
])
