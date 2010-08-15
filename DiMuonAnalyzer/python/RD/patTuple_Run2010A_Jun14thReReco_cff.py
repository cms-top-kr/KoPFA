
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_10_1_Rwu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_11_1_RnJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_12_1_zgD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_13_1_iVi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_14_1_e4e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_15_1_okj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_16_1_ZYW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_17_1_3U4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_18_1_61Y.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_19_1_g7D.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_1_1_FkG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_2_1_pty.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_3_1_dxp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_4_1_jhw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_5_1_JOr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_6_1_izt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_7_1_elG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_8_1_FpX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUONSKIM/Aug9th/Run2010A-Jun14thReReco_v1/patTuple_muon_9_1_guz.root',
]
        )
