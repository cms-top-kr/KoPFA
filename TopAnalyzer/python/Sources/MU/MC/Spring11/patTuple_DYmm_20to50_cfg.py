
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_10_0_UfW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_11_0_IwS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_12_0_7Gs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_13_0_Z7I.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_14_0_xXR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_15_0_h6I.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_16_0_pOM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_17_0_snf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_18_0_3ao.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_19_0_FNl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_1_1_TsR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_20_0_wmc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_21_0_aXK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_2_1_k6p.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_3_0_PFO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_4_0_WOw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_5_0_AaH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_6_0_vdk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_7_0_p2I.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_8_0_WaY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYmm_20to50_v2/patTuple_skim_9_0_eKg.root',
]
        )
