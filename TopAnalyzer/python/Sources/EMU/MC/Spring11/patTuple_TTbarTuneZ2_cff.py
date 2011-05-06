
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_10_2_ZBy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_11_1_tY2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_12_1_Jsf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_1_1_fNd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_2_1_uHa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_3_1_VH6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_4_2_1oI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_5_2_7g8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_6_1_zmc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_7_2_YnM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_8_1_6PS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/TTbar/patTuple_skim_9_1_cHV.root',
]
        )
