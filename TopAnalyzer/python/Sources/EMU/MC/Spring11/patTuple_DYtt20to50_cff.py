
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_10_1_SdV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_11_1_qRW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_12_1_FDX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_13_2_9Hn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_14_1_Ok5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_15_1_hEg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_16_1_XVf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_17_1_CB7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_18_1_LhR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_19_1_PQw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_1_1_UTw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_20_1_X29.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_21_1_6rU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_2_1_q9a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_3_1_J0D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_4_1_SOd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_5_1_FE5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_6_1_n5o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_7_1_7ks.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_8_1_Wwc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYtt20to50/patTuple_skim_9_1_PD3.root',
]
        )
