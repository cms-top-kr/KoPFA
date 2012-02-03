################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1
### File index = 15
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1
### File index = 17
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1
### File index = 43
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_1_1_CYx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_2_1_3T3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_3_2_sd4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_4_1_6Or.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_5_1_2aF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_6_1_srY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_7_1_VF1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_8_1_HyC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_9_3_MOg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_10_1_Iy6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_11_1_TwY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_12_1_UGr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_13_1_71S.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_14_1_CQu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_15_1_3Qd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_16_2_sJ7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_17_2_v0e.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_18_1_Yhx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_19_1_Smi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_20_1_54R.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_21_1_eij.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_22_1_dF9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_23_1_EHZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_24_1_Ked.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_25_2_kpH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_26_3_isp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_27_1_UH7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_28_1_nha.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_29_1_LKu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_30_1_QvZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_31_2_2Qh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_32_1_VrR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_33_0_WYu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_34_1_uGw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_35_1_NFk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_36_1_4bJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_37_1_O88.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_38_1_3SN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_39_0_HNt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_40_0_QIK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_41_1_dfW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_42_1_WcB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_43_3_yF6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_44_2_9Yx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_45_1_fTN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_46_0_WDZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_47_1_l1A.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_48_1_ysA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_49_2_aQg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_50_2_nw7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_51_0_56C.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_52_2_TrM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-05Aug2011-v1_1/patTuple_skim_53_1_3AA.root",
])
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1
### File index = 113
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1
### File index = 49
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1
### File index = 50
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1
### File index = 83
################################################################################

readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_1_2_HXf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_2_0_5gv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_3_1_nfR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_4_0_OAz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_5_1_COm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_6_1_Toc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_7_1_orI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_8_1_eeP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_9_0_BwX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_10_0_xrZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_11_1_gKM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_12_1_4OR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_13_2_a1H.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_14_0_7jL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_15_1_mpz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_16_0_MH7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_17_0_xMt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_18_1_feM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_19_2_n83.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_20_1_Zl9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_21_1_JQQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_22_0_j8i.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_23_0_28l.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_24_0_Wdu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_25_1_tXC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_26_0_OeG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_27_1_yA2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_28_1_66M.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_29_1_QS7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_30_1_ng6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_31_1_EWJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_32_1_1US.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_33_0_FJF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_34_0_gD9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_35_0_8up.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_36_2_Iug.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_37_2_a8K.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_38_1_zW2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_39_1_JBi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_40_1_cis.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_41_3_Rsr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_42_1_xSy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_43_1_M08.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_44_0_xas.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_45_2_egG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_46_1_tr1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_47_1_NPA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_48_0_Pcd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_49_1_DKo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_50_2_khI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_51_1_g7B.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_52_1_v4f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_53_0_Mjw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_54_1_ztF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_55_1_Dl9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_56_2_bSr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_57_0_ebZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_58_2_V7X.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_59_0_jVk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_60_1_hdf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_61_1_Fnc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_62_0_kmi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_63_0_Ct8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_64_1_jGM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_65_0_dsL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_66_0_KDd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_67_1_mem.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_68_2_HBH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_69_1_yHS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_70_0_5CQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_71_0_TDa.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_72_0_fKp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_73_1_PHv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_74_0_6Lo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_75_1_6UX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_76_0_OR7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_77_0_YC1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_78_2_KPA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_79_1_y7f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_80_1_lGr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_81_0_QU3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_82_1_qwr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_83_0_nWI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_84_0_p1t.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_85_1_Dnp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_86_2_MQB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_87_0_Qjs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_88_1_PB4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_89_1_2Yd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_90_2_aaE.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_91_1_bRn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_92_1_YCA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_93_0_Udd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_94_0_EyO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_95_0_FOR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_96_0_2k8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_97_1_9nI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_98_0_5XZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_99_0_XqK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_100_1_ghX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_101_0_MEa.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_102_0_zVT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_103_0_KI7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_104_1_XqI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_105_0_qBd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_106_1_1KL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_107_1_gIq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_108_0_yZK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_109_1_ktb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_110_2_gVd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_111_1_sJu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_112_0_In4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_113_1_98q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_114_0_6PG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_115_1_1DK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_116_0_GmX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_117_0_9ag.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_118_1_jht.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-May10ReReco-v1_1/patTuple_skim_119_0_2eE.root",
])
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 114
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 130
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 145
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 160
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 179
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 181
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 183
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 188
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 189
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 191
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 192
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 193
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 194
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 202
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 205
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 206
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 207
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1
### File index = 76
################################################################################

readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_1_2_tXz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_2_0_Ffd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_3_0_DjN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_4_0_vij.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_5_3_dZG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_6_3_FyD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_7_5_48C.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_8_1_or2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_9_2_9xl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_10_3_lJP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_11_4_d8P.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_12_1_sWf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_13_5_Zyl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_14_1_BCc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_15_1_nhb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_16_1_kVu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_17_1_Sm2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_18_2_S2D.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_19_0_Tat.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_20_0_arW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_21_0_wHR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_22_2_VJT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_23_2_aQ6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_24_2_eXg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_25_1_W7f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_26_1_dWL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_27_1_vf7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_28_1_IL7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_29_1_6iM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_30_1_aTd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_31_1_KK2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_32_1_ONp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_33_2_V76.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_34_1_h8i.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_35_1_NJQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_36_1_1oJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_37_2_xjb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_38_1_khd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_39_0_Cb4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_40_1_ak6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_41_0_5hf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_42_0_D5L.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_43_0_St2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_44_0_OZu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_45_0_8pr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_46_0_CUT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_47_0_fks.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_48_0_RJA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_49_0_8RB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_50_0_Qzt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_51_0_Ntl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_52_0_VLh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_53_0_5fz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_54_0_Qma.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_55_0_15H.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_56_0_Dcj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_57_0_HTb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_58_0_vlW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_59_0_Lk4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_60_0_sFL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_61_3_O7s.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_62_1_0UO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_63_3_qDN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_64_0_DmL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_65_0_JuR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_66_0_cfV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_67_0_75k.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_68_0_A6H.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_69_0_nT3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_70_0_pQr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_71_0_dK5.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_72_2_y9F.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_73_2_NdV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_74_1_ETt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_75_1_FZX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_76_1_I8i.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_77_1_aL7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_78_2_jXL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_79_1_xMk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_80_2_tx6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_81_2_74n.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_82_2_T5G.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_83_2_mtn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_84_0_N3r.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_85_0_Qa4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_86_0_HHQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_87_0_CNg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_88_0_bBB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_89_0_Vg8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_90_0_MDD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_91_0_aRG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_92_0_YWq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_93_1_BXr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_94_2_i3z.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_95_2_Bee.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_96_2_i3e.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_97_2_qMn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_98_1_vBG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_99_1_At0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_100_2_yJx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_101_1_TNm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_102_1_6p1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_103_2_wS6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_104_2_jOM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_105_1_dwz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_106_1_Cfy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_107_3_T10.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_108_2_XH8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_109_3_irO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_110_1_SVC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_111_0_rjO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_112_0_Hb9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_113_0_Vs0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_114_1_nDg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_115_0_Eyq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_116_2_bAb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_117_1_l4m.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_118_1_bYd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_119_2_QEu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_120_2_Xed.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_121_2_KBm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_122_0_fkB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_123_0_W5x.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_124_0_j14.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_125_0_UUv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_126_0_TeO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_127_1_fZ3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_128_3_2UV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_129_1_dGo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_130_2_koe.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_131_2_CuJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_132_2_KIm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_133_2_oBH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_134_0_3Rn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_135_3_456.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_136_4_1b6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_137_1_U0l.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_138_1_eJ7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_139_5_7n6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_140_4_uTB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_141_0_xxK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_142_0_N2F.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_143_0_gPr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_144_0_cIs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_145_1_XSi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_146_0_pRU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_147_2_8um.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_148_2_pVR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_149_1_yAR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_150_1_BwB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_151_1_7S4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_152_1_SaD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_153_5_c35.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_154_2_0qi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_155_2_baV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_156_0_24u.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_157_0_tyO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_158_0_MQb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_159_0_y1g.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_160_1_eXo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_161_5_uVe.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_162_1_VNu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_163_1_bvM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_164_1_gK8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_165_1_Ib7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_166_2_UeU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_167_3_9do.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_168_3_uBP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_169_1_nXF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_170_2_Wut.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_171_2_bdW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_172_1_gHv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_173_1_41W.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_174_4_m8B.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_175_1_Eyk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_176_1_zNP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_177_3_62c.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_178_0_miY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_179_1_6df.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_180_0_107.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_181_1_z03.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_182_0_uVn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_183_1_hop.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_184_1_wQe.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_185_3_uTM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_186_1_IcG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_187_1_OsY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_188_1_EwX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_189_1_BKN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_190_0_izb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_191_2_PCc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_192_1_f2B.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_193_1_YL3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_194_1_oiq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_195_0_YpX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_196_0_l3z.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_197_0_MKn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_198_0_4T4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_199_0_Rha.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_200_0_Q5D.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_201_0_m6U.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_202_1_0Fc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_203_0_Fmw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_204_0_m90.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_205_1_pfN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_206_1_czu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_207_1_zrK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_208_4_Flm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v4_1/patTuple_skim_209_2_5uZ.root",
])
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1
### File index = 27
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1
### File index = 34
################################################################################

readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_1_1_lLB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_2_1_Vbp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_3_1_q6v.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_4_0_epZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_5_0_m3q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_6_0_5Xq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_7_1_OWh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_8_0_EHw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_9_0_wvB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_10_0_jGD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_11_0_Kvn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_12_0_r4y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_13_0_vqn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_14_0_PCl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_15_0_xlv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_16_0_mOS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_17_0_CRL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_18_0_TCO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_19_0_QOm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_20_0_gm7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_21_0_7np.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_22_0_DJU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_23_0_tDE.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_24_0_Dr4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_25_0_pRn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_26_0_gqb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_27_1_Vn9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_28_1_mVK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_29_0_vDy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_30_0_yBw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_31_0_YeT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_32_0_8JD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_33_1_hR0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_34_3_72J.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_35_1_pHg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_36_3_m7z.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_37_1_wNG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_38_1_8BZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_39_1_gOC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_40_1_AXw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_41_3_00v.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_42_1_4d1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_43_1_dMv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_44_0_RHG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_45_0_hoo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_46_0_AkZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_47_1_MuF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_48_0_BfX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_49_0_rnu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_50_1_49a.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_51_1_iyN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_52_1_3Cf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_53_1_OnP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_54_1_nLp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_55_3_9as.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_56_1_Tha.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_57_0_J79.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_58_0_3sx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_59_1_Gvg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_60_0_cjo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_61_0_qxL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_62_0_9jP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_63_0_wlr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_64_0_zWD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_65_0_iMY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_66_0_9Ah.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_67_0_zrD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_68_1_B9u.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_69_0_LZS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_70_0_vpG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_71_0_Qrv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_72_1_jfP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_73_0_HGV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_74_0_h8U.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_75_0_Q44.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_76_0_bwl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_77_1_Eoa.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_78_3_a91.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_79_0_wn6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_80_0_szE.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_81_0_uoz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_82_0_REB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_83_0_Iij.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_84_0_KSY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_85_0_WSO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_86_0_ngt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_87_0_qiU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_88_0_8Ee.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_89_0_0Ni.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_90_0_tiT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_91_0_YZt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/RD/SingleElectron/20120126_1/Run2011A-PromptReco-v6_1/patTuple_skim_92_0_jhy.root",
])
