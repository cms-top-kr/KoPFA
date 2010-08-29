
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_10_1_uhS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_1_1_gIR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_2_1_3qO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_3_1_lCC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_4_1_P6m.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_5_1_juH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_6_1_Coy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_7_1_pBs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_8_1_DCG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/ZJets/patTuple_muon_9_1_1mX.root',
]
        )
