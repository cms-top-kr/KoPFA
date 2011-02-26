
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_10_0_l3U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_11_0_mIE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_12_0_Sgc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_13_0_n7F.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_14_0_r2h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_15_0_CGg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_16_0_xUD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_17_1_wzU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_18_1_l21.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_19_1_Gdf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_1_1_3Uc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_20_1_V1z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_21_1_bUz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_22_1_6hx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_23_0_9Sg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_2_1_rgc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_3_1_3iq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_4_1_dFC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_5_0_8i5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_6_0_rx3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_7_0_Jdq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_8_1_S22.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_jetfixed/QCD_Pt_470to600/patTuple_skim_9_1_Txc.root',
]
        )
