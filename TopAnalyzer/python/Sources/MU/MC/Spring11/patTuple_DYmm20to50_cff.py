import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_1_3_huu.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_2_1_bII.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_3_0_qhD.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_4_0_msf.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_5_0_Dmz.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_6_0_k6P.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_7_0_nPj.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_8_1_Tps.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_9_0_scx.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_10_3_fDL.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_11_3_xhZ.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_12_0_Qjp.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_13_0_Kse.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_14_0_jUt.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_15_0_tH9.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_16_0_ZmW.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_17_0_g0d.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_18_0_zuY.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_19_0_rfL.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_20_0_aaB.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Spring11/Mar29PromptReco_v8/DYmm20to50/patTuple_skim_21_0_HPS.root",
])
