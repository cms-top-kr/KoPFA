
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_10_1_Ck9.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_11_1_ykr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_12_1_Bow.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_13_1_ZIu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_14_1_KW8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_15_1_ikF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_16_1_lAv.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_17_1_Ke1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_18_1_Z9x.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_19_1_721.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_1_1_cjL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_20_0_oOx.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_2_1_ASX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_3_1_hi1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_4_1_zAY.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_5_1_SE4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_6_1_fPp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_7_1_GDz.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_8_1_zQU.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr8/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_9_1_zMU.root',
]
        )
