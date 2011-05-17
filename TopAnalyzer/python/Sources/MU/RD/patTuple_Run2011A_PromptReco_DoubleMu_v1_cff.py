import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_1_3_sra.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_2_0_XXe.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_3_0_Hgm.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_4_0_qgz.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_5_0_XfI.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_6_0_iwe.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_7_0_sNb.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_8_0_UOu.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_9_0_aMI.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_10_0_lZU.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_11_0_0JT.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011data/DoubleMu/Mar29PromptReco_v8/Run2011A-PromptReco-v1_DoubleMu_V2/patTuple_skim_12_0_94h.root",
])
