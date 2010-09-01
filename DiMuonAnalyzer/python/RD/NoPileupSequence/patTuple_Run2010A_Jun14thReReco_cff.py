
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_10_1_q71.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_11_1_2vQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_12_1_KCs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_13_1_ePZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_14_1_wt5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_15_1_caK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_16_1_gZN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_17_1_1Di.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_18_1_5lp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_19_1_aYd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_1_1_CIT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_2_1_uUU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_3_1_Lgr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_4_1_qZQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_5_1_f0H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_6_1_D1H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_7_1_jtv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_8_1_132.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Aug13_nopileup/Run2010A-Jun14thReReco_v1/patTuple_muon_9_1_ZHJ.root',
]
        )
