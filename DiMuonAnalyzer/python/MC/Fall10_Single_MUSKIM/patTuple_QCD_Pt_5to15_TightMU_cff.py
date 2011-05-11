
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_10_1_fLx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_11_1_XQa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_12_1_wMH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_13_1_3wz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_14_1_2vf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_15_1_iDD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_16_1_KOJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_17_1_Zfm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_1_1_oSZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_2_1_vii.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_3_1_jL0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_4_1_ANT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_5_1_iOS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_6_1_RT1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_7_1_7II.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_8_1_4de.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_5to15/patTuple_skim_9_1_P59.root',
]
        )
