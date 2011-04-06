
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_10_1_fLX.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_11_1_DIa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_12_1_9Qf.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_13_1_So6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_14_1_rgM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_15_1_x0Q.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_16_1_7xN.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_17_1_OgV.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_18_1_TWE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_19_0_qKy.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_1_1_HAt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_2_1_2NW.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_3_1_8EE.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_4_1_yQe.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_5_1_wrd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_6_1_tsM.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_7_1_cJ2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_8_1_2fL.root',
	'rfio:///castor/cern.ch/user/t/tjkim/2011data/DoubleMu/Apr6/Run2011A-PromptReco-v1_DoubleMu/patTuple_skim_9_1_FwF.root',
]
        )
