################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 10
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 10
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 1
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 21
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 22
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 23
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 24
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 26
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 26
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 28
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 29
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 29
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 2
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 30
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 32
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 33
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 34
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 35
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 35
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 3
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 44
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 4
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 4
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 5
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 5
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 7
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
### File index = 8
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1
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
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_1_5_VG8.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_2_5_EFj.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_3_4_KWl.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_4_5_QD3.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_5_5_bPx.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_6_3_e8Q.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_7_5_MbX.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_8_5_2DO.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_9_4_lTr.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_10_5_i8y.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_11_0_aYm.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_12_0_9hR.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_13_0_GL9.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_14_0_yUw.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_15_0_3HT.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_16_0_GVb.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_17_0_gPP.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_18_0_l2i.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_19_0_lxx.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_20_0_wEJ.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_21_0_YA8.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_22_0_YZF.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_23_0_p4b.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_24_0_RNk.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_25_0_C54.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_26_0_lEP.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_27_0_QPz.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_28_0_p4F.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_29_0_kof.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_30_0_PjG.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_31_0_Mti.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_32_5_bxo.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_33_5_SGR.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_34_5_bxU.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_35_5_wvh.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_36_3_s1c.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_37_0_8qJ.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_38_0_06k.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_39_0_QUV.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_40_0_dEr.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_42_0_RNp.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_43_0_Wzx.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt20to50_1/patTuple_skim_44_2_lFM.root",
])
