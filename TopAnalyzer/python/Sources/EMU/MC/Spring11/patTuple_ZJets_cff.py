
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_10_1_XGF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_11_1_VFY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_12_1_rwH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_13_1_mRp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_14_1_GaJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_15_1_TaD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_16_1_JyR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_17_1_mLY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_18_1_gdT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_19_1_eMb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_1_1_33a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_20_1_R9f.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_2_1_XRr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_3_1_He1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_4_1_XEC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_5_1_IwY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_6_1_K9P.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_7_1_wZ9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_8_1_gb7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/ZJets/patTuple_skim_9_1_EEt.root',
]
        )
