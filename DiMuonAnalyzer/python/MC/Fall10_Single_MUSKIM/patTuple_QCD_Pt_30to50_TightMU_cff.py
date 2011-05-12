
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_10_1_JDM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_11_1_QWE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_12_1_fXU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_13_1_cDH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_14_1_uDb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_15_1_Ue7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_16_1_VJr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_17_1_Nw2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_18_1_3KN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_19_1_i08.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_1_1_lq9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_20_1_87H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_21_1_1L7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_22_1_yF3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_23_1_HCY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_24_1_kic.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_25_1_0P5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_26_1_q4M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_27_1_hPi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_28_1_lKo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_29_1_LH6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_2_1_TDe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_30_1_eW3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_31_1_jas.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_32_1_0SM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_33_1_keW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_34_1_9O5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_3_1_q7F.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_4_1_e6J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_5_1_KnB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_6_1_9Co.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_7_1_ZVa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_8_1_SDT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/QCD_Pt_30to50/patTuple_skim_9_1_3ip.root',
]
        )
