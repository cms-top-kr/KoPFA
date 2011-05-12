
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_10_1_VJo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_11_1_Fa4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_12_1_qLt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_13_1_AHJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_14_1_VaG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_15_1_MDG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_16_1_auI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_17_1_2tf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_18_1_14h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_19_1_Pf3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_1_1_qw9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_20_1_OPq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_21_1_fKS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_22_1_2ew.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_23_1_S5H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_24_1_rUK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_25_1_GQR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_26_1_NGX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_27_1_qKk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_28_1_y0k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_29_1_xYZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_2_1_pJb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_30_1_mvQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_31_1_9Kv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_32_1_pO1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_33_1_EtA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_3_1_7aT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_4_1_Tqt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_5_1_pV4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_6_1_zvb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_7_1_EAB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_8_1_cPx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_50to80/patTuple_skim_9_1_UeE.root',
]
        )
