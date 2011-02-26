
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_10_1_Jlb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_11_1_AY5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_12_1_akE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_13_1_vQb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_14_1_ogE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_15_1_qUY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_16_1_WKJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_17_1_SJn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_18_1_d1h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_19_1_UoN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_1_1_z9j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_20_1_7Tk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_21_1_PER.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_22_1_87c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_23_1_ej8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_24_1_23R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_25_1_Fph.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_26_1_XJ6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_27_1_iSW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_28_1_nB3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_29_1_buM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_2_1_7Kr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_30_1_SVE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_31_1_TqM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_32_1_lpK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_33_1_Ulr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_34_1_yZK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_3_1_8R8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_4_1_Nqa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_5_1_lmD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_6_1_RZC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_7_1_XJ1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_8_1_Rqn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_120to170/patTuple_skim_9_1_ZBM.root',
]
        )
