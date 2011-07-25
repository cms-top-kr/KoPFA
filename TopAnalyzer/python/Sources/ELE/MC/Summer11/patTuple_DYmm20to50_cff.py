################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1
### File index = 16
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1
### File index = 40
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_1_1_4Eh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_2_2_Wy7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_3_1_h5G.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_4_2_mCU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_5_2_Ub7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_6_0_VR7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_7_0_x8B.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_8_0_doU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_9_0_vth.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_10_0_r9f.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_11_0_NWr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_12_0_D34.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_13_0_ALA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_14_0_fQI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_15_0_waE.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_16_4_0bu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_17_0_KZO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_18_0_4eo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_19_0_fpe.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_20_0_oW6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_21_0_HKh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_22_0_wvG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_23_1_JNZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_24_1_i2c.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_25_0_CYK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_26_0_EzO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_27_0_NpW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_28_0_lxS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_29_0_KoW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_30_0_q22.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_31_0_uTR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_32_0_moz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_33_0_NCD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_34_0_PIK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_35_0_2C0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_36_0_D2J.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_37_0_vbB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_38_3_ick.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_39_0_UKz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_40_3_Nak.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_41_2_Grm.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYmm_20to50_1/patTuple_skim_42_0_wtB.root",
])
