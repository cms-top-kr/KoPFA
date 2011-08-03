
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Summer11/ZPrimeM500W50_3/patTuple_skim_1_1_VcR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Summer11/ZPrimeM500W50_3/patTuple_skim_2_1_0Vj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Summer11/ZPrimeM500W50_3/patTuple_skim_3_1_4pS.root',
]
        )
