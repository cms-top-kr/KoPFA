
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_10_2_Wyj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_11_2_RMl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_12_1_GBS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_13_1_qzM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_14_2_6Xc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_15_2_8kV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_16_2_4qJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_17_2_VWc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_18_2_QVJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_19_1_2qs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_1_1_s4f.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_20_1_AVt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_21_1_MyP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_22_1_qzX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_23_2_9xW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_24_2_UPL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_25_2_oeR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_26_3_rr2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_27_2_UeL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_28_1_y82.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_29_2_dXy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_2_1_EvY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_30_2_iTN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_31_1_FWO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_32_1_9Qf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_33_1_eVP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_34_2_p8L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_35_2_oo8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_36_1_3xB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_37_1_Qfp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_38_2_Y5X.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_39_2_Sv9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_3_1_4JO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_40_1_gei.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_41_3_61k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_42_1_9QY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_43_1_SPi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_44_1_wOn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_45_1_lIy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_46_1_ogr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_47_1_MIK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_48_3_HUU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_49_3_QnY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_4_1_5Am.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_50_1_Bvc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_51_2_8TF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_52_2_MYM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_53_1_i4c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_54_2_oSU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_55_2_Uyf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_56_1_YMe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_57_2_Aoj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_58_2_LbG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_59_3_zyY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_5_2_7Yz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_60_2_A9L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_61_2_xcD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_62_3_0Bn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_63_2_XBK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_64_1_BxT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_65_2_UOK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_66_4_wxf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_67_3_566.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_68_2_M9e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_69_2_n5f.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_6_2_88f.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_70_2_Cvv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_71_2_Yy5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_72_2_7jI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_73_1_WJE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_74_3_xEx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_75_2_0gL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_76_2_7N2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_77_1_oWa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_78_2_LQw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_79_2_HO3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_7_1_gyT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_80_1_by5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_81_1_KzZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_82_1_AOy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_83_2_g9z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_84_2_ERC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_8_1_xRL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-May10ReReco-v1/patTuple_skim_9_1_Xrq.root',

	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_100_0_PGZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_101_0_vuL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_102_0_lwg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_103_2_g3m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_104_3_cCu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_105_0_T9X.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_106_0_VYu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_107_0_HII.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_108_0_508.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_109_0_qEW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_10_1_Gqz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_110_0_hGo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_111_0_rjX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_112_0_0kJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_113_0_T6Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_114_0_xmg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_115_0_1Dz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_116_0_PYv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_117_0_k27.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_118_0_1zH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_119_0_FIY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_11_1_dLn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_120_0_RFP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_121_0_QUC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_122_0_NMi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_123_0_UfF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_124_0_Lgf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_125_0_5gY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_126_0_XrY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_127_0_DMY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_128_0_tBf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_129_0_ojw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_12_1_cH4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_130_0_Rcz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_131_0_Z5r.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_132_0_9YT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_133_0_u9m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_134_0_50l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_135_0_2oA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_136_0_HRc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_137_0_kDC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_138_0_l7m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_139_0_9Xy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_13_2_Yxc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_140_0_1Pn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_141_0_xjg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_142_0_P7s.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_143_0_fq8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_14_1_pWh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_15_1_yyy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_16_0_bMg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_17_0_wyX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_18_1_8Hy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_19_1_wWJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_1_1_olN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_20_1_T8f.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_21_1_kwJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_22_1_bGg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_23_0_MJn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_24_2_A05.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_25_1_4zr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_26_1_izY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_27_1_pAJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_28_1_eHu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_29_1_FzF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_2_1_IN6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_30_1_XHh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_31_0_D1N.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_32_1_0uo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_33_1_alb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_34_1_nxk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_35_1_ZAg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_36_1_UqG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_37_1_ZT6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_38_1_rr8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_39_1_Brw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_3_1_MoL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_40_1_L5c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_41_1_Q5i.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_42_1_wCD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_43_1_Emf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_44_1_Mou.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_45_1_qiL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_46_0_mSp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_47_0_ST2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_48_0_ZBb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_49_0_4Pa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_4_1_Vyc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_50_2_5Ee.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_51_0_Zd6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_52_0_5OW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_53_1_egj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_54_1_eLT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_55_2_oJp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_56_1_btz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_57_1_RF3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_58_1_9gS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_59_1_bZX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_5_1_PUA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_60_0_xCk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_61_1_2Yq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_62_1_WkC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_63_1_3GQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_64_1_4j3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_65_1_43Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_66_1_LdQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_67_1_CGk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_68_1_JZu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_69_1_iHw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_6_1_62p.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_70_1_8BK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_71_2_3to.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_72_1_MPi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_73_1_GtU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_74_1_FCZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_75_2_XCD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_76_1_gIK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_77_1_MOL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_78_1_a2J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_79_1_WM7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_7_1_3j0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_80_1_QoE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_81_1_X2d.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_82_0_Vf5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_83_0_CSy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_84_0_BCt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_85_0_EXy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_86_0_rXx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_87_0_G1R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_88_0_80v.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_89_0_0IM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_8_1_z9y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_90_0_dvp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_91_0_J9y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_92_0_uHm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_93_0_FxT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_94_0_2OV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_95_0_Rv5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_96_0_u8y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_97_0_kmk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_98_0_BFb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_99_0_cfq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v4/patTuple_skim_9_1_8b4.root',

	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_10_1_zFS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_11_1_O44.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_12_2_YtH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_13_1_wyW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_14_2_Cco.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_15_2_knh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_16_1_K6c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_17_1_dLZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_18_1_tas.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_19_1_8OU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_1_1_fzj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_20_1_LDd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_21_1_MgZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_22_1_pxF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_23_1_4c7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_24_1_5By.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_25_1_OHt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_26_1_Gzv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_27_1_DMA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_28_3_qH7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_29_2_d6L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_2_1_nR6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_30_1_lTQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_31_1_FZN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_32_1_jkn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_33_1_3gs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_34_1_g5R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_35_2_haD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_36_1_rG1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_36_2_bGf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_37_1_puB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_38_2_P5C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_39_3_auK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_3_1_rsp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_3_2_pa7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_4_1_Dpj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_5_1_UmS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_6_3_8eC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_7_1_snQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_8_1_e54.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_8_2_yY7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-05Aug2011-v1/patTuple_skim_9_3_h0o.root',

	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_10_1_6Er.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_11_1_dnH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_12_1_qs4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_13_1_pBT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_14_1_AC1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_15_1_qSF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_16_1_PkD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_17_0_iLW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_18_0_Vil.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_19_0_Q3p.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_1_1_Qx9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_20_0_51z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_21_0_SCe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_22_1_J0Z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_23_1_aoG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_24_1_nKc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_25_0_y5d.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_26_1_J50.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_27_1_YUW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_28_1_5Q9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_29_0_dsq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_2_1_hZb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_30_1_g7l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_31_0_xbc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_32_0_00n.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_33_0_Bz7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_34_0_kfK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_35_0_Q6C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_36_0_1Dm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_37_0_Y3N.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_38_0_REg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_39_0_ern.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_3_1_T9M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_40_0_r0t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_41_0_edp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_42_0_jMj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_43_0_Gt4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_44_0_K33.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_45_0_cUg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_46_0_YGk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_47_0_52r.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_48_0_TXF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_49_0_UDY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_4_1_mRg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_50_0_gSa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_51_0_fhf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_52_0_59l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_53_0_c3V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_54_0_7lO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_55_0_3wx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_56_0_O96.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_57_0_BAM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_58_0_P5z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_59_0_BIm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_5_1_UCF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_60_0_edK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_61_0_4Jv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_62_0_Y0O.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_63_0_9cU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_6_1_jQn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_7_1_vGE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_8_1_bUW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Nov10/Run2011A-PromptReco-v6/patTuple_skim_9_1_baK.root',
]
        )
