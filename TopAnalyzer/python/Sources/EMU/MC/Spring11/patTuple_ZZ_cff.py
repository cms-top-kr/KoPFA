
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_10_1_dvH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_11_1_XLD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_1_1_mLS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_2_1_219.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_3_1_Hxd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_4_1_VJE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_5_1_mdF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_6_1_3bZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_7_1_iA6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_8_1_GQk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZZ/patTuple_skim_9_1_CAs.root',
]
        )
