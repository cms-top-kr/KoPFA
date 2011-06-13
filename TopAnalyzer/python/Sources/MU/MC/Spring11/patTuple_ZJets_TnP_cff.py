
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_100_1_Z0d.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_101_1_5bi.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_102_1_jWZ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_103_1_Isp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_104_1_lFD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_105_1_XVp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_106_1_7ml.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_107_1_0ms.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_108_1_cwf.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_109_1_G9y.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_10_1_rYF.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_110_1_0yK.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_111_1_36N.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_112_1_JPb.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_113_1_qFy.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_114_1_qYE.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_115_1_J22.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_116_1_0j3.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_117_1_y81.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_118_1_Bnr.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_119_1_4Gz.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_11_1_R4u.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_120_1_plY.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_121_1_y5d.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_122_1_pCM.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_123_1_nYK.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_124_1_Crp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_125_2_xCs.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_126_1_PkA.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_127_1_64m.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_128_1_kGQ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_129_1_MVH.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_12_1_62f.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_130_1_YUN.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_131_1_3XG.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_132_1_zlc.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_133_1_aEl.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_134_1_mjJ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_135_1_znf.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_136_1_z3b.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_137_1_Gke.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_138_1_dBs.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_139_1_sLS.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_13_1_iaN.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_140_1_a8P.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_141_1_mlg.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_142_1_5OD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_143_1_I2X.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_144_1_xWU.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_145_1_Pm4.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_146_1_UBz.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_147_2_xdf.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_148_1_Hgn.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_149_2_Qj2.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_14_1_MBk.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_150_1_oMR.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_151_1_D67.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_152_1_6Cu.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_153_1_bRT.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_154_1_zN8.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_155_1_UIB.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_156_1_ILr.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_157_1_f8z.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_158_1_XwD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_159_1_o34.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_15_1_45f.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_160_1_Drb.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_161_1_k0h.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_162_1_I1s.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_163_1_40a.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_164_1_TF7.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_165_1_Njz.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_166_1_de3.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_167_1_NW8.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_168_1_AZx.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_169_1_IC8.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_16_1_fDp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_170_1_HwW.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_171_1_xCN.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_172_1_vTF.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_173_1_kS1.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_174_1_ImO.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_175_1_9CW.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_176_1_37k.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_177_1_twY.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_178_1_W0l.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_179_1_6vE.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_17_1_cWo.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_180_1_mMf.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_181_1_NEl.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_182_1_1fn.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_183_1_Rft.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_184_1_xA7.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_185_1_Mqb.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_186_1_pkI.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_187_1_u1N.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_188_1_tHR.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_189_1_kPV.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_18_1_47T.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_190_1_I9q.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_191_1_zT7.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_192_1_NCp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_193_1_2rY.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_194_1_e4Y.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_195_1_ebP.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_196_1_d1j.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_197_1_Ac3.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_198_1_ijA.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_199_1_ZKw.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_19_1_Jac.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_1_1_LvJ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_200_1_qiw.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_20_1_nda.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_21_1_sFJ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_22_1_q8D.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_23_1_nBD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_24_1_rf4.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_25_1_ZZo.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_26_1_re1.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_27_1_H1I.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_28_1_wGS.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_29_1_Vjx.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_2_1_dTM.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_30_1_pRS.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_31_1_gMI.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_32_1_Huc.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_33_1_iBO.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_34_1_zjH.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_35_1_6VL.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_36_1_MZC.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_37_1_aou.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_38_1_1Nx.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_39_1_YEl.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_3_1_G2c.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_40_1_4Op.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_41_1_S0l.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_42_1_5Yh.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_43_1_Ifm.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_44_1_ZwL.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_45_1_jEv.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_46_1_9y1.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_47_1_mkz.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_48_1_6Ll.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_49_1_Vm8.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_4_1_iAr.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_50_1_XGv.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_51_1_KzD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_52_1_Ldm.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_53_1_bf9.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_54_1_Nqe.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_55_1_e9L.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_56_1_euu.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_57_1_87i.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_58_1_Nhy.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_59_1_mtz.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_5_1_ioh.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_60_1_6lQ.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_61_1_XT4.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_62_1_Y7t.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_63_1_Gdb.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_64_1_ZmN.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_65_1_ctS.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_66_1_NBD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_67_1_rGt.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_68_1_oLi.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_69_1_4yX.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_6_1_eTm.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_70_1_huB.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_71_1_Z2p.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_72_1_aNk.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_73_1_2mp.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_74_1_odo.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_75_1_sI6.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_76_1_iRa.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_77_1_QTt.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_78_1_Am0.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_79_1_cqg.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_7_1_xLV.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_80_1_eSw.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_81_1_PLB.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_82_1_tRk.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_83_1_dDD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_84_1_1Cq.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_85_1_98X.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_86_1_dt6.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_87_1_3XD.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_88_1_e4M.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_89_1_eDU.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_8_1_C8m.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_90_1_4dF.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_91_1_9BT.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_92_1_xvi.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_93_1_0ck.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_94_1_kU5.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_95_1_V74.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_96_1_nmm.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_97_1_w9A.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_98_1_GR0.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_99_1_NLn.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuTnP/MC/20110610_1/ZJets/patTuple_skim_9_1_grQ.root',
]
        )