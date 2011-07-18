import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_1_4_Yco.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_2_2_MHt.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_3_0_B2a.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_5_0_DzO.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_6_1_B84.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_7_1_mAc.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_8_0_9Wh.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_9_0_BdD.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYmm10to20_1/patTuple_skim_10_2_22G.root",
])
