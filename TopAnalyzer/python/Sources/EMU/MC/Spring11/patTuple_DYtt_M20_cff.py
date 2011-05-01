
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_10_2_Kh8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_11_2_Wjo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_12_2_mpR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_13_2_4kF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_14_2_wBo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_15_2_MUF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_16_2_mWs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_17_2_cL8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_18_2_bwN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_19_2_YRE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_1_2_NYj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_20_2_HiN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_21_2_M3g.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_2_2_QXn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_3_2_22U.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_4_2_v1k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_5_2_xXR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_6_2_m62.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_7_2_FdE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_8_2_Hi8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYtt_20to50/patTuple_skim_9_2_fWf.root',
]
        )
