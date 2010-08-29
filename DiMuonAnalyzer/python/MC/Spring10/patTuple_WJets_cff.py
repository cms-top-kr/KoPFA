
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_10_1_WvC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_1_1_R81.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_2_1_In5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_3_1_Y0C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_4_1_ixL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_5_1_X1l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_6_1_UAV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_7_1_ag1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_8_1_2PR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/WJets/patTuple_muon_9_1_1fU.root',
]
        )
