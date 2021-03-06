
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_100_1_F4z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_101_0_Akw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_102_0_YUX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_103_0_3cP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_104_1_Btd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_105_1_ZyQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_106_1_MQr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_106_2_44g.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_107_1_8G0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_108_1_TSY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_109_1_6ja.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_110_1_8Wm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_110_2_G9j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_111_1_c67.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_112_1_lwN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_112_2_2oX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_113_1_Dgl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_114_1_gZm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_115_1_ppJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_115_2_h8k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_116_1_O0D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_116_2_j8E.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_117_1_9Ur.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_118_1_Y54.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_118_2_Ufz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_119_1_NBk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_119_3_hUZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_11_2_ekc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_120_1_0qI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_120_2_jpI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_121_2_L3U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_122_1_ZHk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_123_1_W5j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_124_1_9vz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_125_2_CRr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_126_1_fwC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_127_1_Vw2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_128_1_mOH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_129_1_XtJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_12_2_a9k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_130_1_LFt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_131_1_iRW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_132_1_58e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_133_1_kYO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_134_2_qHC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_135_1_P3T.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_136_1_QVR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_137_1_wpj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_138_1_xAP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_138_2_5aN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_139_1_c0X.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_13_2_DEA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_140_1_AcF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_141_2_Mzp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_142_1_RxK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_143_1_2DV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_144_1_RVp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_144_2_5Sb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_145_1_zeC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_146_1_Kj1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_148_2_7tT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_149_2_GHm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_14_1_4k9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_150_1_VI0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_151_1_1ck.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_151_2_naQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_152_1_0Dl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_152_2_ly7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_153_2_XTM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_154_2_UNP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_155_1_uH4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_158_0_e7Q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_158_1_Arj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_159_0_rax.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_15_1_5db.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_16_2_yE5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_17_2_PQH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_18_2_BQx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_19_2_NAo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_20_2_c7t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_21_1_O1a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_22_2_wEQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_23_1_4wc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_24_3_BsZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_25_1_4sb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_26_2_MdZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_27_2_pNb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_28_2_ecw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_29_1_MJw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_2_2_r9o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_30_1_Rwl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_31_2_Dxq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_32_2_7Lh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_33_1_SM5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_34_2_vBL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_35_1_WH1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_36_2_YMo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_37_2_IKf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_38_1_bIe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_39_1_il7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_3_1_EXE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_40_1_Qcp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_41_2_ecT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_42_1_erV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_43_1_jOW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_44_1_aLO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_45_1_qPd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_46_1_K1O.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_47_2_jbt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_48_2_rKC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_49_2_PBN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_4_2_xWl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_50_2_aMC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_51_1_h8l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_52_0_NZb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_52_1_WGG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_56_0_siv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_56_1_BVE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_58_0_nEM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_58_1_NCb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_59_0_v0u.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_59_1_dwm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_5_1_wGX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_60_0_t8e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_60_1_cNF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_62_0_8kx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_64_0_ocj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_64_1_zeH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_65_0_Y68.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_65_1_o1K.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_66_0_e5d.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_66_1_tw7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_68_0_PpH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_69_0_gpl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_69_1_1wS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_6_2_vtZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_71_0_tB3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_71_1_OEz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_72_0_smd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_72_1_W95.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_75_0_Cx6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_75_1_eh3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_76_0_8La.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_79_0_EOQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_7_2_5WS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_83_0_79m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_84_0_ECO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_84_1_g0W.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_85_0_YxY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_85_1_yBJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_86_0_Kfo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_89_0_sSz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_8_1_MwI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_90_1_chJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_91_0_8BS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_92_0_ExB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_93_0_JR2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_93_1_7Cp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_94_0_27W.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_94_1_NPK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_96_0_lXq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_96_1_e2e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_97_0_niE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_97_1_y4Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_98_0_aZm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_98_1_0c6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/DYJetsToLL_M-10To50/patTuple_skim_9_1_6hw.root',
]
        )
