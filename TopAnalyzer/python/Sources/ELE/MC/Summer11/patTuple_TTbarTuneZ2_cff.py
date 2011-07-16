################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 21
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 22
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 22
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 3
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 5
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/
### File index = 9
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_1_1_bOG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_2_1_eHp.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_3_3_H6i.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_4_1_zXl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_5_3_HtF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_6_1_18M.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_7_1_lqy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_8_1_MLX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_9_3_Il7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_10_1_mNG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_11_1_0Sq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_12_1_6Bh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_13_1_bmL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_14_1_o5j.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_15_1_gN0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_16_1_00Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_17_1_pIA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_18_1_E5n.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_19_1_0Ht.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_20_1_2RR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_21_3_ZZU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_22_6_mJx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_23_1_T8f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_24_1_UxN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_25_1_FGf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_26_1_paA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_27_1_hef.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_28_1_6fr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_29_1_RJI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_30_1_0CS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_31_1_AqV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_32_1_sEd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_1/patTuple_skim_33_1_G24.root",
])
