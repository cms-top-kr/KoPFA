import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_1_1_zHS.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_2_1_tzm.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_3_1_mhB.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_4_1_8eP.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_5_1_1r6.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_6_1_oyH.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_7_1_WoD.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_8_1_IRC.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_9_1_0ga.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/TTbarTuneZ2/patTuple_skim_10_1_vcM.root",
])
