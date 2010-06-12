
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_10_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_11_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_1_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_2_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_3_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_4_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_5_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_6_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_7_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_8_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_136588-9999999/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_9_1.root',
	)
)
