################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/
### File index = 23
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/
### File index = 41
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_1_1_gta.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_2_1_998.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_3_1_kXK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_4_1_1Rk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_5_1_EQR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_6_0_4cf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_7_0_CyB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_8_0_xg1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_9_0_srU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_10_0_su0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_11_0_Q5R.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_12_0_qNg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_13_0_qO3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_14_0_TH5.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_15_0_4eh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_16_0_Z1q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_17_0_anZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_18_0_ZAZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_19_0_wt1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_20_0_OJs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_21_1_t1W.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_22_0_ctv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_23_0_taK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_24_0_gYj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_25_0_9uk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_26_2_jCD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_27_2_6fc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_28_2_ttA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_29_1_uQM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_30_2_PTw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_31_2_oZY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_32_2_Pgq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_33_2_r4Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_34_1_IOn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_35_1_eSU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_36_0_eQn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_37_0_s7o.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_38_0_flA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_39_0_vjs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_40_0_THX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_41_0_eto.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYmm_20to50_1/patTuple_skim_42_0_Jj7.root",
])
