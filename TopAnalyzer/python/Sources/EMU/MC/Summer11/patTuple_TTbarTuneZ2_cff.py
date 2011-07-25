################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2
### File index = 14
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2
### File index = 23
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2
### File index = 25
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_1_2_FXU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_2_0_mD2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_3_0_q7u.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_4_0_8fs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_5_1_StR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_6_0_xwH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_7_1_vji.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_8_1_6f0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_9_0_csG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_10_1_QLC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_11_0_gGZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_12_1_xjq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_13_0_sEr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_14_1_7Nj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_15_0_2hS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_16_0_gvT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_17_0_4tg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_18_0_USH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_19_0_7DK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_20_0_EQ7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_21_0_LPp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_22_0_Gcx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_23_3_E4h.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_24_0_6uC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_25_0_x1s.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_26_0_wTI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_27_0_1Z2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_28_0_7Cy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_29_0_OXn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_30_1_VWq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_31_0_QY3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_32_0_fxk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_33_0_4Vv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_34_0_xOB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_35_2_iKw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_36_1_ff3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_37_0_yKc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_38_0_uC3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/TTbar_2/patTuple_skim_39_0_nRa.root",
])
