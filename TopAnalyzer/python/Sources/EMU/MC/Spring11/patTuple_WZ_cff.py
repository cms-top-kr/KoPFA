
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/WZ/patTuple_skim_1_1_mcb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/WZ/patTuple_skim_2_1_jyZ.root',
]
        )
