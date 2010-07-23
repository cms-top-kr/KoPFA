
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_10_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_1_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_2_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_3_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_4_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_5_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_6_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_7_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_8_2.root',
		'rfio:/castor/cern.ch/user/b/beaudett/grid/CMSSW361p2/PATTUPLES-EMURELAXEDISO/Wenu/Wenu/patTuple_PF2PAT_9_2.root',
	)
)
