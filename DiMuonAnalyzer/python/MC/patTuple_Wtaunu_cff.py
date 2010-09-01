
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_10_1_qpN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_11_1_iYJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_12_1_EXu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_13_1_PN6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_14_1_u9R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_15_1_lMU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_16_1_KXt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_17_1_AKc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_18_1_EjT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_19_1_Y9h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_1_1_6ld.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_20_1_zFy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_2_1_IVl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_3_1_MD7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_4_1_RSF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_5_1_Dnz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_6_1_kjg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_7_1_GxF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_8_1_9iv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wtaunu/patTuple_muon_9_1_t8c.root',
]
        )
