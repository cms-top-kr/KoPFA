
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_10_0_1gL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_11_0_5eV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_12_0_SmO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_13_0_FGT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_14_0_dAT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_15_0_vyW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_16_0_THo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_17_0_7oM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_18_0_Mz5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_19_1_xeT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_1_1_dg8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_20_1_c5V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_21_1_Xby.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_22_1_sBU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_23_1_l4W.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_2_1_Gwi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_3_1_hx9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_4_1_rIb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_5_1_fmC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_6_1_vIu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_7_1_uHK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_8_1_dEh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/ZmmPU/patTuple_skim_9_1_P9s.root',
]
        )
