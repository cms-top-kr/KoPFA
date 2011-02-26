
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_10_1_Ue5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_11_1_jXE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_12_1_3JT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_13_1_9QH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_14_1_x5t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_15_1_8HX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_16_1_hSX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_17_1_AhT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_18_1_Qft.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_19_1_6Wm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_1_1_SvZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_20_1_dz7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_21_1_cD6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_22_1_bSB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_23_1_enW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_24_1_QbG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_25_1_Xiz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_26_1_D7Z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_27_1_CTs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_28_1_2Dt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_29_1_keC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_2_1_kcf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_30_1_wBK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_31_1_ray.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_32_1_9jU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_33_1_dYL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_34_1_a0R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_3_1_YI4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_4_1_BR4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_5_1_48d.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_6_1_jDy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_7_1_NYC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_8_1_dyF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_30to50/patTuple_skim_9_1_NNu.root',
]
        )
