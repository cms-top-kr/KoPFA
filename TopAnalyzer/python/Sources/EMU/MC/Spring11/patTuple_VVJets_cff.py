
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/VVJets/patTuple_skim_1_1_onH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/VVJets/patTuple_skim_2_1_QXV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/VVJets/patTuple_skim_3_1_e4U.root',
]
        )
