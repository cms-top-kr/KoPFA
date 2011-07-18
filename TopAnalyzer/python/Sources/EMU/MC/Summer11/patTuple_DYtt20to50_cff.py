################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/
### File index = 23
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/
### File index = 26
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/
### File index = 26
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/
### File index = 5
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_1_3_Gzj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_2_3_gz6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_3_3_6LC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_4_3_My0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_5_5_XLT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_6_2_VLh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_7_2_yyI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_8_3_h5Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_9_3_G1Z.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_10_3_jRK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_11_0_jsH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_12_0_38R.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_13_0_mEx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_14_0_ILj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_15_0_G7f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_16_0_Vjp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_17_0_KGK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_18_0_EUw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_19_0_G4l.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_20_0_E6t.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_21_0_fTC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_22_0_If0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_23_3_98m.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_24_1_Tra.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_25_0_m6l.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_26_3_t4L.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_27_0_Nks.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_28_0_FWF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_29_0_vvy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_30_0_CCB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_31_0_7x4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_32_3_ojG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_33_2_2mP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_34_2_ydI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_35_3_tHX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_36_3_DiN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_37_0_3Gy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_38_0_7PO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_39_0_lO5.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_40_0_8OG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_41_0_i9W.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_42_0_gsH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_43_1_CkH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_44_0_3uf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_20to50_1/patTuple_skim_45_0_rzN.root",
])
