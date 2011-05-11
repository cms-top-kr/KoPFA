
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_10_2_poH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_11_2_BFa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_12_2_jzk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_13_2_ZZq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_14_2_iOo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_15_2_zcB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_16_2_MEy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_17_2_nuH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_18_2_WD0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_19_2_UJC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_1_2_W13.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_20_2_Pci.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_21_2_6R6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_2_2_ing.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_3_2_RFk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_4_2_FEv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_5_2_CoE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_6_2_kam.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_7_2_SAW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_8_2_Be6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYee20to50/patTuple_skim_9_2_hxd.root',
]
        )
