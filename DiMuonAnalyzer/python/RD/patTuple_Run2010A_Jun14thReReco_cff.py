
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_10_1_csW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_11_1_RzV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_12_1_d0R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_13_1_chs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_14_1_JrF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_15_1_DB8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_16_1_pt9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_17_1_IyP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_18_1_yfL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_19_1_2Jz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_1_1_DuP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_2_1_u5G.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_3_1_IyR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_4_1_kic.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_5_1_AK9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_6_1_T6z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_7_1_ojn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_8_1_83n.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_9_1_q09.root',
]
        )
