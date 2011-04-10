
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_10_1_SAo.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_11_1_sgR.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_12_1_qBQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_13_2_niM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_14_1_nyL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_15_1_8wm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_16_1_B8h.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_17_1_aes.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_18_1_bY7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_19_1_UZm.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_1_1_Obb.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_20_0_Gx7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_2_1_Ug7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_3_1_KxL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_4_1_ko8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_5_1_J0R.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_6_1_Unu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_7_1_BYG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_8_1_W7T.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8_official/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_9_1_OUL.root',
]
        )
