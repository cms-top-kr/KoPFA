
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/ZPrime_M500W50_1/patTuple_skim_1_2_wv6.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/ZPrime_M500W50_1/patTuple_skim_2_2_bW5.root',
	'rfio:///castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/ZPrime_M500W50_1/patTuple_skim_3_2_28d.root',
]
        )
