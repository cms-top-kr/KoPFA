
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_10_1_C2S.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_11_1_pjK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_12_1_gGf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_13_1_mpj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_14_1_F14.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_15_1_NlQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_16_1_2c4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_17_1_Obs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_18_1_xmD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_19_1_lvb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_1_1_v2c.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_20_1_15M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_2_1_zKH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_3_1_aRT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_4_1_Z1H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_5_1_yFH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_6_1_0yJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_7_1_Y7T.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_8_1_VsI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/Wmunu/patTuple_muon_9_1_1AY.root',
]
        )
