################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1
### File index = 8
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_1_1_76d.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_2_1_6eb.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_3_1_pXX.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_4_0_Q3V.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_5_0_qox.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_6_0_UbL.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_7_0_v7I.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_8_3_l8e.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_9_0_F42.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_10_0_vPc.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_11_0_DbB.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_12_0_4vM.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_13_0_RBt.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_14_0_dp1.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_15_0_2bK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_16_0_EQi.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_17_1_IPW.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_18_0_fs9.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_19_0_1B9.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_20_0_5Nd.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_21_0_Bg5.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_22_0_oFg.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_23_0_0cc.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_24_0_Rea.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_25_0_njT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_26_0_Ylb.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_27_0_5HE.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_28_0_3aS.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_29_0_QUQ.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_30_2_scU.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_31_0_nBA.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_32_0_djJ.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_33_0_n6f.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_34_0_PY1.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_35_0_zlb.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_36_0_SoW.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_37_0_Pjs.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_38_0_KA9.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_39_0_PEX.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_40_0_apx.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYmm20to50_1/patTuple_skim_41_1_Mk5.root",
])
