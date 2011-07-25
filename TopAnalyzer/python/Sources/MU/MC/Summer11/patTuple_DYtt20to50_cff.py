################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1
### File index = 23
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1
### File index = 2
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1
### File index = 30
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_1_1_fMw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_2_2_g1B.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_3_1_7Ma.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_4_2_1WQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_5_1_K8M.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_6_2_nFo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_7_1_bqR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_8_1_qFR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_9_1_7qN.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_10_1_1qP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_11_0_O0x.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_12_0_20Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_13_0_paj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_14_0_bNR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_15_0_kDS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_16_0_R33.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_17_0_TR1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_18_0_ITI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_19_0_IKb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_20_0_iW8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_21_1_JEX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_22_0_J80.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_23_1_nEh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_24_0_Oc0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_25_0_Pp3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_26_4_YjR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_27_0_CmX.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_28_0_Mvs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_29_0_CX1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_30_1_tpT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_31_0_8Le.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_32_0_yO6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_33_0_NtR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_34_0_woZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_35_0_Hxz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_36_0_7Ze.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_37_2_k8Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_38_1_iKR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_39_1_zwD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_40_1_6CS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_41_1_ZrD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_42_1_uCd.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_43_2_oD0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_44_1_Euu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_20to50_1/patTuple_skim_45_1_gXr.root",
])
