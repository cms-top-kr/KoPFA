
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/SingleTop/patTuple_muon_1_1_UEx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/SingleTop/patTuple_muon_2_1_5yC.root',
]
        )
