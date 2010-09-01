
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_10_1_RQg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_1_1_JBM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_4_1_aJE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_5_1_wpT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_6_1_J9Z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_7_1_uxh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_8_1_9Nw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Ztautau/patTuple_muon_9_1_DRj.root',
]
        )
