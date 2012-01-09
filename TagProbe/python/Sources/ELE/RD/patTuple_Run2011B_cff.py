
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_100_1_uVM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_101_1_c72.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_102_1_yK0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_103_1_6IH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_104_1_Ykr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_106_1_TNY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_107_1_Lgh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_108_1_6fx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_109_1_1qs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_10_1_2QC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_110_1_y6V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_111_1_TfH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_112_1_zvE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_113_1_q6N.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_114_1_1vi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_115_1_mCU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_116_1_9mw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_118_1_6LS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_119_1_icp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_11_1_fHu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_121_1_Oyl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_122_1_2fH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_123_1_ND5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_124_1_Tn5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_126_1_ZKv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_127_1_kmx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_128_1_MBx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_129_2_5uh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_12_1_HUL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_130_1_vYD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_131_1_j9S.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_132_1_fYU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_133_1_73H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_134_1_XaJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_135_1_5he.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_136_1_o4F.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_137_1_1H6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_138_1_vBU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_139_1_XM5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_140_1_Djr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_141_1_DlS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_142_1_17U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_143_1_j9U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_144_1_HgM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_145_1_z8u.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_146_1_YEE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_147_1_jzr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_148_1_CsH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_149_1_Jzw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_14_1_T00.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_153_1_P5p.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_15_1_tAa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_16_1_FT9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_17_1_zFl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_18_1_vY3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_19_1_6QG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_1_1_SdG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_20_1_dUM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_21_1_Cd3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_22_1_W4q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_23_1_0q8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_24_1_LUo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_25_1_X42.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_26_1_nIk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_27_1_OZk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_28_1_XvV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_29_1_cWV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_2_2_qyi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_30_1_U7H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_32_1_Xy8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_33_1_qTf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_34_1_YxK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_35_1_DFb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_36_1_Hog.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_37_1_bvp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_38_1_n65.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_39_1_Dg3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_3_1_JnX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_40_1_Hw6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_41_1_Iv8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_42_1_qaK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_44_1_n4P.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_45_1_Asa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_47_1_eGY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_49_1_esZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_4_1_dLN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_51_1_2b4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_52_1_aLd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_54_1_BP5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_55_1_8Ka.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_56_1_iqu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_57_1_QQR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_58_2_T6z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_59_1_ZKc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_5_1_iCL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_60_1_0RB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_61_1_BaB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_62_1_Glt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_63_1_DWu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_64_1_aog.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_65_1_1uq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_66_1_uQv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_67_1_LdM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_68_1_UA5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_69_1_EzC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_6_1_zQq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_70_1_RPY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_71_1_NZO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_72_1_NqO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_73_1_B1i.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_75_1_uA3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_76_1_GyO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_77_1_j8K.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_78_1_E0J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_79_1_Nlt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_7_1_UkL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_80_1_Go0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_81_1_MoZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_82_1_N1u.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_83_1_Vaf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_84_1_Y7A.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_85_1_z99.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_86_1_hDc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_87_1_Y53.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_88_1_LSA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_89_1_xrw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_8_1_vxC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_90_1_FTM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_91_1_gs7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_92_1_ox4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_93_1_fgM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_94_1_W5H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_95_1_8Z7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_96_1_VL5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_97_1_HnY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_98_1_7HB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_99_1_6lV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011B-PromptReco-v1-V2/patTuple_skim_9_1_qMl.root',
]
        )