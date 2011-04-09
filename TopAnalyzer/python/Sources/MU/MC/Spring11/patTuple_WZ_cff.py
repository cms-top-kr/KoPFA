
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/WZ/patTuple_skim_1_1_8Fj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/MC/Spring11/WZ/patTuple_skim_2_1_Eml.root',
]
        )
