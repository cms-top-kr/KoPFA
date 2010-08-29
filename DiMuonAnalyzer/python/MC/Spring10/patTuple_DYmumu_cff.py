
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_10_1_tl3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_11_1_PWy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_12_1_ll3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_13_1_aUJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_14_1_O6O.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_15_1_iwI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_16_1_o7o.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_17_1_7rx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_18_1_v5s.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_19_1_lMm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_1_1_14D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_20_2_qPk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_2_1_dan.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_3_1_mC1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_4_1_T6A.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_5_1_UNs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_6_1_xbr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_7_2_xlz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_8_1_SfU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Spring10/DYmumu/patTuple_muon_9_1_yRj.root',
]
        )
