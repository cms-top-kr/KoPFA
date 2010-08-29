
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_10_1_5Er.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_1_1_Rkm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_2_1_7RS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_3_1_jxR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_4_1_Drj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_5_1_a03.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_6_1_2m8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_7_1_iXa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_8_1_7GW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/Ztautau/patTuple_muon_9_1_gBu.root',
]
        )
