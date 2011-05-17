import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_1_1_D5Z.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_2_1_hNG.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_3_1_JQh.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_4_1_Iyo.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_5_1_iNE.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_6_1_gQh.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_7_1_frl.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_8_1_6hp.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_9_1_v61.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_10_1_wRh.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_11_1_5gV.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_12_1_aPB.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_13_3_8Qk.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_14_1_JUg.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_15_1_kg4.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_16_1_pIO.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_17_1_O8g.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_18_1_avx.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_19_1_PfH.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_20_2_QYk.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYee20to50/patTuple_skim_21_1_5C9.root",
])
