
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_10_0_SO6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_11_0_ZXG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_12_1_OLo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_13_1_pWT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_14_0_sOd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_15_3_k8S.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_16_1_2ok.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_17_1_m7q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_18_1_CdF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_1_1_gRN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_2_0_QO7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_3_0_ChI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_4_0_SSe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_5_3_syM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_6_0_JcG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_7_1_q1e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_8_0_Zwl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Fall10_TightMU/TTbarD6T/patTuple_skim_9_0_fLn.root',
]
        )
