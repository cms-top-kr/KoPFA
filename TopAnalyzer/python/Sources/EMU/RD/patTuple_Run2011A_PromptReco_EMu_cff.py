
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_10_0_NFu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_2_0_9Md.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_4_0_RA5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_5_0_Ovi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_6_1_3IF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_7_1_3Xo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_8_0_zCj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v1_MuEG/patTuple_skim_9_0_NXA.root',

	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_10_1_XSn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_11_1_VpB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_12_2_hxc.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_13_1_TIw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_14_1_hn3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_15_1_Yol.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_16_1_IU8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_17_2_BgB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_18_1_a7C.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_19_1_sWI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_21_1_CUm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_22_1_F2H.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_2_1_igT.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_3_1_ZRm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_4_2_rXC.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_5_1_zkB.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_6_3_lHX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_7_1_VKK.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_8_2_lyP.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/MuEG/Apr29/Run2011A-PromptReco-v2_MuEG/patTuple_skim_9_3_sXe.root',
]
        )
