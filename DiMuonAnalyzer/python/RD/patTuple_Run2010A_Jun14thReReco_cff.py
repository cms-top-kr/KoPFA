
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_10_1_Wq3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_11_1_3ii.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_12_1_XIa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_13_1_ZHy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_14_1_69D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_15_1_dHJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_16_1_58n.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_17_1_P2J.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_18_1_9Ll.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_19_2_uI9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_1_1_Bj7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_2_1_1Mb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_3_1_9ZM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_4_1_KCc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_5_1_JiW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_6_1_0ae.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_7_1_9kd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_8_1_pBm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13/Run2010A-Jun14thReReco_v1/patTuple_muon_9_1_IY5.root',
]
        )
