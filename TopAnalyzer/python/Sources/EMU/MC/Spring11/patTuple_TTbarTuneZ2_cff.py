
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_10_1_965.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_1_1_igH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_2_1_DR6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_3_2_GmV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_4_1_aYT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_5_2_URQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_6_2_uZl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_7_2_xsQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_8_2_wX7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/EMUSKIM/MC/Spring11_v2/TTbarTuneZ2/patTuple_skim_9_1_rfR.root',
]
        )
