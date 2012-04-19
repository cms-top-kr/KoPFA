
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_105_1_omT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_106_0_G53.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_107_0_hzg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_108_0_D3Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_109_0_IKM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_115_0_Wws.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_117_0_oko.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_118_0_TZA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_120_0_qki.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_121_0_taA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_122_1_JSN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_124_2_bQa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_125_1_nTH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_127_0_5p3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_143_0_O0u.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_144_0_zXG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_146_0_L9N.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_147_0_JIR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_147_1_z8r.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_14_0_4x6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_154_2_Ide.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_156_0_khj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_157_0_Uqh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_158_0_wEA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_159_0_5Y4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_161_0_mdp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_163_0_o76.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_165_1_Sk4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_166_3_xaw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_168_1_FBq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_169_1_C4s.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_171_1_g5U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_173_0_Ld8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_17_2_z7P.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_181_0_N6L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_182_0_b2o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_183_0_lvH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_23_1_RIM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_29_0_Tr7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_34_0_el2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_36_0_Hwi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_37_0_0an.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_3_1_R1t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_43_3_BFP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_4_1_epa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_57_1_4tP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_5_1_NqE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_62_0_Mda.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_64_0_EBa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_66_0_1L1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_69_0_H74.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_6_1_qWK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_73_0_OJ3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_74_0_Hln.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_79_0_oIk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_80_0_iyp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_82_0_SJm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_83_0_yac.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_84_0_A4T.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_85_0_pcZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_8_2_shZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_92_0_vAO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/DoubleElectron_DecoupledIso/WJetsToLNu/patTuple_skim_93_0_OMo.root',
]
        )