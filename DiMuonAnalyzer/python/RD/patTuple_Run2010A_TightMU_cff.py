
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_10_1_rMo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_11_1_1YT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_12_1_blI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_13_1_EXm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_14_1_nFg.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_15_1_i7h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_16_1_bo1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_17_1_TY7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_18_1_i9l.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_19_1_IDp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_1_1_WzI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_20_1_F7y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_21_1_cSS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_2_1_B8R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_3_1_oR9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_4_1_mh6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_5_1_CJM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_6_1_rie.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_7_1_L40.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_8_1_MsM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_TightMU/Run2010A-Nov4ReReco_v1/patTuple_skim_9_1_tce.root',
]
        )
