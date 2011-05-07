
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_10_0_n2a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_11_1_vrU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_12_1_6BS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_13_1_16g.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_14_1_Bp4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_15_1_vTh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_16_1_J7z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_17_1_Hnz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_18_1_k3S.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_19_1_2wP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_1_2_G2s.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_20_1_Sh0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_21_0_lex.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_2_2_EeL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_3_1_EcB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_4_1_CO3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_5_1_oUx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_6_1_GAy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_7_1_XDz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_8_0_r5y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/DYmm_20to50/patTuple_skim_9_1_7hb.root',
]
        )
