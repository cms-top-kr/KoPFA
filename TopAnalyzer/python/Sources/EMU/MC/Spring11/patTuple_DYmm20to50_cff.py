
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_10_0_IAW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_11_0_3ha.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_12_0_FBx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_13_0_RTL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_14_0_Nuy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_15_0_rJq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_16_0_Xzx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_17_0_leV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_18_0_YAo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_19_0_WCN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_1_1_jUq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_20_0_4rF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_21_0_Q8o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_2_1_jer.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_3_0_X0v.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_4_0_OYV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_5_0_4h5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_6_0_A6e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_7_0_H8m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_8_0_8me.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/DYmm20to50/patTuple_skim_9_0_AeI.root',
]
        )
