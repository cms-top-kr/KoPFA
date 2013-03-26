import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_1_4_9aw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_3_2_m1S.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_3_4_48H.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_4_0_vXC.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_4_0_sRH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_7_3_Xqn.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_7_0_qN3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_11_3_3xU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_13_2_OCA.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_13_0_zl5.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_14_2_NKY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_15_1_5j2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_17_0_D1O.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_17_0_ZQj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_20_1_vYe.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_20_0_N6Q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_22_2_2Yo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_1/patTuple_skim_23_2_uez.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYee10to20_3/patTuple_skim_23_0_RhP.root",
])
