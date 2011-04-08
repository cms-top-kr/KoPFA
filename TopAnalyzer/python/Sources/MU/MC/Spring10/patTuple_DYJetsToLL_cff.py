
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_10_1_dNc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_11_1_BE2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_12_1_gZh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_13_1_Fwl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_14_2_xim.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_15_1_Uei.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_16_1_8Kc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_17_1_tny.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_18_1_Xqr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_19_1_LC1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_1_1_nyt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_20_2_vlI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_21_1_lCj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_22_1_BN1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_23_1_X72.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_24_1_UUJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_2_1_EHl.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_3_1_MzY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_4_1_s5w.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_5_1_K4e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_6_1_eWP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_7_1_atU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_8_1_oQG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/DIMUSKIM/MC/Spring11/DYJetsToLL/patTuple_skim_9_1_FXf.root',
]
        )
