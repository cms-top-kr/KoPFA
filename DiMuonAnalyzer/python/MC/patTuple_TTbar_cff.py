
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_10_1_UXe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_11_1_emH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_12_1_N4J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_13_1_s7J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_14_1_YYx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_15_1_jMg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_16_1_dAH.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_17_1_ULX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_18_1_p8D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_19_1_2Gv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_1_1_RGC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_20_1_ba2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_2_1_t7V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_3_1_wCO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_4_1_VDa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_5_1_p5x.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_6_1_gA8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_7_1_Yfz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_8_1_lvU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/MC/Summer10/TTbar/patTuple_muon_9_1_Egu.root',
]
        )
