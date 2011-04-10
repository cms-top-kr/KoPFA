
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_10_1_1z3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_11_1_Htk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_1_1_hLM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_2_1_emO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_3_1_6iL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_4_1_Sv6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_5_1_h3m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_6_1_WLy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_7_1_i94.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_8_1_8Gv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/ZZ/patTuple_skim_9_1_YZm.root',
]
        )
