
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_10_1_UU2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_11_1_uSX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_12_1_Cqv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_13_1_KrT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_14_1_eGz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_15_1_n1Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_16_1_Fv8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_17_1_zaF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_18_1_rcA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_19_1_C9a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_1_1_Bwq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_20_1_lvx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_2_1_r6z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_3_1_Wxt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_4_1_G7B.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_5_1_wwu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_6_1_iFY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_7_1_cpM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_8_1_xuT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v3/patTuple_skim_9_1_cdc.root',
]
        )
