
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_10_0_Ua3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_11_0_2yR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_12_0_wUT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_13_0_2mS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_14_0_sZH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_15_0_oyl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_16_0_0jM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_17_0_NP6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_18_0_JB6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_19_0_TSr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_1_1_PKn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_20_0_3Lc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_21_0_ZFu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_22_0_oXg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_23_0_DqJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_24_0_ZSX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_25_1_pfl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_26_1_Yfo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_27_1_pri.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_28_1_AjG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_29_1_L7t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_2_1_7Lz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_30_1_Zqj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_31_1_JkC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_32_1_tCu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_33_1_Ku5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_3_1_tgf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_4_1_cAA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_5_1_AK2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_6_1_x26.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_7_0_BgB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_8_0_D17.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_300to470/patTuple_skim_9_0_wsI.root',
]
        )
