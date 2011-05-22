import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_1_1_kgH.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_2_1_Vtp.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_3_1_Z4v.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_4_1_UTJ.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_5_1_xGi.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_6_1_Z4X.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_7_1_Zvf.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_8_1_cfi.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_9_1_yxS.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_10_1_WXf.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_11_1_AmQ.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v9/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_12_1_ciW.root",
])
