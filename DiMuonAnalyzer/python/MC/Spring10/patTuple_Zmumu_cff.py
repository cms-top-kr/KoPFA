
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_10_1_zua.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_1_1_n2h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_2_1_eFg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_3_1_2l6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_4_1_Y1n.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_5_1_cYa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_6_1_Lgb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_7_1_NkH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_8_1_WET.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Zmumu/patTuple_muon_9_1_S2o.root',
]
        )
