################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3
### File index = 18
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3
### File index = 27
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_1_2_BJP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_2_2_zAd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_3_1_vDm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_4_2_YHC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_5_2_3qb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_6_2_jS8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_7_1_7W0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_8_1_kPd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_9_1_vZv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_10_0_bWu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_11_0_Ubw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_12_0_6v4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_14_0_6Yp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_16_1_Vkg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_17_0_7Hw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_18_0_j4e.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_19_0_vPW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_20_0_raA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_21_0_6jZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_22_0_do2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_23_0_nNg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_24_0_4Uw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_25_0_Sqq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_26_0_CJu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_27_1_5mr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_28_0_uMm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_29_0_xDu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_30_0_HY6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_31_0_1PZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_32_0_1MI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_34_0_rTF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_35_0_qsM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_36_0_DLF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_37_0_Hzt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_39_0_VGb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_40_0_3JO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_41_0_jd2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_42_0_Qe4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt20to50_3/patTuple_skim_43_0_yHw.root",
])
