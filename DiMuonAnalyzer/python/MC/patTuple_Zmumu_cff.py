
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_10_1_XKB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_11_1_Hle.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_12_1_UnK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_13_1_laO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_14_1_1Wt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_15_1_iAZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_16_1_0FD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_17_1_CSv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_18_1_bOu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_19_1_8wh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_1_1_2lm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_20_1_thf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_2_1_exp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_3_1_3r9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_4_1_QDz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_5_1_qlO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_6_1_4Xw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_7_1_lwP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_8_1_qCl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_9_1_dWf.root',
]
        )
