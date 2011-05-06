
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/SingleTop_tW/patTuple_skim_1_1_T7m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/SingleTop_tW/patTuple_skim_2_1_EqN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/SingleTop_tW/patTuple_skim_3_1_jQX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/SingleTop_tW/patTuple_skim_4_1_OPq.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11/SingleTop_tW/patTuple_skim_5_1_haG.root',
]
        )
