
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_10_1_XYp.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_1_1_P2b.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_2_2_uFR.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_3_1_D9T.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_4_1_nHq.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_5_1_tYX.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_6_2_WhF.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_7_1_x9F.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_8_2_Eqh.root',
		'rfio:/castor/cern.ch/user/w/wreece/SDMUONFILTER/MC/CMSSW_3_6_1_patch3/050710/Wmunu/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_9_1_ep4.root',
	)
)
