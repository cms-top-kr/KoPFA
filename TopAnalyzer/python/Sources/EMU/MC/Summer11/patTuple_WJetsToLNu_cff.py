################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1
### File index = 52
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1
### File index = 62
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_1_1_SAK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_2_2_E38.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_3_1_BF0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_4_0_pO3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_5_0_s9L.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_7_0_xwB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_8_0_6Gu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_10_2_27Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_12_0_d0M.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_13_1_71Y.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_15_0_JMu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_16_0_oPk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_17_0_Kcv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_18_0_ZJ3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_19_0_9R0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_20_0_im9.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_22_1_Xsw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_23_1_0Zt.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_24_1_B2l.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_25_1_zNP.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_26_1_NtK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_27_1_b2W.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_28_1_R2X.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_29_0_Lk1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_30_0_SUQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_31_0_pZi.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_32_0_CUh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_33_0_OFc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_34_0_0mH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_35_0_Hde.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_36_0_A8t.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_37_0_W7I.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_38_0_cxx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_39_0_hFR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_40_1_W1j.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_41_1_tkK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_42_1_obS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_43_1_xNk.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_44_0_cZT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_46_0_2x3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_47_0_I7p.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_48_0_vP7.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_49_0_OSx.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_50_0_T5F.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_51_0_L5E.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_52_1_u88.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_53_0_RqJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_54_0_q8Q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_55_0_PED.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_56_0_hxj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_59_1_3YD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_60_0_o9d.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_61_0_gsS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_62_1_BM6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_63_1_mUG.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_64_1_gjB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_65_1_VXa.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_68_0_ixU.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/WJetsToLNu_1/patTuple_skim_70_0_1Gh.root",
])
