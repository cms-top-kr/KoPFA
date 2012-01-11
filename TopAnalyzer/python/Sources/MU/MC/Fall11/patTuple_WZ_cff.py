import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_1_1_Ieq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_2_1_F19.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_3_1_cOi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_4_1_YAY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_5_1_mmN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_6_1_yzC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_7_1_xKt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_8_1_RNs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_9_1_n1v.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_10_1_h0J.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/WZ_3/patTuple_skim_11_1_AgA.root",
])
