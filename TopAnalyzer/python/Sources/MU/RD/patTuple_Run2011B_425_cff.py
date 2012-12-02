
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_100_0_ZvQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_101_0_MOH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_102_0_ezv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_103_0_T8G.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_104_0_BTC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_105_0_0rN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_106_0_Xr1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_107_0_AKS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_108_0_BRD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_109_0_NBk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_10_1_rHg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_110_0_Nc8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_111_0_UxY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_112_0_3Ce.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_113_0_l1J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_114_0_xXV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_115_0_cdk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_116_0_pXW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_117_0_kpu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_118_0_JTI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_119_0_b1z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_11_1_Drw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_120_0_Hf1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_121_0_bLr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_122_0_8c2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_123_0_RLO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_124_0_zVf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_125_0_jkc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_126_0_tbh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_127_0_gXL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_128_0_aMI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_129_0_9pu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_12_1_euY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_130_0_B79.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_131_0_PaA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_132_0_ClK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_133_0_Gps.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_134_0_9k2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_135_0_yg3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_136_0_zch.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_137_0_cAM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_138_0_PEr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_139_0_iV9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_13_1_sNu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_140_0_Csf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_141_0_Ptt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_142_0_e2k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_143_0_qM2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_144_0_n7b.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_145_0_Bqm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_146_0_Tv3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_147_0_nZl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_148_0_BWe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_149_0_GNf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_14_1_ghV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_150_0_lnC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_151_0_R4Q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_152_0_9Lx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_153_0_LwY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_154_0_Ck8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_155_0_Ecj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_156_0_l3v.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_157_0_VpL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_158_0_qX9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_15_1_qK5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_16_1_Ieo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_17_1_TSM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_18_1_hY5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_19_1_kwc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_1_1_JWT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_20_1_X33.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_21_1_76W.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_22_1_KxW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_23_1_s9g.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_24_1_R3D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_25_1_7lK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_26_1_2vq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_27_1_NYU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_28_1_8SB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_29_1_x7c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_2_1_SmM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_30_1_e75.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_31_1_5PY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_32_1_EN3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_33_1_t9V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_34_1_oTt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_35_1_fA2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_36_1_cC6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_37_1_2TQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_38_1_ieb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_39_0_UTB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_3_1_ZP5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_40_0_Myo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_41_0_tEC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_42_0_c1b.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_43_0_lNq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_44_0_zKu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_45_0_H1j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_46_0_3WU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_47_0_69j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_48_0_M2m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_49_0_c8i.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_4_1_9Ry.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_50_0_Tsk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_51_0_Lg1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_52_0_HPd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_53_0_Bqa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_54_0_olH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_55_0_Co2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_56_0_l15.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_57_0_Tor.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_58_0_6Bg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_59_0_g2H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_5_1_HJz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_60_0_zZf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_61_0_dQV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_62_0_x5u.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_63_0_SVY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_64_0_I07.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_65_0_TCo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_66_0_vMb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_67_0_i3U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_68_0_WcP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_69_0_Tkl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_6_1_9wq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_70_0_80X.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_71_0_AkY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_72_0_pWR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_73_0_8Wz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_74_0_vzS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_75_0_wpG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_76_0_K78.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_77_0_04j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_78_0_qPv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_79_0_PuQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_7_1_SZG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_80_0_sth.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_81_0_UkU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_82_0_vq4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_83_0_8aa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_84_0_maS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_85_0_Q8l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_86_0_pz6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_87_0_zWI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_88_0_51L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_89_0_D4B.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_8_1_vCp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_90_0_8Yg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_91_0_CLa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_92_0_HxD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_93_0_Oyk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_94_0_lRp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_95_0_568.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_96_0_coG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_97_0_dVp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_98_0_4Jb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_99_0_eXn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011B-PromptReco-v1/patTuple_skim_9_1_2Yd.root',
]
        )
