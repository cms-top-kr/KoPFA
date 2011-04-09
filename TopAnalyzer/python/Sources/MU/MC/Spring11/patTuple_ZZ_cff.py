
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_10_1_KkJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_11_1_eRM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_12_1_1sf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_13_1_Wpm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_14_1_CO2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_15_1_OyU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_16_1_W5L.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_17_1_AiQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_18_1_j0K.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_19_0_FTz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_1_1_k3x.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_20_0_r0c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_21_0_zQh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_22_0_FJD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_2_1_D70.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_3_1_I5z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_4_1_8pE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_5_1_VML.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_6_1_dcn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_7_1_HFV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_8_1_DQA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/ZZ/patTuple_skim_9_1_h31.root',
]
        )
