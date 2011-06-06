import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_1_1_pcS.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_2_1_kV8.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_3_1_pD4.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_4_1_8Cb.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_5_1_MBM.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_6_1_nX6.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_7_1_yLM.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_8_1_UBL.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_9_1_S2V.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_10_1_Opr.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_11_1_tbA.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_12_1_uJw.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_13_1_HX2.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_14_1_54w.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_15_1_2UF.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_16_1_ZRu.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_17_1_Dgs.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_18_1_oky.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_19_1_gkG.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_20_1_hFN.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt20to50/patTuple_skim_21_1_qbg.root',
])
