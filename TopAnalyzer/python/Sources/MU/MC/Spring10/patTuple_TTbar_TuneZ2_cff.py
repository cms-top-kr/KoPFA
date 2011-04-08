
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_10_3_XM9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_11_3_Ho7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_12_3_sdE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_1_3_Ycd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_2_3_Hn4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_3_3_yyY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_4_3_AyC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_5_3_fip.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_6_3_hAn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_7_3_goK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_8_3_xzL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/TTbar/patTuple_skim_9_3_9k0.root',
]
        )
