
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_10_1_whh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_11_1_ZoF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_12_1_28C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_13_1_Ob1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_14_1_ZWX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_15_1_ccU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_16_1_jYk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_17_1_se0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_18_1_INV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_19_1_0cP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_1_1_OO1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_20_1_HYI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_21_1_uEr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_22_1_wyk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_23_1_yN3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_2_1_GfN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_3_1_KK1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_4_1_TZg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_5_1_Q5A.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_6_1_8FK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_7_1_8hr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_8_1_fvH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/Zmm/patTuple_skim_9_1_yc9.root',
]
        )
