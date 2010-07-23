
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_1_2.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_2_3.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_3_1.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_4_2.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_5_2.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_7_2.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_8_2.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/090610/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_9_2.root',
	)
)
