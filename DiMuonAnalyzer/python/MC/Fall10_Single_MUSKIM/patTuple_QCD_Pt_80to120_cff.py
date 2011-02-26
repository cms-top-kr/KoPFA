
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_10_0_GoD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_11_0_U3E.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_12_0_UTb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_13_0_nHb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_14_0_G5P.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_15_0_VLS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_16_0_muy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_17_0_UOG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_18_0_2s9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_19_0_fnK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_1_2_smd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_20_0_mV1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_21_0_6Nb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_22_0_IEH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_23_0_dpi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_24_0_zNI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_25_0_IJN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_26_0_bGG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_27_0_qt1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_28_0_buy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_29_0_5GD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_2_1_RcY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_30_0_HL1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_31_0_MDp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_32_0_cms.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_33_0_WPj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_34_0_OlH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_3_1_zdV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_4_1_A2O.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_5_1_8IL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_6_1_Kr5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_7_1_hhj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_8_1_UBO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_80to120/patTuple_skim_9_0_Vly.root',
]
        )
