
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_10_1_7CN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_1_1_GNS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_2_1_ny5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_3_1_44t.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_4_1_sPR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_5_1_7TA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_6_1_rs2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_7_1_bSd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_8_1_EEb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Zmumu/patTuple_muon_9_1_mQp.root',
]
        )
