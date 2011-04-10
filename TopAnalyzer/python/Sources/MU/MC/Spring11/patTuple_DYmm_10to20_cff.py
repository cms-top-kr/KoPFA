
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_10_1_Q2C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_11_1_nGg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_12_1_Two.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_13_1_eAe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_14_1_eVW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_15_1_N0C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_16_1_bkL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_17_1_cGO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_18_1_00a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_19_1_m1O.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_1_1_ei5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_20_1_7yG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_2_1_uhh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_3_1_p80.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_4_1_5c5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_5_1_47F.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_6_1_HKi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_7_1_Tm3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_8_1_8Is.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_10to20_v2/patTuple_skim_9_1_GJZ.root',
]
        )
