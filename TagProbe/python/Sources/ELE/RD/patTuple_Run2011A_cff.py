
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_10_0_JXF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_11_0_w6a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_12_0_4J5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_13_0_uvw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_14_0_AMO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_15_0_CGN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_16_1_GVc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_17_0_XJt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_18_0_lRk.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_19_0_sgn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_1_1_U3a.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_20_0_21e.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_21_0_eW0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_22_1_MjS.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_23_1_VhR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_24_0_Hgh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_25_1_FxC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_26_0_SVp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_27_0_HbM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_28_0_90M.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_29_0_x8I.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_2_1_xSA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_30_0_HvK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_32_1_0ti.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_33_0_aIj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_34_0_Yd2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_36_0_WiK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_37_0_06R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_38_1_FEZ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_39_1_pBA.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_3_0_UFu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_4_0_c2R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_5_0_Ex2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_6_0_PED.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_7_0_ldI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_8_0_TUh.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleElectron/Dec19_Gsf/Run2011A-05Aug2011-v1-V2/patTuple_skim_9_0_YAG.root',
]
        )
