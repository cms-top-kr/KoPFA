
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_10_1_nBE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_11_1_KFQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_12_1_1wr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_13_1_FBD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_14_1_zqT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_15_1_wgW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_16_1_7pz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_17_1_JMn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_18_1_8VU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_19_1_fBb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_1_1_IxL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_20_1_3O7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_21_1_f6Z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_22_0_NgB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_23_0_b7j.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_24_0_Bpm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_2_1_ps2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_3_1_feJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_4_1_kMJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_5_1_MM8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_6_1_3Ui.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_7_1_Yx7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_8_1_usK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/ZJets/patTuple_skim_9_1_cje.root',
]
        )
