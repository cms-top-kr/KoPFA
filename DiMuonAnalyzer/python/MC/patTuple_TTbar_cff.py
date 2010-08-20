
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_10_1_FCY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_11_1_Y1k.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_12_1_OKC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_13_1_NY5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_14_1_mvM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_15_1_sEC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_16_1_4hr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_17_1_lRl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_18_1_d3Q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_19_1_435.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_1_1_NGj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_20_1_5ra.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_2_1_O3M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_3_1_C8z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_4_1_Iao.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_5_1_laW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_6_1_Pqg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_7_1_uRD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_8_1_raf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_9_1_1kw.root',
]
        )
