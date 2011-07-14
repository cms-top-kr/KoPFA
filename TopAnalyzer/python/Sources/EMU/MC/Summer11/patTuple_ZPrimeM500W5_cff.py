
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ZPrime_M500W5_1/patTuple_skim_1_1_rUl.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ZPrime_M500W5_1/patTuple_skim_2_1_yXQ.root',
]
        )
