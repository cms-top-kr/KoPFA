import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/SingleTop_tW/patTuple_skim_1_1_XLy.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/SingleTop_tW/patTuple_skim_2_1_Oed.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/SingleTop_tW/patTuple_skim_3_1_daL.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/SingleTop_tW/patTuple_skim_4_1_13E.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/SingleTop_tW/patTuple_skim_5_1_kx9.root",
])
