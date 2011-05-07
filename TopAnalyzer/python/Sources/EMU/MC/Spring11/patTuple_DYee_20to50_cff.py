
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_10_1_91o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_11_1_JMh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_12_1_iBx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_13_1_fAS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_14_1_jDI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_15_1_rcI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_16_1_37l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_17_1_lR3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_18_1_6Sv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_19_1_xCW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_1_1_8NA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_20_1_Vvi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_21_1_ed0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_2_1_vDI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_3_1_D2z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_4_1_mJh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_5_1_QO6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_6_1_6bA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_7_1_bXK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_8_1_vmr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYee_20to50/patTuple_skim_9_1_VQG.root',
]
        )
