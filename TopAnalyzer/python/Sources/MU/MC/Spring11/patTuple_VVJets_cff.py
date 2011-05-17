import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/VVJets/patTuple_skim_1_1_C9P.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/VVJets/patTuple_skim_2_1_nbb.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/VVJets/patTuple_skim_3_1_m0X.root",
])
