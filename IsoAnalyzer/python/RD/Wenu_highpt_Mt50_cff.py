
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
                'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50-PAT/patTuple_PF2PAT.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_0.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_1.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_10.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_11.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_12.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_3.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_4.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_5.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_6.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_7.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_8.root',
		'rfio:/castor/cern.ch/user/b/beaudett/Skims/ElectronPlusMT50_EG_V4-PAT/patTuple_PF2PAT_9.root',
	)
)
