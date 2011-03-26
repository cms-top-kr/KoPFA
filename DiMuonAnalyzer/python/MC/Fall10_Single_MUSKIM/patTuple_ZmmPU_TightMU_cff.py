
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_10_0_bIF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_11_0_25M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_12_0_BnX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_13_0_SX9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_14_1_SiS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_15_0_zf6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_16_0_QjD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_17_0_PO4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_18_0_XZr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_19_1_hai.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_1_1_RmI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_20_1_rAt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_21_1_tja.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_22_1_QsF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_23_1_2AQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_2_1_Fmo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_3_1_Dsz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_4_1_unz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_5_1_Nv2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_6_1_KOy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_7_1_Azw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_8_1_4aw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/ZmmPU/patTuple_skim_9_1_uPF.root',
]
        )
