import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_1_1_Q2M.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_2_1_MMs.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_3_1_XRB.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_4_2_AJY.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_5_1_g66.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_6_1_qoF.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_7_5_cuT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_8_0_ZuU.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_9_4_lOp.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_10_0_8gr.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_11_0_jjt.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_12_0_l9P.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_13_0_naJ.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_14_0_DLh.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_15_0_qFb.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_16_0_rio.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/WJetsToLNu_1/patTuple_skim_17_0_1ps.root",
])
